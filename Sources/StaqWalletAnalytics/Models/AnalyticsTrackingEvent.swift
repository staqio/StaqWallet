//
//  AnalyticsTrackingEvent.swift
//  StaqWallet
//
//  Created by Dmytro Lunov on 24.09.2025.
//

import Foundation

public enum AnalyticsTrackingEvent: String {
    case walletStart = "wallet_start"

    public var name: String { rawValue }

    public func properties(screen: AnalyticsTrackingScreen) -> [String: Any] {
        switch self {
        case .walletStart:
            return ["screen": screen.event.key]
        }
    }
}
