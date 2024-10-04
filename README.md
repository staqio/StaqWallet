# StaqWallet

### Requirements

- Xcode 16
- Apple Swift version 6.0

### Installation

#### Using Swift Package Manager (SPM)

Add the package dependency to your `Package.swift` file and add the dependency to the `dependencies` array. Here's an example:

```swift
dependencies: [
    .package(url: "https://github.com/staqio/StaqWallet", from: "0.9.7")
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

To start the Wallet flow, import the `StaqWallet` framework and use the `AppFlowCoordinator` it provides. This flow allows users to initiate the wallet process after setting up some configuration. Here’s a step-by-step guide:

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
            googleMapsApiKey: "app-google-maps-api-key",
        )
        AppFlowCoordinator(config: config).start()
    }
}
```
