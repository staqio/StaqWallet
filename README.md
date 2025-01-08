# Staq Wallet

### Requirements

- Xcode 16
- Apple Swift version 6.0

### Installation

#### Using Swift Package Manager (SPM)

Add the package dependency to your `Package.swift` file and add the dependency to the `dependencies` array. Here's an example:

```swift
dependencies: [
    .package(url: "https://github.com/staqio/StaqWallet", from: "1.2.0")
]
```

```swift
targets: [
    .target(name: "TargetName", dependencies:[
        "StaqWallet"
    ])
]
```

Run the command `swift package update` to download the package and its dependencies.

### Usage

To start the Wallet flow, import the `StaqWallet` framework and use the `AppFlowCoordinator` it provides. This flow allows users to initiate the wallet process after setting up some configuration.

```swift
let coordinator = AppFlowCoordinator(
    navController,
    config: StaqWalletConfig(...)
)
coordinator.start()
```

#### Navigation Controller Setup

You can provide a UINavigationController to the SDK for navigation purposes. This navigation controller will be used internally by the SDK for pushing and presenting views.

If no UINavigationController is provided (or if you pass nil), the SDK will automatically attempt to use the first navigation controller found in the UIWindow of your application.

#### Face ID Setup

Make sure to enable Face ID in your app by adding the following key to your Info.plist file:

```xml
<key>NSFaceIDUsageDescription</key>
<string>We use Face ID to authenticate your identity quickly and securely.</string>
```

If this key is not added, your application will crash when attempting to use Face ID.

#### Document Scanning & KYC Verification

For features like document scanning and KYC verification, you need to add camera and microphone permissions to your Info.plist:

```xml
<key>NSCameraUsageDescription</key>
<string>We need access to the camera to capture your documents for verification purposes.</string>
<key>NSMicrophoneUsageDescription</key>
<string>We need access to the microphone to assist in the verification process.</string>
```

Again, if these permissions are missing, the app will crash when the camera or microphone is required.

### Example Code to Start the Wallet Flow

Below is a minimal implementation in your SceneDelegate to initialize the Wallet flow:

```swift
import StaqWallet
import UIKit

class SceneDelegate: UIResponder, UIWindowSceneDelegate {
    var window: UIWindow?

    func scene(_ scene: UIScene, willConnectTo session: UISceneSession, options connectionOptions: UIScene.ConnectionOptions) {
        guard let windowScene = scene as? UIWindowScene else { return }
        let window = UIWindow(windowScene: windowScene)
        self.window = window

        let rootVC = UIViewController()
        let navController = UINavigationController(rootViewController: rootVC)  // you existing navigation controller
        window.rootViewController = navController
        window.makeKeyAndVisible()

        let config = StaqWalletConfig(
            userId: "user-id",
            secret: "user-secret",
            email: "user-email",
            mobileNumber: "user-mobile-phone-number",
            language: .en, // or .ar
        )
        AppFlowCoordinator(navController, config: config).start()
    }
}
```

# Staq Wallet Pay

### WalletPayParams

The `WalletPayParams` struct provides the following parameters:

- `totalAmount`: The total transaction amount.
- `subtotalAmount`: The subtotal amount before fees.
- `currencyCode`: The currency code (default is "SAR").
- `fees`: The fees associated with the transaction.
- `productId`: The unique identifier for the product.
- `sku`: The stock-keeping unit for the product.
- `narative`: An optional narrative or description for the transaction.

Initialization example:

```swift
let params = WalletPayParams(
    totalAmount: 150.0,
    subtotalAmount: 140.0,
    currencyCode: "SAR",
    fees: 10.0,
    productId: "12345",
    sku: "ABC-678",
    narative: "Payment for Order #12345"
)
```

---

### SwiftUI

#### WalletPayView

Here is an example of how to use `WalletPayView` in a SwiftUI app:

```swift
import SwiftUI

struct ContentView: View {
    @State var isSelected = false

    var body: some View {
        WalletPayView(
            isSelected: $isSelected,
            variant: .inline,
            balance: 1000.0,
            params: WalletPayParams(/* your parameters */)
        )
        .onTapGesture {
            isSelected.toggle()
        }
    }
}
```

#### Parameters

- `isSelected`: A `Binding<Bool>` property to toggle selection state.
- `variant`: A `WalletPayView.Variant` enum value to specify the view style (`inline` or `breakdown`).
- `balance`: A `Double` representing the wallet balance.
- `params`: A `WalletPayParams` object to provide additional configuration.

---

#### WalletPayDetailsView

The `WalletPayDetailsView` is a SwiftUI component designed for displaying detailed wallet payment transactions.

Here is an example of how to use `WalletPayDetailsView`:

```swift
struct WalletPayDetailsExampleView: View {
    @State private var isDetailsVisible = false

    var body: some View {
        VStack { ... }
            .overlay {
                WalletPayDetailsModalView(
                    isPresented: $isDetailsVisible,
                    balance: 1000.0
                    params: WalletPayParams(...)
                )
            }
    }
}
```

#### Parameters

- `isPresented`: A `Binding<Bool>` determines whether the modal is presented.
- `balance`: A `Double` representing the wallet balance.
- `params`: A `WalletPayParams` object containing transaction details.

### WalletPayPresenter

A utility for presenting the WalletPayDetailsModalView in a UIKit-based application.

```swift
WalletPayPresenter.presentPaymentDetails(
    from: UIViewController(...),
    balance: 1000.0,
    params: WalletPayParams(...),
    didDismiss: {},
    didTapConfirm: { dismiss in
        dismiss()
    }
)
```

---

### UIKit

For UIKit integration, use the `UIWalletPayView` class, which wraps the SwiftUI view in a `UIView`.

Here is how to integrate `UIWalletPayView` into a UIKit application:

```swift
import UIKit
import SwiftUI

class ViewController: UIViewController {
    var walletPayView: UIWalletPayView!

    override func viewDidLoad() {
        super.viewDidLoad()

        walletPayView = UIWalletPayView(
            frame: CGRect(x: 0, y: 0, width: 300, height: 100),
            isSelected: false,
            variant: .inline,
            balance: 1000.0,
            params: WalletPayParams(/* your parameters */)
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
        walletPayView.setSelected(!walletPayView.isSelected)
    }
}
```

#### Initialization

`UIWalletPayView` can be initialized with:

- `frame`: The frame for the view.
- `isSelected`: A `Bool` to set the initial selection state.
- `variant`: A `WalletPayView.Variant` enum value to specify the view style (`inline` or `breakdown`).
- `balance`: A `Double` representing the wallet balance.
- `params`: A `WalletPayParams` object to provide additional configuration.

#### Methods

- `setSelected(_ isSelected: Bool)`: Updates the selection state programmatically.

---

### Additional Information

#### Animations

The selection state is animated using a spring animation: `.animation(.spring, value: isSelected)`
