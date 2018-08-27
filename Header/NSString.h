/*	NSString.h
	Copyright (c) 1994-2016, Apple Inc. All rights reserved.
 */

typedef unsigned short unichar;

#import <limits.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <stdarg.h>

@class NSData, NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSCharacterSet, NSURL, NSError, NSLocale;

NS_ASSUME_NONNULL_BEGIN

/* These options apply to the various search/find and comparison methods (except where noted).
 */
typedef NS_OPTIONS(NSUInteger, NSStringCompareOptions) {
    //比较不区分大小写
    NSCaseInsensitiveSearch = 1,
    //比较区分大小写
    NSLiteralSearch = 2,		/* Exact character-by-character equivalence */
    //从字符串末尾开始查询搜索
    NSBackwardsSearch = 4,		/* Search from end of source string */
    //搜索有限制范围的字符串
    NSAnchoredSearch = 8,		/* Search is limited to start (or end, if NSBackwardsSearch) of source string */
    //根据字符串里的数字来计算顺序
    NSNumericSearch = 64,		/* Added in 10.2; Numbers within strings are compared using numeric value, that is, Foo2.txt < Foo7.txt < Foo25.txt; only applies to compare methods, not find */
    NSDiacriticInsensitiveSearch NS_ENUM_AVAILABLE(10_5, 2_0) = 128, /* If specified, ignores diacritics (o-umlaut == o) */
    //可以忽略字符串的宽度（长度）
    NSWidthInsensitiveSearch NS_ENUM_AVAILABLE(10_5, 2_0) = 256, /* If specified, ignores width differences ('a' == UFF41) */
    //忽略不区分大小写比较的选项
    NSForcedOrderingSearch NS_ENUM_AVAILABLE(10_5, 2_0) = 512, /* If specified, comparisons are forced to return either NSOrderedAscending or NSOrderedDescending if the strings are equivalent but not strictly equal, for stability when sorting (e.g. "aaa" > "AAA" with NSCaseInsensitiveSearch specified) */
    NSRegularExpressionSearch NS_ENUM_AVAILABLE(10_7, 3_2) = 1024    /* Applies to rangeOfString:..., stringByReplacingOccurrencesOfString:..., and replaceOccurrencesOfString:... methods only; the search string is treated as an ICU-compatible regular expression; if set, no other options can apply except NSCaseInsensitiveSearch and NSAnchoredSearch */
};

/* Note that in addition to the values explicitly listed below, NSStringEncoding supports encodings provided by CFString.
 See CFStringEncodingExt.h for a list of these encodings.
 See CFString.h for functions which convert between NSStringEncoding and CFStringEncoding.
 */
typedef NSUInteger NSStringEncoding;
NS_ENUM(NSStringEncoding) {
    NSASCIIStringEncoding = 1,		/* 0..127 only */
    NSNEXTSTEPStringEncoding = 2,
    NSJapaneseEUCStringEncoding = 3,
    NSUTF8StringEncoding = 4,
    NSISOLatin1StringEncoding = 5,
    NSSymbolStringEncoding = 6,
    NSNonLossyASCIIStringEncoding = 7,
    NSShiftJISStringEncoding = 8,          /* kCFStringEncodingDOSJapanese */
    NSISOLatin2StringEncoding = 9,
    NSUnicodeStringEncoding = 10,
    NSWindowsCP1251StringEncoding = 11,    /* Cyrillic; same as AdobeStandardCyrillic */
    NSWindowsCP1252StringEncoding = 12,    /* WinLatin1 */
    NSWindowsCP1253StringEncoding = 13,    /* Greek */
    NSWindowsCP1254StringEncoding = 14,    /* Turkish */
    NSWindowsCP1250StringEncoding = 15,    /* WinLatin2 */
    NSISO2022JPStringEncoding = 21,        /* ISO 2022 Japanese encoding for e-mail */
    NSMacOSRomanStringEncoding = 30,
    
    NSUTF16StringEncoding = NSUnicodeStringEncoding,      /* An alias for NSUnicodeStringEncoding */
    
    NSUTF16BigEndianStringEncoding = 0x90000100,          /* NSUTF16StringEncoding encoding with explicit endianness specified */
    NSUTF16LittleEndianStringEncoding = 0x94000100,       /* NSUTF16StringEncoding encoding with explicit endianness specified */
    
    NSUTF32StringEncoding = 0x8c000100,
    NSUTF32BigEndianStringEncoding = 0x98000100,          /* NSUTF32StringEncoding encoding with explicit endianness specified */
    NSUTF32LittleEndianStringEncoding = 0x9c000100        /* NSUTF32StringEncoding encoding with explicit endianness specified */
};
//字符串编码 typedefNSUInteger NSStringEncoding; 字符串编码转换条件option，下面指定缓冲区转换会用到
typedef NS_OPTIONS(NSUInteger, NSStringEncodingConversionOptions) {
    NSStringEncodingConversionAllowLossy = 1,
    NSStringEncodingConversionExternalRepresentation = 2
};


@interface NSString : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

#pragma mark *** String funnel methods ***

/* NSString primitives. A minimal subclass of NSString just needs to implement these two, along with an init method appropriate for that subclass. We also recommend overriding getCharacters:range: for performance.
 */
//只读属性字符串长度length
@property (readonly) NSUInteger length;
//选取字符串对应下标的字符
- (unichar)characterAtIndex:(NSUInteger)index;

/* The initializers available to subclasses. See further below for additional init methods.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end
    
    @interface NSString (NSStringExtensionMethods)

#pragma mark *** Substrings ***

/* To avoid breaking up character sequences such as Emoji, you can do:
 [str substringFromIndex:[str rangeOfComposedCharacterSequenceAtIndex:index].location]
 [str substringToIndex:NSMaxRange([str rangeOfComposedCharacterSequenceAtIndex:index])]
 [str substringWithRange:[str rangeOfComposedCharacterSequencesForRange:range]
 */
//从指定下标处开始截取到字符串尾的子字符串
- (NSString *)substringFromIndex:(NSUInteger)from;
//从索引0第一个字符串开始，截取指定长度的字符串
- (NSString *)substringToIndex:(NSUInteger)to;
//截取字符串的指定段，返回值为NSString
- (NSString *)substringWithRange:(NSRange)range;                // Use with rangeOfComposedCharacterSequencesForRange: to avoid breaking up character sequences

- (void)getCharacters:(unichar *)buffer range:(NSRange)range;   // Use with rangeOfComposedCharacterSequencesForRange: to avoid breaking up character sequences


#pragma mark *** String comparison and equality ***

/* In the compare: methods, the range argument specifies the subrange, rather than the whole, of the receiver to use in the comparison. The range is not applied to the search string.  For example, [@"AB" compare:@"ABC" options:0 range:NSMakeRange(0,1)] compares "A" to "ABC", not "A" to "A", and will return NSOrderedAscending. It is an error to specify a range that is outside of the receiver's bounds, and an exception may be raised.
 */
//比较两个字符串
- (NSComparisonResult)compare:(NSString *)string;
//比较两个字符串，并加上条件
- (NSComparisonResult)compare:(NSString *)string options:(NSStringCompareOptions)mask;
//比较两个字符串，并加上某些条件到指定段
- (NSComparisonResult)compare:(NSString *)string options:(NSStringCompareOptions)mask range:(NSRange)rangeOfReceiverToCompare;
//比较两个字符串，并加上某些条件还有本地化语言环境，在指定段进行比较
- (NSComparisonResult)compare:(NSString *)string options:(NSStringCompareOptions)mask range:(NSRange)rangeOfReceiverToCompare locale:(nullable id)locale; // locale arg used to be a dictionary pre-Leopard. We now accept NSLocale. Assumes the current locale if non-nil and non-NSLocale. nil continues to mean canonical compare, which doesn't depend on user's locale choice.
//Returns the result of invoking compare:options: with NSCaseInsensitiveSearch as the only option.
//不区分大小写比较字符串
- (NSComparisonResult)caseInsensitiveCompare:(NSString *)string;
//本地化比较字符串
- (NSComparisonResult)localizedCompare:(NSString *)string;
//不区分大小写以及本地化比较字符串
- (NSComparisonResult)localizedCaseInsensitiveCompare:(NSString *)string;

/* localizedStandardCompare:, added in 10.6, should be used whenever file names or other strings are presented in lists and tables where Finder-like sorting is appropriate.  The exact behavior of this method may be tweaked in future releases, and will be different under different localizations, so clients should not depend on the exact sorting order of the strings.
 */
//Compares strings as sorted by the Finder.
- (NSComparisonResult)localizedStandardCompare:(NSString *)string NS_AVAILABLE(10_6, 4_0);
//比较两个字符串是否相等
- (BOOL)isEqualToString:(NSString *)aString;


#pragma mark *** String searching ***

/* These perform locale unaware prefix or suffix match. If you need locale awareness, use rangeOfString:options:range:locale:, passing NSAnchoredSearch (or'ed with NSBackwardsSearch for suffix, and NSCaseInsensitiveSearch|NSDiacriticInsensitiveSearch if needed) for options, NSMakeRange(0, [receiver length]) for range, and [NSLocale currentLocale] for locale.
 */
//字符串是否以str开头
- (BOOL)hasPrefix:(NSString *)str;
//字符串是否以str结尾
- (BOOL)hasSuffix:(NSString *)str;

- (NSString *)commonPrefixWithString:(NSString *)str options:(NSStringCompareOptions)mask;

/* Simple convenience methods for string searching. containsString: returns YES if the target string is contained within the receiver. Same as calling rangeOfString:options: with no options, thus doing a case-sensitive, locale-unaware search. localizedCaseInsensitiveContainsString: is the case-insensitive variant which also takes the current locale into effect. Starting in 10.11 and iOS9, the new localizedStandardRangeOfString: or localizedStandardContainsString: APIs are even better convenience methods for user level searching.   More sophisticated needs can be achieved by calling rangeOfString:options:range:locale: directly.
 */
//判断当前字符串是否包含字符串str，返回值Bool
- (BOOL)containsString:(NSString *)str NS_AVAILABLE(10_10, 8_0);
//这是iOS8的新特性API 判断字符串A是否包含字符串B，不区分大小写，返回Bool
/*
 例：NSString * stringA = @“abcd”;
 NSString * stringB = @“d”;
 BOOl  test = [stringA localizedCaseInsensitiveContainsString:stringB];
 输出打印值 YES
 */
- (BOOL)localizedCaseInsensitiveContainsString:(NSString *)str NS_AVAILABLE(10_10, 8_0);

/* The following two are the most appropriate methods for doing user-level string searches, similar to how searches are done generally in the system.  The search is locale-aware, case and diacritic insensitive. As with other APIs, "standard" in the name implies "system default behavior," so the exact list of search options applied may change over time.  If you need more control over the search options, please use the rangeOfString:options:range:locale: method. You can pass [NSLocale currentLocale] for searches in user's locale.
 */
- (BOOL)localizedStandardContainsString:(NSString *)str NS_AVAILABLE(10_11, 9_0);
- (NSRange)localizedStandardRangeOfString:(NSString *)str NS_AVAILABLE(10_11, 9_0);

/* These methods perform string search, looking for the searchString within the receiver string.  These return length==0 if the target string is not found. So, to check for containment: ([str rangeOfString:@"target"].length > 0).  Note that the length of the range returned by these methods might be different than the length of the target string, due composed characters and such.
 
 Note that the first three methods do not take locale arguments, and perform the search in a non-locale aware fashion, which is not appropriate for user-level searching. To do user-level string searching, use the last method, specifying locale:[NSLocale currentLocale], or better yet, use localizedStandardRangeOfString: or localizedStandardContainsString:.
 
 The range argument specifies the subrange, rather than the whole, of the receiver to use in the search.  It is an error to specify a range that is outside of the receiver's bounds, and an exception may be raised.
 */
//搜索一个字符串是否包含某个字符 rangeOfString前面的参数是要被搜索的字符串，后面的是要搜索的字符,并返回位置
- (NSRange)rangeOfString:(NSString *)searchString;
- (NSRange)rangeOfString:(NSString *)searchString options:(NSStringCompareOptions)mask;
- (NSRange)rangeOfString:(NSString *)searchString options:(NSStringCompareOptions)mask range:(NSRange)rangeOfReceiverToSearch;
- (NSRange)rangeOfString:(NSString *)searchString options:(NSStringCompareOptions)mask range:(NSRange)rangeOfReceiverToSearch locale:(nullable NSLocale *)locale NS_AVAILABLE(10_5, 2_0);

/* These return the range of the first character from the set in the string, not the range of a sequence of characters.
 
 The range argument specifies the subrange, rather than the whole, of the receiver to use in the search.  It is an error to specify a range that is outside of the receiver's bounds, and an exception may be raised.
 */
//指定字符集进行搜索并查找位置
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)searchSet;
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)searchSet options:(NSStringCompareOptions)mask;
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)searchSet options:(NSStringCompareOptions)mask range:(NSRange)rangeOfReceiverToSearch;
//用字符串的字符编码指定索引查找位置
- (NSRange)rangeOfComposedCharacterSequenceAtIndex:(NSUInteger)index;
//用字符串的字符编码指定区域段查找位置
- (NSRange)rangeOfComposedCharacterSequencesForRange:(NSRange)range NS_AVAILABLE(10_5, 2_0);
//将aString字符串添加到当前字符串的后面
- (NSString *)stringByAppendingString:(NSString *)aString;
//将多个字符串添加到当前字符串的后面
- (NSString *)stringByAppendingFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);


#pragma mark *** Extracting numeric values ***

/* The following convenience methods all skip initial space characters (whitespaceSet) and ignore trailing characters. They are not locale-aware. NSScanner or NSNumberFormatter can be used for more powerful and locale-aware parsing of numbers.
 */
@property (readonly) double doubleValue;
@property (readonly) float floatValue;
@property (readonly) int intValue;
@property (readonly) NSInteger integerValue NS_AVAILABLE(10_5, 2_0);
@property (readonly) long long longLongValue NS_AVAILABLE(10_5, 2_0);
@property (readonly) BOOL boolValue NS_AVAILABLE(10_5, 2_0);  // Skips initial space characters (whitespaceSet), or optional -/+ sign followed by zeroes. Returns YES on encountering one of "Y", "y", "T", "t", or a digit 1-9. It ignores any trailing characters.


#pragma mark *** Case changing ***

/* The following three return the canonical (non-localized) mappings. They are suitable for programming operations that require stable results not depending on the user's locale preference.  For locale-aware case mapping for strings presented to users, use the "localized" methods below.
 */
//将字符串的所有字符转化成大写
@property (readonly, copy) NSString *uppercaseString;
//将字符串的所有字符转化为小写
@property (readonly, copy) NSString *lowercaseString;
//将所有单词的首字母转化成大写
@property (readonly, copy) NSString *capitalizedString;

/* The following three return the locale-aware case mappings. They are suitable for strings presented to the user.
 */
@property (readonly, copy) NSString *localizedUppercaseString NS_AVAILABLE(10_11, 9_0);
@property (readonly, copy) NSString *localizedLowercaseString NS_AVAILABLE(10_11, 9_0);
@property (readonly, copy) NSString *localizedCapitalizedString NS_AVAILABLE(10_11, 9_0);

/* The following methods perform localized case mappings based on the locale specified. Passing nil indicates the canonical mapping.  For the user preference locale setting, specify +[NSLocale currentLocale].
 */
//将字符串的所有字符转化成大写 本地化
- (NSString *)uppercaseStringWithLocale:(nullable NSLocale *)locale NS_AVAILABLE(10_8, 6_0);
//将字符串的所有字符转化为小写 本地化
- (NSString *)lowercaseStringWithLocale:(nullable NSLocale *)locale NS_AVAILABLE(10_8, 6_0);
//将所有单词的首字母转化成大写 本地化
- (NSString *)capitalizedStringWithLocale:(nullable NSLocale *)locale NS_AVAILABLE(10_8, 6_0);


#pragma mark *** Finding lines, sentences, words, etc ***
//指定段分行去字符串
- (void)getLineStart:(nullable NSUInteger *)startPtr end:(nullable NSUInteger *)lineEndPtr contentsEnd:(nullable NSUInteger *)contentsEndPtr forRange:(NSRange)range;
//返回字符串指定段位置和长度
- (NSRange)lineRangeForRange:(NSRange)range;
//给字符串指定段分段取字符串
- (void)getParagraphStart:(nullable NSUInteger *)startPtr end:(nullable NSUInteger *)parEndPtr contentsEnd:(nullable NSUInteger *)contentsEndPtr forRange:(NSRange)range;
//指定段分段的位置和长度
- (NSRange)paragraphRangeForRange:(NSRange)range;

typedef NS_OPTIONS(NSUInteger, NSStringEnumerationOptions) {
    // Pass in one of the "By" options:
    NSStringEnumerationByLines = 0,                       // Equivalent to lineRangeForRange:
    NSStringEnumerationByParagraphs = 1,                  // Equivalent to paragraphRangeForRange:
    NSStringEnumerationByComposedCharacterSequences = 2,  // Equivalent to rangeOfComposedCharacterSequencesForRange:
    NSStringEnumerationByWords = 3,
    NSStringEnumerationBySentences = 4,
    // ...and combine any of the desired additional options:
    NSStringEnumerationReverse = 1UL << 8,
    NSStringEnumerationSubstringNotRequired = 1UL << 9,
    NSStringEnumerationLocalized = 1UL << 10              // User's default locale
};

/* In the enumerate methods, the blocks will be invoked inside an autorelease pool, so any values assigned inside the block should be retained.
 */
//检查是否在指定范围内是否有匹配的字符串
- (void)enumerateSubstringsInRange:(NSRange)range options:(NSStringEnumerationOptions)opts usingBlock:(void (^)(NSString * _Nullable substring, NSRange substringRange, NSRange enclosingRange, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
//列举枚举字符串所有行
- (void)enumerateLinesUsingBlock:(void (^)(NSString *line, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);


#pragma mark *** Character encoding and converting to/from c-string representations ***

@property (nullable, readonly) const char *UTF8String NS_RETURNS_INNER_POINTER;	// Convenience to return null-terminated UTF8 representation
//字符串最快编码值
@property (readonly) NSStringEncoding fastestEncoding;    	// Result in O(1) time; a rough estimate
//字符串最小编码值
@property (readonly) NSStringEncoding smallestEncoding;   	// Result in O(n) time; the encoding in which the string is most compact
//返回指定编码的NSData对象
- (nullable NSData *)dataUsingEncoding:(NSStringEncoding)encoding allowLossyConversion:(BOOL)lossy;   // External representation
//返回指定编码的NSData对象
- (nullable NSData *)dataUsingEncoding:(NSStringEncoding)encoding;                                    // External representation
//判断是否可以无损化转码
- (BOOL)canBeConvertedToEncoding:(NSStringEncoding)encoding;

/* Methods to convert NSString to a NULL-terminated cString using the specified encoding. Note, these are the "new" cString methods, and are not deprecated like the older cString methods which do not take encoding arguments.
 */
//char编码转化
- (nullable const char *)cStringUsingEncoding:(NSStringEncoding)encoding NS_RETURNS_INNER_POINTER;	// "Autoreleased"; NULL return if encoding conversion not possible; for performance reasons, lifetime of this should not be considered longer than the lifetime of the receiving string (if the receiver string is freed, this might go invalid then, before the end of the autorelease scope)
//C字符串转化是够成功
- (BOOL)getCString:(char *)buffer maxLength:(NSUInteger)maxBufferCount encoding:(NSStringEncoding)encoding;	// NO return if conversion not possible due to encoding errors or too small of a buffer. The buffer should include room for maxBufferCount bytes; this number should accomodate the expected size of the return value plus the NULL termination character, which this method adds. (So note that the maxLength passed to this method is one more than the one you would have passed to the deprecated getCString:maxLength:.)

/* Use this to convert string section at a time into a fixed-size buffer, without any allocations.  Does not NULL-terminate.
 buffer is the buffer to write to; if NULL, this method can be used to computed size of needed buffer.
 maxBufferCount is the length of the buffer in bytes. It's a good idea to make sure this is at least enough to hold one character's worth of conversion.
 usedBufferCount is the length of the buffer used up by the current conversion. Can be NULL.
 encoding is the encoding to convert to.
 options specifies the options to apply.
 range is the range to convert.
 leftOver is the remaining range. Can be NULL.
 YES return indicates some characters were converted. Conversion might usually stop when the buffer fills,
 but it might also stop when the conversion isn't possible due to the chosen encoding.
 */
//指定缓存区转换
- (BOOL)getBytes:(nullable void *)buffer maxLength:(NSUInteger)maxBufferCount usedLength:(nullable NSUInteger *)usedBufferCount encoding:(NSStringEncoding)encoding options:(NSStringEncodingConversionOptions)options range:(NSRange)range remainingRange:(nullable NSRangePointer)leftover;

/* These return the maximum and exact number of bytes needed to store the receiver in the specified encoding in non-external representation. The first one is O(1), while the second one is O(n). These do not include space for a terminating null.
 */
//字符串编码时需要用到最大字节长度
- (NSUInteger)maximumLengthOfBytesUsingEncoding:(NSStringEncoding)enc;	// Result in O(1) time; the estimate may be way over what's needed. Returns 0 on error (overflow)
//字符串编码时需要用的字节长度
- (NSUInteger)lengthOfBytesUsingEncoding:(NSStringEncoding)enc;		// Result in O(n) time; the result is exact. Returns 0 on error (cannot convert to specified encoding, or overflow)

#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
@property (class, readonly) const NSStringEncoding *availableStringEncodings;
#endif
+ (NSString *)localizedNameOfStringEncoding:(NSStringEncoding)encoding;

/* User-dependent encoding whose value is derived from user's default language and potentially other factors. The use of this encoding might sometimes be needed when interpreting user documents with unknown encodings, in the absence of other hints.  This encoding should be used rarely, if at all. Note that some potential values here might result in unexpected encoding conversions of even fairly straightforward NSString content --- for instance, punctuation characters with a bidirectional encoding.
 */
#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
@property (class, readonly) NSStringEncoding defaultCStringEncoding;	// Should be rarely used
#endif


#pragma mark *** Other ***
//unicode范式D标准化
@property (readonly, copy) NSString *decomposedStringWithCanonicalMapping;
//unicode范式c标准化
@property (readonly, copy) NSString *precomposedStringWithCanonicalMapping;
//unicode范式KD标准化
@property (readonly, copy) NSString *decomposedStringWithCompatibilityMapping;
//unicode范式KC标准化
@property (readonly, copy) NSString *precomposedStringWithCompatibilityMapping;

- (NSArray<NSString *> *)componentsSeparatedByString:(NSString *)separator;
- (NSArray<NSString *> *)componentsSeparatedByCharactersInSet:(NSCharacterSet *)separator NS_AVAILABLE(10_5, 2_0);
//去掉字符串开始及结尾的set无效内容
- (NSString *)stringByTrimmingCharactersInSet:(NSCharacterSet *)set;
- (NSString *)stringByPaddingToLength:(NSUInteger)newLength withString:(NSString *)padString startingAtIndex:(NSUInteger)padIndex;

/* Returns a string with the character folding options applied. theOptions is a mask of compare flags with *InsensitiveSearch suffix.
 */
//本地化字符串折叠
- (NSString *)stringByFoldingWithOptions:(NSStringCompareOptions)options locale:(nullable NSLocale *)locale NS_AVAILABLE(10_5, 2_0);

/* Replace all occurrences of the target string in the specified range with replacement. Specified compare options are used for matching target. If NSRegularExpressionSearch is specified, the replacement is treated as a template, as in the corresponding NSRegularExpression methods, and no other options can apply except NSCaseInsensitiveSearch and NSAnchoredSearch.
 */
//字符串的指定区域段被有条件的替换掉
- (NSString *)stringByReplacingOccurrencesOfString:(NSString *)target withString:(NSString *)replacement options:(NSStringCompareOptions)options range:(NSRange)searchRange NS_AVAILABLE(10_5, 2_0);

/* Replace all occurrences of the target string with replacement. Invokes the above method with 0 options and range of the whole string.
 */
//字符串的特定字符串被替换掉
- (NSString *)stringByReplacingOccurrencesOfString:(NSString *)target withString:(NSString *)replacement NS_AVAILABLE(10_5, 2_0);

/* Replace characters in range with the specified string, returning new string.
 */
//将字符串的指定区域段字符串被替换掉
- (NSString *)stringByReplacingCharactersInRange:(NSRange)range withString:(NSString *)replacement NS_AVAILABLE(10_5, 2_0);

typedef NSString *NSStringTransform NS_EXTENSIBLE_STRING_ENUM;

/* Perform string transliteration.  The transformation represented by transform is applied to the receiver. reverse indicates that the inverse transform should be used instead, if it exists. Attempting to use an invalid transform identifier or reverse an irreversible transform will return nil; otherwise the transformed string value is returned (even if no characters are actually transformed). You can pass one of the predefined transforms below (NSStringTransformLatinToKatakana, etc), or any valid ICU transform ID as defined in the ICU User Guide. Arbitrary ICU transform rules are not supported.
 */
- (nullable NSString *)stringByApplyingTransform:(NSStringTransform)transform reverse:(BOOL)reverse NS_AVAILABLE(10_11, 9_0);	// Returns nil if reverse not applicable or transform is invalid

FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToKatakana         NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToHiragana         NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToHangul           NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToArabic           NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToHebrew           NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToThai             NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToCyrillic         NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToGreek            NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSStringTransform const NSStringTransformToLatin                 NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSStringTransform const NSStringTransformMandarinToLatin         NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSStringTransform const NSStringTransformHiraganaToKatakana      NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSStringTransform const NSStringTransformFullwidthToHalfwidth    NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSStringTransform const NSStringTransformToXMLHex                NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSStringTransform const NSStringTransformToUnicodeName           NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSStringTransform const NSStringTransformStripCombiningMarks     NS_AVAILABLE(10_11, 9_0);
FOUNDATION_EXPORT NSStringTransform const NSStringTransformStripDiacritics         NS_AVAILABLE(10_11, 9_0);


/* Write to specified url or path using the specified encoding.  The optional error return is to indicate file system or encoding errors.
 */
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)useAuxiliaryFile encoding:(NSStringEncoding)enc error:(NSError **)error;
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile encoding:(NSStringEncoding)enc error:(NSError **)error;

@property (readonly, copy) NSString *description;

@property (readonly) NSUInteger hash;


#pragma mark *** Initializers ***

/* In general creation methods in NSString do not apply to subclassers, as subclassers are assumed to provide their own init methods which create the string in the way the subclass wishes.  Designated initializers of NSString are thus init and initWithCoder:.
 */
//指定缓冲区，编码和字节长度初始化NSString对象
- (instancetype)initWithCharactersNoCopy:(unichar *)characters length:(NSUInteger)length freeWhenDone:(BOOL)freeBuffer;	/* "NoCopy" is a hint */
//指定unichar字符，字节长度初始化NSString对象
- (instancetype)initWithCharacters:(const unichar *)characters length:(NSUInteger)length;
//转化UTF8为NSString对象
- (nullable instancetype)initWithUTF8String:(const char *)nullTerminatedCString;
//指定字符串初始化为NSString对象
- (instancetype)initWithString:(NSString *)aString;
//格式化多个字符串初始化NSString对象
- (instancetype)initWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);
//格式化字符串初始化NSString对象
- (instancetype)initWithFormat:(NSString *)format arguments:(va_list)argList NS_FORMAT_FUNCTION(1,0);
//本地化格式化多个字符串初始化NSString对象
- (instancetype)initWithFormat:(NSString *)format locale:(nullable id)locale, ... NS_FORMAT_FUNCTION(1,3);
//本地化格式化字符串初始化NSString对象
- (instancetype)initWithFormat:(NSString *)format locale:(nullable id)locale arguments:(va_list)argList NS_FORMAT_FUNCTION(1,0);
//指定编码转化NSData数据
- (nullable instancetype)initWithData:(NSData *)data encoding:(NSStringEncoding)encoding;
//指定编码和字节数初始化NSString对象
- (nullable instancetype)initWithBytes:(const void *)bytes length:(NSUInteger)len encoding:(NSStringEncoding)encoding;
//指定缓冲区，编码和字节数初始化NSString对象
- (nullable instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)len encoding:(NSStringEncoding)encoding freeWhenDone:(BOOL)freeBuffer;	/* "NoCopy" is a hint */

+ (instancetype)string;
+ (instancetype)stringWithString:(NSString *)string;
+ (instancetype)stringWithCharacters:(const unichar *)characters length:(NSUInteger)length;
+ (nullable instancetype)stringWithUTF8String:(const char *)nullTerminatedCString;
+ (instancetype)stringWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);
//初始化NSString自动释放内存，本地化
+ (instancetype)localizedStringWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);
//初始化C字符串并且指定编码，在这里需要手动释放内存（init）
- (nullable instancetype)initWithCString:(const char *)nullTerminatedCString encoding:(NSStringEncoding)encoding;
+ (nullable instancetype)stringWithCString:(const char *)cString encoding:(NSStringEncoding)enc;

/* These use the specified encoding.  If nil is returned, the optional error return indicates problem that was encountered (for instance, file system or encoding errors).
 */
//读取URL地址数据转化为字符串并且指定编码 同样需要手动释放内存，已经知道编码
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url encoding:(NSStringEncoding)enc error:(NSError **)error;
//读取FILE地址数据转化为字符串并且指定编码 同样需要手动释放内存，已经知道编码
- (nullable instancetype)initWithContentsOfFile:(NSString *)path encoding:(NSStringEncoding)enc error:(NSError **)error;
//读取URL地址数据转化为字符串并且指定编码 自动释放内存，已经知道编码
+ (nullable instancetype)stringWithContentsOfURL:(NSURL *)url encoding:(NSStringEncoding)enc error:(NSError **)error;
//读取FILE地址数据转化为字符串并且指定编码 自动释放内存，已经知道编码
+ (nullable instancetype)stringWithContentsOfFile:(NSString *)path encoding:(NSStringEncoding)enc error:(NSError **)error;

/* These try to determine the encoding, and return the encoding which was used.  Note that these methods might get "smarter" in subsequent releases of the system, and use additional techniques for recognizing encodings. If nil is returned, the optional error return indicates problem that was encountered (for instance, file system or encoding errors).
 */
//读取URL地址数据转化为字符串并且指定编码，在这里init创建需要手动释放内存，不知道编码
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;
//读取FILE地址数据转化为字符串并且指定编码，同样需要手动释放内存，不知道编码
- (nullable instancetype)initWithContentsOfFile:(NSString *)path usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;
+ (nullable instancetype)stringWithContentsOfURL:(NSURL *)url usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;
+ (nullable instancetype)stringWithContentsOfFile:(NSString *)path usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;

@end
    
typedef NSString * NSStringEncodingDetectionOptionsKey NS_STRING_ENUM;
//关于字符串编码检测的扩展
@interface NSString (NSStringEncodingDetection)

#pragma mark *** Encoding detection ***

/* This API is used to detect the string encoding of a given raw data. It can also do lossy string conversion. It converts the data to a string in the detected string encoding. The data object contains the raw bytes, and the option dictionary contains the hints and parameters for the analysis. The opts dictionary can be nil. If the string parameter is not NULL, the string created by the detected string encoding is returned. The lossy substitution string is emitted in the output string for characters that could not be converted when lossy conversion is enabled. The usedLossyConversion indicates if there is any lossy conversion in the resulted string. If no encoding can be detected, 0 is returned.
 
 The possible items for the dictionary are:
 1) an array of suggested string encodings (without specifying the 3rd option in this list, all string encodings are considered but the ones in the array will have a higher preference; moreover, the order of the encodings in the array is important: the first encoding has a higher preference than the second one in the array)
 2) an array of string encodings not to use (the string encodings in this list will not be considered at all)
 3) a boolean option indicating whether only the suggested string encodings are considered
 4) a boolean option indicating whether lossy is allowed
 5) an option that gives a specific string to substitude for mystery bytes
 6) the current user's language
 7) a boolean option indicating whether the data is generated by Windows
 
 If the values in the dictionary have wrong types (for example, the value of NSStringEncodingDetectionSuggestedEncodingsKey is not an array), an exception is thrown.
 If the values in the dictionary are unknown (for example, the value in the array of suggested string encodings is not a valid encoding), the values will be ignored.
 */
/*对一份data数据进行转换为字符串，有可选option字典，另外还有是否允许有损失，最终转换之后返回一个编码种类。下面是7种不同option字典选项*/
+ (NSStringEncoding)stringEncodingForData:(NSData *)data
                          encodingOptions:(nullable NSDictionary<NSStringEncodingDetectionOptionsKey, id> *)opts
                          convertedString:(NSString * _Nullable * _Nullable)string
                      usedLossyConversion:(nullable BOOL *)usedLossyConversion NS_AVAILABLE(10_10, 8_0);

/* The following keys are for the option dictionary for the string encoding detection API.
 */
FOUNDATION_EXPORT NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionSuggestedEncodingsKey           NS_AVAILABLE(10_10, 8_0);   // NSArray of NSNumbers which contain NSStringEncoding values; if this key is not present in the dictionary, all encodings are weighted the same
FOUNDATION_EXPORT NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionDisallowedEncodingsKey          NS_AVAILABLE(10_10, 8_0);   // NSArray of NSNumbers which contain NSStringEncoding values; if this key is not present in the dictionary, all encodings are considered
FOUNDATION_EXPORT NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionUseOnlySuggestedEncodingsKey    NS_AVAILABLE(10_10, 8_0);   // NSNumber boolean value; if this key is not present in the dictionary, the default value is NO
FOUNDATION_EXPORT NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionAllowLossyKey                   NS_AVAILABLE(10_10, 8_0);   // NSNumber boolean value; if this key is not present in the dictionary, the default value is YES
FOUNDATION_EXPORT NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionFromWindowsKey                  NS_AVAILABLE(10_10, 8_0);   // NSNumber boolean value; if this key is not present in the dictionary, the default value is NO
FOUNDATION_EXPORT NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionLossySubstitutionKey            NS_AVAILABLE(10_10, 8_0);   // NSString value; if this key is not present in the dictionary, the default value is U+FFFD
FOUNDATION_EXPORT NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionLikelyLanguageKey               NS_AVAILABLE(10_10, 8_0);   // NSString value; ISO language code; if this key is not present in the dictionary, no such information is considered

@end
    
    
    
@interface NSMutableString : NSString

#pragma mark *** Mutable string ***

/* NSMutableString primitive (funnel) method. See below for the other mutation methods.
 */
- (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)aString;

@end
    
@interface NSMutableString (NSMutableStringExtensionMethods)

/* Additional mutation methods.  For subclassers these are all available implemented in terms of the primitive replaceCharactersInRange:range: method.
 */
//插入字符串aString，在指定的loc位置
- (void)insertString:(NSString *)aString atIndex:(NSUInteger)loc;
//删除指定区域段的字符串
- (void)deleteCharactersInRange:(NSRange)range;
//追加字符串aString
- (void)appendString:(NSString *)aString;
//追加多个字符串
- (void)appendFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);
//设置新的aString
- (void)setString:(NSString *)aString;

/* This method replaces all occurrences of the target string with the replacement string, in the specified range of the receiver string, and returns the number of replacements. NSBackwardsSearch means the search is done from the end of the range (the results could be different); NSAnchoredSearch means only anchored (but potentially multiple) instances will be replaced. NSLiteralSearch and NSCaseInsensitiveSearch also apply. NSNumericSearch is ignored. Use NSMakeRange(0, [receiver length]) to process whole string. If NSRegularExpressionSearch is specified, the replacement is treated as a template, as in the corresponding NSRegularExpression methods, and no other options can apply except NSCaseInsensitiveSearch and NSAnchoredSearch.
 */
//指定限制条件，指定区段中的replacement替换成target
- (NSUInteger)replaceOccurrencesOfString:(NSString *)target withString:(NSString *)replacement options:(NSStringCompareOptions)options range:(NSRange)searchRange;

/* Perform string transliteration.  The transformation represented by transform is applied to the given range of string in place. Only the specified range will be modified, but the transform may look at portions of the string outside that range for context. If supplied, resultingRange is modified to reflect the new range corresponding to the original range. reverse indicates that the inverse transform should be used instead, if it exists. Attempting to use an invalid transform identifier or reverse an irreversible transform will return NO; otherwise YES is returned, even if no characters are actually transformed. You can pass one of the predefined transforms listed above (NSStringTransformLatinToKatakana, etc), or any valid ICU transform ID as defined in the ICU User Guide. Arbitrary ICU transform rules are not supported.
 */
- (BOOL)applyTransform:(NSString *)transform reverse:(BOOL)reverse range:(NSRange)range updatedRange:(nullable NSRangePointer)resultingRange NS_AVAILABLE(10_11, 9_0);

/* In addition to these two, NSMutableString responds properly to all NSString creation methods.
 */
- (NSMutableString *)initWithCapacity:(NSUInteger)capacity;
+ (NSMutableString *)stringWithCapacity:(NSUInteger)capacity;

@end
    
    
    
FOUNDATION_EXPORT NSExceptionName const NSCharacterConversionException;
FOUNDATION_EXPORT NSExceptionName const NSParseErrorException; // raised by -propertyList
#define NSMaximumStringLength	(INT_MAX-1)
    
#pragma mark *** Deprecated/discouraged APIs ***
    
    @interface NSString (NSExtendedStringPropertyListParsing)

/* These methods are no longer recommended since they do not work with property lists and strings files in binary plist format. Please use the APIs in NSPropertyList.h instead.
 */
//将字符串转化为属性列表
- (id)propertyList;
//字符串转化为字典
- (nullable NSDictionary *)propertyListFromStringsFileFormat;

@end
    
    @interface NSString (NSStringDeprecated)

/* The following methods are deprecated and will be removed from this header file in the near future. These methods use NSString.defaultCStringEncoding as the encoding to convert to, which means the results depend on the user's language and potentially other settings. This might be appropriate in some cases, but often these methods are misused, resulting in issues when running in languages other then English. UTF8String in general is a much better choice when converting arbitrary NSStrings into 8-bit representations. Additional potential replacement methods are being introduced in NSString as appropriate.
 */
- (nullable const char *)cString NS_RETURNS_INNER_POINTER NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (nullable const char *)lossyCString NS_RETURNS_INNER_POINTER NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (NSUInteger)cStringLength NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)getCString:(char *)bytes NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)getCString:(char *)bytes maxLength:(NSUInteger)maxLength NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)getCString:(char *)bytes maxLength:(NSUInteger)maxLength range:(NSRange)aRange remainingRange:(nullable NSRangePointer)leftoverRange NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

- (nullable id)initWithContentsOfFile:(NSString *)path NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (nullable id)initWithContentsOfURL:(NSURL *)url NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
+ (nullable id)stringWithContentsOfFile:(NSString *)path NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
+ (nullable id)stringWithContentsOfURL:(NSURL *)url NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

- (nullable id)initWithCStringNoCopy:(char *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)freeBuffer NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (nullable id)initWithCString:(const char *)bytes length:(NSUInteger)length NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (nullable id)initWithCString:(const char *)bytes NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
+ (nullable id)stringWithCString:(const char *)bytes length:(NSUInteger)length NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
+ (nullable id)stringWithCString:(const char *)bytes NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

/* This method is unsafe because it could potentially cause buffer overruns. You should use -getCharacters:range: instead.
 */
- (void)getCharacters:(unichar *)buffer;

@end
    
    NS_ENUM(NSStringEncoding) {
        NSProprietaryStringEncoding = 65536    /* Installation-specific encoding */
        };
        
        /* The rest of this file is bookkeeping stuff that has to be here. Don't use this stuff, don't refer to it.
         */
#if !defined(_OBJC_UNICHAR_H_)
#define _OBJC_UNICHAR_H_
#endif
#define NS_UNICHAR_IS_EIGHT_BIT 0
        
        @interface NSSimpleCString : NSString {
            @package
            char *bytes;
            int numBytes;
#if __LP64__
            int _unused;
#endif
        }
@end
        
        @interface NSConstantString : NSSimpleCString
@end
        
#if __LP64__
#else
        extern void *_NSConstantStringClassReference;
#endif
        
        NS_ASSUME_NONNULL_END
