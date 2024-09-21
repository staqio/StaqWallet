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
        .package(url: "https://github.com/innovatrics/dot-ios-sdk-spm", exact: "8.3.2"),
        .package(url: "https://github.com/googlemaps/ios-maps-sdk", exact: "9.0.0"),
        .package(url: "https://github.com/googlemaps/ios-places-sdk", exact: "9.0.0"),
        .package(url: "https://github.com/staqio/TrustlessSDK", exact: "0.7.1")
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
                .product(name: "DotFaceDetectionBalanced", package: "dot-ios-sdk-spm"),
                .product(name: "DotFaceDetectionFast", package: "dot-ios-sdk-spm"),
                .product(name: "DotFaceExpressionNeutral", package: "dot-ios-sdk-spm"),
                .product(name: "GoogleMaps", package: "ios-maps-sdk"),
                .product(name: "GooglePlaces", package: "ios-places-sdk"),
                .product(name: "TrustlessSDK", package: "TrustlessSDK"),
                .target(name: "StaqWallet")
            ],
            path: "Sources/StaqWalletTarget",
            sources: ["StaqWalletEmpty.m"],
            publicHeadersPath: "Sources"
        )
    ]
)