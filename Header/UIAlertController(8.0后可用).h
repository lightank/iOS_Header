//
//  UIAlertController.h
//  UIKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

#import <UIKit/UIViewController.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIAlertActionStyle) {
    UIAlertActionStyleDefault = 0,
    UIAlertActionStyleCancel,
    UIAlertActionStyleDestructive
} NS_ENUM_AVAILABLE_IOS(8_0);

typedef NS_ENUM(NSInteger, UIAlertControllerStyle) {
    //底端显示
    UIAlertControllerStyleActionSheet = 0,
    //中部现在
    UIAlertControllerStyleAlert
} NS_ENUM_AVAILABLE_IOS(8_0);

NS_CLASS_AVAILABLE_IOS(8_0) @interface UIAlertAction : NSObject <NSCopying>

+ (instancetype)actionWithTitle:(nullable NSString *)title style:(UIAlertActionStyle)style handler:(void (^ __nullable)(UIAlertAction *action))handler;
//动作标题
@property (nullable, nonatomic, readonly) NSString *title;
//动作类型
@property (nonatomic, readonly) UIAlertActionStyle style;
//是否可用
@property (nonatomic, getter=isEnabled) BOOL enabled;

@end

/*
 参考自:http://blog.csdn.net/iosbird/article/details/50432216
 
 如果上拉菜单中有“取消”按钮的话，那么它永远都会出现在菜单的底部，不管添加的次序是如何（就是这么任性）。其他的按钮将会按照添加的次序从上往下依次显示。《iOS 用户界面指南》要求所有的“毁坏”样式按钮都必须排名第一（红榜嘛，很好理解的，对不对？）
 */

NS_CLASS_AVAILABLE_IOS(8_0) @interface UIAlertController : UIViewController
//初始化,同时设置标题,描述信息,跟显示的类型
+ (instancetype)alertControllerWithTitle:(nullable NSString *)title message:(nullable NSString *)message preferredStyle:(UIAlertControllerStyle)preferredStyle;
//添加动作
- (void)addAction:(UIAlertAction *)action;
@property (nonatomic, readonly) NSArray<UIAlertAction *> *actions;

@property (nonatomic, strong, nullable) UIAlertAction *preferredAction NS_AVAILABLE_IOS(9_0);
//添加文字输入框
- (void)addTextFieldWithConfigurationHandler:(void (^ __nullable)(UITextField *textField))configurationHandler;
//文字输入框数组
@property (nullable, nonatomic, readonly) NSArray<UITextField *> *textFields;

@property (nullable, nonatomic, copy) NSString *title;
@property (nullable, nonatomic, copy) NSString *message;

@property (nonatomic, readonly) UIAlertControllerStyle preferredStyle;

@end

NS_ASSUME_NONNULL_END
