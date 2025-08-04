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
        .package(url: "https://github.com/innovatrics/dot-ios-sdk-spm", exact: "8.4.0"),
        .package(url: "https://github.com/staqio/TrustlessSDK", exact: "0.13.0"),
        .package(url: "https://github.com/PostHog/posthog-ios", exact: "3.29.0")
    ],
    targets: [
        .binaryTarget(
            name: "StaqWallet",
            path: "Sources/StaqWallet.xcframework"
        ),
        .target(
            name: "StaqWalletTarget",
            dependencies: [
                .product(name: "DotDocument", package: "dot-ios-sdk-spm"),
                .product(name: "DotFaceBackgroundUniformity", package: "dot-ios-sdk-spm"),
                .product(name: "DotFaceDetectionFast", package: "dot-ios-sdk-spm"),
                .product(name: "DotFaceExpressionNeutral", package: "dot-ios-sdk-spm"),
                .product(name: "TrustlessSDK", package: "TrustlessSDK"),
                .product(name: "PostHog", package: "posthog-ios"),
                .target(name: "StaqWallet")
            ],
            path: "Sources/StaqWalletTarget",
            sources: ["StaqWalletEmpty.m"],
            publicHeadersPath: "Sources",
            linkerSettings: [
                .linkedFramework("PassKit"),
                .linkedFramework("StaqWallet")
            ]
        )
    ]
)