//
//  UIWindow.h
//  UIKit
//
//  Copyright (c) 2005-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>   //基础框架入口
#import <CoreGraphics/CoreGraphics.h>   //绘图入口
#import <UIKit/UIView.h>    //视图对象
#import <UIKit/UIApplication.h> //提供iOS程序运行期的协作和控制
#import <UIKit/UIKitDefines.h>  //一些宏定义

NS_ASSUME_NONNULL_BEGIN

typedef CGFloat UIWindowLevel;  //32位则为float | 64位为double
/*
 UIEvent 触摸事件，运动事件
 UIScreen 屏幕处理
 NSUndoManager  记录撤销，修改操作的消息
 UIViewController 视图控制器
 */
@class UIEvent, UIScreen, NSUndoManager, UIViewController;

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIWindow : UIView

@property(nonatomic,strong) UIScreen *screen NS_AVAILABLE_IOS(3_2);  // default is [UIScreen mainScreen]. changing the screen may be an expensive operation and should not be done in performance-sensitive code

@property(nonatomic) UIWindowLevel windowLevel;                   // default = 0.0
@property(nonatomic,readonly,getter=isKeyWindow) BOOL keyWindow;
- (void)becomeKeyWindow;                               // override point for subclass. Do not call directly
- (void)resignKeyWindow;                               // override point for subclass. Do not call directly

- (void)makeKeyWindow;
- (void)makeKeyAndVisible;                             // convenience. most apps call this to show the main window and also make it key. otherwise use view hidden property

@property(nullable, nonatomic,strong) UIViewController *rootViewController NS_AVAILABLE_IOS(4_0);  // default is nil
/*
 事件拦截分发到指定视图对象
 当用户发起一个事件，比如触摸屏幕或者晃动设备，系统产生一个事件，同时投递给UIApplication，而UIApplication则将这个事件传递给特定
 UIWindow进行处理(正常情况都一个程序都只有一个UIWindow)，然后由UIWindow将这个事件传递给特定的对象(即first responder)并通过响应链
 进行处理。虽然都是通过响应链对事件进行处理，但是触摸事件和运动事件在处理上有着明显的不同(主要体现在确定哪个对象才是他们的firstresponder)：
 */
- (void)sendEvent:(UIEvent *)event;                    // called by UIApplication to dispatch events to views inside the window
//窗口坐标系统转化
//转化当前窗口一个坐标相对另外一个窗口的坐标
- (CGPoint)convertPoint:(CGPoint)point toWindow:(nullable UIWindow *)window;    // can be used to convert to another window
//转化另外窗口一个坐标相对于当前窗口的坐标
- (CGPoint)convertPoint:(CGPoint)point fromWindow:(nullable UIWindow *)window;  // pass in nil to mean screen
//转化当前窗口一个矩形坐标相对另外一个窗口的坐标
- (CGRect)convertRect:(CGRect)rect toWindow:(nullable UIWindow *)window;
//转化另外窗口一个矩形坐标相对于当前窗口的坐标
- (CGRect)convertRect:(CGRect)rect fromWindow:(nullable UIWindow *)window;

@end

UIKIT_EXTERN const UIWindowLevel UIWindowLevelNormal;   //默认等级
UIKIT_EXTERN const UIWindowLevel UIWindowLevelAlert;    //UIAlert等级
UIKIT_EXTERN const UIWindowLevel UIWindowLevelStatusBar __TVOS_PROHIBITED;  //状态栏等级
// 通知对象窗口为可见
UIKIT_EXTERN NSNotificationName const UIWindowDidBecomeVisibleNotification; // nil
// 通知对象窗口为隐藏
UIKIT_EXTERN NSNotificationName const UIWindowDidBecomeHiddenNotification;  // nil
// 通知对象窗口为重要
UIKIT_EXTERN NSNotificationName const UIWindowDidBecomeKeyNotification;     // nil
// 通知对象窗口取消主窗
UIKIT_EXTERN NSNotificationName const UIWindowDidResignKeyNotification;     // nil

// Each notification includes a nil object and a userInfo dictionary containing the
// begining and ending keyboard frame in screen coordinates. Use the various UIView and
// UIWindow convertRect facilities to get the frame in the desired coordinate system.
// Animation key/value pairs are only available for the "will" family of notification.
//当键盘显示或消失时，系统会发送相关的通知:
//通知键盘对象视图即将加载
UIKIT_EXTERN NSNotificationName const UIKeyboardWillShowNotification __TVOS_PROHIBITED;
//通知键盘对象视图完全加载
UIKIT_EXTERN NSNotificationName const UIKeyboardDidShowNotification __TVOS_PROHIBITED;
//通知键盘对象视图即将隐藏
UIKIT_EXTERN NSNotificationName const UIKeyboardWillHideNotification __TVOS_PROHIBITED;
//通知键盘对象视图完全隐藏
UIKIT_EXTERN NSNotificationName const UIKeyboardDidHideNotification __TVOS_PROHIBITED;
/*
 通知消息 NSNotification中的 userInfo字典中包含键盘的位置和大小信息，对应的key为
     UIKeyboardFrameBeginUserInfoKey
     UIKeyboardFrameEndUserInfoKey
     UIKeyboardAnimationDurationUserInfoKey
     UIKeyboardAnimationCurveUserInfoKey
     UIKeyboardFrameBeginUserInfoKey,
     UIKeyboardFrameEndUserInfoKey
     对应的Value是个NSValue对象，内部包含CGRect结构，分别为键盘起始时和终止时的位置信息。
     UIKeyboardAnimationCurveUserInfoKey对应的Value是NSNumber对象，内部为UIViewAnimationCurve类型的数据，表示键盘显示或消失的动画类型。
     UIKeyboardAnimationDurationUserInfoKey对应的Value也是NSNumber对象，内部为double类型的数据，表示键盘h显示或消失时动画的持续时间
 
 例如，在UIKeyboardWillShowNotification，UIKeyboardDidShowNotification通知中的userInfo内容为
 userInfo = {
     UIKeyboardAnimationCurveUserInfoKey = 0;
     UIKeyboardAnimationDurationUserInfoKey = "0.25";
     UIKeyboardBoundsUserInfoKey = "NSRect: {{0, 0}, {320, 216}}";
     UIKeyboardCenterBeginUserInfoKey = "NSPoint: {160, 588}";
     UIKeyboardCenterEndUserInfoKey = "NSPoint: {160, 372}";
     UIKeyboardFrameBeginUserInfoKey = "NSRect: {{0, 480}, {320, 216}}";
     UIKeyboardFrameChangedByUserInteraction = 0;
     UIKeyboardFrameEndUserInfoKey = "NSRect: {{0, 264}, {320, 216}}";
 }
 在UIKeyboardWillHideNotification,UIKeyboardDidHideNotification通知中的userInfo内容为:
 userInfo = {
     UIKeyboardAnimationCurveUserInfoKey = 0;
     UIKeyboardAnimationDurationUserInfoKey = "0.25";
     UIKeyboardBoundsUserInfoKey = "NSRect: {{0, 0}, {320, 216}}";
     UIKeyboardCenterBeginUserInfoKey = "NSPoint: {160, 372}";
     UIKeyboardCenterEndUserInfoKey = "NSPoint: {160, 588}";
     UIKeyboardFrameBeginUserInfoKey = "NSRect: {{0, 264}, {320, 216}}";
     UIKeyboardFrameChangedByUserInteraction = 0;
     UIKeyboardFrameEndUserInfoKey = "NSRect: {{0, 480}, {320, 216}}";
 }
 */

UIKIT_EXTERN NSString *const UIKeyboardFrameBeginUserInfoKey        NS_AVAILABLE_IOS(3_2) __TVOS_PROHIBITED; // NSValue of CGRect
UIKIT_EXTERN NSString *const UIKeyboardFrameEndUserInfoKey          NS_AVAILABLE_IOS(3_2) __TVOS_PROHIBITED; // NSValue of CGRect
UIKIT_EXTERN NSString *const UIKeyboardAnimationDurationUserInfoKey NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED; // NSNumber of double
UIKIT_EXTERN NSString *const UIKeyboardAnimationCurveUserInfoKey    NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED; // NSNumber of NSUInteger (UIViewAnimationCurve)
UIKIT_EXTERN NSString *const UIKeyboardIsLocalUserInfoKey           NS_AVAILABLE_IOS(9_0) __TVOS_PROHIBITED; // NSNumber of BOOL

// Like the standard keyboard notifications above, these additional notifications include
// a nil object and begin/end frames of the keyboard in screen coordinates in the userInfo dictionary.
//键盘即将改变布局发出通知
UIKIT_EXTERN NSNotificationName const UIKeyboardWillChangeFrameNotification  NS_AVAILABLE_IOS(5_0) __TVOS_PROHIBITED;
//键盘已经改变布局后发出通知
UIKIT_EXTERN NSNotificationName const UIKeyboardDidChangeFrameNotification   NS_AVAILABLE_IOS(5_0) __TVOS_PROHIBITED;

// These keys are superseded by UIKeyboardFrameBeginUserInfoKey and UIKeyboardFrameEndUserInfoKey.
UIKIT_EXTERN NSString *const UIKeyboardCenterBeginUserInfoKey   NS_DEPRECATED_IOS(2_0, 3_2) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIKeyboardCenterEndUserInfoKey     NS_DEPRECATED_IOS(2_0, 3_2) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIKeyboardBoundsUserInfoKey        NS_DEPRECATED_IOS(2_0, 3_2) __TVOS_PROHIBITED;

NS_ASSUME_NONNULL_END
