//
//  UITabBarController.h
//  UIKit
//
//  Copyright (c) 2007-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIViewControllerTransitioning.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITabBar.h>

NS_ASSUME_NONNULL_BEGIN

@class UIView, UIImage, UINavigationController, UITabBarItem;
@protocol UITabBarControllerDelegate;

/*!
 UITabBarController manages a button bar and transition view, for an application with multiple top-level modes.
 
 To use in your application, add its view to the view hierarchy, then add top-level view controllers in order.
 Most clients will not need to subclass UITabBarController.
 
 If more than five view controllers are added to a tab bar controller, only the first four will display.
 The rest will be accessible under an automatically generated More item.
 
 UITabBarController is rotatable if all of its view controllers are rotatable.
 */
/*
 UITabBarController管理一个按钮栏和转换视图，用于具有多个顶级模式的应用程序。
  
   要在应用程序中使用，请将其视图添加到视图层次结构中，然后按顺序添加顶级视图控制器。
   大多数客户端不需要对UITabBarController进行子类化。
  
   如果超过五个视图控制器添加到标签栏控制器，则只显示前四个。
   其余的将在自动生成的更多项目下访问。
  
   如果所有视图控制器都可旋转，则UITabBarController可旋转。
 */
//一个 TabBar 上只能出现最多5个 TabBarItem ，第六个及更多的将不被显示
/*
 参考自:http://blog.csdn.net/ssirreplaceable/article/details/52324936
 UITabBarController的原理
 
 当UITabBarController做为Window的根控制器时，程序一启动，UITabBarController就会一次性初始化所有子控制器，但是默认只加载第一个控制器视图，其他视图控制器只初始化，但默认不会加载，只有在需要显示的时候才调用loadView方法加载。特殊情况：在AppDelegate中设置其他的子控制器视图的背景颜色，就会提前加载该控制器视图，但不显示该视图。
 
 每一个控制器视图只加载一次，就会一直存在内存中，当切换子控制器时直接显示，不显示在屏幕上的子控制器不会被销毁。当遇到内存警告时，会释放掉没有加载的子控制器。
 
 每个视图控制器都有一个tabBarController属性，通过它可以访问所在的UITabBarController，而且对于UITabBarController的直接子视图，其tabBarController属性相当于它的父视图parentViewController。
 
 每个视图控制器都有一个tabBarItem属性，通过它控制视图在UITabBarController的tabBar中的显示信息
 
 tabBarItem的image属性必须是png格式(建议大小32*32)，并且打开alpha通道否则无法正常显示。
 
 当往UITabBarController添加子控制器，标签栏就会有序的自动生成对应的UITabBarButton对象，有多少个子控制器，标签栏就有多少个UITabBarButton对象，但是子控制器的数量超过5个的时候，标签栏上的第五个UITabBarButton对象就会显示成”More”类型的按钮。
 */
NS_CLASS_AVAILABLE_IOS(2_0) @interface UITabBarController : UIViewController <UITabBarDelegate, NSCoding>
//An array of the root view controllers displayed by the tab bar interface.
//由选项卡栏界面显示的根视图控制器的数组。
@property(nullable, nonatomic,copy) NSArray<__kindof UIViewController *> *viewControllers;
// If the number of view controllers is greater than the number displayable by a tab bar, a "More" navigation controller will automatically be shown.
// The "More" navigation controller will not be returned by -viewControllers, but it may be returned by -selectedViewController.
//如果视图控制器的数量大于选项卡栏可显示的数字，则会自动显示“更多”导航控制器。
//“更多”导航控制器不会由-viewController返回，但可能由-selectedViewController返回。
//重置控制器
- (void)setViewControllers:(NSArray<__kindof UIViewController *> * __nullable)viewControllers animated:(BOOL)animated;
//The view controller associated with the currently selected tab item.
//与当前选择的选项卡项相关联的视图控制器。
@property(nullable, nonatomic, assign) __kindof UIViewController *selectedViewController; // This may return the "More" navigation controller if it exists.
//The index of the view controller associated with the currently selected tab item.
//与当前选择的选项卡项相关联的视图控制器的索引。
@property(nonatomic) NSUInteger selectedIndex;
//The view controller that manages the More navigation interface. (read-only)
//管理更多导航界面的视图控制器。 （只读）
//moreNavigationController是默认创建的，只有子控制器的数量超过5个的时候才显示”More”按钮
@property(nonatomic, readonly) UINavigationController *moreNavigationController __TVOS_PROHIBITED; // Returns the "More" navigation controller, creating it if it does not already exist.
//如果不为零，则“更多”视图将包括一个“编辑”按钮，该按钮显示指定控制器的自定义UI。 默认情况下，所有视图控制器都是可定制的。
//此属性控制选项卡栏中的哪些项目可以由用户重新排列。 当用户点击“标签栏”视图上的“更多”项目时，会显示一个自定义界面，显示在主标签栏上不适合的任何项目。 此界面还包含一个编辑按钮，允许用户重新排列项目。 只有相关视图控制器在此阵列中的项目才能从此界面重新排列。 如果数组为空或此属性的值为nil，则选项卡栏不允许任何项目重新排列。
//更改viewControllers属性的值（直接或使用setViewControllers：animated：method）也会更改此属性的值。 首次分配给标签栏控制器时，默认情况下，所有视图控制器都是可自定义的。
// 在”More”的控制器视图中，有一个“Edit”按钮，设置这个按钮里面显示的自定义控制器，默认是所有控制器
// 注意：当UITabBarController的viewControllers属性发生变化的时候，customizableViewControllers就会自动设置成跟viewControllers一致
@property(nullable, nonatomic, copy) NSArray<__kindof UIViewController *> *customizableViewControllers __TVOS_PROHIBITED; // If non-nil, then the "More" view will include an "Edit" button that displays customization UI for the specified controllers. By default, all view controllers are customizable.
//为 - [UIActionSheet showFromTabBar：]提供的。 试图直接修改标签栏的内容会抛出异常。
@property(nonatomic,readonly) UITabBar *tabBar NS_AVAILABLE_IOS(3_0); // Provided for -[UIActionSheet showFromTabBar:]. Attempting to modify the contents of the tab bar directly will throw an exception.

@property(nullable, nonatomic,weak) id<UITabBarControllerDelegate> delegate;

@end

@protocol UITabBarControllerDelegate <NSObject>
@optional
//Asks the delegate whether the specified view controller should be made active.
//请求代表是否应使指定的视图控制器处于活动状态。
- (BOOL)tabBarController:(UITabBarController *)tabBarController shouldSelectViewController:(UIViewController *)viewController NS_AVAILABLE_IOS(3_0);
//Tells the delegate that the user selected an item in the tab bar.
//告诉委托人用户在标签栏中选择了一个项目。
- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)viewController;
//Tells the delegate that the tab bar customization sheet is about to be displayed.
//告诉代理人，标签栏定制表即将被显示。
//当点击”More”的控制器视图里的“Edit”按钮时调用
- (void)tabBarController:(UITabBarController *)tabBarController willBeginCustomizingViewControllers:(NSArray<__kindof UIViewController *> *)viewControllers NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;
// 点击”More”的控制器视图里的“Edit”按钮，在即将退出编辑时调用
- (void)tabBarController:(UITabBarController *)tabBarController willEndCustomizingViewControllers:(NSArray<__kindof UIViewController *> *)viewControllers changed:(BOOL)changed NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;
// 点击”More”的控制器视图里的“Edit”按钮，在退出编辑后调用
- (void)tabBarController:(UITabBarController *)tabBarController didEndCustomizingViewControllers:(NSArray<__kindof UIViewController *> *)viewControllers changed:(BOOL)changed __TVOS_PROHIBITED;
//Called to allow the delegate to provide the complete set of supported interface orientations for the tab bar controller.
//Return Value:One of the UIInterfaceOrientationMask constants that represents the set of interface orientations supported by the tab bar controller.
//被调用以查询tabBarController支持的旋转方向
- (UIInterfaceOrientationMask)tabBarControllerSupportedInterfaceOrientations:(UITabBarController *)tabBarController NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
//Called to allow the delegate to provide the preferred orientation for presentation of the tab bar controller.
//被调用以查询tabBarController支持最佳旋转方向
- (UIInterfaceOrientation)tabBarControllerPreferredInterfaceOrientationForPresentation:(UITabBarController *)tabBarController NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
//Called to allow the delegate to return a UIViewControllerInteractiveTransitioning delegate object for use during an animated tab bar transition.
//调用去允许代理返回一个在tab bar转场动画时遵守UIViewControllerInteractiveTransitioning协议的代理
- (nullable id <UIViewControllerInteractiveTransitioning>)tabBarController:(UITabBarController *)tabBarController
                               interactionControllerForAnimationController: (id <UIViewControllerAnimatedTransitioning>)animationController NS_AVAILABLE_IOS(7_0);
//Called to allow the delegate to return a UIViewControllerAnimatedTransitioning delegate object for use during a noninteractive tab bar view controller transition.
//调用去允许代理返回一个在无交互tab bar转场时遵守UIViewControllerAnimatedTransitioning协议的代理
- (nullable id <UIViewControllerAnimatedTransitioning>)tabBarController:(UITabBarController *)tabBarController
                     animationControllerForTransitionFromViewController:(UIViewController *)fromVC
                                                       toViewController:(UIViewController *)toVC  NS_AVAILABLE_IOS(7_0);

@end

@interface UIViewController (UITabBarControllerItem)
//如果没有明确设置，则使用视图控制器的标题自动创建。
@property(null_resettable, nonatomic, strong) UITabBarItem *tabBarItem; // Automatically created lazily with the view controller's title if it's not set explicitly.
//如果视图控制器具有标签栏控制器作为其祖先，则返回。 否则返回零。
@property(nullable, nonatomic, readonly, strong) UITabBarController *tabBarController; // If the view controller has a tab bar controller as its ancestor, return it. Returns nil otherwise.

@end

NS_ASSUME_NONNULL_END
