/* CoreAnimation - CAAnimation.h
 
 Copyright (c) 2006-2017, Apple Inc.
 All rights reserved. */

#import <QuartzCore/CALayer.h>
#import <Foundation/NSObject.h>

@class NSArray, NSString, CAMediaTimingFunction, CAValueFunction;
@protocol CAAnimationDelegate;

NS_ASSUME_NONNULL_BEGIN

/*
 1.CABasicAnimation
 通过设定起始点，终点，时间，动画会沿着你这设定点进行移动。可以看做特殊的CAKeyFrameAnimation
 2.CAKeyframeAnimation
 Keyframe顾名思义就是关键点的frame，你可以通过设定CALayer的始点、中间关键点、终点的frame，时间，动画会沿你设定的轨迹进行移动
 3.CAAnimationGroup
 Group也就是组合的意思，就是把对这个Layer的所有动画都组合起来。PS：一个layer设定了很多动画，他们都会同时执行，如何按顺序执行我到时候再讲。
 4.CATransition
 这个就是苹果帮开发者封装好的一些动画，
 */

/** The base animation class. **/

CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CAAnimation : NSObject   //动画基类
<NSCoding, NSCopying, CAMediaTiming, CAAction>
{
@private
    void *_attr;
    uint32_t _flags;
}

/* Creates a new animation object. */
//类方法（工厂方法),创建一个新的动画对象
+ (instancetype)animation;

/* Animations implement the same property model as defined by CALayer.
 * See CALayer.h for more details. */

+ (nullable id)defaultValueForKey:(NSString *)key;
- (BOOL)shouldArchiveValueForKey:(NSString *)key;

/* A timing function defining the pacing of the animation. Defaults to
 * nil indicating linear pacing. */
/*
 速度控制函数(CAMediaTimingFunction):
 1> kCAMediaTimingFunctionLinear（线性）：匀速，给你一个相对静态的感觉
 2> kCAMediaTimingFunctionEaseIn（渐进）：动画缓慢进入，然后加速离开
 3> kCAMediaTimingFunctionEaseOut（渐出）：动画全速进入，然后减速的到达目的地
 4> kCAMediaTimingFunctionEaseInEaseOut（渐进渐出）：动画缓慢的进入，中间加速，然后减速的到达目的地。
 */
@property(nullable, strong) CAMediaTimingFunction *timingFunction;

/* The delegate of the animation. This object is retained for the
 * lifetime of the animation object. Defaults to nil. See below for the
 * supported delegate methods. */
//动画代理，默认为nil。设置之后在相应时间会回调相应的代理方法
@property(nullable, strong) id <CAAnimationDelegate> delegate;

/* When true, the animation is removed from the render tree once its
 * active duration has passed. Defaults to YES. */
//默认为YES，代表动画执行完毕后就从图层上移除，图形会恢复到动画执行前的状态。如果想让图层保持显示动画执行后的状态，那就设置为NO，不过还要设置fillMode为kCAFillModeForwards .
@property(getter=isRemovedOnCompletion) BOOL removedOnCompletion;

@end

/* Delegate methods for CAAnimation. */

@protocol CAAnimationDelegate <NSObject>
@optional

/* Called when the animation begins its active duration. */
// 动画开始时的回调
- (void)animationDidStart:(CAAnimation *)anim;

/* Called when the animation either completes its active duration or
 * is removed from the object it is attached to (i.e. the layer). 'flag'
 * is true if the animation reached the end of its active duration
 * without being removed. */
//动画停止的回调，可以通过flag判断动画是否是完成还是暂停
- (void)animationDidStop:(CAAnimation *)anim finished:(BOOL)flag;

@end


/** Subclass for property-based animations. **/
/*
 是CAAnimation的子类，也是个抽象类。要想创建动画，应该使用它的两个子类：CABasicAnimation和CAKeyframeAnimation
 */
CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CAPropertyAnimation : CAAnimation

/* Creates a new animation object with its `keyPath' property set to
 * 'path'. */

+ (instancetype)animationWithKeyPath:(nullable NSString *)path;

/* The key-path describing the property to be animated. */
// 通过指定CALayer的一个属性名，并且对CALayer的这个属性的值进行修改，达到相应的效果。
@property(nullable, copy) NSString *keyPath;

/* When true the value specified by the animation will be "added" to
 * the current presentation value of the property to produce the new
 * presentation value. The addition function is type-dependent, e.g.
 * for affine transforms the two matrices are concatenated. Defaults to
 * NO. */

@property(getter=isAdditive) BOOL additive;

/* The `cumulative' property affects how repeating animations produce
 * their result. If true then the current value of the animation is the
 * value at the end of the previous repeat cycle, plus the value of the
 * current repeat cycle. If false, the value is simply the value
 * calculated for the current repeat cycle. Defaults to NO. */

@property(getter=isCumulative) BOOL cumulative;

/* If non-nil a function that is applied to interpolated values
 * before they are set as the new presentation value of the animation's
 * target property. Defaults to nil. */

@property(nullable, strong) CAValueFunction *valueFunction;

@end


/** Subclass for basic (single-keyframe) animations. **/
//提供了对单一动画的实现，继承于CAPropertyAbimation
CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CABasicAnimation : CAPropertyAnimation

/* The objects defining the property values being interpolated between.
 * All are optional, and no more than two should be non-nil. The object
 * type should match the type of the property being animated (using the
 * standard rules described in CALayer.h). The supported modes of
 * animation are:
 *
 * - both `fromValue' and `toValue' non-nil. Interpolates between
 * `fromValue' and `toValue'.
 *
 * - `fromValue' and `byValue' non-nil. Interpolates between
 * `fromValue' and `fromValue' plus `byValue'.
 *
 * - `byValue' and `toValue' non-nil. Interpolates between `toValue'
 * minus `byValue' and `toValue'.
 *
 * - `fromValue' non-nil. Interpolates between `fromValue' and the
 * current presentation value of the property.
 *
 * - `toValue' non-nil. Interpolates between the layer's current value
 * of the property in the render tree and `toValue'.
 *
 * - `byValue' non-nil. Interpolates between the layer's current value
 * of the property in the render tree and that plus `byValue'. */

@property(nullable, strong) id fromValue;
@property(nullable, strong) id toValue;
@property(nullable, strong) id byValue;

@end


/** General keyframe animation class. **/
//关键帧动画，可以定义动画路线，继承于CAPropertyAbimation
CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CAKeyframeAnimation : CAPropertyAnimation
/*
 CApropertyAnimation的子类，跟CABasicAnimation的区别是：
 CABasicAnimation只能从一个数值(fromValue)变到另一个数值(toValue)，而CAKeyframeAnimation会使用一个NSArray保存这些数值 .
 
 属性解析
 values:
 就是上述的NSArray对象。里面的元素称为”关键帧”(keyframe)。动画对象会在指定的时间(duration)内，依次显示values数组中的每一个关键帧 .
 path:
 可以设置一个CGPathRef\CGMutablePathRef,让层跟着路径移动。path只对CALayer的anchorPoint和position起作用。如果你设置了path，那么values将被
 忽略 .
 keyTimes:
 可以为对应的关键帧指定对应的时间点,其取值范围为0到1.0,keyTimes中的每一个时间值都对应values中的每一帧.当keyTimes没有设置的时候,各个关键帧的时间是
 平分的 .
 timeFunctions:
 用过UIKit层动画的同学应该对这个属性不陌生，这个属性用以指定时间函数，类似于运动的加速度，有以下几种类型。上例子的AB段就是用了淡入淡出效果。记住，这是
 一个数组，你有几个子路径就应该传入几个元素
 kCAMediaTimingFunctionLinear//线性
 kCAMediaTimingFunctionEaseIn//淡入
 kCAMediaTimingFunctionEaseOut//淡出
 kCAMediaTimingFunctionEaseInEaseOut//淡入淡出
 kCAMediaTimingFunctionDefault//默认
 calculationMode属性:
 该属性决定了物体在每个子路径下是跳着走还是匀速走，跟timeFunctions属性有点类似
 const kCAAnimationLinear//线性，默认
 const kCAAnimationDiscrete//离散，无中间过程，但keyTimes设置的时间依旧生效，物体跳跃地出现在各个关键帧上
 const kCAAnimationPaced//平均，keyTimes跟timeFunctions失效
 const kCAAnimationCubic//平均，同上
 const kCAAnimationCubicPaced//平均，同上
 
 对关键帧为座标点的关键帧进行圆滑曲线相连后插值计算,对于曲线的形状还可以通过tensionValues,continuityValues,biasValues来进行调整自定义,这里的数学
 原理是Kochanek–Bartels spline,这里的主要目的是使得运行的轨迹变得圆滑;
 */
/* An array of objects providing the value of the animation function for
 * each keyframe. */

@property(nullable, copy) NSArray *values;

/* An optional path object defining the behavior of the animation
 * function. When non-nil overrides the `values' property. Each point
 * in the path except for `moveto' points defines a single keyframe for
 * the purpose of timing and interpolation. Defaults to nil. For
 * constant velocity animation along the path, `calculationMode' should
 * be set to `paced'. Upon assignment the path is copied. */

@property(nullable) CGPathRef path;

/* An optional array of `NSNumber' objects defining the pacing of the
 * animation. Each time corresponds to one value in the `values' array,
 * and defines when the value should be used in the animation function.
 * Each value in the array is a floating point number in the range
 * [0,1]. */

@property(nullable, copy) NSArray<NSNumber *> *keyTimes;

/* An optional array of CAMediaTimingFunction objects. If the `values' array
 * defines n keyframes, there should be n-1 objects in the
 * `timingFunctions' array. Each function describes the pacing of one
 * keyframe to keyframe segment. */

@property(nullable, copy) NSArray<CAMediaTimingFunction *> *timingFunctions;

/* The "calculation mode". Possible values are `discrete', `linear',
 * `paced', `cubic' and `cubicPaced'. Defaults to `linear'. When set to
 * `paced' or `cubicPaced' the `keyTimes' and `timingFunctions'
 * properties of the animation are ignored and calculated implicitly. */

@property(copy) NSString *calculationMode;

/* For animations with the cubic calculation modes, these properties
 * provide control over the interpolation scheme. Each keyframe may
 * have a tension, continuity and bias value associated with it, each
 * in the range [-1, 1] (this defines a Kochanek-Bartels spline, see
 * http://en.wikipedia.org/wiki/Kochanek-Bartels_spline).
 *
 * The tension value controls the "tightness" of the curve (positive
 * values are tighter, negative values are rounder). The continuity
 * value controls how segments are joined (positive values give sharp
 * corners, negative values give inverted corners). The bias value
 * defines where the curve occurs (positive values move the curve before
 * the control point, negative values move it after the control point).
 *
 * The first value in each array defines the behavior of the tangent to
 * the first control point, the second value controls the second
 * point's tangents, and so on. Any unspecified values default to zero
 * (giving a Catmull-Rom spline if all are unspecified). */

@property(nullable, copy) NSArray<NSNumber *> *tensionValues;
@property(nullable, copy) NSArray<NSNumber *> *continuityValues;
@property(nullable, copy) NSArray<NSNumber *> *biasValues;

/* Defines whether or objects animating along paths rotate to match the
 * path tangent. Possible values are `auto' and `autoReverse'. Defaults
 * to nil. The effect of setting this property to a non-nil value when
 * no path object is supplied is undefined. `autoReverse' rotates to
 * match the tangent plus 180 degrees. */

@property(nullable, copy) NSString *rotationMode;

@end

/* `calculationMode' strings. */

CA_EXTERN NSString * const kCAAnimationLinear
CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAAnimationDiscrete
CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAAnimationPaced
CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAAnimationCubic
CA_AVAILABLE_STARTING (10.7, 4.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAAnimationCubicPaced
CA_AVAILABLE_STARTING (10.7, 4.0, 9.0, 2.0);

/* `rotationMode' strings. */

CA_EXTERN NSString * const kCAAnimationRotateAuto
CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCAAnimationRotateAutoReverse
CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/** Subclass for mass-spring animations. */
//提供弹簧效果，继承于CABasicAnimationCA_CLASS_AVAILABLE (10.11, 9.0, 9.0, 2.0)
@interface CASpringAnimation : CABasicAnimation
/*
 iOS9才引入的动画类，它继承于CABaseAnimation，用于制作弹簧动画，先演示个例子
 1. 参数说明
 mass:
 质量，影响图层运动时的弹簧惯性，质量越大，弹簧拉伸和压缩的幅度越大.
 stiffness:
 刚度系数(劲度系数/弹性系数)，刚度系数越大，形变产生的力就越大，运动越快
 damping:
 阻尼系数，阻止弹簧伸缩的系数，阻尼系数越大，停止越快
 initialVelocity:
 初始速率，动画视图的初始速度大小
 速率为正数时，速度方向与运动方向一致，速率为负数时，速度方向与运动方向相反
 settlingDuration:
 结算时间返回弹簧动画到停止时的估算时间，根据当前的动画参数估算
 通常弹簧动画的时间使用结算时间比较准确
 */
/* The mass of the object attached to the end of the spring. Must be greater
 than 0. Defaults to one. */

@property CGFloat mass;

/* The spring stiffness coefficient. Must be greater than 0.
 * Defaults to 100. */

@property CGFloat stiffness;

/* The damping coefficient. Must be greater than or equal to 0.
 * Defaults to 10. */

@property CGFloat damping;

/* The initial velocity of the object attached to the spring. Defaults
 * to zero, which represents an unmoving object. Negative values
 * represent the object moving away from the spring attachment point,
 * positive values represent the object moving towards the spring
 * attachment point. */

@property CGFloat initialVelocity;

/* Returns the estimated duration required for the spring system to be
 * considered at rest. The duration is evaluated for the current animation
 * parameters. */

@property(readonly) CFTimeInterval settlingDuration;

@end

/** Transition animation subclass. **/
//提供渐变效果，继承于CAAnimation
CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CATransition : CAAnimation
/*
 CAAnimation的子类，用于做转场动画，能够为层提供移出屏幕和移入屏幕的动画效果。iOS比Mac OS X的转场动画效果少一点
 UINavigationController就是通过CATransition实现了将控制器的视图推入屏幕的动画效果
 属性解析:
 type：动画过渡类型
 subtype：动画过渡方向
 startProgress：动画起点(在整体动画的百分比)
 endProgress：动画终点(在整体动画的百分比)
 */
/* The name of the transition. Current legal transition types include
 * `fade', `moveIn', `push' and `reveal'. Defaults to `fade'. */
/* 过渡效果类型:
        fade     //交叉淡化过渡(不支持过渡方向) kCATransitionFade
        push     //新视图把旧视图推出去  kCATransitionPush
        moveIn   //新视图移到旧视图上面   kCATransitionMoveIn
        reveal   //将旧视图移开,显示下面的新视图  kCATransitionReveal
        cube     //立方体翻滚效果
        oglFlip  //上下左右翻转效果
        suckEffect   //收缩效果，如一块布被抽走(不支持过渡方向)
        rippleEffect //滴水效果(不支持过渡方向)
        pageCurl     //向上翻页效果
        pageUnCurl   //向下翻页效果
        cameraIrisHollowOpen  //相机镜头打开效果(不支持过渡方向)
        cameraIrisHollowClose //相机镜头关上效果(不支持过渡方向)
 */
@property(copy) NSString *type;

/* An optional subtype for the transition. E.g. used to specify the
 * transition direction for motion-based transitions, in which case
 * the legal values are `fromLeft', `fromRight', `fromTop' and
 * `fromBottom'. */
/* 过渡方向
         kCATransitionFromRight
         kCATransitionFromLeft
         kCATransitionFromBottom
         kCATransitionFromTop
 */
@property(nullable, copy) NSString *subtype;

/* The amount of progress through to the transition at which to begin
 * and end execution. Legal values are numbers in the range [0,1].
 * `endProgress' must be greater than or equal to `startProgress'.
 * Default values are 0 and 1 respectively. */
//动画起点(在整体动画的百分比),值在［0，1］之间，默认0
@property float startProgress;
//动画终点(在整体动画的百分比),值在［0，1］之间，默认1
@property float endProgress;

/* An optional filter object implementing the transition. When set the
 * `type' and `subtype' properties are ignored. The filter must
 * implement `inputImage', `inputTargetImage' and `inputTime' input
 * keys, and the `outputImage' output key. Optionally it may support
 * the `inputExtent' key, which will be set to a rectangle describing
 * the region in which the transition should run. Defaults to nil. */
/*
 为动画添加一个可选的滤镜。
 如果指定，那么指定的filter必须同时支持x和y，否则该filter将不起作用。
 默认值为nil。
 如果设置了filter，那么，为layer设置的type和subtype属性将被忽略。
 该属性只在iOS 5.0以及以后版本被支持。
 如果设置了filter，那么必须实现`inputImage', `inputTargetImage' and `inputTime' input
 keys, and the `outputImage' output key. Optionally it may support
 the `inputExtent' key,
 */
@property(nullable, strong) id filter;

@end

/* Common transition types. */

CA_EXTERN NSString * const kCATransitionFade
CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCATransitionMoveIn
CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCATransitionPush
CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCATransitionReveal
CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);

/* Common transition subtypes. */

CA_EXTERN NSString * const kCATransitionFromRight
CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCATransitionFromLeft
CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCATransitionFromTop
CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
CA_EXTERN NSString * const kCATransitionFromBottom
CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);


/** Animation subclass for grouped animations. **/
//允许多个动画同时播放，继承于CAAnimation
CA_CLASS_AVAILABLE (10.5, 2.0, 9.0, 2.0)
@interface CAAnimationGroup : CAAnimation

/* An array of CAAnimation objects. Each member of the array will run
 * concurrently in the time space of the parent animation using the
 * normal rules. */
/*
CAAnimation的子类，可以保存一组动画对象，将CAAnimationGroup对象加入层后，组中所有动画对象可以同时并发运行
属性解析：
animations：用来保存一组动画对象的NSArray
默认情况下，一组动画对象是同时运行的，也可以通过设置动画对象的beginTime属性来更改动画的开始时间
*/
@property(nullable, copy) NSArray<CAAnimation *> *animations;

@end

NS_ASSUME_NONNULL_END
