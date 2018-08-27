/*	NSURL.h
	Copyright (c) 1997-2016, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSCharacterSet.h>
#if !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#import <Foundation/NSURLHandle.h>
#endif

/*
 参考自:http://www.jianshu.com/p/38f5f53dfbad
 
 URI
 
 URL(统一资源定位符) 是一种 URI，URN(统一资源名称) 也是一种 URI，所以 URI (统一资源标志符)可被视为定位符，名称或两者兼备。URN 如同一个人的名称，而 URL 代表一个人的住址。换言之，URN 定义某事物的身份，而 URL 提供查找该事物的方法。例如，ISBN 0-486-27557-4 无二义性地标识出莎士比亚的戏剧《罗密欧与朱丽叶》的某一特定版本，它可以允许人们在不指出其位置和获得方式的情况下谈论这本书。为获得该资源并阅读该书，人们需要它的位置，也就是一个URL地址。在类Unix操作系统中，一个典型的URL地址可能是一个文件目录，例如
 file:///home/username/RomeoAndJuliet.pdf，该URL标识出存储于本地硬盘中的电子书文件。因此，URL和URN有着互补的作用。
 
 语法
 
 URI语法由URI协议名，一个冒号，和协议对应的内容所构成。特定的协议定义了协议内容的语法和语义，而所有的协议都必须遵循一定的URI语法通用规则，亦即为某些专门目的保留部分特殊字符。URI语法同时也就各种原因对协议内容加以其他的限制，例如，保证各种分层协议之间的协同性。百分号编码也为URI提供附加信息。
 
 一般的 URI 格式为：
     scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
 具体的例子如：
 
                     hierarchical part
       ┌───────────────────┴─────────────────────┐
                  authority               path
       ┌───────────────┴───────────────┐┌───┴────┐
 abc://username:password@example.com:123/path/data?key=value&key2=value2#fragid1
 └┬┘   └───────┬───────┘ └────┬────┘ └┬┘           └─────────┬─────────┘ └──┬──┘
 scheme  user information     host     port                  query         fragment
 
 urn:example:mammal:monotreme:echidna
 └┬┘ └────────────┬───────────────┘
 scheme          path
 
 NSURL 根据 RFC 2396(https://www.ietf.org/rfc/rfc2396.txt) 的定义提供了只读属性用于获取 URL 每一部分的值：
 
     scheme，协议名，不带有连接内容的冒号，如“http”。
     user，解码后的用户名。
     password，解码后的 password。
     host，主机域名或 IP 地址。
     port ，端口号。
     path，authority(user，password，host，port)后的部分，如果 URL 对象是 file URL，该属性会去掉最后的/。
     query，解码后的 query 字符串，没有?，但包括连接多个键值对的&。
     fragment，解码后的片段，不包括#。
     parameterString，path 后由分号分隔的部分，如file:///path/to/file;foo中的 foo。
     lastPathComponent，path 部分的最后一段。
     pathExtension，path 指向资源的扩展名。
     pathComponents，由解码后的 path 各段组成的数组。
     resourceSpecifier，冒号后的全部内容。
     absoluteString，将 URL string 和相对的 Base URL 拼接成的完整 URL string。
     absoluteURL，返回一个 NSURL 对象，将 absoluteString 作为该 URL 对象的 string。
     baseURL，如果 URL 对象本身由完整 URL 字符串构成，那么该属性为 nil。
     relativeString，URL 对象的相对部分，即创建时传入的字符串部分。
     relativePath，只包含相对字符串中的 path，而不包括 Base URL 中的。
     standardizedURL，删除掉 path 中的.和..的新的 URL 对象。
     fileSystemRepresentation，c string 表示的文件资源路径。
 
 相等比较
 NSURL 重写了- isEqual:方法，判断条件是，当两个 NSURL 对象的 baseURL 和 relativeString 都相同时，就认为它们是相等的。
 */

@class NSArray<ObjectType>, NSNumber, NSData, NSDictionary<KeyType, ObjectType>;

typedef NSString * NSURLResourceKey NS_EXTENSIBLE_STRING_ENUM;

NS_ASSUME_NONNULL_BEGIN

#if (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
@interface NSURL: NSObject <NSSecureCoding, NSCopying>
#else
@interface NSURL: NSObject <NSSecureCoding, NSCopying, NSURLHandleClient>
#endif
{
    NSString *_urlString;
    NSURL *_baseURL;
    void *_clients;
    void *_reserved;
}

/* Convenience initializers
 */
- (nullable instancetype)initWithScheme:(NSString *)scheme host:(nullable NSString *)host path:(NSString *)path NS_DEPRECATED(10_0, 10_11, 2_0, 9_0, "Use NSURLComponents instead, which lets you create a valid URL with any valid combination of URL components and subcomponents (not just scheme, host and path), and lets you set components and subcomponents with either percent-encoded or un-percent-encoded strings."); // this call percent-encodes both the host and path, so this cannot be used to set a username/password or port in the hostname part or with a IPv6 '[...]' type address. NSURLComponents handles IPv6 addresses correctly.

/* Initializes a newly created file NSURL referencing the local file or directory at path, relative to a base URL.
 */
/*
 创建一个 file URL (协议为file:///)，参数 Path 需要传入一个系统路径，如果路径中包含~，那么需要先调用 NSString 的stringByExpandingTildeInPath方法解析~，如果传入的路径是相对路径，那么生成的 URL 将相对于当前路径。当没有 isDirectory 参数时，如果路径以/结束，则认为路径是一个目录，若不是以/结束，则系统会先检查路径是否存在，若路径存在且是一个目录，则系统会在路径后添加/，若路径不存在，系统则认为路径代表一个文件。而 isDirectory 参数则明确指明路径是否代表一个目录。
 
 */
- (instancetype)initFileURLWithPath:(NSString *)path isDirectory:(BOOL)isDir relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0) NS_DESIGNATED_INITIALIZER;
/* Initializes a newly created file NSURL referencing the local file or directory at path, relative to a base URL.
 */
- (instancetype)initFileURLWithPath:(NSString *)path relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0) NS_DESIGNATED_INITIALIZER; // Better to use initFileURLWithPath:isDirectory:relativeToURL: if you know if the path is a directory vs non-directory, as it saves an I/O.

- (instancetype)initFileURLWithPath:(NSString *)path isDirectory:(BOOL)isDir NS_AVAILABLE(10_5, 2_0) NS_DESIGNATED_INITIALIZER;
- (instancetype)initFileURLWithPath:(NSString *)path NS_DESIGNATED_INITIALIZER;  // Better to use initFileURLWithPath:isDirectory: if you know if the path is a directory vs non-directory, as it saves an i/o.

/* Initializes and returns a newly created file NSURL referencing the local file or directory at path, relative to a base URL.
 */
+ (NSURL *)fileURLWithPath:(NSString *)path isDirectory:(BOOL) isDir relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0);
/* Initializes and returns a newly created file NSURL referencing the local file or directory at path, relative to a base URL.
 */
+ (NSURL *)fileURLWithPath:(NSString *)path relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0); // Better to use fileURLWithPath:isDirectory:relativeToURL: if you know if the path is a directory vs non-directory, as it saves an I/O.

+ (NSURL *)fileURLWithPath:(NSString *)path isDirectory:(BOOL)isDir NS_AVAILABLE(10_5, 2_0);
+ (NSURL *)fileURLWithPath:(NSString *)path; // Better to use fileURLWithPath:isDirectory: if you know if the path is a directory vs non-directory, as it saves an i/o.

/* Initializes a newly created URL referencing the local file or directory at the file system representation of the path. File system representation is a null-terminated C string with canonical UTF-8 encoding.
 */
//通过 c string Path 创建文件 URL 对象。
- (instancetype)initFileURLWithFileSystemRepresentation:(const char *)path isDirectory:(BOOL)isDir relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_9, 7_0) NS_DESIGNATED_INITIALIZER;

/* Initializes and returns a newly created URL referencing the local file or directory at the file system representation of the path. File system representation is a null-terminated C string with canonical UTF-8 encoding.
 */
//通过 c string Path 创建文件 URL 对象。
+ (NSURL *)fileURLWithFileSystemRepresentation:(const char *)path isDirectory:(BOOL) isDir relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_9, 7_0);

/* These methods expect their string arguments to contain any percent escape codes that are necessary. It is an error for URLString to be nil.
 */
/*
 NSURL *baseURL = [NSURL URLWithString:@"http://example.com/v1/"];
 // http://example.com/v1/foo
 [NSURL URLWithString:@"foo" relativeToURL:baseURL];
 // 如果相对路径以/开始，根据规则，URL 最终会拼装为http://example.com/foo
 [NSURL URLWithString:@"/foo" relativeToURL:baseURL];
 // http://example2.com/，因为 URLString 并不是相对的 path 部分，而是完整的 URL，所以最终的值会忽略掉 baseURL。
 [NSURL URLWithString:@"http://example2.com/" relativeToURL:baseURL];
 
 除了字符串类型的 URL 参数，还需要一个 NSURL 类型的 Base URL 参数，字符串类型的 URL 将作为 Base URL 的相对路径。同样字符串类型的 URL 参数要求是经过编码后的，如果不符合规范或者传入了 nil，那么也会返回 nil。
 */
- (nullable instancetype)initWithString:(NSString *)URLString;
- (nullable instancetype)initWithString:(NSString *)URLString relativeToURL:(nullable NSURL *)baseURL NS_DESIGNATED_INITIALIZER;
+ (nullable instancetype)URLWithString:(NSString *)URLString;
+ (nullable instancetype)URLWithString:(NSString *)URLString relativeToURL:(nullable NSURL *)baseURL;


/* Initializes a newly created NSURL using the contents of the given data, relative to a base URL. If the data representation is not a legal URL string as ASCII bytes, the URL object may not behave as expected.
 */
- (instancetype)initWithDataRepresentation:(NSData *)data relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0) NS_DESIGNATED_INITIALIZER;
/* Initializes and returns a newly created NSURL using the contents of the given data, relative to a base URL. If the data representation is not a legal URL string as ASCII bytes, the URL object may not behave as expected.
 */
+ (NSURL *)URLWithDataRepresentation:(NSData *)data relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0);

/* Initializes a newly created absolute NSURL using the contents of the given data, relative to a base URL. If the data representation is not a legal URL string as ASCII bytes, the URL object may not behave as expected.
 */
- (instancetype)initAbsoluteURLWithDataRepresentation:(NSData *)data relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0) NS_DESIGNATED_INITIALIZER;
/* Initializes and returns a newly created absolute NSURL using the contents of the given data, relative to a base URL. If the data representation is not a legal URL string as ASCII bytes, the URL object may not behave as expected.
 */
+ (NSURL *)absoluteURLWithDataRepresentation:(NSData *)data relativeToURL:(nullable NSURL *)baseURL NS_AVAILABLE(10_11, 9_0);

/* Returns the data representation of the URL's relativeString. If the URL was initialized with -initWithData:relativeToURL:, the data representation returned are the same bytes as those used at initialization; otherwise, the data representation returned are the bytes of the relativeString encoded with NSUTF8StringEncoding.
 */
@property (readonly, copy) NSData *dataRepresentation NS_AVAILABLE(10_11, 9_0);

#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(6)
@property (nullable, readonly, copy) NSString *absoluteString;
@property (readonly, copy) NSString *relativeString; // The relative portion of a URL.  If baseURL is nil, or if the receiver is itself absolute, this is the same as absoluteString
@property (nullable, readonly, copy) NSURL *baseURL; // may be nil.
@property (nullable, readonly, copy) NSURL *absoluteURL; // if the receiver is itself absolute, this will return self.

/* Any URL is composed of these two basic pieces.  The full URL would be the concatenation of [myURL scheme], ':', [myURL resourceSpecifier]
 */
@property (nullable, readonly, copy) NSString *scheme;
@property (nullable, readonly, copy) NSString *resourceSpecifier;
#endif // FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(6)

/* If the URL conforms to rfc 1808 (the most common form of URL), the following accessors will return the various components; otherwise they return nil.  The litmus test for conformance is as recommended in RFC 1808 - whether the first two characters of resourceSpecifier is @"//".  In all cases, they return the component's value after resolving the receiver against its base URL.
 */
@property (nullable, readonly, copy) NSString *host;
@property (nullable, readonly, copy) NSNumber *port;
@property (nullable, readonly, copy) NSString *user;
@property (nullable, readonly, copy) NSString *password;
@property (nullable, readonly, copy) NSString *path;
@property (nullable, readonly, copy) NSString *fragment;
@property (nullable, readonly, copy) NSString *parameterString;
@property (nullable, readonly, copy) NSString *query;
@property (nullable, readonly, copy) NSString *relativePath; // The same as path if baseURL is nil

/* Determines if a given URL string's path represents a directory (i.e. the path component in the URL string ends with a '/' character). This does not check the resource the URL refers to.
 */
@property (readonly) BOOL hasDirectoryPath NS_AVAILABLE(10_11, 9_0);

/* Returns the URL's path in file system representation. File system representation is a null-terminated C string with canonical UTF-8 encoding.
 */
//将文件 URL 以 c string 填入到提供的 buffer 中
- (BOOL)getFileSystemRepresentation:(char *)buffer maxLength:(NSUInteger)maxBufferLength NS_AVAILABLE(10_9, 7_0);

/* Returns the URL's path in file system representation. File system representation is a null-terminated C string with canonical UTF-8 encoding. The returned C string will be automatically freed just as a returned object would be released; your code should copy the representation or use getFileSystemRepresentation:maxLength: if it needs to store the representation outside of the autorelease context in which the representation is created.
 */
@property (readonly) const char *fileSystemRepresentation NS_RETURNS_INNER_POINTER NS_AVAILABLE(10_9, 7_0);
//指明 URL 是否使用file:///协议，无论是 file path URL 还是 file reference URL
@property (readonly, getter=isFileURL) BOOL fileURL; // Whether the scheme is file:; if [myURL isFileURL] is YES, then [myURL path] is suitable for input into NSFileManager or NSPathUtilities.

/* A string constant for the "file" URL scheme. If you are using this to compare to a URL's scheme to see if it is a file URL, you should instead use the NSURL fileURL property -- the fileURL property is much faster. */
FOUNDATION_EXPORT NSString *NSURLFileScheme;


@property (nullable, readonly, copy) NSURL *standardizedURL;


/* Returns whether the URL's resource exists and is reachable. This method synchronously checks if the resource's backing store is reachable. Checking reachability is appropriate when making decisions that do not require other immediate operations on the resource, e.g. periodic maintenance of UI state that depends on the existence of a specific document. When performing operations such as opening a file or copying resource properties, it is more efficient to simply try the operation and handle failures. If this method returns NO, the optional error is populated. This method is currently applicable only to URLs for file system resources. For other URL types, NO is returned. Symbol is present in iOS 4, but performs no operation.
 */
//返回布尔值,说明 file URL 指向的文件资源是否可获取，若返回 NO，通过 error 参数可以获取更多信息
- (BOOL)checkResourceIsReachableAndReturnError:(NSError **)error NS_SWIFT_NOTHROW NS_AVAILABLE(10_6, 4_0);


/* Working with file reference URLs
 */

/* Returns whether the URL is a file reference URL. Symbol is present in iOS 4, but performs no operation.
 */
//返回布尔值，说明 URL 对象是否为 file reference URL
- (BOOL)isFileReferenceURL NS_AVAILABLE(10_6, 4_0);

/* Returns a file reference URL that refers to the same resource as a specified file URL. File reference URLs use a URL path syntax that identifies a file system object by reference, not by path. This form of file URL remains valid when the file system path of the URL’s underlying resource changes. An error will occur if the url parameter is not a file URL. File reference URLs cannot be created to file system objects which do not exist or are not reachable. In some areas of the file system hierarchy, file reference URLs cannot be generated to the leaf node of the URL path. A file reference URL's path should never be persistently stored because is not valid across system restarts, and across remounts of volumes -- if you want to create a persistent reference to a file system object, use a bookmark (see -bookmarkDataWithOptions:includingResourceValuesForKeys:relativeToURL:error:). Symbol is present in iOS 4, but performs no operation.
 */
/*
 如果 URL 对象代表了一个 file path URL，那么该方法则返回一个其指向资源对应的 file reference URL，格式如file:///.file/id=16777217.83600349/ file reference URL 直接引用资源，而不是通过资源所在文件系统的路径，这样即使资源的 path 改变，file reference URL 仍然是有效的。如果 URL 对象不是一个 file path URL 或者 path 指向的资源并不存在，那么该方法会返回 nil。如果 URL 对象本身就是 file reference URL 那么该方法返回对象本身。不要直接持久化保存 file reference URL，因为当系统重新启动后它们不再有效，而应该使用 bookmarkDataWithOptions:includingResourceValuesForKeys:relativeToURL:error:。
 */
- (nullable NSURL *)fileReferenceURL NS_AVAILABLE(10_6, 4_0);

/* Returns a file path URL that refers to the same resource as a specified URL. File path URLs use a file system style path. An error will occur if the url parameter is not a file URL. A file reference URL's resource must exist and be reachable to be converted to a file path URL. Symbol is present in iOS 4, but performs no operation.
 */
//如果 URL 对象是一个 file path URL 且指向的资源确实存在，那么该属性返回对象本身，如果 URL 对象是一个 file reference URL，那么则返回对应的 file path URL，否则返回 nil。
@property (nullable, readonly, copy) NSURL *filePathURL NS_AVAILABLE(10_6, 4_0);


/* Resource access
 
 The behavior of resource value caching is slightly different between the NSURL and CFURL API.
 
 When the NSURL methods which get, set, or use cached resource values are used from the main thread, resource values cached by the URL (except those added as temporary properties) are removed the next time the main thread's run loop runs. -removeCachedResourceValueForKey: and -removeAllCachedResourceValues also may be used to remove cached resource values.
 
 The CFURL functions do not automatically remove any resource values cached by the URL. The client has complete control over the cache lifetime. If you are using CFURL API, you must use CFURLClearResourcePropertyCacheForKey or CFURLClearResourcePropertyCache to remove cached resource values.
 */

/* Returns the resource value identified by a given resource key. This method first checks if the URL object already caches the resource value. If so, it returns the cached resource value to the caller. If not, then this method synchronously obtains the resource value from the backing store, adds the resource value to the URL object's cache, and returns the resource value to the caller. The type of the resource value varies by resource property (see resource key definitions). If this method returns YES and value is populated with nil, it means the resource property is not available for the specified resource and no errors occurred when determining the resource property was not available. If this method returns NO, the optional error is populated. This method is currently applicable only to URLs for file system resources. Symbol is present in iOS 4, but performs no operation.
 */
/*
 File System Resource Properties
 
 当 URL 对象为 file URL 时，可以通过特定的 key 设置、获取及删除 URL 对应的某些资源。
 
 系统内置的 key ：
 
 Common File System Resource Keys (https://developer.apple.com/library/ios/documentation/Cocoa/Reference/Foundation/Classes/NSURL_Class/index.html#//apple_ref/doc/constant_group/Common_File_System_Resource_Keys)
 File Property Keys (https://developer.apple.com/library/ios/documentation/Cocoa/Reference/Foundation/Classes/NSURL_Class/index.html#//apple_ref/doc/constant_group/File_Property_Keys)
 Ubiquitous Item Property Keys (https://developer.apple.com/library/ios/documentation/Cocoa/Reference/Foundation/Classes/NSURL_Class/index.html#//apple_ref/doc/constant_group/Ubiquitous_Item_Property_Keys)
 Volume Property Keys (https://developer.apple.com/library/ios/documentation/Cocoa/Reference/Foundation/Classes/NSURL_Class/index.html#//apple_ref/doc/constant_group/Volume_Property_Keys)
 */
// 获取指定 key 的资源内容，
- (BOOL)getResourceValue:(out id _Nullable * _Nonnull)value forKey:(NSURLResourceKey)key error:(out NSError ** _Nullable)error NS_AVAILABLE(10_6, 4_0);

/* Returns the resource values identified by specified array of resource keys. This method first checks if the URL object already caches the resource values. If so, it returns the cached resource values to the caller. If not, then this method synchronously obtains the resource values from the backing store, adds the resource values to the URL object's cache, and returns the resource values to the caller. The type of the resource values vary by property (see resource key definitions). If the result dictionary does not contain a resource value for one or more of the requested resource keys, it means those resource properties are not available for the specified resource and no errors occurred when determining those resource properties were not available. If this method returns NULL, the optional error is populated. This method is currently applicable only to URLs for file system resources. Symbol is present in iOS 4, but performs no operation.
 */
// 返回一个字典，包含了所有指定 key 的对应资源
- (nullable NSDictionary<NSURLResourceKey, id> *)resourceValuesForKeys:(NSArray<NSURLResourceKey> *)keys error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Sets the resource value identified by a given resource key. This method writes the new resource value out to the backing store. Attempts to set a read-only resource property or to set a resource property not supported by the resource are ignored and are not considered errors. If this method returns NO, the optional error is populated. This method is currently applicable only to URLs for file system resources. Symbol is present in iOS 4, but performs no operation.
 */
// 设置某一资源值，并直接持久化保存
- (BOOL)setResourceValue:(nullable id)value forKey:(NSURLResourceKey)key error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Sets any number of resource values of a URL's resource. This method writes the new resource values out to the backing store. Attempts to set read-only resource properties or to set resource properties not supported by the resource are ignored and are not considered errors. If an error occurs after some resource properties have been successfully changed, the userInfo dictionary in the returned error contains an array of resource keys that were not set with the key kCFURLKeysOfUnsetValuesKey. The order in which the resource values are set is not defined. If you need to guarantee the order resource values are set, you should make multiple requests to this method or to -setResourceValue:forKey:error: to guarantee the order. If this method returns NO, the optional error is populated. This method is currently applicable only to URLs for file system resources. Symbol is present in iOS 4, but performs no operation.
 */
// 传入一个字典，设置多个资源值，持久化保存
- (BOOL)setResourceValues:(NSDictionary<NSURLResourceKey, id> *)keyedValues error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

FOUNDATION_EXPORT NSURLResourceKey const NSURLKeysOfUnsetValuesKey NS_AVAILABLE(10_7, 5_0); // Key for the resource properties that have not been set after setResourceValues:error: returns an error, returned as an array of of strings.

/* Removes the cached resource value identified by a given resource value key from the URL object. Removing a cached resource value may remove other cached resource values because some resource values are cached as a set of values, and because some resource values depend on other resource values (temporary resource values have no dependencies). This method is currently applicable only to URLs for file system resources.
 */
// 删除缓存中指定资源 key 的值
- (void)removeCachedResourceValueForKey:(NSURLResourceKey)key NS_AVAILABLE(10_9, 7_0);

/* Removes all cached resource values and all temporary resource values from the URL object. This method is currently applicable only to URLs for file system resources.
 */
// 删除缓存中所有资源 key 的值
- (void)removeAllCachedResourceValues NS_AVAILABLE(10_9, 7_0);

/* Sets a temporary resource value on the URL object. Temporary resource values are for client use. Temporary resource values exist only in memory and are never written to the resource's backing store. Once set, a temporary resource value can be copied from the URL object with -getResourceValue:forKey:error: or -resourceValuesForKeys:error:. To remove a temporary resource value from the URL object, use -removeCachedResourceValueForKey:. Care should be taken to ensure the key that identifies a temporary resource value is unique and does not conflict with system defined keys (using reverse domain name notation in your temporary resource value keys is recommended). This method is currently applicable only to URLs for file system resources.
 */
// 设置自定义资源 key 的值到内存中
- (void)setTemporaryResourceValue:(nullable id)value forKey:(NSURLResourceKey)key NS_AVAILABLE(10_9, 7_0);

/*
 The File System Resource Keys
 
 URLs to file system resources support the properties defined below. Note that not all property values will exist for all file system URLs. For example, if a file is located on a volume that does not support creation dates, it is valid to request the creation date property, but the returned value will be nil, and no error will be generated.
 */

/* Resource keys applicable to all file system objects
 */
FOUNDATION_EXPORT NSURLResourceKey const NSURLNameKey                        NS_AVAILABLE(10_6, 4_0); // The resource name provided by the file system (Read-write, value type NSString)
FOUNDATION_EXPORT NSURLResourceKey const NSURLLocalizedNameKey               NS_AVAILABLE(10_6, 4_0); // Localized or extension-hidden name as displayed to users (Read-only, value type NSString)
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsRegularFileKey               NS_AVAILABLE(10_6, 4_0); // True for regular files (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsDirectoryKey                 NS_AVAILABLE(10_6, 4_0); // True for directories (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsSymbolicLinkKey              NS_AVAILABLE(10_6, 4_0); // True for symlinks (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsVolumeKey                    NS_AVAILABLE(10_6, 4_0); // True for the root directory of a volume (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsPackageKey                   NS_AVAILABLE(10_6, 4_0); // True for packaged directories (Read-only 10_6 and 10_7, read-write 10_8, value type boolean NSNumber). Note: You can only set or clear this property on directories; if you try to set this property on non-directory objects, the property is ignored. If the directory is a package for some other reason (extension type, etc), setting this property to false will have no effect.
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsApplicationKey               NS_AVAILABLE(10_11, 9_0); // True if resource is an application (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLApplicationIsScriptableKey     NS_AVAILABLE(10_11, NA); // True if the resource is scriptable. Only applies to applications (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsSystemImmutableKey           NS_AVAILABLE(10_6, 4_0); // True for system-immutable resources (Read-write, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsUserImmutableKey             NS_AVAILABLE(10_6, 4_0); // True for user-immutable resources (Read-write, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsHiddenKey                    NS_AVAILABLE(10_6, 4_0); // True for resources normally not displayed to users (Read-write, value type boolean NSNumber). Note: If the resource is a hidden because its name starts with a period, setting this property to false will not change the property.
FOUNDATION_EXPORT NSURLResourceKey const NSURLHasHiddenExtensionKey          NS_AVAILABLE(10_6, 4_0); // True for resources whose filename extension is removed from the localized name property (Read-write, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLCreationDateKey                NS_AVAILABLE(10_6, 4_0); // The date the resource was created (Read-write, value type NSDate)
FOUNDATION_EXPORT NSURLResourceKey const NSURLContentAccessDateKey           NS_AVAILABLE(10_6, 4_0); // The date the resource was last accessed (Read-only, value type NSDate)
FOUNDATION_EXPORT NSURLResourceKey const NSURLContentModificationDateKey     NS_AVAILABLE(10_6, 4_0); // The time the resource content was last modified (Read-write, value type NSDate)
FOUNDATION_EXPORT NSURLResourceKey const NSURLAttributeModificationDateKey   NS_AVAILABLE(10_6, 4_0); // The time the resource's attributes were last modified (Read-only, value type NSDate)
FOUNDATION_EXPORT NSURLResourceKey const NSURLLinkCountKey                   NS_AVAILABLE(10_6, 4_0); // Number of hard links to the resource (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLParentDirectoryURLKey          NS_AVAILABLE(10_6, 4_0); // The resource's parent directory, if any (Read-only, value type NSURL)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeURLKey                   NS_AVAILABLE(10_6, 4_0); // URL of the volume on which the resource is stored (Read-only, value type NSURL)
FOUNDATION_EXPORT NSURLResourceKey const NSURLTypeIdentifierKey              NS_AVAILABLE(10_6, 4_0); // Uniform type identifier (UTI) for the resource (Read-only, value type NSString)
FOUNDATION_EXPORT NSURLResourceKey const NSURLLocalizedTypeDescriptionKey    NS_AVAILABLE(10_6, 4_0); // User-visible type or "kind" description (Read-only, value type NSString)
FOUNDATION_EXPORT NSURLResourceKey const NSURLLabelNumberKey                 NS_AVAILABLE(10_6, 4_0); // The label number assigned to the resource (Read-write, value type NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLLabelColorKey                  NS_AVAILABLE(10_6, 4_0); // The color of the assigned label (Read-only, value type NSColor)
FOUNDATION_EXPORT NSURLResourceKey const NSURLLocalizedLabelKey              NS_AVAILABLE(10_6, 4_0); // The user-visible label text (Read-only, value type NSString)
FOUNDATION_EXPORT NSURLResourceKey const NSURLEffectiveIconKey               NS_AVAILABLE(10_6, 4_0); // The icon normally displayed for the resource (Read-only, value type NSImage)
FOUNDATION_EXPORT NSURLResourceKey const NSURLCustomIconKey                  NS_AVAILABLE(10_6, 4_0); // The custom icon assigned to the resource, if any (Currently not implemented, value type NSImage)
FOUNDATION_EXPORT NSURLResourceKey const NSURLFileResourceIdentifierKey      NS_AVAILABLE(10_7, 5_0); // An identifier which can be used to compare two file system objects for equality using -isEqual (i.e, two object identifiers are equal if they have the same file system path or if the paths are linked to same inode on the same file system). This identifier is not persistent across system restarts. (Read-only, value type id <NSCopying, NSCoding, NSSecureCoding, NSObject>)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIdentifierKey            NS_AVAILABLE(10_7, 5_0); // An identifier that can be used to identify the volume the file system object is on. Other objects on the same volume will have the same volume identifier and can be compared using for equality using -isEqual. This identifier is not persistent across system restarts. (Read-only, value type id <NSCopying, NSCoding, NSSecureCoding, NSObject>)
FOUNDATION_EXPORT NSURLResourceKey const NSURLPreferredIOBlockSizeKey        NS_AVAILABLE(10_7, 5_0); // The optimal block size when reading or writing this file's data, or nil if not available. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsReadableKey                  NS_AVAILABLE(10_7, 5_0); // true if this process (as determined by EUID) can read the resource. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsWritableKey                  NS_AVAILABLE(10_7, 5_0); // true if this process (as determined by EUID) can write to the resource. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsExecutableKey                NS_AVAILABLE(10_7, 5_0); // true if this process (as determined by EUID) can execute a file resource or search a directory resource. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLFileSecurityKey                NS_AVAILABLE(10_7, 5_0); // The file system object's security information encapsulated in a NSFileSecurity object. (Read-write, Value type NSFileSecurity)
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsExcludedFromBackupKey        NS_AVAILABLE(10_8, 5_1); // true if resource should be excluded from backups, false otherwise (Read-write, value type boolean NSNumber). This property is only useful for excluding cache and other application support files which are not needed in a backup. Some operations commonly made to user documents will cause this property to be reset to false and so this property should not be used on user documents.
FOUNDATION_EXPORT NSURLResourceKey const NSURLTagNamesKey                    NS_AVAILABLE(10_9, NA);	// The array of Tag names (Read-write, value type NSArray of NSString)
FOUNDATION_EXPORT NSURLResourceKey const NSURLPathKey                        NS_AVAILABLE(10_8, 6_0); // the URL's path as a file system path (Read-only, value type NSString)
FOUNDATION_EXPORT NSURLResourceKey const NSURLCanonicalPathKey               API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)); // the URL's path as a canonical absolute file system path (Read-only, value type NSString)
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsMountTriggerKey              NS_AVAILABLE(10_7, 5_0); // true if this URL is a file system trigger directory. Traversing or opening a file system trigger will cause an attempt to mount a file system on the trigger directory. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLGenerationIdentifierKey NS_AVAILABLE(10_10, 8_0); // An opaque generation identifier which can be compared using isEqual: to determine if the data in a document has been modified. For URLs which refer to the same file inode, the generation identifier will change when the data in the file's data fork is changed (changes to extended attributes or other file system metadata do not change the generation identifier). For URLs which refer to the same directory inode, the generation identifier will change when direct children of that directory are added, removed or renamed (changes to the data of the direct children of that directory will not change the generation identifier). The generation identifier is persistent across system restarts. The generation identifier is tied to a specific document on a specific volume and is not transferred when the document is copied to another volume. This property is not supported by all volumes. (Read-only, value type id <NSCopying, NSCoding, NSSecureCoding, NSObject>)
FOUNDATION_EXPORT NSURLResourceKey const NSURLDocumentIdentifierKey NS_AVAILABLE(10_10, 8_0); // The document identifier -- a value assigned by the kernel to a document (which can be either a file or directory) and is used to identify the document regardless of where it gets moved on a volume. The document identifier survives "safe save” operations; i.e it is sticky to the path it was assigned to (-replaceItemAtURL:withItemAtURL:backupItemName:options:resultingItemURL:error: is the preferred safe-save API). The document identifier is persistent across system restarts. The document identifier is not transferred when the file is copied. Document identifiers are only unique within a single volume. This property is not supported by all volumes. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLAddedToDirectoryDateKey NS_AVAILABLE(10_10, 8_0); // The date the resource was created, or renamed into or within its parent directory. Note that inconsistent behavior may be observed when this attribute is requested on hard-linked items. This property is not supported by all volumes. (Read-only, value type NSDate)
FOUNDATION_EXPORT NSURLResourceKey const NSURLQuarantinePropertiesKey NS_AVAILABLE(10_10, NA); // The quarantine properties as defined in LSQuarantine.h. To remove quarantine information from a file, pass NSNull as the value when setting this property. (Read-write, value type NSDictionary)
FOUNDATION_EXPORT NSURLResourceKey const NSURLFileResourceTypeKey            NS_AVAILABLE(10_7, 5_0); // Returns the file system object type. (Read-only, value type NSString)

typedef NSString * NSURLFileResourceType NS_STRING_ENUM;

/* The file system object type values returned for the NSURLFileResourceTypeKey
 */
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeNamedPipe      NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeCharacterSpecial NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeDirectory      NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeBlockSpecial   NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeRegular        NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeSymbolicLink   NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeSocket         NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeUnknown        NS_AVAILABLE(10_7, 5_0);

FOUNDATION_EXPORT NSURLResourceKey const NSURLThumbnailDictionaryKey         NS_AVAILABLE(10_10, 8_0); // dictionary of NSImage/UIImage objects keyed by size
FOUNDATION_EXPORT NSURLResourceKey const NSURLThumbnailKey                   NS_AVAILABLE_MAC(10_10); // returns all thumbnails as a single NSImage

typedef NSString *NSURLThumbnailDictionaryItem NS_EXTENSIBLE_STRING_ENUM;
/* size keys for the dictionary returned by NSURLThumbnailDictionaryKey
 */
FOUNDATION_EXPORT NSURLThumbnailDictionaryItem const NSThumbnail1024x1024SizeKey         NS_AVAILABLE(10_10, 8_0); // size key for a 1024 x 1024 thumbnail image

/* Resource keys applicable only to regular files
 */
FOUNDATION_EXPORT NSURLResourceKey const NSURLFileSizeKey                    NS_AVAILABLE(10_6, 4_0); // Total file size in bytes (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLFileAllocatedSizeKey           NS_AVAILABLE(10_6, 4_0); // Total size allocated on disk for the file in bytes (number of blocks times block size) (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLTotalFileSizeKey               NS_AVAILABLE(10_7, 5_0); // Total displayable size of the file in bytes (this may include space used by metadata), or nil if not available. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLTotalFileAllocatedSizeKey      NS_AVAILABLE(10_7, 5_0); // Total allocated size of the file in bytes (this may include space used by metadata), or nil if not available. This can be less than the value returned by NSURLTotalFileSizeKey if the resource is compressed. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsAliasFileKey                 NS_AVAILABLE(10_6, 4_0); // true if the resource is a Finder alias file or a symlink, false otherwise ( Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLFileProtectionKey              NS_AVAILABLE_IOS(9_0); // The protection level for this file

typedef NSString * NSURLFileProtectionType NS_STRING_ENUM;
/* The protection level values returned for the NSURLFileProtectionKey
 */
FOUNDATION_EXPORT NSURLFileProtectionType const NSURLFileProtectionNone NS_AVAILABLE_IOS(9_0); // The file has no special protections associated with it. It can be read from or written to at any time.
FOUNDATION_EXPORT NSURLFileProtectionType const NSURLFileProtectionComplete NS_AVAILABLE_IOS(9_0); // The file is stored in an encrypted format on disk and cannot be read from or written to while the device is locked or booting.
FOUNDATION_EXPORT NSURLFileProtectionType const NSURLFileProtectionCompleteUnlessOpen NS_AVAILABLE_IOS(9_0); // The file is stored in an encrypted format on disk. Files can be created while the device is locked, but once closed, cannot be opened again until the device is unlocked. If the file is opened when unlocked, you may continue to access the file normally, even if the user locks the device. There is a small performance penalty when the file is created and opened, though not when being written to or read from. This can be mitigated by changing the file protection to NSURLFileProtectionComplete when the device is unlocked.
FOUNDATION_EXPORT NSURLFileProtectionType const NSURLFileProtectionCompleteUntilFirstUserAuthentication NS_AVAILABLE_IOS(9_0); // The file is stored in an encrypted format on disk and cannot be accessed until after the device has booted. After the user unlocks the device for the first time, your app can access the file and continue to access it even if the user subsequently locks the device.

/* Volumes resource keys
 
 As a convenience, volume resource values can be requested from any file system URL. The value returned will reflect the property value for the volume on which the resource is located.
 */
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeLocalizedFormatDescriptionKey NS_AVAILABLE(10_6, 4_0); // The user-visible volume format (Read-only, value type NSString)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeTotalCapacityKey              NS_AVAILABLE(10_6, 4_0); // Total volume capacity in bytes (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeAvailableCapacityKey          NS_AVAILABLE(10_6, 4_0); // Total free space in bytes (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeResourceCountKey              NS_AVAILABLE(10_6, 4_0); // Total number of resources on the volume (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsPersistentIDsKey      NS_AVAILABLE(10_6, 4_0); // true if the volume format supports persistent object identifiers and can look up file system objects by their IDs (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsSymbolicLinksKey      NS_AVAILABLE(10_6, 4_0); // true if the volume format supports symbolic links (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsHardLinksKey          NS_AVAILABLE(10_6, 4_0); // true if the volume format supports hard links (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsJournalingKey         NS_AVAILABLE(10_6, 4_0); // true if the volume format supports a journal used to speed recovery in case of unplanned restart (such as a power outage or crash). This does not necessarily mean the volume is actively using a journal. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsJournalingKey               NS_AVAILABLE(10_6, 4_0); // true if the volume is currently using a journal for speedy recovery after an unplanned restart. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsSparseFilesKey        NS_AVAILABLE(10_6, 4_0); // true if the volume format supports sparse files, that is, files which can have 'holes' that have never been written to, and thus do not consume space on disk. A sparse file may have an allocated size on disk that is less than its logical length (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsZeroRunsKey           NS_AVAILABLE(10_6, 4_0); // For security reasons, parts of a file (runs) that have never been written to must appear to contain zeroes. true if the volume keeps track of allocated but unwritten runs of a file so that it can substitute zeroes without actually writing zeroes to the media. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsCaseSensitiveNamesKey NS_AVAILABLE(10_6, 4_0); // true if the volume format treats upper and lower case characters in file and directory names as different. Otherwise an upper case character is equivalent to a lower case character, and you can't have two names that differ solely in the case of the characters. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsCasePreservedNamesKey NS_AVAILABLE(10_6, 4_0); // true if the volume format preserves the case of file and directory names.  Otherwise the volume may change the case of some characters (typically making them all upper or all lower case). (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsRootDirectoryDatesKey NS_AVAILABLE(10_7, 5_0); // true if the volume supports reliable storage of times for the root directory. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsVolumeSizesKey        NS_AVAILABLE(10_7, 5_0); // true if the volume supports returning volume size values (NSURLVolumeTotalCapacityKey and NSURLVolumeAvailableCapacityKey). (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsRenamingKey           NS_AVAILABLE(10_7, 5_0); // true if the volume can be renamed. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsAdvisoryFileLockingKey NS_AVAILABLE(10_7, 5_0); // true if the volume implements whole-file flock(2) style advisory locks, and the O_EXLOCK and O_SHLOCK flags of the open(2) call. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsExtendedSecurityKey   NS_AVAILABLE(10_7, 5_0); // true if the volume implements extended security (ACLs). (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsBrowsableKey                NS_AVAILABLE(10_7, 5_0); // true if the volume should be visible via the GUI (i.e., appear on the Desktop as a separate volume). (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeMaximumFileSizeKey            NS_AVAILABLE(10_7, 5_0); // The largest file size (in bytes) supported by this file system, or nil if this cannot be determined. (Read-only, value type NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsEjectableKey                NS_AVAILABLE(10_7, 5_0); // true if the volume's media is ejectable from the drive mechanism under software control. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsRemovableKey                NS_AVAILABLE(10_7, 5_0); // true if the volume's media is removable from the drive mechanism. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsInternalKey                 NS_AVAILABLE(10_7, 5_0); // true if the volume's device is connected to an internal bus, false if connected to an external bus, or nil if not available. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsAutomountedKey              NS_AVAILABLE(10_7, 5_0); // true if the volume is automounted. Note: do not mistake this with the functionality provided by kCFURLVolumeSupportsBrowsingKey. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsLocalKey                    NS_AVAILABLE(10_7, 5_0); // true if the volume is stored on a local device. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsReadOnlyKey                 NS_AVAILABLE(10_7, 5_0); // true if the volume is read-only. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeCreationDateKey               NS_AVAILABLE(10_7, 5_0); // The volume's creation date, or nil if this cannot be determined. (Read-only, value type NSDate)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeURLForRemountingKey           NS_AVAILABLE(10_7, 5_0); // The NSURL needed to remount a network volume, or nil if not available. (Read-only, value type NSURL)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeUUIDStringKey                 NS_AVAILABLE(10_7, 5_0); // The volume's persistent UUID as a string, or nil if a persistent UUID is not available for the volume. (Read-only, value type NSString)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeNameKey                       NS_AVAILABLE(10_7, 5_0); // The name of the volume (Read-write if NSURLVolumeSupportsRenamingKey is YES, otherwise read-only, value type NSString)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeLocalizedNameKey              NS_AVAILABLE(10_7, 5_0); // The user-presentable name of the volume (Read-only, value type NSString)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsEncryptedKey                API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)); // true if the volume is encrypted. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsRootFileSystemKey           API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)); // true if the volume is the root filesystem. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsCompressionKey        API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)); // true if the volume supports transparent decompression of compressed files using decmpfs. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsFileCloningKey API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)); // true if the volume supports clonefile(2) (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsSwapRenamingKey API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)); // true if the volume supports renamex_np(2)'s RENAME_SWAP option (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsExclusiveRenamingKey API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)); // true if the volume supports renamex_np(2)'s RENAME_EXCL option (Read-only, value type boolean NSNumber)

/* Ubiquitous item resource keys
 */
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsUbiquitousItemKey                     NS_AVAILABLE(10_7, 5_0); // true if this item is synced to the cloud, false if it is only a local file. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemHasUnresolvedConflictsKey NS_AVAILABLE(10_7, 5_0); // true if this item has conflicts outstanding. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemIsDownloadedKey           NS_DEPRECATED(10_7, 10_9, 5_0, 7_0, "Use NSURLUbiquitousItemDownloadingStatusKey instead"); // equivalent to NSURLUbiquitousItemDownloadingStatusKey == NSURLUbiquitousItemDownloadingStatusCurrent. Has never behaved as documented in earlier releases, hence deprecated.  (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemIsDownloadingKey          NS_AVAILABLE(10_7, 5_0); // true if data is being downloaded for this item. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemIsUploadedKey             NS_AVAILABLE(10_7, 5_0); // true if there is data present in the cloud for this item. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemIsUploadingKey            NS_AVAILABLE(10_7, 5_0); // true if data is being uploaded for this item. (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemPercentDownloadedKey      NS_DEPRECATED(10_7, 10_8, 5_0, 6_0); // Use NSMetadataQuery and NSMetadataUbiquitousItemPercentDownloadedKey on NSMetadataItem instead
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemPercentUploadedKey        NS_DEPRECATED(10_7, 10_8, 5_0, 6_0); // Use NSMetadataQuery and NSMetadataUbiquitousItemPercentUploadedKey on NSMetadataItem instead
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemDownloadingStatusKey      NS_AVAILABLE(10_9, 7_0); // returns the download status of this item. (Read-only, value type NSString). Possible values below.
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemDownloadingErrorKey       NS_AVAILABLE(10_9, 7_0); // returns the error when downloading the item from iCloud failed, see the NSUbiquitousFile section in FoundationErrors.h (Read-only, value type NSError)
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemUploadingErrorKey         NS_AVAILABLE(10_9, 7_0); // returns the error when uploading the item to iCloud failed, see the NSUbiquitousFile section in FoundationErrors.h (Read-only, value type NSError)
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemDownloadRequestedKey      NS_AVAILABLE(10_10, 8_0); // returns whether a download of this item has already been requested with an API like -startDownloadingUbiquitousItemAtURL:error: (Read-only, value type boolean NSNumber)
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemContainerDisplayNameKey   NS_AVAILABLE(10_10, 8_0); // returns the name of this item's container as displayed to users.

typedef NSString * NSURLUbiquitousItemDownloadingStatus NS_STRING_ENUM;
/* The values returned for the NSURLUbiquitousItemDownloadingStatusKey
 */
FOUNDATION_EXPORT NSURLUbiquitousItemDownloadingStatus const NSURLUbiquitousItemDownloadingStatusNotDownloaded  NS_AVAILABLE(10_9, 7_0); // this item has not been downloaded yet. Use startDownloadingUbiquitousItemAtURL:error: to download it.
FOUNDATION_EXPORT NSURLUbiquitousItemDownloadingStatus const NSURLUbiquitousItemDownloadingStatusDownloaded     NS_AVAILABLE(10_9, 7_0); // there is a local version of this item available. The most current version will get downloaded as soon as possible.
FOUNDATION_EXPORT NSURLUbiquitousItemDownloadingStatus const NSURLUbiquitousItemDownloadingStatusCurrent        NS_AVAILABLE(10_9, 7_0); // there is a local version of this item and it is the most up-to-date version known to this device.

/* Working with Bookmarks and alias (bookmark) files
 */

typedef NS_OPTIONS(NSUInteger, NSURLBookmarkCreationOptions) {
    NSURLBookmarkCreationPreferFileIDResolution NS_ENUM_DEPRECATED(10_6, 10_9, 4_0, 7_0) = ( 1UL << 8 ), /* This option does nothing and has no effect on bookmark resolution */
    NSURLBookmarkCreationMinimalBookmark = ( 1UL << 9 ), /* creates bookmark data with "less" information, which may be smaller but still be able to resolve in certain ways */
    NSURLBookmarkCreationSuitableForBookmarkFile = ( 1UL << 10 ), /* include the properties required by writeBookmarkData:toURL:options: in the bookmark data created */
    NSURLBookmarkCreationWithSecurityScope NS_ENUM_AVAILABLE(10_7, NA) = ( 1 << 11 ), /* include information in the bookmark data which allows the same sandboxed process to access the resource after being relaunched */
    NSURLBookmarkCreationSecurityScopeAllowOnlyReadAccess NS_ENUM_AVAILABLE(10_7, NA) = ( 1 << 12 ), /* if used with kCFURLBookmarkCreationWithSecurityScope, at resolution time only read access to the resource will be granted */
} NS_ENUM_AVAILABLE(10_6, 4_0);

typedef NS_OPTIONS(NSUInteger, NSURLBookmarkResolutionOptions) {
    NSURLBookmarkResolutionWithoutUI = ( 1UL << 8 ), /* don't perform any user interaction during bookmark resolution */
    NSURLBookmarkResolutionWithoutMounting = ( 1UL << 9 ), /* don't mount a volume during bookmark resolution */
    NSURLBookmarkResolutionWithSecurityScope NS_ENUM_AVAILABLE(10_7, NA) = ( 1 << 10 ) /* use the secure information included at creation time to provide the ability to access the resource in a sandboxed process */
} NS_ENUM_AVAILABLE(10_6, 4_0);

typedef NSUInteger NSURLBookmarkFileCreationOptions;

/* Returns bookmark data for the URL, created with specified options and resource values. If this method returns nil, the optional error is populated.
 */
/*
 通过 NSURL 的 bookmarks 相关 API，可以持久化保存文件的路径。所谓 bookmark，是一种 NSData 类型的数据，描述了文件路径的信息。将 bookmark 持久化保存，当应用重新启动后，可通过 bookmark 获取到对应文件路径的 URL，即使期间文件被重新命名或移动到其他路径。
 创建一个 NSURL 对象对应的 bookmark。
 参数 options 有两个值，NSURLBookmarkCreationMinimalBookmark指通过尽可能少的信息创建一个 bookmark，NSURLBookmarkCreationSuitableForBookmarkFile指创建的 bookmark 需要包含用于创建 Finder alias files 的属性。
 参数 keys，通过传入 key 的数组，指明哪些 URL 资源需要保存到 bookmark 中
 参数 relativeURL 指 bookmark 相对的 URL
 */
- (nullable NSData *)bookmarkDataWithOptions:(NSURLBookmarkCreationOptions)options includingResourceValuesForKeys:(nullable NSArray<NSURLResourceKey> *)keys relativeToURL:(nullable NSURL *)relativeURL error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Initializes a newly created NSURL that refers to a location specified by resolving bookmark data. If this method returns nil, the optional error is populated.
 */
- (nullable instancetype)initByResolvingBookmarkData:(NSData *)bookmarkData options:(NSURLBookmarkResolutionOptions)options relativeToURL:(nullable NSURL *)relativeURL bookmarkDataIsStale:(BOOL * _Nullable)isStale error:(NSError **)error NS_AVAILABLE(10_6, 4_0);
/* Creates and Initializes an NSURL that refers to a location specified by resolving bookmark data. If this method returns nil, the optional error is populated.
 */
/*
 通过解析 bookmark 转换成一个 NSURL 对象，额外的参数：
 options，NSURLBookmarkResolutionWithoutUI、NSURLBookmarkResolutionWithoutMounting
 relativeURL，bookmark 相对的 URL
 isStale，指定转换后，bookmark 是否失效
 */
+ (nullable instancetype)URLByResolvingBookmarkData:(NSData *)bookmarkData options:(NSURLBookmarkResolutionOptions)options relativeToURL:(nullable NSURL *)relativeURL bookmarkDataIsStale:(BOOL * _Nullable)isStale error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Returns the resource values for properties identified by a specified array of keys contained in specified bookmark data. If the result dictionary does not contain a resource value for one or more of the requested resource keys, it means those resource properties are not available in the bookmark data.
 */
//获取保存在 bookmark 中的 URL 资源。
+ (nullable NSDictionary<NSURLResourceKey, id> *)resourceValuesForKeys:(NSArray<NSURLResourceKey> *)keys fromBookmarkData:(NSData *)bookmarkData NS_AVAILABLE(10_6, 4_0);

/* Creates an alias file on disk at a specified location with specified bookmark data. bookmarkData must have been created with the NSURLBookmarkCreationSuitableForBookmarkFile option. bookmarkFileURL must either refer to an existing file (which will be overwritten), or to location in an existing directory. If this method returns NO, the optional error is populated.
 */
/*
 指定一个 alias file 的路径，将 NSData 类型的 bookmark 持久化保存在其中，可以将这个 alias file 理解为一个 symbolic link。
 */
+ (BOOL)writeBookmarkData:(NSData *)bookmarkData toURL:(NSURL *)bookmarkFileURL options:(NSURLBookmarkFileCreationOptions)options error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Initializes and returns bookmark data derived from an alias file pointed to by a specified URL. If bookmarkFileURL refers to an alias file created prior to OS X v10.6 that contains Alias Manager information but no bookmark data, this method synthesizes bookmark data for the file. If this method returns nil, the optional error is populated.
 */
//从创建的 alias file 获取 bookmark
+ (nullable NSData *)bookmarkDataWithContentsOfURL:(NSURL *)bookmarkFileURL error:(NSError **)error NS_AVAILABLE(10_6, 4_0);

/* Creates and initializes a NSURL that refers to the location specified by resolving the alias file at url. If the url argument does not refer to an alias file as defined by the NSURLIsAliasFileKey property, the NSURL returned is the same as url argument. This method fails and returns nil if the url argument is unreachable, or if the original file or directory could not be located or is not reachable, or if the original file or directory is on a volume that could not be located or mounted. If this method fails, the optional error is populated. The NSURLBookmarkResolutionWithSecurityScope option is not supported by this method.
 */
//直接通过 alias file 的 URL 获取保存在其中的 bookmark 对应的真正 URL，options 参数指明了如何解析 bookmark。
+ (nullable instancetype)URLByResolvingAliasFileAtURL:(NSURL *)url options:(NSURLBookmarkResolutionOptions)options error:(NSError **)error NS_AVAILABLE(10_10, 8_0);

/*  Given a NSURL created by resolving a bookmark data created with security scope, make the resource referenced by the url accessible to the process. When access to this resource is no longer needed the client must call stopAccessingSecurityScopedResource. Each call to startAccessingSecurityScopedResource must be balanced with a call to stopAccessingSecurityScopedResource (Note: this is not reference counted).
 */
- (BOOL)startAccessingSecurityScopedResource NS_AVAILABLE(10_7, 8_0);

/*  Revokes the access granted to the url by a prior successful call to startAccessingSecurityScopedResource.
 */
- (void)stopAccessingSecurityScopedResource NS_AVAILABLE(10_7, 8_0);

@end


@interface NSURL (NSPromisedItems)

/* Get resource values from URLs of 'promised' items. A promised item is not guaranteed to have its contents in the file system until you use NSFileCoordinator to perform a coordinated read on its URL, which causes the contents to be downloaded or otherwise generated. Promised item URLs are returned by various APIs, including currently:
 - NSMetadataQueryUbiquitousDataScope
 - NSMetadataQueryUbiquitousDocumentsScope
 - An NSFilePresenter presenting the contents of the directory located by -URLForUbiquitousContainerIdentifier: or a subdirectory thereof
 
 The following methods behave identically to their similarly named methods above (-getResourceValue:forKey:error:, etc.), except that they allow you to get resource values and check for presence regardless of whether the promised item's contents currently exist at the URL. You must use these APIs instead of the normal NSURL resource value APIs if and only if any of the following are true:
 - You are using a URL that you know came directly from one of the above APIs
 - You are inside the accessor block of a coordinated read or write that used NSFileCoordinatorReadingImmediatelyAvailableMetadataOnly, NSFileCoordinatorWritingForDeleting, NSFileCoordinatorWritingForMoving, or NSFileCoordinatorWritingContentIndependentMetadataOnly
 
 Most of the NSURL resource value keys will work with these APIs. However, there are some that are tied to the item's contents that will not work, such as NSURLContentAccessDateKey or NSURLGenerationIdentifierKey. If one of these keys is used, the method will return YES, but the value for the key will be nil.
 */
- (BOOL)getPromisedItemResourceValue:(id _Nullable * _Nonnull)value forKey:(NSURLResourceKey)key error:(NSError **)error NS_AVAILABLE(10_10, 8_0);
- (nullable NSDictionary<NSURLResourceKey, id> *)promisedItemResourceValuesForKeys:(NSArray<NSURLResourceKey> *)keys error:(NSError **)error NS_AVAILABLE(10_10, 8_0);
- (BOOL)checkPromisedItemIsReachableAndReturnError:(NSError **)error NS_SWIFT_NOTHROW NS_AVAILABLE(10_10, 8_0);

@end



NS_CLASS_AVAILABLE(10_10, 8_0)
// NSURLQueryItem encapsulates a single query name-value pair. The name and value strings of a query name-value pair are not percent encoded. For use with the NSURLComponents queryItems property.
@interface NSURLQueryItem : NSObject <NSSecureCoding, NSCopying> {
@private
    NSString *_name;
    NSString *_value;
}
- (instancetype)initWithName:(NSString *)name value:(nullable NSString *)value NS_DESIGNATED_INITIALIZER;
+ (instancetype)queryItemWithName:(NSString *)name value:(nullable NSString *)value;
@property (readonly) NSString *name;
@property (nullable, readonly) NSString *value;
@end


NS_CLASS_AVAILABLE(10_9, 7_0)
/*
 NSURLComponents 是一个用于解析和构建 URL 的类，
 通过 NSURLComponents 可以单独修改 URL 的某一部分，获取某一部分编码后的值
 */
@interface NSURLComponents : NSObject <NSCopying>

// Initialize a NSURLComponents with all components undefined. Designated initializer.
- (instancetype)init;

// Initialize a NSURLComponents with the components of a URL. If resolvingAgainstBaseURL is YES and url is a relative URL, the components of [url absoluteURL] are used. If the url string from the NSURL is malformed, nil is returned.
- (nullable instancetype)initWithURL:(NSURL *)url resolvingAgainstBaseURL:(BOOL)resolve;

// Initializes and returns a newly created NSURLComponents with the components of a URL. If resolvingAgainstBaseURL is YES and url is a relative URL, the components of [url absoluteURL] are used. If the url string from the NSURL is malformed, nil is returned.
// 通过传入的 URL 对象创建，resolve 参数决定是否解析 URL 对象的 baseURL
+ (nullable instancetype)componentsWithURL:(NSURL *)url resolvingAgainstBaseURL:(BOOL)resolve;

// Initialize a NSURLComponents with a URL string. If the URLString is malformed, nil is returned.
- (nullable instancetype)initWithString:(NSString *)URLString;

// Initializes and returns a newly created NSURLComponents with a URL string. If the URLString is malformed, nil is returned.
// 通过传入的 URL string 创建
+ (nullable instancetype)componentsWithString:(NSString *)URLString;

// Returns a URL created from the NSURLComponents. If the NSURLComponents has an authority component (user, password, host or port) and a path component, then the path must either begin with "/" or be an empty string. If the NSURLComponents does not have an authority component (user, password, host or port) and has a path component, the path component must not start with "//". If those requirements are not met, nil is returned.
//返回 URL 对象
@property (nullable, readonly, copy) NSURL *URL;

// Returns a URL created from the NSURLComponents relative to a base URL. If the NSURLComponents has an authority component (user, password, host or port) and a path component, then the path must either begin with "/" or be an empty string. If the NSURLComponents does not have an authority component (user, password, host or port) and has a path component, the path component must not start with "//". If those requirements are not met, nil is returned.
//返回 URL 对象并相对于传入的 baseURL 参数
- (nullable NSURL *)URLRelativeToURL:(nullable NSURL *)baseURL;

// Returns a URL string created from the NSURLComponents. If the NSURLComponents has an authority component (user, password, host or port) and a path component, then the path must either begin with "/" or be an empty string. If the NSURLComponents does not have an authority component (user, password, host or port) and has a path component, the path component must not start with "//". If those requirements are not met, nil is returned.
//返回 URL string
@property (nullable, readonly, copy) NSString *string NS_AVAILABLE(10_10, 8_0);

// Warning: IETF STD 66 (rfc3986) says the use of the format "user:password" in the userinfo subcomponent of a URI is deprecated because passing authentication information in clear text has proven to be a security risk. However, there are cases where this practice is still needed, and so the user and password components and methods are provided.

// Getting these properties removes any percent encoding these components may have (if the component allows percent encoding). Setting these properties assumes the subcomponent or component string is not percent encoded and will add percent encoding (if the component allows percent encoding).
//可读写的 URL 各部分的属性
@property (nullable, copy) NSString *scheme; // Attempting to set the scheme with an invalid scheme string will cause an exception.
@property (nullable, copy) NSString *user;
@property (nullable, copy) NSString *password;
@property (nullable, copy) NSString *host;
@property (nullable, copy) NSNumber *port; // Attempting to set a negative port number will cause an exception.
@property (nullable, copy) NSString *path;
@property (nullable, copy) NSString *query;
@property (nullable, copy) NSString *fragment;

// Getting these properties retains any percent encoding these components may have. Setting these properties assumes the component string is already correctly percent encoded. Attempting to set an incorrectly percent encoded string will cause an exception. Although ';' is a legal path character, it is recommended that it be percent-encoded for best compatibility with NSURL (-stringByAddingPercentEncodingWithAllowedCharacters: will percent-encode any ';' characters if you pass the URLPathAllowedCharacterSet).
//百分号编码后的各部分的读写属性
@property (nullable, copy) NSString *percentEncodedUser;
@property (nullable, copy) NSString *percentEncodedPassword;
@property (nullable, copy) NSString *percentEncodedHost;
@property (nullable, copy) NSString *percentEncodedPath;
@property (nullable, copy) NSString *percentEncodedQuery;
@property (nullable, copy) NSString *percentEncodedFragment;

/* These properties return the character range of a component in the URL string returned by -[NSURLComponents string]. If the component does not exist in the NSURLComponents object, {NSNotFound, 0} is returned. Note: Zero length components are legal. For example, the URL string "scheme://:@/?#" has a zero length user, password, host, query and fragment; the URL strings "scheme:" and "" both have a zero length path.
 */
@property (readonly) NSRange rangeOfScheme NS_AVAILABLE(10_11, 9_0);
@property (readonly) NSRange rangeOfUser NS_AVAILABLE(10_11, 9_0);
@property (readonly) NSRange rangeOfPassword NS_AVAILABLE(10_11, 9_0);
@property (readonly) NSRange rangeOfHost NS_AVAILABLE(10_11, 9_0);
@property (readonly) NSRange rangeOfPort NS_AVAILABLE(10_11, 9_0);
@property (readonly) NSRange rangeOfPath NS_AVAILABLE(10_11, 9_0);
@property (readonly) NSRange rangeOfQuery NS_AVAILABLE(10_11, 9_0);
@property (readonly) NSRange rangeOfFragment NS_AVAILABLE(10_11, 9_0);

// The getter method that underlies the queryItems property parses the query string based on these delimiters and returns an NSArray containing any number of NSURLQueryItem objects, each of which represents a single key-value pair, in the order in which they appear in the original query string.  Note that a name may appear more than once in a single query string, so the name values are not guaranteed to be unique. If the NSURLComponents object has an empty query component, queryItems returns an empty NSArray. If the NSURLComponents object has no query component, queryItems returns nil.
// The setter method that underlies the queryItems property combines an NSArray containing any number of NSURLQueryItem objects, each of which represents a single key-value pair, into a query string and sets the NSURLComponents' query property. Passing an empty NSArray to setQueryItems sets the query component of the NSURLComponents object to an empty string. Passing nil to setQueryItems removes the query component of the NSURLComponents object.
// Note: If a name-value pair in a query is empty (i.e. the query string starts with '&', ends with '&', or has "&&" within it), you get a NSURLQueryItem with a zero-length name and and a nil value. If a query's name-value pair has nothing before the equals sign, you get a zero-length name. If a query's name-value pair has nothing after the equals sign, you get a zero-length value. If a query's name-value pair has no equals sign, the query name-value pair string is the name and you get a nil value.
//其中queryItems属性是一个包含 NSURLQueryItem 对象的数组，每一个 NSURLQueryItem 对象代表了 query string 中的一个键值对
@property (nullable, copy) NSArray<NSURLQueryItem *> *queryItems NS_AVAILABLE(10_10, 8_0);

@end

/*
 URL Encode
 
 URL 采用 ASCII 编码格式，所以不支持如中文等非 ASCII 码字符，另外 URL 中保留的分隔符号(?、&、=等)也无法作为内容，否则会引起歧义。这就需要通过编码，用安全的字符来表示这些不符合要求的字符，格式是%加两位安全字符，所以 URL 编码也称为百分号编码。在 iOS 中的相关操作分别为：
 */
@interface NSCharacterSet (NSURLUtilities)
#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
// Predefined character sets for the six URL components and subcomponents which allow percent encoding. These character sets are passed to -stringByAddingPercentEncodingWithAllowedCharacters:.

// Returns a character set containing the characters allowed in an URL's user subcomponent.
@property (class, readonly, copy) NSCharacterSet *URLUserAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

// Returns a character set containing the characters allowed in an URL's password subcomponent.
@property (class, readonly, copy) NSCharacterSet *URLPasswordAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

// Returns a character set containing the characters allowed in an URL's host subcomponent.
@property (class, readonly, copy) NSCharacterSet *URLHostAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

// Returns a character set containing the characters allowed in an URL's path component. ';' is a legal path character, but it is recommended that it be percent-encoded for best compatibility with NSURL (-stringByAddingPercentEncodingWithAllowedCharacters: will percent-encode any ';' characters if you pass the URLPathAllowedCharacterSet).
@property (class, readonly, copy) NSCharacterSet *URLPathAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

// Returns a character set containing the characters allowed in an URL's query component.
@property (class, readonly, copy) NSCharacterSet *URLQueryAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);

// Returns a character set containing the characters allowed in an URL's fragment component.
@property (class, readonly, copy) NSCharacterSet *URLFragmentAllowedCharacterSet NS_AVAILABLE(10_9, 7_0);
#endif
@end

/*
 URL Unencode
 
 // 有时从服务端获取的 URL 中，空格被编码为+,
 // 而方法- stringByRemovingPercentEncoding只替换百分号编码，
 // 所以要在执行该方法前，先将`+`替换掉(真正的加号字符是被百分号编码的)
 NSString *result = [URLString stringByReplacingOccurrencesOfString:@"+" withString:@" "];
 result = [result stringByRemovingPercentEncoding];
 */
@interface NSString (NSURLUtilities)

// Returns a new string made from the receiver by replacing all characters not in the allowedCharacters set with percent encoded characters. UTF-8 encoding is used to determine the correct percent encoded characters. Entire URL strings cannot be percent-encoded. This method is intended to percent-encode an URL component or subcomponent string, NOT the entire URL string. Any characters in allowedCharacters outside of the 7-bit ASCII range are ignored.
- (nullable NSString *)stringByAddingPercentEncodingWithAllowedCharacters:(NSCharacterSet *)allowedCharacters NS_AVAILABLE(10_9, 7_0);

// Returns a new string made from the receiver by replacing all percent encoded sequences with the matching UTF-8 characters.
@property (nullable, readonly, copy) NSString *stringByRemovingPercentEncoding NS_AVAILABLE(10_9, 7_0);


- (nullable NSString *)stringByAddingPercentEscapesUsingEncoding:(NSStringEncoding)enc NS_DEPRECATED(10_0, 10_11, 2_0, 9_0, "Use -stringByAddingPercentEncodingWithAllowedCharacters: instead, which always uses the recommended UTF-8 encoding, and which encodes for a specific URL component or subcomponent since each URL component or subcomponent has different rules for what characters are valid.");
- (nullable NSString *)stringByReplacingPercentEscapesUsingEncoding:(NSStringEncoding)enc NS_DEPRECATED(10_0, 10_11, 2_0, 9_0, "Use -stringByRemovingPercentEncoding instead, which always uses the recommended UTF-8 encoding.");

@end


@interface NSURL (NSURLPathUtilities)

/* The following methods work on the path portion of a URL in the same manner that the NSPathUtilities methods on NSString do.
 */
//传入一个字符串类型元素的数组，该方法用/将这些元素组装成一个 file URL。
+ (nullable NSURL *)fileURLWithPathComponents:(NSArray<NSString *> *)components NS_AVAILABLE(10_6, 4_0);
@property (nullable, readonly, copy) NSArray<NSString *> *pathComponents NS_AVAILABLE(10_6, 4_0);
@property (nullable, readonly, copy) NSString *lastPathComponent NS_AVAILABLE(10_6, 4_0);
@property (nullable, readonly, copy) NSString *pathExtension NS_AVAILABLE(10_6, 4_0);
#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(6)
//返回一个新的 file path URL，这个 URL 在原 URL 对象后添加了传入的一段路径参数。该方法会自动在原 URL 对象和新的 path 间加入/，如果 path 参数最后没有以/结尾，那么该方法会同步检测新 URL 对象指向的资源是否存在且是一个目录，如果路径指向网络挂载卷，这将会造成严重的性能损耗。
- (nullable NSURL *)URLByAppendingPathComponent:(NSString *)pathComponent NS_AVAILABLE(10_6, 4_0);
//功能同上一个方法，不过可以通过 isDirectory 参数具体指明新的 file URL 是否为一个目录，从而避免系统的同步检测。
- (nullable NSURL *)URLByAppendingPathComponent:(NSString *)pathComponent isDirectory:(BOOL)isDirectory NS_AVAILABLE(10_7, 5_0);
//去掉最后一段 path 的 URL 对象
@property (nullable, readonly, copy) NSURL *URLByDeletingLastPathComponent NS_AVAILABLE(10_6, 4_0);
//返回一个添加扩展名的 URL 对象，该方法会自动去掉原 URL 对象最后的/并添加.
- (nullable NSURL *)URLByAppendingPathExtension:(NSString *)pathExtension NS_AVAILABLE(10_6, 4_0);
//去掉最后一段文件扩展名的 URL 对象
@property (nullable, readonly, copy) NSURL *URLByDeletingPathExtension NS_AVAILABLE(10_6, 4_0);
#endif // FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(6)

/* The following methods work only on `file:` scheme URLs; for non-`file:` scheme URLs, these methods return the URL unchanged.
 */
//将原 URL 对象表示的 file path 标准化，包括转换~标识符，去掉多余的空格和/，转换..等操作。
@property (nullable, readonly, copy) NSURL *URLByStandardizingPath NS_AVAILABLE(10_6, 4_0);
//一个解析了 symbolic link 后的 URL
@property (nullable, readonly, copy) NSURL *URLByResolvingSymlinksInPath NS_AVAILABLE(10_6, 4_0);

@end


#if (TARGET_OS_MAC || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
/* NSFileSecurity encapsulates a file system object's security information. NSFileSecurity and CFFileSecurity are toll-free bridged. Use the CFFileSecurity API for access to the low-level file security properties encapsulated by NSFileSecurity.
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSFileSecurity : NSObject <NSCopying, NSCoding>
- (nullable instancetype) initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
@end
#endif


/* deprecated interfaces
 */

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
/* NSURLClient and NSURLLoading are deprecated; use NSURLConnection instead.
 */

/* Client informal protocol for use with the deprecated loadResourceDataNotifyingClient: below.
 */
#if !defined(SWIFT_CLASS_EXTRA)
@interface NSObject (NSURLClient)
- (void)URL:(NSURL *)sender resourceDataDidBecomeAvailable:(NSData *)newBytes NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)URLResourceDidFinishLoading:(NSURL *)sender NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)URLResourceDidCancelLoading:(NSURL *)sender NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (void)URL:(NSURL *)sender resourceDidFailLoadingWithReason:(NSString *)reason NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
@end
#endif

@interface NSURL (NSURLLoading)
- (nullable NSData *)resourceDataUsingCache:(BOOL)shouldUseCache NS_DEPRECATED(10_0, 10_4, 2_0, 2_0); // Blocks to load the data if necessary.  If shouldUseCache is YES, then if an equivalent URL has already been loaded and cached, its resource data will be returned immediately.  If shouldUseCache is NO, a new load will be started
- (void)loadResourceDataNotifyingClient:(id)client usingCache:(BOOL)shouldUseCache NS_DEPRECATED(10_0, 10_4, 2_0, 2_0); // Starts an asynchronous load of the data, registering delegate to receive notification.  Only one such background load can proceed at a time.
- (nullable id)propertyForKey:(NSString *)propertyKey NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

/* These attempt to write the given arguments for the resource specified by the URL; they return success or failure
 */
- (BOOL)setResourceData:(NSData *)data NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);
- (BOOL)setProperty:(id)property forKey:(NSString *)propertyKey NS_DEPRECATED(10_0, 10_4, 2_0, 2_0);

- (nullable NSURLHandle *)URLHandleUsingCache:(BOOL)shouldUseCache NS_DEPRECATED(10_0, 10_4, 2_0, 2_0); // Sophisticated clients will want to ask for this, then message the handle directly.  If shouldUseCache is NO, a newly instantiated handle is returned, even if an equivalent URL has been loaded
@end
#endif

NS_ASSUME_NONNULL_END
