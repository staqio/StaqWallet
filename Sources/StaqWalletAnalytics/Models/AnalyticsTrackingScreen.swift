//
//  AnalyticsTrackingScreen.swift
//  StaqWallet
//
//  Created by Dmytro Lunov on 24.09.2025.
//

import Foundation

public enum AnalyticsTrackingScreen {
    
    public struct Event {
        public let key, name: String
        
        public var properties: [String: Any] {
            ["screen": name]
        }
    }
    
    // MARK: - Start
    case start
    // MARK: - Onboarding
    case verifyMobile
    case verifyCode
    case securitySetup
    case createPasscode
    case confirmPasscode
    case visaNumberForm
    case termsAndConditions
    case identityVerificationFailure
    // MARK: - KYC
    case passportScanInstructions
    case passportScan
    case selfieInstructions
    case selfieCapture
    case videoInstructions
    case videoCapture
    case passportPortraitVerification
    // MARK: - User
    case arrivalInfo
    case setCardPin
    case confirmCardPin // New
    case approvalPending
    case identityApprovalPending
    case cardApprovalPending
    case verificationFailure
    case verificationRejection
    case verificationBlocked
    case generateVerificationCode
    case showVerificationCode
    // MARK: - Card
    case cardHome
    case activateCard
    case withdrawInstructions
    case withdrawForm
    case withdrawConfirmation
    case topUpOptions
    case bankTransferDetails
    case cardSettings
    case contactSupport
    case transactionsList
    case transactionDetails
    // MARK: - Others
    case contactSupportRequest
    case appSettings
    case aboutApp
    // MARK: - Session
    case passcodeAuthentication
    case faceIdAuthentication
    // MARK: - Local Wallet
    case selectResidency
    case enterNationalId
    case nationalSingleSignOn
    case localTermsAndConditions
    case walletHome
    case localApprovalPending
    case localIdentityVerificationFailure
    case emailSetup
    case localTopUpOptions
    case localTopUpInstructions
    case localTopUpSadadOption
    case localTopUpAmount
    case localTopUpSource
    case localTopUpConfirmation
    case localTopUpSuccess
    case localTopUpFailure
    case localTopUpConfirmationWebView
    case localWithdrawAmount
    case localWithdrawRecipientAccount
    case localWithdrawConfirmation
    case localWithdrawSuccess
    case localWithdrawFailure
    // MARK: - Modals
    case approvalPendingModal
    // MARK: - Local Wallet
    case localWalletSelectCitizen
    case localWalletTerms
    case localWalletNafathAccountNumber
    
    public var event: Event {
        switch self {
        case .start:
            Event(key: "start", name: "Start")
        case .verifyMobile:
            Event(key: "verify_mobile", name: "Verify Mobile")
        case .verifyCode:
            Event(key: "verify_code", name: "Code Verification")
        case .securitySetup:
            Event(key: "security_setup", name: "Security Setup")
        case .createPasscode:
            Event(key: "create_passcode", name: "Create Passcode")
        case .confirmPasscode:
            Event(key: "confirm_passcode", name: "Confirm Passcode Creation")
        case .visaNumberForm:
            Event(key: "visa_number_form", name: "Visa Number")
        case .termsAndConditions:
            Event(key: "terms_and_conditions", name: "Terms and Conditions")
        case .identityVerificationFailure:
            Event(key: "identity_verification_failure", name: "Identity Verification Failure")
        case .passportScanInstructions:
            Event(key: "passport_scan_instructions", name: "Scan Passport Instructions")
        case .passportScan:
            Event(key: "passport_scan", name: "Scan Passport")
        case .selfieInstructions:
            Event(key: "selfie_instructions", name: "Pre-Selfie Instructions")
        case .selfieCapture:
            Event(key: "selfie_capture", name: "Selfie Capture")
        case .videoInstructions:
            Event(key: "video_instructions", name: "Pre-Video Upload")
        case .videoCapture:
            Event(key: "video_capture", name: "Video Upload")
        case .passportPortraitVerification:
            Event(key: "passport_portrait_verification", name: "Similarity Check")
        case .arrivalInfo:
            Event(key: "arrival_info", name: "Arrival Info")
        case .setCardPin:
            Event(key: "set_card_pin", name: "Set Card PIN Code")
        case .confirmCardPin:
            Event(key: "confirm_card_pin", name: "Confirm Card PIN Code")
        case .approvalPending:
            Event(key: "approval_pending", name: "Wait for 48 Hours")
        case .identityApprovalPending:
            Event(key: "identity_approval_pending", name: "Pending Identity Approval")
        case .cardApprovalPending:
            Event(key: "card_approval_pending", name: "Pending Card Approval")
        case .verificationFailure:
            Event(key: "verification_failure", name: "Verification Failure")
        case .verificationRejection:
            Event(key: "verification_rejection", name: "Verification Rejection")
        case .verificationBlocked:
            Event(key: "verification_blocked", name: "Verification Blocked")
        case .generateVerificationCode:
            Event(key: "generate_verification_code", name: "Generate Verification Code")
        case .showVerificationCode:
            Event(key: "show_verification_code", name: "Verification Code")
        case .cardHome:
            Event(key: "card_home", name: "Card Main Screen")
        case .activateCard:
            Event(key: "activate_card", name: "Activate Card")
        case .withdrawInstructions:
            Event(key: "withdraw_instructions", name: "Withdraw Instructions")
        case .withdrawForm:
            Event(key: "withdraw_form", name: "Withdraw Screen")
        case .withdrawConfirmation:
            Event(key: "withdraw_confirmation", name: "Withdraw Confirmation")
        case .topUpOptions:
            Event(key: "top_up_options", name: "Top Up Options")
        case .bankTransferDetails:
            Event(key: "bank_transfer_details", name: "Bank Transfer Info")
        case .cardSettings:
            Event(key: "card_settings", name: "Card Settings")
        case .contactSupport:
            Event(key: "contact_support", name: "Contact Support")
        case .transactionsList:
            Event(key: "transactions_list", name: "Transactions History")
        case .transactionDetails:
            Event(key: "transaction_details", name: "Transaction Details")
        case .contactSupportRequest:
            Event(key: "contact_support_request", name: "Contact Support Request")
        case .appSettings:
            Event(key: "app_settings", name: "App Settings")
        case .aboutApp:
            Event(key: "about_app", name: "About the App")
        case .passcodeAuthentication:
            Event(key: "passcode_authentication", name: "Passcode Local Authentication")
        case .faceIdAuthentication:
            Event(key: "face_id_authentication", name: "FaceID Local Authentication")
        case .selectResidency:
            Event(key: "select_residency", name: "Select Residency")
        case .enterNationalId:
            Event(key: "enter_national_id", name: "Enter National ID")
        case .nationalSingleSignOn:
            Event(key: "national_single_sign_on", name: "National Signle Sign On")
        case .localTermsAndConditions:
            Event(key: "local_terms_and_conditions", name: "Local Terms and Conditions")
        case .walletHome:
            Event(key: "wallet_home", name: "Wallet Main Screen")
        case .localApprovalPending:
            Event(key: "local_approval_pending", name: "Local Approval Pending")
        case .localIdentityVerificationFailure:
            Event(key: "local_identity_verification_failure", name: "Local Verification Failure")
        case .emailSetup:
            Event(key: "email_setup", name: "Email Set Up")
        case .localTopUpOptions:
            Event(key: "local_top_up_options", name: "Top Up Options")
        case .localTopUpInstructions:
            Event(key: "local_top_up_instructions", name: "Top Up Instructions")
        case .localTopUpSadadOption:
            Event(key: "local_top_up_sadad_option", name: "Top Up Sadad Option")
        case .localTopUpAmount:
            Event(key: "local_top_up_amount", name: "Top Up Amount")
        case .localTopUpSource:
            Event(key: "local_top_up_source", name: "Top Up Source")
        case .localTopUpConfirmation:
            Event(key: "local_top_up_confirmation", name: "Confirm Top Up")
        case .localTopUpSuccess:
            Event(key: "local_top_up_success", name: "Top Up Success")
        case .localTopUpFailure:
            Event(key: "local_top_up_failure", name: "Top Up Failure")
        case .localTopUpConfirmationWebView:
            Event(key: "local_top_up_confirmation_web_view", name: "Top Up Confirmation WebView")
        case .localWithdrawAmount:
            Event(key: "local_withdraw_amount", name: "Withdraw Amount")
        case .localWithdrawRecipientAccount:
            Event(key: "local_withdraw_recipient_account", name: "Withdraw Recipient Account")
        case .localWithdrawConfirmation:
            Event(key: "local_withdraw_confirmation", name: "Withdraw Confirmation")
        case .localWithdrawSuccess:
            Event(key: "local_withdraw_success", name: "Withdraw Success")
        case .localWithdrawFailure:
            Event(key: "local_withdraw_failure", name: "Withdraw Failure")
        case .approvalPendingModal:
            Event(key: "approval_pending_modal", name: "Wait for 48 Hours Modal")
        case .localWalletSelectCitizen:
            Event(key: "local_wallet", name: "Local Wallet SelectCitizen")
        case .localWalletTerms:
            Event(key: "local_wallet", name: "Local Wallet Terms")
        case .localWalletNafathAccountNumber:
            Event(key: "local_wallet", name: "Local Wallet Nafath Account Number")
        }
    }
}

