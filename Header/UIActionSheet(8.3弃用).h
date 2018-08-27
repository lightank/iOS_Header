//
//  UIActionSheet.h
//  UIKit
//
//  Copyright 2010-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITextField.h>
#import <UIKit/UIView.h>

NS_ASSUME_NONNULL_BEGIN

@protocol UIActionSheetDelegate;
@class UILabel, UIToolbar, UITabBar, UIWindow, UIBarButtonItem, UIPopoverController;

typedef NS_ENUM(NSInteger, UIActionSheetStyle) {
    UIActionSheetStyleAutomatic        = -1,       // take appearance from toolbar style otherwise uses 'default'
    UIActionSheetStyleDefault          = UIBarStyleDefault,
    UIActionSheetStyleBlackTranslucent = UIBarStyleBlackTranslucent,
    UIActionSheetStyleBlackOpaque      = UIBarStyleBlackOpaque ,
} __TVOS_PROHIBITED;

NS_CLASS_DEPRECATED_IOS(2_0, 8_3, "UIActionSheet is deprecated. Use UIAlertController with a preferredStyle of UIAlertControllerStyleActionSheet instead") __TVOS_PROHIBITED

/*
 UIActionSheet 与alertview相似，同样也是弹框提示，不同的地方在于actionsheet是靠底端显示，而alertview是居中显示。
 // 方法1 无代理，只有2个确定按钮
 UIActionSheet *actionsheet01 = [[UIActionSheet alloc] initWithTitle:@"按钮点击后我才出现的。" delegate:nil cancelButtonTitle:@"取消" destructiveButtonTitle:@"确定" otherButtonTitles:@"知道了", nil nil];
 // 显示
 [actionsheet01 showInView:self.view];
 
 
 
 // 方法2 无代理，有多个确定按钮
 UIActionSheet *actionsheet02 = [[UIActionSheet alloc] initWithTitle:@"按钮点击后我才出现的。" delegate:nil cancelButtonTitle:@"取消" destructiveButtonTitle:@"确定" otherButtonTitles:@"知道了0", @"知道了1", @"知道了2", @"知道了3", nil nil];
 // 显示
 [actionsheet02 showInView:self.view];
 
 
 
 // 方法3 有代理，有2个确定按钮
 
 1 设置代理为 self
 2 添加协议
 3 实现方法
 
UIActionSheet *actionsheet03 = [[UIActionSheet alloc] initWithTitle:@"选择图片" delegate:self cancelButtonTitle:@"取消" destructiveButtonTitle:nil otherButtonTitles:@"相册", @"拍照", nil nil];
// 显示
[actionsheet03 showInView:self.view];

 // 添加协议
 @interface ViewController () <UIActionSheetDelegate>
 
 @end

// UIActionSheetDelegate实现代理方法
- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    NSLog(@"buttonIndex=%ld", buttonIndex);
    
    // 方法1
    //    if (0 == buttonIndex)
    //    {
    //        NSLog(@"点击了相册按钮");
    //    }
    //    else if (1 == buttonIndex)
    //    {
    //        NSLog(@"点击了拍照按钮");
    //    }
    //    else if (2 == buttonIndex)
    //    {
    //        NSLog(@"点击了取消按钮");
    //    }
    
    // 方法2
    NSString *title = [actionSheet buttonTitleAtIndex:buttonIndex];
    BOOL isTakePhoto = [title isEqualToString:@"拍照"];
    BOOL isPhotos = [title isEqualToString:@"相册"];
    if (isTakePhoto)
    {
        NSLog(@"点击了拍照按钮");
    }
    else if (isPhotos)
    {
        NSLog(@"点击了相册按钮");
    }
    else
    {
        NSLog(@"点击了取消按钮");  
    }  
}
 
 
 // 方法4
 iOS8以后出现了UIAlertController视图控制器，通过设置UIAlertController的style属性来控制是alertview还是actionsheet

UIAlertController *actionSheetController = [UIAlertController alertControllerWithTitle:nil message:@"选择图片" preferredStyle:UIAlertControllerStyleActionSheet];
// 响应方法-取消
UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
    NSLog(@"点击了取消按钮");
}];
// 响应方法-相册
UIAlertAction *takeAction = [UIAlertAction actionWithTitle:@"相册" style:UIAlertActionStyleDestructive handler:^(UIAlertAction * _Nonnull action) {
    NSLog(@"点击了相册按钮");
}];
// 响应方法-拍照
UIAlertAction *photoAction = [UIAlertAction actionWithTitle:@"拍照" style:UIAlertActionStyleDestructive handler:^(UIAlertAction * _Nonnull action) {
    NSLog(@"点击了拍照按钮");
}];
// 添加响应方式
[actionSheetController addAction:cancelAction];
[actionSheetController addAction:takeAction];
[actionSheetController addAction:photoAction];
// 显示
[self presentViewController:actionSheetController animated:YES completion:nil];
 */

@interface UIActionSheet : UIView

- (instancetype)initWithTitle:(nullable NSString *)title delegate:(nullable id<UIActionSheetDelegate>)delegate cancelButtonTitle:(nullable NSString *)cancelButtonTitle destructiveButtonTitle:(nullable NSString *)destructiveButtonTitle otherButtonTitles:(nullable NSString *)otherButtonTitles, ... NS_REQUIRES_NIL_TERMINATION NS_EXTENSION_UNAVAILABLE_IOS("Use UIAlertController instead.");

@property(nullable,nonatomic,weak) id<UIActionSheetDelegate> delegate;
@property(nonatomic,copy) NSString *title;
@property(nonatomic) UIActionSheetStyle actionSheetStyle; // default is UIActionSheetStyleAutomatic. ignored if alert is visible

// adds a button with the title. returns the index (0 based) of where it was added. buttons are displayed in the order added except for the
// destructive and cancel button which will be positioned based on HI requirements. buttons cannot be customized.
//视图标题
- (NSInteger)addButtonWithTitle:(nullable NSString *)title;    // returns index of button. 0 based.
//对应下标按钮的标题
- (nullable NSString *)buttonTitleAtIndex:(NSInteger)buttonIndex;
//按钮数量
@property(nonatomic,readonly) NSInteger numberOfButtons;
@property(nonatomic) NSInteger cancelButtonIndex;      // if the delegate does not implement -actionSheetCancel:, we pretend this button was clicked on. default is -1
@property(nonatomic) NSInteger destructiveButtonIndex;        // sets destructive (red) button. -1 means none set. default is -1. ignored if only one button

@property(nonatomic,readonly) NSInteger firstOtherButtonIndex;	// -1 if no otherButtonTitles or initWithTitle:... not used
@property(nonatomic,readonly,getter=isVisible) BOOL visible;

// show a sheet animated. you can specify either a toolbar, a tab bar, a bar button item or a plain view. We do a special animation if the sheet rises from
// a toolbar, tab bar or bar button item and we will automatically select the correct style based on the bar style. if not from a bar, we use
// UIActionSheetStyleDefault if automatic style set
- (void)showFromToolbar:(UIToolbar *)view;
- (void)showFromTabBar:(UITabBar *)view;
- (void)showFromBarButtonItem:(UIBarButtonItem *)item animated:(BOOL)animated NS_AVAILABLE_IOS(3_2);
- (void)showFromRect:(CGRect)rect inView:(UIView *)view animated:(BOOL)animated NS_AVAILABLE_IOS(3_2);
- (void)showInView:(UIView *)view;

// hides alert sheet or popup. use this method when you need to explicitly dismiss the alert.
// it does not need to be called if the user presses on a button
- (void)dismissWithClickedButtonIndex:(NSInteger)buttonIndex animated:(BOOL)animated;

@end


__TVOS_PROHIBITED
@protocol UIActionSheetDelegate <NSObject>
@optional

// Called when a button is clicked. The view will be automatically dismissed after this call returns
//点击按钮时触发
- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex NS_DEPRECATED_IOS(2_0, 8_3) __TVOS_PROHIBITED;

// Called when we cancel a view (eg. the user clicks the Home button). This is not called when the user clicks the cancel button.
// If not defined in the delegate, we simulate a click in the cancel button
- (void)actionSheetCancel:(UIActionSheet *)actionSheet NS_DEPRECATED_IOS(2_0, 8_3) __TVOS_PROHIBITED;
//视图将要弹出时触发
- (void)willPresentActionSheet:(UIActionSheet *)actionSheet NS_DEPRECATED_IOS(2_0, 8_3)__TVOS_PROHIBITED;  // before animation and showing view
//视图已经弹出时触发
- (void)didPresentActionSheet:(UIActionSheet *)actionSheet NS_DEPRECATED_IOS(2_0, 8_3) __TVOS_PROHIBITED;  // after animation

- (void)actionSheet:(UIActionSheet *)actionSheet willDismissWithButtonIndex:(NSInteger)buttonIndex NS_DEPRECATED_IOS(2_0, 8_3) __TVOS_PROHIBITED; // before animation and hiding view
- (void)actionSheet:(UIActionSheet *)actionSheet didDismissWithButtonIndex:(NSInteger)buttonIndex NS_DEPRECATED_IOS(2_0, 8_3) __TVOS_PROHIBITED;  // after animation

@end

NS_ASSUME_NONNULL_END

