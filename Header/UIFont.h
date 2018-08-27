//
//  UIFont.h
//  UIKit
//
//  Copyright (c) 2007-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIFontDescriptor.h>

@class UITraitCollection;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIFont : NSObject <NSCopying>

// Returns an instance of the font associated with the text style and scaled appropriately for the user's selected content size category. See UIFontDescriptor.h for the complete list.
//获取用户偏好字体
+ (UIFont *)preferredFontForTextStyle:(UIFontTextStyle)style NS_AVAILABLE_IOS(7_0);
// Returns an instance of the font associated with the text style and scaled appropriately for the content size category defined in the trait collection.
+ (UIFont *)preferredFontForTextStyle:(UIFontTextStyle)style compatibleWithTraitCollection:(nullable UITraitCollection *)traitCollection NS_AVAILABLE_IOS(10_0);

// Returns a font using CSS name matching semantics.
//使用CSS名称匹配语义返回字体
+ (nullable UIFont *)fontWithName:(NSString *)fontName size:(CGFloat)fontSize;

// Returns an array of font family names for all installed fonts
#if UIKIT_DEFINE_AS_PROPERTIES
//以数组的形式返回已安装的字体名称
@property(class, nonatomic, readonly) NSArray<NSString *> *familyNames;
#else
+ (NSArray<NSString *> *)familyNames;
#endif

// Returns an array of font names for the specified family name
//返回给定字型集名称的字体名字数组
+ (NSArray<NSString *> *)fontNamesForFamilyName:(NSString *)familyName;


// Some convenience methods to create system fonts

// Think carefully before using these methods. In most cases, a font returned by +preferredFontForTextStyle: will be more appropriate, and will respect the user's selected content size category.
//常规
+ (UIFont *)systemFontOfSize:(CGFloat)fontSize;
//粗体
+ (UIFont *)boldSystemFontOfSize:(CGFloat)fontSize;
//斜体
+ (UIFont *)italicSystemFontOfSize:(CGFloat)fontSize;

// Weights used here are analogous to those used with UIFontDescriptor's UIFontWeightTrait.
// See the UIFontWeight... constants in UIFontDescriptor.h for suggested values.
// The caveat above about the use of ...systemFont... methods applies to these methods too.
+ (UIFont *)systemFontOfSize:(CGFloat)fontSize weight:(CGFloat)weight NS_AVAILABLE_IOS(8_2);
+ (UIFont *)monospacedDigitSystemFontOfSize:(CGFloat)fontSize weight:(CGFloat)weight NS_AVAILABLE_IOS(9_0);


// Font attributes
//字体的family名称
@property(nonatomic,readonly,strong) NSString *familyName;
//字体名称
@property(nonatomic,readonly,strong) NSString *fontName;
//字体大小
@property(nonatomic,readonly)        CGFloat   pointSize;
//The top y-coordinate, offset from the baseline, of the receiver’s longest ascender. (read-only)
//接收者最长上升沿的顶点y坐标与基线偏移。 （只读）
@property(nonatomic,readonly)        CGFloat   ascender;
//The bottom y-coordinate, offset from the baseline, of the receiver’s longest descender. (read-only)
//接收器最长下降线的底线y坐标与基线偏移。 （只读）
@property(nonatomic,readonly)        CGFloat   descender;
//The receiver’s cap height information. (read-only)
//大写高度
@property(nonatomic,readonly)        CGFloat   capHeight;
//The x-height of the receiver. (read-only)
//比如'bxp'中字母'x'的高度,而不是'b','p'
@property(nonatomic,readonly)        CGFloat   xHeight;
//The height of text lines (measured in points). (read-only)
//设置行间的距离（行高）
@property(nonatomic,readonly)        CGFloat   lineHeight NS_AVAILABLE_IOS(4_0);
//The receiver’s leading information. (read-only)
//The leading value represents the spacing between lines of text and is measured (in points) from baseline to baseline.
//头间距
@property(nonatomic,readonly)        CGFloat   leading;

// Create a new font that is identical to the current font except the specified size
//Returns a font object that is the same as the receiver but which has the specified size instead.
//返回给定字体大小的字体对象
- (UIFont *)fontWithSize:(CGFloat)fontSize;

// Returns a font matching the font descriptor. If fontSize is greater than 0.0, it has precedence over UIFontDescriptorSizeAttribute in fontDescriptor.
//Returns a font matching the given font descriptor.
//返回符合给定字体描述的字体
+ (UIFont *)fontWithDescriptor:(UIFontDescriptor *)descriptor size:(CGFloat)pointSize NS_AVAILABLE_IOS(7_0);

// Returns a font descriptor which describes the font.
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) UIFontDescriptor *fontDescriptor NS_AVAILABLE_IOS(7_0);
#else
- (UIFontDescriptor *)fontDescriptor NS_AVAILABLE_IOS(7_0);
#endif

@end

NS_ASSUME_NONNULL_END


