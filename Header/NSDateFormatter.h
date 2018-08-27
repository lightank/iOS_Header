/*	NSDateFormatter.h
	Copyright (c) 1995-2016, Apple Inc. All rights reserved.
 */

#import <Foundation/NSFormatter.h>
#include <CoreFoundation/CFDateFormatter.h>

@class NSLocale, NSDate, NSCalendar, NSTimeZone, NSError, NSArray<ObjectType>, NSMutableDictionary, NSString;

NS_ASSUME_NONNULL_BEGIN

#if !defined(NS_CALENDAR_ENUM_DEPRECATED)
#if 1 || NS_ENABLE_CALENDAR_DEPRECATIONS
#define NS_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) NS_ENUM_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED(A, B, C, D, ...) NS_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED_MAC(A, B, ...) NS_DEPRECATED_MAC(A, B, __VA_ARGS__)
#else
#define NS_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) NS_ENUM_AVAILABLE(A, C)
#define NS_CALENDAR_DEPRECATED(A, B, C, D, ...) NS_AVAILABLE(A, C)
#define NS_CALENDAR_DEPRECATED_MAC(A, B, ...) NS_AVAILABLE_MAC(A)
#endif
#endif


@interface NSDateFormatter : NSFormatter {
@private
    NSMutableDictionary *_attributes;
    CFDateFormatterRef _formatter;
    NSUInteger _counter;
}
//主要用来确定英文等语言中，输出的字符串首字母是否需要大写的问题
@property NSFormattingContext formattingContext NS_AVAILABLE(10_10, 8_0); // default is NSFormattingContextUnknown

// - (id)init; // designated initializer

// Report the used range of the string and an NSError, in addition to the usual stuff from NSFormatter
//Returns by reference a date representation of a given string and the range of the string used, and returns a Boolean value that indicates whether the string could be parsed.
- (BOOL)getObjectValue:(out id _Nullable * _Nullable)obj forString:(NSString *)string range:(inout nullable NSRange *)rangep error:(out NSError **)error;

// Even though NSDateFormatter responds to the usual NSFormatter methods,
//   here are some convenience methods which are a little more obvious.

- (NSString *)stringFromDate:(NSDate *)date;
- (nullable NSDate *)dateFromString:(NSString *)string;

typedef NS_ENUM(NSUInteger, NSDateFormatterStyle) {    // date and time format styles
    // 无输出
    NSDateFormatterNoStyle = kCFDateFormatterNoStyle,
    // 10/29/12, 2:27 PM
    NSDateFormatterShortStyle = kCFDateFormatterShortStyle,
    // Oct 29, 2012, 2:36:59 PM
    NSDateFormatterMediumStyle = kCFDateFormatterMediumStyle,
    // October 29, 2012, 2:38:46 PM GMT+08:00
    NSDateFormatterLongStyle = kCFDateFormatterLongStyle,
    // Monday, October 29, 2012, 2:39:56 PM China Standard Time
    NSDateFormatterFullStyle = kCFDateFormatterFullStyle
};

typedef NS_ENUM(NSUInteger, NSDateFormatterBehavior) {
    NSDateFormatterBehaviorDefault = 0,
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
    NSDateFormatterBehavior10_0 = 1000,
#endif
    NSDateFormatterBehavior10_4 = 1040,
};


+ (NSString *)localizedStringFromDate:(NSDate *)date dateStyle:(NSDateFormatterStyle)dstyle timeStyle:(NSDateFormatterStyle)tstyle NS_AVAILABLE(10_6, 4_0);

+ (nullable NSString *)dateFormatFromTemplate:(NSString *)tmplate options:(NSUInteger)opts locale:(nullable NSLocale *)locale NS_AVAILABLE(10_6, 4_0);
// no options defined, pass 0 for now

// Attributes of an NSDateFormatter
#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
//Returns the default formatting behavior for instances of the class.
@property (class) NSDateFormatterBehavior defaultFormatterBehavior;
#endif

/*
 A convenient way to generate an appropriate localized date format, and set it, in a single operation.
 
 Equivalent to, though not necessarily implemented as:
 formatter.dateFormat = [NSDateFormatter dateFormatFromTemplate:dateFormatTemplate options:0 locale:formatter.locale];
 
 Note that the template string is used only to specify which date format components should be included. Ordering and other text will not be preserved.
 The parameter is also not stored, or updated when the locale or other options change, just as with the ‘dateFormat’ property.
 */
- (void) setLocalizedDateFormatFromTemplate:(NSString *)dateFormatTemplate NS_AVAILABLE(10_10, 8_0);
//时间格式,如:[dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"]
@property (null_resettable, copy) NSString *dateFormat;
//The date style of the receiver.
@property NSDateFormatterStyle dateStyle;
//The time style of the receiver.
@property NSDateFormatterStyle timeStyle;
//自定义区域语言,[[NSLocale alloc] initWithLocaleIdentifier:@"zh_CN"]
@property (null_resettable, copy) NSLocale *locale;
//YES if the receiver generates calendar dates, otherwise NO.
//NSCalendarDate is no longer supported; you should not use this method.
@property BOOL generatesCalendarDates;
//The formatter behavior for the receiver.
@property NSDateFormatterBehavior formatterBehavior;
//时区,如:[NSTimeZone timeZoneWithName:@"Asia/Shanghai"]
@property (null_resettable, copy) NSTimeZone *timeZone;
//日历,如:[[NSCalendar alloc] initWithCalendarIdentifier:NSGregorianCalendar]
@property (null_resettable, copy) NSCalendar *calendar;
//A Boolean value that indicates whether the receiver uses heuristics when parsing a string.
@property (getter=isLenient) BOOL lenient;
//The earliest date that can be denoted by a two-digit year specifier.
@property (nullable, copy) NSDate *twoDigitStartDate;
//The default date for the receiver.
@property (nullable, copy) NSDate *defaultDate;
//NSDateFormatter中同样提供了相应的方式，去修改这些字符。一般情况下，使用相应区域语言下面的默认字符就OK了。但是你的确有这个需求，那么也是可以办到的。相应的方法非常多
@property (null_resettable, copy) NSArray<NSString *> *eraSymbols;
@property (null_resettable, copy) NSArray<NSString *> *monthSymbols;
@property (null_resettable, copy) NSArray<NSString *> *shortMonthSymbols;
@property (null_resettable, copy) NSArray<NSString *> *weekdaySymbols;
@property (null_resettable, copy) NSArray<NSString *> *shortWeekdaySymbols;
@property (null_resettable, copy) NSString *AMSymbol;
@property (null_resettable, copy) NSString *PMSymbol;
@property (null_resettable, copy) NSArray<NSString *> *longEraSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *veryShortMonthSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *standaloneMonthSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *shortStandaloneMonthSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *veryShortStandaloneMonthSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *veryShortWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *standaloneWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *shortStandaloneWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *veryShortStandaloneWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *quarterSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *shortQuarterSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *standaloneQuarterSymbols NS_AVAILABLE(10_5, 2_0);
@property (null_resettable, copy) NSArray<NSString *> *shortStandaloneQuarterSymbols NS_AVAILABLE(10_5, 2_0);
@property (nullable, copy) NSDate *gregorianStartDate NS_AVAILABLE(10_5, 2_0);
@property BOOL doesRelativeDateFormatting NS_AVAILABLE(10_6, 4_0);

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
@interface NSDateFormatter (NSDateFormatterCompatibility)

- (id)initWithDateFormat:(NSString *)format allowNaturalLanguage:(BOOL)flag NS_CALENDAR_DEPRECATED_MAC(10_4, 10_9, "Use -setDateFormat: as of OS X 10.9 to set the date format of a 10.0-style date formatter; but expect 10.0-style date formatting to be deprecated in the future as well");
- (BOOL)allowsNaturalLanguage NS_CALENDAR_DEPRECATED_MAC(10_4, 10_9, "There is no replacement");

@end
#endif

NS_ASSUME_NONNULL_END
