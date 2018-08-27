//
//  UIBarCommon.h
//  UIKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
//Constants to specify metrics to use for appearance.
//常数来指定用于外观的度量。
typedef NS_ENUM(NSInteger, UIBarMetrics) {
    //Specifies default metrics for the device.
    //指定设备的默认度量标准。
    //表示横屏竖屏都显示
    UIBarMetricsDefault,
    //Specifies metrics when using the phone idiom.
    //指定使用手机成语时的指标。
    //表示在只横屏下才显示，和UIBarMetricsLandscapePhone功效一样，不过iOS8已经弃用了
    UIBarMetricsCompact,
    //Specifies default metrics for the device for bars with the prompt property, such as UINavigationBar and UISearchBar.
    //指定具有prompt属性的bar的设备的默认度量标准，例如UINavigationBar和UISearchBar。
    //仅适用于具有提示属性的栏，如UINavigationBar和UISearchBar
    UIBarMetricsDefaultPrompt = 101, // Applicable only in bars with the prompt property, such as UINavigationBar and UISearchBar
    //Specifies metrics for bars with the prompt property when using the phone idiom, such as UINavigationBar and UISearchBar.
    //使用手机成语（如UINavigationBar和UISearchBar）指定使用提示属性的条形的指标。
    UIBarMetricsCompactPrompt,
    //Specifies metrics for landscape orientation using the phone idiom.
    //使用手机成语指定景观方向的指标。
    UIBarMetricsLandscapePhone NS_ENUM_DEPRECATED_IOS(5_0, 8_0, "Use UIBarMetricsCompact instead") = UIBarMetricsCompact,
    //Specifies metrics for landscape orientation using the phone idiom for bars with the prompt property, such as UINavigationBar and UISearchBar.
    //使用提示属性的条形码（如UINavigationBar和UISearchBar）为使用手机成语指定横向方向的指标。
    UIBarMetricsLandscapePhonePrompt NS_ENUM_DEPRECATED_IOS(7_0, 8_0, "Use UIBarMetricsCompactPrompt") = UIBarMetricsCompactPrompt,
};

//Constants to identify the position of a bar.
//常数来标识一个bar的位置。
typedef NS_ENUM(NSInteger, UIBarPosition) {
    //Specifies that the position is unspecified.
    //指定该位置未指定。
    UIBarPositionAny = 0,
    //The system uses this as a hint to draw directional decoration accordingly. For example, any shadow would be drawn above the bar.
    //系统使用它作为提示相应地绘制方向装饰。 例如，任何阴影将被绘制在bar上方。
    //bar位于其本地背景的底部，相应地定向装饰（例如，bar上方的阴影）。
    UIBarPositionBottom = 1, // The bar is at the bottom of its local context, and directional decoration draws accordingly (e.g., shadow above the bar).
    //The system uses this as a hint to draw directional decoration accordingly. For example, any shadow would be drawn below the bar.
    //系统使用它作为提示相应地绘制方向装饰。 例如，任何阴影将被绘制在bar下面。
    //bar位于当地上下文的顶端，相应地定向装饰（例如，bar下方的阴影）
    UIBarPositionTop = 2, // The bar is at the top of its local context, and directional decoration draws accordingly (e.g., shadow below the bar)
    //Bars with this position draw their background extended upwards, allowing their background content to show through the status bar.
    //具有此位置的条带将其背景向上延伸，允许其背景内容通过状态栏显示。
    //该栏位于屏幕顶部（以及其本地上下文），并且其背景向上延伸，目前状态栏已足够。
    UIBarPositionTopAttached = 3, // The bar is at the top of the screen (as well as its local context), and its background extends upward—currently only enough for the status bar.
} NS_ENUM_AVAILABLE_IOS(7_0);

#define UIToolbarPosition UIBarPosition
#define UIToolbarPositionAny UIBarPositionAny
#define UIToolbarPositionBottom UIBarPositionBottom
#define UIToolbarPositionTop UIBarPositionTop


@protocol UIBarPositioning <NSObject> // UINavigationBar, UIToolbar, and UISearchBar conform to this
@property(nonatomic,readonly) UIBarPosition barPosition;
@end

@protocol UIBarPositioningDelegate <NSObject> // UINavigationBarDelegate, UIToolbarDelegate, and UISearchBarDelegate all extend from this
@optional
/* Implement this method on your manual bar delegate when not managed by a UIKit controller.
 UINavigationBar and UISearchBar default to UIBarPositionTop, UIToolbar defaults to UIBarPositionBottom.
 This message will be sent when the bar moves to a window.
 */
/*
 在不由UIKit控制器管理的情况下，在手动条代码上实现此方法。
   UINavigationBar和UISearchBar默认为UIBarPositionTop，UIToolbar默认为UIBarPositionBottom。
   当条移动到窗口时，将发送此消息。
 */
- (UIBarPosition)positionForBar:(id <UIBarPositioning>)bar;
@end

NS_ASSUME_NONNULL_END
