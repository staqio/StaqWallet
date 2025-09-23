//
//  RGLCustomization+Private.h
//  DocumentReader
//
//  Created by Serge Rylko on 16.04.25.
//  Copyright © 2025 Regula. All rights reserved.
//

#import <DocumentReader/RGLCustomization.h>

NS_ASSUME_NONNULL_BEGIN

@interface RGLCustomization (Private)

- (instancetype)initWithJSON:(NSDictionary<NSString *, id> *)json;
- (NSDictionary<NSString *, id> *)toJSON;

@end

NS_ASSUME_NONNULL_END
