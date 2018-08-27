//
//  UINavigationController.h
//  UIKit
//
//  Copyright (c) 2007-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIPanGestureRecognizer.h>
#import <UIKit/UITapGestureRecognizer.h>

/*!
 UINavigationController manages a stack of view controllers and a navigation bar.
 It performs horizontal view transitions for pushed and popped views while keeping the navigation bar in sync.
 
 Most clients will not need to subclass UINavigationController.
 
 If a navigation controller is nested in a tabbar controller, it uses the title and toolbar attributes of the bottom view controller on the stack.
 
 UINavigationController is rotatable if its top view controller is rotatable.
 Navigation between controllers with non-uniform rotatability is currently not supported.
 */


NS_ASSUME_NONNULL_BEGIN
//These constants define the type of navigation controller transitions that can occur.
//导航控制器当前发生的转场类型
typedef NS_ENUM(NSInteger, UINavigationControllerOperation) {
    //无
    UINavigationControllerOperationNone,    //No operation is taking place.
    //push,一个控制器被推到导航控制器栈
    UINavigationControllerOperationPush,    //A view controller is being pushed onto the navigation stack.
    //pop,一个控制器从导航控制器栈被移除
    UINavigationControllerOperationPop, //The topmost view controller is being removed from the navigation stack.
};

//A global constant that specifies a preferred duration when animating the navigation bar.
//一个指明导航栏动画时间的全局常量
UIKIT_EXTERN const CGFloat UINavigationControllerHideShowBarDuration;

@class UIView, UINavigationBar, UINavigationItem, UIToolbar;
@protocol UINavigationControllerDelegate;


NS_CLASS_AVAILABLE_IOS(2_0) @interface UINavigationController : UIViewController


/* Use this initializer to make the navigation controller use your custom bar class.
 Passing nil for navigationBarClass will get you UINavigationBar, nil for toolbarClass gets UIToolbar.
 The arguments must otherwise be subclasses of the respective UIKit classes.
 */
//Initializes and returns a newly created navigation controller that uses your custom bar subclasses.
//初始化并返回使用自定义的navigationBar和toolbar的导航控制器
- (instancetype)initWithNavigationBarClass:(nullable Class)navigationBarClass toolbarClass:(nullable Class)toolbarClass NS_AVAILABLE_IOS(5_0);
//使用根控制器初始化
- (instancetype)initWithRootViewController:(UIViewController *)rootViewController; // Convenience method pushes the root view controller without animation.
//使用水平滑动效果将控制器推入栈,对已经入栈的控制器无影响
- (void)pushViewController:(UIViewController *)viewController animated:(BOOL)animated; // Uses a horizontal slide transition. Has no effect if the view controller is already in the stack.
//Pops the top view controller from the navigation stack and updates the display.
//pop栈顶控制器,并更新显示
- (nullable UIViewController *)popViewControllerAnimated:(BOOL)animated; // Returns the popped controller.
//pop控制器,指定这个指定控制器是栈顶控制器,返回被pop的控制器数组
- (nullable NSArray<__kindof UIViewController *> *)popToViewController:(UIViewController *)viewController animated:(BOOL)animated; // Pops view controllers until the one specified is on top. Returns the popped controllers.
//pop 到根控制器,返回被pop的控制器数组
- (nullable NSArray<__kindof UIViewController *> *)popToRootViewControllerAnimated:(BOOL)animated; // Pops until there's only a single view controller left on the stack. Returns the popped controllers.
//栈顶控制器
@property(nullable, nonatomic,readonly,strong) UIViewController *topViewController; // The top view controller on the stack.
//如果存在modal 出来的控制器,那么就返回它,如果没有就返回栈顶控制器
@property(nullable, nonatomic,readonly,strong) UIViewController *visibleViewController; // Return modal view controller if it exists. Otherwise the top view controller.
//在栈中的控制器数组
@property(nonatomic,copy) NSArray<__kindof UIViewController *> *viewControllers; // The current view controller stack.
//重置栈控制器,如果animated为YES,那么模拟push或pop取决于新的栈顶控制器是否先前在栈中
- (void)setViewControllers:(NSArray<UIViewController *> *)viewControllers animated:(BOOL)animated NS_AVAILABLE_IOS(3_0); // If animated is YES, then simulate a push or pop depending on whether the new top view controller was previously in the stack.
//A Boolean value that indicates whether the navigation bar is hidden.
/*
 //方法一：
 [self.navigationController setNavigationBarHidden:YES];
 //方法二：
 self.navigationController.navigationBar.hidden = YES;
 以上两个方法效果相同，区别在于一个是操作navigationController的属性（navigationBar是navigationController的一个属性），一个是操作navigationBar的属性。
 
 但是，方法一会出现一个bug，就是当页面初始状态时setNavigationBarHidden为YES,也就相当于navigationBar那一刻是不存在的，那么导航栏上的控件也就自然看不到，而且navigationBar的出现和消失会很突兀。
 
 采用方法二效果会好很多，因为navigationBar本身是存在的，只是做了显示和隐藏的操作，过渡也相对顺滑很多。
 */
//是否隐藏导航栏
@property(nonatomic,getter=isNavigationBarHidden) BOOL navigationBarHidden;
//隐藏导航栏,可以带动画,如果带动画,那么动画时间使用UINavigationControllerHideShowBarDuration
- (void)setNavigationBarHidden:(BOOL)hidden animated:(BOOL)animated; // Hide or show the navigation bar. If animated, it will transition vertically using UINavigationControllerHideShowBarDuration.
//The navigation bar managed by the navigation controller. (read-only)
//被导航控制器管理的导航栏.只读属性
@property(nonatomic,readonly) UINavigationBar *navigationBar; // The navigation bar managed by the controller. Pushing, popping or setting navigation items on a managed navigation bar is not supported.
//是否隐藏顶部的toolbar栏,默认是YES
@property(nonatomic,getter=isToolbarHidden) BOOL toolbarHidden NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED; // Defaults to YES, i.e. hidden.
////隐藏toolbar栏,可以带动画,如果带动画,那么动画时间使用UINavigationControllerHideShowBarDuration
- (void)setToolbarHidden:(BOOL)hidden animated:(BOOL)animated NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED; // Hide or show the toolbar at the bottom of the screen. If animated, it will transition vertically using UINavigationControllerHideShowBarDuration.
//The custom toolbar associated with the navigation controller. (read-only)
//导航控制器中自定义的toolbar
@property(null_resettable,nonatomic,readonly) UIToolbar *toolbar NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED; // For use when presenting an action sheet.
//导航控制器的代理
@property(nullable, nonatomic, weak) id<UINavigationControllerDelegate> delegate;
//The gesture recognizer responsible for popping the top view controller off the navigation stack. (read-only)
//The navigation controller installs this gesture recognizer on its view and uses it to pop the topmost view controller off the navigation stack. You can use this property to retrieve the gesture recognizer and tie it to the behavior of other gesture recognizers in your user interface. When tying your gesture recognizers together, make sure they recognize their gestures simultaneously to ensure that your gesture recognizers are given a chance to handle the event.
//右滑返回手势,这个手势可以pop当前栈顶控制器
@property(nullable, nonatomic, readonly) UIGestureRecognizer *interactivePopGestureRecognizer NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;

/**
 Presents the specified view controller in the navigation interface.

 @param vc The view controller to display.
 @param sender The object that made the request to show the view controller.
 */
//对pushViewController:animated:的解释
- (void)showViewController:(UIViewController *)vc sender:(nullable id)sender NS_AVAILABLE_IOS(8_0); // Interpreted as pushViewController:animated:

/// When the keyboard appears, the navigation controller's navigationBar toolbar will be hidden. The bars will remain hidden when the keyboard dismisses, but a tap in the content area will show them.
//A Boolean value indicating whether the navigation controller hides its bars when the keyboard appears.
//When this property is set to YES, the appearance of the keyboard causes the navigation controller to hide its navigation bar and toolbar. The default value of this property is NO.
//在键盘弹出时,隐藏navigationBar跟toolbar,键盘消失后,navigationBar跟toolbar并不会展示
@property (nonatomic, readwrite, assign) BOOL hidesBarsWhenKeyboardAppears NS_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED;
/// When the user swipes, the navigation controller's navigationBar & toolbar will be hidden (on a swipe up) or shown (on a swipe down). The toolbar only participates if it has items.
//A Boolean value indicating whether the navigation bar hides its bars in response to a swipe gesture.
//When this property is set to YES, an upward swipe hides the navigation bar and toolbar. A downward swipe shows both bars again. If the toolbar does not have any items, it remains visible even after a swipe. The default value of this property is NO.
//当为YES时,向上滑时,隐藏navigationBar和toolbar,向下滑时显示navigationBar和toolbar
@property (nonatomic, readwrite, assign) BOOL hidesBarsOnSwipe NS_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED;
/// The gesture recognizer that triggers if the bars will hide or show due to a swipe. Do not change the delegate or attempt to replace this gesture by overriding this method.
//The gesture recognizer used to hide the navigation bar and toolbar. (read-only)
//This property contains the gesture recognizer used to hide and show the navigation bar and toolbar. The gesture recognizer is inactive unless the hidesBarsOnSwipe property is YES. You can make changes to the gesture recognizer as needed but must not change its delegate and you must not remove the default target object and action that come configured with it. Do not try to replace this gesture recognizer by overriding the property.
//If you tie this gesture recognizer to one of your own, make sure both recognize their gestures simultaneously to ensure that each has a chance to handle the event.
//上下滑手势
@property (nonatomic, readonly, strong) UIPanGestureRecognizer *barHideOnSwipeGestureRecognizer NS_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED;
/// When the UINavigationController's vertical size class is compact, hide the UINavigationBar and UIToolbar. Unhandled taps in the regions that would normally be occupied by these bars will reveal the bars.
//When the value of this property is YES, the navigation controller hides its navigation bar and toolbar when it transitions to a vertically compact environment. Upon returning to a vertically regular environment, the navigation controller automatically shows both bars again. In addition, unhandled taps in the content area cause the navigation controller to show both bars again. The default value of this property is NO.
//当导航控制器的size class 是vertically compact型的时候,隐藏navigationBar和toolbar,不是时自动显示.在内容被点击时,将重新显示navigationBar和toolbar,默认是NO
@property (nonatomic, readwrite, assign) BOOL hidesBarsWhenVerticallyCompact NS_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED;
/// When the user taps, the navigation controller's navigationBar & toolbar will be hidden or shown, depending on the hidden state of the navigationBar. The toolbar will only be shown if it has items to display.
//点击手势,为YES,则点击时隐藏navigationBar和toolbar,再次点击时显示隐藏navigationBar和toolbar
@property (nonatomic, readwrite, assign) BOOL hidesBarsOnTap NS_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED;
/// The gesture recognizer used to recognize if the bars will hide or show due to a tap in content. Do not change the delegate or attempt to replace this gesture by overriding this method.
//点击手势
@property (nonatomic, readonly, assign) UITapGestureRecognizer *barHideOnTapGestureRecognizer NS_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED;

@end

@protocol UIViewControllerInteractiveTransitioning;
@protocol UIViewControllerAnimatedTransitioning;

@protocol UINavigationControllerDelegate <NSObject>

@optional

// Called when the navigation controller shows a new top view controller via a push, pop or setting of the view controller stack.
//在导航控制器在通过push或pop,或者重置栈控制器数组展示一个新的栈顶控制器时调用
- (void)navigationController:(UINavigationController *)navigationController willShowViewController:(UIViewController *)viewController animated:(BOOL)animated;
- (void)navigationController:(UINavigationController *)navigationController didShowViewController:(UIViewController *)viewController animated:(BOOL)animated;
//Returns the complete set of supported interface orientations for the navigation controller, as determined by the delegate.
//返回由代理决定的导航控制器支持的设备方向无序数组
- (UIInterfaceOrientationMask)navigationControllerSupportedInterfaceOrientations:(UINavigationController *)navigationController NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
//Returns the preferred orientation for presentation of the navigation controller, as determined by the delegate.
//返回由代理决定的导航控制器偏好的的设备方向
- (UIInterfaceOrientation)navigationControllerPreferredInterfaceOrientationForPresentation:(UINavigationController *)navigationController NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
//Called to allow the delegate to return an interactive animator object for use during view controller transitions.
//在控制器转场时调用去允许代理返回一个动画对象去使用
- (nullable id <UIViewControllerInteractiveTransitioning>)navigationController:(UINavigationController *)navigationController
                                   interactionControllerForAnimationController:(id <UIViewControllerAnimatedTransitioning>) animationController NS_AVAILABLE_IOS(7_0);
//Called to allow the delegate to return a noninteractive animator object for use during view controller transitions.
//Implement this delegate method when you want to provide a custom animated transition between view controllers as they are added to or removed from the navigation stack. The object you return should be capable of configuring and performing noninteractive animations for the specified view controllers for the specified type of operation over a fixed period of time.
//If you want to allow the user to perform interactive transitions, you must also implement the navigationController:interactionControllerForAnimationController: method.
//实现这个代理方法去返回自定义的转场动画,在控制器从栈中被添加或移除时使用.这个返回的对象应该能够处理在特定的时间和动作内给定控制器的noninteractive animations
- (nullable id <UIViewControllerAnimatedTransitioning>)navigationController:(UINavigationController *)navigationController
                                            animationControllerForOperation:(UINavigationControllerOperation)operation
                                                         fromViewController:(UIViewController *)fromVC
                                                           toViewController:(UIViewController *)toVC  NS_AVAILABLE_IOS(7_0);

@end

@interface UIViewController (UINavigationControllerItem)
//The navigation item used to represent the view controller in a parent's navigation bar.
//控制器在父控制器的navigation bar中的navigation item
@property(nonatomic,readonly,strong) UINavigationItem *navigationItem; // Created on-demand so that a view controller may customize its navigation appearance.
//当被push入栈的时候,隐藏下方的bar(比如tab bar),默认是NO
@property(nonatomic) BOOL hidesBottomBarWhenPushed __TVOS_PROHIBITED; // If YES, then when this view controller is pushed into a controller hierarchy with a bottom bar (like a tab bar), the bottom bar will slide out. Default is NO.
//控制器所在的导航控制器
@property(nullable, nonatomic,readonly,strong) UINavigationController *navigationController; // If this view controller has been pushed onto a navigation controller, return it.

@end

@interface UIViewController (UINavigationControllerContextualToolbarItems)
//控制器的toolBar
@property (nullable, nonatomic, strong) NSArray<__kindof UIBarButtonItem *> *toolbarItems NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;
- (void)setToolbarItems:(nullable NSArray<UIBarButtonItem *> *)toolbarItems animated:(BOOL)animated NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
