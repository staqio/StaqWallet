# Staq Wallet

### Requirements

- Xcode 16
- Apple Swift version 6.0

### Installation

#### Using Swift Package Manager (SPM)

To install **StaqWallet** using Swift Package Manager, add the package dependency to your **Package.swift** file and include it in the dependencies array:

```swift
dependencies: [
    .package(url: "https://github.com/staqio/StaqWallet", exact: "2.0.0")
]
```

Then, add it to your target dependencies:

```swift
targets: [
    .target(name: "TargetName", dependencies:[
        "StaqWallet"
    ])
]
```

Run the following command to download the package and its dependencies:

```sh
swift package update
```

### Usage

To start the wallet flow, import the **StaqWallet** framework and use the `StaqWalletManager` class to initiate the process.

#### StaqWalletConfig

The `StaqWalletConfig` struct holds configuration parameters for initializing and authenticating the **StaqWallet** SDK.

**Parameters**

- `userId`: A unique identifier for the user.
- `secret`: A secret key used for authentication.
- `email`: (Optional) The user’s email address.
- `language`: The preferred language for the wallet interface (defaults to `.en`).
- `walletEnv`: The operating environment of the wallet (default: `.production`).

**Example Usage**

```swift
import StaqWallet

StaqWalletManager.start(
    withConfig: StaqWalletConfig(...),
    fromNavigationController: navigationController
)
```

#### Navigation Controller Setup

A `UINavigationController` must be provided to the SDK for navigation purposes. The navigation controller is used internally for presenting views. Ensure you pass a valid instance when starting the wallet flow.

#### Face ID Setup

Enable Face ID in your app by adding the following key to your **Info.plist** file:

```xml
<key>NSFaceIDUsageDescription</key>
<string>We use Face ID to authenticate your identity quickly and securely.</string>
```

Without this key, the application will crash when attempting to use Face ID.

#### Document Scanning & KYC Verification

To enable document scanning and KYC verification, add camera and microphone permissions to your **Info.plist**:

```xml
<key>NSCameraUsageDescription</key>
<string>We need access to the camera to capture your documents for verification purposes.</string>
<key>NSMicrophoneUsageDescription</key>
<string>We need access to the microphone to assist in the verification process.</string>
```

If these permissions are missing, the app will crash when trying to access the camera or microphone.

#### Domestic User Authentication Redirection

To support user authentication via **Nafath** services, add the following query scheme to your **Info.plist**:

```xml
<key>LSApplicationQueriesSchemes</key>
<array>
    <string>nafath</string>
</array>
```

This allows your app to detect the **Nafath** app and redirect users for registration.

#### Handling Navigation for Ordered Packages

The domestic wallet does not include built-in navigation for displaying ordered packages. You must manually handle navigation by providing a callback to `setPackagesNavigationCallback`:

```swift
StaqWalletManager.setPackagesNavigationCallback {
    // Implement your custom navigation logic here
}
```

### Example Code to Start the Wallet Flow

Below is an example implementation within SceneDelegate:

```swift
import StaqWallet
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
        let navigationController = UINavigationController(
            rootViewController: rootViewController
        )

        window.rootViewController = navigationController
        window.makeKeyAndVisible()

        let config = StaqWalletConfig(
            userId: "user-id",
            secret: "user-secret",
            email: "user-email",
            language: .en,
        )

        StaqWalletManager.setPackagesNavigationCallback {
            // Implement your custom navigation logic here
        }

        StaqWalletManager.start(
            withConfig: config,
            fromNavigationController: navigationController
        )
    }
}
```

<br />
<br />

# Staq Wallet Pay

The `StaqWalletPay` class provides Wallet Pay functionality, including balance management, payment order creation, and UI components.

### Overview

StaqWalletPay is a singleton class designed to streamline Wallet Pay operations. It supports:

- UI Management: Present modals for Wallet Pay details and actions.
- Wallet Management: Fetch the wallet balance with robust error handling.
- Payment Order Management: Create and retrieve payment order details using asynchronous methods.

## Retrieve Wallet Balance

Fetch the current wallet balance asynchronously.

**Method Signature**

```swift
public static func getWalletBalance() async throws -> Double
```

**Returns**

The available balance of the wallet as a `Double`.

**Throws**

- `WalletPayError.walletNotAvailable`: Wallet account is unavailable.
- `WalletPayError.notLoggedIn`: User is not logged in or session is invalid.
- `WalletPayError.server`: Server error with code and message.
- `WalletPayError.unexpected`: An unexpected error occurred.

## Models

### WalletPayError

An enum representing errors that may occur during payment operations in the Wallet Pay system.

**Error Cases**

- `notLoggedIn`: Indicates that the user is not logged in or their session is invalid.
- `walletNotAvailable`: Indicates that the wallet is not available for use.
- `server(code: String, message: String)`: Represents server-side errors with an error code and a descriptive message.
- `unexpected`: Indicates that an unexpected error occurred.

**Example Usage**

```swift
do {
    let balance = try await StaqWalletPay.getWalletBalance()
} catch let error as StaqWalletPay.WalletPayError {
    print("Wallet Pay Error: \(error.errorDescription ?? "Unknown error")")
} catch {
    print("Other Error: \(error.localizedDescription)")
}
```

---

### PaymentOrderParams

A struct representing the parameters required to create a payment order within the Wallet Pay system.

**Parameters**

- `idempotencyKey`: A unique key to ensure idempotency of the request.
- `externalId`: Optional external identifier for the order.
- `totalAmount`: The total amount of the payment order.
- `feesAmount`: Optional portion of the total amount representing fees.
- `taxAmount`: Optional portion of the total amount representing taxes.
- `supplierId`: Unique identifier of the supplier fulfilling the order.
- `metaData`: Optional additional metadata for the order.

**Initializer**

```swift
public init(
    idempotencyKey: String = UUID().uuidString,
    externalId: String? = nil,
    totalAmount: Double,
    feesAmount: Double?,
    taxAmount: Double?,
    supplierId: String,
    metaData: [String: String] = [:]
)
```

## Payment Order UI

The Wallet Pay UI is a combination of SwiftUI and UIKit components that handle payment-related workflows. These components include views to display wallet details and modals to handle user interactions for payments.

### WalletPayView

**Overview**

`WalletPayView` is a SwiftUI view that dynamically renders two types of layouts:

- Inline View (`inline`): A compact representation of Wallet Pay details.
- Breakdown View (`breakdown`): A detailed view showing payment order parameters.

**Parameters**

- `variant`: Specifies the layout type (`inline` or `breakdown`).
- `state`: The state object that manages the Wallet Pay view's behavior and balance (`WalletPayViewState`).
- `params`: The parameters for the payment order (`StaqWalletPay.PaymentOrderParams`).

**Example Usage**

```swift
struct ContentView: View {
    @StateObject var state = WalletPayViewState(
        isSelected: false,
        balance: 100.0
    )

    var body: some View {
        WalletPayView(
            variant: .breakdown,
            state: state,
            params: StaqWalletPay.PaymentOrderParams(...)
        )
        .onTapGesture {
            state.isSelected.toggle()
        }
    }
}
```

---

### UIWalletPayView

**Overview**

`UIWalletPayView` is a UIKit wrapper for embedding the `WalletPayView` into UIKit-based projects. It uses `UIHostingController` to integrate SwiftUI views seamlessly.

**Properties**

- `frame`: The frame rectangle for the view, measured in points.
- `variant`: The layout type of the Wallet Pay view (`inline` or `breakdown`).
- `state`: The state object that manages the Wallet Pay view's behavior and balance (`WalletPayViewState`).
- `params`: The parameters for the payment order (`StaqWalletPay.PaymentOrderParams`).

**Example Usage**

```swift
class ViewController: UIViewController {
    var walletPayView: UIWalletPayView!

    override func viewDidLoad() {
        super.viewDidLoad()

        walletPayView = UIWalletPayView(
            frame: CGRect(x: 0, y: 0, width: 300, height: 150),
            variant: .inline,
            state: WalletPayViewState(isSelected: false, balance: 100.0),
            params: StaqWalletPay.PaymentOrderParams(...)
        )

        let tapGesture = UITapGestureRecognizer(
            target: self,
            action: #selector(handleTap)
        )
        walletPayView.addGestureRecognizer(tapGesture)

        view.addSubview(walletPayView)
        walletPayView.center = view.center
    }

    @objc private func handleTap() {
        walletPayView.isSelected.toggle()
    }
}
```

---

### WalletPayDetailsModalView

**Overview**

`WalletPayDetailsModalView` is a SwiftUI modal for displaying detailed wallet payment information, such as the balance and payment parameters, with options for user interaction.

**Parameters**

- `isPresented`: A binding that determines whether the modal is presented.
- `balance`: The current wallet balance to be displayed.
- `params`: The parameters for the payment order (`StaqWalletPay.PaymentOrderParams`).
- `didDismiss`: An optional closure that executes when the modal is dismissed.
- `didTapConfirm`: An optional closure that executes when the confirm button is tapped. The closure receives a `dismiss` function to allow the modal to close programmatically.

**Example Usage**

```swift
struct WalletPayDetailsExampleView: View {
    @State private var isDetailsPresented = false

    var body: some View {
        VStack { ... }
            .overlay {
                WalletPayDetailsModalView(
                    isPresented: $isDetailsPresented,
                    balance: 150.0,
                    params: StaqWalletPay.PaymentOrderParams(...),
                    didDismiss: {
                        print("Modal dismissed")
                    },
                    didTapConfirm: { dismiss in
                        print("Confirm tapped")
                        dismiss()
                    }
                )
            }
    }
}
```

---

### Wallet Pay Details

**Overview**

Presents the Wallet Pay details modal, enabling users to review payment details, check wallet balance, and confirm actions.

**Method Signature**

```swift
public static func presentWalletPayDetails(
    from parent: UIViewController,
    balance: Double,
    params: StaqWalletPay.PaymentOrderParams,
    didDismiss: (() -> Void)? = nil,
    didTapConfirm: ((_ dismiss: () -> Void) -> Void)? = nil
)
```

**Parameters**

- `parent`: The parent View Controller from which the modal will be presented.
- `balance`: The current balance of the wallet.
- `params`: The parameters required for the Wallet payment operation (`StaqWalletPay.PaymentOrderParams`).
- `didDismiss`: An optional closure that is called when the modal is dismissed.
- `didTapConfirm`: An optional closure called when the confirm button is tapped. The closure provides a `dismiss` function that can be called to dismiss the modal.

**Example Usage**

```swift
StaqWalletPay.presentWalletPayDetails(
    from: self,
    balance: 150.0,
    params: params,
    didDismiss: {
        print("Modal dismissed")
    },
    didTapConfirm: { dismiss in
        print("Payment confirmed")
        dismiss()
    }
)
```

---

### Supporting Components

#### WalletPayViewType

`WalletPayViewType` is an enum that specifies the layout type for `WalletPayView`.

**Cases**

- `.inline`: A compact representation of Wallet Pay.
- `.breakdown`: A detailed view including payment order parameters.

---

#### WalletPayViewState

`WalletPayViewState` is an observable object that tracks the state of the Wallet Pay view. It is designed to work seamlessly with SwiftUI, allowing dynamic updates when state changes.

**Properties**

- `isSelected`: A boolean indicating if the view is selected.
- `balance`: The current wallet balance.

## Payment Order Management

### Overview

The `StaqWalletPay` class provides functionality to manage payment orders, including creating new payment orders and retrieving details of existing ones.

### Create Payment Order

Creates a new payment order asynchronously using the specified parameters.

**Method Signature**

```swift
public static func createPaymentOrder(
    params: StaqWalletPay.PaymentOrderParams
) async throws -> CreatePaymentOrderResponse
```

**Parameters**

- `params`: An instance of `PaymentOrderParams` containing the required details for the payment order.

**Throws**

- `WalletPayError`

**Returns**

- `CreatePaymentOrderResponse`: A response containing the details of the created payment order.

---

### Get Payment Order Details

Fetches the details of an existing payment order by its unique identifier.

**Method Signature**

```swift
public static func getPaymentOrderDetails(
    orderId: String
) async throws -> PaymentOrderDetails
```

**Parameters**

- `orderId`: A String representing the unique identifier of the payment order.

**Throws**

- `WalletPayError`

**Returns**

- `PaymentOrderDetails`: An object containing detailed information about the payment order.

<br />

---

If you have any questions or need assistance, reach out via email at [d.lunov@staq.io]. I’ll do my best to respond promptly!
