//
//  UIScrollView.h
//  UIKit
//
//  Copyright (c) 2007-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIRefreshControl.h>

NS_ASSUME_NONNULL_BEGIN

//滚动条的样式类型
typedef NS_ENUM(NSInteger, UIScrollViewIndicatorStyle) {
    //黑条白边,适用所有背景
    UIScrollViewIndicatorStyleDefault,     // black with white border. good against any background
    //小黑条,适用白色背景
    UIScrollViewIndicatorStyleBlack,       // black only. smaller. good against a white background
    //小白条,适用黑色背景
    UIScrollViewIndicatorStyleWhite        // white only. smaller. good against a black background
};
//The manner in which the keyboard is dismissed when a drag begins in the scroll view.
//在滚动视图中拖动开始时键盘被关闭的方式。
typedef NS_ENUM(NSInteger, UIScrollViewKeyboardDismissMode) {
    //The keyboard does not get dismissed with a drag.
    //在拖拽时键盘不会消失
    UIScrollViewKeyboardDismissModeNone,
    //The keyboard is dismissed when a drag begins.
    //在拖拽开始时键盘消失
    UIScrollViewKeyboardDismissModeOnDrag,      // dismisses the keyboard when a drag begins
    //The keyboard follows the dragging touch offscreen, and can be pulled upward again to cancel the dismiss.
    //键盘跟随拖动触摸屏幕，并可以再次向上拉取消键盘dismiss。
    UIScrollViewKeyboardDismissModeInteractive, // the keyboard follows the dragging touch off screen, and may be pulled upward again to cancel the dismiss
} NS_ENUM_AVAILABLE_IOS(7_0);

typedef NS_ENUM(NSInteger, UIScrollViewIndexDisplayMode) {
    UIScrollViewIndexDisplayModeAutomatic,    // the index will show or hide automatically as needed
    UIScrollViewIndexDisplayModeAlwaysHidden, // the index will never be displayed
} API_AVAILABLE(tvos(10.2));

//The default deceleration rate for a scroll view.
//滚动视图的默认减速率。
UIKIT_EXTERN const CGFloat UIScrollViewDecelerationRateNormal NS_AVAILABLE_IOS(3_0);
//A fast deceleration rate for a scroll view.
//滚动视图的快速减速率。
UIKIT_EXTERN const CGFloat UIScrollViewDecelerationRateFast NS_AVAILABLE_IOS(3_0);

@class UIEvent, UIImageView, UIPanGestureRecognizer, UIPinchGestureRecognizer;
@protocol UIScrollViewDelegate;

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIScrollView : UIView <NSCoding>
//内容的偏移位置。默认为（0，0），左上角原点。
@property(nonatomic)         CGPoint                      contentOffset;                  // default CGPointZero
//内容的大小
@property(nonatomic)         CGSize                       contentSize;                    // default CGSizeZero
//内容视图在scrollview中的位置，UIEdgeInsets描述一个矩形区域默认UIEdgeInsetsZero
@property(nonatomic)         UIEdgeInsets                 contentInset;                   // default UIEdgeInsetsZero. add additional scroll area around content
@property(nullable,nonatomic,weak) id<UIScrollViewDelegate>        delegate;                       // default nil. weak reference
//指定控件是否只能在一个方向上滚动,默认NO
@property(nonatomic,getter=isDirectionalLockEnabled) BOOL directionalLockEnabled;         // default NO. if YES, try to lock vertical or horizontal scrolling while dragging
//弹簧效果
@property(nonatomic)         BOOL                         bounces;                        // default YES. if YES, bounces past edge of content and back again
//垂直弹簧效果
@property(nonatomic)         BOOL                         alwaysBounceVertical;           // default NO. if YES and bounces is YES, even if content is smaller than bounds, allow drag vertically
//水平弹簧效果
@property(nonatomic)         BOOL                         alwaysBounceHorizontal;         // default NO. if YES and bounces is YES, even if content is smaller than bounds, allow drag horizontally
//分页效果
@property(nonatomic,getter=isPagingEnabled) BOOL          pagingEnabled __TVOS_PROHIBITED;// default NO. if YES, stop on multiples of view bounds
//是否可以滚动
@property(nonatomic,getter=isScrollEnabled) BOOL          scrollEnabled;                  // default YES. turn off any dragging temporarily
//在滑动时是否显示水平的轨迹条（默认是）
@property(nonatomic)         BOOL                         showsHorizontalScrollIndicator; // default YES. show indicator while we are tracking. fades out after tracking
//在滑动时是否显示垂直的轨迹条（默认是）
@property(nonatomic)         BOOL                         showsVerticalScrollIndicator;   // default YES. show indicator while we are tracking. fades out after tracking
//滚动条在滚动视图中的位置
@property(nonatomic)         UIEdgeInsets                 scrollIndicatorInsets;          // default is UIEdgeInsetsZero. adjust indicators inside of insets
//轨迹条的样式（默认UIScrollViewIndicatorStyleDefault）
@property(nonatomic)         UIScrollViewIndicatorStyle   indicatorStyle;                 // default is UIScrollViewIndicatorStyleDefault
//Your application can use the UIScrollViewDecelerationRateNormal and UIScrollViewDecelerationRateFast constants as reference points for reasonable deceleration rates.
//滑动速率,您的应用程序可以使用UIScrollViewDecelerationRateNormal和UIScrollViewDecelerationRateFast常量作为合理减速率的参考点。
@property(nonatomic)         CGFloat                      decelerationRate NS_AVAILABLE_IOS(3_0);
@property(nonatomic)         UIScrollViewIndexDisplayMode indexDisplayMode API_AVAILABLE(tvos(10.2));
//设置内容的偏移位置，带动画
- (void)setContentOffset:(CGPoint)contentOffset animated:(BOOL)animated;  // animate at constant velocity to new offset
- (void)scrollRectToVisible:(CGRect)rect animated:(BOOL)animated;         // scroll so rect is just visible (nearest edges). nothing if rect completely visible
//让滚动条闪动一次，从而提示用户该控件是可以滑动的
- (void)flashScrollIndicators;             // displays the scroll indicators for a short time. This should be done whenever you bring the scroll view to front.

/*
 Scrolling with no scroll bars is a bit complex. on touch down, we don't know if the user will want to scroll or track a subview like a control.
 on touch down, we start a timer and also look at any movement. if the time elapses without sufficient change in position, we start sending events to
 the hit view in the content subview. if the user then drags far enough, we switch back to dragging and cancel any tracking in the subview.
 the methods below are called by the scroll view and give subclasses override points to add in custom behaviour.
 you can remove the delay in delivery of touchesBegan:withEvent: to subviews by setting delaysContentTouches to NO.
 */
//用户已经触屏，但还拖动，返回YES。
@property(nonatomic,readonly,getter=isTracking)     BOOL tracking;        // returns YES if user has touched. may not yet have started dragging
//拖动中，返回YES。
@property(nonatomic,readonly,getter=isDragging)     BOOL dragging;        // returns YES if user has started scrolling. this may require some time and or distance to move to initiate dragging
//滑动中(用户不在拖动，但是仍在滑动)，返回YES
@property(nonatomic,readonly,getter=isDecelerating) BOOL decelerating;    // returns YES if user isn't dragging (touch up) but scroll view is still moving
//是否延迟调用touchesShouldBegin:withEvent:inContentView
@property(nonatomic) BOOL delaysContentTouches;       // default is YES. if NO, we immediately call -touchesShouldBegin:withEvent:inContentView:. this has no effect on presses
//默认是,如果为NO，我们保持触屏状态，移动手指，将不能拖动。
@property(nonatomic) BOOL canCancelContentTouches;    // default is YES. if NO, then once we start tracking, we don't try to drag if the touch moves. this has no effect on presses

// override points for subclasses to control delivery of touch events to subviews of the scroll view
// called before touches are delivered to a subview of the scroll view. if it returns NO the touches will not be delivered to the subview
// this has no effect on presses
// default returns YES
- (BOOL)touchesShouldBegin:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event inContentView:(UIView *)view;
// called before scrolling begins if touches have already been delivered to a subview of the scroll view. if it returns NO the touches will continue to be delivered to the subview and scrolling will not occur
// not called if canCancelContentTouches is NO. default returns YES if view isn't a UIControl
// this has no effect on presses
- (BOOL)touchesShouldCancelInContentView:(UIView *)view;

/*
 the following properties and methods are for zooming. as the user tracks with two fingers, we adjust the offset and the scale of the content. When the gesture ends, you should update the content
 as necessary. Note that the gesture can end and a finger could still be down. While the gesture is in progress, we do not send any tracking calls to the subview.
 the delegate must implement both viewForZoomingInScrollView: and scrollViewDidEndZooming:withView:atScale: in order for zooming to work and the max/min zoom scale must be different
 note that we are not scaling the actual scroll view but the 'content view' returned by the delegate. the delegate must return a subview, not the scroll view itself, from viewForZoomingInScrollview:
 */
//最小缩放比例
@property(nonatomic) CGFloat minimumZoomScale;     // default is 1.0
//最大缩放比例
@property(nonatomic) CGFloat maximumZoomScale;     // default is 1.0. must be > minimum zoom scale to enable zooming
//缩放比例
@property(nonatomic) CGFloat zoomScale NS_AVAILABLE_IOS(3_0);            // default is 1.0
- (void)setZoomScale:(CGFloat)scale animated:(BOOL)animated NS_AVAILABLE_IOS(3_0);
- (void)zoomToRect:(CGRect)rect animated:(BOOL)animated NS_AVAILABLE_IOS(3_0);
//缩放时候是否遇边界反弹
@property(nonatomic) BOOL  bouncesZoom;          // default is YES. if set, user can go past min/max zoom while gesturing and the zoom will animate to the min/max value at gesture end
//正在缩放
@property(nonatomic,readonly,getter=isZooming)       BOOL zooming;       // returns YES if user in zoom gesture
//正在缩放反弹
@property(nonatomic,readonly,getter=isZoomBouncing)  BOOL zoomBouncing;  // returns YES if we are in the middle of zooming back to the min/max value

// When the user taps the status bar, the scroll view beneath the touch which is closest to the status bar will be scrolled to top, but only if its `scrollsToTop` property is YES, its delegate does not return NO from `shouldScrollViewScrollToTop`, and it is not already at the top.
// On iPhone, we execute this gesture only if there's one on-screen scroll view with `scrollsToTop` == YES. If more than one is found, none will be scrolled.
//点击设备的状态栏时,scrollsToTop == YES的控件滚动返回至顶部。
/*
 所以要实现某一UIScrollView的实例点击设备状态栏返回顶部，则需要关闭其他的UIScrollView的实例的scrollsToTop属性为NO。很好理解：若多个scrollView响应返回顶部的事件，系统就不知道到底要将那个scrollView返回顶部了，因此也就不做任何操作了。。。
 */
@property(nonatomic) BOOL  scrollsToTop __TVOS_PROHIBITED;          // default is YES.

// Use these accessors to configure the scroll view's built-in gesture recognizers.
// Do not change the gestures' delegates or override the getters for these properties.

// Change `panGestureRecognizer.allowedTouchTypes` to limit scrolling to a particular set of touch types.
//拖动手势
@property(nonatomic, readonly) UIPanGestureRecognizer *panGestureRecognizer NS_AVAILABLE_IOS(5_0);
// `pinchGestureRecognizer` will return nil when zooming is disabled.
//捏合手势
@property(nullable, nonatomic, readonly) UIPinchGestureRecognizer *pinchGestureRecognizer NS_AVAILABLE_IOS(5_0);
// `directionalPressGestureRecognizer` is disabled by default, but can be enabled to perform scrolling in response to up / down / left / right arrow button presses directly, instead of scrolling indirectly in response to focus updates.
@property(nonatomic, readonly) UIGestureRecognizer *directionalPressGestureRecognizer UIKIT_AVAILABLE_TVOS_ONLY(9_0);
//设置键盘消失的方式
@property(nonatomic) UIScrollViewKeyboardDismissMode keyboardDismissMode NS_AVAILABLE_IOS(7_0); // default is UIScrollViewKeyboardDismissModeNone

@property (nonatomic, strong, nullable) UIRefreshControl *refreshControl NS_AVAILABLE_IOS(10_0) __TVOS_PROHIBITED;

@end

@protocol UIScrollViewDelegate<NSObject>

@optional
//只要滚动了就会触发
- (void)scrollViewDidScroll:(UIScrollView *)scrollView;                                               // any offset changes
//只要缩放了就会触发
- (void)scrollViewDidZoom:(UIScrollView *)scrollView NS_AVAILABLE_IOS(3_2); // any zoom scale changes

// called on start of dragging (may require some time and or distance to move)
//开始拖拽
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView;
// called on finger up if the user dragged. velocity is in points/millisecond. targetContentOffset may be changed to adjust where the scroll view comes to rest
//即将停止拖拽
- (void)scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset NS_AVAILABLE_IOS(5_0);
// called on finger up if the user dragged. decelerate is true if it will continue moving afterwards
//已经停止拖拽
- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate;
//将开始降速时
- (void)scrollViewWillBeginDecelerating:(UIScrollView *)scrollView;   // called on finger up as we are moving
//减速停止了时执行，
- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView;      // called when scroll view grinds to a halt
//只要停止滚动了就会触发
- (void)scrollViewDidEndScrollingAnimation:(UIScrollView *)scrollView; // called when setContentOffset/scrollRectVisible:animated: finishes. not called if not animating
//指定要缩放哪个视图
- (nullable UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView;     // return a view that will be scaled. if delegate returns nil, nothing happens
//即将开始缩放时
- (void)scrollViewWillBeginZooming:(UIScrollView *)scrollView withView:(nullable UIView *)view NS_AVAILABLE_IOS(3_2); // called before the scroll view begins zooming its content
//已经停止缩放时
- (void)scrollViewDidEndZooming:(UIScrollView *)scrollView withView:(nullable UIView *)view atScale:(CGFloat)scale; // scale between minimum and maximum. called after any 'bounce' animations
//scrollView是否可以滚动到top,如果未定义,默认为YES
- (BOOL)scrollViewShouldScrollToTop:(UIScrollView *)scrollView;   // return a yes if you want to scroll to the top. if not defined, assumes YES
//scrollView已经滚动到top后通知代理
- (void)scrollViewDidScrollToTop:(UIScrollView *)scrollView;      // called when scrolling animation finished. may be called immediately if already at top

@end

NS_ASSUME_NONNULL_END
