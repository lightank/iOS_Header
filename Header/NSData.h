/*	NSData.h
	Copyright (c) 1994-2016, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSString, NSURL, NSError;

NS_ASSUME_NONNULL_BEGIN

/****************	Read/Write Options	****************/
//data读取过程的可选配置条件
typedef NS_OPTIONS(NSUInteger, NSDataReadingOptions) {
    NSDataReadingMappedIfSafe =   1UL << 0,	// Hint to map the file in if possible and safe
    NSDataReadingUncached = 1UL << 1,	// Hint to get the file not to be cached in the kernel
    NSDataReadingMappedAlways NS_ENUM_AVAILABLE(10_7, 5_0) = 1UL << 3,	// Hint to map the file in if possible. This takes precedence over NSDataReadingMappedIfSafe if both are given.
    
    // Options with old names for NSData reading methods. Please stop using these old names.
    NSDataReadingMapped = NSDataReadingMappedIfSafe,	// Deprecated name for NSDataReadingMappedIfSafe
    NSMappedRead = NSDataReadingMapped,			// Deprecated name for NSDataReadingMapped
    NSUncachedRead = NSDataReadingUncached		// Deprecated name for NSDataReadingUncached
};
//data写入过程的可选配置条件
typedef NS_OPTIONS(NSUInteger, NSDataWritingOptions) {
    NSDataWritingAtomic = 1UL << 0,	// Hint to use auxiliary file when saving; equivalent to atomically:YES
    NSDataWritingWithoutOverwriting NS_ENUM_AVAILABLE(10_8, 6_0) = 1UL << 1, // Hint to  prevent overwriting an existing file. Cannot be combined with NSDataWritingAtomic.
    
    NSDataWritingFileProtectionNone NS_ENUM_AVAILABLE_IOS(4_0)                                  = 0x10000000,
    NSDataWritingFileProtectionComplete NS_ENUM_AVAILABLE_IOS(4_0)                              = 0x20000000,
    NSDataWritingFileProtectionCompleteUnlessOpen NS_ENUM_AVAILABLE_IOS(5_0)                    = 0x30000000,
    NSDataWritingFileProtectionCompleteUntilFirstUserAuthentication NS_ENUM_AVAILABLE_IOS(5_0)  = 0x40000000,
    NSDataWritingFileProtectionMask NS_ENUM_AVAILABLE_IOS(4_0)                                  = 0xf0000000,
    
    // Options with old names for NSData writing methods. Please stop using these old names.
    NSAtomicWrite = NSDataWritingAtomic	    // Deprecated name for NSDataWritingAtomic
};


/****************	Data Search Options	****************/
//data在搜索过程中的可选配置条件
typedef NS_OPTIONS(NSUInteger, NSDataSearchOptions) {
    NSDataSearchBackwards = 1UL << 0,
    NSDataSearchAnchored = 1UL << 1
} NS_ENUM_AVAILABLE(10_6, 4_0);


/****************        Base 64 Options	****************/
/*** Base64是一组二进制到文本转化的方案，以ASSCII格式表示二进制数据，这些方案用来编码二进制数据以存储或者通过把多媒体文件转换成文本数据进行传输，这个能保证数据在传输的过程中的完整性。Base64最常见的用于是处理电子邮件附件，或者解码小图片。在iOS7之前，Base64的编码和解码是需要自己实现的或者是使用第三方库，但是现在苹果提供一些API来实现Base64功能 ***/
//base64编码中的一些设置选择
typedef NS_OPTIONS(NSUInteger, NSDataBase64EncodingOptions) {
    // Use zero or one of the following to control the maximum line length after which a line ending is inserted. No line endings are inserted by default.
    NSDataBase64Encoding64CharacterLineLength = 1UL << 0,
    NSDataBase64Encoding76CharacterLineLength = 1UL << 1,
    
    // Use zero or more of the following to specify which kind of line ending is inserted. The default line ending is CR LF.
    NSDataBase64EncodingEndLineWithCarriageReturn = 1UL << 4,
    NSDataBase64EncodingEndLineWithLineFeed = 1UL << 5,
    
} NS_ENUM_AVAILABLE(10_9, 7_0);

//base64在解码过程中的option可选条件,下面选项表示在将解码过程中忽略不能识别的字节
typedef NS_OPTIONS(NSUInteger, NSDataBase64DecodingOptions) {
    // Use the following option to modify the decoding algorithm so that it ignores unknown non-Base64 bytes, including line ending characters.
    NSDataBase64DecodingIgnoreUnknownCharacters = 1UL << 0
} NS_ENUM_AVAILABLE(10_9, 7_0);


/****************	Immutable Data		****************/

@interface NSData : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>
//data长度的属性
@property (readonly) NSUInteger length;
/*
 The -bytes method returns a pointer to a contiguous region of memory managed by the receiver.
 If the regions of memory represented by the receiver are already contiguous, it does so in O(1) time, otherwise it may take longer
 Using -enumerateByteRangesUsingBlock: will be efficient for both contiguous and discontiguous data.
 */
//A pointer to the mutable memory managed by the buffer map. (read-only)
//返回data对象的首指针
@property (readonly) const void *bytes NS_RETURNS_INNER_POINTER;

@end

@interface NSData (NSExtendedData)
//返回一个ASCII编码格式的字符串，采用的格式是data属性列表的格式。
@property (readonly, copy) NSString *description;
//取出data中指定长度的字节存入buffer这个提前声明的数组中
- (void)getBytes:(void *)buffer length:(NSUInteger)length;
//取出data中指定位置range的字节存入buffer这个提前声明的数组中
- (void)getBytes:(void *)buffer range:(NSRange)range;
//判断两个data是否相等
- (BOOL)isEqualToData:(NSData *)other;
//指定位置的子data
- (NSData *)subdataWithRange:(NSRange)range;
//将data写入指定的文件
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
//将data写入指定的url
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically; // the atomically flag is ignored if the url is not of a type the supports atomic writes
//将data写入指定文件，并且有写入过程的设置条件，带错误信息
- (BOOL)writeToFile:(NSString *)path options:(NSDataWritingOptions)writeOptionsMask error:(NSError **)errorPtr;
//将data写入指定的url，并且有写入过程的设置条件，带错误信息
- (BOOL)writeToURL:(NSURL *)url options:(NSDataWritingOptions)writeOptionsMask error:(NSError **)errorPtr;
//搜索在data1内部存在data2的位置，并且有搜索配置条件，并且可加入搜索的范围
- (NSRange)rangeOfData:(NSData *)dataToFind options:(NSDataSearchOptions)mask range:(NSRange)searchRange NS_AVAILABLE(10_6, 4_0);

/*
 'block' is called once for each contiguous region of memory in the receiver (once total for contiguous NSDatas), until either all bytes have been enumerated, or the 'stop' parameter is set to YES.
 */
//列举遍历字典的方法
- (void) enumerateByteRangesUsingBlock:(void (NS_NOESCAPE ^)(const void *bytes, NSRange byteRange, BOOL *stop))block NS_AVAILABLE(10_9, 7_0);

@end
/*** 创建data的所有相关方法作为一个类别几种到一块 ***/
@interface NSData (NSDataCreation)
//data的快速创建办法
+ (instancetype)data;
//赋值以bytes开头，长度为length的数据，进行初始化使其成为数据对象的内容
+ (instancetype)dataWithBytes:(nullable const void *)bytes length:(NSUInteger)length;
//这个方法生成的data中保存的是指向数据的指针，并没有对数据进行复制操作。
+ (instancetype)dataWithBytesNoCopy:(void *)bytes length:(NSUInteger)length;
//这个方法生成的data中保存的是指向数据的指针，并没有对数据进行复制操作。当flag为yes的时候，生成的data对象是bytes的所有者，当data对象被释放的时候也会同时释放bytes，所以bytes必须是通过malloc在堆上分配的内存。当flag为no的时候，bytes不会被自动释放，释放bytes时要注意时机，不要再data对象还被使用的时候释放bytes。
+ (instancetype)dataWithBytesNoCopy:(void *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)b;
//加载file文件，并且有可选择读取文件的选项配置条件，带有错误信息
+ (nullable instancetype)dataWithContentsOfFile:(NSString *)path options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
//加载url，并且有可选择读取文件的选项配置条件，带有错误信息
+ (nullable instancetype)dataWithContentsOfURL:(NSURL *)url options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
//从参数path指定的文件读入二进制数据，用该数据初始化NSData对象。
+ (nullable instancetype)dataWithContentsOfFile:(NSString *)path;
//从参数path指定的url读入，用该数据初始化NSData对象。
+ (nullable instancetype)dataWithContentsOfURL:(NSURL *)url;
//赋值以bytes开头，长度为length的数据，进行初始化使其成为数据对象的内容
- (instancetype)initWithBytes:(nullable const void *)bytes length:(NSUInteger)length;
//这个方法生成的data中保存的是指向数据的指针，并没有对数据进行复制操作
- (instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)length;
//这个方法生成的data中保存的是指向数据的指针，并没有对数据进行复制操作。当flag为yes的时候，生成的data对象是bytes的所有者，当data对象被释放的时候也会同时释放bytes，所以bytes必须是通过malloc在堆上分配的内存。当flag为no的时候，bytes不会被自动释放，释放bytes时要注意时机，不要再data对象还被使用的时候释放bytes
- (instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)b;
- (instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)length deallocator:(nullable void (^)(void *bytes, NSUInteger length))deallocator NS_AVAILABLE(10_9, 7_0);
//从参数path指定的文件读入二进制数据，用该数据初始化NSData对象。如果读取文件失败，则释放调用者并返回nil，同时把错误信息写入指针errorPtr。mask是一个选项信息，用于指定是否使用虚拟内存等
- (nullable instancetype)initWithContentsOfFile:(NSString *)path options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
//从参数url指定的路径中读入，用该数据初始化NSData对象。如果读取文件失败，则释放调用者并返回nil，同时把错误信息写入指针errorPtr。mask是一个选项信息，用于指定是否使用虚拟内存等
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
//加载flie文件路径
- (nullable instancetype)initWithContentsOfFile:(NSString *)path;
//加载url
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url;
//用指定的NSData对象aData来创建一个新的NSData对象，参数可以是NSMutableData对象
- (instancetype)initWithData:(NSData *)data;
//用指定的NSData对象aData来创建一个新的NSData对象，参数可以是NSMutableData对象
+ (instancetype)dataWithData:(NSData *)data;

@end
/*** base64方案编码分类  iOS7之后苹果给出以下四个API供实现base64方案 头两个是处理字符串的，后两个是处理UTF-8编码数据的，这两个承兑的方法功能是一样的，但是有时候用其中一个比另一个效率要高。如果你像要bae64编码字符串然后写进文件，你应该使用UTF-8编码数据的这对方法。如果你打算base64编码字符串之后用作json，你应该使用另外一对方法编码解码一一对应***/
@interface NSData (NSDataBase64Encoding)

/* Create an NSData from a Base-64 encoded NSString using the given options. By default, returns nil when the input is not recognized as valid Base-64.
 */
//解码。将已经base64编码之后的字符串数据再转化为NSData数据
- (nullable instancetype)initWithBase64EncodedString:(NSString *)base64String options:(NSDataBase64DecodingOptions)options NS_AVAILABLE(10_9, 7_0);

/* Create a Base-64 encoded NSString from the receiver's contents using the given options.
 */
//编码。将一个data数据利用base64方案转化成base64之后的NSString字符串
- (NSString *)base64EncodedStringWithOptions:(NSDataBase64EncodingOptions)options NS_AVAILABLE(10_9, 7_0);

/* Create an NSData from a Base-64, UTF-8 encoded NSData. By default, returns nil when the input is not recognized as valid Base-64.
 */
//解码。将已经base64编码之后的NSData数据再转化为NSData数据
- (nullable instancetype)initWithBase64EncodedData:(NSData *)base64Data options:(NSDataBase64DecodingOptions)options NS_AVAILABLE(10_9, 7_0);

/* Create a Base-64, UTF-8 encoded NSData from the receiver's contents using the given options.
 */
//编码.将一个data数据利用base64方案转化成base64之后的NSData数据
- (NSData *)base64EncodedDataWithOptions:(NSDataBase64EncodingOptions)options NS_AVAILABLE(10_9, 7_0);

/*
 示例程序：使用第一对编码解码API。
 NSString * stringExample = [NSString stringWithFormat:@"I Love You"];
 NSData * data1 = [stringExample dataUsingEncoding:NSUTF8StringEncoding];
 
 NSString * base64String   = [data1 base64EncodedStringWithOptions:NSDataBase64EncodingEndLineWithCarriageReturn];
 NSLog(@"Base64-encoded string is %@",base64String);
 //log（Base64-encoded string is SSBMb3ZlIFlvdQ==）；
 
 NSData * dataFromString = [[NSData alloc] initWithBase64EncodedString:base64String options:NSDataBase64DecodingIgnoreUnknownCharacters];
 NSLog(@"string is %@",[NSString stringWithUTF8String:[dataFromString bytes]]);
 //log(string is I Love You);
 */

@end


@interface NSData (NSDeprecated)

- (void)getBytes:(void *)buffer NS_DEPRECATED(10_0, 10_10, 2_0, 8_0, "This method is unsafe because it could potentially cause buffer overruns. Use -getBytes:length: instead.");
+ (nullable id)dataWithContentsOfMappedFile:(NSString *)path NS_DEPRECATED(10_0, 10_10, 2_0, 8_0, "Use +dataWithContentsOfURL:options:error: and NSDataReadingMappedIfSafe or NSDataReadingMappedAlways instead.");
- (nullable id)initWithContentsOfMappedFile:(NSString *)path  NS_DEPRECATED(10_0, 10_10, 2_0, 8_0, "Use -initWithContentsOfURL:options:error: and NSDataReadingMappedIfSafe or NSDataReadingMappedAlways instead.");

/* These methods first appeared in NSData.h on OS X 10.9 and iOS 7.0. They are deprecated in the same releases in favor of the methods in the NSDataBase64Encoding category. However, these methods have existed for several releases, so they may be used for applications targeting releases prior to OS X 10.9 and iOS 7.0.
 */
- (nullable id)initWithBase64Encoding:(NSString *)base64String NS_DEPRECATED(10_6, 10_9, 4_0, 7_0);
- (NSString *)base64Encoding NS_DEPRECATED(10_6, 10_9, 4_0, 7_0);

@end

/****************	Mutable Data		****************/

@interface NSMutableData : NSData
//可变data的可变字节
@property (readonly) void *mutableBytes NS_RETURNS_INNER_POINTER;
//可变data的长度
@property NSUInteger length;

@end

@interface NSMutableData (NSExtendedMutableData)
//给可变data追加字节
- (void)appendBytes:(const void *)bytes length:(NSUInteger)length;
//给data追加其他的data
- (void)appendData:(NSData *)other;
//为已经存在的data追加新的长度
- (void)increaseLengthBy:(NSUInteger)extraLength;
//给data替换对应位置的字节
- (void)replaceBytesInRange:(NSRange)range withBytes:(const void *)bytes;
//重置可变data对应位置的字节
- (void)resetBytesInRange:(NSRange)range;
//为可变data设置data数据
- (void)setData:(NSData *)data;
//给data替换对应位置的字节, 并且替换长度
- (void)replaceBytesInRange:(NSRange)range withBytes:(nullable const void *)replacementBytes length:(NSUInteger)replacementLength;

@end

@interface NSMutableData (NSMutableDataCreation)
//动态创建可变data并且初始化指定大小
+ (nullable instancetype)dataWithCapacity:(NSUInteger)aNumItems;
//动态创建可变data并且初始化指定长度
+ (nullable instancetype)dataWithLength:(NSUInteger)length;
//静态创建可变data并且初始化指定大小
- (nullable instancetype)initWithCapacity:(NSUInteger)capacity;
//静态创建可变data并且初始化指定长度
- (nullable instancetype)initWithLength:(NSUInteger)length;

@end

/****************	    Purgeable Data	****************/

NS_CLASS_AVAILABLE(10_6, 4_0)
@interface NSPurgeableData : NSMutableData <NSDiscardableContent> {
@private
    NSUInteger _length;
    int32_t _accessCount;
    uint8_t _private[32];
    void *_reserved;
}

@end

NS_ASSUME_NONNULL_END
