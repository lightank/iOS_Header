/*
 * Copyright (C) 2014 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <WebKit/WKFoundation.h>

#if WK_API_ENABLED

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class WKBackForwardList;
@class WKBackForwardListItem;
@class WKNavigation;
@class WKWebViewConfiguration;

@protocol WKNavigationDelegate;
@protocol WKUIDelegate;

/*!
 A WKWebView object displays interactive Web content.
 @helperclass @link WKWebViewConfiguration @/link
 Used to configure @link WKWebView @/link instances.
 */
#if TARGET_OS_IPHONE
WK_EXTERN API_AVAILABLE(macosx(10.10), ios(8.0))
@interface WKWebView : UIView
#else
WK_EXTERN API_AVAILABLE(macosx(10.10), ios(8.0))
@interface WKWebView : NSView
#endif

/*! @abstract A copy of the configuration with which the web view was
 initialized. */
//A copy of the configuration to initialize the web view with. (read-only)
//用于初始化Web视图的配置副本。 （只读）
@property (nonatomic, readonly, copy) WKWebViewConfiguration *configuration;

/*! @abstract The web view's navigation delegate. */
//The web view's navigation delegate.
//网络视图的导航代理。
@property (nullable, nonatomic, weak) id <WKNavigationDelegate> navigationDelegate;

/*! @abstract The web view's user interface delegate. */
//The web view's user interface delegate.
//网页视图的用户界面委托。
@property (nullable, nonatomic, weak) id <WKUIDelegate> UIDelegate;

/*! @abstract The web view's back-forward list. */
//The web view's back-forward list. (read-only)
//网页视图的后退列表。 （只读）
@property (nonatomic, readonly, strong) WKBackForwardList *backForwardList;

/*! @abstract Returns a web view initialized with a specified frame and
 configuration.
 @param frame The frame for the new web view.
 @param configuration The configuration for the new web view.
 @result An initialized web view, or nil if the object could not be
 initialized.
 @discussion This is a designated initializer. You can use
 @link -initWithFrame: @/link to initialize an instance with the default
 configuration. The initializer copies the specified configuration, so
 mutating the configuration after invoking the initializer has no effect
 on the web view.
 */
/*！ @abstract 返回使用指定的框架初始化的Web视图
   组态。
   @param frame新的Web视图的框架。
   @param配置新的Web视图的配置。
   @result初始化的Web视图，如果对象不可能，则为nil
  初始化。
   @discussion这是一个指定的初始化程序。 您可以使用
   @link -initWithFrame：@/link使用默认值初始化一个实例
   组态。 初始化程序复制指定的配置，所以
   在调用初始化器之后突变配置没有任何效果
   在网络视图上。
  */
- (instancetype)initWithFrame:(CGRect)frame configuration:(WKWebViewConfiguration *)configuration NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/*! @abstract Navigates to a requested URL.
 @param request The request specifying the URL to which to navigate.
 @result A new navigation for the given request.
 */
//Navigates to a requested URL.
/*！ @abstract 导航到所请求的URL。
   @param请求请求指定要导航的URL。
   @result给定请求的新导航。
  */
//导航到所请求的URL。
- (nullable WKNavigation *)loadRequest:(NSURLRequest *)request;

/*! @abstract Navigates to the requested file URL on the filesystem.
 @param URL The file URL to which to navigate.
 @param readAccessURL The URL to allow read access to.
 @discussion If readAccessURL references a single file, only that file may be loaded by WebKit.
 If readAccessURL references a directory, files inside that file may be loaded by WebKit.
 @result A new navigation for the given file URL.
 */
//Navigates to the requested file URL on the filesystem
/*！ @abstract导航到文件系统上请求的文件URL。
   @param URL要导航的文件URL。
   @param readAccessURL允许读访问的URL。
   @discussion如果readAccessURL引用单个文件，则只能由WebKit加载该文件。
   如果readAccessURL引用一个目录，该文件中的文件可能被WebKit加载。
   @result给定文件URL的新导航。
  */
//导航到文件系统上的请求的文件URL
- (nullable WKNavigation *)loadFileURL:(NSURL *)URL allowingReadAccessToURL:(NSURL *)readAccessURL API_AVAILABLE(macosx(10.11), ios(9.0));

/*! @abstract Sets the webpage contents and base URL.
 @param string The string to use as the contents of the webpage.
 @param baseURL A URL that is used to resolve relative URLs within the document.
 @result A new navigation.
 */
//Sets the webpage contents and base URL.
/*！ @abstract设置网页内容和基本URL。
   @param string用作网页内容的字符串。
   @param baseURL用于解析文档中的相对URL的URL。
   @result新的导航。
  */
//设置网页内容和基本URL。
- (nullable WKNavigation *)loadHTMLString:(NSString *)string baseURL:(nullable NSURL *)baseURL;

/*! @abstract Sets the webpage contents and base URL.
 @param data The data to use as the contents of the webpage.
 @param MIMEType The MIME type of the data.
 @param encodingName The data's character encoding name.
 @param baseURL A URL that is used to resolve relative URLs within the document.
 @result A new navigation.
 */
//Sets the webpage contents and base URL.
/*！ @abstract设置网页内容和基本URL。
   @param data要用作网页内容的数据。
   @param MIMEType数据的MIME类型。
   @param encodingName数据的字符编码名称。
   @param baseURL用于解析文档中的相对URL的URL。
   @result新的导航。
  */
//设置网页内容和基本URL。
- (nullable WKNavigation *)loadData:(NSData *)data MIMEType:(NSString *)MIMEType characterEncodingName:(NSString *)characterEncodingName baseURL:(NSURL *)baseURL API_AVAILABLE(macosx(10.11), ios(9.0));

/*! @abstract Navigates to an item from the back-forward list and sets it
 as the current item.
 @param item The item to which to navigate. Must be one of the items in the
 web view's back-forward list.
 @result A new navigation to the requested item, or nil if it is already
 the current item or is not part of the web view's back-forward list.
 @seealso backForwardList
 */
//Navigates to an item from the back-forward list and sets it as the current item.
/*！ @abstract从后退列表导航到一个项目并设置它
   作为当前项目。
   @param item要导航的项目。 必须是其中的项目之一
   网页视图的后退列表。
   @result对所请求的项目的新导航，如果已经存在，则为nil
   当前项目或不是Web视图的后退列表的一部分。
   @seealso backForwardList
  */
//从后退列表导航到一个项目，并将其设置为当前项目。
- (nullable WKNavigation *)goToBackForwardListItem:(WKBackForwardListItem *)item;

/*! @abstract The page title.
 @discussion @link WKWebView @/link is key-value observing (KVO) compliant
 for this property.
 */
//The page title. (read-only),The WKWebView class is key-value observing (KVO) compliant for this property.
//页面标题。 （只读），WKWebView类是符合此属性的键值观察（KVO）。
@property (nullable, nonatomic, readonly, copy) NSString *title;

/*! @abstract The active URL.
 @discussion This is the URL that should be reflected in the user
 interface.
 @link WKWebView @/link is key-value observing (KVO) compliant for this
 property.
 */
//The active URL. (read-only)
/*！ @abstract活动的URL。
   @discussion这是应该在用户中反映的URL
   接口。
   @link WKWebView @ / link是符合键值观察（KVO）的
   属性。
  */
//活动网址。 （只读）
@property (nullable, nonatomic, readonly, copy) NSURL *URL;

/*! @abstract A Boolean value indicating whether the view is currently
 loading content.
 @discussion @link WKWebView @/link is key-value observing (KVO) compliant
 for this property.
 */
/*！ @abstract一个布尔值，指示视图是否当前
   加载内容
   @discussion @link WKWebView @ / link是符合键值观察（KVO）的
   为此属性。
  */
@property (nonatomic, readonly, getter=isLoading) BOOL loading;

/*! @abstract An estimate of what fraction of the current navigation has been completed.
 @discussion This value ranges from 0.0 to 1.0 based on the total number of
 bytes expected to be received, including the main document and all of its
 potential subresources. After a navigation completes, the value remains at 1.0
 until a new navigation starts, at which point it is reset to 0.0.
 @link WKWebView @/link is key-value observing (KVO) compliant for this
 property.
 */
/*！ @abstract估计当前导航的几个部分已经完成。
   @discussion此值的范围为0.0到1.0，基于总数
   预计将收到的字节，包括主文档及其全部
   潜在的子资源 导航完成后，值保持为1.0
   直到新的导航开始，此时它被重置为0.0。
   @link WKWebView @ / link是符合键值观察（KVO）的
   属性。
  */
@property (nonatomic, readonly) double estimatedProgress;

/*! @abstract A Boolean value indicating whether all resources on the page
 have been loaded over securely encrypted connections.
 @discussion @link WKWebView @/link is key-value observing (KVO) compliant
 for this property.
 */
/*！ @abstract一个布尔值，表示页面上的所有资源
   已经通过安全加密的连接加载。
   @discussion @link WKWebView @ / link是符合键值观察（KVO）的
   为此属性。
  */
@property (nonatomic, readonly) BOOL hasOnlySecureContent;

/*! @abstract A SecTrustRef for the currently committed navigation.
 @discussion @link WKWebView @/link is key-value observing (KVO) compliant
 for this property.
 */
/*！ @abstract A当前承诺的导航的SecTrustRef。
   @discussion @link WKWebView @ / link是符合键值观察（KVO）的
   为此属性。
  */
@property (nonatomic, readonly, nullable) SecTrustRef serverTrust API_AVAILABLE(macosx(10.12), ios(10.0));

/*! @abstract A Boolean value indicating whether there is a back item in
 the back-forward list that can be navigated to.
 @discussion @link WKWebView @/link is key-value observing (KVO) compliant
 for this property.
 @seealso backForwardList.
 */
/*！ @abstract一个布尔值，表示是否有后面的项目
   可以导航到的后退列表。
   @discussion @link WKWebView @ / link是符合键值观察（KVO）的
   为此属性。
   @seealso backForwardList。
  */
@property (nonatomic, readonly) BOOL canGoBack;

/*! @abstract A Boolean value indicating whether there is a forward item in
 the back-forward list that can be navigated to.
 @discussion @link WKWebView @/link is key-value observing (KVO) compliant
 for this property.
 @seealso backForwardList.
 */
/*！ @abstract一个布尔值，表示是否存在转发项
   可以导航到的后退列表。
   @discussion @link WKWebView @ / link是符合键值观察（KVO）的
   为此属性。
   @seealso backForwardList。
  */
@property (nonatomic, readonly) BOOL canGoForward;

/*! @abstract Navigates to the back item in the back-forward list.
 @result A new navigation to the requested item, or nil if there is no back
 item in the back-forward list.
 */
/*！ @abstract导航到后退列表中的后退项目。
   @result对所请求的项目的新导航，如果没有返回，则为nil
   项目在后退列表中。
  */
- (nullable WKNavigation *)goBack;

/*! @abstract Navigates to the forward item in the back-forward list.
 @result A new navigation to the requested item, or nil if there is no
 forward item in the back-forward list.
 */
/*！ @abstract导航到后退列表中的前进项。
   @result对所请求的项目的新导航，如果没有，则为nil
   转发项目在后退列表中。
  */
- (nullable WKNavigation *)goForward;

/*! @abstract Reloads the current page.
 @result A new navigation representing the reload.
 */
/*！ @abstract重新加载当前页面。
   @result表示重新加载的新导航。
  */
- (nullable WKNavigation *)reload;

/*! @abstract Reloads the current page, performing end-to-end revalidation
 using cache-validating conditionals if possible.
 @result A new navigation representing the reload.
 */
/*！ @abstract重新加载当前页面，执行端到端重新验证
   如果可能，使用缓存验证条件。
   @result表示重新加载的新导航。
  */
- (nullable WKNavigation *)reloadFromOrigin;

/*! @abstract Stops loading all resources on the current page.
 */
//停止加载当前页面上的所有资源。
- (void)stopLoading;

/* @abstract Evaluates the given JavaScript string.
 @param javaScriptString The JavaScript string to evaluate.
 @param completionHandler A block to invoke when script evaluation completes or fails.
 @discussion The completionHandler is passed the result of the script evaluation or an error.
 */
/* @abstract评估给定的JavaScript字符串。
  @param javaScriptString要评估的JavaScript字符串。
  @param completionHandler脚本评估完成或失败时调用的块。
  @discussion completeHandler传递脚本评估的结果或错误。
 */
- (void)evaluateJavaScript:(NSString *)javaScriptString completionHandler:(void (^ _Nullable)(_Nullable id, NSError * _Nullable error))completionHandler;

/*! @abstract A Boolean value indicating whether horizontal swipe gestures
 will trigger back-forward list navigations.
 @discussion The default value is NO.
 */
/*！ @abstract一个布尔值，表示水平滑动手势
   将触发后退列表导航。
   @discussion默认值为NO。
  */
@property (nonatomic) BOOL allowsBackForwardNavigationGestures;

/*! @abstract The custom user agent string or nil if no custom user agent string has been set.
 */
/*！ @abstract自定义用户代理字符串，如果没有设置自定义用户代理字符串，则为nil。
  */
@property (nullable, nonatomic, copy) NSString *customUserAgent API_AVAILABLE(macosx(10.11), ios(9.0));

/*! @abstract A Boolean value indicating whether link preview is allowed for any
 links inside this WKWebView.
 @discussion The default value is YES on Mac and iOS.
 */
/*！ @abstract一个布尔值，表示是否允许链接预览
   此WKWebView内的链接。
   @discussion Mac和iOS上的默认值为YES。
  */
@property (nonatomic) BOOL allowsLinkPreview API_AVAILABLE(macosx(10.11), ios(9.0));

#if TARGET_OS_IPHONE
/*! @abstract The scroll view associated with the web view.
 */
/*！ @abstract与网页视图关联的滚动视图。
  */
@property (nonatomic, readonly, strong) UIScrollView *scrollView;
#endif

#if !TARGET_OS_IPHONE
/* @abstract A Boolean value indicating whether magnify gestures will
 change the web view's magnification.
 @discussion It is possible to set the magnification property even if
 allowsMagnification is set to NO.
 The default value is NO.
 */
/* @abstract一个布尔值，表示是否放大手势会
  更改网页视图的放大倍数。
  @discussion即使设置放大属性也是可以的
  allowMagnification设置为NO。
  默认值为NO。
 */
@property (nonatomic) BOOL allowsMagnification;

/* @abstract The factor by which the page content is currently scaled.
 @discussion The default value is 1.0.
 */
/* @abstract目前缩放页面内容的因素。
  @discussion默认值为1.0。
 */
@property (nonatomic) CGFloat magnification;

/* @abstract Scales the page content by a specified factor and centers the
 result on a specified point.
 * @param magnification The factor by which to scale the content.
 * @param point The point (in view space) on which to center magnification.
 */
/* @abstract按照指定的因素缩放页面内容，并将其中心
  导致指定点。
 * @param是缩放内容的因素。
 * @param point放置中心的点（视图空间）。
 */
- (void)setMagnification:(CGFloat)magnification centeredAtPoint:(CGPoint)point;

#endif

@end

#if !TARGET_OS_IPHONE

@interface WKWebView (WKIBActions) <NSUserInterfaceValidations>

/*! @abstract Action method that navigates to the back item in the
 back-forward list.
 @param sender The object that sent this message.
 */
- (IBAction)goBack:(nullable id)sender;

/*! @abstract Action method that navigates to the forward item in the
 back-forward list.
 @param sender The object that sent this message.
 */
- (IBAction)goForward:(nullable id)sender;

/*! @abstract Action method that reloads the current page.
 @param sender The object that sent this message.
 */
- (IBAction)reload:(nullable id)sender;

/*! @abstract Action method that reloads the current page, performing
 end-to-end revalidation using cache-validating conditionals if possible.
 @param sender The object that sent this message.
 */
- (IBAction)reloadFromOrigin:(nullable id)sender;

/*! @abstract Action method that stops loading all resources on the current
 page.
 @param sender The object that sent this message.
 */
- (IBAction)stopLoading:(nullable id)sender;

@end

#endif

@interface WKWebView (WKDeprecated)

@property (nonatomic, readonly, copy) NSArray *certificateChain API_DEPRECATED_WITH_REPLACEMENT("serverTrust", macosx(10.11, 10.12), ios(9.0, 10.0));

@end

NS_ASSUME_NONNULL_END

#endif
