//
//  UINavigationBar.h
//  UIKit
//
//  Copyright (c) 2005-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIFont.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIButton.h>
#import <UIKit/UIBarButtonItem.h>
#import <UIKit/UIBarCommon.h>

NS_ASSUME_NONNULL_BEGIN

@class UINavigationItem, UIBarButtonItem, UIImage, UIColor;
@protocol UINavigationBarDelegate;

NS_CLASS_AVAILABLE_IOS(2_0) @interface UINavigationBar : UIView <NSCoding, UIBarPositioning>

@property(nonatomic,assign) UIBarStyle barStyle UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED;
@property(nullable,nonatomic,weak) id<UINavigationBarDelegate> delegate;

/*
 New behavior on iOS 7.
 Default is YES.
 You may force an opaque background by setting the property to NO.
 If the navigation bar has a custom background image, the default is inferred
 from the alpha values of the image—YES if it has any pixel with alpha < 1.0
 If you send setTranslucent:YES to a bar with an opaque custom background image
 it will apply a system opacity less than 1.0 to the image.
 If you send setTranslucent:NO to a bar with a translucent custom background image
 it will provide an opaque background for the image using the bar's barTintColor if defined, or black
 for UIBarStyleBlack or white for UIBarStyleDefault if barTintColor is nil.
 */
/*
 iOS 7上的新行为。
   默认为YES。
   您可以通过将属性设置为NO来强制执行不透明的背景。
   如果导航栏具有自定义背景图像，则推断出默认值
   从图像的alpha值 - 如果它具有alpha <1.0的任何像素，则为YES
   如果将setTranslucent：YES发送到具有不透明的自定义背景图像的条形图
   它将对图像应用系统不透明度小于1.0。
   如果将setTranslucent：NO发送到具有半透明自定义背景图像的条形图
   它将使用bar的barTintColor（如果定义）或黑色为图像提供不透明的背景
   对于UIBarStyleBlack，如果barTintColor为零，则为UIBarStyleDefault。
 */
//A Boolean value indicating whether the navigation bar is translucent (YES) or not (NO).
//指示导航栏是否为半透明（YES）的布尔值（否）。
@property(nonatomic,assign,getter=isTranslucent) BOOL translucent NS_AVAILABLE_IOS(3_0) UI_APPEARANCE_SELECTOR; // Default is NO on iOS 6 and earlier. Always YES if barStyle is set to UIBarStyleBlackTranslucent

// Pushing a navigation item displays the item's title in the center of the navigation bar.
// The previous top navigation item (if it exists) is displayed as a "back" button on the left.
//push导航item会在导航栏的中央显示该项目的标题。
//上一个顶部导航项（如果存在）显示为左侧的“后退”按钮。
- (void)pushNavigationItem:(UINavigationItem *)item animated:(BOOL)animated;
//Pops the top item from the receiver’s stack and updates the navigation bar.
//从接收者的堆栈中pop出顶部项目，并更新导航栏。
- (nullable UINavigationItem *)popNavigationItemAnimated:(BOOL)animated; // Returns the item that was popped.
//The navigation item at the top of the navigation bar’s stack. (read-only)
//导航栏顶部的导航项目。 （只读）
@property(nullable, nonatomic,readonly,strong) UINavigationItem *topItem;
//The navigation item that is immediately below the topmost item on navigation bar’s stack. (read-only)
//位于导航栏堆栈上最上方项目下方的导航项。 （只读）
@property(nullable, nonatomic,readonly,strong) UINavigationItem *backItem;
//An array of navigation items managed by the navigation bar.
//由导航栏管理的导航项数组。
@property(nullable,nonatomic,copy) NSArray<UINavigationItem *> *items;
//如果动画为YES，则根据新的top item 是否以前在堆栈中模拟推送或弹出。
- (void)setItems:(nullable NSArray<UINavigationItem *> *)items animated:(BOOL)animated; // If animated is YES, then simulate a push or pop depending on whether the new top item was previously in the stack.

/*
 The behavior of tintColor for bars has changed on iOS 7.0. It no longer affects the bar's background
 and behaves as described for the tintColor property added to UIView.
 To tint the bar's background, please use -barTintColor.
 */
/*
 在iOS 7.0上，tintColor for bars的行为发生了变化。 它不再影响bar的背景
   并按照添加到UIView的tintColor属性的描述来执行。
   要使bar的背景变色，请使用-barTintColor。
 */
//The tint color to apply to the button item.
//渲染色应用于按钮项目。
@property(null_resettable, nonatomic,strong) UIColor *tintColor;
@property(nullable, nonatomic,strong) UIColor *barTintColor NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR;  // default is nil

/* In general, you should specify a value for the normal state to be used by other states which don't have a custom value set.
 
 Similarly, when a property is dependent on the bar metrics (on the iPhone in landscape orientation, bars have a different height from standard), be sure to specify a value for UIBarMetricsDefault.
 */
/*
 一般来说，您应该为没有设置自定义值的其他状态指定正常状态的值。
 类似地，当属性依赖于条形度量（在iPhone上以横向方向，条形与标准的高度不同）时，一定要为UIBarMetricsDefault指定一个值。
 */
//Sets the background image to use for a given bar position and set of metrics.
//设置用于给定栏位置和一组指标的背景图像。
- (void)setBackgroundImage:(nullable UIImage *)backgroundImage forBarPosition:(UIBarPosition)barPosition barMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR;
//Returns the background image to use for a given bar position and set of metrics.
//返回用于给定条形位置和指标集的背景图像。
- (nullable UIImage *)backgroundImageForBarPosition:(UIBarPosition)barPosition barMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR;

/*
 Same as using UIBarPositionAny in -setBackgroundImage:forBarPosition:barMetrics. Resizable images will be stretched
 vertically if necessary when the navigation bar is in the position UIBarPositionTopAttached.
 */
/*
 与在-setBackgroundImage中使用UIBarPositionAny相同：forBarPosition：barMetrics。 可调整大小的图像将被拉伸
   当导航栏位于UIBarPositionTopAttached的位置时，必要时垂直。
 */
//Sets the background image for given bar metrics.
//设置给定条指标的背景图像。
- (void)setBackgroundImage:(nullable UIImage *)backgroundImage forBarMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
//Returns the background image for given bar metrics.
//返回给定条指标的背景图像。
- (nullable UIImage *)backgroundImageForBarMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;

/* Default is nil. When non-nil, a custom shadow image to show instead of the default shadow image. For a custom shadow to be shown, a custom background image must also be set with -setBackgroundImage:forBarMetrics: (if the default background image is used, the default shadow image will be used).
 */
/*
 默认值为零。 当不为零时，自定义阴影图像将显示，而不是默认的阴影图像。 要显示自定义阴影，还必须使用-setBackgroundImage设置自定义背景图像：forBarMetrics：（如果使用默认背景图像，将使用默认阴影图像）。
 */
//The shadow image to be used for the navigation bar.
//用于导航栏的阴影图像。
@property(nullable, nonatomic,strong) UIImage *shadowImage NS_AVAILABLE_IOS(6_0) UI_APPEARANCE_SELECTOR;

/* You may specify the font, text color, and shadow properties for the title in the text attributes dictionary, using the keys found in NSAttributedString.h.
 */
//您可以使用NSAttributedString.h中找到的键在文本属性字典中指定标题的字体，文本颜色和阴影属性。
//Display attributes for the bar’s title text.
//bar title的文字属性,可以在NSAttributedString.h中找到相关属性,如:NSForegroundColorAttributeName(文字颜色)
@property(nullable,nonatomic,copy) NSDictionary<NSString *,id> *titleTextAttributes NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
//Sets the title’s vertical position adjustment for given bar metrics.
//设置标题的垂直位置调整用于给定的条形指标。
- (void)setTitleVerticalPositionAdjustment:(CGFloat)adjustment forBarMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
//Returns the title’s vertical position adjustment for given bar metrics.
//返回给定条形指标的标题垂直位置调整。
- (CGFloat)titleVerticalPositionAdjustmentForBarMetrics:(UIBarMetrics)barMetrics NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;

/*
 The back indicator image is shown beside the back button.
 The back indicator transition mask image is used as a mask for content during push and pop transitions
 Note: These properties must both be set if you want to customize the back indicator image.
 */
/*
 后面的指示器图像显示在后退按钮旁边。
   反向指示器转换掩码图像在推送和弹出转换期间用作内容的掩码
   注意：如果要自定义反向指示器图像，则必须同时设置这些属性。
 */
//The image shown beside the back button.
//后退按钮旁边显示的图像。
@property(nullable,nonatomic,strong) UIImage *backIndicatorImage NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED;
//The image used as a mask for content during push and pop transitions.
//图像在推送和弹出转换期间用作内容的mask。
@property(nullable,nonatomic,strong) UIImage *backIndicatorTransitionMaskImage NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED;

@end

/*
 UINavigationBarDelegate协议定义了可选方法，UINavigationBar委托应该实现这些方法，以便在从堆栈中推送和弹出项目时更新其视图。 导航栏仅代表屏幕顶部的栏，而不是下面的视图。 当顶级项目更改时，应用程序负责实施该行为。
 您可以通过实现navigationBar：shouldPushItem：和navigationBar：shouldPopItem：methods来控制是否应该推送或弹出项目。 如果允许动作，这些方法应返回YES; 否则，否。
 屏幕应始终反映导航栏上的顶部项目。 您实现导航栏：didPushItem：方法来更新导航栏下方的视图以反映新项目。 类似地，您实现了导航栏：didPopItem：方法来替换导航栏下方的视图。
 */
@protocol UINavigationBarDelegate <UIBarPositioningDelegate>

@optional
//Returns a Boolean value indicating whether the navigation bar should push an item.
//返回一个布尔值，指示导航栏是否应该push一个项目。
- (BOOL)navigationBar:(UINavigationBar *)navigationBar shouldPushItem:(UINavigationItem *)item; // called to push. return NO not to.
//在推动动画结束时呼叫，如果不是动画，则立即进行
- (void)navigationBar:(UINavigationBar *)navigationBar didPushItem:(UINavigationItem *)item;    // called at end of animation of push or immediately if not animated
- (BOOL)navigationBar:(UINavigationBar *)navigationBar shouldPopItem:(UINavigationItem *)item;  // same as push methods
- (void)navigationBar:(UINavigationBar *)navigationBar didPopItem:(UINavigationItem *)item;

@end

NS_CLASS_AVAILABLE_IOS(2_0) @interface UINavigationItem : NSObject <NSCoding>

//Returns a navigation item initialized with the specified title.
//返回用指定的标题初始化的导航项。
- (instancetype)initWithTitle:(NSString *)title NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
//标题最上方的堆栈。 默认值为零
@property(nullable, nonatomic,copy)   NSString        *title;             // Title when topmost on the stack. default is nil
//用于替代标题的自定义视图。 可以水平尺寸。 仅当堆叠上的项目最上层时才使用。
@property(nullable, nonatomic,strong) UIView          *titleView;         // Custom view to use in lieu of a title. May be sized horizontally. Only used when item is topmost on the stack.
//A single line of text displayed at the top of the navigation bar.
//导航栏顶部显示一行文字。
//导航栏上方显示的说明文字按钮。
@property(nullable,nonatomic,copy)   NSString *prompt __TVOS_PROHIBITED;     // Explanatory text to display above the navigation bar buttons.
//设置它的时候，会在push的下一个控制器返回按钮中显示,默认是空,如需更改它,要重新定义个UIBarbuttonItem赋给backBarButtonItem,并设置这个自定义的title
/*
 UIBarButtonItem *backBarButtonItem = [[UIBarButtonItem alloc]
                                                     initWithTitle:@"返回"
                                                     style:UIBarButtonItemStylePlain
                                                     target:nil
                                                     action:nil];
 self.navigationItem.backBarButtonItem = backBarButtonItem;
 */
//The bar button item to use when a back button is needed on the navigation bar.
//在导航栏上需要后退按钮时使用的条形按钮item。
@property(nullable,nonatomic,strong) UIBarButtonItem *backBarButtonItem __TVOS_PROHIBITED; // Bar button item to use for the back button in the child navigation item.
//A Boolean value that determines whether the back button is hidden.
//一个布尔值，用于确定后退按钮是否被隐藏。如果是，则该导航项将在堆栈顶部隐藏后退按钮。
@property(nonatomic,assign) BOOL hidesBackButton __TVOS_PROHIBITED; // If YES, this navigation item will hide the back button when it's on top of the stack.
- (void)setHidesBackButton:(BOOL)hidesBackButton animated:(BOOL)animated __TVOS_PROHIBITED;

/* Use these properties to set multiple items in a navigation bar.
 The older single properties (leftBarButtonItem and rightBarButtonItem) now refer to
 the first item in the respective array of items.
 
 NOTE: You'll achieve the best results if you use either the singular properties or
 the plural properties consistently and don't try to mix them.
 
 leftBarButtonItems are placed in the navigation bar left to right with the first
 item in the list at the left outside edge and left aligned.
 rightBarButtonItems are placed right to left with the first item in the list at
 the right outside edge and right aligned.
 */
/*
 使用这些属性可以在导航栏中设置多个项目。
 旧的单个属性（leftBarButtonItem和rightBarButtonItem）现在引用相应的项目数组中的第一个项目。
 
 注意：如果您使用单个属性或多个属性数组一致，不要混合使用。比如:使用leftBarButtonItem修改左边的item,那么就一直使用这个属性,不应该使用leftBarButtonItems
 leftBarButtonItems放在导航栏中从左到右的第一个列表中的项目在左外边缘并左对齐。
 rightBarButtonItems从右到左放置在列表中的第一个项目
 右边右边对齐。
 */
@property(nullable,nonatomic,copy) NSArray<UIBarButtonItem *> *leftBarButtonItems NS_AVAILABLE_IOS(5_0);
@property(nullable,nonatomic,copy) NSArray<UIBarButtonItem *> *rightBarButtonItems NS_AVAILABLE_IOS(5_0);
- (void)setLeftBarButtonItems:(nullable NSArray<UIBarButtonItem *> *)items animated:(BOOL)animated NS_AVAILABLE_IOS(5_0);
- (void)setRightBarButtonItems:(nullable NSArray<UIBarButtonItem *> *)items animated:(BOOL)animated NS_AVAILABLE_IOS(5_0);

/* By default, the leftItemsSupplementBackButton property is NO. In this case,
 the back button is not drawn and the left item or items replace it. If you
 would like the left items to appear in addition to the back button (as opposed to instead of it)
 set leftItemsSupplementBackButton to YES.
 */
//A Boolean value indicating whether the left items are displayed in addition to the back button.
//一个布尔值，表示除后退按钮之外是否显示左边的项目。
//设置左侧自定义按钮是否与返回按钮共同存在
@property(nonatomic) BOOL leftItemsSupplementBackButton NS_AVAILABLE_IOS(5_0) __TVOS_PROHIBITED;

// Some navigation items want to display a custom left or right item when they're on top of the stack.
// A custom left item replaces the regular back button unless you set leftItemsSupplementBackButton to YES
@property(nullable, nonatomic,strong) UIBarButtonItem *leftBarButtonItem;
@property(nullable, nonatomic,strong) UIBarButtonItem *rightBarButtonItem;
- (void)setLeftBarButtonItem:(nullable UIBarButtonItem *)item animated:(BOOL)animated;
- (void)setRightBarButtonItem:(nullable UIBarButtonItem *)item animated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
