// swift-tools-version: 6.2
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "StaqWallet",
    platforms: [
        .iOS(.v16),
    ],
    products: [
        .library(
            name: "StaqWallet",
            targets: ["StaqWalletTarget"]
        )
    ],
    dependencies: [
        .package(url: "https://github.com/regulaforensics/DocumentReader-Swift-Package", exact: "9.1.5702"),
        .package(url: "https://github.com/regulaforensics/DocumentReaderBounds-Swift-Package", exact: "9.1.15608"),
        .package(url: "https://github.com/regulaforensics/FaceCoreBasic-Swift-Package", exact: "7.2.1622"),
        .package(url: "https://github.com/regulaforensics/FaceSDK-Swift-Package", exact: "7.2.3526")
        // .package(url: "https://github.com/staqio/TrustlessSDK", exact: "1.0.0-beta.6")
    ],
    targets: [
        .binaryTarget(
            name: "StaqWallet",
            path: "Sources/StaqWallet.xcframework"
        ),
        .binaryTarget(
            name: "TrustlessSDK",
            path: "Sources/TrustlessSDK.xcframework"
        ),
        .target(
            name: "StaqWalletTarget",
            dependencies: [
                .target(name: "StaqWallet"),
                .target(name: "TrustlessSDK"),
                .product(name: "DocumentReader", package: "documentreader-swift-package"),
                .product(name: "Bounds", package: "documentreaderbounds-swift-package"),
                .product(name: "FaceCoreBasic", package: "facecorebasic-swift-package"),
                .product(name: "FaceSDK", package: "facesdk-swift-package")
                // .product(name: "TrustlessSDK", package: "TrustlessSDK")
            ],
            path: "Sources/StaqWalletTarget",
            sources: ["Exports.swift"],
            linkerSettings: [
                .linkedFramework("PassKit")
            ]
        )
    ]
)