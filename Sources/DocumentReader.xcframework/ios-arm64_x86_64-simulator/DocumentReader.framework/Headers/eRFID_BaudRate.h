//
//  eRFID_BaudRate.h
//  DocumentReader
//
//  Created by Serge Rylko on 10.03.25.
//  Copyright © 2025 Regula. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, eRFID_BaudRate) {

  /**
   * 106 bits/s
   */
  eRFID_BaudRate_rfbr106            = 0x01,
  /**
   * 212 bits/s
   */
  eRFID_BaudRate_rfbr212            = 0x02,
  /**
   * 424 bits/s
   */
  eRFID_BaudRate_rfbr424            = 0x04,
  /**
   * 848 bits/s
   */
  eRFID_BaudRate_rfbr848            = 0x08,
  eRFID_BaudRate_rfbr1695           = 0x10,
  eRFID_BaudRate_rfbr3390           = 0x20,
  eRFID_BaudRate_rfbr6780           = 0x40,
} NS_SWIFT_NAME(eRFID_BaudRate);
