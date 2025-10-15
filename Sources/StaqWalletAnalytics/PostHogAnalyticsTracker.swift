//
//  PostHogAnalyticsTracker.swift
//  StaqWallet
//
//  Created by Dmytro Lunov on 06.08.2025.
//

internal import PostHog

public final class PostHogAnalyticsTracker: AnalyticsTrackerProtocol {
    
    public init(apiKey: String, host: String) {
        let config = PostHogConfig(apiKey: apiKey, host: host)
        config.captureScreenViews = false
        PostHogSDK.shared.setup(config)
        
        #if DEBUG
        PostHogSDK.shared.debug(true)
        #endif
    }
    
    public func identify(_ userId: String) {
        PostHogSDK.shared.identify(userId)
    }
    
    public func setUserProperties(_ properties: [AnalyticsTrackingProperty: Any]) {
        let userId = PostHogSDK.shared.getDistinctId()
        if userId.isEmpty { return }
        let userProperties: [String: Any] = Dictionary(
            uniqueKeysWithValues: properties.map { ($0.key.rawValue, $0.value) }
        )
        PostHogSDK.shared.identify(userId, userProperties: userProperties)
    }
    
    public func screen(_ screen: AnalyticsTrackingScreen) {
        let event = screen.event
        PostHogSDK.shared.screen(
            event.key,
            properties: event.properties
        )
    }
    
    public func track(_ event: AnalyticsTrackingEvent, on screen: AnalyticsTrackingScreen) {
        PostHogSDK.shared.capture(
            event.name,
            properties: event.properties(screen: screen)
        )
    }
}
