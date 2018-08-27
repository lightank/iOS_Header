//
//  UIVisualEffectView.h
//  UIKit
//
//  Copyright (c) 2014-2016 Apple Inc. All rights reserved.
//

#import <UIKit/UIView.h>

NS_ASSUME_NONNULL_BEGIN

/* UIVisualEffectView is a class that provides a simple abstraction over complex visual effects. Depending on the desired effect, the results may affect content layered behind the view or content added to the view's contentView. Please see the notes for each UIVisualEffect for more details.
 
 Proper use of this class requires some assistance on your part. Namely:
 
 • Avoid alpha values < 1 - By default, when a view is partially transparent, the system composites that view and all of its subviews in an offscreen render pass to get the correct translucency. However, UIVisualEffects require being composited as part of the content they are logically layered on top of to look correct. If alpha is less than 1 on the UIVisualEffectView or any of its superviews, many effects will look incorrect or won't show up at all. Setting the alpha on views placed inside the contentView is supported.
 
 • Judicious masking - Masks have similar semantics to non-opaque views with regards to offscreen rendering. Masks applied to the UIVisualEffectView itself are forwarded to all internal views, including the contentView. You are free to apply a mask to just the contentView. The mask you provide to UIVisualEffectView will not be the view that actually performs the mask. UIKit will make copies of the view to apply to each subview. To reflect a size change to the mask, you must apply the change to the original mask view and reset it on the effect view. Applying a mask to a superview of a UIVisualEffectView (via setMaskView: or the layer's mask property) will cause the effect to fail.
 
 • Correctly capturing snapshots - Many effects require support from the window that hosts the view. As such, attempting to take a snapshot of just the UIVisualEffectView will result in the snapshot not containing the effect at all or it appearing incorrectly. To properly snapshot a view hierarchy that contains a UIVisualEffectView, you must snapshot the entire UIWindow or UIScreen that contains it.
 */

/*
 从iOS 7开始，苹果改变了App的UI风格和动画效果，例如当导航栏出现在屏幕上的效果。尤其是苹果在iOS7中，使用了全新的雾玻璃效果（模糊特效）。不仅仅是导航栏，通知中心和控制中心也采用了这个特殊的视觉效果。但是苹果并没有在SDK中放入这个特效，程序员不得不使用自己的方法在模拟这个效果，一直到iOS8的出现。在iOS 8中，SDK中终于正式加入了这个特性，不但让程序员易于上手，而且性能表现也很优秀。苹果将之称为Visual Effects（视觉效果）。Visual Effects是一整套的视觉特效，包括了UIBlurEffect和UIVibrancyEffect。这两者都是UIVisualEffect的子类，前者允许在你App中动态地创建实时的雾玻璃效果，而后者则允许你在雾玻璃上“写字”。
 */
//3种不同的模糊效果：很亮、亮、暗色。
typedef NS_ENUM(NSInteger, UIBlurEffectStyle) {
    UIBlurEffectStyleExtraLight,    //偏白色
    UIBlurEffectStyleLight, //模糊
    UIBlurEffectStyleDark,  //偏黑色
    UIBlurEffectStyleExtraDark __TVOS_AVAILABLE(10_0) __IOS_PROHIBITED __WATCHOS_PROHIBITED,
    UIBlurEffectStyleRegular NS_ENUM_AVAILABLE_IOS(10_0), // Adapts to user interface style
    UIBlurEffectStyleProminent NS_ENUM_AVAILABLE_IOS(10_0), // Adapts to user interface style
} NS_ENUM_AVAILABLE_IOS(8_0);

NS_CLASS_AVAILABLE_IOS(8_0) @interface UIVisualEffect : NSObject <NSCopying, NSSecureCoding> @end

/* UIBlurEffect will provide a blur that appears to have been applied to the content layered behind the UIVisualEffectView. Views added to the contentView of a blur visual effect are not blurred themselves. */
//UIBlurEffect类继承于UIVisualEffect，允许在你App中动态地创建实时的雾玻璃效果
NS_CLASS_AVAILABLE_IOS(8_0) @interface UIBlurEffect : UIVisualEffect
+ (UIBlurEffect *)effectWithStyle:(UIBlurEffectStyle)style;//模糊效果
@end

/* UIVibrancyEffect amplifies and adjusts the color of content layered behind the view, allowing content placed inside the contentView to become more vivid. It is intended to be placed over, or as a subview of, a UIVisualEffectView that has been configured with a UIBlurEffect. This effect only affects content added to the contentView. Because the vibrancy effect is color dependent, subviews added to the contentView need to be tintColorDidChange aware and must be prepared to update themselves accordingly. UIImageView will need its image to have a rendering mode of UIImageRenderingModeAlwaysTemplate to receive the proper effect.
 */
/* UIVibrancyEffect放大并调整视图后面分层的内容的颜色，允许放置在contentView内的内容变得更加生动。 它将被放置在已经配置了UIBlurEffect的UIVisualEffectView中，或作为子视图。 此效果仅影响添加到contentView中的内容。 由于活力影响是颜色依赖的，添加到contentView的子视图需要被知道tintColorDidChange，并且必须准备相应地进行更新。 UIImageView将需要其图像具有UIImageRenderingModeAlwaysTemplate的渲染模式才能获得正确的效果。
 */
//UIVibrancyEffect类继承于UIVisualEffect，允许你在雾玻璃上“写字”
NS_CLASS_AVAILABLE_IOS(8_0) @interface UIVibrancyEffect : UIVisualEffect
+ (UIVibrancyEffect *)effectForBlurEffect:(UIBlurEffect *)blurEffect;
@end

NS_CLASS_AVAILABLE_IOS(8_0) @interface UIVisualEffectView : UIView <NSSecureCoding>
@property (nonatomic, strong, readonly) UIView *contentView; // Do not add subviews directly to UIVisualEffectView, use this view instead.
//The visual effect provided by the view. (read-only)
//视觉效果由视图提供。 （只读）
@property (nonatomic, copy, nullable) UIVisualEffect *effect;
- (instancetype)initWithEffect:(nullable UIVisualEffect *)effect NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
@end

/*
 
 self.view.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"6.jpg"]];

    模糊效果的三种风格
 
   @param UIBlurEffectStyle
 
 UIBlurEffectStyleExtraLight,额外亮度，（高亮风格）
 UIBlurEffectStyleLight,亮风格
 UIBlurEffectStyleDark暗风格
 
//实现模糊效果
UIBlurEffect *blurEffrct =[UIBlurEffect effectWithStyle:UIBlurEffectStyleLight];

//毛玻璃视图
UIVisualEffectView *visualEffectView = [[UIVisualEffectView alloc]initWithEffect:blurEffrct];

visualEffectView.frame = CGRectMake(60, 100, 300, 500);

visualEffectView.alpha = 0.9;

[self.view addSubview:visualEffectView];
 */

NS_ASSUME_NONNULL_END

