//
//  UILabel.h
//  UIKit
//
//  Copyright (c) 2006-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIContentSizeCategoryAdjusting.h>

NS_ASSUME_NONNULL_BEGIN

@class UIColor, UIFont;

NS_CLASS_AVAILABLE_IOS(2_0) @interface UILabel : UIView <NSCoding, UIContentSizeCategoryAdjusting>
//设置和读取文本内容,默认为nil
/*
 竖排文字显示每个文字加一个换行符，这是最方便和简单的实现方式。
 label.text = @"请\n竖\n直\n方\n向\n排\n列";
 label.numberOfLines = [label.text length];
 */
@property(nullable, nonatomic,copy)   NSString           *text;            // default is nil
//设置字体大小，默认17
@property(null_resettable, nonatomic,strong) UIFont      *font;            // default is nil (system font 17 plain)
//设置文字颜色，默认为黑色
@property(null_resettable, nonatomic,strong) UIColor     *textColor;       // default is nil (text draws black)
//设置阴影颜色
@property(nullable, nonatomic,strong) UIColor            *shadowColor;     // default is nil (no shadow)
//设置阴影偏移量
@property(nonatomic)        CGSize             shadowOffset;    // default is CGSizeMake(0, -1) -- a top shadow
//设置标签文本对齐方式。
@property(nonatomic)        NSTextAlignment    textAlignment;   // default is NSTextAlignmentNatural (before iOS 9, the default was NSTextAlignmentLeft)
//设置文字过长时的显示格式
/*
 label.lineBreakMode = NSLineBreakByCharWrapping;以字符为显示单位显
 示，后面部分省略不显示。
 label.lineBreakMode = NSLineBreakByClipping;剪切与文本宽度相同的内
 容长度，后半部分被删除。
 label.lineBreakMode = NSLineBreakByTruncatingHead;前面部分文字
 以……方式省略，显示尾部文字内容。
 label.lineBreakMode = NSLineBreakByTruncatingMiddle;中间的内容
 以……方式省略，显示头尾的文字内容。
 label.lineBreakMode = NSLineBreakByTruncatingTail;结尾部分的内容
 以……方式省略，显示头的文字内容。
 label.lineBreakMode = NSLineBreakByWordWrapping;以单词为显示单位显
 示，后面部分省略不显示。
 */
@property(nonatomic)        NSLineBreakMode    lineBreakMode;   // default is NSLineBreakByTruncatingTail. used for single and multiple lines of text

// the underlying attributed string drawn by the label, if set, the label ignores the properties above.
//设置标签属性文本。
/*
 NSMutableAttributedString*attriString=[[NSMutableAttributedString alloc]initWithString:@"this is test!"];
 [attriString addAttributes:@{NSForegroundColorAttributeName:[UIColor redColor]} range:NSMakeRange(0, 4)];
 [attriString addAttributes:@{NSForegroundColorAttributeName:[UIColor greenColor]} range:NSMakeRange(8, 4)];
 //改变this的字体，value必须是一个CTFontRef
 [attriString addAttribute:(NSString *)kCTFontAttributeName
 value:(id)CFBridgingRelease(CTFontCreateWithName((CFStringRef)[UIFont boldSystemFontOfSize:14].fontName,14,NULL))range:NSMakeRange(0, 4)];
 //给this加上下划线，value可以在指定的枚举中选择
 [attriString addAttribute:(NSString *)kCTUnderlineStyleAttributeName
 value:(id)[NSNumber numberWithInt:kCTUnderlineStyleDouble]
 range:NSMakeRange(0, 4)];
 UILabel*Label=[[UILabel alloc]initWithFrame:CGRectMake(100, 100, 200, 30)];
 Label.attributedText=attriString;
 [self.view addSubview:Label];
 */
@property(nullable, nonatomic,copy)   NSAttributedString *attributedText NS_AVAILABLE_IOS(6_0);  // default is nil

// the 'highlight' property is used by subclasses for such things as pressed states. it's useful to make it part of the base class as a user property
//高亮显示时的文本颜色
@property(nullable, nonatomic,strong)               UIColor *highlightedTextColor; // default is nil
//是否高亮显示
@property(nonatomic,getter=isHighlighted) BOOL     highlighted;          // default is NO
//是否可以与用户交互
@property(nonatomic,getter=isUserInteractionEnabled) BOOL userInteractionEnabled;  // default is NO
//只是决定了Label的绘制方式，将它设置为NO将会使文本变暗，表示它没有激活，这时向它设置颜色值是无效的。
@property(nonatomic,getter=isEnabled)                BOOL enabled;                 // default is YES. changes how the label is drawn

// this determines the number of lines to draw and what to do when sizeToFit is called. default value is 1 (single line). A value of 0 means no limit
// if the height of the text reaches the # of lines or the height of the view is less than the # of lines allowed, the text will be
// truncated using the line break mode.
//标签最多显示行数,如果为0则表示多行。
@property(nonatomic) NSInteger numberOfLines;

// these next 3 property allow the label to be autosized to fit a certain width by scaling the font size(s) by a scaling factor >= the minimum scaling factor
// and to specify how the text baseline moves when it needs to shrink the font.
//设置字体大小适应label宽度
@property(nonatomic) BOOL adjustsFontSizeToFitWidth;         // default is NO
//如果adjustsFontSizeToFitWidth属性设置为YES，这个属性就来控制文本基线的行为。
/*
 UIBaselineAdjustmentAlignBaselines = 0,默认，文本最上端与中线对齐。
 UIBaselineAdjustmentAlignCenters,  文本中线与label中线对齐。
 UIBaselineAdjustmentNone, 文本最低端与label中线对齐。
 */
@property(nonatomic) UIBaselineAdjustment baselineAdjustment; // default is UIBaselineAdjustmentAlignBaselines
//设置最小收缩比例，如果Label宽度小于文字长度时，文字进行收缩，收缩超过比例后，停止收缩。
@property(nonatomic) CGFloat minimumScaleFactor NS_AVAILABLE_IOS(6_0); // default is 0.0


// Tightens inter-character spacing in attempt to fit lines wider than the available space if the line break mode is one of the truncation modes before starting to truncate.
// The maximum amount of tightening performed is determined by the system based on contexts such as font, line width, etc.
//When this property is set to YES, the label tightens inter-character spacing of its text before allowing any truncation to occur. The label determines the maximum amount of tightening automatically based on the font, current line width, line break mode, and other relevant information.
//如果换行模式是开始截断之前的截断模式之一，请尝试匹配宽于可用空间的字符间距。
//执行的最大紧固量由系统基于字体，行宽等上下文确定。
//当此属性设置为YES时，标签会在允许任何截断发生之前收紧文本的字符间距。 标签根据字体，当前行宽，换行模式和其他相关信息自动确定最大收紧量。
@property(nonatomic) BOOL allowsDefaultTighteningForTruncation NS_AVAILABLE_IOS(9_0); // default is NO

// override points. can adjust rect before calling super.
// label has default content mode of UIViewContentModeRedraw
//Returns the drawing rectangle for the label’s text.
//覆盖点。 在调用super之前可以调整rect。
// label具有UIViewContentModeRedraw的默认内容模式
//返回标签文字的绘图矩形。
- (CGRect)textRectForBounds:(CGRect)bounds limitedToNumberOfLines:(NSInteger)numberOfLines;
//Draws the receiver’s text (or its shadow) in the specified rectangle.
//在指定的矩形中绘制接收者的文本（或其阴影）。
- (void)drawTextInRect:(CGRect)rect;


// Support for constraint-based layout (auto layout)
// If nonzero, this is used when determining -intrinsicContentSize for multiline labels
//这个属性是用来设置多行label的最大宽度的
//当自动布局的时候约束这个label的时候这个属性会起作用
//在自动布局添加约束中，若文本超过了指定的最大宽度的时候 文本会另起一行 从而增加了label的高度
@property(nonatomic) CGFloat preferredMaxLayoutWidth NS_AVAILABLE_IOS(6_0);


// deprecated:
//设置最小收缩字号，如果Label宽度小于文字长度时，文字字号减小，低于设定字号后，不再减小。6.0以后不再使用了。
@property(nonatomic) CGFloat minimumFontSize NS_DEPRECATED_IOS(2_0, 6_0) __TVOS_PROHIBITED; // deprecated - use minimumScaleFactor. default is 0.0

// Non-functional.  Hand tune by using NSKernAttributeName to affect tracking, or consider using the allowsDefaultTighteningForTruncation property.
//改变字母之间的间距来适应Label大小
@property(nonatomic) BOOL adjustsLetterSpacingToFitWidth NS_DEPRECATED_IOS(6_0,7_0) __TVOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
