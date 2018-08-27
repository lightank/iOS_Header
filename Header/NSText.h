//
//  NSText.h
//  UIKit
//
//  Copyright (c) 2011-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#if __has_include(<CoreText/CTParagraphStyle.h>)
#import <CoreText/CTParagraphStyle.h>
#endif
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/* Values for NSTextAlignment */
//文本的在文本框的显示位置
typedef NS_ENUM(NSInteger, NSTextAlignment) {
    //左对齐
    NSTextAlignmentLeft      = 0,    // Visually left aligned
#if TARGET_OS_IPHONE
    //居中
    NSTextAlignmentCenter    = 1,    // Visually centered
    //右对齐
    NSTextAlignmentRight     = 2,    // Visually right aligned
#else /* !TARGET_OS_IPHONE */
    NSTextAlignmentRight     = 1,    // Visually right aligned
    NSTextAlignmentCenter    = 2,    // Visually centered
#endif
    //最后一行自然对齐
    NSTextAlignmentJustified = 3,    // Fully-justified. The last line in a paragraph is natural-aligned.
    //默认对齐脚本
    NSTextAlignmentNatural   = 4,    // Indicates the default alignment for script
} NS_ENUM_AVAILABLE_IOS(6_0);

#if __has_include(<CoreText/CTParagraphStyle.h>)
// 文本对其方式切换函数
// CTTextAlignment 和 NSTextAlignment 进行互换
UIKIT_EXTERN CTTextAlignment NSTextAlignmentToCTTextAlignment(NSTextAlignment nsTextAlignment) NS_AVAILABLE_IOS(6_0);
UIKIT_EXTERN NSTextAlignment NSTextAlignmentFromCTTextAlignment(CTTextAlignment ctTextAlignment) NS_AVAILABLE_IOS(6_0);
#endif

/* Values for NSWritingDirection */
typedef NS_ENUM(NSInteger, NSWritingDirection) {
    NSWritingDirectionNatural       = -1,    // Determines direction using the Unicode Bidi Algorithm rules P2 and P3
    //从左到右
    NSWritingDirectionLeftToRight   =  0,    // Left to right writing direction
    //从右到左
    NSWritingDirectionRightToLeft   =  1     // Right to left writing direction
} NS_ENUM_AVAILABLE_IOS(6_0);

NS_ASSUME_NONNULL_END
