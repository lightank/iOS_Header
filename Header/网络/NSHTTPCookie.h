/*
 NSHTTPCookie.h
 Copyright (c) 2003-2016, Apple Inc. All rights reserved.
 
 Public header file.
 */

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>;
@class NSDate;
@class NSDictionary<KeyType, ObjectType>;
@class NSNumber;
@class NSString;
@class NSURL;

typedef NSString * NSHTTPCookiePropertyKey NS_EXTENSIBLE_STRING_ENUM;

NS_ASSUME_NONNULL_BEGIN

//参考自:http://www.jianshu.com/p/199f58f04955
/*
 当访问一个网页的时候，NSURLRequest会默认帮你主动记录当前站点的设置的Cookie,然后访问之后就会自动写入磁盘，iOS是把cookie信息放在的NSHTTPCookieStorage容器中管理，当下一次请求的时候，NSURLRequest会从内存中拿出上次保存下来的Cookie继续去请求。
 
 Cookie
 
 Cookie由服务器端生成，响应后发送给客户端，每一个Cookie都是一个NSHTTPCookie类的实例。
 
 NSHTTPCookieStorage
 
 NSHTTPCookieStorage实现了一个管理cookie的单例对象(只有一个实例)，每个Cookie都是NSHTTPCookie类的实例。同一个域下的Cookie在应用内是共享的。
 
 HTTPHeader
 
 HTTPHeader中包含HTTP请求和响应的参数,header中定义了传输数据的各种特性。header以属性名开始，属性值之间用;间隔 。Cookie属于HTTPHeader的一部分。
 
 iOS中Cookie的读取和写入
 
 Cookie一般是通过http的Response中传过来，作为Response的HTTP Header中，系统默认会将cookie写入磁盘保存。那么如何获取Cookie,并且写入自定义Cookie呢？
 
 需要先手动获取当前NSHTTPCookieStorage中的所有cookie，然后将cookie放到NSURLRequest请求头中
 1.获取已有的Cookie，然后添加新的Cookie。
 
 - (NSArray *)fetchNewCookies 
 {
     NSMutableArray *cookies = [[[NSHTTPCookieStorage sharedHTTPCookieStorage] cookiesForURL:[NSURL URLWithString:@"https://backend.gmei.com"]] mutableCopy];
     NSHTTPCookie *accessCookie = [self fetchAccessTokenCookie];
     //添加新Cookie最好多加一步去重
     [cookies addObject:accessCookie];
     return [cookies copy];
 }
 
 - (NSHTTPCookie *)fetchAccessTokenCookie
 {
     NSMutableDictionary *properties = [NSMutableDictionary dictionary];
     [properties setObject:@"_gm_token" forKey:NSHTTPCookieName];
     [properties setObject:accessToken forKey:NSHTTPCookieValue];
     [properties setObject:@"backend.gmei.com" forKey:NSHTTPCookieDomain];
     [properties setObject:@"/" forKey:NSHTTPCookiePath];
     NSHTTPCookie *accessCookie = [[NSHTTPCookie alloc] initWithProperties:properties];
     return accessCookie;
 }
 
 2.Cookie的本地同步和动态绑定
 
 1的操作首先是构造需要写入的自定义Cookie，构造成功后，因为Response中的Cookie不仅仅只有一个，所以我们通过url获取到当前域下的Cookie得到的是一个数组Cookies,然后将自定义的Cookie添加到原有的Cookies数组中得到新的Cookies。
 
 NSMutableArray *cookies = [[[NSHTTPCookieStorage sharedHTTPCookieStorage] cookiesForURL:[NSURL URLWithString:@"https://backend.gmei.com"]] mutableCopy];
 Okay,现在新Cookies我们已经构造好了。需要做的是，再新的http请求到来的时候，新的http请求的头部中的Cookies是我们构造好的Cookie。
 
 场景1 自定义的Cookie的value是常量
 如果我们仅仅写入的一个Cookie值是一个常量(当然很少见),我们可以直接将新的Cookies交由NSHTTPCookieStorage管理，执行完这段代码后，之后的请求Header中的Cookies就是新的Cookies。如果fetchAccessTokenCookie方法中设置一个例如24小时的过期时间的key，那么24小时内，新的Cookies在客户端都是有效的。
 
 系统提供setCookie方法,需要注意的是如果两个cookie的name名字相同,后面的会覆盖已经存在的cookie。
 - (void)setCookie:(NSHTTPCookie *)cookie;
 执行就okay了:
    NSHTTPCookie *accessCookie =  [self fetchAccessTokenCookie];
    [[NSHTTPCookieStorage sharedHTTPCookieStorage] setCookie:accessCookie];
 
场景2 自定义的Cookie的value是变量且要求立即生效，不能遗漏任何一个http请求。
在这种要求生效的及时性和完整性的时候，上面的方案1就无法满足。这个时候我们需要将新的Cookies和接下来的请求url进行绑定。Cookie是HTTPHeader的一部分，所以现将得到的新Cookies，生成一个HTTPHeader，系统提供了将 cookie转成请求头的方法。

    -requestHeaderFieldsWithCookies:

    UIWebView

    NSHTTPCookie *accessCookie =  [self fetchAccessTokenCookie];
    NSDictionary *requestHeaders = [NSHTTPCookie requestHeaderFieldsWithCookies:accessCookie];
    [request setValue:[requestHeaders objectForKey:@"Cookie"] forHTTPHeaderField:@"Cookie"];
    [_webView loadRequest:request];
    
 AFNetworking
 GET/PSOT/DELETE/PUT/PATCH

    AFHTTPRequestOperationManager *manager = [AFHTTPRequestOperationManager manager];
    manager.requestSerializer.HTTPShouldHandleCookies = YES;
    [manager.requestSerializer setValue:newCookies forHTTPHeaderField:@"Cookie"];
 对于上传音视频的时候，AFNetworking用的是AFURLSessionManager而不是AFHTTPRequestOperationManager。

    NSMutableURLRequest *request = [[AFHTTPRequestSerializer serializer] multipartFormRequestWithMethod:@"POST" URLString:URLString parameters:parameters constructingBodyWithBlock:^(id<AFMultipartFormData> formData) {
        //没有指定name的时候,name不能为空，默认填充 @"file" 即可
        [formData appendPartWithFileData:data name:name fileName:fileName mimeType:mineType];
    } error:nil];
    request.timeoutInterval = 30;
    NSHTTPCookie *accessCookie =  [self fetchAccessTokenCookie];
    NSDictionary *requestHeaders = [NSHTTPCookie requestHeaderFieldsWithCookies:accessCookie];
    [request setValue:[httpHeader objectForKey:@"Cookie"] forHTTPHeaderField:@"Cookie"];
    AFURLSessionManager *manager = [[AFURLSessionManager alloc] initWithSessionConfiguration:[NSURLSessionConfiguration defaultSessionConfiguration]];
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    NSURLSessionUploadTask *uploadTask = [manager uploadTaskWithStreamedRequest:request progress:NULL completionHandler:^(NSURLResponse *response, id responseObject, NSError *error) {
        [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
        if (error) {
            [self failureWithTask:nil error:error failed:failed];
        } else {
            [self successWithTask:nil responseObject:responseObject success:success];
        }
    }];

    [uploadTask resume];

 */



/*!
 @const NSHTTPCookieName
 @discussion Key for cookie name
 */
//包含cookie名称的NSString对象。此cookie属性是必选的
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieName;

/*!
 @const NSHTTPCookieValue
 @discussion Key for cookie value
 */
//包含cookie的值的NSString对象。此cookie属性是必选的
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieValue;

/*!
 @const NSHTTPCookieOriginURL
 @discussion Key for cookie origin URL
 */
//包含设置此cookie的URL的NSURL或NSString对象。如果您不提供NSHTTPCookieOriginURL的值，则必须为NSHTTPCookieDomain提供一个值
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieOriginURL;

/*!
 @const NSHTTPCookieVersion
 @discussion Key for cookie version
 */
//Cookie有两个版本：Version 0 和 Version 1。通过它们有两种设置响应头的标识，分别是 “Set-Cookie”和“Set-Cookie2”。该属性的值必须是“0”或“1”。默认值为“0”,是可选的。
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieVersion;

/*!
 @const NSHTTPCookieDomain
 @discussion Key for cookie domain
 */
// 包含cookie的域的NSString对象,如果缺少此cookie属性，则会根据NSHTTPCookieOriginURL的值推断该域。如果未指定NSHTTPCookieOriginURL的值，则必须为NSHTTPCookieDomain指定值
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieDomain;

/*!
 @const NSHTTPCookiePath
 @discussion Key for cookie path
 */
//该Cookie是在当前的哪个路径下生成的,/表示在当前目录,此cookie属性是必选的
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookiePath;

/*!
 @const NSHTTPCookieSecure
 @discussion Key for cookie secure flag
 */
//一个NSString对象，如果设置了这个属性，那么只会在 SSH 连接时才会回传该 Cookie。默认是fasle
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieSecure;

/*!
 @const NSHTTPCookieExpires
 @discussion Key for cookie expiration date
 */
//指定了Cookie过期日期的NSDate对象或NSString对象,此cookie属性仅用于版本0的Cookie,是可选属性
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieExpires;

/*!
 @const NSHTTPCookieComment
 @discussion Key for cookie comment text
 */
//包含cookie的注释的NSString对象,注释项,用户说明该 Cookie 有何用途,对Vesion1以及以后的版本有效，是可选属性
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieComment;

/*!
 @const NSHTTPCookieCommentURL
 @discussion Key for cookie comment URL
 */
//一个NSURL对象NSString对象包含Cookie的评论的网址。仅适用于第1版及其以后版本的缓存。 这头字段是可选的。
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieCommentURL;

/*!
 @const NSHTTPCookieDiscard
 @discussion Key for cookie discard (session-only) flag
 */
//说明cookie是否应在session结束时丢弃NSString对象。字符串值必须是“true”或“false”。 这头字段是可选的。 默认为“false”;如果cookie版本在1.0及以上时,且NSHTTPCookieMaximumAge未指定时,这是它被假定为“true” 。
//一个NSString对象，用于标识在会话结束时是否应该丢弃改Cookie，是可选属性。String的值必须是True或者false。默认值是false，除非该cookie是version1或更高版本，且未指定NSHTTPCookieMaximumAge的值，在这种情况下，它被假定为TRUE
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieDiscard;

/*!
 @const NSHTTPCookieMaximumAge
 @discussion Key for cookie maximum age (an alternate way of specifying the expiration)
 */
//个包含一个整数值的NSString对象，表示cookie最大保留时间(以秒为单位)。仅适用于版本1 Cookie及更高版本。默认值为“0”。此cookie属性是可选的。
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieMaximumAge;

/*!
 @const NSHTTPCookiePort
 @discussion Key for cookie ports
 */
//NSString对象，包含逗号分隔的整数值，指定Cookie的端口。仅适用于version1或更高版本。默认值为空字符串,是可选的
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookiePort;


@class NSHTTPCookieInternal;

/*!
 @class NSHTTPCookie
 @abstract NSHTTPCookie represents an http cookie.
 @discussion A NSHTTPCookie instance represents a single http cookie. It is
 an immutable object initialized from a dictionary that contains
 the various cookie attributes. It has accessors to get the various
 attributes of a cookie.
 */

@interface NSHTTPCookie : NSObject
{
@private
    NSHTTPCookieInternal * _cookiePrivate;
}

/*!
     @method initWithProperties:
     @abstract Initialize a NSHTTPCookie object with a dictionary of
     parameters
     @param properties The dictionary of properties to be used to
     initialize this cookie.
     @discussion Supported dictionary keys and value types for the
     given dictionary are as follows.
     
     All properties can handle an NSString value, but some can also
     handle other types.
     
     <table border=1 cellspacing=2 cellpadding=4>
     <tr>
         <th>Property key constant</th>
         <th>Type of value</th>
         <th>Required</th>
         <th>Description</th>
     </tr>
     <tr>
         <td>NSHTTPCookieComment</td>
         <td>NSString</td>
         <td>NO</td>
         <td>Comment for the cookie. Only valid for version 1 cookies and
         later. Default is nil.</td>
     </tr>
     <tr>
         <td>NSHTTPCookieCommentURL</td>
         <td>NSURL or NSString</td>
         <td>NO</td>
         <td>Comment URL for the cookie. Only valid for version 1 cookies
         and later. Default is nil.</td>
     </tr>
     <tr>
         <td>NSHTTPCookieDomain</td>
         <td>NSString</td>
         <td>Special, a value for either NSHTTPCookieOriginURL or
         NSHTTPCookieDomain must be specified.</td>
         <td>Domain for the cookie. Inferred from the value for
         NSHTTPCookieOriginURL if not provided.</td>
     </tr>
     <tr>
         <td>NSHTTPCookieDiscard</td>
         <td>NSString</td>
         <td>NO</td>
         <td>A string stating whether the cookie should be discarded at
         the end of the session. String value must be either "TRUE" or
         "FALSE". Default is "FALSE", unless this is cookie is version
         1 or greater and a value for NSHTTPCookieMaximumAge is not
         specified, in which case it is assumed "TRUE".</td>
     </tr>
     <tr>
         <td>NSHTTPCookieExpires</td>
         <td>NSDate or NSString</td>
         <td>NO</td>
         <td>Expiration date for the cookie. Used only for version 0
         cookies. Ignored for version 1 or greater.</td>
     </tr>
     <tr>
         <td>NSHTTPCookieMaximumAge</td>
         <td>NSString</td>
         <td>NO</td>
         <td>A string containing an integer value stating how long in
         seconds the cookie should be kept, at most. Only valid for
         version 1 cookies and later. Default is "0".</td>
     </tr>
     <tr>
         <td>NSHTTPCookieName</td>
         <td>NSString</td>
         <td>YES</td>
         <td>Name of the cookie</td>
     </tr>
     <tr>
         <td>NSHTTPCookieOriginURL</td>
         <td>NSURL or NSString</td>
         <td>Special, a value for either NSHTTPCookieOriginURL or
         NSHTTPCookieDomain must be specified.</td>
         <td>URL that set this cookie. Used as default for other fields
         as noted.</td>
     </tr>
     <tr>
         <td>NSHTTPCookiePath</td>
         <td>NSString</td>
         <td>NO</td>
         <td>Path for the cookie. Inferred from the value for
         NSHTTPCookieOriginURL if not provided. Default is "/".</td>
     </tr>
     <tr>
         <td>NSHTTPCookiePort</td>
         <td>NSString</td>
         <td>NO</td>
         <td>comma-separated integer values specifying the ports for the
         cookie. Only valid for version 1 cookies and later. Default is
         empty string ("").</td>
     </tr>
     <tr>
         <td>NSHTTPCookieSecure</td>
         <td>NSString</td>
         <td>NO</td>
         <td>A string stating whether the cookie should be transmitted
         only over secure channels. String value must be either "TRUE"
         or "FALSE". Default is "FALSE".</td>
     </tr>
     <tr>
         <td>NSHTTPCookieValue</td>
         <td>NSString</td>
         <td>YES</td>
         <td>Value of the cookie</td>
     </tr>
     <tr>
         <td>NSHTTPCookieVersion</td>
         <td>NSString</td>
         <td>NO</td>
         <td>Specifies the version of the cookie. Must be either "0" or
         "1". Default is "0".</td>
     </tr>
     </table>
     <p>
     All other keys are ignored.
     @result An initialized NSHTTPCookie, or nil if the set of
     dictionary keys is invalid, for example because a required key is
     missing, or a recognized key maps to an illegal value.
 */
- (nullable instancetype)initWithProperties:(NSDictionary<NSHTTPCookiePropertyKey, id> *)properties;

/*!
 @method cookieWithProperties:
 @abstract Allocates and initializes an NSHTTPCookie with the given
 dictionary.
 @discussion See the NSHTTPCookie <tt>-initWithProperties:</tt>
 method for more information on the constraints imposed on the
 dictionary, and for descriptions of the supported keys and values.
 @param properties The dictionary to use to initialize this cookie.
 @result A newly-created and autoreleased NSHTTPCookie instance, or
 nil if the set of dictionary keys is invalid, for example because
 a required key is missing, or a recognized key maps to an illegal
 value.
 */
+ (nullable NSHTTPCookie *)cookieWithProperties:(NSDictionary<NSHTTPCookiePropertyKey, id> *)properties;

/*!
 @method requestHeaderFieldsWithCookies:
 @abstract Return a dictionary of header fields that can be used to add the
 specified cookies to the request.
 @param cookies The cookies to turn into request headers.
 @result An NSDictionary where the keys are header field names, and the values
 are the corresponding header field values.
 */
//Returns a dictionary of header fields corresponding to a provided array of cookies.
// 将cookie转成请求头
+ (NSDictionary<NSString *, NSString *> *)requestHeaderFieldsWithCookies:(NSArray<NSHTTPCookie *> *)cookies;

/*!
 @method cookiesWithResponseHeaderFields:forURL:
 @abstract Return an array of cookies parsed from the specified response header fields and URL.
 @param headerFields The response header fields to check for cookies.
 @param URL The URL that the cookies came from - relevant to how the cookies are interpeted.
 @result An NSArray of NSHTTPCookie objects
 @discussion This method will ignore irrelevant header fields so
 you can pass a dictionary containing data other than cookie data.
 */
//Returns an array of NSHTTPCookie objects corresponding to the provided response header fields for the provided URL.
//返回给定url的响应头中NSHTTPCookie对象数组
+ (NSArray<NSHTTPCookie *> *)cookiesWithResponseHeaderFields:(NSDictionary<NSString *, NSString *> *)headerFields forURL:(NSURL *)URL;

/*!
 @method properties
 @abstract Returns a dictionary representation of the receiver.
 @discussion This method returns a dictionary representation of the
 NSHTTPCookie which can be saved and passed to
 <tt>-initWithProperties:</tt> or <tt>+cookieWithProperties:</tt>
 later to reconstitute an equivalent cookie.
 <p>See the NSHTTPCookie <tt>-initWithProperties:</tt> method for
 more information on the constraints imposed on the dictionary, and
 for descriptions of the supported keys and values.
 @result The dictionary representation of the receiver.
 */
//属性字典
@property (nullable, readonly, copy) NSDictionary<NSHTTPCookiePropertyKey, id> *properties;

/*!
 @method version
 @abstract Returns the version of the receiver.
 @discussion Version 0 maps to "old-style" Netscape cookies.
 Version 1 maps to RFC2965 cookies. There may be future versions.
 @result the version of the receiver.
 */
@property (readonly) NSUInteger version;

/*!
 @method name
 @abstract Returns the name of the receiver.
 @result the name of the receiver.
 */
@property (readonly, copy) NSString *name;

/*!
 @method value
 @abstract Returns the value of the receiver.
 @result the value of the receiver.
 */
@property (readonly, copy) NSString *value;

/*!
 @method expiresDate
 @abstract Returns the expires date of the receiver.
 @result the expires date of the receiver.
 @discussion The expires date is the date when the cookie should be
 deleted. The result will be nil if there is no specific expires
 date. This will be the case only for "session-only" cookies.
 @result The expires date of the receiver.
 */
@property (nullable, readonly, copy) NSDate *expiresDate;

/*!
 @method isSessionOnly
 @abstract Returns whether the receiver is session-only.
 @result YES if this receiver should be discarded at the end of the
 session (regardless of expiration date), NO if receiver need not
 be discarded at the end of the session.
 */
@property (readonly, getter=isSessionOnly) BOOL sessionOnly;

/*!
 @method domain
 @abstract Returns the domain of the receiver.
 @discussion This value specifies URL domain to which the cookie
 should be sent. A domain with a leading dot means the cookie
 should be sent to subdomains as well, assuming certain other
 restrictions are valid. See RFC 2965 for more detail.
 @result The domain of the receiver.
 */
@property (readonly, copy) NSString *domain;

/*!
 @method path
 @abstract Returns the path of the receiver.
 @discussion This value specifies the URL path under the cookie's
 domain for which this cookie should be sent. The cookie will also
 be sent for children of that path, so "/" is the most general.
 @result The path of the receiver.
 */
@property (readonly, copy) NSString *path;

/*!
 @method isSecure
 @abstract Returns whether the receiver should be sent only over
 secure channels
 @discussion Cookies may be marked secure by a server (or by a javascript).
 Cookies marked as such must only be sent via an encrypted connection to
 trusted servers (i.e. via SSL or TLS), and should not be delievered to any
 javascript applications to prevent cross-site scripting vulnerabilities.
 @result YES if this cookie should be sent only over secure channels,
 NO otherwise.
 */
@property (readonly, getter=isSecure) BOOL secure;

/*!
 @method isHTTPOnly
 @abstract Returns whether the receiver should only be sent to HTTP servers
 per RFC 2965
 @discussion Cookies may be marked as HTTPOnly by a server (or by a javascript).
 Cookies marked as such must only be sent via HTTP Headers in HTTP Requests
 for URL's that match both the path and domain of the respective Cookies.
 Specifically these cookies should not be delivered to any javascript
 applications to prevent cross-site scripting vulnerabilities.
 @result YES if this cookie should only be sent via HTTP headers,
 NO otherwise.
 */
@property (readonly, getter=isHTTPOnly) BOOL HTTPOnly;

/*!
 @method comment
 @abstract Returns the comment of the receiver.
 @discussion This value specifies a string which is suitable for
 presentation to the user explaining the contents and purpose of this
 cookie. It may be nil.
 @result The comment of the receiver, or nil if the receiver has no
 comment.
 */
@property (nullable, readonly, copy) NSString *comment;

/*!
 @method commentURL
 @abstract Returns the comment URL of the receiver.
 @discussion This value specifies a URL which is suitable for
 presentation to the user as a link for further information about
 this cookie. It may be nil.
 @result The comment URL of the receiver, or nil if the receiver
 has no comment URL.
 */
@property (nullable, readonly, copy) NSURL *commentURL;

/*!
 @method portList
 @abstract Returns the list ports to which the receiver should be
 sent.
 @discussion This value specifies an NSArray of NSNumbers
 (containing integers) which specify the only ports to which this
 cookie should be sent.
 @result The list ports to which the receiver should be sent. The
 array may be nil, in which case this cookie can be sent to any
 port.
 */
@property (nullable, readonly, copy) NSArray<NSNumber *> *portList;

@end

NS_ASSUME_NONNULL_END
