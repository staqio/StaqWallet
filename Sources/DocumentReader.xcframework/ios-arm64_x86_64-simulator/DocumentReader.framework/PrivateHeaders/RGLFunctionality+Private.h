//
//  RGLFunctionality+Private.h
//  DocumentReader
//
//  Created by Serge Rylko on 14.04.25.
//  Copyright © 2025 Regula. All rights reserved.
//

#import <DocumentReader/RGLFunctionality.h>

NS_ASSUME_NONNULL_BEGIN

@interface RGLFunctionality (Private)

- (instancetype)initWithJSON:(NSDictionary<NSString *, id> *)json;
- (NSDictionary<NSString *, id> *)toJSON;

@end

NS_ASSUME_NONNULL_END
