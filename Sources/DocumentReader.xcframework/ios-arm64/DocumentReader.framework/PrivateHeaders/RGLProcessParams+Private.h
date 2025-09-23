//
//  RGLProcessParams+Private.h
//  DocumentReader
//
//  Created by Serge Rylko on 5.03.25.
//  Copyright © 2025 Regula. All rights reserved.
//

#import <DocumentReader/RGLProcessParams.h>

NS_ASSUME_NONNULL_BEGIN

@interface RGLProcessParams (Private)

- (instancetype)init:(NSDictionary<NSString *, id> *)json;
- (NSDictionary<NSString *, id> *)toJSON;

@end

NS_ASSUME_NONNULL_END
