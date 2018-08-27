//
//  NSAttributedString.h
//  UIKit
//
//  Copyright (c) 2011-2015, Apple Inc. All rights reserved.
//

#import <Foundation/NSAttributedString.h>
#import <UIKit/UIKitDefines.h>
@class NSFileWrapper;
@class NSURL;

NS_ASSUME_NONNULL_BEGIN
/************************ Attributes ************************/

// Predefined character attributes for text. If the key is not in the dictionary, then use the default values as described below.
//设置字体属性，默认值：字体：Helvetica(Neue) 字号：12
UIKIT_EXTERN NSString * const NSFontAttributeName NS_AVAILABLE(10_0, 6_0);                // UIFont, default Helvetica(Neue) 12
//设置文本段落排版格式（居中，换行模式，间距等诸多风格，取值为 NSParagraphStyle 对象
UIKIT_EXTERN NSString * const NSParagraphStyleAttributeName NS_AVAILABLE(10_0, 6_0);      // NSParagraphStyle, default defaultParagraphStyle
//设置字体颜色，取值为 UIColor对象，默认值为黑色
UIKIT_EXTERN NSString * const NSForegroundColorAttributeName NS_AVAILABLE(10_0, 6_0);     // UIColor, default blackColor
//设置字体所在区域背景颜色，取值为 UIColor对象，默认值为nil, 透明色
UIKIT_EXTERN NSString * const NSBackgroundColorAttributeName NS_AVAILABLE(10_0, 6_0);     // UIColor, default nil: no background
//设置连体属性，取值为NSNumber 对象(整数)，0 表示没有连体字符，1 表示使用默认的连体字符
UIKIT_EXTERN NSString * const NSLigatureAttributeName NS_AVAILABLE(10_0, 6_0);            // NSNumber containing integer, default 1: default ligatures, 0: no ligatures
//设定字符间距，取值为 NSNumber 对象（整数），正值间距加宽，负值间距变窄
UIKIT_EXTERN NSString * const NSKernAttributeName NS_AVAILABLE(10_0, 6_0);                // NSNumber containing floating point value, in points; amount to modify default kerning. 0 means kerning is disabled.
//设置删除线，取值为 NSNumber 对象（整数）
UIKIT_EXTERN NSString * const NSStrikethroughStyleAttributeName NS_AVAILABLE(10_0, 6_0);  // NSNumber containing integer, default 0: no strikethrough
//设置下划线，取值为 NSNumber 对象（整数），枚举常量 NSUnderlineStyle中的值，与删除线类似
UIKIT_EXTERN NSString * const NSUnderlineStyleAttributeName NS_AVAILABLE(10_0, 6_0);      // NSNumber containing integer, default 0: no underline
//填充部分颜色，不是字体颜色，取值为 UIColor 对象
UIKIT_EXTERN NSString * const NSStrokeColorAttributeName NS_AVAILABLE(10_0, 6_0);         // UIColor, default nil: same as foreground color
//设置笔画宽度，取值为 NSNumber 对象（整数），负值填充效果，正值中空效果
UIKIT_EXTERN NSString * const NSStrokeWidthAttributeName NS_AVAILABLE(10_0, 6_0);         // NSNumber containing floating point value, in percent of font point size, default 0: no stroke; positive for stroke alone, negative for stroke and fill (a typical value for outlined text would be 3.0)
//设置阴影属性，取值为 NSShadow 对象
UIKIT_EXTERN NSString * const NSShadowAttributeName NS_AVAILABLE(10_0, 6_0);              // NSShadow, default nil: no shadow
//设置文本特殊效果，取值为 NSString 对象，目前只有图版印刷效果可用
UIKIT_EXTERN NSString *const NSTextEffectAttributeName NS_AVAILABLE(10_10, 7_0);          // NSString, default nil: no text effect
//设置文本附件,取值为NSTextAttachment对象,常用于文字图片混排
UIKIT_EXTERN NSString * const NSAttachmentAttributeName NS_AVAILABLE(10_0, 7_0);          // NSTextAttachment, default nil
//设置链接属性，点击后调用浏览器打开指定URL地址
UIKIT_EXTERN NSString * const NSLinkAttributeName NS_AVAILABLE(10_0, 7_0);                // NSURL (preferred) or NSString
//设置基线偏移值，取值为 NSNumber （float）,正值上偏，负值下偏
UIKIT_EXTERN NSString * const NSBaselineOffsetAttributeName NS_AVAILABLE(10_0, 7_0);      // NSNumber containing floating point value, in points; offset from baseline, default 0
//设置下划线颜色，取值为 UIColor 对象，默认值为黑色
UIKIT_EXTERN NSString * const NSUnderlineColorAttributeName NS_AVAILABLE(10_0, 7_0);      // UIColor, default nil: same as foreground color
//设置删除线颜色，取值为 UIColor 对象，默认值为黑色
UIKIT_EXTERN NSString * const NSStrikethroughColorAttributeName NS_AVAILABLE(10_0, 7_0);  // UIColor, default nil: same as foreground color
//设置字形倾斜度，取值为 NSNumber （float）,正值右倾，负值左倾
UIKIT_EXTERN NSString * const NSObliquenessAttributeName NS_AVAILABLE(10_0, 7_0);         // NSNumber containing floating point value; skew to be applied to glyphs, default 0: no skew
//字体扁平化 设置文本横向拉伸属性，取值为 NSNumber （float）,正值横向拉伸文本，负值横向压缩文本
UIKIT_EXTERN NSString * const NSExpansionAttributeName NS_AVAILABLE(10_0, 7_0);           // NSNumber containing floating point value; log of expansion factor to be applied to glyphs, default 0: no expansion
//文字书写方向，从左向右书写或者从右向左书写
UIKIT_EXTERN NSString * const NSWritingDirectionAttributeName NS_AVAILABLE(10_6, 7_0);    // NSArray of NSNumbers representing the nested levels of writing direction overrides as defined by Unicode LRE, RLE, LRO, and RLO characters.  The control characters can be obtained by masking NSWritingDirection and NSWritingDirectionFormatType values.  LRE: NSWritingDirectionLeftToRight|NSWritingDirectionEmbedding, RLE: NSWritingDirectionRightToLeft|NSWritingDirectionEmbedding, LRO: NSWritingDirectionLeftToRight|NSWritingDirectionOverride, RLO: NSWritingDirectionRightToLeft|NSWritingDirectionOverride,
//设置文字排版方向，取值为 NSNumber 对象(整数)，0 表示横排文本，1 表示竖排文本
UIKIT_EXTERN NSString * const NSVerticalGlyphFormAttributeName NS_AVAILABLE(10_7, 6_0);   // An NSNumber containing an integer value.  0 means horizontal text.  1 indicates vertical text.  If not specified, it could follow higher-level vertical orientation settings.  Currently on iOS, it's always horizontal.  The behavior for any other value is undefined.

/*
 参考自:http://www.cnblogs.com/mylizh/p/3975737.html
 
 UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width - 40, 50)];
 label.textAlignment = NSTextAlignmentCenter;
 label.center = self.view.center;
 [self.view addSubview:label];
 
 NSMutableAttributedString *attributedString = [[NSMutableAttributedString alloc] initWithString:@"caiiiac.github.io"];
 
 //字体 颜色 背景色
 NSDictionary * attris = @{NSForegroundColorAttributeName:[UIColor whiteColor],NSBackgroundColorAttributeName:[UIColor grayColor],NSFontAttributeName:[UIFont boldSystemFontOfSize:30]};
 
 
 //下划线
 NSDictionary * attris = @{NSFontAttributeName:[UIFont boldSystemFontOfSize:30],NSForegroundColorAttributeName:[UIColor orangeColor],NSUnderlineStyleAttributeName:@(NSUnderlineStyleSingle),                             NSUnderlineColorAttributeName:[UIColor blueColor],};
 
 //描边
 NSDictionary * attris = @{NSFontAttributeName:[UIFont boldSystemFontOfSize:30],NSForegroundColorAttributeName:[UIColor whiteColor],NSStrokeColorAttributeName:[UIColor blueColor],NSStrokeWidthAttributeName:@(2)};
 
 //阴影
 NSShadow * shadow = [[NSShadow alloc] init];
 shadow.shadowColor = [UIColor blueColor];
 shadow.shadowBlurRadius = 4.0;
 shadow.shadowOffset = CGSizeMake(2.0, 2.0);
 NSDictionary * attris = @{NSFontAttributeName:[UIFont systemFontOfSize:30],NSShadowAttributeName:shadow};
 
 //字符间隔
 NSDictionary * attris = @{NSKernAttributeName:@(5), NSFontAttributeName:[UIFont systemFontOfSize:30]};
 
 //字体倾斜
 NSDictionary * attris = @{NSObliquenessAttributeName:@(0.8), NSFontAttributeName:[UIFont systemFontOfSize:30]};
 
 //字体扁平化
 NSDictionary * attris = @{NSExpansionAttributeName:@(1.0), NSFontAttributeName:[UIFont systemFontOfSize:30]};
 
 
 //添加图片
 NSTextAttachment * attach = [[NSTextAttachment alloc] init];
 attach.image = [UIImage imageNamed:@"收藏后"];
 attach.bounds = CGRectMake(2, -4, 20, 20);
 NSAttributedString * imageStr = [NSAttributedString attributedStringWithAttachment:attach];
 [attributedString appendAttributedString:imageStr];
 
 
 [attributedString setAttributes:attris range:NSMakeRange(0,attributedString.length)];
 label.attributedText = attributedString;
 
 自定义view:
 NSMutableAttributedString * attributeStr = [[NSMutableAttributedString alloc] initWithString:@"绘图风格（居中，换行模式，间距等诸多风格），value是NSParagraphStyle对象"];
 NSMutableParagraphStyle * paragraphStyle = [[NSMutableParagraphStyle alloc] init];
 paragraphStyle.alignment = NSTextAlignmentRight;
 paragraphStyle.headIndent = 4.0;
 paragraphStyle.lineBreakMode = NSLineBreakByCharWrapping;
 paragraphStyle.lineSpacing = 2.0;
 NSDictionary * attributes = @{NSParagraphStyleAttributeName:paragraphStyle};
 [attributeStr setAttributes:attributes range:NSMakeRange(0, attributeStr.length)];
 [attributeStr drawInRect:self.bounds];

 */


/************************ Attribute values ************************/
// This defines currently supported values for NSUnderlineStyleAttributeName and NSStrikethroughStyleAttributeName. NSUnderlineStyle*, NSUnderlinePattern*, and NSUnderlineByWord are or'ed together to produce an underline style.
//下面定义了下划线、删除线支持的样式
typedef NS_ENUM(NSInteger, NSUnderlineStyle) {
    //无下划线
    NSUnderlineStyleNone                                    = 0x00,
    // 设置删除线为细单实线
    NSUnderlineStyleSingle                                  = 0x01,
    // 设置删除线为粗单实线
    NSUnderlineStyleThick NS_ENUM_AVAILABLE(10_0, 7_0)      = 0x02,
    // 设置删除线为细双实线
    NSUnderlineStyleDouble NS_ENUM_AVAILABLE(10_0, 7_0)     = 0x09,
    //设置下划线／删除线样式为连续的实线
    NSUnderlinePatternSolid NS_ENUM_AVAILABLE(10_0, 7_0)      = 0x0000,
    //设置下划线／删除线样式为点，也就是虚线，比如这样：－－－－－－
    NSUnderlinePatternDot NS_ENUM_AVAILABLE(10_0, 7_0)        = 0x0100,
    //设置下划线／删除线样式为破折号，比如这样：—— —— ——
    NSUnderlinePatternDash NS_ENUM_AVAILABLE(10_0, 7_0)       = 0x0200,
    //设置下划线／删除线样式为连续的破折号和点，比如这样：——－——－——－
    NSUnderlinePatternDashDot NS_ENUM_AVAILABLE(10_0, 7_0)    = 0x0300,
    //设置下划线／删除线样式为连续的破折号、点、点，比如：——－－——－－——－－
    NSUnderlinePatternDashDotDot NS_ENUM_AVAILABLE(10_0, 7_0) = 0x0400,
    //在有空格的地方不设置下划线／删除线
    NSUnderlineByWord NS_ENUM_AVAILABLE(10_0, 7_0)            = 0x8000
} NS_ENUM_AVAILABLE(10_0, 6_0);

// NSWritingDirectionFormatType values used by NSWritingDirectionAttributeName. It is or'ed with either NSWritingDirectionLeftToRight or NSWritingDirectionRightToLeft. Can specify the formatting controls defined by Unicode Bidirectional Algorithm.
typedef NS_ENUM(NSInteger, NSWritingDirectionFormatType) {
    NSWritingDirectionEmbedding     = (0 << 1),
    NSWritingDirectionOverride      = (1 << 1)
} NS_ENUM_AVAILABLE(10_11, 9_0);

// NSTextEffectAttributeName values
UIKIT_EXTERN NSString *const NSTextEffectLetterpressStyle NS_AVAILABLE(10_10, 7_0);


/************************ Attribute fixing ************************/

@interface NSMutableAttributedString (NSAttributedStringAttributeFixing)
// This method fixes attribute inconsistencies inside range.  It ensures NSFontAttributeName covers the characters, NSParagraphStyleAttributeName is only changing at paragraph boundaries, and NSTextAttachmentAttributeName is assigned to NSAttachmentCharacter.  NSTextStorage automatically invokes this method via -ensureAttributesAreFixedInRange:.
- (void)fixAttributesInRange:(NSRange)range NS_AVAILABLE(10_0, 7_0);

@end


/************************ Document formats ************************/

// Supported document types for the NSDocumentTypeDocumentAttribute key in the document attributes dictionary.
// 普通文本
UIKIT_EXTERN NSString * const NSPlainTextDocumentType NS_AVAILABLE(10_0, 7_0);
// 富文本
UIKIT_EXTERN NSString * const NSRTFTextDocumentType NS_AVAILABLE(10_0, 7_0);
// 带附件的富文本
UIKIT_EXTERN NSString * const NSRTFDTextDocumentType NS_AVAILABLE(10_0, 7_0);
// HTML
UIKIT_EXTERN NSString * const NSHTMLTextDocumentType NS_AVAILABLE(10_0, 7_0);

// Keys for NSLayoutOrientationSectionsAttribute.
// 文字展示的方向
UIKIT_EXTERN NSString * const NSTextLayoutSectionOrientation NS_AVAILABLE(10_7, 7_0); // NSNumber containing NSTextLayoutOrientation value. default: NSTextLayoutOrientationHorizontal
// 字符的范围
UIKIT_EXTERN NSString * const NSTextLayoutSectionRange NS_AVAILABLE(10_7, 7_0); // NSValue containing NSRange representing a character range. default: a range covering the whole document


// Keys for options and document attributes dictionaries.  They are in and out document properties used by both read/write methods.

UIKIT_EXTERN NSString * const NSDocumentTypeDocumentAttribute NS_AVAILABLE(10_0, 7_0);  // @"DocumentType", one of the document types declared above.  For reader methods, this key in options can specify the document type for interpreting the contents.  Upon return, the document attributes can contain this key for indicating the actual format used to read the contents.  For write methods, this key specifies the format for generating the data.


// NSPlainTextDocumentType document attributes
// 普通文本的编码
UIKIT_EXTERN NSString * const NSCharacterEncodingDocumentAttribute NS_AVAILABLE(10_0, 7_0);  // @"CharacterEncoding", NSNumber containing integer specifying NSStringEncoding for the file; default for plain text is the default encoding.  This key in options can specify the string encoding for reading the data.  Upon return, the document attributes can contain the actual encoding used.  For writing methods, this value is used for generating the plain text data.
UIKIT_EXTERN NSString * const NSDefaultAttributesDocumentAttribute NS_AVAILABLE(10_11, 7_0);  // @"DefaultAttributes", NSDictionary containing attributes to be applied to plain files.  Used by reader methods.  This key in options can specify the default attributes applied to the entire document contents.  The document attributes can contain this key indicating the actual attributes used.


// NSRTFTextDocumentType and NSRTFDTextDocumentType document attributes
// Document dimension
// They are document attributes used by read/write methods.
UIKIT_EXTERN NSString * const NSPaperSizeDocumentAttribute NS_AVAILABLE(10_0, 7_0);  // @"PaperSize", NSValue containing CGSize (in points)
UIKIT_EXTERN NSString * const NSPaperMarginDocumentAttribute NS_AVAILABLE_IOS(7_0);  // @"PaperMargin", NSValue containing UIEdgeInsets

UIKIT_EXTERN NSString * const NSViewSizeDocumentAttribute NS_AVAILABLE(10_0, 7_0);  // @"ViewSize", NSValue containing CGSize (in points)
UIKIT_EXTERN NSString * const NSViewZoomDocumentAttribute NS_AVAILABLE(10_0, 7_0);  // @"ViewZoom", NSNumber containing floating point value (100 == 100% zoom)
UIKIT_EXTERN NSString * const NSViewModeDocumentAttribute NS_AVAILABLE(10_0, 7_0);  // @"ViewMode", NSNumber containing integer; 0 = normal; 1 = page layout

// Document settings
// They are document attributes used by read/write methods.
UIKIT_EXTERN NSString * const NSReadOnlyDocumentAttribute NS_AVAILABLE(10_0, 7_0);  // @"ReadOnly", NSNumber containing integer; if missing, or 0 or negative, not readonly; 1 or more, readonly. Note that this has nothing to do with the file system protection on the file, but instead, on how the file should be displayed to the user
UIKIT_EXTERN NSString * const NSBackgroundColorDocumentAttribute NS_AVAILABLE(10_0, 7_0);  // @"BackgroundColor", UIColor, representing the document-wide page background color
UIKIT_EXTERN NSString * const NSHyphenationFactorDocumentAttribute NS_AVAILABLE(10_0, 7_0);  // @"HyphenationFactor", NSNumber containing floating point value (0=off, 1=full hyphenation)
UIKIT_EXTERN NSString * const NSDefaultTabIntervalDocumentAttribute NS_AVAILABLE(10_0, 7_0);  // @"DefaultTabInterval", NSNumber containing floating point value, representing the document-wide default tab stop interval, in points
UIKIT_EXTERN NSString * const NSTextLayoutSectionsAttribute NS_AVAILABLE(10_7, 7_0);  // NSArray of dictionaries.  Each dictionary describing a layout orientation section.  The dictionary can have two attributes: NSTextLayoutSectionOrientation and NSTextLayoutSectionRange.  When there is a gap between sections, it's assumed to have NSTextLayoutOrientationHorizontal.



@interface NSAttributedString (NSAttributedStringDocumentFormats)
// Methods initializing the receiver contents with an external document data.  options specify document attributes for interpreting the document contents.  NSDocumentTypeDocumentAttribute, NSCharacterEncodingDocumentAttribute, and NSDefaultAttributesDocumentAttribute are supported options key.  When they are not specified, these methods will examine the data and do their best to detect the appropriate attributes.  If dict is non-NULL, it will return a dictionary with various document-wide attributes accessible via NS...DocumentAttribute keys.
- (nullable instancetype)initWithURL:(NSURL *)url options:(NSDictionary<NSString *, id> *)options documentAttributes:(NSDictionary<NSString *, id> * __nullable * __nullable)dict error:(NSError **)error NS_AVAILABLE(10_4, 9_0);
- (nullable instancetype)initWithData:(NSData *)data options:(NSDictionary<NSString *, id> *)options documentAttributes:(NSDictionary<NSString *, id> * __nullable * __nullable)dict error:(NSError **)error NS_AVAILABLE(10_0, 7_0);

// Generates an NSData object for the receiver contents in range.  It requires a document attributes dict specifying at least the NSDocumentTypeDocumentAttribute to determine the format to be written.
- (nullable NSData *)dataFromRange:(NSRange)range documentAttributes:(NSDictionary<NSString *, id> *)dict error:(NSError **)error NS_AVAILABLE(10_0, 7_0);

// Returns an NSFileWrapper object for the receiver contents in range.  It requires a document attributes dict specifying at least the NSDocumentTypeDocumentAttribute to determine the format to be written.  The method returns a directory file wrapper for those document types represented by a file package such as NSRTFDTextDocumentType; otherwise, it returns a regular-file file wrapper.
- (nullable NSFileWrapper *)fileWrapperFromRange:(NSRange)range documentAttributes:(NSDictionary<NSString *, id> *)dict error:(NSError **)error NS_AVAILABLE(10_0, 7_0);

@end

@interface NSMutableAttributedString (NSMutableAttributedStringDocumentFormats)
// Methods replacing the receiver contents with an external document data.  options specify document attributes for interpreting the document contents.  NSDocumentTypeDocumentAttribute, NSCharacterEncodingDocumentAttribute, and NSDefaultAttributesDocumentAttribute are supported options key.  When they are not specified, these methods will examine the data and do their best to detect the appropriate attributes.  If dict is non-NULL, it will return a dictionary with various document-wide attributes accessible via NS...DocumentAttribute keys.
- (BOOL)readFromURL:(NSURL *)url options:(NSDictionary<NSString *, id> *)opts documentAttributes:(NSDictionary<NSString *, id> * __nullable * __nullable)dict error:(NSError **)error  NS_AVAILABLE(10_11, 9_0);
- (BOOL)readFromData:(NSData *)data options:(NSDictionary<NSString *, id> *)opts documentAttributes:(NSDictionary<NSString *, id> * __nullable * __nullable)dict error:(NSError **)error NS_AVAILABLE(10_0, 7_0);
@end


/************************ Misc methods ************************/
@interface NSAttributedString (NSAttributedStringKitAdditions)
// Returns YES if the receiver contains a property configured (NSAttachmentAttributeName with NSAttachmentCharacter) in range
- (BOOL)containsAttachmentsInRange:(NSRange)range NS_AVAILABLE(10_11, 9_0);
@end

/************************ Deprecated ************************/

typedef NS_ENUM(NSInteger, NSTextWritingDirection) {
    NSTextWritingDirectionEmbedding     = (0 << 1),
    NSTextWritingDirectionOverride      = (1 << 1)
} NS_ENUM_DEPRECATED_IOS(7_0, 9_0, "Use NSWritingDirectionFormatType instead") __TVOS_PROHIBITED;

@interface NSAttributedString(NSDeprecatedKitAdditions)
- (nullable instancetype)initWithFileURL:(NSURL *)url options:(NSDictionary *)options documentAttributes:(NSDictionary* __nullable * __nullable)dict error:(NSError **)error NS_DEPRECATED_IOS(7_0, 9_0, "Use -initWithURL:options:documentAttributes:error: instead") __TVOS_PROHIBITED;
@end

@interface NSMutableAttributedString (NSDeprecatedKitAdditions)
- (BOOL)readFromFileURL:(NSURL *)url options:(NSDictionary *)opts documentAttributes:(NSDictionary* __nullable * __nullable)dict error:(NSError **)error NS_DEPRECATED_IOS(7_0, 9_0, "Use -readFromURL:options:documentAttributes:error: instead") __TVOS_PROHIBITED;
@end
NS_ASSUME_NONNULL_END
