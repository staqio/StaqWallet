# Staq Wallet

A modular, embeddable wallet solution with support for onboarding, payments, KYC, and native biometric authentication.

## 🔧 Requirements

- **iOS**: 16.0+
- **Xcode**: 27.0+ (Swift 6.4)

## 📦 Installation

### Swift Package Manager

1. Add the package dependency to your **Package.swift** file and include it in the dependencies array:

```swift
dependencies: [
    .package(url: "https://github.com/staqio/StaqWallet", exact: "5.1.0")
]
```

2. Add StaqWallet to your target dependencies:

```swift
targets: [
    .target(name: "TargetName", dependencies:[
        "StaqWallet"
    ])
]
```

3. Run the following command in terminal to download the package and its dependencies:

```sh
swift package update
```

Or in Xcode: File → Add Packages → paste the repo URL.

## 🚀 Getting Started

**Step 1 – Initialize the SDK**

You **must** call `StaqWalletManager.initialize(withConfig:)` once, early in your app’s lifecycle, typically in `AppDelegate.application(_:didFinishLaunchingWithOptions:)` or in your `@main` SwiftUI entry point. Call it on the main actor.

```swift
let config = StaqWalletConfig(
    merchantIdentifier: "merchant.com.example",
    language: .en, // or .ar
    walletEnv: .production // or .development
)

StaqWalletManager.initialize(withConfig: config)
```

**Step 2 – Describe the User**

```swift
let user = StaqWalletUser(
    userId: "user-id",
    secret: "user-secret",
    userType: .local, // or .international, or nil
    nationalId: "user-national-id",
    idToken: "id-token-from-your-backend"
)
```

**Step 3 – Present the Wallet**

`StaqWalletManager.makeStartView(user:onClose:)` returns a SwiftUI view. Present it full screen and dismiss it in `onClose`:

```swift
struct ContentView: View {
    let user: StaqWalletUser
    @State private var isWalletPresented = false

    var body: some View {
        Button("Open Wallet") { isWalletPresented = true }
            .fullScreenCover(isPresented: $isWalletPresented) {
                StaqWalletManager.makeStartView(user: user) {
                    isWalletPresented = false
                }
            }
    }
}
```

For UIKit, see [Minimum Example Code to Start the Wallet Flow](#minimum-example-code-to-start-the-wallet-flow).

## 🛠️ Usage

### StaqWalletConfig

Used to configure the SDK during app launch. You must create and pass this config to `StaqWalletManager.initialize(withConfig:)` before starting any flows.

| Name                | Type                    | Description                                                                   |
|---------------------|-------------------------|-------------------------------------------------------------------------------|
| merchantIdentifier  | `String`                | Apple Pay merchant identifier, used for Apple Pay top-ups.                    |
| language            | `StaqWalletLanguage`    | Initial wallet language (`.en` or `.ar`).                                     |
| walletEnv           | `StaqWalletEnvironment` | SDK operating environment (`.production` or `.development`). Defaults to `.production`. |

### StaqWalletUser

Represents a specific user within the wallet. Pass it when presenting the wallet and when calling `StaqWalletPay` methods. It contains the data used for authentication, personalization, and request headers.

| Name       | Type                       | Description                                                                                         |
|------------|----------------------------|-----------------------------------------------------------------------------------------------------|
| userId     | `String`                   | The unique identifier of the user.                                                                  |
| secret     | `String`                   | Secret token used for authentication.                                                               |
| userType   | `StaqWalletUser.UserType?` | `.local` (residents, verified with Nafath) or `.international` (foreign visitors). Optional: if `nil`, the user chooses during onboarding. |
| nationalId | `String?`                  | National identification number. Optional.                                                          |
| idToken    | `String`                   | Identity token issued by your backend or identity provider. The wallet exchanges it for a wallet session, which is the only way to sign in. |

Always pass a current `idToken`: the wallet uses it whenever the stored session can't be restored. If the backend rejects it as expired, the `StaqWalletPay` methods throw `StaqWalletPayError.idTokenExpired`; get a new token from your backend and call again. The backend may ask the user to confirm the session with an OTP; the wallet handles that step.

### Wallet Tiers

| Tier   | Who                  | How the user gets it                                                                 |
|--------|----------------------|--------------------------------------------------------------------------------------|
| Tier 0 | Every wallet user    | Registered automatically the first time the user opens the wallet or uses `StaqWalletPay`. |
| Tier 1 | Local users          | Upgraded inside the wallet, verified with Nafath.                                    |
| Tier 2 | International users  | Upgraded inside the wallet with visa details and identity verification (document and face scan). |

### Changing the Language

Set the initial language in `StaqWalletConfig`. To change it later, call on the main actor:

```swift
StaqWalletManager.changeLanguage(.ar) // or .en
```

### Closing the Wallet

The wallet calls the `onClose` closure passed to `makeStartView(user:onClose:)` when it closes: when the user closes it, or when the wallet ends the session and has to be opened again, for example when the `idToken` is no longer valid after the user resets a forgotten passcode. Dismiss the wallet view there.

### Apple Pay Setup

Tier 1 top-ups support Apple Pay. Add the **Apple Pay** capability to your app target with the merchant identifier you pass in `StaqWalletConfig.merchantIdentifier`.

### Face ID Setup

Enable Face ID in your app by adding the following key to your **Info.plist** file:

```xml
<key>NSFaceIDUsageDescription</key>
<string>We use Face ID to authenticate your identity quickly and securely.</string>
```

Without this key, the application will crash when attempting to use Face ID.

### Document Scanning & KYC Verification

To enable document scanning and KYC verification, add camera and microphone permissions to your **Info.plist**:

```xml
<key>NSCameraUsageDescription</key>
<string>We need access to the camera to capture your documents for verification purposes.</string>
<key>NSMicrophoneUsageDescription</key>
<string>We need access to the microphone to assist in the verification process.</string>
```

If these permissions are missing, the app will crash when trying to access the camera or microphone.

### Domestic User Authentication Redirection

To support user authentication via **Nafath** services, add the following query scheme to your **Info.plist**:

```xml
<key>LSApplicationQueriesSchemes</key>
<array>
    <string>nafath</string>
</array>
```

This allows your app to detect the **Nafath** app and redirect users for registration.

### Handling Navigation for Ordered Packages

The domestic wallet does not include built-in navigation for displaying ordered packages. You must manually handle navigation by providing a callback to `setPackagesNavigationCallback`:

```swift
StaqWalletManager.setPackagesNavigationCallback {
    // Implement your custom navigation logic here
}
```

### Minimum Example Code to Start the Wallet Flow

Below is an example implementation within `SceneDelegate`:

```swift
import StaqWallet
import SwiftUI
import UIKit

class SceneDelegate: UIResponder, UIWindowSceneDelegate {
    var window: UIWindow?

    func scene(
        _ scene: UIScene,
        willConnectTo session: UISceneSession,
        options connectionOptions: UIScene.ConnectionOptions
    ) {
        guard let windowScene = scene as? UIWindowScene else { return }
        let window = UIWindow(windowScene: windowScene)
        self.window = window

        let rootViewController = UIViewController()
        window.rootViewController = rootViewController
        window.makeKeyAndVisible()

        let config = StaqWalletConfig(
            merchantIdentifier: "merchant.com.example",
            language: .ar, // or .en
            walletEnv: .production // or .development
        )

        StaqWalletManager.initialize(withConfig: config)

        StaqWalletManager.setPackagesNavigationCallback {
            // Implement your custom navigation logic here
        }

        let user = StaqWalletUser(
            userId: "user-id",
            secret: "user-secret",
            userType: .local, // or .international, or nil
            nationalId: "user-national-id",
            idToken: "id-token-from-your-backend"
        )

        let walletViewController = UIHostingController(
            rootView: StaqWalletManager.makeStartView(user: user) {
                rootViewController.dismiss(animated: true)
            }
        )
        walletViewController.modalPresentationStyle = .fullScreen

        // Present once the window is on screen.
        DispatchQueue.main.async {
            rootViewController.present(walletViewController, animated: true)
        }
    }
}
```

<br />

# Staq Wallet Pay

The `StaqWalletPay` class provides Wallet Pay functionality without opening the wallet.

### Overview

`StaqWalletPay` exposes static methods for:

- Wallet: Fetch the user's wallet with its balance and transactions.
- Payment Orders: Create payment orders and retrieve their details.
- UI: Present a card top-up screen.

Call `StaqWalletManager.initialize(withConfig:)` before using any of them. Each method performs network requests and must be called from an async context.

Each call restores the user's wallet session, or creates one from `StaqWalletUser.idToken`. If the backend requires the user to confirm the session with an OTP, the call throws `StaqWalletPayError.unauthorizedAccess`; open the wallet with `StaqWalletManager.makeStartView(user:onClose:)` so the user can confirm it. If the backend rejects the `idToken` as expired, the call throws `StaqWalletPayError.idTokenExpired`; issue a new `idToken`, create a new `StaqWalletUser` with it, and call again.

## Get Wallet

Registers the user for Tier 0 if needed, then returns the wallet for the user's current tier with its balance and transactions.

**Method Signature**

```swift
public static func getWallet(forUser user: StaqWalletUser) async throws -> StaqWalletDetails
```

**Parameters**

- `user`: The user whose wallet to fetch.

**Returns**

A `StaqWalletDetails` describing the wallet, its balance, and its transactions.

**Throws**

- `StaqWalletPayError.notInitialized`: If the SDK was not properly initialized.
- `StaqWalletPayError.unauthorizedAccess`: If the session expired or needs OTP confirmation.
- `StaqWalletPayError.idTokenExpired`: If the backend rejects the user's `idToken` as expired.
- `StaqWalletPayError.walletDoesNotExist`: If no wallet was found for the user.
- `StaqWalletPayError.server`: If the backend returns an error.
- `StaqWalletPayError.unknown`: If any unexpected failures occur.

**Example Usage**

```swift
do {
    let wallet = try await StaqWalletPay.getWallet(forUser: user)
    print("Available balance: \(wallet.balance.availableBalance) \(wallet.balance.currency)")
} catch StaqWalletPayError.idTokenExpired {
    // Get a new idToken from your backend, create a new StaqWalletUser with it, and call again.
} catch StaqWalletPayError.unauthorizedAccess {
    // Open the wallet with makeStartView so the user can confirm the session with an OTP.
} catch let error as StaqWalletPayError {
    print("Wallet Pay Error: \(error.errorDescription ?? "Unknown error")")
} catch {
    print("Other Error: \(error.localizedDescription)")
}
```

## Payment Order Management

### Create Payment Order

Creates a payment order paid from the user's wallet. Registers the user for Tier 0 if needed.

**Method Signature**

```swift
public static func createPaymentOrder(
    forUser user: StaqWalletUser,
    params: CreateStaqWalletPaymentOrderParams
) async throws -> StaqWalletPaymentOrder
```

**Parameters**

- `user`: The user for whom the payment order will be created.
- `params`: A `CreateStaqWalletPaymentOrderParams` instance with the details of the payment order.

**Returns**

A `StaqWalletPaymentOrder` describing the created order.

**Throws**

- `StaqWalletPayError.notInitialized`: If the SDK was not properly initialized.
- `StaqWalletPayError.unauthorizedAccess`: If the session expired or needs OTP confirmation.
- `StaqWalletPayError.idTokenExpired`: If the backend rejects the user's `idToken` as expired.
- `StaqWalletPayError.walletDoesNotExist`: If no wallet was found for the user.
- `StaqWalletPayError.server`: If the backend returns an error.
- `StaqWalletPayError.unknown`: If any unexpected failures occur.

---

### Get Payment Order Details

Fetches the details of an existing payment order by its unique identifier.

**Method Signature**

```swift
public static func getPaymentOrderDetails(
    forUser user: StaqWalletUser,
    orderId: String
) async throws -> StaqWalletPaymentOrder
```

**Parameters**

- `user`: The user associated with the payment order.
- `orderId`: The unique identifier of the payment order.

**Returns**

A `StaqWalletPaymentOrder` with the current state of the order.

**Throws**

- `StaqWalletPayError.notInitialized`: If the SDK was not properly initialized.
- `StaqWalletPayError.unauthorizedAccess`: If the session expired or needs OTP confirmation.
- `StaqWalletPayError.idTokenExpired`: If the backend rejects the user's `idToken` as expired.
- `StaqWalletPayError.server`: If the backend returns an error.
- `StaqWalletPayError.unknown`: If any unexpected failures occur.

## Top-Up UI

Returns a SwiftUI screen where the user tops up their wallet with a bank card. The top-up registers the user for Tier 0 if needed.

**Method Signature**

```swift
public static func makeTopUpView(
    user: StaqWalletUser,
    onClose: @escaping () -> Void
) -> some View
```

**Parameters**

- `user`: The user whose wallet to top up.
- `onClose`: Called when the user closes the screen. Dismiss the view here.

**Example Usage**

```swift
struct WalletScreen: View {
    let user: StaqWalletUser
    @State private var isTopUpPresented = false

    var body: some View {
        Button("Top Up") { isTopUpPresented = true }
            .navigationDestination(isPresented: $isTopUpPresented) {
                StaqWalletPay.makeTopUpView(user: user) {
                    isTopUpPresented = false
                }
            }
    }
}
```

## Models

### StaqWalletPayError

An enum representing errors that may occur during Wallet Pay operations. It conforms to `LocalizedError`, so `errorDescription` holds a readable message.

**Error Cases**

- `notInitialized`: The SDK has not been initialized.
- `unauthorizedAccess`: The session expired or is no longer valid; the user needs to confirm it with an OTP in the wallet.
- `idTokenExpired`: The `idToken` in `StaqWalletUser` is expired; issue a new one and call again.
- `walletDoesNotExist`: No wallet was found for the user.
- `server(_ message: String)`: The backend returned an error with the given message.
- `unknown`: An unknown or unexpected error occurred.

---

### StaqWalletDetails

The user's wallet for their current tier.

| Name         | Type                  | Description                                                                 |
|--------------|-----------------------|-----------------------------------------------------------------------------|
| id           | `String`              | Identifier of the wallet, account, or card.                                 |
| sourceType   | `WalletSourceType`    | `.wallet` (Tier 0 wallet), `.account` (Tier 1 account), or `.card` (Tier 2 card). |
| balance      | `WalletBalance`       | The wallet balance.                                                         |
| transactions | `[WalletTransaction]` | The latest wallet transactions.                                             |

**WalletBalance**

- `currency`: Currency code of the balance.
- `currentBalance`: Current balance (`Decimal`).
- `blockedAmount`: Amount on hold (`Decimal`).
- `availableBalance`: Balance available to spend (`Decimal`).

**WalletTransaction**

- `id`: Transaction identifier.
- `type`: Debit or credit indicator.
- `amount`: Transaction amount (`Decimal`).
- `currency`: Currency code of the transaction.
- `description`: Transaction description.
- `date`: Formatted transaction date.
- `time`: Formatted transaction time.

---

### CreateStaqWalletPaymentOrderParams

The parameters required to create a payment order.

**Parameters**

- `idempotencyKey`: A unique key to ensure idempotency of the request. Defaults to a new UUID string.
- `externalId`: Optional external identifier for the order.
- `totalAmount`: The total amount of the payment order.
- `feesAmount`: Optional portion of the total amount representing fees.
- `taxAmount`: Optional portion of the total amount representing taxes.
- `supplierId`: Unique identifier of the supplier fulfilling the order.
- `metaData`: Optional additional metadata for the order.
- `entityId`, `userId`, `serviceId`: Identifiers sent with the order as `EntityId`, `UserId`, and `ServiceId`.

The currency is always `SAR`.

**Initializer**

```swift
public init(
    idempotencyKey: String = UUID().uuidString,
    externalId: String? = nil,
    totalAmount: Decimal,
    feesAmount: Decimal? = nil,
    taxAmount: Decimal? = nil,
    supplierId: String,
    metaData: [String: String] = [:],
    entityId: String,
    userId: String,
    serviceId: String
)
```

---

### StaqWalletPaymentOrder

A payment order returned by `createPaymentOrder(forUser:params:)` and `getPaymentOrderDetails(forUser:orderId:)`.

| Name                     | Type              | Description                                                     |
|--------------------------|-------------------|-----------------------------------------------------------------|
| orderId                  | `String`          | Unique identifier of the order.                                 |
| orderType                | `String`          | Type of the order.                                              |
| createdAt                | `String?`         | Creation date of the order.                                     |
| status                   | `OrderStatus`     | Order status: `code`, `name`, `label`, and `labelAr`.           |
| errorDescription         | `String?`         | Description of the failure, if the order failed.                |
| currency                 | `String`          | Currency code of the order.                                     |
| totalAmount              | `Decimal`         | Total amount of the order.                                      |
| feesAmount               | `Decimal?`        | Fees part of the total amount.                                  |
| taxAmount                | `Decimal?`        | Taxes part of the total amount.                                 |
| localCurrencyAmount      | `Decimal`         | Amount in the local currency.                                   |
| exchangeRate             | `Decimal`         | Exchange rate applied to the order.                             |
| transactionId            | `String?`         | Identifier of the payment transaction.                          |
| externalUniqueIdentifier | `String?`         | The `externalId` passed when the order was created.             |
| orderMetaData            | `[String: Any]?`  | The metadata passed when the order was created.                 |

<br />

# Migrating from Earlier Versions

## From 5.0.x to 5.1.0

`StaqWalletPayError` has a new case, `idTokenExpired`, thrown when the backend rejects the user's `idToken` as expired. Your code compiles unchanged unless it switches over `StaqWalletPayError` without a `default`: add a case for `idTokenExpired` there. Nothing else in the public API changed.

## Removed APIs

| Removed                                                                 | Use instead                                                                                     |
|-------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------|
| `StaqWalletManager.start(forUser:withLanguage:fromNavigationController:)` | `StaqWalletManager.makeStartView(user:onClose:)`. Set the language in `StaqWalletConfig` or with `changeLanguage(_:)`. |
| `StaqWalletUser(userId:secret:userType:nationalID:email:)`              | `StaqWalletUser(userId:secret:userType:nationalId:idToken:)`.                                   |
| `StaqWalletPay.registerUser(withConfig:)`                               | Not needed: the wallet and `StaqWalletPay` register the user for Tier 0 automatically.         |
| `StaqWalletPay.getWalletBalance(forUser:)`                              | `StaqWalletPay.getWallet(forUser:)` and its `balance`.                                          |
| `StaqWalletPay.WalletPayError`                                          | `StaqWalletPayError`.                                                                           |
| `StaqWalletPay.PaymentOrderParams`                                      | `CreateStaqWalletPaymentOrderParams`.                                                           |
| `CreatePaymentOrderResponse`, `PaymentOrderDetails`                     | `StaqWalletPaymentOrder`.                                                                       |
| `WalletPayView`, `UIWalletPayView`, `WalletPayDetailsModalView`, `StaqWalletPay.presentWalletPayDetails(...)`, `WalletPayViewType`, `WalletPayViewState` | No replacement. Build the payment selection UI in your app.               |

<br />

---

If you have any questions or need assistance, reach out via email at [d.lunov@staq.io]. I’ll do my best to respond promptly!
