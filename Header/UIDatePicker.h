//
//  UIDatePicker.h
//  UIKit
//
//  Copyright (c) 2006-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIDatePickerMode) {
    //日期模式：时，分，上下午(e.g. 6 | 53 | PM)
    UIDatePickerModeTime,           // Displays hour, minute, and optionally AM/PM designation depending on the locale setting (e.g. 6 | 53 | PM)
    //日期模式：年，月，日(e.g. November | 15 | 2007)
    UIDatePickerModeDate,           // Displays month, day, and year depending on the locale setting (e.g. November | 15 | 2007)
    //日期模式：星期，月，日，时，分，上下午(e.g. Wed Nov 15 | 6 | 53 | PM)
    UIDatePickerModeDateAndTime,    // Displays date, hour, minute, and optionally AM/PM designation depending on the locale setting (e.g. Wed Nov 15 | 6 | 53 | PM)
    //日期模式：时，分 (e.g. 1 | 53)
    UIDatePickerModeCountDownTimer, // Displays hour and minute (e.g. 1 | 53)
} __TVOS_PROHIBITED;

NS_CLASS_AVAILABLE_IOS(2_0) __TVOS_PROHIBITED @interface UIDatePicker : UIControl <NSCoding>
// 日期模式, 默认是：UIDatePickerModeDateAndTime
@property (nonatomic) UIDatePickerMode datePickerMode; // default is UIDatePickerModeDateAndTime
/*
 设置DatePicker的地区,即设置DatePicker显示的语言。
 1.跟踪所有可用的地区，取出想要的地区
 NSLog(@"%@", [NSLocale availableLocaleIdentifiers]);
 2. 设置日期选择控件的地区
 [datePicker setLocale:[[NSLocale alloc]initWithLocaleIdentifier:@"zh_Hans_CN"]];//简体中文
 [datePicker setLocale:[[NSLocale alloc]initWithLocaleIdentifier:@"en_SC"]];//英文
 不设置的话显示默认的，随着当前所在环境的改变而改变
 */
//设置DatePicker显示的语言,默认是：[NSLocale currentLocale].
@property (nullable, nonatomic, strong) NSLocale   *locale;   // default is [NSLocale currentLocale]. setting nil returns to default
//设置DatePicker的日历。默认为当天
@property (null_resettable, nonatomic, copy)   NSCalendar *calendar; // default is [NSCalendar currentCalendar]. setting nil returns to default
//设置DatePicker的时区。
@property (nullable, nonatomic, strong) NSTimeZone *timeZone; // default is nil. use current time zone or time zone from calendar
//设置DatePicker的日期
@property (nonatomic, strong) NSDate *date;        // default is current date when picker created. Ignored in countdown timer mode. for that mode, picker starts at 0:00
//设置DatePicker的允许的最小日期。
@property (nullable, nonatomic, strong) NSDate *minimumDate; // specify min/max date range. default is nil. When min > max, the values are ignored. Ignored in countdown timer mode
//设置DatePicker的允许的最大日期。
@property (nullable, nonatomic, strong) NSDate *maximumDate; // default is nil
//设置DatePicker的倒计时间.
/*
 1) 设置日期选择的模
 [self.datePicker setDatePickerMode:UIDatePickerModeCountDownTimer];
 2) 设置倒计时的时长
 注意：设置倒计时时长需要在确定模式之后指定
 // 倒计时的时长，以秒为单位
 [self.datePicker setCountDownDuration:10 * 60];// 十分钟
 */
@property (nonatomic) NSTimeInterval countDownDuration; // for UIDatePickerModeCountDownTimer, ignored otherwise. default is 0.0. limit is 23:59 (86,399 seconds). value being set is div 60 (drops remaining seconds).
/*
 你可以将分钟表盘设置为以不同的时间间隔来显示分钟，前提是该间隔要能够让60整除。默认间隔是一分钟。如果要使用不同的间隔，需要改变 minuteInterval属性：
 // 设置分钟间隔
 datePicker.minuteInterval = 15;
 */
@property (nonatomic) NSInteger      minuteInterval;    // display minutes wheel with interval. interval must be evenly divided into 60. default is 1. min is 1, max is 30
/*
 用 setDate方法。如果选择了使用动画，则表盘会滚动到你指定的日期：
 [datePicker setDate:maxDate animated:YES];
 */
- (void)setDate:(NSDate *)date animated:(BOOL)animated; // if animated is YES, animate the wheels of time to display the new date
@end

NS_ASSUME_NONNULL_END

