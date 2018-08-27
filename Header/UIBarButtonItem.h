//
//  UIBarButtonItem.h
//  UIKit
//
//  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIBarItem.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIAppearance.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIBarCommon.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIBarButtonItemStyle) {
    //默认按钮风格；按下时会闪动
    UIBarButtonItemStylePlain,
    //与UIBarButtonItemStylePlain相同，但显示的按钮有边框
    UIBarButtonItemStyleBordered NS_ENUM_DEPRECATED_IOS(2_0, 8_0, "Use UIBarButtonItemStylePlain when minimum deployment target is iOS7 or later"),
    //显示一个蓝色按钮，提醒用户编辑完毕时应该点触（tap）该按钮
    UIBarButtonItemStyleDone,
};

typedef NS_ENUM(NSInteger, UIBarButtonSystemItem) {
    //"Done"
    UIBarButtonSystemItemDone,
    //"Cancel"
    UIBarButtonSystemItemCancel,
    //"Edit"
    UIBarButtonSystemItemEdit,
    //"Save"
    UIBarButtonSystemItemSave,
    //"＋"
    UIBarButtonSystemItemAdd,
    //无样式,弹簧,控件平均分布
    UIBarButtonSystemItemFlexibleSpace,
    //无样式,弹簧,使特定位置控件替代
    UIBarButtonSystemItemFixedSpace,
    //写作,编辑图标
    UIBarButtonSystemItemCompose,
    //回复图标
    UIBarButtonSystemItemReply,
    //分享图标
    UIBarButtonSystemItemAction,
    //文件夹图标
    UIBarButtonSystemItemOrganize,
    //打开的书本图标
    UIBarButtonSystemItemBookmarks,
    //放大镜"🔍"图标
    UIBarButtonSystemItemSearch,
    //刷新图标
    UIBarButtonSystemItemRefresh,
    //"X"图标
    UIBarButtonSystemItemStop,
    //"📷"图标
    UIBarButtonSystemItemCamera,
    //垃圾桶图标
    UIBarButtonSystemItemTrash,
    //播放图标
    UIBarButtonSystemItemPlay,
    //暂停图标
    UIBarButtonSystemItemPause,
    //上一曲图标
    UIBarButtonSystemItemRewind,
    //下一曲图标
    UIBarButtonSystemItemFastForward,
    //"Undo"
    UIBarButtonSystemItemUndo NS_ENUM_AVAILABLE_IOS(3_0),
    //"Redo"
    UIBarButtonSystemItemRedo NS_ENUM_AVAILABLE_IOS(3_0),
    UIBarButtonSystemItemPageCurl NS_ENUM_AVAILABLE_IOS(4_0),
};

@class UIImage, UIView;

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIBarButtonItem : UIBarItem <NSCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithImage:(nullable UIImage *)image style:(UIBarButtonItemStyle)style target:(nullable id)target action:(nullable SEL)action;
- (instancetype)initWithImage:(nullable UIImage *)image landscapeImagePhone:(nullable UIImage *)landscapeImagePhone style:(UIBarButtonItemStyle)style target:(nullable id)target action:(nullable SEL)action NS_AVAILABLE_IOS(5_0); // landscapeImagePhone will be used for the bar button image when the bar has Compact or Condensed bar metrics.
- (instancetype)initWithTitle:(nullable NSString *)title style:(UIBarButtonItemStyle)style target:(nullable id)target action:(nullable SEL)action;
- (instancetype)initWithBarButtonSystemItem:(UIBarButtonSystemItem)systemItem target:(nullable id)target action:(nullable SEL)action;
- (instancetype)initWithCustomView:(UIView *)customView;

@property(nonatomic)         UIBarButtonItemStyle style;            // default is UIBarButtonItemStylePlain
@property(nonatomic)         CGFloat              width;            // default is 0.0
@property(nullable, nonatomic,copy)    NSSet<NSString *>   *possibleTitles;   // default is nil
@property(nullable, nonatomic,strong)  __kindof UIView     *customView;       // default is nil
@property(nullable, nonatomic)         SEL                  action;           // default is NULL
@property(nullable, nonatomic,weak)    id                   target;           // default is nil

//
// Appearance modifiers
//

/* Send these messages to the [UIBarButtonItem appearance] proxy to customize all buttons, or, to customize a specific button, send them to a specific UIBarButtonItem instance, which may be used in all the usual places in a UINavigationItem (backBarButtonItem, leftBarButtonItem, rightBarButtonItem) or a UIToolbar.
 */

/* In general, you should specify a value for the normal state to be used by other states which don't have a custom value set.
 
 Similarly, when a property is dependent on the bar metrics (on the iPhone in landscape orientation, bars have a different height from standard), be sure to specify a value for UIBarMetricsDefault.
 
 This sets the background image for buttons of any style.
 */
//Sets the background image for a given state and bar metrics.
/*
 typedef enum : NSInteger {
 //表示横屏竖屏都显示
 UIBarMetricsDefault,
 //表示在只横屏下才显示，和UIBarMetricsLandscapePhone功效一样，不过iOS8已经弃用了
 UIBarMetricsCompact,
 UIBarMetricsDefaultPrompt = 101,
 UIBarMetricsCompactPrompt,
 UIBarMetricsLandscapePhone ,       // Deprecated
 UIBarMetricsLandscapePhonePrompt , // Deprecated.
 } UIBarMetrics;
 */
- (void)setBackgroundImage:(nullable UIImage *)backgroundImage forState:(UIControlState)state barMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
- (nullable UIImage *)backgroundImageForState:(UIControlState)state barMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;

/* This sets the background image for buttons with a specific style. When calling this on a UIBarButtonItem instance, the style argument must match the button's style; when calling on the UIAppearance proxy, any style may be passed.
 */
- (void)setBackgroundImage:(nullable UIImage *)backgroundImage forState:(UIControlState)state style:(UIBarButtonItemStyle)style barMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(6_0) UI_APPEARANCE_SELECTOR;
- (nullable UIImage *)backgroundImageForState:(UIControlState)state style:(UIBarButtonItemStyle)style barMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(6_0) UI_APPEARANCE_SELECTOR;

@property(nullable, nonatomic,strong) UIColor *tintColor NS_AVAILABLE_IOS(5_0);

/* For adjusting the vertical centering of bordered bar buttons within the bar
 */
- (void)setBackgroundVerticalPositionAdjustment:(CGFloat)adjustment forBarMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
- (CGFloat)backgroundVerticalPositionAdjustmentForBarMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;

/* For adjusting the position of a title (if any) within a bordered bar button
 */
- (void)setTitlePositionAdjustment:(UIOffset)adjustment forBarMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
- (UIOffset)titlePositionAdjustmentForBarMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;

/* The remaining appearance modifiers apply solely to UINavigationBar back buttons and are ignored by other buttons.
 */
/*
 backgroundImage must be a resizable image for good results.
 */
- (void)setBackButtonBackgroundImage:(nullable UIImage *)backgroundImage forState:(UIControlState)state barMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED;
- (nullable UIImage *)backButtonBackgroundImageForState:(UIControlState)state barMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED;

- (void)setBackButtonTitlePositionAdjustment:(UIOffset)adjustment forBarMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED;
- (UIOffset)backButtonTitlePositionAdjustmentForBarMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED;

/* For adjusting the vertical centering of bordered bar buttons within the bar
 */
- (void)setBackButtonBackgroundVerticalPositionAdjustment:(CGFloat)adjustment forBarMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED;
- (CGFloat)backButtonBackgroundVerticalPositionAdjustmentForBarMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END

