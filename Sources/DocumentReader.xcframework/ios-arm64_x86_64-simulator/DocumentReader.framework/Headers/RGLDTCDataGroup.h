//
//  RGLDTCDataGroup.h
//  DocumentReader
//
//  Created by Dmitry Evglevsky on 16.11.24.
//  Copyright © 2024 Regula. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RGLDataGroup;

NS_SWIFT_NAME(DTCDataGroup)
@interface RGLDTCDataGroup : NSObject

@property(nonatomic, assign) BOOL dG17;
@property(nonatomic, assign) BOOL dG18;
@property(nonatomic, assign) BOOL dG22;
@property(nonatomic, assign) BOOL dG23;
@property(nonatomic, assign) BOOL dG24;

- (instancetype _Nonnull)initWithJSON:(NSDictionary *_Nonnull)json;
- (NSDictionary *_Nonnull)dataGroupsDictionary;
+ (instancetype _Nonnull)initWithJSON:(NSDictionary * _Nonnull)json;

@end

