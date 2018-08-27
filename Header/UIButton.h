//
//  UIButton.h
//  UIKit
//
//  Copyright (c) 2005-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage, UIFont, UIColor, UIImageView, UILabel;

typedef NS_ENUM(NSInteger, UIButtonType) {
    //自定义样式
    UIButtonTypeCustom = 0,                         // no button type
    //系统默认样式
    UIButtonTypeSystem NS_ENUM_AVAILABLE_IOS(7_0),  // standard system button
    //用于显示当前列表项的详情 圆圈里的感叹号
    UIButtonTypeDetailDisclosure,
    //该按钮用于显示简短的说明,亮  圆圈里的感叹号
    UIButtonTypeInfoLight,
    //该按钮用户显示简短的说明,暗 圆圈里的感叹号
    UIButtonTypeInfoDark,
    //该按钮通常用于添加联系人  圆圈里的加号
    UIButtonTypeContactAdd,
    //圆角矩形的按钮
    UIButtonTypeRoundedRect = UIButtonTypeSystem,   // Deprecated, use UIButtonTypeSystem instead
};

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIButton : UIControl <NSCoding>

+ (instancetype)buttonWithType:(UIButtonType)buttonType;

// 按钮内的子控件（图片和文字）的内边距
@property(nonatomic)          UIEdgeInsets contentEdgeInsets UI_APPEARANCE_SELECTOR; // default is UIEdgeInsetsZero. On tvOS 10 or later, default is nonzero except for custom buttons.
// 按钮内的子控件（文字）的内边距，
@property(nonatomic)          UIEdgeInsets titleEdgeInsets;                // default is UIEdgeInsetsZero
//是否子高亮状态下对阴影效果在雕刻和浮雕的之间的转变
@property(nonatomic)          BOOL         reversesTitleShadowWhenHighlighted; // default is NO. if YES, shadow reverses to shift between engrave and emboss appearance
// 按钮内的子控件（图片）的内边距
@property(nonatomic)          UIEdgeInsets imageEdgeInsets;                // default is UIEdgeInsetsZero
// 设置在 Highlighted 状态点击时是否调整图片显示亮度
@property(nonatomic)          BOOL         adjustsImageWhenHighlighted;    // default is YES. if YES, image is drawn darker when highlighted(pressed)
// 设置在disabled状态是否调整图片显示亮度
@property(nonatomic)          BOOL         adjustsImageWhenDisabled;       // default is YES. if YES, image is drawn lighter when disabled
//设置在高亮时发光
@property(nonatomic)          BOOL         showsTouchWhenHighlighted __TVOS_PROHIBITED;      // default is NO. if YES, show a simple feedback (currently a glow) while highlighted
//渲染颜色
@property(null_resettable, nonatomic,strong)   UIColor     *tintColor NS_AVAILABLE_IOS(5_0); // The tintColor is inherited through the superview hierarchy. See UIView for more information.
//按钮类型
@property(nonatomic,readonly) UIButtonType buttonType;

// you can set the image, title color, title shadow color, and background image to use for each state. you can specify data
// for a combined state by using the flags added together. in general, you should specify a value for the normal state to be used
// by other states which don't have a custom value set
//设置不同状态下的标题文字
- (void)setTitle:(nullable NSString *)title forState:(UIControlState)state;                     // default is nil. title is assumed to be single line
//设置不同状态下的渲染颜色
- (void)setTitleColor:(nullable UIColor *)color forState:(UIControlState)state UI_APPEARANCE_SELECTOR; // default if nil. use opaque white
//设置不同状态下的标题文字阴影颜色
- (void)setTitleShadowColor:(nullable UIColor *)color forState:(UIControlState)state UI_APPEARANCE_SELECTOR; // default is nil. use 50% black
//设置不同状态下的图片
- (void)setImage:(nullable UIImage *)image forState:(UIControlState)state;                      // default is nil. should be same size if different for different states
//设置不同状态下的背景图片
- (void)setBackgroundImage:(nullable UIImage *)image forState:(UIControlState)state UI_APPEARANCE_SELECTOR; // default is nil
//设置不同状态下的标题富文字
- (void)setAttributedTitle:(nullable NSAttributedString *)title forState:(UIControlState)state NS_AVAILABLE_IOS(6_0); // default is nil. title is assumed to be single line
//不同状态下的标题文字
- (nullable NSString *)titleForState:(UIControlState)state;          // these getters only take a single state value
//不同状态下的标题文字颜色
- (nullable UIColor *)titleColorForState:(UIControlState)state;
//不同状态下的标题文字阴影颜色
- (nullable UIColor *)titleShadowColorForState:(UIControlState)state;
//不同状态下的图片
- (nullable UIImage *)imageForState:(UIControlState)state;
//不同状态下的背景图片
- (nullable UIImage *)backgroundImageForState:(UIControlState)state;
//不同状态下的标题富文字
- (nullable NSAttributedString *)attributedTitleForState:(UIControlState)state NS_AVAILABLE_IOS(6_0);

// these are the values that will be used for the current state. you can also use these for overrides. a heuristic will be used to
// determine what image to choose based on the explict states set. For example, the 'normal' state value will be used for all states
// that don't have their own image defined.
//当前状态下的标题文字
@property(nullable, nonatomic,readonly,strong) NSString *currentTitle;             // normal/highlighted/selected/disabled. can return nil
//当前状态下的标题文字颜色
@property(nonatomic,readonly,strong) UIColor  *currentTitleColor;        // normal/highlighted/selected/disabled. always returns non-nil. default is white(1,1)
//当前状态下的标题文字阴影颜色
@property(nullable, nonatomic,readonly,strong) UIColor  *currentTitleShadowColor;  // normal/highlighted/selected/disabled.
//当前状态下的图片
@property(nullable, nonatomic,readonly,strong) UIImage  *currentImage;             // normal/highlighted/selected/disabled. can return nil
//当前状态下的背景图片
@property(nullable, nonatomic,readonly,strong) UIImage  *currentBackgroundImage;   // normal/highlighted/selected/disabled. can return nil
//当前状态下的标题富文本
@property(nullable, nonatomic,readonly,strong) NSAttributedString *currentAttributedTitle NS_AVAILABLE_IOS(6_0);  // normal/highlighted/selected/disabled. can return nil

// return title and image views. will always create them if necessary. always returns nil for system buttons
//标题文本
@property(nullable, nonatomic,readonly,strong) UILabel     *titleLabel NS_AVAILABLE_IOS(3_0);
//图片
@property(nullable, nonatomic,readonly,strong) UIImageView *imageView  NS_AVAILABLE_IOS(3_0);

// these return the rectangle for the background (assumes bounds), the content (image + title) and for the image and title separately. the content rect is calculated based
// on the title and image size and padding and then adjusted based on the control content alignment. there are no draw methods since the contents
// are rendered in separate subviews (UIImageView, UILabel)
//自定义按钮返回的不同位置
- (CGRect)backgroundRectForBounds:(CGRect)bounds;
- (CGRect)contentRectForBounds:(CGRect)bounds;
- (CGRect)titleRectForContentRect:(CGRect)contentRect;
- (CGRect)imageRectForContentRect:(CGRect)contentRect;
@end

@interface UIButton(UIButtonDeprecated)

@property(nonatomic,strong) UIFont         *font              NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;
@property(nonatomic)        NSLineBreakMode lineBreakMode     NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;
@property(nonatomic)        CGSize          titleShadowOffset NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
