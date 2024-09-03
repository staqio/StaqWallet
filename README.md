# StaqWallet

### Installation

### Using Swift Package Manager (SPM)

Add the package dependency to your `Package.swift` file and add the dependency to the `dependencies` array. Here's an example:

```swift
dependencies: [
    .package(url: "https://github.com/staqio/StaqWallet", from: "0.9.0")
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

> ! Note: You need to add the TrustlessSDK package as well because StaqWallet depends on it.

### Usage

To initiate the Wallet flow, import StaqWallet and utilize the `AppFlowCoordinator` it provides. To start the flow, firstly you need to initialize user and trigger Wallet flow using `AppFlowCoordinator`.

To enable Face ID, open the Info.plist and add the parameter `Privacy - Face ID Usage Description` (NSFaceIDUsageDescription) with your description value. If this permission is not added your application will crash.

To enable document scanning and KYC verification, open the Info.plist file and add the `Privacy - Camera Usage Description` (`NSCameraUsageDescription`) and `Privacy - Microphone Usage Description` (`NSMicrophoneUsageDescription`) keys with appropriate description values. If this permissions are not added your application will crash.

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
            googleMapsApiKey: "app-google-maps-api-key",
        )
        AppFlowCoordinator(config: config).start()
    }
}
```
