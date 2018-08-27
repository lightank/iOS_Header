//
//  UITextView.h
//  UIKit
//
//  Copyright (c) 2007-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIScrollView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UITextInput.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDataDetectors.h>
#import <UIKit/UITextInteraction.h>
#import <UIKit/UIContentSizeCategoryAdjusting.h>

NS_ASSUME_NONNULL_BEGIN

@class UIFont, UIColor, UITextView, NSTextContainer, NSLayoutManager, NSTextStorage, NSTextAttachment;

@protocol UITextViewDelegate <NSObject, UIScrollViewDelegate>

@optional
//是否可以开始编辑
- (BOOL)textViewShouldBeginEditing:(UITextView *)textView;
//是否可以结束编辑
- (BOOL)textViewShouldEndEditing:(UITextView *)textView;
//开始编辑
- (void)textViewDidBeginEditing:(UITextView *)textView;
//结束编辑
- (void)textViewDidEndEditing:(UITextView *)textView;
//Asks the delegate whether the specified text should be replaced in the text view.
//请求代理是否应在文本视图中替换指定的文本。
- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text;
//文本内容变更
- (void)textViewDidChange:(UITextView *)textView;
//Tells the delegate that the text selection changed in the specified text view.
//告诉委托人在指定的文本视图中更改了文本选择。
- (void)textViewDidChangeSelection:(UITextView *)textView;
//Asks the delegate if the specified text view should allow user interaction with the given URL in the given range of text.
//向代理询问指定的文本视图是否应允许用户与给定文本范围内的给定URL进行交互。
- (BOOL)textView:(UITextView *)textView shouldInteractWithURL:(NSURL *)URL inRange:(NSRange)characterRange interaction:(UITextItemInteraction)interaction NS_AVAILABLE_IOS(10_0);
//Asks the delegate if the specified text view should allow user interaction with the provided text attachment in the given range of text.
//向代理询问指定的文本视图是否应允许用户与给定文本范围内的提供的文本附件进行交互。
- (BOOL)textView:(UITextView *)textView shouldInteractWithTextAttachment:(NSTextAttachment *)textAttachment inRange:(NSRange)characterRange interaction:(UITextItemInteraction)interaction NS_AVAILABLE_IOS(10_0);
//Asks the delegate if the specified text view should allow user interaction with the given URL in the given range of text.
//向代理询问指定的文本视图是否应允许用户与给定文本范围内的给定URL进行交互。
- (BOOL)textView:(UITextView *)textView shouldInteractWithURL:(NSURL *)URL inRange:(NSRange)characterRange NS_DEPRECATED_IOS(7_0, 10_0, "Use textView:shouldInteractWithURL:inRange:forInteractionType: instead");
//Asks the delegate if the specified text view should allow user interaction with the provided text attachment in the given range of text.
//向代理询问指定的文本视图是否应允许用户与给定文本范围内的提供的文本附件进行交互。
- (BOOL)textView:(UITextView *)textView shouldInteractWithTextAttachment:(NSTextAttachment *)textAttachment inRange:(NSRange)characterRange NS_DEPRECATED_IOS(7_0, 10_0, "Use textView:shouldInteractWithTextAttachment:inRange:forInteractionType: instead");

@end

NS_CLASS_AVAILABLE_IOS(2_0) @interface UITextView : UIScrollView <UITextInput, UIContentSizeCategoryAdjusting>
//代理
@property(nullable,nonatomic,weak) id<UITextViewDelegate> delegate;
//文本内容
@property(null_resettable,nonatomic,copy) NSString *text;
//字体
@property(nullable,nonatomic,strong) UIFont *font;
//文字颜色
@property(nullable,nonatomic,strong) UIColor *textColor;
//文本对齐方式
@property(nonatomic) NSTextAlignment textAlignment;    // default is NSLeftTextAlignment
//The current selection range of the receiver.
//当前接收者的选择范围。
@property(nonatomic) NSRange selectedRange;
//A Boolean value indicating whether the receiver is editable.
//是否正在编辑
@property(nonatomic,getter=isEditable) BOOL editable __TVOS_PROHIBITED;
//A Boolean value indicating whether the receiver is selectable.
//是否可选择
@property(nonatomic,getter=isSelectable) BOOL selectable NS_AVAILABLE_IOS(7_0); // toggle selectability, which controls the ability of the user to select content and interact with URLs & attachments
//The types of data converted to clickable URLs in the text view.
//在文本视图中转换为可点击网址的数据类型。如:电话,网址,地址,日历事件等等
@property(nonatomic) UIDataDetectorTypes dataDetectorTypes NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;

//A Boolean value indicating whether the text view allows the user to edit style information.
//一个布尔值，指示文本视图是否允许用户编辑样式信息。
@property(nonatomic) BOOL allowsEditingTextAttributes NS_AVAILABLE_IOS(6_0); // defaults to NO
//The styled text displayed by the text view.
//由文本视图显示的样式文本。
@property(null_resettable,copy) NSAttributedString *attributedText NS_AVAILABLE_IOS(6_0);
//The attributes to apply to new text being entered by the user.
//应用于用户输入的新文本的属性。
@property(nonatomic,copy) NSDictionary<NSString *, id> *typingAttributes NS_AVAILABLE_IOS(6_0); // automatically resets when the selection changes
//Scrolls the receiver until the text in the specified range is visible.
//滚动接收者，直到指定范围内的文本可见。
- (void)scrollRangeToVisible:(NSRange)range;


// Presented when object becomes first responder.  If set to nil, reverts to following responder chain.  If
// set while first responder, will not take effect until reloadInputViews is called.
//当对象成为第一个响应者时呈现。 如果设置为nil，则恢复到以下响应者链。 如果
//设置第一个响应者，直到reloadInputViews被调用才会生效。
//The custom input view to display when the text view becomes the first responder.
//当文本视图成为第一个响应者时显示的自定义输入视图。
@property (nullable, readwrite, strong) UIView *inputView;
//The custom accessory view to display when the text view becomes the first responder
//当文本视图成为第一个响应者时显示的自定义附件视图
@property (nullable, readwrite, strong) UIView *inputAccessoryView;

//A Boolean value indicating whether inserting text replaces the previous contents.
//The default value of this property is NO. When the value of this property is YES and the text view is in editing mode, the selection UI is hidden and inserting new text clears the contents of the text view and sets the value of this property back to NO.
//一个布尔值，指示插入文本是否替换以前的内容。
//此属性的默认值为NO。 当此属性的值为YES并且文本视图处于编辑模式时，选择UI被隐藏，并插入新文本将清除文本视图的内容，并将该属性的值设置为NO。
@property(nonatomic) BOOL clearsOnInsertion NS_AVAILABLE_IOS(6_0); // defaults to NO. if YES, the selection UI is hidden, and inserting text will replace the contents of the field. changing the selection will automatically set this to NO.

// Create a new text view with the specified text container (can be nil) - this is the new designated initializer for this class
//使用指定的文本容器创建一个新的文本视图（可以是nil） - 这是这个类的新的指定的初始化器
- (instancetype)initWithFrame:(CGRect)frame textContainer:(nullable NSTextContainer *)textContainer NS_AVAILABLE_IOS(7_0) NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

// Get the text container for the text view
//The text container object defining the area in which text is displayed in this text view. (read-only)
//获取文本视图的文本容器
//文本容器对象定义在此文本视图中显示文本的区域。 （只读）
@property(nonatomic,readonly) NSTextContainer *textContainer NS_AVAILABLE_IOS(7_0);
// Inset the text container's layout area within the text view's content area
//The inset of the text container's layout area within the text view's content area.
//在文本视图的内容区域内插入文本容器的布局区域
//文本视图内容区域中文本容器的布局区域的插入。
@property(nonatomic, assign) UIEdgeInsets textContainerInset NS_AVAILABLE_IOS(7_0);

// Convenience accessors (access through the text container)
//The layout manager that lays out text for the receiver’s text container. (read-only)
//方便的访问者（通过文本容器访问）
//布局管理器为接收者的文本容器布置文本。 （只读）
@property(nonatomic,readonly) NSLayoutManager *layoutManager NS_AVAILABLE_IOS(7_0);
//The text storage object holding the text displayed in this text view. (read-only)
//保存文本显示在此文本视图中的文本存储对象。 （只读）
@property(nonatomic,readonly,strong) NSTextStorage *textStorage NS_AVAILABLE_IOS(7_0);

// Style for links
//The attributes to apply to links.
@property(null_resettable, nonatomic, copy) NSDictionary<NSString *, id> *linkTextAttributes NS_AVAILABLE_IOS(7_0);

@end
//开始编辑
UIKIT_EXTERN NSNotificationName const UITextViewTextDidBeginEditingNotification;
//编辑中
UIKIT_EXTERN NSNotificationName const UITextViewTextDidChangeNotification;
//编辑结束
UIKIT_EXTERN NSNotificationName const UITextViewTextDidEndEditingNotification;

NS_ASSUME_NONNULL_END
