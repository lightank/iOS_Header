//
//  UIActivityIndicatorView.h
//  UIKit
//
//  Copyright (c) 2005-2016 Apple Inc. All rights reserved.
//

#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIActivityIndicatorViewStyle) {
    //白色,大小是（37，37）
    UIActivityIndicatorViewStyleWhiteLarge,
    //白色,大小是（22，22）
    UIActivityIndicatorViewStyleWhite,
    //灰色大小是（22，22）
    UIActivityIndicatorViewStyleGray __TVOS_PROHIBITED,
};

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIActivityIndicatorView : UIView <NSCoding>

- (instancetype)initWithActivityIndicatorStyle:(UIActivityIndicatorViewStyle)style NS_DESIGNATED_INITIALIZER; // sizes the view according to the style
- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;
- (instancetype) initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property(nonatomic) UIActivityIndicatorViewStyle activityIndicatorViewStyle; // default is UIActivityIndicatorViewStyleWhite
//default is YES. 设置动画结束是否隐藏控件。
@property(nonatomic) BOOL                         hidesWhenStopped;           // default is YES. calls -setHidden when animating gets set to NO

@property (nullable, readwrite, nonatomic, strong) UIColor *color NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
//开启动画，也就是开始旋转
- (void)startAnimating;
//停止动画，旋转
- (void)stopAnimating;
#if UIKIT_DEFINE_AS_PROPERTIES
//获取状态，NO 表示正在旋转，YES 表示没有旋转
@property(nonatomic, readonly, getter=isAnimating) BOOL animating;
#else
- (BOOL)isAnimating;
#endif

@end

NS_ASSUME_NONNULL_END
