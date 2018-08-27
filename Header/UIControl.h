//
//  UIControl.h
//  UIKit
//
//  Copyright (c) 2005-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

//UIControl事件
typedef NS_OPTIONS(NSUInteger, UIControlEvents) {
    //单点触摸按下事件：用户点触屏幕，又有或者新手指落下的时候
    UIControlEventTouchDown                                         = 1 <<  0,      // on all touch downs
    //多点触摸按下事件，点触计数大于1：用户按下第二，三，或第四根手指的时候
    UIControlEventTouchDownRepeat                                   = 1 <<  1,      // on multiple touchdowns (tap count > 1)
    //当一次触摸在控件窗口内拖动时
    UIControlEventTouchDragInside                                   = 1 <<  2,
    //当一次触摸在控件窗口之外拖动时
    UIControlEventTouchDragOutside                                  = 1 <<  3,
    //当一次触摸从控件窗口之外拖动到内部时
    UIControlEventTouchDragEnter                                    = 1 <<  4,
    //当一次触摸从控件窗口内部拖动到外部时
    UIControlEventTouchDragExit                                     = 1 <<  5,
    //所有在控件之内触摸抬起事件
    UIControlEventTouchUpInside                                     = 1 <<  6,
    //所有在控件之外触摸抬起事件（点触必须开始与控件内部才会发送通知）
    UIControlEventTouchUpOutside                                    = 1 <<  7,
    //所有触摸取消事件，即一次触摸因为放上了太多手指而被取消，或者被上锁或者电话呼叫打断
    UIControlEventTouchCancel                                       = 1 <<  8,
    
    //当控件的值发生改变时，发送通知。用于滑块，分段控件，以及其他取值的控件。你可以配置滑块控件何时发送通知，在滑块被放下时发送，或者在被拖动时发送
    UIControlEventValueChanged                                      = 1 << 12,     // sliders, etc.
    //当控件的首要行为被触发，例如button的点击事件，slider的滑动事件
    UIControlEventPrimaryActionTriggered NS_ENUM_AVAILABLE_IOS(9_0) = 1 << 13,     // semantic action: for buttons, etc.
    
    //UITextField
    //开始编辑
    UIControlEventEditingDidBegin                                   = 1 << 16,     // UITextField
    //编辑中
    UIControlEventEditingChanged                                    = 1 << 17,
    //结束编辑
    UIControlEventEditingDidEnd                                     = 1 << 18,
    //当文本控件内通过按下回车键（或等价行为）结束编辑
    UIControlEventEditingDidEndOnExit                               = 1 << 19,     // 'return key' ending editing
    
    //所有触摸事件
    UIControlEventAllTouchEvents                                    = 0x00000FFF,  // for touch events
    //UITextField:所有的文字编辑事件
    UIControlEventAllEditingEvents                                  = 0x000F0000,  // for UITextField
    //预留给application（应用）使用的事件
    UIControlEventApplicationReserved                               = 0x0F000000,  // range available for application use
    //预留给internal framework（内部框架）使用的事件
    UIControlEventSystemReserved                                    = 0xF0000000,  // range reserved for internal framework use
    //所有事件
    UIControlEventAllEvents                                         = 0xFFFFFFFF
};

//控件如何在垂直方向上布置自身的内容
typedef NS_ENUM(NSInteger, UIControlContentVerticalAlignment) {
    //居中对齐
    UIControlContentVerticalAlignmentCenter  = 0,
    // 顶部对齐
    UIControlContentVerticalAlignmentTop     = 1,
    // 底部对齐
    UIControlContentVerticalAlignmentBottom  = 2,
    //Aligns the content vertically to fill the content rectangle; images may be stretched.
    //填充满
    UIControlContentVerticalAlignmentFill    = 3,
};

//控件如何在水平方向上布置自身的内容
typedef NS_ENUM(NSInteger, UIControlContentHorizontalAlignment) {
    //居中对齐
    UIControlContentHorizontalAlignmentCenter = 0,
    // 左对齐
    UIControlContentHorizontalAlignmentLeft   = 1,
    // 右对齐
    UIControlContentHorizontalAlignmentRight  = 2,
    //填充满
    UIControlContentHorizontalAlignmentFill   = 3,
};

//控件状态
typedef NS_OPTIONS(NSUInteger, UIControlState) {
    //普通状态
    UIControlStateNormal       = 0,
    //高亮状态
    UIControlStateHighlighted  = 1 << 0,                  // used when UIControl isHighlighted is set
    //禁用状态
    UIControlStateDisabled     = 1 << 1,
    //选择状态
    UIControlStateSelected     = 1 << 2,                  // flag usable by app (see below)
    //焦点状态
    UIControlStateFocused NS_ENUM_AVAILABLE_IOS(9_0) = 1 << 3, // Applicable only when the screen supports focus
    //application保留的状态
    UIControlStateApplication  = 0x00FF0000,              // additional flags available for application use
    //internal framework（内部框架）保留的状态
    UIControlStateReserved     = 0xFF000000               // flags reserved for internal framework use
};

@class UITouch;
@class UIEvent;

//______________________________________________________

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIControl : UIView

//A Boolean value that determines whether the receiver is enabled.
//决定控件是否能接收事件
@property(nonatomic,getter=isEnabled) BOOL enabled;                                  // default is YES. if NO, ignores touch events and subclasses may draw differently
//A Boolean value that determines the receiver’s selected state.
//决定控件是否是选中的状态
@property(nonatomic,getter=isSelected) BOOL selected;                                // default is NO may be used by some subclasses or by application
//决定控件是否是高亮的状态
@property(nonatomic,getter=isHighlighted) BOOL highlighted;                          // default is NO. this gets set/cleared automatically when touch enters/exits during tracking and cleared on up
//The vertical alignment of content (text or image) within the receiver.
//控件垂直方向上的布局
@property(nonatomic) UIControlContentVerticalAlignment contentVerticalAlignment;     // how to position content vertically inside control. default is center
//控件水平方向上的布局
@property(nonatomic) UIControlContentHorizontalAlignment contentHorizontalAlignment; // how to position content hozontally inside control. default is center
//控件当前的状态
@property(nonatomic,readonly) UIControlState state;                  // could be more than one state (e.g. disabled|selected). synthesized from other flags.
//Sent to the control when a touch related to the given event enters the control’s bounds.
//当触摸在给定事件发生在控件bounds上时就是YES
@property(nonatomic,readonly,getter=isTracking) BOOL tracking;
//A Boolean value that indicates whether a touch is inside the bounds of the receiver. (read-only)
//布尔值表面一个touch事件是否发生在接收者的bounds中
@property(nonatomic,readonly,getter=isTouchInside) BOOL touchInside; // valid during tracking only
//Sent to the control when a touch related to the given event enters the control’s bounds.
//当一个关联上给定事件的touch事件发生在控件的bounds中时发送事件给控件
- (BOOL)beginTrackingWithTouch:(UITouch *)touch withEvent:(nullable UIEvent *)event;
//Sent continuously to the control as it tracks a touch related to the given event within the control’s bounds.
//当一个关联上给定事件的touch事件不断发生在控件的bounds中时不断的发送事件给控件
- (BOOL)continueTrackingWithTouch:(UITouch *)touch withEvent:(nullable UIEvent *)event;
//Sent to the control when the last touch for the given event completely ends, telling it to stop tracking.
//当一个关联上给定事件的touch事件停止发生在控件的bounds中时发送事件给控件
- (void)endTrackingWithTouch:(nullable UITouch *)touch withEvent:(nullable UIEvent *)event; // touch is sometimes nil if cancelTracking calls through to this.
//Tells the control to cancel tracking related to the given event.
//告诉控件取消跟踪相关事件
- (void)cancelTrackingWithEvent:(nullable UIEvent *)event;   // event may be nil if cancelled for non-event reasons, e.g. removed from window

// add target/action for particular event. you can call this multiple times and you can specify multiple target/actions for a particular event.
// passing in nil as the target goes up the responder chain. The action may optionally include the sender and the event in that order
// the action cannot be NULL. Note that the target is not retained.
//为控件某个事件添加target,并在事件发生时执行action动作
- (void)addTarget:(nullable id)target action:(SEL)action forControlEvents:(UIControlEvents)controlEvents;

// remove the target/action for a set of events. pass in NULL for the action to remove all actions for that target
// 为控件某个事件移除target,以及事件发生时执行的action动作
- (void)removeTarget:(nullable id)target action:(nullable SEL)action forControlEvents:(UIControlEvents)controlEvents;

// get info about target & actions. this makes it possible to enumerate all target/actions by checking for each event kind
#if UIKIT_DEFINE_AS_PROPERTIES
//所有的target无序集合
@property(nonatomic,readonly) NSSet *allTargets;
//控件支持的所有事件数组
@property(nonatomic,readonly) UIControlEvents allControlEvents;                            // list of all events that have at least one action
#else
- (NSSet *)allTargets;                                                                     // set may include NSNull to indicate at least one nil target
- (UIControlEvents)allControlEvents;                                                       // list of all events that have at least one action
#endif
//控件指定事件的所有绑定target的action数组
- (nullable NSArray<NSString *> *)actionsForTarget:(nullable id)target forControlEvent:(UIControlEvents)controlEvent;    // single event. returns NSArray of NSString selector names. returns nil if none

// send the action. the first method is called for the event and is a point at which you can observe or override behavior. it is called repeately by the second.
//给定事件发生时给target发生action消息
- (void)sendAction:(SEL)action to:(nullable id)target forEvent:(nullable UIEvent *)event;
//Sends action messages for the given control events.
//给定事件发生时发生所欲的action消息
- (void)sendActionsForControlEvents:(UIControlEvents)controlEvents;                        // send all actions associated with events

@end

NS_ASSUME_NONNULL_END
