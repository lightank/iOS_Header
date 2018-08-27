//
//  UIDataDetectors.h
//  UIKit
//
//  Copyright (c) 2009-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
//自动检测电话、网址和邮箱
typedef NS_OPTIONS(NSUInteger, UIDataDetectorTypes) {
    //自动检测电话
    UIDataDetectorTypePhoneNumber                                        = 1 << 0, // Phone number detection
    //自动检测网址
    UIDataDetectorTypeLink                                               = 1 << 1, // URL detection
    //自动检测地址
    UIDataDetectorTypeAddress NS_ENUM_AVAILABLE_IOS(4_0)                 = 1 << 2, // Street address detection
    //自动检测日历事件
    UIDataDetectorTypeCalendarEvent NS_ENUM_AVAILABLE_IOS(4_0)           = 1 << 3, // Event detection
    //货物订单号
    UIDataDetectorTypeShipmentTrackingNumber NS_ENUM_AVAILABLE_IOS(10_0) = 1 << 4, // Shipment tracking number detection
    //机票
    UIDataDetectorTypeFlightNumber NS_ENUM_AVAILABLE_IOS(10_0)           = 1 << 5, // Flight number detection
    //用户信息
    UIDataDetectorTypeLookupSuggestion NS_ENUM_AVAILABLE_IOS(10_0)       = 1 << 6, // Information users may want to look up
    //无检测
    UIDataDetectorTypeNone          = 0,               // Disable detection
    //检测所有的
    UIDataDetectorTypeAll           = NSUIntegerMax    // Enable all types, including types that may be added later
} __TVOS_PROHIBITED;
