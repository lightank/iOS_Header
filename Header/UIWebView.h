//
//  UIWebView.h
//  UIKit
//
//  Copyright (c) 2007-2015 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDataDetectors.h>
#import <UIKit/UIScrollView.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIWebViewNavigationType) {
    UIWebViewNavigationTypeLinkClicked, //用户触击了一个链接
    UIWebViewNavigationTypeFormSubmitted,   //用户提交了一个表单
    UIWebViewNavigationTypeBackForward, //用户触击前进或返回按钮
    UIWebViewNavigationTypeReload,  //用户触击重新加载的按钮
    UIWebViewNavigationTypeFormResubmitted, //用户重复提交表单
    UIWebViewNavigationTypeOther    //发生其它行为
} __TVOS_PROHIBITED;

typedef NS_ENUM(NSInteger, UIWebPaginationMode) {
    UIWebPaginationModeUnpaginated, //不使用翻页效果
    UIWebPaginationModeLeftToRight, //将网页超出部分分页，从左向右进行翻页
    UIWebPaginationModeTopToBottom, //将网页超出部分分页，从上向下进行翻页
    UIWebPaginationModeBottomToTop, //将网页超出部分分页，从下向上进行翻页
    UIWebPaginationModeRightToLeft  //将网页超出部分分页，从右向左进行翻页
} __TVOS_PROHIBITED;

typedef NS_ENUM(NSInteger, UIWebPaginationBreakingMode) {
    UIWebPaginationBreakingModePage,
    UIWebPaginationBreakingModeColumn
} __TVOS_PROHIBITED;

@class UIWebViewInternal;
@protocol UIWebViewDelegate;

NS_CLASS_AVAILABLE_IOS(2_0) __TVOS_PROHIBITED @interface UIWebView : UIView <NSCoding, UIScrollViewDelegate>
//设置webView的代理
@property (nullable, nonatomic, assign) id <UIWebViewDelegate> delegate;
//内置的scrollView
@property (nonatomic, readonly, strong) UIScrollView *scrollView NS_AVAILABLE_IOS(5_0);
//这是加载网页最常用的一种方式，通过一个网页URL来进行加载，这个URL可以是远程的也可以是本地的
- (void)loadRequest:(NSURLRequest *)request;
//这个方法需要将html文件读取为字符串，其中baseURL是我们自己设置的一个路径，用于寻找html文件中引用的图片等素材
- (void)loadHTMLString:(NSString *)string baseURL:(nullable NSURL *)baseURL;
//这个方式使用的比较少，但也更加自由，其中data是文件数据，MIMEType是文件类型，textEncodingName是编码类型，baseURL是素材资源路径。
- (void)loadData:(NSData *)data MIMEType:(NSString *)MIMEType textEncodingName:(NSString *)textEncodingName baseURL:(NSURL *)baseURL;

@property (nullable, nonatomic, readonly, strong) NSURLRequest *request;
//重新加载数据
- (void)reload;
//停止加载数据
- (void)stopLoading;
//返回上一级
- (void)goBack;
//跳转下一级
- (void)goForward;
//获取能否返回上一级
@property (nonatomic, readonly, getter=canGoBack) BOOL canGoBack;
//获取能否跳转下一级
@property (nonatomic, readonly, getter=canGoForward) BOOL canGoForward;
//获取是否正在加载数据
@property (nonatomic, readonly, getter=isLoading) BOOL loading;
//通过JavaScript操作web数据
- (nullable NSString *)stringByEvaluatingJavaScriptFromString:(NSString *)script;
//设置是否缩放到适合屏幕大小
@property (nonatomic) BOOL scalesPageToFit;

@property (nonatomic) BOOL detectsPhoneNumbers NS_DEPRECATED_IOS(2_0, 3_0);
//设置某些数据变为链接形式，这个枚举可以设置如电话号，地址，邮箱等转化为链接
@property (nonatomic) UIDataDetectorTypes dataDetectorTypes NS_AVAILABLE_IOS(3_0);
//设置是否使用内联播放器播放视频
@property (nonatomic) BOOL allowsInlineMediaPlayback NS_AVAILABLE_IOS(4_0); // iPhone Safari defaults to NO. iPad Safari defaults to YES
//设置视频是否自动播放
@property (nonatomic) BOOL mediaPlaybackRequiresUserAction NS_AVAILABLE_IOS(4_0); // iPhone and iPad Safari both default to YES
//设置音频播放是否支持ari play功能
@property (nonatomic) BOOL mediaPlaybackAllowsAirPlay NS_AVAILABLE_IOS(5_0); // iPhone and iPad Safari both default to YES
//设置是否将数据加载如内存后渲染界面
@property (nonatomic) BOOL suppressesIncrementalRendering NS_AVAILABLE_IOS(6_0); // iPhone and iPad Safari both default to NO
//设置用户交互模式
@property (nonatomic) BOOL keyboardDisplayRequiresUserAction NS_AVAILABLE_IOS(6_0); // default is YES
//这个属性用来设置一种模式，当网页的大小超出view时，将网页以翻页的效果展示
@property (nonatomic) UIWebPaginationMode paginationMode NS_AVAILABLE_IOS(7_0);
@property (nonatomic) UIWebPaginationBreakingMode paginationBreakingMode NS_AVAILABLE_IOS(7_0);
//设置每一页的长度
@property (nonatomic) CGFloat pageLength NS_AVAILABLE_IOS(7_0);
//设置每一页的间距
@property (nonatomic) CGFloat gapBetweenPages NS_AVAILABLE_IOS(7_0);
//获取分页数
@property (nonatomic, readonly) NSUInteger pageCount NS_AVAILABLE_IOS(7_0);
//如果你使用WebKit支持PiP功能，但要退出特定视频的画中画。设定关联web view 实例的allowsPictureInPictureMediaPlayback属性为NO。
@property (nonatomic) BOOL allowsPictureInPictureMediaPlayback NS_AVAILABLE_IOS(9_0);

@property (nonatomic) BOOL allowsLinkPreview NS_AVAILABLE_IOS(9_0); // default is NO
@end

__TVOS_PROHIBITED @protocol UIWebViewDelegate <NSObject>

@optional
//准备加载内容时调用的方法，通过返回值来进行是否加载的设置
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType;
//开始加载时调用的方法
- (void)webViewDidStartLoad:(UIWebView *)webView;
//结束加载时调用的方法
- (void)webViewDidFinishLoad:(UIWebView *)webView;
//加载失败时调用的方法
- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
