//
//  UITextField.h
//  UIKit
//
//  Copyright (c) 2005-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIFont.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UITextInput.h>
#import <UIKit/UIContentSizeCategoryAdjusting.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage, UIImageView, UILabel, UIColor, UIButton;
@class UITextFieldAtomBackgroundView;
@class UITextFieldBackgroundView;
@class UITextFieldBorderView;
@class UITextFieldLabel;
@class UITextInputTraits;
@class UITextSelectionView;
@class UITextInteractionAssistant;
@class UIPopoverController;
@protocol UITextFieldDelegate;
@protocol UITextSelecting;

typedef NS_ENUM(NSInteger, UITextBorderStyle) {
    UITextBorderStyleNone,
    //矩形，黑色边框，透明背景
    UITextBorderStyleLine,
    //和上面类似，但是是灰色的边框，背景透明
    UITextBorderStyleBezel,
    //圆角矩形，背景是白色，不再是透明的
    UITextBorderStyleRoundedRect
};

//UITextField各类辅助视图类型
typedef NS_ENUM(NSInteger, UITextFieldViewMode) {
    //永不出现
    UITextFieldViewModeNever,
    //编辑时出现
    UITextFieldViewModeWhileEditing,
    //不编辑时出现
    UITextFieldViewModeUnlessEditing,
    //总出现
    UITextFieldViewModeAlways
};

//UITextField结束编辑原因
typedef NS_ENUM(NSInteger, UITextFieldDidEndEditingReason) {
    //提交
    UITextFieldDidEndEditingReasonCommitted,
    //取消
    UITextFieldDidEndEditingReasonCancelled UIKIT_AVAILABLE_TVOS_ONLY(10_0)
} NS_ENUM_AVAILABLE_IOS(10_0);

NS_CLASS_AVAILABLE_IOS(2_0) @interface UITextField : UIControl <UITextInput, NSCoding, UIContentSizeCategoryAdjusting>
//输入框纯文本内容
@property(nullable, nonatomic,copy)   NSString               *text;                 // default is nil
//输入框富文本内容
@property(nullable, nonatomic,copy)   NSAttributedString     *attributedText NS_AVAILABLE_IOS(6_0); // default is nil
//输入框文本颜色
@property(nullable, nonatomic,strong) UIColor                *textColor;            // default is nil. use opaque black
//输入框文本字体
@property(nullable, nonatomic,strong) UIFont                 *font;                 // default is nil. use system font 12 pt
//文本对齐方式,默认是左对齐
@property(nonatomic)        NSTextAlignment         textAlignment;        // default is NSLeftTextAlignment
//边框类型,默认无边框
@property(nonatomic)        UITextBorderStyle       borderStyle;          // default is UITextBorderStyleNone. If set to UITextBorderStyleRoundedRect, custom background images are ignored.
//The default attributes to apply to the text.
//默认的文字书写
@property(nonatomic,copy)   NSDictionary<NSString *, id>           *defaultTextAttributes NS_AVAILABLE_IOS(7_0); // applies attributes to the full range of text. Unset attributes act like default values.
//占位符
@property(nullable, nonatomic,copy)   NSString               *placeholder;          // default is nil. string is drawn 70% gray
//占位符富文本
@property(nullable, nonatomic,copy)   NSAttributedString     *attributedPlaceholder NS_AVAILABLE_IOS(6_0); // default is nil
//是否在开始编辑时清空内容
@property(nonatomic)        BOOL                    clearsOnBeginEditing; // default is NO which moves cursor to location clicked. if YES, all text cleared
//A Boolean value indicating whether the font size should be reduced in order to fit the text string into the text field’s bounding rectangle.
//一个布尔值，指示是否应缩小字体大小以便将文本字符串适合文本字段的边界矩形。
@property(nonatomic)        BOOL                    adjustsFontSizeToFitWidth; // default is NO. if YES, text will shrink to minFontSize along baseline
//The size of the smallest permissible font with which to draw the text field’s text.
//用于绘制文本字段文本的最小允许字体的大小。默认值为0.0。 实际的最小值可能固定在可读取的位置。 如果adjustFontSizeToFitWidth为YES则使用
@property(nonatomic)        CGFloat                 minimumFontSize;      // default is 0.0. actual min may be pinned to something readable. used if adjustsFontSizeToFitWidth is YES
//输入框代理
@property(nullable, nonatomic,weak)   id<UITextFieldDelegate> delegate;             // default is nil. weak reference
//背景图片,默认值为零。 画边界。 形象应该是可拉伸的
@property(nullable, nonatomic,strong) UIImage                *background;           // default is nil. draw in border rect. image should be stretchable
//The image that represents the background appearance of the text field when it is disabled.
//表示文本字段禁用时的背景外观的图像。
@property(nullable, nonatomic,strong) UIImage                *disabledBackground;   // default is nil. ignored if background not set. image should be stretchable
//是否正在编辑
@property(nonatomic,readonly,getter=isEditing) BOOL editing;
//是否允许编辑文字属性
//A Boolean value indicating whether the user may edit the attributes of the text in the text field.
//一个布尔值，指示用户是否可以在文本字段中编辑文本的属性。默认为NO。 允许使用样式操作编辑文本属性并粘贴富文本
@property(nonatomic) BOOL allowsEditingTextAttributes NS_AVAILABLE_IOS(6_0); // default is NO. allows editing text attributes with style operations and pasting rich text
//The attributes to apply to new text being entered by the user.
//应用于用户输入的新文本的属性。选择更改时自动复位
@property(nullable, nonatomic,copy) NSDictionary<NSString *, id> *typingAttributes NS_AVAILABLE_IOS(6_0); // automatically resets when the selection changes

// You can supply custom views which are displayed at the left or right
// sides of the text field. Uses for such views could be to show an icon or
// a button to operate on the text in the field in an application-defined
// manner.
//
// A very common use is to display a clear button on the right side of the
// text field, and a standard clear button is provided.
//您可以提供左侧或右侧显示的自定义视图
//文本字段的边。 用于此类视图可能是显示图标或
//一个按钮在应用程序定义的字段中对文本进行操作
//方式
//
//很常见的用法是在右侧显示一个清除按钮
//文本字段，并提供标准的清除按钮。
//清空按钮视图类型
@property(nonatomic)        UITextFieldViewMode  clearButtonMode; // sets when the clear button shows up. default is UITextFieldViewModeNever
/*
 实现如下需求
 在输入框左侧有一个小图标提示(比如账号左侧一个人的提示，密码左侧有一个锁的提示）
 
 userName=[[UITextField alloc]initWithFrame:CGRectMake(10, SCREEN_HEIGHT*0.3, SCREEN_WIDTH-20, 36)];
 userName.placeholder=@"登陆账号";
 userName.borderStyle=UITextBorderStyleRoundedRect;
 userName.clearButtonMode=UITextFieldViewModeWhileEditing;
 UIImageView *imageViewUserName=[[UIImageView alloc]initWithFrame:CGRectMake(0, 0, 30, 30)];
 imageViewUserName.image=[UIImage imageNamed:@"userinfo.png"];
 userName.leftView=imageViewUserName;
 userName.leftViewMode=UITextFieldViewModeAlways; //此处用来设置leftview现实时机
 */
//左边视图
@property(nullable, nonatomic,strong) UIView              *leftView;        // e.g. magnifying glass
@property(nonatomic)        UITextFieldViewMode  leftViewMode;    // sets when the left view shows up. default is UITextFieldViewModeNever
//同左边视图
@property(nullable, nonatomic,strong) UIView              *rightView;       // e.g. bookmarks button
@property(nonatomic)        UITextFieldViewMode  rightViewMode;   // sets when the right view shows up. default is UITextFieldViewModeNever

// drawing and positioning overrides
//绘制和定位覆盖

//Returns the receiver’s border rectangle.
//返回接收者的边框矩形。
- (CGRect)borderRectForBounds:(CGRect)bounds;
//Returns the drawing rectangle for the text field’s text.
//返回文本字段文本的绘图矩形。
- (CGRect)textRectForBounds:(CGRect)bounds;
//Returns the drawing rectangle for the text field’s placeholder text
//返回文本字段占位符文本的绘图矩形
- (CGRect)placeholderRectForBounds:(CGRect)bounds;
//Returns the rectangle in which editable text can be displayed.
//返回可显示可编辑文本的矩形。
- (CGRect)editingRectForBounds:(CGRect)bounds;
//Returns the drawing rectangle for the built-in clear button.
//返回内置清除按钮的绘图矩形。
- (CGRect)clearButtonRectForBounds:(CGRect)bounds;
//Returns the drawing rectangle of the receiver’s left overlay view.
//返回接收者的左重叠视图的绘图矩形。
- (CGRect)leftViewRectForBounds:(CGRect)bounds;
//Returns the drawing location of the receiver’s right overlay view.
//返回接收者右侧叠加视图的绘图位置。
- (CGRect)rightViewRectForBounds:(CGRect)bounds;
//Draws the receiver’s text in the specified rectangle.
//在指定的矩形中绘制接收者的文本。
- (void)drawTextInRect:(CGRect)rect;
//Draws the receiver’s placeholder text in the specified rectangle.
//在指定的矩形中绘制接收者的占位符文本。
- (void)drawPlaceholderInRect:(CGRect)rect;

// Presented when object becomes first responder.  If set to nil, reverts to following responder chain.  If
// set while first responder, will not take effect until reloadInputViews is called.
//当对象成为第一个响应者时呈现。 如果设置为nil，则恢复到以下响应者链。 如果
//设置第一个响应者，直到reloadInputViews被调用才会生效。
//The custom input view to display when the text field becomes the first responder.
//当文本字段成为第一个响应者时显示的自定义输入视图。
@property (nullable, readwrite, strong) UIView *inputView;
//The custom accessory view to display when the text field becomes the first responder
//当文本字段成为第一个响应者时显示的自定义附件视图
@property (nullable, readwrite, strong) UIView *inputAccessoryView;

//A Boolean value indicating whether inserting text replaces the previous contents.
//一个布尔值，指示是否插入文本替换以前的内容。插入的时候清空输入框
//默认为NO。 如果是，则选择UI被隐藏，并且插入文本将替换该字段的内容。 更改选择将自动设置为NO。
@property(nonatomic) BOOL clearsOnInsertion NS_AVAILABLE_IOS(6_0); // defaults to NO. if YES, the selection UI is hidden, and inserting text will replace the contents of the field. changing the selection will automatically set this to NO.

@end

@interface UIView (UITextField)
//Causes the view (or one of its embedded text fields) to resign the first responder status.
//导致视图（或其中一个嵌入文本字段）撤销第一个响应者状态。
- (BOOL)endEditing:(BOOL)force;    // use to make the view or any subview that is the first responder resign (optionally force)
@end

@protocol UITextFieldDelegate <NSObject>

@optional
//是否可以开始编辑
- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField;        // return NO to disallow editing.
//已经开始编辑
- (void)textFieldDidBeginEditing:(UITextField *)textField;           // became first responder
//是否可以结束编辑
- (BOOL)textFieldShouldEndEditing:(UITextField *)textField;          // return YES to allow editing to stop and to resign first responder status. NO to disallow the editing session to end
//已经结束编辑
- (void)textFieldDidEndEditing:(UITextField *)textField;             // may be called if forced even if shouldEndEditing returns NO (e.g. view removed from window) or endEditing:YES called
//因为什么原因已经结束编辑
- (void)textFieldDidEndEditing:(UITextField *)textField reason:(UITextFieldDidEndEditingReason)reason NS_AVAILABLE_IOS(10_0); // if implemented, called in place of textFieldDidEndEditing:
//Asks the delegate if the specified text should be changed.
//请求委托人是否应该更改指定的文本。
//The text field calls this method whenever the user types a new character in the text field or deletes an existing character.
//只要用户在文本字段中键入新字符或删除现有字符，文本字段就会调用此方法。
- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string;   // return NO to not change text
//当点击清空按钮时,是否清空文本
- (BOOL)textFieldShouldClear:(UITextField *)textField;               // called when clear button pressed. return NO to ignore (no notifications)
//当点击"return"按钮时,是否返回
- (BOOL)textFieldShouldReturn:(UITextField *)textField;              // called when 'return' key pressed. return NO to ignore.

@end
//开始编辑
UIKIT_EXTERN NSNotificationName const UITextFieldTextDidBeginEditingNotification;
//编辑中
UIKIT_EXTERN NSNotificationName const UITextFieldTextDidEndEditingNotification;
//结束编辑
UIKIT_EXTERN NSNotificationName const UITextFieldTextDidChangeNotification;

UIKIT_EXTERN NSString *const UITextFieldDidEndEditingReasonKey NS_AVAILABLE_IOS(10_0);

NS_ASSUME_NONNULL_END

