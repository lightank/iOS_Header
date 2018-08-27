/*	NSValue.h
	Copyright (c) 1994-2016, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>

/*
 1.由于集合里只能存放对象，不可以存放基本数据类型,所以我们有时候需要讲一些对象比如基本数据类型，结构体等存到NSDictionary NSArray中，我们就需要将这些数据类型或结构体包装成OC对象，以便集合能访问到。常用的用来包装这些类型的有NSNumber NSValue
 2.NSNumber只能包装基本数据类型，比如int, float,char,BOOL等
 3.NSValue可以包装任意一个对象，包括系统自定义的数据结构，结构体等等
 4.NSNumber是NSValue的一个子类
 
 
 //NSValue 可以包装任意值
 NSRange range = {1, 5};
 //将结构体包装成对象
 NSValue *value = [NSValue value:&range withObjCType:@encode(NSRange)];
 NSLog(@"value is %@", value);
 
 //还原
 NSRange newRange;
 [value getValue:&newRange];
 //NSLog(@"%ld, %ld",newRange.location, newRange.length);
 NSLog(@"%@",NSStringFromRange(newRange));
 */

@class NSString, NSDictionary;

NS_ASSUME_NONNULL_BEGIN

@interface NSValue : NSObject <NSCopying, NSSecureCoding>

- (void)getValue:(void *)value;
@property (readonly) const char *objCType NS_RETURNS_INNER_POINTER;

- (instancetype)initWithBytes:(const void *)value objCType:(const char *)type NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSValue (NSValueCreation)

+ (NSValue *)valueWithBytes:(const void *)value objCType:(const char *)type;
+ (NSValue *)value:(const void *)value withObjCType:(const char *)type;

@end

@interface NSValue (NSValueExtensionMethods)

+ (NSValue *)valueWithNonretainedObject:(nullable id)anObject;
@property (nullable, readonly) id nonretainedObjectValue;

+ (NSValue *)valueWithPointer:(nullable const void *)pointer;
@property (nullable, readonly) void *pointerValue;

- (BOOL)isEqualToValue:(NSValue *)value;

@end

@interface NSNumber : NSValue

- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithChar:(char)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithUnsignedChar:(unsigned char)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithShort:(short)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithUnsignedShort:(unsigned short)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithInt:(int)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithUnsignedInt:(unsigned int)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithLong:(long)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithUnsignedLong:(unsigned long)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithLongLong:(long long)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithUnsignedLongLong:(unsigned long long)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithFloat:(float)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithDouble:(double)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithBool:(BOOL)value NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithInteger:(NSInteger)value NS_AVAILABLE(10_5, 2_0) NS_DESIGNATED_INITIALIZER;
- (NSNumber *)initWithUnsignedInteger:(NSUInteger)value NS_AVAILABLE(10_5, 2_0) NS_DESIGNATED_INITIALIZER;

@property (readonly) char charValue;
@property (readonly) unsigned char unsignedCharValue;
@property (readonly) short shortValue;
@property (readonly) unsigned short unsignedShortValue;
@property (readonly) int intValue;
@property (readonly) unsigned int unsignedIntValue;
@property (readonly) long longValue;
@property (readonly) unsigned long unsignedLongValue;
@property (readonly) long long longLongValue;
@property (readonly) unsigned long long unsignedLongLongValue;
@property (readonly) float floatValue;
@property (readonly) double doubleValue;
@property (readonly) BOOL boolValue;
@property (readonly) NSInteger integerValue NS_AVAILABLE(10_5, 2_0);
@property (readonly) NSUInteger unsignedIntegerValue NS_AVAILABLE(10_5, 2_0);

@property (readonly, copy) NSString *stringValue;

- (NSComparisonResult)compare:(NSNumber *)otherNumber;

- (BOOL)isEqualToNumber:(NSNumber *)number;

- (NSString *)descriptionWithLocale:(nullable id)locale;

@end

@interface NSNumber (NSNumberCreation)

+ (NSNumber *)numberWithChar:(char)value;
+ (NSNumber *)numberWithUnsignedChar:(unsigned char)value;
+ (NSNumber *)numberWithShort:(short)value;
+ (NSNumber *)numberWithUnsignedShort:(unsigned short)value;
+ (NSNumber *)numberWithInt:(int)value;
+ (NSNumber *)numberWithUnsignedInt:(unsigned int)value;
+ (NSNumber *)numberWithLong:(long)value;
+ (NSNumber *)numberWithUnsignedLong:(unsigned long)value;
+ (NSNumber *)numberWithLongLong:(long long)value;
+ (NSNumber *)numberWithUnsignedLongLong:(unsigned long long)value;
+ (NSNumber *)numberWithFloat:(float)value;
+ (NSNumber *)numberWithDouble:(double)value;
+ (NSNumber *)numberWithBool:(BOOL)value;
+ (NSNumber *)numberWithInteger:(NSInteger)value NS_AVAILABLE(10_5, 2_0);
+ (NSNumber *)numberWithUnsignedInteger:(NSUInteger)value NS_AVAILABLE(10_5, 2_0);

@end

NS_ASSUME_NONNULL_END
