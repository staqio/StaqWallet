//
//  AnalyticsTrackerProtocol.swift
//  StaqWallet
//
//  Created by Dmytro Lunov on 24.09.2025.
//

import Foundation

public protocol AnalyticsTrackerProtocol {
    func identify(_ userId: String)
    func setUserProperties(_ properties: [AnalyticsTrackingProperty: Any])
    func screen(_ screen: AnalyticsTrackingScreen)
    func track(_ event: AnalyticsTrackingEvent, on screen: AnalyticsTrackingScreen)
}
