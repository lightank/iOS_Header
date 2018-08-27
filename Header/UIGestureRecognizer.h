//
//  UIGestureRecognizer.h
//  UIKit
//
//  Copyright (c) 2008-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@protocol UIGestureRecognizerDelegate;
@class UIView, UIEvent, UITouch, UIPress;
//手势状态
typedef NS_ENUM(NSInteger, UIGestureRecognizerState) {
    //手势识别器尚未识别其手势，但可能正在评估触摸事件。 这是默认状态
    UIGestureRecognizerStatePossible,   // the recognizer has not yet recognized its gesture, but may be evaluating touch events. this is the default state
    //手势识别器已经接收被识别为手势的触摸。将在运行循环的下一回合调用动作方法
    UIGestureRecognizerStateBegan,      // the recognizer has received touches recognized as the gesture. the action method will be called at the next turn of the run loop
    //识别器已经接收被识别为对手势的改变的触摸。 将在运行循环的下一回合调用动作方法
    UIGestureRecognizerStateChanged,    // the recognizer has received touches recognized as a change to the gesture. the action method will be called at the next turn of the run loop
    //识别器已经接收被识别为手势的结束的触摸。 操作方法将在运行循环的下一个循环处被调用，并且识别器将被重置为UIGestureRecognizerStatePossible
    UIGestureRecognizerStateEnded,      // the recognizer has received touches recognized as the end of the gesture. the action method will be called at the next turn of the run loop and the recognizer will be reset to UIGestureRecognizerStatePossible
    //识别器已经接收到导致取消手势的触摸。 将在运行循环的下一回合调用动作方法。 识别器将被重置为UIGestureRecognizerStatePossible
    UIGestureRecognizerStateCancelled,  // the recognizer has received touches resulting in the cancellation of the gesture. the action method will be called at the next turn of the run loop. the recognizer will be reset to UIGestureRecognizerStatePossible
    //识别器已经接收到不能被识别为手势的触摸序列。 该操作方法将不被调用，识别器将被重置为UIGestureRecognizerStatePossible
    UIGestureRecognizerStateFailed,     // the recognizer has received a touch sequence that can not be recognized as the gesture. the action method will not be called and the recognizer will be reset to UIGestureRecognizerStatePossible
    
    // Discrete Gestures – gesture recognizers that recognize a discrete event but do not report changes (for example, a tap) do not transition through the Began and Changed states and can not fail or be cancelled
    //识别器已经接收被识别为手势的触摸。 操作方法将在运行循环的下一个循环处被调用，并且识别器将被重置为UIGestureRecognizerStatePossible
    UIGestureRecognizerStateRecognized = UIGestureRecognizerStateEnded // the recognizer has received touches recognized as the gesture. the action method will be called at the next turn of the run loop and the recognizer will be reset to UIGestureRecognizerStatePossible
};

NS_CLASS_AVAILABLE_IOS(3_2) @interface UIGestureRecognizer : NSObject

// Valid action method signatures:
//     -(void)handleGesture;
//     -(void)handleGesture:(UIGestureRecognizer*)gestureRecognizer;
//初始化,添加target跟相应action
- (instancetype)initWithTarget:(nullable id)target action:(nullable SEL)action NS_DESIGNATED_INITIALIZER; // designated initializer
//添加target跟相应action
- (void)addTarget:(id)target action:(SEL)action;    // add a target/action pair. you can call this multiple times to specify multiple target/actions
//移除target跟相应action
- (void)removeTarget:(nullable id)target action:(nullable SEL)action; // remove the specified target/action pair. passing nil for target matches all targets, and the same for actions
//手势状态
@property(nonatomic,readonly) UIGestureRecognizerState state;  // the current state of the gesture recognizer
//代理
@property(nullable,nonatomic,weak) id <UIGestureRecognizerDelegate> delegate; // the gesture recognizer's delegate
//默认为YES。 禁用手势识别器将不会收到触摸。 当更改为否时，如果正在识别手势，手势识别器将被取消
@property(nonatomic, getter=isEnabled) BOOL enabled;  // default is YES. disabled gesture recognizers will not receive touches. when changed to NO the gesture recognizer will be cancelled if it's currently recognizing a gesture

// a UIGestureRecognizer receives touches hit-tested to its view and any of that view's subviews
//UIGestureRecognizer接收对其视图和任何该视图的子视图的hit-tested测试
//手势附加的视图。 通过使用addGestureRecognizer：方法将识别器添加到UIView中来设置
@property(nullable, nonatomic,readonly) UIView *view;           // the view the gesture is attached to. set by adding the recognizer to a UIView using the addGestureRecognizer: method
//默认为YES。 导致touchesCancelled：withEvent：或pressCancelled：withEvent：在动作方法被调用之前立即发送到所有触摸或按压的视图中被识别为此手势的一部分
@property(nonatomic) BOOL cancelsTouchesInView;       // default is YES. causes touchesCancelled:withEvent: or pressesCancelled:withEvent: to be sent to the view for all touches or presses recognized as part of this gesture immediately before the action method is called.
//默认为NO。 只有在此手势识别失败之后，才能将所有触摸或按下事件传递到目标视图。 设置为YES以防止视图处理可能被识别为此手势的一部分的任何触摸或按压
@property(nonatomic) BOOL delaysTouchesBegan;         // default is NO.  causes all touch or press events to be delivered to the target view only after this gesture has failed recognition. set to YES to prevent views from processing any touches or presses that may be recognized as part of this gesture
//默认为YES。 导致touchesEnded或pressedEnded事件只有在此手势识别失败后才能传递到目标视图。 这确保如果识别手势，则可以取消作为手势一部分的触摸或按键
@property(nonatomic) BOOL delaysTouchesEnded;         // default is YES. causes touchesEnded or pressesEnded events to be delivered to the target view only after this gesture has failed recognition. this ensures that a touch or press that is part of the gesture can be cancelled if the gesture is recognized
//An array of touch types used to distinguish type of touches.
@property(nonatomic, copy) NSArray<NSNumber *> *allowedTouchTypes NS_AVAILABLE_IOS(9_0); // Array of UITouchTypes as NSNumbers.
//An array of press types used to distinguish the type of button press.
@property(nonatomic, copy) NSArray<NSNumber *> *allowedPressTypes NS_AVAILABLE_IOS(9_0); // Array of UIPressTypes as NSNumbers.

// Indicates whether the gesture recognizer will consider touches of different touch types simultaneously.
// If NO, it receives all touches that match its allowedTouchTypes.
// If YES, once it receives a touch of a certain type, it will ignore new touches of other types, until it is reset to UIGestureRecognizerStatePossible.
//指示手势识别器是否会同时考虑不同触摸类型的触摸。
//如果否，它将接收与其allowedTouchTypes匹配的所有触摸。
//如果是，一旦接收到某种类型的触摸，它将忽略其他类型的新触摸，直到它被重置为UIGestureRecognizerStatePossible。
@property (nonatomic) BOOL requiresExclusiveTouchType NS_AVAILABLE_IOS(9_2); // defaults to YES

// create a relationship with another gesture recognizer that will prevent this gesture's actions from being called until otherGestureRecognizer transitions to UIGestureRecognizerStateFailed
// if otherGestureRecognizer transitions to UIGestureRecognizerStateRecognized or UIGestureRecognizerStateBegan then this recognizer will instead transition to UIGestureRecognizerStateFailed
// example usage: a single tap may require a double tap to fail
//创建与另一个手势识别器的关系，这将阻止此手势的动作被调用，直到otherGestureRecognizer转换为UIGestureRecognizerStateFailed
//如果otherGestureRecognizer转换为UIGestureRecognizerStateRecognized或UIGestureRecognizerStateBegan，则该识别器将转而转换为UIGestureRecognizerStateFailed
//示例用法：单击可能需要双击才能失败
- (void)requireGestureRecognizerToFail:(UIGestureRecognizer *)otherGestureRecognizer;

// individual UIGestureRecognizer subclasses may provide subclass-specific location information. see individual subclasses for details
//个别UIGestureRecognizer子类可以提供特定于子类的位置信息。 有关详细信息，请参阅各个子类
//手势的通用单点位置。 通常是涉及触摸的重心
- (CGPoint)locationInView:(nullable UIView*)view;                                // a generic single-point location for the gesture. usually the centroid of the touches involved

#if UIKIT_DEFINE_AS_PROPERTIES
//指定位置可以查询的触摸次数
@property(nonatomic, readonly) NSUInteger numberOfTouches;                                          // number of touches involved for which locations can be queried
#else
- (NSUInteger)numberOfTouches;                                          // number of touches involved for which locations can be queried
#endif
//指定触摸事件的地点
- (CGPoint)locationOfTouch:(NSUInteger)touchIndex inView:(nullable UIView*)view; // the location of a particular touch

@end


@protocol UIGestureRecognizerDelegate <NSObject>
@optional
// called when a gesture recognizer attempts to transition out of UIGestureRecognizerStatePossible. returning NO causes it to transition to UIGestureRecognizerStateFailed
//当手势识别器尝试转换出UIGestureRecognizerStatePossible时调用。返回NO导致它转换到UIGestureRecognizerStateFailed
- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer;

// called when the recognition of one of gestureRecognizer or otherGestureRecognizer would be blocked by the other
// return YES to allow both to recognize simultaneously. the default implementation returns NO (by default no two gestures can be recognized simultaneously)
// note: returning YES is guaranteed to allow simultaneous recognition. returning NO is not guaranteed to prevent simultaneous recognition, as the other gesture's delegate may return YES
//当其中一个手势识别器或其他GestureRecognizer的识别被另一个阻止时调用
//返回YES以允许两者同时识别。 默认实现返回NO（默认情况下不会同时识别两个手势）
//注意：返回YES保证允许同时识别。 返回NO不能保证同时识别，因为其他手势的代理可能返回YES
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer;

// called once per attempt to recognize, so failure requirements can be determined lazily and may be set up between recognizers across view hierarchies
// return YES to set up a dynamic failure requirement between gestureRecognizer and otherGestureRecognizer
//
// note: returning YES is guaranteed to set up the failure requirement. returning NO does not guarantee that there will not be a failure requirement as the other gesture's counterpart delegate or subclass methods may return YES
//每次尝试识别一次，因此可以懒洋洋地确定故障要求，并且可以跨视图层次结构在识别器之间建立
//返回YES以在gestureRecognizer和其他GestureRecognizer之间设置动态失败要求
//注意：返回YES是保证设置失败的要求。 返回NO并不保证不会有失败的要求，因为另一个手势的对方委托或子类方法可能返回YES
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRequireFailureOfGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer NS_AVAILABLE_IOS(7_0);
//Overridden to indicate that the receiver should be required to fail by the specified gesture recognizer.
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldBeRequiredToFailByGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer NS_AVAILABLE_IOS(7_0);

// called before touchesBegan:withEvent: is called on the gesture recognizer for a new touch. return NO to prevent the gesture recognizer from seeing this touch
//在触摸之前调用开始：withEvent：在手势识别器上调用新的触摸。 返回NO以防止手势识别器看到此触摸
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch;

// called before pressesBegan:withEvent: is called on the gesture recognizer for a new press. return NO to prevent the gesture recognizer from seeing this press
//在pressBegan之前打电话：withEvent：在手机识别器上调用新的按压。 返回NO，以防止手势识别器看到此新闻
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceivePress:(UIPress *)press;

@end

NS_ASSUME_NONNULL_END
