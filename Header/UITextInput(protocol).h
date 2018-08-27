//
//  UITextInput.h
//  UIKit
//
//  Copyright (c) 2009-2016 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>

#import <UIKit/UITextInputTraits.h>
#import <UIKit/UIResponder.h>

//===================================================================================================
// Responders that implement the UIKeyInput protocol will be driven by the system-provided keyboard,
// which will be made available whenever a conforming responder becomes first responder.

NS_ASSUME_NONNULL_BEGIN

/*
 让你的自定义View具备输入的功能（UIKeyInput协议）:
 通过UIKeyInput协议可以为响应者提供简单的键盘输入的功能，让需要键盘的responder成为第一响应者就行了。UIKeyInput协议必须实现的有三个方法，分别是以下方法：
 - (BOOL)hasText {
     return self.textStore.length > 0;
 }
 
 - (void)insertText:(NSString *)text {
 if (self.textStore.length < self.passWordNum) {
     //判断是否是数字
         NSCharacterSet *cs = [[NSCharacterSet characterSetWithCharactersInString:MONEYNUMBERS] invertedSet];
         NSString*filtered = [[text componentsSeparatedByCharactersInSet:cs] componentsJoinedByString:@""];
         BOOL basicTest = [text isEqualToString:filtered];
         if(basicTest) {
             if ([self.delegate respondsToSelector:@selector(passWordDidChange:)]) {
                 [self.delegate passWordDidChange:self];
             }
             if (self.textStore.length == self.passWordNum) {
                 if ([self.delegate respondsToSelector:@selector(passWordCompleteInput:)]) {
                     [self.delegate passWordCompleteInput:self];
                 }
             }
             [self.textStore appendString:text];
             [self setNeedsDisplay];
         }
     }
 }
 
 - (void)deleteBackward {
     if (self.textStore.length > 0) {
         [self.textStore deleteCharactersInRange:NSMakeRange(self.textStore.length - 1, 1)];
         if ([self.delegate respondsToSelector:@selector(passWordDidChange:)]) {
             [self.delegate passWordDidChange:self];
         }
     }
     [self setNeedsDisplay];
 }
 //是否能成为第一响应者
 - (BOOL)canBecomeFirstResponder {
     return YES;
 }

 //点击成为第一相应者
 - (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
     if (![self isFirstResponder]) {
         [self becomeFirstResponder];
     }
 }
 */

@protocol UIKeyInput <UITextInputTraits>

#if UIKIT_DEFINE_AS_PROPERTIES
//A Boolean value that indicates whether the text-entry objects has any text.
//一个布尔值，指示文本输入对象是否具有任何文本。
@property(nonatomic, readonly) BOOL hasText;
#else
- (BOOL)hasText;
#endif
//Insert a character into the displayed text.
//在显示的文本中插入一个字符。
- (void)insertText:(NSString *)text;
//Delete a character from the displayed text.
//从显示的文本中删除一个字符。
- (void)deleteBackward;

@end

//===================================================================================================
// Responders that implement the UITextInput protocol allow the system-provided keyboard to
// offer more sophisticated behaviors based on a current selection and context.
//实现UITextInput协议的响应者允许系统提供的键盘
//提供基于当前选择和上下文的更复杂的行为。

@class NSTextAlternatives;
@class UITextPosition;
@class UITextRange;
@class UITextSelectionRect;
@class UIBarButtonItemGroup;

@protocol UITextInputTokenizer;
@protocol UITextInputDelegate;

//The direction of text storage.
//文本存储方向。
typedef NS_ENUM(NSInteger, UITextStorageDirection) {
    //Storage of the text in a forward direction.
    //将文本正向存储。
    UITextStorageDirectionForward = 0,
    //Storage of the text in a backward direction.
    //将文本反向存储。
    UITextStorageDirectionBackward
};

//The direction of text layout.
//文本布局方向。
//Constants of this type are used as arguments in the positionFromPosition:inDirection:offset:, positionWithinRange:farthestInDirection:, and characterRangeByExtendingPosition:inDirection: methods.
//这种类型的常量在positionFromPosition中用作参数：inDirection：offset :, positionWithinRange：farthestInDirection :,和characterRangeByExtendingPosition：inDirection：methods。
typedef NS_ENUM(NSInteger, UITextLayoutDirection) {
    //Layout of the text to the right.
    //文本布局在右边。
    UITextLayoutDirectionRight = 2,
    //Layout of the text to the left.
    //文本布局在左边。
    UITextLayoutDirectionLeft,
    //Layout of the text in an upward direction.
    //文本在向上的布局。
    UITextLayoutDirectionUp,
    //Layout of the text in a downward direction.
    //文本的布局向下。
    UITextLayoutDirectionDown
};

typedef NSInteger UITextDirection;

//The writing direction of the text, based on language.
//文字的写作方向，基于语言。
typedef NS_ENUM(NSInteger, UITextWritingDirection) {
    //The natural writing direction as defined by the Bidi algorithm.
    //由Bidi算法定义的自然书写方向。
    UITextWritingDirectionNatural = -1,
    //Writing that goes from left to right.
    //写作从左到右。
    UITextWritingDirectionLeftToRight = 0,
    //Writing that goes from right to left.
    //写作从右到左。
    UITextWritingDirectionRightToLeft,
};

//The granularity of a unit of text.
//文本单位的大小。
typedef NS_ENUM(NSInteger, UITextGranularity) {
    //The unit of text is a character.
    //文字的单位是一个字符。
    UITextGranularityCharacter,
    //The unit of text is a word.
    //文字的单位是一个字。
    UITextGranularityWord,
    //The unit of text is a sentence.
    //文本单位是一个句子。
    UITextGranularitySentence,
    //The unit of text is a paragraph.
    //文本单位是一个段落。
    UITextGranularityParagraph,
    //The unit of text is a line.
    //文本的单位是一行。
    UITextGranularityLine,
    //The unit of text is a document.
    //文本单位是文件。
    UITextGranularityDocument
};

/*
 A dictation phrase object represents the textual interpretation of a spoken phrase as dictated by a user.
 
 Starting in iOS 5.1, when the user chooses dictation input on a supported device, the system automatically inserts recognized phrases into the current text view. You can use an object of the UIDictationPhrase class to obtain a string representing a phrase a user has dictated. In the case of ambiguous dictation results, a dictation phrase object provides an array containing alternative strings. Methods in the UITextInput protocol allow your app to respond to the completion of dictation.
 */
/*
 听写短语对象表示由用户指定的口头短语的文本解释。
 
 从iOS 5.1开始，当用户在支持的设备上选择听写输入时，系统会自动将识别的短语插入到当前的文本视图中。 您可以使用UIDictationPhrase类的对象来获取表示用户指定的短语的字符串。 在含糊的听写结果的情况下，听写短语对象提供包含替代字符串的数组。 UITextInput协议中的方法允许您的应用程序响应完成口授。
 */
NS_CLASS_AVAILABLE_IOS(5_1) @interface UIDictationPhrase : NSObject {
@private
    NSString *_text;
    NSArray * __nullable _alternativeInterpretations;
}

/* -text returns the most likely interpretation for a phrase. If there are other
 * interpretations, -alternativeInterpretations will return an array of them, with
 * the first being most likely and the last being least likely. */
/* -text返回一个短语的最可能的解释。 如果还有其他的
 *解释，-alternativeInterpretations将返回一个数组，与
 *第一个是最有可能的，最后一个是最不可能的。*/
@property (nonatomic, readonly) NSString *text;
@property (nullable, nonatomic, readonly) NSArray<NSString *> *alternativeInterpretations;

@end

/*
 A UITextInputAssistantItem object manages bar button items displayed in the shortcuts bar above the keyboard on iPad. Use this object to add app-specific actions to the shortcuts bar. The center of the shortcuts bar displays typing suggestions for the user. You can install custom bar button items that lead or trail the typing suggestions.
 
 You do not create instances of this class directly. Instead, you get an input assistant from the inputAssistantItem property of the responder object whose keyboard you want to modify. When the keyboard is displayed, UIKit automatically searches the responder chain for a text input assistant object. Typically, you assign the text input assistant to the object that becomes the first responder, but you may also assign it to a parent responder object in order to share a set of shortcuts among multiple children.
 
 The bar button items you create for the shortcuts bar must be organized into groups. A UIBarButtonItemGroup object manages each group of items, and each group may contain a single item or several items. UIKit displays as many items as possible based on the available space. When there is not enough space for all of the items, UIKit collapses each group of items down to a single representative item to make more space.
 
 Listing 1 shows a code snippet for configuring the items of the shortcuts bar. After creating the bar button items, this code creates a group and assigns that group to the leadingBarButtonGroups property. The resulting items are displayed before the typing suggestions.
 */
/*
 UITextInputAssistantItem对象管理iPad上键盘上方的快捷方式栏中显示的条形按钮项目。使用此对象可将特定于应用的操作添加到快捷方式栏中。快捷方式栏的中心显示用户的打字建议。您可以安装导航或跟踪打字建议的自定义栏按钮项。
 
 您不直接创建此类的实例。而是从您要修改其键盘的responder对象的inputAssistantItem属性中获取输入助手。当键盘显示时，UIKit会自动搜索响应者链中的文本输入辅助对象。通常，您将文本输入助手分配给成为第一个响应者的对象，但您也可以将其分配给父应答器对象，以便在多个子节点之间共享一组快捷方式。
 
 您为快捷方式栏创建的条形按钮项必须组织成组。 UIBarButtonItemGroup对象管理每组项目，每个组可能包含单个项目或多个项目。 UIKit将根据可用空间显示尽可能多的项目。当没有足够的空间用于所有项目时，UIKit将每组项目折叠到一个代表项目，以获得更多的空间。
 
 清单1显示了用于配置快捷方式条目的代码片段。创建条形按钮项后，此代码将创建一个组，并将该组分配给leadingBarButtonGroups属性。结果项目将在打字建议之前显示。
 */
NS_CLASS_AVAILABLE_IOS(9_0) __TVOS_PROHIBITED __WATCHOS_PROHIBITED @interface UITextInputAssistantItem : NSObject

/// Default is YES, controls if the user is allowed to hide the shortcuts bar. Does not influence the built in auto-hiding logic.
///A Boolean value indicating whether the shortcuts bar may be hidden by the user.
///默认值为YES，控制是否允许用户隐藏快捷方式栏。 不影响内置的自动隐藏逻辑。
///一个布尔值，指示快捷方式栏是否可能被用户隐藏。
@property (nonatomic, readwrite, assign) BOOL allowsHidingShortcuts;
/// Contains UIBarButtonItemGroups that should be displayed in the leading position on the keyboard's assistant bar.
///The array of button item groups to display before the typing suggestions.
///包含UIBarButtonItemGroups，应该显示在键盘助理栏的前导位置。
///在打字建议之前显示的按钮项目组数组。
@property (nonatomic, readwrite, copy) NSArray<UIBarButtonItemGroup *> *leadingBarButtonGroups;
/// Contains UIBarButtonItemGroups that should be displayed in the trailing position on the keyboard's assistant bar.
///The array of button item groups to display after the typing suggestions.
///包含UIBarButtonItemGroups，应该显示在键盘助理栏的尾随位置。
///在打字建议后显示的按钮项目组数组。
@property (nonatomic, readwrite, copy) NSArray<UIBarButtonItemGroup *> *trailingBarButtonGroups;

@end

@protocol UITextInput <UIKeyInput>
@required

/* Methods for manipulating text. */
//Return the text in the specified range.
//返回指定范围内的文本。
- (nullable NSString *)textInRange:(UITextRange *)range;
//Replace the text in a document that is in the specified range.
//替换文档中指定范围内的文本。
- (void)replaceRange:(UITextRange *)range withText:(NSString *)text;

/* Text may have a selection, either zero-length (a caret) or ranged.  Editing operations are
 * always performed on the text from this selection.  nil corresponds to no selection. */
//The range of selected text in a document.
/*文本可能有一个选择，零长度（插入符号）或范围。 编辑操作是
 *始终执行此选择的文本。 无对应无选择。*/
//文档中所选文本的范围。
@property (nullable, readwrite, copy) UITextRange *selectedTextRange;

/* If text can be selected, it can be marked. Marked text represents provisionally
 * inserted text that has yet to be confirmed by the user.  It requires unique visual
 * treatment in its display.  If there is any marked text, the selection, whether a
 * caret or an extended range, always resides witihin.
 *
 * Setting marked text either replaces the existing marked text or, if none is present,
 * inserts it from the current selection. */
//The range of text that is currently marked in a document. (read-only)
/*如果文本可以被选择，那么久可以被标记。 标记文字暂时表示
 *插入的文本尚未被用户确认。 它需要独特的视觉
 *在其展示处理。 如果有任何标记的文字，选择，是否
 *插入符号或扩展范围，始终驻留在屏幕上。
 *
 *设置标记的文本将取代现有标记的文本，或者如果没有，
 *从当前选择中插入。*/
//文档中当前标记的文本范围。 （只读）
@property (nullable, nonatomic, readonly) UITextRange *markedTextRange; // Nil if no marked text.
//A dictionary of attributes that describes how marked text should be drawn.
//描述如何绘制标记文本的属性字典。
@property (nullable, nonatomic, copy) NSDictionary *markedTextStyle; // Describes how the marked text should be drawn.
//Insert the provided text and marks it to indicate that it is part of an active input session.
//插入提供的文本并标记它，以指示它是活动输入会话的一部分。
- (void)setMarkedText:(nullable NSString *)markedText selectedRange:(NSRange)selectedRange; // selectedRange is a range within the markedText
//Unmark the currently marked text.
//取消标记当前标记的文本。
- (void)unmarkText;

/* The end and beginning of the the text document. */
//The text position for the beginning of a document. (read-only)
//文档开头的文本位置。 （只读）
@property (nonatomic, readonly) UITextPosition *beginningOfDocument;
//The text position for the end of a document. (read-only)
//文档结尾的文本位置。 （只读）
@property (nonatomic, readonly) UITextPosition *endOfDocument;

/* Methods for creating ranges and positions. */
//Return the range between two text positions.
//返回两个文本位置之间的范围。
- (nullable UITextRange *)textRangeFromPosition:(UITextPosition *)fromPosition toPosition:(UITextPosition *)toPosition;
//Returns the text position at a given offset from another text position.
//从另一个文本位置返回给定偏移量的文本位置。
- (nullable UITextPosition *)positionFromPosition:(UITextPosition *)position offset:(NSInteger)offset;
//Returns the text position at a given offset in a specified direction from another text position.
//从指定的方向返回给定偏移处的文本位置，从另一个文本位置。
- (nullable UITextPosition *)positionFromPosition:(UITextPosition *)position inDirection:(UITextLayoutDirection)direction offset:(NSInteger)offset;

/* Simple evaluation of positions */
//Return how one text position compares to another text position.
//返回一个文本位置与另一个文本位置的比较。
- (NSComparisonResult)comparePosition:(UITextPosition *)position toPosition:(UITextPosition *)other;
//Return the number of visible characters between one text position and another text position.
//返回一个文本位置和另一个文本位置之间的可见字符数。
- (NSInteger)offsetFromPosition:(UITextPosition *)from toPosition:(UITextPosition *)toPosition;

/* A system-provied input delegate is assigned when the system is interested in input changes. */
//An input delegate that is notified when text changes or when the selection changes.
/*当系统对输入更改感兴趣时，系统提供的输入委托是分配的。*/
//当文本更改或选择更改时通知的输入委托。
@property (nullable, nonatomic, weak) id <UITextInputDelegate> inputDelegate;

/* A tokenizer must be provided to inform the text input system about text units of varying granularity. */
//An input tokenizer that provides information about the granularity of text units. (read-only)
//输入标记器，提供有关文本单元的粒度的信息。 （只读）
@property (nonatomic, readonly) id <UITextInputTokenizer> tokenizer;

/* Layout questions. */
//Return the text position that is at the farthest extent in a given layout direction within a range of text.
//返回文本范围内给定布局方向上最远处的文本位置。
- (nullable UITextPosition *)positionWithinRange:(UITextRange *)range farthestInDirection:(UITextLayoutDirection)direction;
//Return a text range from a given text position to its farthest extent in a certain direction of layout.
//将文本范围从给定的文本位置返回到其最大范围内，在某个方向布局。
- (nullable UITextRange *)characterRangeByExtendingPosition:(UITextPosition *)position inDirection:(UITextLayoutDirection)direction;

/* Writing direction */
//Return the base writing direction for a position in the text going in a certain direction.
//返回文本中某个位置的基本写入方向。
- (UITextWritingDirection)baseWritingDirectionForPosition:(UITextPosition *)position inDirection:(UITextStorageDirection)direction;
//Set the base writing direction for a given range of text in a document.
//为文档中给定的文本范围设置基本写入方向。
- (void)setBaseWritingDirection:(UITextWritingDirection)writingDirection forRange:(UITextRange *)range;

/* Geometry used to provide, for example, a correction rect. */
//Return the first rectangle that encloses a range of text in a document.
//返回在文档中包含文本范围的第一个矩形。
- (CGRect)firstRectForRange:(UITextRange *)range;
//Return a rectangle used to draw the caret at a given insertion point.
//返回一个用于在给定插入点绘制插入符的矩形。
- (CGRect)caretRectForPosition:(UITextPosition *)position;
//Returns an array of selection rects corresponding to the range of text.
//返回与文本范围对应的选择符的数组。
- (NSArray *)selectionRectsForRange:(UITextRange *)range NS_AVAILABLE_IOS(6_0);       // Returns an array of UITextSelectionRects

/* Hit testing. */
//Return the position in a document that is closest to a specified point.
//返回最靠近指定点的文档中的位置。
- (nullable UITextPosition *)closestPositionToPoint:(CGPoint)point;
//Return the position in a document that is closest to a specified point in a given range.
//返回最接近给定范围内指定点的文档中的位置。
- (nullable UITextPosition *)closestPositionToPoint:(CGPoint)point withinRange:(UITextRange *)range;
//Return the character or range of characters that is at a given point in a document.
//返回文档中给定点的字符或字符范围。
- (nullable UITextRange *)characterRangeAtPoint:(CGPoint)point;

@optional

//Asks whether the text in the specified range should be replaced.
//询问是否应替换指定范围内的文本。
- (BOOL)shouldChangeTextInRange:(UITextRange *)range replacementText:(NSString *)text NS_AVAILABLE_IOS(6_0);   // return NO to not change text

/* Text styling information can affect, for example, the appearance of a correction rect.
 * Returns a dictionary containing NSAttributedString keys. */
//Return a dictionary with properties that specify how text is to be style at a certain location in a document.
/*文字样式信息可能会影响例如矫正的外观。
 *返回一个包含NSAttributedString键的字典。*/
//返回具有指定文档中某一位置的文本样式的属性的字典。
- (nullable NSDictionary<NSString *,id> *)textStylingAtPosition:(UITextPosition *)position inDirection:(UITextStorageDirection)direction;

/* To be implemented if there is not a one-to-one correspondence between text positions within range and character offsets into the associated string. */
//Return the position within a range of a document’s text that corresponds to the character offset from the start of that range.
/*要实现，如果在范围内的文本位置与字符偏移之间没有一对一对应关联的字符串。*/
//返回与该范围开头的字符偏移量相对应的文档文本范围内的位置。
- (nullable UITextPosition *)positionWithinRange:(UITextRange *)range atCharacterOffset:(NSInteger)offset;
//Return the character offset of a position in a document’s text that falls within a given range.
//返回文档文本中位于给定范围内的位置的字符偏移量。
- (NSInteger)characterOffsetOfPosition:(UITextPosition *)position withinRange:(UITextRange *)range;

/* An affiliated view that provides a coordinate system for all geometric values in this protocol.
 * If unimplmeented, the first view in the responder chain will be selected. */
//An affiliated view that provides a coordinate system for all geometric values in this protocol. (read-only)
/*附属视图，为本协议中的所有几何值提供坐标系。
 *如果不明确，将选择响应者链中的第一个视图。*/
//为该协议中的所有几何值提供坐标系的附属视图。 （只读）
@property (nonatomic, readonly) __kindof UIView *textInputView;

/* Selection affinity determines whether, for example, the insertion point appears after the last
 * character on a line or before the first character on the following line in cases where text
 * wraps across line boundaries. */
//The desired location for the insertion point.
/*选择关联确定例如插入点是否出现在最后一个之后
 *字符在一行或第一个字符之前的下一行在文本的情况下
 *包裹在线边界。*/
//插入点所需的位置。
@property (nonatomic) UITextStorageDirection selectionAffinity;

/* This is an optional method for clients that wish to support dictation phrase alternatives. If
 * they do not implement this method, dictation will just insert the most likely interpretation
 * of what was spoken via -insertText:.
 * dictationResult is an array of UIDictationPhrases. */
//Called when there is more than one interpretation of a spoken phrase in a dictation result.
/*这是希望支持口语短语替代方案的客户端的可选方法。 如果
 *他们不实行这种方法，口述只会插入最有可能的解释
 *通过-insertText：发表的内容。
 * dictationResult是一个UIDictationPhrases数组。*/
//在听写结果中对口头短语有不止一个解释时调用。
- (void)insertDictationResult:(NSArray<UIDictationPhrase *> *)dictationResult;

/* These are optional methods for clients that wish to know when there are pending dictation results. */
//Called when there is a pending dictation result.
//当有等待听写结果时调用。
- (void)dictationRecordingDidEnd;
//Called when dictation ended but recognition failed.
//当听写结束但被认可失败时，
- (void)dictationRecognitionFailed;

/* The following three optional methods are for clients that wish to support a placeholder for
 * pending dictation results. -insertDictationPlaceholder must return a reference to the
 * placeholder. This reference will be used to identify the placeholder by the other methods
 * (there may be more than one placeholder). */
#if UIKIT_DEFINE_AS_PROPERTIES
//Asks for the placeholder object to use while dictation results are being generated.
//要求占位符对象使用，而听写结果正在生成。
@property(nonatomic, readonly) id insertDictationResultPlaceholder;
#else
- (id)insertDictationResultPlaceholder;
#endif
//Asks for the rectangle in which to display the dictation placeholder animation.
//要求显示听写占位符动画的矩形。
- (CGRect)frameForDictationResultPlaceholder:(id)placeholder;
/* willInsertResult will be NO if the recognition failed. */
//Tells the view that the specified placeholder object is no longer needed.
/*如果识别失败，则willInsertResult将为NO。*/
//告诉视图，不再需要指定的占位符对象。
- (void)removeDictationResultPlaceholder:(id)placeholder willInsertResult:(BOOL)willInsertResult;

/* The following three optional methods are for clients that wish to display a floating cursor to
 * guide user manipulation of the selected text range via the system-provided keyboard. If a client
 * does not implement these methods, user feedback will be limited to the outcome after setting the
 * selected text range using positions resulting from hit testing. */
/*以下三种可选方法适用于希望显示浮动光标的客户端
 *通过系统提供的键盘指导用户对所选文本范围的操纵。 如果是客户端
 *没有实现这些方法，用户反馈将限制在设置后的结果
 *使用从命中测试产生的位置的所选文本范围。*/
- (void)beginFloatingCursorAtPoint:(CGPoint)point NS_AVAILABLE_IOS(9_0);
- (void)updateFloatingCursorAtPoint:(CGPoint)point NS_AVAILABLE_IOS(9_0);
- (void)endFloatingCursor NS_AVAILABLE_IOS(9_0);

@end

//---------------------------------------------------------------------------------------------------

/* UITextInput keys to style dictionaries are deprecated. Use NSAttributedString keys instead, such as NSFontAttribute, etc. */
UIKIT_EXTERN NSString *const UITextInputTextBackgroundColorKey NS_DEPRECATED_IOS(3_2, 8_0, "Use NSBackgroundColorAttributeName instead") __TVOS_PROHIBITED; // Key to a UIColor
UIKIT_EXTERN NSString *const UITextInputTextColorKey           NS_DEPRECATED_IOS(3_2, 8_0, "Use NSForegroundColorAttributeName instead") __TVOS_PROHIBITED; // Key to a UIColor
UIKIT_EXTERN NSString *const UITextInputTextFontKey            NS_DEPRECATED_IOS(3_2, 8_0, "Use NSFontAttributeName instead") __TVOS_PROHIBITED; // Key to a UIFont

/* To accommodate text entry in documents that contain nested elements, or in which supplying and
 * evaluating characters at indices is an expensive proposition, a position within a text input
 * document is represented as an object, not an integer.  UITextRange and UITextPosition are abstract
 * classes provided to be subclassed when adopting UITextInput */
NS_CLASS_AVAILABLE_IOS(3_2) @interface UITextPosition : NSObject

@end

NS_CLASS_AVAILABLE_IOS(3_2) @interface UITextRange : NSObject
//A Boolean value that indicates whether the range of text represented by the receiver is zero-length. (read-only)
//一个布尔值，指示接收者表示的文本范围是否为零长度。 （只读）
@property (nonatomic, readonly, getter=isEmpty) BOOL empty;     //  Whether the range is zero-length.
//The start of a range of text. (read-only)
@property (nonatomic, readonly) UITextPosition *start;
//The end of the range of text. (read-only)
@property (nonatomic, readonly) UITextPosition *end;

@end

/* UITextSelectionRect defines an annotated selection rect used by the system to
 * offer rich text interaction experience.  It also serves as an abstract class
 * provided to be subclassed when adopting UITextInput */
/* UITextSelectionRect定义了系统使用的注释选区
 *提供丰富的文字互动体验。 它也是抽象类
 *在采用UITextInput协议时提供子类化 */
NS_CLASS_AVAILABLE_IOS(6_0) @interface UITextSelectionRect : NSObject
//The rectangle that encloses the receiver’s text range. (read-only)
//包围接收者文本范围的矩形。 （只读）
@property (nonatomic, readonly) CGRect rect;
//The writing direction of text in the receiver’s text range. (read-only)
//接收者文本范围内文本的写入方向。 （只读）
@property (nonatomic, readonly) UITextWritingDirection writingDirection;
//A Boolean value indicating whether the rectangle contains the start of the selection. (read-only)
//一个布尔值，指示矩形是否包含选择的开始。 （只读）
@property (nonatomic, readonly) BOOL containsStart; // Returns YES if the rect contains the start of the selection.
//A Boolean value indicating whether the rectangle contains the end of the selection. (read-only)
//一个布尔值，指示矩形是否包含选择的结尾。 （只读）
@property (nonatomic, readonly) BOOL containsEnd; // Returns YES if the rect contains the end of the selection.
//A Boolean value indicating whether the text is oriented vertically. (read-only)
//一个布尔值，指示文本是否垂直定向。 （只读）
@property (nonatomic, readonly) BOOL isVertical; // Returns YES if the rect is for vertically oriented text.

@end

/* The input delegate must be notified of changes to the selection and text. */
/*必须通知输入委托对选择和文本的更改。*/
@protocol UITextInputDelegate <NSObject>
//Tells the input delegate when the selection is about to change in the document.
//当文档中的选择即将更改时，告诉输入委托。
- (void)selectionWillChange:(nullable id <UITextInput>)textInput;
//Tells the input delegate when the selection has changed in the document.
//当文档中的选择更改时，告诉输入委托。
- (void)selectionDidChange:(nullable id <UITextInput>)textInput;
//Tells the input delegate when text is about to change in the document.
//告诉输入委托文本中的文本即将更改。
- (void)textWillChange:(nullable id <UITextInput>)textInput;
//Tells the input delegate when text has changed in the document.
//当文档中的文本更改时，告诉输入委托。
- (void)textDidChange:(nullable id <UITextInput>)textInput;

@end


/* A tokenizer allows the text input system to evaluate text units of varying granularity. */
/*标记器允许文本输入系统评估不同粒度的文本单位。*/
@protocol UITextInputTokenizer <NSObject>

@required
//Return the range for the text enclosing a text position in a text unit of a given granularity in a given direction.s
//以指定方向返回给定粒度的文本单位中包含文本位置的文本的范围。
- (nullable UITextRange *)rangeEnclosingPosition:(UITextPosition *)position withGranularity:(UITextGranularity)granularity inDirection:(UITextDirection)direction;   // Returns range of the enclosing text unit of the given granularity, or nil if there is no such enclosing unit.  Whether a boundary position is enclosed depends on the given direction, using the same rule as isPosition:withinTextUnit:inDirection:
//Return whether a text position is at a boundary of a text unit of a specified granularity in a specified direction.
//返回文本位置是否处于指定方向上指定粒度的文本单位的边界。
- (BOOL)isPosition:(UITextPosition *)position atBoundary:(UITextGranularity)granularity inDirection:(UITextDirection)direction;                             // Returns YES only if a position is at a boundary of a text unit of the specified granularity in the particular direction.
//Return the next text position at a boundary of a text unit of the given granularity in a given direction.
//在给定方向的给定粒度的文本单位的边界返回下一个文本位置。
- (nullable UITextPosition *)positionFromPosition:(UITextPosition *)position toBoundary:(UITextGranularity)granularity inDirection:(UITextDirection)direction;   // Returns the next boundary position of a text unit of the given granularity in the given direction, or nil if there is no such position.
//Return whether a text position is within a text unit of a specified granularity in a specified direction.
//返回文本位置是否在指定方向上的指定粒度的文本单位内。
- (BOOL)isPosition:(UITextPosition *)position withinTextUnit:(UITextGranularity)granularity inDirection:(UITextDirection)direction;                         // Returns YES if position is within a text unit of the given granularity.  If the position is at a boundary, returns YES only if the boundary is part of the text unit in the given direction.

@end


/* A recommended base implementation of the tokenizer protocol. Subclasses are responsible
 * for handling directions and granularities affected by layout.*/
/*推荐的基本实现的tokenizer协议。 子类负责
  *用于处理受布局影响的方向和粒度*/
NS_CLASS_AVAILABLE_IOS(3_2) @interface UITextInputStringTokenizer : NSObject <UITextInputTokenizer>
//Returns an object initialized with the document object that directly communicates with the text input system.
//返回使用与文本输入系统直接通信的文档对象初始化的对象。
- (instancetype)initWithTextInput:(UIResponder <UITextInput> *)textInput;

@end

/* The UITextInputMode class should not be subclassed. It is to allow other in-app functionality to adapt
 * based on the keyboard language. Different UITextInputMode objects may have the same primaryLanguage. */
/* UITextInputMode类不应该被子类化。 它允许其他应用程序内功能适应
  *基于键盘语言。 不同的UITextInputMode对象可能具有相同的主语言。*/
NS_CLASS_AVAILABLE_IOS(4_2) @interface UITextInputMode : NSObject <NSSecureCoding>
//输入模式的主要语言（如果有）。 BCP 47语言标识符，如en-US
@property (nullable, nonatomic, readonly, strong) NSString *primaryLanguage; // The primary language, if any, of the input mode.  A BCP 47 language identifier such as en-US

// To query the UITextInputMode, refer to the UIResponder method -textInputMode.
//要查询UITextInputMode，请参阅UIResponder方法-textInputMode。
+ (nullable UITextInputMode *)currentInputMode NS_DEPRECATED_IOS(4_2, 7_0)  __TVOS_PROHIBITED; // The current input mode.  Nil if unset.
#if UIKIT_DEFINE_AS_PROPERTIES
//Returns the active text-input modes.
@property(class, nonatomic, readonly) NSArray<UITextInputMode *> *activeInputModes; // The active input modes.
#else
+ (NSArray<UITextInputMode *> *)activeInputModes; // The active input modes.
#endif

@end
/*
 UITextInputMode大家看了是不是有些陌生呢？这个类是在4.2之后才有的一个新的类，是用来获取当前文本输入模式的。这个可能说的有些模糊。说白了就是在用户输入文本时，判断用户使用的是什么键盘的。
 其实用法很简单哦。
 如果要在用户改变输入方式时，获得此值，可如此使用：
 首先在用户开始输入之前注册通知：
 [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(changeMode:) name:@"UITextInputCurrentInputModeDidChangeNotification" object:nil];
 然后实现上面的方法：
 -(void) changeMode:(NSNotification *)notification{
 NSLog(@"%@",[[UITextInputMode currentInputMode] primaryLanguage]);
 }
 
 我们当前只能拿到用户以何种语言输入。不过对于当前的大部分应用来说，这个已经足够了。
 直接获取方式：
 
 [[UITextInputMode currentInputMode] primaryLanguage];
 */
UIKIT_EXTERN NSNotificationName const UITextInputCurrentInputModeDidChangeNotification NS_AVAILABLE_IOS(4_2);

NS_ASSUME_NONNULL_END
