//
//  UIView.h
//  UIKit
//
//  Copyright (c) 2005-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIResponder.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIAppearance.h>
#import <UIKit/UIDynamicBehavior.h>
#import <UIKit/NSLayoutConstraint.h>
#import <UIKit/UITraitCollection.h>
#import <UIKit/UIFocus.h>

NS_ASSUME_NONNULL_BEGIN
//View设置动画块中的动画属性变化的曲线
typedef NS_ENUM(NSInteger, UIViewAnimationCurve) {
    //淡入淡出，开始时慢，由慢变快，中间最快，然后变慢
    UIViewAnimationCurveEaseInOut,         // slow at beginning and end
    //淡入，开始时慢然后越来越快
    UIViewAnimationCurveEaseIn,            // slow at beginning
    //淡出，开始快然后越来越慢
    UIViewAnimationCurveEaseOut,           // slow at end
    //线性匀速，开始和结束是一个速度
    UIViewAnimationCurveLinear,
};
//View内容填充模式,参考自:http://www.jianshu.com/p/8c784b59fe6a
/*
 枚举最前面三个属性是会拉伸(缩放)图片的,其余的属性是不会拉伸图片.
 同时可以总结出两点
 1.凡是带有scale单词的属性,图片都会被拉伸.
 2.凡是带有Ascept单词属性,图片会保持原来的宽高比,即图片不会变形.
 */
typedef NS_ENUM(NSInteger, UIViewContentMode) {
    //图片拉伸填充至整个UIImageView(图片可能会变形),这也是默认的属性,如果什么都不设置就是它在起作用
    UIViewContentModeScaleToFill,
    //图片拉伸至完全显示在UIImageView里面为止(图片不会变形)
    UIViewContentModeScaleAspectFit,      // contents scaled to fit with fixed aspect. remainder is transparent
    //图片拉伸至图片的的宽度或者高度等于UIImageView的宽度或者高度为止.看图片的宽高哪一边最接近UIImageView的宽高,一个属性相等后另一个就停止拉伸.
    UIViewContentModeScaleAspectFill,     // contents scaled to fill with fixed aspect. some portion of content may be clipped.
    //下面的属性都是不会拉伸图片的
    //调用setNeedsDisplay 方法时,就会重新渲染图片
    UIViewContentModeRedraw,              // redraw on bounds change (calls -setNeedsDisplay)
    //中间模式
    UIViewContentModeCenter,              // contents remain same size. positioned adjusted.
    //顶部
    UIViewContentModeTop,
    //底部
    UIViewContentModeBottom,
    //左边
    UIViewContentModeLeft,
    //右边
    UIViewContentModeRight,
    //左上
    UIViewContentModeTopLeft,
    //右上
    UIViewContentModeTopRight,
    //左下
    UIViewContentModeBottomLeft,
    //右下
    UIViewContentModeBottomRight,
};
//五种动画效果
typedef NS_ENUM(NSInteger, UIViewAnimationTransition) {
    UIViewAnimationTransitionNone,          //没有动画
    UIViewAnimationTransitionFlipFromLeft,  //从左向右旋转翻页
    UIViewAnimationTransitionFlipFromRight, //从右向左旋转翻页
    UIViewAnimationTransitionCurlUp,        //卷曲翻页，从下往上
    UIViewAnimationTransitionCurlDown,      //卷曲翻页 从上往下
};
//这些属性是为了自动调整子控件与父控件中间的位置，宽高
typedef NS_OPTIONS(NSUInteger, UIViewAutoresizing) {
    UIViewAutoresizingNone                 = 0,         //不自动调整
    UIViewAutoresizingFlexibleLeftMargin   = 1 << 0,    //自动调整与superView左边的距离，保证与superView左边的距离不变
    UIViewAutoresizingFlexibleWidth        = 1 << 1,    //自动调整自己的宽度，保证与superView左边和右边的距离不变
    UIViewAutoresizingFlexibleRightMargin  = 1 << 2,    //自动调整与superView的右边距离，保证与superView左边的距离不变
    UIViewAutoresizingFlexibleTopMargin    = 1 << 3,    //自动调整与superView顶部的距离，保证与superView底部的距离不变
    UIViewAutoresizingFlexibleHeight       = 1 << 4,    //自动调整自己的高度，保证与superView左边和右边的距离不变
    UIViewAutoresizingFlexibleBottomMargin = 1 << 5     //自动调整与superView底部的距离，保证与superView顶部的距离不变
};
//关于动画Option的一些可选项
typedef NS_OPTIONS(NSUInteger, UIViewAnimationOptions) {
    //提交动画的时候布局子控件，表示子控件将和父控件一同动画
    UIViewAnimationOptionLayoutSubviews            = 1 <<  0,
    //动画时允许用户交互，比如触摸
    UIViewAnimationOptionAllowUserInteraction      = 1 <<  1, // turn on user interaction while animating
    //从当前状态开始动画
    UIViewAnimationOptionBeginFromCurrentState     = 1 <<  2, // start all views from current value, not initial value
    //动画无限重复
    UIViewAnimationOptionRepeat                    = 1 <<  3, // repeat animation indefinitely
    //执行动画回路，前提是设置动画无限重复
    UIViewAnimationOptionAutoreverse               = 1 <<  4, // if repeat, run animation back and forth
    //忽略外层动画嵌套的执行时间
    UIViewAnimationOptionOverrideInheritedDuration = 1 <<  5, // ignore nested duration
    //忽略外层动画嵌套的时间变化曲线
    UIViewAnimationOptionOverrideInheritedCurve    = 1 <<  6, // ignore nested curve
    //通过改变属性和重回实现动画效果，如果key没有提交动画将使用快照
    UIViewAnimationOptionAllowAnimatedContent      = 1 <<  7, // animate contents (applies to transitions only)
    //用显隐的方式替代添加移除图层的动画效果
    UIViewAnimationOptionShowHideTransitionViews   = 1 <<  8, // flip to/from hidden state instead of adding/removing
    //忽略嵌套继承的选项
    UIViewAnimationOptionOverrideInheritedOptions  = 1 <<  9, // do not inherit any options or animation type
    
    //时间函数曲线相关
    //时间曲线函数，由慢到快
    UIViewAnimationOptionCurveEaseInOut            = 0 << 16, // default
    //时间曲线函数，由慢到特别快
    UIViewAnimationOptionCurveEaseIn               = 1 << 16,
    //时间曲线函数，由快到慢
    UIViewAnimationOptionCurveEaseOut              = 2 << 16,
    //时间曲线函数，匀速
    UIViewAnimationOptionCurveLinear               = 3 << 16,
    
    //转场动画相关的
    //无转场动画
    UIViewAnimationOptionTransitionNone            = 0 << 20, // default
    //转场从左翻转
    UIViewAnimationOptionTransitionFlipFromLeft    = 1 << 20,
    //转场从右翻转
    UIViewAnimationOptionTransitionFlipFromRight   = 2 << 20,
    //上卷转场
    UIViewAnimationOptionTransitionCurlUp          = 3 << 20,
    //下卷转场
    UIViewAnimationOptionTransitionCurlDown        = 4 << 20,
    //转场交叉消失
    UIViewAnimationOptionTransitionCrossDissolve   = 5 << 20,
    //转场从上翻转
    UIViewAnimationOptionTransitionFlipFromTop     = 6 << 20,
    //转场从下翻转
    UIViewAnimationOptionTransitionFlipFromBottom  = 7 << 20,
    
    //动画帧率
    //每秒默认的帧率
    UIViewAnimationOptionPreferredFramesPerSecondDefault     = 0 << 24,
    //60帧每秒
    UIViewAnimationOptionPreferredFramesPerSecond60          = 3 << 24,
    //30帧每秒
    UIViewAnimationOptionPreferredFramesPerSecond30          = 7 << 24,
    
} NS_ENUM_AVAILABLE_IOS(4_0);
//关键帧动画的选项参数设置
typedef NS_OPTIONS(NSUInteger, UIViewKeyframeAnimationOptions) {
    UIViewKeyframeAnimationOptionLayoutSubviews            = UIViewAnimationOptionLayoutSubviews,
    UIViewKeyframeAnimationOptionAllowUserInteraction      = UIViewAnimationOptionAllowUserInteraction, // turn on user interaction while animating
    UIViewKeyframeAnimationOptionBeginFromCurrentState     = UIViewAnimationOptionBeginFromCurrentState, // start all views from current value, not initial value
    UIViewKeyframeAnimationOptionRepeat                    = UIViewAnimationOptionRepeat, // repeat animation indefinitely
    UIViewKeyframeAnimationOptionAutoreverse               = UIViewAnimationOptionAutoreverse, // if repeat, run animation back and forth
    UIViewKeyframeAnimationOptionOverrideInheritedDuration = UIViewAnimationOptionOverrideInheritedDuration, // ignore nested duration
    UIViewKeyframeAnimationOptionOverrideInheritedOptions  = UIViewAnimationOptionOverrideInheritedOptions, // do not inherit any options or animation type
    //The option to use a simple linear calculation when interpolating between keyframe values.
    //线性插入每个新的keyframe values,默认值
    UIViewKeyframeAnimationOptionCalculationModeLinear     = 0 << 10, // default
    //The option to not interpolate between keyframe values, but rather to jump directly to each new keyframe value.
    //不插入keyframe values,而是直接跳到每一个新的keyframe value
    UIViewKeyframeAnimationOptionCalculationModeDiscrete   = 1 << 10,
    //The option to compute intermediate keyframe values using a simple pacing algorithm. This option results in an evenly paced animation.
    //使用pacing algorithm算法计算keyframe values的中间值,这个会让动画步调均衡
    UIViewKeyframeAnimationOptionCalculationModePaced      = 2 << 10,
    //The option to compute intermediate frames using a default Catmull-Rom spline that passes through the keyframe values. You cannot adjust the parameters of this algorithm.
    UIViewKeyframeAnimationOptionCalculationModeCubic      = 3 << 10,
    //The option to compute intermediate frames using the cubic scheme while ignoring the timing properties of the animation. Instead, timing parameters are calculated implicitly to give the animation a constant velocity.
    UIViewKeyframeAnimationOptionCalculationModeCubicPaced = 4 << 10
} NS_ENUM_AVAILABLE_IOS(7_0);

typedef NS_ENUM(NSUInteger, UISystemAnimation) {
    //当动画结束时,将视图从视图层级中移除
    UISystemAnimationDelete,    // removes the views from the hierarchy when complete
} NS_ENUM_AVAILABLE_IOS(7_0);
//tintColor属性相关的还有个tintAdjustmentMode属性，它是一个枚举值，定义了tint color的调整模式 参考自:http://www.cocoachina.com/ios/20150703/12363.html
typedef NS_ENUM(NSInteger, UIViewTintAdjustmentMode) {
    UIViewTintAdjustmentModeAutomatic,      //视图的着色调整模式与父视图一致
    
    UIViewTintAdjustmentModeNormal,         //视图的tintColor属性返回完全未修改的视图着色颜色
    UIViewTintAdjustmentModeDimmed,         //视图的tintColor属性返回一个去饱和度的、变暗的视图着色颜色
} NS_ENUM_AVAILABLE_IOS(7_0);
//判断试图是否会遵循显示的方向规则.对阿拉伯语等「从右向左」阅读的语言进行了支持。对不同的 Controller、Gesture甚至UIImage都可以选择显示的方向
typedef NS_ENUM(NSInteger, UISemanticContentAttribute) {
    UISemanticContentAttributeUnspecified = 0,
    UISemanticContentAttributePlayback, // for playback controls such as Play/RW/FF buttons and playhead scrubbers
    UISemanticContentAttributeSpatial, // for controls that result in some sort of directional change in the UI, e.g. a segmented control for text alignment or a D-pad in a game
    UISemanticContentAttributeForceLeftToRight,
    UISemanticContentAttributeForceRightToLeft
} NS_ENUM_AVAILABLE_IOS(9_0);
//坐标与坐标系之间的转换
@protocol UICoordinateSpace <NSObject>

- (CGPoint)convertPoint:(CGPoint)point toCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace NS_AVAILABLE_IOS(8_0);
- (CGPoint)convertPoint:(CGPoint)point fromCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace NS_AVAILABLE_IOS(8_0);
- (CGRect)convertRect:(CGRect)rect toCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace NS_AVAILABLE_IOS(8_0);
- (CGRect)convertRect:(CGRect)rect fromCoordinateSpace:(id <UICoordinateSpace>)coordinateSpace NS_AVAILABLE_IOS(8_0);

@property (readonly, nonatomic) CGRect bounds NS_AVAILABLE_IOS(8_0);

@end

@class UIBezierPath, UIEvent, UIWindow, UIViewController, UIColor, UIGestureRecognizer, UIMotionEffect, CALayer, UILayoutGuide;

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIView : UIResponder <NSCoding, UIAppearance, UIAppearanceContainer, UIDynamicItem, UITraitEnvironment, UICoordinateSpace, UIFocusItem, CALayerDelegate>

#if UIKIT_DEFINE_AS_PROPERTIES
//UIView有个layer属性，可以返回它的主CALayer实例，UIView有一个layerClass方法，返回主layer所使用的类，UIView的子类，可以通过重载这个方法，来让UIView使用不同的CALayer来显示。
@property(class, nonatomic, readonly) Class layerClass;                        // default is [CALayer class]. Used when creating the underlying layer for the view.
#else
+ (Class)layerClass;                        // default is [CALayer class]. Used when creating the underlying layer for the view.
#endif
//初始化View并设置frame大小
- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
//是否支持用户交互
@property(nonatomic,getter=isUserInteractionEnabled) BOOL userInteractionEnabled;  // default is YES. if set to NO, user events (touch, keys) are ignored and removed from the event queue.
//tag标签,默认值是0
@property(nonatomic)                                 NSInteger tag;                // default is 0
//view的layer属性,返回值总是非空值.view是layer的代理
@property(nonatomic,readonly,strong)                 CALayer  *layer;              // returns view's layer. Will always return a non-nil value. view is layer's delegate

#if UIKIT_DEFINE_AS_PROPERTIES
//YES if the view can become focused; NO otherwise.
@property(nonatomic,readonly) BOOL canBecomeFocused NS_AVAILABLE_IOS(9_0); // NO by default
#else
- (BOOL)canBecomeFocused NS_AVAILABLE_IOS(9_0); // NO by default
#endif
@property (readonly, nonatomic, getter=isFocused) BOOL focused NS_AVAILABLE_IOS(9_0);
//A semantic description of the view’s contents, used to determine whether the view should be flipped when switching between left-to-right and right-to-left layouts.
//对视图内容的语言描述,用于决定视图是否在左到右与右到左之间切换的时候快速翻转
@property (nonatomic) UISemanticContentAttribute semanticContentAttribute NS_AVAILABLE_IOS(9_0);

// This method returns the layout direction implied by the provided semantic content attribute relative to the application-wide layout direction (as returned by UIApplication.sharedApplication.userInterfaceLayoutDirection).
//这个方法返回被与application-wide(被UIApplication.sharedApplication.userInterfaceLayoutDirection返回的值)布局方向相关的语义内容参数实现的布局方向
+ (UIUserInterfaceLayoutDirection)userInterfaceLayoutDirectionForSemanticContentAttribute:(UISemanticContentAttribute)attribute NS_AVAILABLE_IOS(9_0);

// This method returns the layout direction implied by the provided semantic content attribute relative to the provided layout direction. For example, when provided a layout direction of RightToLeft and a semantic content attribute of Playback, this method returns LeftToRight. Layout and drawing code can use this method to determine how to arrange elements, but might find it easier to query the container view’s effectiveUserInterfaceLayoutDirection property instead.
// 这个返回被提供的布局方向的语义上下文实现的布局方向.例如,当提供了RightToLeft布局方向,语义上下文参数是Playback,那么这个方法返回LeftToRight.布局跟drawing代码可以使用这个方法去决定怎么安排元素,会发现使用内容视图的effectiveUserInterfaceLayoutDirection属性去查询更加容易
+ (UIUserInterfaceLayoutDirection)userInterfaceLayoutDirectionForSemanticContentAttribute:(UISemanticContentAttribute)semanticContentAttribute relativeToLayoutDirection:(UIUserInterfaceLayoutDirection)layoutDirection NS_AVAILABLE_IOS(10_0);

// Returns the user interface layout direction appropriate for arranging the immediate content of this view. Always consult the effectiveUserInterfaceLayoutDirection of the view whose immediate content is being arranged or drawn. Do not assume that the value propagates through the view’s subtree.
// 返回正在安排的视图内容的合适界面布局方向.总会查询立即内容被安排或被渲染的视图的effectiveUserInterfaceLayoutDirection.不要以为这个值通过视图层级传送
@property (readonly, nonatomic) UIUserInterfaceLayoutDirection effectiveUserInterfaceLayoutDirection NS_AVAILABLE_IOS(10_0);

@end

@interface UIView(UIViewGeometry)

// animatable. do not use frame if view is transformed since it will not correctly reflect the actual location of the view. use bounds + center instead.
// 是可以有动画效果的.在视图被转场时,不要使用frame,因为这是并不会正确的反应视图的实际位置.使用bounds跟center来代替
@property(nonatomic) CGRect            frame;

// use bounds/center and not frame if non-identity transform. if bounds dimension is odd, center may be have fractional part
// 使用bounds/center而不是frame如果使用的不是恒等式的转场动画.如果bounds尺寸很奇怪,center可能有小数部分
// 默认bounds是zero origin, frame size
@property(nonatomic) CGRect            bounds;      // default bounds is zero origin, frame size. animatable
// center是frame的中心
@property(nonatomic) CGPoint           center;      // center is center of frame. animatable
// 默认是CGAffineTransformIdentity
@property(nonatomic) CGAffineTransform transform;   // default is CGAffineTransformIdentity. animatable
// The scale factor used to draw the overlay’s content. (read-only)
// 用于渲染覆盖内容的缩放因子
@property(nonatomic) CGFloat           contentScaleFactor NS_AVAILABLE_IOS(4_0);
// 返回值决定是否支持多点触摸,默认是NO
@property(nonatomic,getter=isMultipleTouchEnabled) BOOL multipleTouchEnabled __TVOS_PROHIBITED;   // default is NO
// A Boolean value that indicates whether the receiver handles touch events exclusively.
// Setting this property to YES causes the receiver to block the delivery of touch events to other views in the same window. The default value of this property is NO
// 如果设置为YES则当前UIView会独占整个Touch事件。具体来说就是如果UIView设置了exclusiveTouch属性为YES则当这个UIView成为第一响应者时，在手指离开屏幕前其它view不会响应任何touch事件。
@property(nonatomic,getter=isExclusiveTouch) BOOL       exclusiveTouch __TVOS_PROHIBITED;         // default is NO

// 当在一个view上添加一个屏蔽罩，但又不影响对下面view的操作，也就是可以透过屏蔽罩对下面的view进行操作，这个函数就很好用了
/*
 -(UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event
 {
    UIView *hitView = [super hitTest:point withEvent:event];
    return hitView == self ? nil : hitView;
 }
 */
// 递归调用-pointInside:withEvent:.point是在接收者的坐标系中
- (nullable UIView *)hitTest:(CGPoint)point withEvent:(nullable UIEvent *)event;   // recursively calls -pointInside:withEvent:. point is in the receiver's coordinate system
// 这个函数的用处是判断当前的点击或者触摸事件的点是否在当前的view中
- (BOOL)pointInside:(CGPoint)point withEvent:(nullable UIEvent *)event;   // default returns YES if point is in bounds
// 转换一个点从接受者坐标系到给定视图坐标系
- (CGPoint)convertPoint:(CGPoint)point toView:(nullable UIView *)view;
// 把一个点从一个坐标系转换到接收者的坐标系
- (CGPoint)convertPoint:(CGPoint)point fromView:(nullable UIView *)view;
// 转换接收者坐标系中的矩形到其他视图
- (CGRect)convertRect:(CGRect)rect toView:(nullable UIView *)view;
// 转换一个矩形从其他视图坐标系到接收者坐标系
- (CGRect)convertRect:(CGRect)rect fromView:(nullable UIView *)view;
// A Boolean value that determines whether the receiver automatically resizes its subviews when its bounds change.
// When set to YES, the receiver adjusts the size of its subviews when its bounds change. The default value is YES.
// 如果某个视图的这个属性被设置为YES，则其子视图会根据autoresizingMask属性的值自动进行尺寸调整，简单配置一下视图的自动尺寸调整掩码常常就能使应用程序得到合适的行为。否则，应用程序就必须通过重载layoutSubviews方法来提供自己的实现
@property(nonatomic) BOOL               autoresizesSubviews; // default is YES. if set, subviews are adjusted according to their autoresizingMask if self.bounds changes
// An integer bit mask that determines how the receiver resizes itself when its superview’s bounds change.
// 枚举值
@property(nonatomic) UIViewAutoresizing autoresizingMask;    // simple resize. default is UIViewAutoresizingNone
// 这个方法会计算并且返回一个最适应接收子视图的大小.这个不是实际更改视图.默认是现有视图大小
- (CGSize)sizeThatFits:(CGSize)size;     // return 'best' size to fit given size. does not actually resize view. Default is return existing view size
// 当前view调用sizeThatFits:然后改变bounds大小
- (void)sizeToFit;                       // calls sizeThatFits: with current view bounds and changes bounds size.

@end

@interface UIView(UIViewHierarchy)
// 父视图
@property(nullable, nonatomic,readonly) UIView       *superview;
// 子视图数组
@property(nonatomic,readonly,copy) NSArray<__kindof UIView *> *subviews;
// The receiver’s window object, or nil if it has none. (read-only)
// 当前视图所在的window,如果这个视图没有添加到window上,那么就是nil
@property(nullable, nonatomic,readonly) UIWindow     *window;
// 从父视图中移除
- (void)removeFromSuperview;
// 在子视图数组中指定下标中插入一个子视图
- (void)insertSubview:(UIView *)view atIndex:(NSInteger)index;
// 在子视图数组中交换指定下标的视图位置
- (void)exchangeSubviewAtIndex:(NSInteger)index1 withSubviewAtIndex:(NSInteger)index2;
// 增加子视图，新添加的控件默认都是在subviews数组的后面，也就是默认显示在最上面
- (void)addSubview:(UIView *)view;
// 增加一个子视图，插入到siblingSubview的下面
- (void)insertSubview:(UIView *)view belowSubview:(UIView *)siblingSubview;
// 增加一个子视图，插入到siblingSubview的上面
- (void)insertSubview:(UIView *)view aboveSubview:(UIView *)siblingSubview;
// 将一个指定的视图拖动到最上面来显示
- (void)bringSubviewToFront:(UIView *)view;
//将一个指定的视图拖动到最下面来显示
- (void)sendSubviewToBack:(UIView *)view;
// Tells the view that a subview was added.
// The default implementation of this method does nothing. Subclasses can override it to perform additional actions when subviews are added. This method is called in response to adding a subview using any of the relevant view methods.
// 告诉视图:子视图已经添加.默认不执行任何操作，子类可以重写
- (void)didAddSubview:(UIView *)subview;
// Tells the view that a subview is about to be removed.
// The default implementation of this method does nothing. Subclasses can override it to perform additional actions whenever subviews are removed. This method is called when the subview’s superview changes or when the subview is removed from the view hierarchy completely.
//通知视图某个子视图即将被移除，默认不执行任何操作，子类可以重写
- (void)willRemoveSubview:(UIView *)subview;
// Tells the view that its superview is about to change to the specified superview.
// The default implementation of this method does nothing. Subclasses can override it to perform additional actions whenever the superview changes.
// 通知视图即将移动到新的父视图中
- (void)willMoveToSuperview:(nullable UIView *)newSuperview;
// Tells the view that its superview changed.
// The default implementation of this method does nothing. Subclasses can override it to perform additional actions whenever the superview changes.
// 通知已经移动到新的父视图
- (void)didMoveToSuperview;
// Tells the view that its window object is about to change.
// The default implementation of this method does nothing. Subclasses can override it to perform additional actions whenever the window changes.
// 通知即将移动到新的窗口
- (void)willMoveToWindow:(nullable UIWindow *)newWindow;
// Tells the view that its window object changed.
// The default implementation of this method does nothing. Subclasses can override it to perform additional actions whenever the window changes.
// The window property may be nil by the time that this method is called, indicating that the receiver does not currently reside in any window. This occurs when the receiver has just been removed from its superview or when the receiver has just been added to a superview that is not attached to a window. Overrides of this method may choose to ignore such cases if they are not of interest.
// 通知已经移动到新的窗口
- (void)didMoveToWindow;
// Returns a Boolean value indicating whether the receiver is a subview of a given view or identical to that view.
// YES if the receiver is an immediate or distant subview of view or if view is the receiver itself; otherwise NO.
//返回一个布尔值 判断某个视图是不是view的子控件或者子控件的子控件,或者控件自身
- (BOOL)isDescendantOfView:(UIView *)view;  // returns YES for self.
// 通过tag递归查找获得对应tag的子控件,包括自己
- (nullable __kindof UIView *)viewWithTag:(NSInteger)tag; // recursive search. includes self

// Allows you to perform layout before the drawing cycle happens. -layoutIfNeeded forces layout early
// Invalidates the layer’s layout and marks it as needing an update.
// 在调用-layoutIfNeeded对现在有布局有调整更改后，在开始绘制循环前使用这个方法进行更新
- (void)setNeedsLayout;
// Recalculate the receiver’s layout, if required.
// 如果有必要重新计算接收者的布局
- (void)layoutIfNeeded;
// The default implementation of this method does nothing on iOS 5.1 and earlier. Otherwise, the default implementation uses any constraints you have set to determine the size and position of any subviews.
// Subclasses can override this method as needed to perform more precise layout of their subviews. You should override this method only if the autoresizing and constraint-based behaviors of the subviews do not offer the behavior you want. You can use your implementation to set the frame rectangles of your subviews directly.
// You should not call this method directly. If you want to force a layout update, call the setNeedsLayout method instead to do so prior to the next drawing update. If you want to update the layout of your views immediately, call the layoutIfNeeded method.
// 一般写在view内部，当控件的大小约束发生变化的时候在这里重写布局子控件的位置和尺寸，一般在这个方法里面或者视图的frame是最准确的
// 被layoutIfNeeded自动调用.在iOS 6.0上基于约束的布局使用基于约束的布局来实现,不然就什么都不做
- (void)layoutSubviews;    // override point. called by layoutIfNeeded automatically. As of iOS 6.0, when constraints-based layout is used the base implementation applies the constraints-based layout, otherwise it does nothing.

/*
 -layoutMargins returns a set of insets from the edge of the view's bounds that denote a default spacing for laying out content.
 If preservesSuperviewLayoutMargins is YES, margins cascade down the view tree, adjusting for geometry offsets, so that setting the left value of layoutMargins on a superview will affect the left value of layoutMargins for subviews positioned close to the left edge of their superview's bounds
 If your view subclass uses layoutMargins in its layout or drawing, override -layoutMarginsDidChange in order to refresh your view if the margins change.
 */
// The default spacing to use when laying out content in the view.
/*
 Use this property so specify the desired amount of space (measured in points) between the edge of the view and any subviews. Auto layout uses your margins as a cue for placing content. For example, if you specify a set of horizontal constraints using the format string “|-[subview]-|”, the left and right edges of the subview are inset from the edge of the superview by the corresponding layout margins. When the edge of your view is close to the edge of the superview and the preservesSuperviewLayoutMargins property is YES, the actual layout margins may be increased to prevent content from overlapping the superview’s margins.
 
 The default margins are eight points on each side.
 
 If the view is a view controller’s root view, then the system sets and manages the margins. The top and bottom margins are set to zero points. The side margins vary depending on the current size class, but can be either 16 or 20 points. You cannot change these margins.
 */
/*
 使用这个属性去指明想要的视图与任意子视图之间的间隙(以点来计算).Auto layout使用margins作为代替内容的方式.例如,如果指明使用“|-[subview]-|”字符串格式的水平约束集合,那么子视图左右边距是从父视图中相关的布局约束插入的.当你的视图边距跟父视图的边距是靠近的,而且preservesSuperviewLayoutMargins的值是YES,那么实际的布局约束可以增加去防止父视图margins重叠
 默认的margins每条边是8个点
 如果视图是控制器的根视图,那么系统会设置并管理这些margins.顶部与底部的margins值为0.两边的margins的值根据当前size class变化,可能是16或20个点.开发者不能更改这些值
 */
@property (nonatomic) UIEdgeInsets layoutMargins NS_AVAILABLE_IOS(8_0);
// A Boolean value indicating whether the current view also respects the margins of its superview.
// 一个BOOL值表明当前视图是否遵循父控件的margins.默认是NO,如果把它设为YES，layoutMargins会根据屏幕中相关view的布局而改变。
@property (nonatomic) BOOL preservesSuperviewLayoutMargins NS_AVAILABLE_IOS(8_0); // default is NO - set to enable pass-through or cascading behavior of margins from this view’s parent to its children
// 在我们改变view的layoutMargins这个属性时，会触发这个方法，我们在自己的view里面可以重写这个方法来捕获layoutMargins的变化。在大多数情况下，我们可以在这个方法里面触发drawing和layout的update。
- (void)layoutMarginsDidChange NS_AVAILABLE_IOS(8_0);

/* The edges of this guide are constrained to equal the edges of the view inset by the layoutMargins
 */
// A layout guide representing the view’s margins. (read-only)
// Use this layout guide’s anchors to create constraints with the view’s margin.
/*
 反应视图margins的布局指引
 使用布局指引锚点来使用视图的margin创建约束
 */
@property(readonly,strong) UILayoutGuide *layoutMarginsGuide NS_AVAILABLE_IOS(9_0);

/// This content guide provides a layout area that you can use to place text and related content whose width should generally be constrained to a size that is easy for the user to read. This guide provides a centered region that you can place content within to get this behavior for this view.
// A layout guide representing an area with a readable width within the view. (read-only)
@property (nonatomic, readonly, strong) UILayoutGuide *readableContentGuide  NS_AVAILABLE_IOS(9_0);
@end

@interface UIView(UIViewRendering)
// Draws the receiver’s image within the passed-in rectangle.
// rect: The portion of the view’s bounds that needs to be updated. The first time your view is drawn, this rectangle is typically the entire visible bounds of your view. However, during subsequent drawing operations, the rectangle may specify only part of your view.
// The default implementation of this method does nothing. Subclasses that use technologies such as Core Graphics and UIKit to draw their view’s content should override this method and implement their drawing code there. You do not need to override this method if your view sets its content in other ways. For example, you do not need to override this method if your view just displays a background color or if your view sets its content directly using the underlying layer object.
// 如果我们想要在一个UIView中绘图，需要写一个扩展UIView的类，并重写drawRect方法，在这里进行绘图操作。这个方法不能直接调用。苹果要求我们调用UIView类中的setNeedsDisplay方法，则程序会自动调用drawRect方法进行重绘(调用setNeedsDisplay会自动调用drawRect）
- (void)drawRect:(CGRect)rect;
// Marks the layer’s contents as needing to be updated.
// Calling this method causes the layer to recache its content. This results in the layer potentially calling either the displayLayer: or drawLayer:inContext: method of its delegate. The existing content in the layer’s contents property is removed to make way for the new content.
// 表示视图图层将需要更新
// 调用这个方法将让图层刷新内容.这个将导致图层潜在的调用它的代理的displayLayer:或drawLayer:inContext:方法.(图层的代理是视图).已经存在的图层内容属性将被移除来给新内容腾出空间
- (void)setNeedsDisplay;
// Marks the region within the specified rectangle as needing to be updated.
// 同上，直接调用setNeedsDisplay，或者setNeedsDisplayInRect触发drawRect，但是有个前提条件是rect不能为0
- (void)setNeedsDisplayInRect:(CGRect)rect;
// A Boolean value that determines whether subviews are confined to the bounds of the view.
// This property is inherited from the UIView parent class. This class changes the default value of this property to YES.
// 当时YES的时候，如果子视图的范围超出了父视图的边界，那么超出的部分就会被裁剪掉。
@property(nonatomic)                 BOOL              clipsToBounds;              // When YES, content and subviews are clipped to the bounds of the view. Default is NO.
// 背景颜色
@property(nullable, nonatomic,copy)            UIColor          *backgroundColor UI_APPEARANCE_SELECTOR; // default is nil. Can be useful with the appearance proxy on custom UIView subclasses.
// 透明度
@property(nonatomic)                 CGFloat           alpha;                      // animatable. default is 1.0
// A Boolean value indicating whether the layer contains completely opaque content.
// 指明图层中内容是否全部是不透明的
// 不透明.默认是YES.不透明视图必须填充整个bounds或者结果是未定义的.在drawRect:中激活的CGContext将不会被清除,并可能有非零像素.
@property(nonatomic,getter=isOpaque) BOOL              opaque;                     // default is YES. opaque views must fill their entire bounds or the results are undefined. the active CGContext in drawRect: will not have been cleared and may have non-zeroed pixels
// A Boolean value that determines whether the view’s bounds should be automatically cleared before drawing.
// 决定视图bounds是否在重绘前自动清空
// 默认值是YES.不透明视图将忽略这个.透明视图将在drawRect:中激活的CGContext去预填充透明的像素
@property(nonatomic)                 BOOL              clearsContextBeforeDrawing; // default is YES. ignored for opaque views. for non-opaque views causes the active CGContext in drawRect: to be pre-filled with transparent pixels
// A Boolean indicating whether the layer is displayed. Animatable.
// 可以有动画效果.指明图层是否展示
@property(nonatomic,getter=isHidden) BOOL              hidden;                     // default is NO. doesn't check superviews
// A flag used to determine how a view lays out its content when its bounds change.
// 内容显示的模式.决定视图bounds改变时,视图如何布局它的内容.默认值是UIViewContentModeScaleToFill
@property(nonatomic)                 UIViewContentMode contentMode;                // default is UIViewContentModeScaleToFill
//iOS 6被遗弃,使用-[UIImage resizableImageWithCapInsets:]来取得相同的结果
/*
 图片的拉伸操作,例如
 imageView.image = [UIImage imageNamed:@"image.png"];
 [imageView setContentStretch:CGRectMake(150.0/300.0,75.0/150.0,10.0/300.0,10.0/150.0)];
 image.png的大小是 210.0  x  126.0；
 imageView的frame是（9，117，300，150）；
 150.0/300.0表示x轴上，前150个像素不进行拉伸。
 75.0/150.0表示y轴上，前75个像素不进行拉伸。
 10.0/300.0表示x轴上150后的10个像素（151-160）进行拉伸，直到image.png铺满imageView。
 10.0/150.0表示y轴上75后的10个（76-85）像素进行拉伸，直到image.png铺满imageView。
 */
@property(nonatomic)                 CGRect            contentStretch NS_DEPRECATED_IOS(3_0,6_0) __TVOS_PROHIBITED; // animatable. default is unit rectangle {{0,0} {1,1}}. Now deprecated: please use -[UIImage resizableImageWithCapInsets:] to achieve the same effect.
// An optional view whose alpha channel is used to mask a view’s content.
// The view’s alpha channel determines how much of the view’s content and background shows through. Fully or partially opaque pixels allow the underlying content to show through but fully transparent pixels block that content.
// 一个通过alpha通道来掩盖一个view的内容的可选view
// 阿尔法通道(Alpha Channel) 阿尔法通道是一个8位的灰度通道，该通道用256级灰度来记录图像中的透明度信息，定义透明、不透明和半透明区域，其中黑表示透明，白表示不透明，灰表示半透明。
// mask加深理解:投影，只会显示影子
// 蒙板view
@property(nullable, nonatomic,strong)          UIView           *maskView NS_AVAILABLE_IOS(8_0);

/*
 -tintColor always returns a color. The color returned is the first non-default value in the receiver's superview chain (starting with itself).
 If no non-default value is found, a system-defined color is returned.
 If this view's -tintAdjustmentMode returns Dimmed, then the color that is returned for -tintColor will automatically be dimmed.
 If your view subclass uses tintColor in its rendering, override -tintColorDidChange in order to refresh the rendering if the color changes.
 */
/*
 -tintColor总会返回一个颜色.这个被返回的颜色是第一个接收者父视图链中非空的值(从自己开始).如果没找到非空值,那么一个系统定义的颜色将被返回.如果-tintAdjustmentMode返回Dimmed.那么这个返回的颜色将自动无效,如果你的视图子类在它的渲染中使用了tintColor,那么重写-tintColorDidChange在这个颜色改变的时候去刷新渲染
 */
// 这个属性使用是改变应用程序的外观的。默认tintColor的值为nil，这表示它将会运用父视图层次的颜色来进行着色。如果父视图中没有设置tintColor，那么默认系统就会使用蓝色。因此，可以通过root view controller的tintColor来改变系统整体的颜色。
@property(null_resettable, nonatomic, strong) UIColor *tintColor NS_AVAILABLE_IOS(7_0);

/*
 -tintAdjustmentMode always returns either UIViewTintAdjustmentModeNormal or UIViewTintAdjustmentModeDimmed. The value returned is the first non-default value in the receiver's superview chain (starting with itself).
 If no non-default value is found, UIViewTintAdjustmentModeNormal is returned.
 When tintAdjustmentMode has a value of UIViewTintAdjustmentModeDimmed for a view, the color it returns from tintColor will be modified to give a dimmed appearance.
 When the tintAdjustmentMode of a view changes (either the view's value changing or by one of its superview's values changing), -tintColorDidChange will be called to allow the view to refresh its rendering.
 */
// The first non-default tint adjustment mode value in the view’s hierarchy, ascending from and starting with the view itself.
/*
 When this property’s value is UIViewTintAdjustmentModeDimmed, the value of the tintColor property is modified to provide a dimmed appearance.
 
 If the system cannot find a non-default value in the subview hierarchy when you query this property, the value is UIViewTintAdjustmentModeNormal.
 
 When this property’s value changes (either by the view’s value changing or by one of its superview’s values changing), -the system calls the tintColorDidChange method to allow the view to refresh its rendering.
 */
// 枚举,渲染颜色模式
@property(nonatomic) UIViewTintAdjustmentMode tintAdjustmentMode NS_AVAILABLE_IOS(7_0);

/*
 The -tintColorDidChange message is sent to appropriate subviews of a view when its tintColor is changed by client code or to subviews in the view hierarchy of a view whose tintColor is implicitly changed when its superview or tintAdjustmentMode changes.
 */
// Called by the system when the tintColor property changes.
// tintColor变化的时候调用
- (void)tintColorDidChange NS_AVAILABLE_IOS(7_0);

@end

@interface UIView(UIViewAnimation)
// Marks the beginning of a begin/commit animation block.
// animationID:An application-supplied identifier for the animations.
// context:Custom data that you want to associate with this set of animations. information that is passed to the animation delegate messages—the selectors set using the setAnimationWillStartSelector: and setAnimationDidStopSelector: methods.
// This method signals to the system that you want to specify one or more animations to perform. After calling this method, configure the animation options (using the setAnimation… class methods) and then change the desired animatable properties of your views. When you are done changing your view properties, call the commitAnimations method to close the set and schedule the animations.
// 开始动画
+ (void)beginAnimations:(nullable NSString *)animationID context:(nullable void *)context;  // additional context info passed to will start/did stop selectors. begin/commit can be nested(嵌套)
// 提交动画
+ (void)commitAnimations;                                                 // starts up any animations when the top level animation is commited

// no getters. if called outside animation block, these setters have no effect.
// 设置动画代理,如果在动画block外面调用,将无效,没有getter方法
+ (void)setAnimationDelegate:(nullable id)delegate;                          // default = nil
// Sets the message to send to the animation delegate when the animation starts.
// If you specify an animation delegate for a begin/commit set of animations, you use this method to specify the selector to call before the animations begin. This method does nothing if called from outside of an animation block. It must be called between calls to the beginAnimations:context: and commitAnimations methods. This selector is set to NULL by default.
// 给代理发送动画将要开始的时候执行的方法(必须要先设置动画代理)
+ (void)setAnimationWillStartSelector:(nullable SEL)selector;                // default = NULL. -animationWillStart:(NSString *)animationID context:(void *)context
// Sets the message to send to the animation delegate when animation stops.
// 给代理发送动画已经结束的时候执行的方法(必须要先设置动画代理)
+ (void)setAnimationDidStopSelector:(nullable SEL)selector;                  // default = NULL. -animationDidStop:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context
// Sets the animation duration used by all animations within this transaction group.
// 设置动画时长
+ (void)setAnimationDuration:(NSTimeInterval)duration;              // default = 0.2
// Sets the amount of time (in seconds) to wait before animating property changes within an animation block.
// 设置动画延迟执行时间
+ (void)setAnimationDelay:(NSTimeInterval)delay;                    // default = 0.0
// Sets the start time for the current animation block.
// 设置当前动画block开始的时间
+ (void)setAnimationStartDate:(NSDate *)startDate;                  // default = now ([NSDate date])
// Sets the curve to use when animating property changes within an animation block.
// 设置动画曲线,默认是UIViewAnimationCurveEaseInOut(淡入淡出，开始时慢，由慢变快，中间最快，然后变慢)
+ (void)setAnimationCurve:(UIViewAnimationCurve)curve;              // default = UIViewAnimationCurveEaseInOut
// 设置动画的重复播放次数,可以是分数
+ (void)setAnimationRepeatCount:(float)repeatCount;                 // default = 0.0.  May be fractional
// Sets whether the animations within an animation block automatically reverse themselves.
// 设置是否自动翻转当前的动画效果
// 如果设置为YES,代表动画每次重复执行的效果会跟上一次相反
+ (void)setAnimationRepeatAutoreverses:(BOOL)repeatAutoreverses;    // default = NO. used if repeat count is non-zero
// Sets whether the animation should begin playing from the current state.
// 设置动画是否从当前状态开始播放
// YES如果动画需要从他们当前状态开始播放。否则为NO。如果设置为YES那么当动画在运行过程中，当前视图的位置将会作为新的动画的开始状态。如果设置为NO，当前动画结束前新动画将使用视图最後状态的位置作为开始状态。这个方法将不会做任何事情如果动画没有运行或者没有在动画块外调用。使用beginAnimations:context:类方法来开始并用commitAnimations类方法来结束动画块。默认值是NO。
+ (void)setAnimationBeginsFromCurrentState:(BOOL)fromCurrentState;  // default = NO. If YES, the current view position is always used for new animations -- allowing animations to "pile up" on each other. Otherwise, the last end state is used for the animation (the default).
// Sets a transition to apply to a view during an animation block.
// 枚举值,在动画块中为视图设置过渡
/*
 typedef enum {
     UIViewAnimationTransitionNone,
     UIViewAnimationTransitionFlipFromLeft,
     UIViewAnimationTransitionFlipFromRight,
     UIViewAnimationTransitionCurlUp,
     UIViewAnimationTransitionCurlDown,
 } UIViewAnimationTransition;
 */
+ (void)setAnimationTransition:(UIViewAnimationTransition)transition forView:(UIView *)view cache:(BOOL)cache;  // current limitation - only one per begin/commit block
// Sets whether animations are enabled.
// 设置动画是否可执行
+ (void)setAnimationsEnabled:(BOOL)enabled;                         // ignore any attribute changes while set.
#if UIKIT_DEFINE_AS_PROPERTIES
@property(class, nonatomic, readonly) BOOL areAnimationsEnabled;    //动画是否可执行
#else
+ (BOOL)areAnimationsEnabled;   //返回动画是否可执行
#endif
// Disables a view transition animation.
// actionsWithoutAnimation: The view transition code that you want to perform without animation.
// 让视图过度动画失效
// 阻塞动画,一个小但非常有用的新方法[UIView performWithoutAnimation:]。它是一个简单的封装，先检查动画当前是否启用，然后禁止动画，执行块语句，最后重新启用动画。一个需要说明的地方是，它并不会阻塞基于CoreAnimation的动画。
+ (void)performWithoutAnimation:(void (NS_NOESCAPE ^)(void))actionsWithoutAnimation NS_AVAILABLE_IOS(7_0);

#if UIKIT_DEFINE_AS_PROPERTIES
@property(class, nonatomic, readonly) NSTimeInterval inheritedAnimationDuration NS_AVAILABLE_IOS(9_0);
#else
// Returns the inherited duration of the current animation.
// This method only returns a non-zero value if called within a UIView animation block.
// 获得所镶嵌的动画的持续时间
+ (NSTimeInterval)inheritedAnimationDuration NS_AVAILABLE_IOS(9_0);
#endif

@end

@interface UIView(UIViewAnimationWithBlocks)

/**
 @param duration 动画的持续时间
 @param delay 动画延迟delay秒后开始
 @param options 动画的节奏控制
 @param animations 将改变视图属性的代码放在这个block中
 @param completion 动画结束后，会自动调用这个block
 */
+ (void)animateWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay options:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(4_0);

/**
 @param duration 动画的持续时间
 @param animations 将改变视图属性的代码放在这个block中
 @param completion 动画结束后，会自动调用这个block
 */
+ (void)animateWithDuration:(NSTimeInterval)duration animations:(void (^)(void))animations completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(4_0); // delay = 0.0, options = 0

/**
 @param duration 动画的持续时间
 @param animations 将改变视图属性的代码放在这个block中
 */
+ (void)animateWithDuration:(NSTimeInterval)duration animations:(void (^)(void))animations NS_AVAILABLE_IOS(4_0); // delay = 0.0, options = 0, completion = NULL

/* Performs `animations` using a timing curve described by the motion of a spring. When `dampingRatio` is 1, the animation will smoothly decelerate to its final model values without oscillating. Damping ratios less than 1 will oscillate more and more before coming to a complete stop. You can use the initial spring velocity to specify how fast the object at the end of the simulated spring was moving before it was attached. It's a unit coordinate system, where 1 is defined as travelling the total animation distance in a second. So if you're changing an object's position by 200pt in this animation, and you want the animation to behave as if the object was moving at 100pt/s before the animation started, you'd pass 0.5. You'll typically want to pass 0 for the velocity. */
/**
 @param duration 动画的持续时间
 @param delay 动画延迟delay秒后开始
 @param dampingRatio usingSpringWithDamping 的范围为 0.0f 到 1.0f，数值越小「弹簧」的振动效果越明显.
 @param velocity initialSpringVelocity则表示初始的速度，数值越大一开始移动越快。值得注意的是，初始速度取值较高而时间较短时，也会出现反弹情况。
 @param options 动画的节奏控制
 @param animations 将改变视图属性的代码放在这个block中
 @param completion 动画结束后，会自动调用这个block
 */
+ (void)animateWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay usingSpringWithDamping:(CGFloat)dampingRatio initialSpringVelocity:(CGFloat)velocity options:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(7_0);

/**
 @param view 需要进行转场动画的视图
 @param duration 动画的持续时间
 @param options 转场动画的类型
 @param animations 将改变视图属性的代码放在这个block中
 @param completion 动画结束后，会自动调用这个block
 */
+ (void)transitionWithView:(UIView *)view duration:(NSTimeInterval)duration options:(UIViewAnimationOptions)options animations:(void (^ __nullable)(void))animations completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(4_0);

/**
 @param fromView 转场开始的视图.默认情况下,这个视图会从它的父控件中移除作为转场动画的一部分
 @param toView 转场结束的视图.默认情况下,这个视图会从它的父控件中移除作为转场动画的一部分
 @param duration 动画的持续时间
 @param options 转场动画的类型
 @param completion 动画结束后，会自动调用这个block
 */
+ (void)transitionFromView:(UIView *)fromView toView:(UIView *)toView duration:(NSTimeInterval)duration options:(UIViewAnimationOptions)options completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(4_0); // toView added to fromView.superview, fromView removed from its superview

/* Performs the requested system-provided animation on one or more views. Specify addtional animations in the parallelAnimations block. These additional animations will run alongside the system animation with the same timing and duration that the system animation defines/inherits. Additional animations should not modify properties of the view on which the system animation is being performed. Not all system animations honor all available options.
 */
/**
 @param animation 系统动画
 @param views 需要进动画的视图 (数组，可以作用于多个视图)。
 @param options 转场动画的类型
 @param parallelAnimations 将改变视图属性的代码放在这个block中
 @param completion 动画结束后，会自动调用这个block
 */
+ (void)performSystemAnimation:(UISystemAnimation)animation onViews:(NSArray<__kindof UIView *> *)views options:(UIViewAnimationOptions)options animations:(void (^ __nullable)(void))parallelAnimations completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(7_0);

@end

@interface UIView (UIViewKeyframeAnimations)

/**
 关键帧动画:
 UIView动画已经具备高级的方法来创建动画，而且可以更好地理解和构建动画。IOS7以后苹果新加了一个
 animateKeyframesWithDuration的方法，我们可以使用它来创建更多更复杂更酷炫的动画效果，而不需要去使用到核心动画（CoreAnimatino）
 
 @param duration 动画时长
 @param delay 动画延迟
 @param options 动画效果选项
 @param animations 动画执行代码
 @param completion 动画结束执行代码
 */
+ (void)animateKeyframesWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay options:(UIViewKeyframeAnimationOptions)options animations:(void (^)(void))animations completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(7_0);
/**
 添加关键帧

 @param frameStartTime 动画相对开始时间
 @param frameDuration 动画相对持续时间
 @param animations 动画执行代码
 */
+ (void)addKeyframeWithRelativeStartTime:(double)frameStartTime relativeDuration:(double)frameDuration animations:(void (^)(void))animations NS_AVAILABLE_IOS(7_0); // start time and duration are values between 0.0 and 1.0 specifying time and duration relative to the overall time of the keyframe animation

@end

@interface UIView (UIViewGestureRecognizers)
// The system-supplied gesture recognizers for presenting a document interaction controller. (read-only)
// 系统提供的支持文档交互控制器的手势
@property(nullable, nonatomic,copy) NSArray<__kindof UIGestureRecognizer *> *gestureRecognizers NS_AVAILABLE_IOS(3_2);
//Attaches a gesture recognizer to the view.
//添加手势到视图上
- (void)addGestureRecognizer:(UIGestureRecognizer*)gestureRecognizer NS_AVAILABLE_IOS(3_2);
//从视图上移除手势
- (void)removeGestureRecognizer:(UIGestureRecognizer*)gestureRecognizer NS_AVAILABLE_IOS(3_2);

// called when the recognizer attempts to transition out of UIGestureRecognizerStatePossible if a touch hit-tested to this view will be cancelled as a result of gesture recognition
// returns YES by default. return NO to cause the gesture recognizer to transition to UIGestureRecognizerStateFailed
// subclasses may override to prevent recognition of particular gestures. for example, UISlider prevents swipes parallel to the slider that start in the thumb
//Asks the delegate if a gesture recognizer should begin interpreting touches.
//询问代理一个手势是否一个开始解释触摸事件
- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer NS_AVAILABLE_IOS(6_0);

@end

@interface UIView (UIViewMotionEffects)

/*! Begins applying `effect` to the receiver. The effect's emitted keyPath/value pairs will be
 applied to the view's presentation layer.
 
 Animates the transition to the motion effect's values using the present UIView animation
 context. */
//Begins applying a motion effect to the view.
//添加一个motion事件到视图上
- (void)addMotionEffect:(UIMotionEffect *)effect NS_AVAILABLE_IOS(7_0);

/*! Stops applying `effect` to the receiver. Any affected presentation values will animate to
 their post-removal values using the present UIView animation context. */
//Stops applying a motion effect to the view.
//停止视图上motion事件
- (void)removeMotionEffect:(UIMotionEffect *)effect NS_AVAILABLE_IOS(7_0);
//An array of motion effect objects to apply as a group to the view.
//视图上的motion事件数组
@property (copy, nonatomic) NSArray<__kindof UIMotionEffect *> *motionEffects NS_AVAILABLE_IOS(7_0);

@end


//
// UIView Constraint-based Layout Support
//

typedef NS_ENUM(NSInteger, UILayoutConstraintAxis) {
    UILayoutConstraintAxisHorizontal = 0,
    UILayoutConstraintAxisVertical = 1
};

// Installing Constraints

/* A constraint is typically installed on the closest common ancestor of the views involved in the constraint.
 It is required that a constraint be installed on _a_ common ancestor of every view involved.  The numbers in a constraint are interpreted in the coordinate system of the view it is installed on.  A view is considered to be an ancestor of itself.
 */
@interface UIView (UIConstraintBasedLayoutInstallingConstraints)
//A list of constraints affecting the node’s transformation.
//当前view中所有的constraints
@property(nonatomic,readonly) NSArray<__kindof NSLayoutConstraint *> *constraints NS_AVAILABLE_IOS(6_0);
//添加单个constraint
- (void)addConstraint:(NSLayoutConstraint *)constraint NS_AVAILABLE_IOS(6_0); // This method will be deprecated in a future release and should be avoided.  Instead, set NSLayoutConstraint's active property to YES.
//添加一组constraint
- (void)addConstraints:(NSArray<__kindof NSLayoutConstraint *> *)constraints NS_AVAILABLE_IOS(6_0); // This method will be deprecated in a future release and should be avoided.  Instead use +[NSLayoutConstraint activateConstraints:].
//移除单个constraint
- (void)removeConstraint:(NSLayoutConstraint *)constraint NS_AVAILABLE_IOS(6_0); // This method will be deprecated in a future release and should be avoided.  Instead set NSLayoutConstraint's active property to NO.
//移除一组constraint
- (void)removeConstraints:(NSArray<__kindof NSLayoutConstraint *> *)constraints NS_AVAILABLE_IOS(6_0); // This method will be deprecated in a future release and should be avoided.  Instead use +[NSLayoutConstraint deactivateConstraints:].
@end

// Core Layout Methods

/* To render a window, the following passes will occur, if necessary.
 
 update constraints
 layout
 display
 
 Please see the conceptual documentation for a discussion of these methods.
 */
/*
 autoLayout的布局过程是
    update constraints（uodateContraints）->layout subviews(layoutSubviews)->display(drawRect)
    这三步不是单向的，如果layout的过程中改变了constraint，就会触发update constraints，进行新的一轮迭代。我们在实际代码中，应该避免在此造成死循环 
 */
@interface UIView (UIConstraintBasedLayoutCoreMethods)
//我们可以调用这个方法触发update Constraints的操作。在neneedsUpdateContraints返回YES时，才能成功触发update Contraints的操作。我们不应该重写这个方法。
- (void)updateConstraintsIfNeeded NS_AVAILABLE_IOS(6_0); // Updates the constraints from the bottom up for the view hierarchy rooted at the receiver. UIWindow's implementation creates a layout engine if necessary first.
//自定义view时，我们应该重写这个方法来设置当前view布局的布局约束，重写这个方法时一定要调用[super updateContraints]
- (void)updateConstraints NS_AVAILABLE_IOS(6_0) NS_REQUIRES_SUPER; // Override this to adjust your special constraints during a constraints update pass
//布局系统使用这个返回值来确定是否调用updateContraints
- (BOOL)needsUpdateConstraints NS_AVAILABLE_IOS(6_0);
//当一个自定义的view某一个属性的改变可能影响到界面布局，我们应该调用这个方法来告诉布局系统在未来某个时刻需要更新，系统会调用updateContraints去更新布局。
- (void)setNeedsUpdateConstraints NS_AVAILABLE_IOS(6_0);
@end

// Compatibility and Adoption

@interface UIView (UIConstraintBasedCompatibility)

/* By default, the autoresizing mask on a view gives rise to constraints that fully determine
 the view's position. This allows the auto layout system to track the frames of views whose
 layout is controlled manually (through -setFrame:, for example).
 When you elect to position the view using auto layout by adding your own constraints,
 you must set this property to NO. IB will do this for you.
 */
//我们在使用代码来写自己的约束布局代码时，必须设置当前view的translatesAutoresizingMaskIntoContraints为NO，否则无法工作。
@property(nonatomic) BOOL translatesAutoresizingMaskIntoConstraints NS_AVAILABLE_IOS(6_0); // Default YES

/* constraint-based layout engages lazily when someone tries to use it (e.g., adds a constraint to a view).  If you do all of your constraint set up in -updateConstraints, you might never even receive updateConstraints if no one makes a constraint.  To fix this chicken and egg problem, override this method to return YES if your view needs the window to use constraint-based layout.
 */
#if UIKIT_DEFINE_AS_PROPERTIES
@property(class, nonatomic, readonly) BOOL requiresConstraintBasedLayout NS_AVAILABLE_IOS(6_0);
#else
+ (BOOL)requiresConstraintBasedLayout NS_AVAILABLE_IOS(6_0);
#endif

@end

// Separation of Concerns

@interface UIView (UIConstraintBasedLayoutLayering)

/* Constraints do not actually relate the frames of the views, rather they relate the "alignment rects" of views.  This is the same as the frame unless overridden by a subclass of UIView.  Alignment rects are the same as the "layout rects" shown in Interface Builder 3.  Typically the alignment rect of a view is what the end user would think of as the bounding rect around a control, omitting ornamentation like shadows and engraving lines.  The edges of the alignment rect are what is interesting to align, not the shadows and such.
 */

/* These two methods should be inverses of each other.  UIKit will call both as part of layout computation.
 They may be overridden to provide arbitrary transforms between frame and alignment rect, though the two methods must be inverses of each other.
 However, the default implementation uses -alignmentRectInsets, so just override that if it's applicable.  It's easier to get right.
 A view that displayed an image with some ornament would typically override these, because the ornamental part of an image would scale up with the size of the frame.
 Set the NSUserDefault UIViewShowAlignmentRects to YES to see alignment rects drawn.
 */
- (CGRect)alignmentRectForFrame:(CGRect)frame NS_AVAILABLE_IOS(6_0);
- (CGRect)frameForAlignmentRect:(CGRect)alignmentRect NS_AVAILABLE_IOS(6_0);

/* override this if the alignment rect is obtained from the frame by insetting each edge by a fixed amount.  This is only called by alignmentRectForFrame: and frameForAlignmentRect:.
 */
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) UIEdgeInsets alignmentRectInsets NS_AVAILABLE_IOS(6_0);
#else
- (UIEdgeInsets)alignmentRectInsets NS_AVAILABLE_IOS(6_0);
#endif

- (UIView *)viewForBaselineLayout NS_DEPRECATED_IOS(6_0, 9_0, "Override -viewForFirstBaselineLayout or -viewForLastBaselineLayout as appropriate, instead") __TVOS_PROHIBITED;

/* -viewForFirstBaselineLayout is called by the constraints system when interpreting
 the firstBaseline attribute for a view.
 For complex custom UIView subclasses, override this method to return the text-based
 (i.e., UILabel or non-scrollable UITextView) descendant of the receiver whose first baseline
 is appropriate for alignment.
 UIView's implementation returns [self viewForLastBaselineLayout], so if the same
 descendant is appropriate for both first- and last-baseline layout you may override
 just -viewForLastBaselineLayout.
 */
@property(readonly,strong) UIView *viewForFirstBaselineLayout NS_AVAILABLE_IOS(9_0);

/* -viewForLastBaselineLayout is called by the constraints system when interpreting
 the lastBaseline attribute for a view.
 For complex custom UIView subclasses, override this method to return the text-based
 (i.e., UILabel or non-scrollable UITextView) descendant of the receiver whose last baseline
 is appropriate for alignment.
 UIView's implementation returns self.
 */
@property(readonly,strong) UIView *viewForLastBaselineLayout NS_AVAILABLE_IOS(9_0);

/* Override this method to tell the layout system that there is something it doesn't natively understand in this view, and this is how large it intrinsically is.  A typical example would be a single line text field.  The layout system does not understand text - it must just be told that there's something in the view, and that that something will take a certain amount of space if not clipped.
 
 In response, UIKit will set up constraints that specify (1) that the opaque content should not be compressed or clipped, (2) that the view prefers to hug tightly to its content.
 
 A user of a view may need to specify the priority of these constraints.  For example, by default, a push button
 -strongly wants to hug its content in the vertical direction (buttons really ought to be their natural height)
 -weakly hugs its content horizontally (extra side padding between the title and the edge of the bezel is acceptable)
 -strongly resists compressing or clipping content in both directions.
 
 However, you might have a case where you'd prefer to show all the available buttons with truncated text rather than losing some of the buttons. The truncation might only happen in portrait orientation but not in landscape, for example. In that case you'd want to setContentCompressionResistancePriority:forAxis: to (say) UILayoutPriorityDefaultLow for the horizontal axis.
 
 The default 'strong' and 'weak' priorities referred to above are UILayoutPriorityDefaultHigh and UILayoutPriorityDefaultLow.
 
 Note that not all views have an intrinsicContentSize.  UIView's default implementation is to return (UIViewNoIntrinsicMetric, UIViewNoIntrinsicMetric).  The _intrinsic_ content size is concerned only with data that is in the view itself, not in other views. Remember that you can also set constant width or height constraints on any view, and you don't need to override instrinsicContentSize if these dimensions won't be changing with changing view content.
 */
UIKIT_EXTERN const CGFloat UIViewNoIntrinsicMetric NS_AVAILABLE_IOS(6_0); // -1
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) CGSize intrinsicContentSize NS_AVAILABLE_IOS(6_0);
#else
- (CGSize)intrinsicContentSize NS_AVAILABLE_IOS(6_0);
#endif
- (void)invalidateIntrinsicContentSize NS_AVAILABLE_IOS(6_0); // call this when something changes that affects the intrinsicContentSize.  Otherwise UIKit won't notice that it changed.

- (UILayoutPriority)contentHuggingPriorityForAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(6_0);
- (void)setContentHuggingPriority:(UILayoutPriority)priority forAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(6_0);

- (UILayoutPriority)contentCompressionResistancePriorityForAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(6_0);
- (void)setContentCompressionResistancePriority:(UILayoutPriority)priority forAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(6_0);
@end

// Size To Fit

UIKIT_EXTERN const CGSize UILayoutFittingCompressedSize NS_AVAILABLE_IOS(6_0);
UIKIT_EXTERN const CGSize UILayoutFittingExpandedSize NS_AVAILABLE_IOS(6_0);

@interface UIView (UIConstraintBasedLayoutFittingSize)
/* The size fitting most closely to targetSize in which the receiver's subtree can be laid out while optimally satisfying the constraints. If you want the smallest possible size, pass UILayoutFittingCompressedSize; for the largest possible size, pass UILayoutFittingExpandedSize.
 Also see the comment for UILayoutPriorityFittingSizeLevel.
 */
- (CGSize)systemLayoutSizeFittingSize:(CGSize)targetSize NS_AVAILABLE_IOS(6_0); // Equivalent to sending -systemLayoutSizeFittingSize:withHorizontalFittingPriority:verticalFittingPriority: with UILayoutPriorityFittingSizeLevel for both priorities.
- (CGSize)systemLayoutSizeFittingSize:(CGSize)targetSize withHorizontalFittingPriority:(UILayoutPriority)horizontalFittingPriority verticalFittingPriority:(UILayoutPriority)verticalFittingPriority NS_AVAILABLE_IOS(8_0);
@end

@interface UIView (UILayoutGuideSupport)

/* UILayoutGuide objects owned by the receiver.
 */
@property(nonatomic,readonly,copy) NSArray<__kindof UILayoutGuide *> *layoutGuides NS_AVAILABLE_IOS(9_0);

/* Adds layoutGuide to the receiver, passing the receiver in -setOwningView: to layoutGuide.
 */
- (void)addLayoutGuide:(UILayoutGuide *)layoutGuide NS_AVAILABLE_IOS(9_0);

/* Removes layoutGuide from the receiver, passing nil in -setOwningView: to layoutGuide.
 */
- (void)removeLayoutGuide:(UILayoutGuide *)layoutGuide NS_AVAILABLE_IOS(9_0);
@end

@class NSLayoutXAxisAnchor,NSLayoutYAxisAnchor,NSLayoutDimension;
@interface UIView (UIViewLayoutConstraintCreation)
/* Constraint creation conveniences. See NSLayoutAnchor.h for details.
 */
@property(readonly, strong) NSLayoutXAxisAnchor *leadingAnchor NS_AVAILABLE_IOS(9_0);
@property(readonly, strong) NSLayoutXAxisAnchor *trailingAnchor NS_AVAILABLE_IOS(9_0);
@property(readonly, strong) NSLayoutXAxisAnchor *leftAnchor NS_AVAILABLE_IOS(9_0);
@property(readonly, strong) NSLayoutXAxisAnchor *rightAnchor NS_AVAILABLE_IOS(9_0);
@property(readonly, strong) NSLayoutYAxisAnchor *topAnchor NS_AVAILABLE_IOS(9_0);
@property(readonly, strong) NSLayoutYAxisAnchor *bottomAnchor NS_AVAILABLE_IOS(9_0);
@property(readonly, strong) NSLayoutDimension *widthAnchor NS_AVAILABLE_IOS(9_0);
@property(readonly, strong) NSLayoutDimension *heightAnchor NS_AVAILABLE_IOS(9_0);
@property(readonly, strong) NSLayoutXAxisAnchor *centerXAnchor NS_AVAILABLE_IOS(9_0);
@property(readonly, strong) NSLayoutYAxisAnchor *centerYAnchor NS_AVAILABLE_IOS(9_0);
@property(readonly, strong) NSLayoutYAxisAnchor *firstBaselineAnchor NS_AVAILABLE_IOS(9_0);
@property(readonly, strong) NSLayoutYAxisAnchor *lastBaselineAnchor NS_AVAILABLE_IOS(9_0);

@end

// Debugging

/* Everything in this section should be used in debugging only, never in shipping code.  These methods may not exist in the future - no promises.
 */
@interface UIView (UIConstraintBasedLayoutDebugging)

/* This returns a list of all the constraints that are affecting the current location of the receiver.  The constraints do not necessarily involve the receiver, they may affect the frame indirectly.
 Pass UILayoutConstraintAxisHorizontal for the constraints affecting [self center].x and CGRectGetWidth([self bounds]), and UILayoutConstraintAxisVertical for the constraints affecting[self center].y and CGRectGetHeight([self bounds]).
 */
- (NSArray<__kindof NSLayoutConstraint *> *)constraintsAffectingLayoutForAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(6_0);

/* If there aren't enough constraints in the system to uniquely determine layout, we say the layout is ambiguous.  For example, if the only constraint in the system was x = y + 100, then there are lots of different possible values for x and y.  This situation is not automatically detected by UIKit, due to performance considerations and details of the algorithm used for layout.
 The symptom of ambiguity is that views sometimes jump from place to place, or possibly are just in the wrong place.
 -hasAmbiguousLayout runs a check for whether there is another center and bounds the receiver could have that could also satisfy the constraints.
 -exerciseAmbiguousLayout does more.  It randomly changes the view layout to a different valid layout.  Making the UI jump back and forth can be helpful for figuring out where you're missing a constraint.
 */
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) BOOL hasAmbiguousLayout NS_AVAILABLE_IOS(6_0);
#else
- (BOOL)hasAmbiguousLayout NS_AVAILABLE_IOS(6_0);
#endif

- (void)exerciseAmbiguityInLayout NS_AVAILABLE_IOS(6_0);
@end

/* Everything in this section should be used in debugging only, never in shipping code.  These methods may not exist in the future - no promises.
 */
@interface UILayoutGuide (UIConstraintBasedLayoutDebugging)

/* This returns a list of all the constraints that are affecting the current location of the receiver.  The constraints do not necessarily involve the receiver, they may affect the frame indirectly.
 Pass UILayoutConstraintAxisHorizontal for the constraints affecting [self center].x and CGRectGetWidth([self bounds]), and UILayoutConstraintAxisVertical for the constraints affecting[self center].y and CGRectGetHeight([self bounds]).
 */
- (NSArray<__kindof NSLayoutConstraint *> *)constraintsAffectingLayoutForAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(10_0);

/* If there aren't enough constraints in the system to uniquely determine layout, we say the layout is ambiguous.  For example, if the only constraint in the system was x = y + 100, then there are lots of different possible values for x and y.  This situation is not automatically detected by UIKit, due to performance considerations and details of the algorithm used for layout.
 The symptom of ambiguity is that views sometimes jump from place to place, or possibly are just in the wrong place.
 -hasAmbiguousLayout runs a check for whether there is another center and bounds the receiver could have that could also satisfy the constraints.
 */
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) BOOL hasAmbiguousLayout NS_AVAILABLE_IOS(10_0);
#else
- (BOOL)hasAmbiguousLayout NS_AVAILABLE_IOS(10_0);
#endif
@end

@interface UIView (UIStateRestoration)
@property (nullable, nonatomic, copy) NSString *restorationIdentifier NS_AVAILABLE_IOS(6_0);
- (void) encodeRestorableStateWithCoder:(NSCoder *)coder NS_AVAILABLE_IOS(6_0);
- (void) decodeRestorableStateWithCoder:(NSCoder *)coder NS_AVAILABLE_IOS(6_0);
@end

@interface UIView (UISnapshotting)
/*
 * When requesting a snapshot, 'afterUpdates' defines whether the snapshot is representative of what's currently on screen or if you wish to include any recent changes before taking the snapshot.
 
 If called during layout from a committing transaction, snapshots occurring after the screen updates will include all changes made, regardless of when the snapshot is taken and the changes are made. For example:
 
 - (void)layoutSubviews {
 UIView *snapshot = [self snapshotViewAfterScreenUpdates:YES];
 self.alpha = 0.0;
 }
 
 The snapshot will appear to be empty since the change in alpha will be captured by the snapshot. If you need to animate the view during layout, animate the snapshot instead.
 
 * Creating snapshots from existing snapshots (as a method to duplicate, crop or create a resizable variant) is supported. In cases where many snapshots are needed, creating a snapshot from a common superview and making subsequent snapshots from it can be more performant. Please keep in mind that if 'afterUpdates' is YES, the original snapshot is committed and any changes made to it, not the view originally snapshotted, will be included.
 */
- (nullable UIView *)snapshotViewAfterScreenUpdates:(BOOL)afterUpdates NS_AVAILABLE_IOS(7_0);
- (nullable UIView *)resizableSnapshotViewFromRect:(CGRect)rect afterScreenUpdates:(BOOL)afterUpdates withCapInsets:(UIEdgeInsets)capInsets NS_AVAILABLE_IOS(7_0);  // Resizable snapshots will default to stretching the center
// Use this method to render a snapshot of the view hierarchy into the current context. Returns NO if the snapshot is missing image data, YES if the snapshot is complete. Calling this method from layoutSubviews while the current transaction is committing will capture what is currently displayed regardless if afterUpdates is YES.
- (BOOL)drawViewHierarchyInRect:(CGRect)rect afterScreenUpdates:(BOOL)afterUpdates NS_AVAILABLE_IOS(7_0);
@end

NS_ASSUME_NONNULL_END
