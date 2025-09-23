// swift-tools-version: 5.10
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "StaqWallet",
    platforms: [
        .iOS(.v15),
    ],
    products: [
        .library(
            name: "StaqWallet",
            targets: ["StaqWalletTarget"]
        ),
    ],
    dependencies: [
        .package(url: "https://github.com/regulaforensics/DocumentReaderBounds-Swift-Package", exact: "8.2.13454"),
        .package(url: "https://github.com/regulaforensics/FaceCoreBasic-Swift-Package", exact: "7.1.1501"),
        .package(url: "https://github.com/regulaforensics/FaceSDK-Swift-Package", exact: "7.1.2940"),
        .package(url: "https://github.com/PostHog/posthog-ios", .upToNextMajor(from: "3.29.0")),
        .package(url: "https://github.com/staqio/TrustlessSDK", exact: "0.13.1")
    ],
    targets: [
        .binaryTarget(
            name: "StaqWallet",
            path: "Sources/StaqWallet.xcframework"
        ),
        .binaryTarget(
            name: "DocumentReader",
            path: "Sources/DocumentReader.xcframework"
        ),
        .target(
            name: "StaqWalletTarget",
            dependencies: [
                .product(name: "Bounds", package: "documentreaderbounds-swift-package"),
                .target(name: "DocumentReader"),
                .product(name: "FaceCoreBasic", package: "facecorebasic-swift-package"),
                .product(name: "FaceSDK", package: "facesdk-swift-package"),
                .product(name: "PostHog", package: "posthog-ios"),
                .product(name: "TrustlessSDK", package: "TrustlessSDK"),
                .target(name: "StaqWallet")
            ],
            path: "Sources/StaqWalletTarget",
            sources: ["StaqWalletEmpty.m"],
            publicHeadersPath: "Sources",
            linkerSettings: [
                .linkedFramework("PassKit")
            ]
        )
    ]
)