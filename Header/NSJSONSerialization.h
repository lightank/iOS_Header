/*
 NSJSONSerialization.h
 Copyright (c) 2009-2016, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>

@class NSError, NSOutputStream, NSInputStream, NSData;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, NSJSONReadingOptions) {
    //返回可变容器，NSMutableDictionary或NSMutableArray
    NSJSONReadingMutableContainers = (1UL << 0),
    //返回的JSON对象中字符串的值为NSMutableString
    NSJSONReadingMutableLeaves = (1UL << 1),
    //允许JSON字符串最外层既不是NSArray也不是NSDictionary，但必须是有效的JSON Fragment
    NSJSONReadingAllowFragments = (1UL << 2)
} NS_ENUM_AVAILABLE(10_7, 5_0);

typedef NS_OPTIONS(NSUInteger, NSJSONWritingOptions) {
    NSJSONWritingPrettyPrinted = (1UL << 0)
} NS_ENUM_AVAILABLE(10_7, 5_0);

/* A class for converting JSON to Foundation objects and converting Foundation objects to JSON.
 
 An object that may be converted to JSON must have the following properties:
 - Top level object is an NSArray or NSDictionary
 - All objects are NSString, NSNumber, NSArray, NSDictionary, or NSNull
 - All dictionary keys are NSStrings
 - NSNumbers are not NaN or infinity
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSJSONSerialization : NSObject {
@private
    void *reserved[6];
}

/* Returns YES if the given object can be converted to JSON data, NO otherwise. The object must have the following properties:
 - Top level object is an NSArray or NSDictionary
 - All objects are NSString, NSNumber, NSArray, NSDictionary, or NSNull
 - All dictionary keys are NSStrings
 - NSNumbers are not NaN or infinity
 Other rules may apply. Calling this method or attempting a conversion are the definitive ways to tell if a given object can be converted to JSON data.
 */
//返回一个布尔值，指示是否一个给定的对象可以被转换成JSON数据
+ (BOOL)isValidJSONObject:(id)obj;

/* Generate JSON data from a Foundation object. If the object will not produce valid JSON then an exception will be thrown. Setting the NSJSONWritingPrettyPrinted option will generate JSON with whitespace designed to make the output more readable. If that option is not set, the most compact possible JSON will be generated. If an error occurs, the error parameter will be set and the return value will be nil. The resulting data is a encoded in UTF-8.
 */
//将Foundation对象转换为JSON对象
+ (nullable NSData *)dataWithJSONObject:(id)obj options:(NSJSONWritingOptions)opt error:(NSError **)error;

/* Create a Foundation object from JSON data. Set the NSJSONReadingAllowFragments option if the parser should allow top-level objects that are not an NSArray or NSDictionary. Setting the NSJSONReadingMutableContainers option will make the parser generate mutable NSArrays and NSDictionaries. Setting the NSJSONReadingMutableLeaves option will make the parser generate mutable NSString objects. If an error occurs during the parse, then the error parameter will be set and the result will be nil.
 The data must be in one of the 5 supported encodings listed in the JSON specification: UTF-8, UTF-16LE, UTF-16BE, UTF-32LE, UTF-32BE. The data may or may not have a BOM. The most efficient encoding to use for parsing is UTF-8, so if you have a choice in encoding the data passed to this method, use UTF-8.
 */
// 把一个json格式的data,解析为OC中的数据对象(一般为数组或字典)
+ (nullable id)JSONObjectWithData:(NSData *)data options:(NSJSONReadingOptions)opt error:(NSError **)error;

/* Write JSON data into a stream. The stream should be opened and configured. The return value is the number of bytes written to the stream, or 0 on error. All other behavior of this method is the same as the dataWithJSONObject:options:error: method.
 */
//往一个给定的流里写入JSON对象
+ (NSInteger)writeJSONObject:(id)obj toStream:(NSOutputStream *)stream options:(NSJSONWritingOptions)opt error:(NSError **)error;

/* Create a JSON object from JSON data stream. The stream should be opened and configured. All other behavior of this method is the same as the JSONObjectWithData:options:error: method.
 */
//使用文件流的形式来解析json
+ (nullable id)JSONObjectWithStream:(NSInputStream *)stream options:(NSJSONReadingOptions)opt error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
