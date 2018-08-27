/*	NSDate.h
	Copyright (c) 1994-2016, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSNotification.h>

@class NSString;

NS_ASSUME_NONNULL_BEGIN

/*
 > GMT表示的是0时区的时间。
 **>**NSDate表示的是一个绝对的时间点,如（2015-11-9 21:33:12）＋000000
 >时间默认零时区为当前时间（格林尼治）时间
 **>**Date reference时间是以2001－01-01基准时间
 **>**NSDate时间包含了日期，时间，时区
 
 主要有以下类：
 NSDate -- 表示一个绝对的时间点
 NSTimeZone -- 时区信息
 NSLocale -- 本地化信息
 NSDateComponents -- 一个封装了具体年月日、时秒分、周、季度等的类
 NSCalendar -- 日历类，它提供了大部分的日期计算接口，并且允许您在NSDate和NSDateComponents之间转换
 NSDateFormatter -- 用来在日期和字符串之间转换
 */

//Posted whenever the system clock is changed. This can be initiated by a call to settimeofday() or the user changing values in the Date and Time Preference panel. The notification object is null. This notification does not contain a userInfo dictionary.
FOUNDATION_EXPORT NSNotificationName const NSSystemClockDidChangeNotification NS_AVAILABLE(10_6, 4_0);

typedef double NSTimeInterval;

#define NSTimeIntervalSince1970  978307200.0

@interface NSDate : NSObject <NSCopying, NSSecureCoding>

@property (readonly) NSTimeInterval timeIntervalSinceReferenceDate;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
//以当前时间的偏移秒数来初始化
- (instancetype)initWithTimeIntervalSinceReferenceDate:(NSTimeInterval)ti NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSDate (NSExtendedDate)
//以anotherDate为基准时间，返回实例保存的时间与refDate的时间间隔
- (NSTimeInterval)timeIntervalSinceDate:(NSDate *)anotherDate;
//以当前时间(Now)为基准时间，返回实例保存的时间与当前时间(Now)的时间间隔
@property (readonly) NSTimeInterval timeIntervalSinceNow;
//以1970/01/01 GMT为基准时间，返回实例保存的时间与1970/01/01 GMT的时间间隔
@property (readonly) NSTimeInterval timeIntervalSince1970;

- (id)addTimeInterval:(NSTimeInterval)seconds NS_DEPRECATED(10_0, 10_6, 2_0, 4_0);
//返回以当前NSDate对象为基准，偏移多少秒后得到的新NSDate对象
- (instancetype)dateByAddingTimeInterval:(NSTimeInterval)ti NS_AVAILABLE(10_6, 2_0);
//比较两个NSDate对象，返回较早的时间点，并以新NSDate对象的形式返回
- (NSDate *)earlierDate:(NSDate *)anotherDate;
//比较两个NSDate对象，返回较晚的时间点，并以新NSDate对象的形式返回
- (NSDate *)laterDate:(NSDate *)anotherDate;
//将当前对象与参数传递的对象进行比较，如果相同，返回0(NSOrderedSame)；对象时间早于参数时间，返回-1(NSOrderedAscending)；对象时间晚于参数时间，返回1(NSOrderedDescending)
- (NSComparisonResult)compare:(NSDate *)other;
//将当前对象与参数传递的对象进行比较，根据是否相同返回BOOL值
- (BOOL)isEqualToDate:(NSDate *)otherDate;

@property (readonly, copy) NSString *description;
- (NSString *)descriptionWithLocale:(nullable id)locale;

#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
//返回当前对象时间与2001-1-1 0:0:0的相隔秒数,也可以这样理解：从2001-1-1 0:0:0开始，经过多少秒到达对象指定时间
@property (class, readonly) NSTimeInterval timeIntervalSinceReferenceDate;
#endif

@end

@interface NSDate (NSDateCreation)
//输出的时间是格林威治标准时间，本初子午线穿过那里
+ (instancetype)date;
//返回以当前时间为基准，然后过了secs秒的时间
+ (instancetype)dateWithTimeIntervalSinceNow:(NSTimeInterval)secs;
//返回以2001/01/01 0:0:0 GMT为基准，然后过了secs秒的时间
+ (instancetype)dateWithTimeIntervalSinceReferenceDate:(NSTimeInterval)ti;
//返回以1970/01/01 GMT为基准，然后过了secs秒的时间
+ (instancetype)dateWithTimeIntervalSince1970:(NSTimeInterval)secs;
+ (instancetype)dateWithTimeInterval:(NSTimeInterval)secsToBeAdded sinceDate:(NSDate *)date;

#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
//返回很多年以后的未来的某一天。（比如你需要一个比现在(Now)晚(大)很长时间的时间值，则可以调用该方法。测试返回了4000/12/31 16:00:00）
@property (class, readonly, copy) NSDate *distantFuture;
//返回很多年以前的某一天。（比如你需要一个比现在(Now)早(小)大很长时间的时间值，则可以调用该方法。测试返回了公元前0001/12/31 17:00:00）
@property (class, readonly, copy) NSDate *distantPast;
#endif

- (instancetype)initWithTimeIntervalSinceNow:(NSTimeInterval)secs;
- (instancetype)initWithTimeIntervalSince1970:(NSTimeInterval)secs;
- (instancetype)initWithTimeInterval:(NSTimeInterval)secsToBeAdded sinceDate:(NSDate *)date;

@end

NS_ASSUME_NONNULL_END
