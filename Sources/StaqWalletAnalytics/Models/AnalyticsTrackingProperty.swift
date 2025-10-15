//
//  AnalyticsTrackingProperty.swift
//  StaqWallet
//
//  Created by Dmytro Lunov on 06.08.2025.
//

import Foundation

public enum AnalyticsTrackingProperty: String, CaseIterable {
    case internalId = "internal_id"
    case kycId = "kyc_id"
    case userType = "user_type"
    case language = "language"
    case walletVersion = "wallet_version"
    case isCardActivated = "Card_Activation_Status"
}
