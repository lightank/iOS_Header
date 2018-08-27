/*
 NSURLProtocol.h
 Copyright (c) 2003-2017, Apple Inc. All rights reserved.
 
 Public header file.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSURLCache.h>

@class NSCachedURLResponse;
@class NSError;
@class NSMutableURLRequest;
@class NSURLAuthenticationChallenge;
@class NSURLConnection;
@class NSURLProtocol;
@class NSURLProtocolInternal;
@class NSURLRequest;
@class NSURLResponse;
@class NSURLSessionTask;

NS_ASSUME_NONNULL_BEGIN

/*!
 @header NSURLProtocol.h
 
 This header file describes the constructs used to represent URL
 protocols, and describes the extensible system by which specific
 classes can be made to handle the loading of particular URL types or
 schemes.
 
 <p>NSURLProtocol is an abstract class which provides the
 basic structure for performing protocol-specific loading of URL
 data.
 
 <p>The NSURLProtocolClient describes the integration points a
 protocol implemention can use to hook into the URL loading system.
 NSURLProtocolClient describes the methods a protocol implementation
 needs to drive the URL loading system from a NSURLProtocol subclass.
 
 <p>To support customization of protocol-specific requests,
 protocol implementors are encouraged to provide categories on
 NSURLRequest and NSMutableURLRequest. Protocol implementors who
 need to extend the capabilities of NSURLRequest and
 NSMutableURLRequest in this way can store and retrieve
 protocol-specific request data by using the
 <tt>+propertyForKey:inRequest:</tt> and
 <tt>+setProperty:forKey:inRequest:</tt> class methods on
 NSURLProtocol. See the NSHTTPURLRequest on NSURLRequest and
 NSMutableHTTPURLRequest on NSMutableURLRequest for examples of
 such extensions.
 
 <p>An essential responsibility for a protocol implementor is
 creating a NSURLResponse for each request it processes successfully.
 A protocol implementor may wish to create a custom, mutable
 NSURLResponse class to aid in this work.
 */

/*!
 @protocol NSURLProtocolClient
 @discussion NSURLProtocolClient provides the interface to the URL
 loading system that is intended for use by NSURLProtocol
 implementors.
 */
/*！
 @header NSURLProtocol.h
 
 此头文件描述用于表示URL的结构
 协议，并描述了具体的可扩展系统
 可以进行类来处理特定URL类型的加载
 方案。
 
 NSURLProtocol是一个提供的抽象类
 执行协议特定加载URL的基本结构
 数据。
 
 <p> NSURLProtocolClient描述了积分点a
 协议实现可以用于挂载到URL加载系统中。
 NSURLProtocolClient描述了协议实现的方法
 需要从NSURLProtocol子类驱动URL加载系统。
 
 <p>为了支持协议特定请求的定制，
 鼓励协议实施者提供类别
 NSURLRequest和NSMutableURLRequest。协议实现者谁
 需要扩展NSURLRequest的功能
 NSMutableURLRequest以这种方式可以存储和检索
 通过使用协议特定的请求数据
 <tt> + propertyForKey：inRequest：</ tt>和
 <tt> + setProperty：forKey：inRequest：</ tt>类方法
 NSURLProtocol。请参阅NSURLRequest上的NSHTTPURLRequest和
 关于NSMutableURLRequest的NSMutableHTTPURLRequest的例子
 这样的扩展。
 
 协议实现者的重要责任是
 为其成功处理的每个请求创建一个NSURLResponse。
 协议实现者可能希望创建一个定制的，可变的
 NSURLResponse类帮助这项工作。
 */

/*！
 @protocol NSURLProtocolClient
 @discussion NSURLProtocolClient提供了URL的接口
 加载NSURLProtocol使用的系统
 实现者。
 */
@protocol NSURLProtocolClient <NSObject>

/*!
 @method URLProtocol:wasRedirectedToRequest:
 @abstract Indicates to an NSURLProtocolClient that a redirect has
 occurred.
 @param protocol the NSURLProtocol object sending the message.
 @param request the NSURLRequest to which the protocol implementation
 has redirected.
 */
/*！
   @method URLProtocol：wasRedirectedToRequest：
   @abstract向NSURLProtocolClient表示重定向具有
   发生。
   @param协议NSURLProtocol对象发送消息。
   @param请求协议实现的NSURLRequest
   已重定向
  */
- (void)URLProtocol:(NSURLProtocol *)protocol wasRedirectedToRequest:(NSURLRequest *)request redirectResponse:(NSURLResponse *)redirectResponse;

/*!
 @method URLProtocol:cachedResponseIsValid:
 @abstract Indicates to an NSURLProtocolClient that the protocol
 implementation has examined a cached response and has
 determined that it is valid.
 @param protocol the NSURLProtocol object sending the message.
 @param cachedResponse the NSCachedURLResponse object that has
 examined and is valid.
 */
/*！
   @method URLProtocol：cachedResponseIsValid：
   @abstract向NSURLProtocolClient表示协议
   实施检查了缓存的响应
   确定它是有效的。
   @param协议NSURLProtocol对象发送消息。
   @param cachedResponse具有的NSCachedURLResponse对象
   检查并有效。
  */
- (void)URLProtocol:(NSURLProtocol *)protocol cachedResponseIsValid:(NSCachedURLResponse *)cachedResponse;

/*!
 @method URLProtocol:didReceiveResponse:
 @abstract Indicates to an NSURLProtocolClient that the protocol
 implementation has created an NSURLResponse for the current load.
 @param protocol the NSURLProtocol object sending the message.
 @param response the NSURLResponse object the protocol implementation
 has created.
 @param policy The NSURLCacheStoragePolicy the protocol
 has determined should be used for the given response if the
 response is to be stored in a cache.
 */
/*！
   @method URLProtocol：didReceiveResponse：
   @abstract向NSURLProtocolClient表示协议
   实现为当前负载创建了一个NSURLResponse。
   @param协议NSURLProtocol对象发送消息。
   @param响应NSURLResponse对象的协议实现
   已经创建。
   @param policy NSURLCacheStoragePolicy协议
   已经确定应该用于给定的响应，如果
   响应将被存储在缓存中。
  */
- (void)URLProtocol:(NSURLProtocol *)protocol didReceiveResponse:(NSURLResponse *)response cacheStoragePolicy:(NSURLCacheStoragePolicy)policy;

/*!
 @method URLProtocol:didLoadData:
 @abstract Indicates to an NSURLProtocolClient that the protocol
 implementation has loaded URL data.
 @discussion The data object must contain only new data loaded since
 the previous call to this method (if any), not cumulative data for
 the entire load.
 @param protocol the NSURLProtocol object sending the message.
 @param data URL load data being made available.
 */
/*！
   @method URLProtocol：didLoadData：
   @abstract向NSURLProtocolClient表示协议
   实现已经加载了URL数据。
   @discussion数据对象必须只包含加载的新数据
   以前调用此方法（如果有），不累积数据
   整个负载。
   @param协议NSURLProtocol对象发送消息。
   @param数据URL加载数据可用。
  */
- (void)URLProtocol:(NSURLProtocol *)protocol didLoadData:(NSData *)data;

/*!
 @method URLProtocolDidFinishLoading:
 @abstract Indicates to an NSURLProtocolClient that the protocol
 implementation has finished loading successfully.
 @param protocol the NSURLProtocol object sending the message.
 */
/*！
   @method URLProtocolDidFinishLoading：
   @abstract向NSURLProtocolClient表示协议
   实现已成功加载。
   @param协议NSURLProtocol对象发送消息。
  */
- (void)URLProtocolDidFinishLoading:(NSURLProtocol *)protocol;

/*!
 @method URLProtocol:didFailWithError:
 @abstract Indicates to an NSURLProtocolClient that the protocol
 implementation has failed to load successfully.
 @param protocol the NSURLProtocol object sending the message.
 @param error The error that caused the load to fail.
 */
/*！
   @method URLProtocol：didFailWithError：
   @abstract向NSURLProtocolClient表示协议
   实现无法成功加载。
   @param协议NSURLProtocol对象发送消息。
   @param error导致加载失败的错误。
  */
- (void)URLProtocol:(NSURLProtocol *)protocol didFailWithError:(NSError *)error;

/*!
 @method URLProtocol:didReceiveAuthenticationChallenge:
 @abstract Start authentication for the specified request
 @param protocol The protocol object requesting authentication.
 @param challenge The authentication challenge.
 @discussion The protocol client guarantees that it will answer the
 request on the same thread that called this method. It may add a
 default credential to the challenge it issues to the connection delegate,
 if the protocol did not provide one.
 */
/*！
   @method URLProtocol：didReceiveAuthenticationChallenge：
   @abstract为指定的请求启动身份验证
   @param协议请求认证的协议对象。
   @param挑战认证挑战。
   @discussion协议客户端保证它会回答
   请求在同一个线程上调用此方法。 它可以添加一个
   默认凭据来挑战它向连接代理发出问题，
   如果协议没有提供。
  */
- (void)URLProtocol:(NSURLProtocol *)protocol didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/*!
 @method URLProtocol:didCancelAuthenticationChallenge:
 @abstract Cancel authentication for the specified request
 @param protocol The protocol object cancelling authentication.
 @param challenge The authentication challenge.
 */
/*！
   @method URLProtocol：didCancelAuthenticationChallenge：
   @abstract取消指定请求的验证
   @param协议协议对象取消认证。
   @param挑战认证挑战。
  */
- (void)URLProtocol:(NSURLProtocol *)protocol didCancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

@end


/*!
 @class NSURLProtocol
 
 @abstract NSURLProtocol is an abstract class which provides the
 basic structure for performing protocol-specific loading of URL
 data. Concrete subclasses handle the specifics associated with one
 or more protocols or URL schemes.
 */
/*！
   @class NSURLProtocol
  
   @abstract NSURLProtocol是一个抽象类，它提供了
   执行协议特定加载URL的基本结构
   数据。 具体的子类处理与一个关联的细节
   或更多协议或URL方案。
  */
@interface NSURLProtocol : NSObject
{
@private
    NSURLProtocolInternal *_internal;
}

/*!
 @method initWithRequest:cachedResponse:client:
 @abstract Initializes an NSURLProtocol given request,
 cached response, and client.
 @param request The request to load.
 @param cachedResponse A response that has been retrieved from the
 cache for the given request. The protocol implementation should
 apply protocol-specific validity checks if such tests are
 necessary.
 @param client The NSURLProtocolClient object that serves as the
 interface the protocol implementation can use to report results back
 to the URL loading system.
 */
/*！
   @method initWithRequest：cachedResponse：client：
   @abstract初始化NSURLProtocol给定请求，
   缓存响应和客户端。
   @param请求加载请求。
   @param cachedResponse已从中检索到的响应
   缓存给定请求。 协议实现应该
   如果这样的测试，应用协议特定的有效性检查
   必要。
   @param client用作NSURLProtocolClient对象
   接口协议实现可以用来报告结果
   到URL加载系统。
  */
- (instancetype)initWithRequest:(NSURLRequest *)request cachedResponse:(nullable NSCachedURLResponse *)cachedResponse client:(nullable id <NSURLProtocolClient>)client NS_DESIGNATED_INITIALIZER;

/*!
 @abstract Returns the NSURLProtocolClient of the receiver.
 @result The NSURLProtocolClient of the receiver.
 */
/*！
   @abstract返回接收者的NSURLProtocolClient。
   @result接收器的NSURLProtocolClient。
  */
@property (nullable, readonly, retain) id <NSURLProtocolClient> client;

/*!
 @abstract Returns the NSURLRequest of the receiver.
 @result The NSURLRequest of the receiver.
 */
/*！
   @abstract返回接收者的NSURLRequest。
   @result接收器的NSURLRequest。
  */
@property (readonly, copy) NSURLRequest *request;

/*!
 @abstract Returns the NSCachedURLResponse of the receiver.
 @result The NSCachedURLResponse of the receiver.
 */
/*！
   @abstract返回接收者的NSCachedURLResponse。
   @result接收器的NSCachedURLResponse。
  */
@property (nullable, readonly, copy) NSCachedURLResponse *cachedResponse;

/*======================================================================
 Begin responsibilities for protocol implementors
 
 The methods between this set of begin-end markers must be
 implemented in order to create a working protocol.
 ======================================================================*/

/*!
 @method canInitWithRequest:
 @abstract This method determines whether this protocol can handle
 the given request.
 @discussion A concrete subclass should inspect the given request and
 determine whether or not the implementation can perform a load with
 that request. This is an abstract method. Sublasses must provide an
 implementation.
 @param request A request to inspect.
 @result YES if the protocol can handle the given request, NO if not.
 */
/*======================================================================
   开始协议实现者的职责
  
   这组开始标记之间的方法必须是
   实施以创建一个工作协议。
  ======================================================================*/

/*！
   @method canInitWithRequest：
   @abstract此方法确定此协议是否可以处理
   给定的请求。
   @discussion一个具体的子类应该检查给定的请求
   确定实现是否可以执行负载
   那个请求。 这是一个抽象的方法。 子类必须提供
  实现。
   @param请求检查请求。
   @result YES如果协议可以处理给定的请求，否则否。
  */

+ (BOOL)canInitWithRequest:(NSURLRequest *)request;

/*!
 @method canonicalRequestForRequest:
 @abstract This method returns a canonical version of the given
 request.
 @discussion It is up to each concrete protocol implementation to
 define what "canonical" means. However, a protocol should
 guarantee that the same input request always yields the same
 canonical form. Special consideration should be given when
 implementing this method since the canonical form of a request is
 used to look up objects in the URL cache, a process which performs
 equality checks between NSURLRequest objects.
 <p>
 This is an abstract method; sublasses must provide an
 implementation.
 @param request A request to make canonical.
 @result The canonical form of the given request.
 */
/*！
   @method canonicalRequestForRequest：
   @abstract此方法返回给定的规范版本
   请求。
   @discussion由每个具体的协议实现决定
   定义什么是“规范”的意思。 但是，一个协议应该
   保证相同的输入请求总是产生相同的
   规范的形式。 何时应特别考虑
   实现这种方法，因为请求的规范形式是
   用于查找URL缓存中的对象，一个执行的进程
   NSURLRequest对象之间进行相等检查。
  <P>
   这是一个抽象的方法; 子类必须提供
  实现。
   @param请求要求规范。
   @result给定请求的规范形式。
  */
+ (NSURLRequest *)canonicalRequestForRequest:(NSURLRequest *)request;

/*!
 @method requestIsCacheEquivalent:toRequest:
 @abstract Compares two requests for equivalence with regard to caching.
 @discussion Requests are considered euqivalent for cache purposes
 if and only if they would be handled by the same protocol AND that
 protocol declares them equivalent after performing
 implementation-specific checks.
 @result YES if the two requests are cache-equivalent, NO otherwise.
 */
/*！
   @method requestIsCacheEquivalent：toRequest：
   @abstract比较缓存方面的两个等价请求。
   @discussion请求被认为是缓存的目的
   当且仅当它们将被相同的协议处理
   协议在执行后声明它们是等效的
   实施特定检查。
   @result YES如果两个请求是缓存等效的，否则否。
  */
+ (BOOL)requestIsCacheEquivalent:(NSURLRequest *)a toRequest:(NSURLRequest *)b;

/*!
 @method startLoading
 @abstract Starts protocol-specific loading of a request.
 @discussion When this method is called, the protocol implementation
 should start loading a request.
 */
/*！
   @method startLoading
   @abstract开始协议特定的请求加载。
   @discussion当调用此方法时，协议实现
   应该开始加载请求。
  */
- (void)startLoading;

/*!
 @method stopLoading
 @abstract Stops protocol-specific loading of a request.
 @discussion When this method is called, the protocol implementation
 should end the work of loading a request. This could be in response
 to a cancel operation, so protocol implementations must be able to
 handle this call while a load is in progress.
 */
/*！
   @method stopLoading
   @abstract停止请求的协议特定加载。
   @discussion当调用此方法时，协议实现
   应该结束加载请求的工作。 这可以回应
   要取消操作，所以协议实现必须能够
   在加载过程中处理此呼叫。
  */
- (void)stopLoading;

/*======================================================================
 End responsibilities for protocol implementors
 ======================================================================*/

/*!
 @method propertyForKey:inRequest:
 @abstract Returns the property in the given request previously
 stored with the given key.
 @discussion The purpose of this method is to provide an interface
 for protocol implementors to access protocol-specific information
 associated with NSURLRequest objects.
 @param key The string to use for the property lookup.
 @param request The request to use for the property lookup.
 @result The property stored with the given key, or nil if no property
 had previously been stored with the given key in the given request.
 */
/*======================================================================
   协议实施者的最终责任
  ======================================================================*/

/*！
   @method propertyForKey：inRequest：
   @abstract返回给定请求中的属性
   与给定的密钥一起存储。
   @discussion这个方法的目的是提供一个接口
   用于协议实现者访问特定于协议的信息
   与NSURLRequest对象相关联。
   @param key用于属性查找的字符串。
   @param请求用于属性查找的请求。
   @result使用给定键存储的属性，如果没有属性，则为nil
   以前在给定的请求中存储了给定的密钥。
  */
+ (nullable id)propertyForKey:(NSString *)key inRequest:(NSURLRequest *)request;

/*!
 @method setProperty:forKey:inRequest:
 @abstract Stores the given property in the given request using the
 given key.
 @discussion The purpose of this method is to provide an interface
 for protocol implementors to customize protocol-specific
 information associated with NSMutableURLRequest objects.
 @param value The property to store.
 @param key The string to use for the property storage.
 @param request The request in which to store the property.
 */
/*！
   @method setProperty：forKey：inRequest：
   @abstract在给定的请求中存储给定的属性
   给予关键
   @discussion这个方法的目的是提供一个接口
   协议实现者定制特定协议
   与NSMutableURLRequest对象相关联的信息。
   @param value要存储的属性。
   @param key用于属性存储的字符串。
   @param请求存储该属性的请求。
  */
+ (void)setProperty:(id)value forKey:(NSString *)key inRequest:(NSMutableURLRequest *)request;

/*!
 @method removePropertyForKey:inRequest:
 @abstract Remove any property stored under the given key
 @discussion Like setProperty:forKey:inRequest: above, the purpose of this
 method is to give protocol implementors the ability to store
 protocol-specific information in an NSURLRequest
 @param key The key whose value should be removed
 @param request The request to be modified
 */
/*！
   @method removePropertyForKey：inRequest：
   @abstract删除存储在给定键下的任何属性
   @discussion喜欢setProperty：forKey：inRequest：上面，这个的目的
   方法是给协议实现者存储的能力
   NSURLRequest中的协议特定信息
   @param key应该删除其值的键
   @param请求要修改的请求
  */
+ (void)removePropertyForKey:(NSString *)key inRequest:(NSMutableURLRequest *)request;


/*!
 @method registerClass:
 @abstract This method registers a protocol class, making it visible
 to several other NSURLProtocol class methods.
 @discussion When the URL loading system begins to load a request,
 each protocol class that has been registered is consulted in turn to
 see if it can be initialized with a given request. The first
 protocol handler class to provide a YES answer to
 <tt>+canInitWithRequest:</tt> "wins" and that protocol
 implementation is used to perform the URL load. There is no
 guarantee that all registered protocol classes will be consulted.
 Hence, it should be noted that registering a class places it first
 on the list of classes that will be consulted in calls to
 <tt>+canInitWithRequest:</tt>, moving it in front of all classes
 that had been registered previously.
 <p>A similar design governs the process to create the canonical form
 of a request with the <tt>+canonicalRequestForRequest:</tt> class
 method.
 @param protocolClass the class to register.
 @result YES if the protocol was registered successfully, NO if not.
 The only way that failure can occur is if the given class is not a
 subclass of NSURLProtocol.
 */
/*！
 @method registerClass：
 @abstract此方法注册一个协议类，使其可见
 到其他几个NSURLProtocol类的方法。
 @discussion当URL加载系统开始加载请求时，
 已经注册的每个协议类依次参考
 看看它是否可以用给定的请求进行初始化。首先
 协议处理程序类提供YES答案
 <tt> + canInitWithRequest：</ tt>“赢”和该协议
 实现用于执行URL加载。没有
 保证所有注册的协议类都被查询。
 因此，应该注意的是，注册一个类放在第一位
 在通话中将要查询的课程列表中
 <tt> + canInitWithRequest：</ tt>，将其移动到所有类的前面
 以前已经注册过。
 <p>类似的设计管理创建规范表单的过程
 使用<tt> + canonicalRequestForRequest：</ tt>类的请求
 方法。
 @param protocolClass要注册的类。
 @result YES如果协议已成功注册，否则否。
 失败可能发生的唯一方法是如果给定的类不是
 NSURLProtocol的子类。
 */
+ (BOOL)registerClass:(Class)protocolClass;

/*!
 @method unregisterClass:
 @abstract This method unregisters a protocol.
 @discussion After unregistration, a protocol class is no longer
 consulted in calls to NSURLProtocol class methods.
 @param protocolClass The class to unregister.
 */
/*！
   @method unregisterClass：
   @abstract此方法注销协议。
   @discussion取消注册后，协议类不再存在
   在调用NSURLProtocol类方法时咨询。
   @param protocolClass要注销的类。
  */
+ (void)unregisterClass:(Class)protocolClass;

@end


@interface NSURLProtocol (NSURLSessionTaskAdditions)
+ (BOOL)canInitWithTask:(NSURLSessionTask *)task API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
- (instancetype)initWithTask:(NSURLSessionTask *)task cachedResponse:(nullable NSCachedURLResponse *)cachedResponse client:(nullable id <NSURLProtocolClient>)client API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
@property (nullable, readonly, copy) NSURLSessionTask *task API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
@end

NS_ASSUME_NONNULL_END

