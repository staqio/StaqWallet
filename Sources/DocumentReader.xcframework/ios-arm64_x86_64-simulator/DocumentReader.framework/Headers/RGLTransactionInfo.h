//
//  RGLTransactionInfo.h
//  DocumentReader
//
//  Created by Dmitry Evglevsky on 18.01.24.
//  Copyright © 2024 Regula. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RGLTransactionInfo : NSObject

@property(nonatomic, strong, readonly, nullable) NSString *transactionId;
@property(nonatomic, strong, readonly, nullable) NSString *tag;
/// The path to the logs folder of the session.
@property(nonatomic, strong, readonly, nullable) NSString *sessionLogFolder;

- (instancetype _Nonnull)initWithTag:(NSString *)tag
                       transactionId:(NSString *)transactionId
                    sessionLogFolder:(NSString *)sessionLogFolder;
- (instancetype _Nonnull)initWithJSON:(NSDictionary *)json;

@end

NS_ASSUME_NONNULL_END
