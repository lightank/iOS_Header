/*	NSTimeZone.h
	Copyright (c) 1994-2016, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSNotification.h>

/*
 **时区是一个地理名字，是为了克服各个地区或国家之间在使用时间上的混乱。
 
 基本概念：
 
 GMT 0:00 格林威治标准时间; UTC +00:00 校准的全球时间; CCD +08:00 中国标准时间 [来自百度百科]
 夏时制，英文"DaylightSavingTime"。夏季时将时区内的时间提前（一般为1小时），以节省资源，提高效率。使用夏时制期间，当前时区相对于GMT的时间偏移量会发生变化。在某些应用中可能需要考虑。
 任何时区都以GMT为基准，即，任何NSTimeZone对象所代表的时区都是相对于GMT的，这里的相对性是NSTimeZone中最重要的属性，我们称之为当前时区相对于GMT的偏移量。一旦知道了一个偏移量，便可以确定一个时区。在iOS中，偏移量是以"秒"为单位的。
 NSTimeZone是一个类簇，我们所使用的任何NSTimeZone对象都是NSTimeZone的私有子类。
 iOS中的时间类NSDate中存储的时间，都是相对于GMT的，我们使用NSDate时，会根据App的时区设置返回与时区对应的数据。
 iOS系统中的/usr/share/zoneinfo/目录中保存了所有的可根据 地理位置名称 或 时区别名 得到的时区信息。时区别名都是与具体的地理位置一一对应的。(已越狱的童鞋请看)
 iOS中的时区表示方法：GMT+0800 GMT-0800。(+：东区 -：西区 08：小时数 00：分钟数)。 GMT+0830就是指比GMT早8小时外加30分钟的时区。
 */

@class NSString, NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSDate, NSData, NSLocale;

NS_ASSUME_NONNULL_BEGIN

@interface NSTimeZone : NSObject <NSCopying, NSSecureCoding>

//The geopolitical region ID that identifies the receiver.
@property (readonly, copy) NSString *name;
//The data that stores the information used by the receiver.
@property (readonly, copy) NSData *data;

//Returns the difference in seconds between the receiver and Greenwich Mean Time at a given date.
- (NSInteger)secondsFromGMTForDate:(NSDate *)aDate;
//Returns the abbreviation for the receiver at a given date.
- (nullable NSString *)abbreviationForDate:(NSDate *)aDate;
//Returns a Boolean value that indicates whether the receiver uses daylight saving time at a given date.
- (BOOL)isDaylightSavingTimeForDate:(NSDate *)aDate;
//Returns the daylight saving time offset for a given date.
- (NSTimeInterval)daylightSavingTimeOffsetForDate:(NSDate *)aDate NS_AVAILABLE(10_5, 2_0);
//Returns the next daylight saving time transition after a given date.
- (nullable NSDate *)nextDaylightSavingTimeTransitionAfterDate:(NSDate *)aDate NS_AVAILABLE(10_5, 2_0);

@end

@interface NSTimeZone (NSExtendedTimeZone)

#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
//Returns the time zone currently used by the system.
@property (class, readonly, copy) NSTimeZone *systemTimeZone;
#endif
//Resets the system time zone object cached by the application, if any.
+ (void)resetSystemTimeZone;

#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
//Returns the default time zone for the current application.
@property (class, copy) NSTimeZone *defaultTimeZone;
//Returns an object that forwards all messages to the default time zone for the current application.
@property (class, readonly, copy) NSTimeZone *localTimeZone;
//Returns an array of strings listing the IDs of all the time zones known to the system.
// 这个方法的名字很委婉，known一词说明这是“他”已知的时区的名字。世界各地对自己所在的时区可能都有一定的命名，但是不一定被“他”收录。例如，中国大陆，只有重庆和上海被收录了（难道这是中国只使用一个时区的错误？！）。使用这个方法获得的时区名字，都是在iOS系统中/usr/share/zoneinfo/目录中保存时区数据。随着iOS版本的更新，这里面的数据会发生变动。当然，要是你的设备越狱了，你可以手动往该目录下添加时区文件。
// 时区文件里面包括了一下内容：
//        当前时区相对于GMT的偏移量（s）
//        当前时区的名字缩写
//        当前时区是否使“夏时制”时区
// 因为时区文件中包含了"偏移量"，所以通过“时区的名称”可以指定一个“时区”。
// 时区名称举例：
//        Africa/Abidjan
//        America/New_York
//        Asia/Shanghai
//        Asia/Hong_Kong
// 越狱的童鞋可以看出时区的名称和/usr/share/zoneinfo中的目录结构基本一一对应。
@property (class, readonly, copy) NSArray<NSString *> *knownTimeZoneNames;
//Returns a dictionary holding the mappings of time zone abbreviations to time zone names.
// 获取所有的时区名称缩写
// 名称缩写与名称是一一对应的关系，例如：HKT = "Asia/Hong_Kong";
// 默认情况下，调用该方法回去/usr/share/zoneinfo目录下找时区名称缩写，但是当使用方法"+ (void)setAbbreviationDictionary:(NSDictionary *)dict;"后，将会只返回刚才设置的时区名称缩写。请看下文的代码实例！
// 名称缩写举例：
//        EST = "America/New_York";
//        GMT = GMT;
//        GST = "Asia/Dubai";
//        HKT = "Asia/Hong_Kong";
@property (class, copy) NSDictionary<NSString *, NSString *> *abbreviationDictionary NS_AVAILABLE(10_6, 4_0);
//Returns a dictionary holding the mappings of time zone abbreviations to time zone names.
+ (NSDictionary<NSString *, NSString *> *)abbreviationDictionary;
//Returns the time zone data version.
@property (class, readonly, copy) NSString *timeZoneDataVersion NS_AVAILABLE(10_6, 4_0);
#endif
//The current difference in seconds between the receiver and Greenwich Mean Time. (read-only)
//和格林尼治时间差
@property (readonly) NSInteger secondsFromGMT;
//The abbreviation for the receiver, such as “EDT” (Eastern Daylight Time). (read-only)
@property (nullable, readonly, copy) NSString *abbreviation;
//A Boolean value that indicates whether the receiver is currently using daylight saving time. (read-only)
@property (readonly, getter=isDaylightSavingTime) BOOL daylightSavingTime;
//The current daylight saving time offset of the receiver. (read-only)
@property (readonly) NSTimeInterval daylightSavingTimeOffset NS_AVAILABLE(10_5, 2_0); // for current instant
//The date of the next daylight saving time transition for the receiver. (read-only)
@property (nullable, readonly, copy) NSDate *nextDaylightSavingTimeTransition NS_AVAILABLE(10_5, 2_0); // after current instant
//This property contains the date of the next (after the current instant) daylight saving time transition for the receiver. Depending on the time zone of the receiver, the value of this property may represent a change of the time zone's offset from GMT. Returns nil if the time zone of the receiver does not currently observe daylight saving time.
@property (readonly, copy) NSString *description;

- (BOOL)isEqualToTimeZone:(NSTimeZone *)aTimeZone;

typedef NS_ENUM(NSInteger, NSTimeZoneNameStyle) {
    //Specifies a standard name style. For example, “Central Standard Time” for Central Time.
    NSTimeZoneNameStyleStandard,		// Central Standard Time
    //Specifies a short name style. For example, “CST” for Central Time.
    NSTimeZoneNameStyleShortStandard,	// CST
    //Specifies a daylight saving name style. For example, “Central Daylight Time” for Central Time.
    NSTimeZoneNameStyleDaylightSaving,	// Central Daylight Time
    //Specifies a short daylight saving name style. For example, “CDT” for Central Time.
    NSTimeZoneNameStyleShortDaylightSaving,	// CDT
    //Specifies a generic name style. For example, “Central Time” for Central Time.
    NSTimeZoneNameStyleGeneric,		// Central Time
    //Specifies a generic time zone name. For example, “CT” for Central Time.
    NSTimeZoneNameStyleShortGeneric		// CT
};
//Returns the name of the receiver localized for a given locale.
- (nullable NSString *)localizedName:(NSTimeZoneNameStyle)style locale:(nullable NSLocale *)locale NS_AVAILABLE(10_5, 2_0);

@end

@interface NSTimeZone (NSTimeZoneCreation)

// Primary creation method is +timeZoneWithName:; the
// data-taking variants should rarely be used directly
//Returns the time zone object identified by a given ID.
+ (nullable instancetype)timeZoneWithName:(NSString *)tzName;
//Returns the time zone with a given ID whose data has been initialized using given data,
+ (nullable instancetype)timeZoneWithName:(NSString *)tzName data:(nullable NSData *)aData;

- (nullable instancetype)initWithName:(NSString *)tzName;
- (nullable instancetype)initWithName:(NSString *)tzName data:(nullable NSData *)aData;

// Time zones created with this never have daylight savings and the
// offset is constant no matter the date; the name and abbreviation
// do NOT follow the POSIX convention (of minutes-west).
//Returns a time zone object offset from Greenwich Mean Time by a given number of seconds.
+ (instancetype)timeZoneForSecondsFromGMT:(NSInteger)seconds;
//Returns the time zone object identified by a given abbreviation.
+ (nullable instancetype)timeZoneWithAbbreviation:(NSString *)abbreviation;

@end

FOUNDATION_EXPORT NSNotificationName const NSSystemTimeZoneDidChangeNotification NS_AVAILABLE(10_5, 2_0);

NS_ASSUME_NONNULL_END
