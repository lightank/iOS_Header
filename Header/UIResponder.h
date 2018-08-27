//
//  UIResponder.h
//  UIKit
//
//  Copyright (c) 2005-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIEvent.h>

NS_ASSUME_NONNULL_BEGIN

@class UIPress;
@class UIPressesEvent;

@protocol UIResponderStandardEditActions <NSObject>
@optional
//Remove the selection from the user interface and write it to the pasteboard.
//剪切到粘贴板上
- (void)cut:(nullable id)sender NS_AVAILABLE_IOS(3_0);
//Copy the selection to the pasteboard.
//复制到粘贴板上
- (void)copy:(nullable id)sender NS_AVAILABLE_IOS(3_0);
//Read data from the pasteboard and display it in the user interface.
//粘贴
- (void)paste:(nullable id)sender NS_AVAILABLE_IOS(3_0);
//Select the next object the user taps.
//选择
- (void)select:(nullable id)sender NS_AVAILABLE_IOS(3_0);
//Select all objects in the current view.
//全选
- (void)selectAll:(nullable id)sender NS_AVAILABLE_IOS(3_0);
//Remove the selection from the user interface.
//删除
- (void)delete:(nullable id)sender NS_AVAILABLE_IOS(3_2);
//Change the writing direction to left-to-right.
//改变书写方向从左到右
- (void)makeTextWritingDirectionLeftToRight:(nullable id)sender NS_AVAILABLE_IOS(5_0);
//Change the writing direction to right-to-left.
//改变书写方向从右到左
- (void)makeTextWritingDirectionRightToLeft:(nullable id)sender NS_AVAILABLE_IOS(5_0);
//Toggle the bold style information of the selected text.
//切换选中粗体字体信息
- (void)toggleBoldface:(nullable id)sender NS_AVAILABLE_IOS(6_0);
//Toggle the italic style information of the selected text.
//切换选中斜体字体信息
- (void)toggleItalics:(nullable id)sender NS_AVAILABLE_IOS(6_0);
//Toggle the underline style information of the selected text.
//切换选中的下划线字体信息
- (void)toggleUnderline:(nullable id)sender NS_AVAILABLE_IOS(6_0);
//Asks the object to increase the size of an item.
//要求对象增加某个item的size
- (void)increaseSize:(nullable id)sender NS_AVAILABLE_IOS(7_0);
//Asks the object to decrease the size of an item.
//要求对象减少某个item的size
- (void)decreaseSize:(nullable id)sender NS_AVAILABLE_IOS(7_0);

@end

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIResponder : NSObject <UIResponderStandardEditActions>

#if UIKIT_DEFINE_AS_PROPERTIES
//Returns the receiver's next responder, or nil if it
//The UIResponder class does not store or set the next responder automatically, instead returning nil by default. Subclasses must override this method to set the next responder. UIView implements this method by returning the UIViewController object that manages it (if it has one) or its superview (if it doesn’t); UIViewController implements the method by returning its view’s superview; UIWindow returns the application object, and UIApplication returns nil.
//返回接收者的下一个响应者，如果没有就返回nil;
//UIResponder类不自动存储和设置下一个响应者，而是默认返回nil。子类必须override这个方法来设置下一个响应者。UIView重写这个方法返回管理这个UIView的UIViewController(如果有的话)或者它的父视图(如果没有的话)；UIViewController重写这个方法，返回UIViewController的View的父View；UIWindow重写这个方法，返回UIApplication对象；UIApplication返回nil
@property(nonatomic, readonly, nullable) UIResponder *nextResponder;
#else
- (nullable UIResponder*)nextResponder;
#endif

#if UIKIT_DEFINE_AS_PROPERTIES
//Returns a Boolean value indicating whether the receiver can become first responder.
//否可以成为第一响应者,默认为NO
@property(nonatomic, readonly) BOOL canBecomeFirstResponder;    // default is NO
#else
- (BOOL)canBecomeFirstResponder;    // default is NO
#endif
//Notifies the receiver that it is about to become first responder in its window.
//如果返回YES,则通知当前对象将成为第一响应者
- (BOOL)becomeFirstResponder;

#if UIKIT_DEFINE_AS_PROPERTIES
//Returns a Boolean value indicating whether the receiver is willing to relinquish first-responder status.
//当前对象释放可以辞去第一响应者
@property(nonatomic, readonly) BOOL canResignFirstResponder;    // default is YES
#else
- (BOOL)canResignFirstResponder;    // default is YES
#endif
- (BOOL)resignFirstResponder;

#if UIKIT_DEFINE_AS_PROPERTIES
//Returns a Boolean value indicating whether the receiver is the first responder.
//当前对象是否是第一响应者
@property(nonatomic, readonly) BOOL isFirstResponder;
#else
- (BOOL)isFirstResponder;
#endif

// Generally, all responders which do custom touch handling should override all four of these methods.
// Your responder will receive either touchesEnded:withEvent: or touchesCancelled:withEvent: for each
// touch it is handling (those touches it received in touchesBegan:withEvent:).
// *** You must handle cancelled touches to ensure correct behavior in your application.  Failure to
// do so is very likely to lead to incorrect behavior or crashes.
//触摸事件
//触摸屏幕
- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event;
//在屏幕上移动
- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event;
//离开屏幕
- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event;
//系统事件干扰,取消触摸事件
- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event;
//Sent to the responder when the estimated properties for a touch have changed so that they are no longer estimated, or an update is no longer expected.
//当触摸对象预估属性改变到不再是预估值是,或者更新不是预期的时候调用
- (void)touchesEstimatedPropertiesUpdated:(NSSet<UITouch *> *)touches NS_AVAILABLE_IOS(9_1);

// Generally, all responders which do custom press handling should override all four of these methods.
// Your responder will receive either pressesEnded:withEvent or pressesCancelled:withEvent: for each
// press it is handling (those presses it received in pressesBegan:withEvent:).
// pressesChanged:withEvent: will be invoked for presses that provide an analog value
// (like thumbsticks or analog push buttons)
// *** You must handle cancelled presses to ensure correct behavior in your application.  Failure to
// do so is very likely to lead to incorrect behavior or crashes.
//按压事件
//Sent to the receiver when a physical button is pressed in the associated view.
- (void)pressesBegan:(NSSet<UIPress *> *)presses withEvent:(nullable UIPressesEvent *)event NS_AVAILABLE_IOS(9_0);
- (void)pressesChanged:(NSSet<UIPress *> *)presses withEvent:(nullable UIPressesEvent *)event NS_AVAILABLE_IOS(9_0);
- (void)pressesEnded:(NSSet<UIPress *> *)presses withEvent:(nullable UIPressesEvent *)event NS_AVAILABLE_IOS(9_0);
- (void)pressesCancelled:(NSSet<UIPress *> *)presses withEvent:(nullable UIPressesEvent *)event NS_AVAILABLE_IOS(9_0);
//运动事件
- (void)motionBegan:(UIEventSubtype)motion withEvent:(nullable UIEvent *)event NS_AVAILABLE_IOS(3_0);
- (void)motionEnded:(UIEventSubtype)motion withEvent:(nullable UIEvent *)event NS_AVAILABLE_IOS(3_0);
- (void)motionCancelled:(UIEventSubtype)motion withEvent:(nullable UIEvent *)event NS_AVAILABLE_IOS(3_0);
//Sent to the receiver when a remote-control event is received.
//远程控制事件
- (void)remoteControlReceivedWithEvent:(nullable UIEvent *)event NS_AVAILABLE_IOS(4_0);
//验证命令:在我们的应用中，经常会处理各种菜单命令，如文本输入框的”复制”、”粘贴”等。UIResponder为此提供了两个方法来支持此类操作。首先使用以下方法可以启动或禁用指定的命令
//该方法默认返回YES，我们的类可以通过某种途径处理这个命令，包括类本身或者其下一个响应者。子类可以重写这个方法来开启菜单命令。例如，如果我们希望菜单支持”Copy”而不支持”Paser”，则在我们的子类中实现该方法。需要注意的是，即使在子类中禁用某个命令，在响应链上的其它响应者也可能会处理这些命令。
- (BOOL)canPerformAction:(SEL)action withSender:(nullable id)sender NS_AVAILABLE_IOS(3_0);
// Allows an action to be forwarded to another target. By default checks -canPerformAction:withSender: to either return self, or go up the responder chain.
//另外，我们可以使用以下方法来获取可以响应某一行为的接收者：
- (nullable id)targetForAction:(SEL)action withSender:(nullable id)sender NS_AVAILABLE_IOS(7_0);

@property(nullable, nonatomic,readonly) NSUndoManager *undoManager NS_AVAILABLE_IOS(3_0);

@end
//These constants indicate which modifier keys are pressed.
//被按键类型
typedef NS_OPTIONS(NSInteger, UIKeyModifierFlags) {
    //大写键
    UIKeyModifierAlphaShift     = 1 << 16,  // This bit indicates CapsLock
    //shift键
    UIKeyModifierShift          = 1 << 17,
    //control键
    UIKeyModifierControl        = 1 << 18,
    //The Option key is pressed
    //option键
    UIKeyModifierAlternate      = 1 << 19,
    //command键
    UIKeyModifierCommand        = 1 << 20,
    //The key is located on the numeric keypad.
    UIKeyModifierNumericPad     = 1 << 21,
} NS_ENUM_AVAILABLE_IOS(7_0);

NS_CLASS_AVAILABLE_IOS(7_0) @interface UIKeyCommand : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
//The string of characters corresponding to the keys that must be pressed to match this key command.
//按键说明
@property (nonatomic,readonly) NSString *input;
//类型
@property (nonatomic,readonly) UIKeyModifierFlags modifierFlags;
//The title to display to the user.
//给用户看的title
@property (nullable,nonatomic,copy) NSString *discoverabilityTitle NS_AVAILABLE_IOS(9_0);

// The action for UIKeyCommands should accept a single (id)sender, as do the UIResponderStandardEditActions above

// Creates an key command that will _not_ be discoverable in the UI.
//创建一个将不会在UI中展示的快捷键
+ (UIKeyCommand *)keyCommandWithInput:(NSString *)input modifierFlags:(UIKeyModifierFlags)modifierFlags action:(SEL)action;

// Key Commands with a discoverabilityTitle _will_ be discoverable in the UI.
//创建一个将会在UI中展示的快捷键
+ (UIKeyCommand *)keyCommandWithInput:(NSString *)input modifierFlags:(UIKeyModifierFlags)modifierFlags action:(SEL)action discoverabilityTitle:(NSString *)discoverabilityTitle NS_AVAILABLE_IOS(9_0);

@end

@interface UIResponder (UIResponderKeyCommands)
//快捷键数组
@property (nullable,nonatomic,readonly) NSArray<UIKeyCommand *> *keyCommands NS_AVAILABLE_IOS(7_0); // returns an array of UIKeyCommand objects<
@end

@class UIInputViewController;
@class UITextInputMode;
@class UITextInputAssistantItem;

@interface UIResponder (UIResponderInputViewAdditions)

// Called and presented when object becomes first responder.  Goes up the responder chain.
//The primary view for the input view controller.
//This property is typically used to provide a view to replace the system-supplied keyboard that is presented for UITextField and UITextView objects.
//The value of this read-only property is nil. A responder object that requires a custom view to gather input from the user should redeclare this property as read-write and use it to manage its custom input view. When the receiver becomes the first responder, the responder infrastructure presents the specified input view automatically. Similarly, when the receiver resigns its first responder status, the responder infrastructure automatically dismisses the specified input view.
// 在当前对象成为第一响应者时调用跟显示,默认是只读的nil.只有在UITextField和UITextView中才会弹出系统提供的键盘,如果想使用自定义的视图,UIResponder的子类需要重新声明inputAccessoryView属性为readwrite,并且重写它们的get方法，这样在某个自定义视图变成第一响应者时，它就会自动呼出inputView和inputAccessoryView,注意:需重写-canBecomeFirstResponder返回YES,并可能需要手动调用-becomeFirstResponder
@property (nullable, nonatomic, readonly, strong) __kindof UIView *inputView NS_AVAILABLE_IOS(3_2);
//同上
@property (nullable, nonatomic, readonly, strong) __kindof UIView *inputAccessoryView NS_AVAILABLE_IOS(3_2);

/// This method is for clients that wish to put buttons on the Shortcuts Bar, shown on top of the keyboard.
/// You may modify the returned inputAssistantItem to add to or replace the existing items on the bar.
/// Modifications made to the returned UITextInputAssistantItem are reflected automatically.
/// This method should not be overriden. Goes up the responder chain.
//The input assistant to use when configuring the keyboard’s shortcuts bar. (read-only)
//On iPad, the shortcuts bar above the keyboard contains typing suggestions and other controls for managing text, such as cut, copy, and paste commands. This property contains the text input assistant item you use to configure the custom bar button items that you want included in the shortcuts bar. The shortcuts bar is not available on iPhone or iPod Touch.
//iPad 上输入法预测的一行在 iOS 9 上同时提供了快捷操作
@property (nonnull, nonatomic, readonly, strong) UITextInputAssistantItem *inputAssistantItem NS_AVAILABLE_IOS(9_0) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

// For viewController equivalents of -inputView and -inputAccessoryView
// Called and presented when object becomes first responder.  Goes up the responder chain.
//The custom input view controller to use when the receiver becomes the first responder. (read-only)
//This property is typically used to provide a view controller to replace the system-supplied keyboard that is presented for UITextField and UITextView objects.
//The value of this read-only property is nil. If you want to provide a custom input view controller to replace the system keyboard in your app, redeclare this property as read-write in a UIResponder subclass.. You can then use this property to manage a custom input view controller. When the receiver becomes the first responder, the responder infrastructure presents the specified input view controller automatically. Similarly, when the receiver resigns its first responder status, the responder infrastructure automatically dismisses the specified input view controller.
//同inputView
@property (nullable, nonatomic, readonly, strong) UIInputViewController *inputViewController NS_AVAILABLE_IOS(8_0);
@property (nullable, nonatomic, readonly, strong) UIInputViewController *inputAccessoryViewController NS_AVAILABLE_IOS(8_0);

/* When queried, returns the current UITextInputMode, from which the keyboard language can be determined.
 * When overridden it should return a previously-queried UITextInputMode object, which will attempt to be
 * set inside that app, but not persistently affect the user's system-wide keyboard settings. */
//The text input mode identifies the language and keyboard displayed when this responder is active.
//For responders, the system normally displays a keyboard that is based on the user’s language preferences. You can redefine this property and use it to return a different text input mode in cases where you want a responder to use a specific keyboard. The user can still change the keyboard while the responder is active, but switching away to another responder and then back restores the keyboard you specified.
//文本输入模式标识当响应者激活时的语言(如:zh-Hans,en-US)及显示的键盘
@property (nullable, nonatomic, readonly, strong) UITextInputMode *textInputMode NS_AVAILABLE_IOS(7_0);
/* When the first responder changes and an identifier is queried, the system will establish a context to
 * track the textInputMode automatically. The system will save and restore the state of that context to
 * the user defaults via the app identifier. Use of -textInputMode above will supercede use of -textInputContextIdentifier. */
//如果我们想让UIKit来跟踪这个响应者的文本输入模式，我们可以通过textInputContextIdentifier属性来设置一个标识
@property (nullable, nonatomic, readonly, strong) NSString *textInputContextIdentifier NS_AVAILABLE_IOS(7_0);
// This call is to remove stored app identifier state that is no longer needed.
//为了从程序的user default中清理输入模式信息，UIResponder定义了一个类方法，其声明如下：
+ (void)clearTextInputContextIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(7_0);

// If called while object is first responder, reloads inputView, inputAccessoryView, and textInputMode.  Otherwise ignored.
//Updates the custom input and accessory views when the object is the first responder.
//在对象成为第一响应者后更新inputView,inputAccessoryView,textInputMode
- (void)reloadInputViews NS_AVAILABLE_IOS(3_2);

@end

// These are pre-defined constants for use with the input property of UIKeyCommand objects.
UIKIT_EXTERN NSString *const UIKeyInputUpArrow         NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIKeyInputDownArrow       NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIKeyInputLeftArrow       NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIKeyInputRightArrow      NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIKeyInputEscape          NS_AVAILABLE_IOS(7_0);

@interface UIResponder (ActivityContinuation)
//由UIKit管理的User Activities会在适当的时间自动保存,Handoff开发
@property (nullable, nonatomic, strong) NSUserActivity *userActivity NS_AVAILABLE_IOS(8_0);
//用于更新给定的User Activity的状态
- (void)updateUserActivityState:(NSUserActivity *)activity NS_AVAILABLE_IOS(8_0);
//在我们修改了User Activity的状态后，如果想将其恢复到某个状态，则可以使用以下方法：
- (void)restoreUserActivityState:(NSUserActivity *)activity NS_AVAILABLE_IOS(8_0);
@end

NS_ASSUME_NONNULL_END

