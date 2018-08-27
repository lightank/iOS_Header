//
//  UITableViewCell.h
//  UIKit
//
//  Copyright (c) 2005-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIGestureRecognizer.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage, UIColor, UILabel, UIImageView, UIButton, UITextField, UITableView, UILongPressGestureRecognizer;

typedef NS_ENUM(NSInteger, UITableViewCellStyle) {
    // 左侧显示textLabel（不显示detailTextLabel），imageView可选（显示在最左边）
    UITableViewCellStyleDefault,	// Simple cell with text label and optional image view (behavior of UITableViewCell in iPhoneOS 2.x)
    // 左侧显示textLabel、右侧显示detailTextLabel（默认蓝色），imageView可选（显示在最左边）
    UITableViewCellStyleValue1,		// Left aligned label on left and right aligned label on right with blue text (Used in Settings)
    // 左侧依次显示textLabel(默认蓝色)和detailTextLabel，imageView可选（显示在最左边）
    UITableViewCellStyleValue2,		// Right aligned label on left with blue text and left aligned label on right (Used in Phone/Contacts)
    // 左上方显示textLabel，左下方显示detailTextLabel（默认灰色）,imageView可选（显示在最左边）
    UITableViewCellStyleSubtitle	// Left aligned label on top and left aligned label on bottom with gray text (Used in iPod).
};             // available in iPhone OS 3.0

//分割线类型
typedef NS_ENUM(NSInteger, UITableViewCellSeparatorStyle) {
    // 没有分割线
    UITableViewCellSeparatorStyleNone,
    // 单线，默认
    UITableViewCellSeparatorStyleSingleLine,
    // 内嵌线，只有在 UITableView 为 group 类型时才起作用
    UITableViewCellSeparatorStyleSingleLineEtched   // This separator style is only supported for grouped style table views currently
} __TVOS_PROHIBITED;

//cell选择样式
typedef NS_ENUM(NSInteger, UITableViewCellSelectionStyle) {
    //无色
    UITableViewCellSelectionStyleNone,
    //蓝色
    UITableViewCellSelectionStyleBlue,
    //灰色
    UITableViewCellSelectionStyleGray,
    //默认值
    UITableViewCellSelectionStyleDefault NS_ENUM_AVAILABLE_IOS(7_0)
};

//cell focus 样式
typedef NS_ENUM(NSInteger, UITableViewCellFocusStyle) {
    //无
    UITableViewCellFocusStyleDefault,
    //自定义
    UITableViewCellFocusStyleCustom
} NS_ENUM_AVAILABLE_IOS(9_0);

//cell 编辑样式
typedef NS_ENUM(NSInteger, UITableViewCellEditingStyle) {
    //无
    UITableViewCellEditingStyleNone,
    //删除
    UITableViewCellEditingStyleDelete,
    //插入
    UITableViewCellEditingStyleInsert
};

//The type of standard accessory control used by a cell.
//cell使用的标准附件控制的类型
typedef NS_ENUM(NSInteger, UITableViewCellAccessoryType) {
    //The cell does not have any accessory view. This is the default value.
    //单元格没有任何附件视图。 这是默认值。
    UITableViewCellAccessoryNone,                                                      // don't show any accessory view
    //The cell has an accessory control shaped like a chevron. This control indicates that tapping the cell triggers a push action. The control does not track touches.
    //cell具有形状像人字形的附件控制。 该控件表示点击单元触发推动动作。 控件不跟踪触摸。
    UITableViewCellAccessoryDisclosureIndicator,                                       // regular chevron. doesn't track
    //The cell has an info button and a chevron image as content. This control indicates that tapping the cell allows the user to configure the cell’s contents. The control tracks touches.
    //该单元格具有信息按钮和V形图像作为内容。 此控件表示点击单元格允许用户配置单元格的内容。 控制轨迹接触。
    UITableViewCellAccessoryDetailDisclosureButton __TVOS_PROHIBITED,                 // info button w/ chevron. tracks
    //The cell has a check mark on its right side. This control does not track touches. The delegate of the table view can manage check marks in a section of rows (possibly limiting the check mark to one row of the section) in its tableView:didSelectRowAtIndexPath: method.
    //单元格右侧有一个复选标记。 此控件不跟踪触摸。 表视图的委托可以在其tableView：didSelectRowAtIndexPath：方法中管理一部分行中的复选标记（可能将该复选标记限制为该行的一行）。
    UITableViewCellAccessoryCheckmark,                                                 // checkmark. doesn't track
    //The cell has an info button without a chevron. This control indicates that tapping the cell displays additional information about the cell’s contents. The control tracks touches.
    //cell有一个没有V形的信息按钮。 此控件表示点击单元格会显示有关单元格内容的其他信息。 控制轨迹接触。
    UITableViewCellAccessoryDetailButton NS_ENUM_AVAILABLE_IOS(7_0)  __TVOS_PROHIBITED // info button. tracks
};

//Constants used to determine the new state of a cell as it transitions between states.
//常量，用于在状态之间转换时确定单元格的新状态。
typedef NS_OPTIONS(NSUInteger, UITableViewCellStateMask) {
    //The normal state of a table cell.
    //正常状态下的table cell
    UITableViewCellStateDefaultMask                     = 0,
    //The state of a table view cell when the table view is in editing mode.
    //当表视图处于编辑模式时，表视图单元格的状态。
    UITableViewCellStateShowingEditControlMask          = 1 << 0,
    //The state of a table view cell that shows a button requesting confirmation of a delete gesture.
    //表格视图单元格的状态，显示一个请求确认删除手势的按钮。
    UITableViewCellStateShowingDeleteConfirmationMask   = 1 << 1
};

#define UITableViewCellStateEditingMask UITableViewCellStateShowingEditControlMask

NS_CLASS_AVAILABLE_IOS(2_0) @interface UITableViewCell : UIView <NSCoding, UIGestureRecognizerDelegate>

// Designated initializer.  If the cell can be reused, you must pass in a reuse identifier.  You should use the same reuse identifier for all cells of the same form.
//指定的初始化程序 如果单元格可以重复使用，则必须通过重用标识符。 您应该对相同形式的所有单元格使用相同的重用标识符。
- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(nullable NSString *)reuseIdentifier NS_AVAILABLE_IOS(3_0) NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

// Content.  These properties provide direct access to the internal label and image views used by the table view cell.  These should be used instead of the content properties below.
//内容 这些属性提供对表视图单元格使用的内部标签和图像视图的直接访问。 应使用这些代替下面的内容属性。默认是空,如果有必要,将会创建
@property (nonatomic, readonly, strong, nullable) UIImageView *imageView NS_AVAILABLE_IOS(3_0);   // default is nil.  image view will be created if necessary.

@property (nonatomic, readonly, strong, nullable) UILabel *textLabel NS_AVAILABLE_IOS(3_0);   // default is nil.  label will be created if necessary.
@property (nonatomic, readonly, strong, nullable) UILabel *detailTextLabel NS_AVAILABLE_IOS(3_0); // default is nil.  label will be created if necessary (and the current style supports a detail label).

// If you want to customize cells by simply adding additional views, you should add them to the content view so they will be positioned appropriately as the cell transitions into and out of editing mode.
//如果要通过简单添加其他视图来自定义单元格，则应将它们添加到内容视图中，以便在单元格转换和退出编辑模式时，将其适当地定位。
@property (nonatomic, readonly, strong) UIView *contentView;

// Default is nil for cells in UITableViewStylePlain, and non-nil for UITableViewStyleGrouped. The 'backgroundView' will be added as a subview behind all other views.
// UITableViewStylePlain中的单元格的默认值为nil，UITableViewStyleGrouped的默认值为nil。 'backgroundView'将作为所有其他视图背后的子视图添加。
@property (nonatomic, strong, nullable) UIView *backgroundView;

// Default is nil for cells in UITableViewStylePlain, and non-nil for UITableViewStyleGrouped. The 'selectedBackgroundView' will be added as a subview directly above the backgroundView if not nil, or behind all other views. It is added as a subview only when the cell is selected. Calling -setSelected:animated: will cause the 'selectedBackgroundView' to animate in and out with an alpha fade.
// UITableViewStylePlain中的cell的默认值为nil，UITableViewStyleGrouped的默认值为非空。 “selectedBackgroundView”将作为直接在backgroundView上方的子视图添加，如果不是nil，或者在所有其他视图后面。 仅当选择单元格时才将其添加为子视图。 Calling -setSelected：动画：将使“selectedBackgroundView”通过Alpha淡入淡出进行动画化。
@property (nonatomic, strong, nullable) UIView *selectedBackgroundView;

// If not nil, takes the place of the selectedBackgroundView when using multiple selection.
//如果不是nil，则在使用多个选择时取代selectedBackgroundView。
@property (nonatomic, strong, nullable) UIView *multipleSelectionBackgroundView NS_AVAILABLE_IOS(5_0);

//A string used to identify a cell that is reusable. (read-only)
// 用于标识可重用的单元格的字符串。 （只读）
@property (nonatomic, readonly, copy, nullable) NSString *reuseIdentifier;
//Called when the view is removed from the reuse queue.
//如果单元格是可重用的（具有重用标识符），则在从表视图方法dequeueReusableCellWithIdentifier：返回单元格之前调用它。 如果你重写，你必须调用super。
- (void)prepareForReuse;                                                        // if the cell is reusable (has a reuse identifier), this is called just before the cell is returned from the table view method dequeueReusableCellWithIdentifier:.  If you override, you MUST call super.
//cell选中的样式,默认值是:UITableViewCellSelectionStyleBlue
@property (nonatomic) UITableViewCellSelectionStyle   selectionStyle;             // default is UITableViewCellSelectionStyleBlue.
//设置选择的状态（标题，图像，背景）。 默认为NO。 动画是NO
@property (nonatomic, getter=isSelected) BOOL         selected;                   // set selected state (title, image, background). default is NO. animated is NO
//设置突出显示的状态（标题，图像，背景）。 默认为NO。 动画是NO
@property (nonatomic, getter=isHighlighted) BOOL      highlighted;                // set highlighted state (title, image, background). default is NO. animated is NO
//设定常规和选定状态之间的动画
- (void)setSelected:(BOOL)selected animated:(BOOL)animated;                     // animate between regular and selected state
- (void)setHighlighted:(BOOL)highlighted animated:(BOOL)animated;               // animate between regular and highlighted state

//默认为UITableViewCellEditingStyleNone。 这是由UITableView使用委托的值为相应地自定义其外观的单元格设置的。
@property (nonatomic, readonly) UITableViewCellEditingStyle editingStyle;         // default is UITableViewCellEditingStyleNone. This is set by UITableView using the delegate's value for cells who customize their appearance accordingly.
//A Boolean value that determines whether the cell shows the reordering control.
//The reordering control is gray, multiple horizontal bar control on the right side of the cell. Users can drag this control to reorder the cell within the table. The default value is NO. If the value is YES , the reordering control temporarily replaces any accessory view.
//For the reordering control to appear, you must not only set this property but implement the UITableViewDataSource method tableView:moveRowAtIndexPath:toIndexPath:. In addition, if the data source implements tableView:canMoveRowAtIndexPath: to return NO, the reordering control does not appear in that designated row.
//重排序控件为灰色，单元格右侧为多个水平条控制。 用户可以拖动该控件来重新排列表格中的单元格。 默认值为NO。 如果值为YES，则重新排序控件临时替换任何附件视图。
//要重新排序控件出现，您不仅要设置此属性，还要实现UITableViewDataSource方法tableView：moveRowAtIndexPath：toIndexPath :. 另外，如果数据源实现了tableView：canMoveRowAtIndexPath：返回NO，则重新排序控件不会出现在该指定行中。
@property (nonatomic) BOOL                            showsReorderControl;        // default is NO
//A Boolean value that controls whether the cell background is indented when the table view is in editing mode.
//一个布尔值，用于控制表视图处于编辑模式时，单元格背景是否缩进。
@property (nonatomic) BOOL                            shouldIndentWhileEditing;   // default is YES.  This is unrelated to the indentation level below.

//The type of standard accessory view the cell should use (normal state).
//电池应使用的标准配件的类型（正常状态）。
@property (nonatomic) UITableViewCellAccessoryType    accessoryType;              // default is UITableViewCellAccessoryNone. use to set standard type
//A view that is used, typically as a control, on the right side of the cell (normal state).
//通常用作控件的视图，位于单元格的右侧（正常状态）。
@property (nonatomic, strong, nullable) UIView       *accessoryView;              // if set, use custom view. ignore accessoryType. tracks if enabled can calls accessory action
//The type of standard accessory view the cell should use in the table view’s editing state.
//在表视图的编辑状态下，单元格应使用的标准附件的类型。
@property (nonatomic) UITableViewCellAccessoryType    editingAccessoryType;       // default is UITableViewCellAccessoryNone. use to set standard type
@property (nonatomic, strong, nullable) UIView       *editingAccessoryView;       // if set, use custom view. ignore editingAccessoryType. tracks if enabled can calls accessory action

//The indentation level of the cell’s content.
//单元格内容的缩进级别。
//The default value of the property is zero (no indentation). Assigning a positive value to this property indents the cell’s content from the left edge of the cell separator. The amount of indentation is equal to the indentation level multiplied by the value in the indentationWidth property.
//属性的默认值为零（不缩进）。 为此属性分配正值将从单元格分隔符的左边缘缩小单元格的内容。 缩进量等于缩进级乘以indentationWidth属性中的值。
@property (nonatomic) NSInteger                       indentationLevel;           // adjust content indent. default is 0
//The width for each level of indentation of a cell's content.
//每个级别的缩进级别的宽度“的内容。
@property (nonatomic) CGFloat                         indentationWidth;           // width for each level. default is 10.0
/*
 让分割线全屏:在cellForRowAtIndexPath方法中对cell
 cell.layoutMargins = UIEdgeInsetsZero;
 cell.separatorInset = UIEdgeInsetsZero;
 */
//Specifies the default inset of cell separators.
//指定单元格分隔符的默认插入。
@property (nonatomic) UIEdgeInsets                    separatorInset NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED; // allows customization of the separator frame

//A Boolean value that indicates whether the cell is in an editable state.
//一个布尔值，指示单元格是否处于可编辑状态。
@property (nonatomic, getter=isEditing) BOOL          editing;                    // show appropriate edit controls (+/- & reorder). By default -setEditing: calls setEditing:animated: with NO for animated.
- (void)setEditing:(BOOL)editing animated:(BOOL)animated;

//Returns whether the cell is currently showing the delete-confirmation button. (read-only)
//一个布尔值，指示单元格是否处于可编辑状态。
@property(nonatomic, readonly) BOOL                   showingDeleteConfirmation;  // currently showing "Delete" button

//The appearance of the cell when focused.
//聚焦时cell的外观类型。
@property (nonatomic) UITableViewCellFocusStyle       focusStyle NS_AVAILABLE_IOS(9_0) UI_APPEARANCE_SELECTOR;

// These methods can be used by subclasses to animate additional changes to the cell when the cell is changing state
// Note that when the cell is swiped, the cell will be transitioned into the UITableViewCellStateShowingDeleteConfirmationMask state,
// but the UITableViewCellStateShowingEditControlMask will not be set.
//这些方法可以被子类用于在单元格状态更改时为单元格添加更多的更改
//请注意，当单元格被刷新时，单元格将被转换为UITableViewCellStateShowingDeleteConfirmationMask状态，
//但不会设置UITableViewCellStateShowingEditControlMask。
- (void)willTransitionToState:(UITableViewCellStateMask)state NS_AVAILABLE_IOS(3_0);
- (void)didTransitionToState:(UITableViewCellStateMask)state NS_AVAILABLE_IOS(3_0);

@end

@interface UITableViewCell (UIDeprecated)

// Frame is ignored.  The size will be specified by the table view width and row height.
- (id)initWithFrame:(CGRect)frame reuseIdentifier:(nullable NSString *)reuseIdentifier NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;

// Content properties.  These properties were deprecated in iPhone OS 3.0.  The textLabel and imageView properties above should be used instead.
// For selected attributes, set the highlighted attributes on the textLabel and imageView.
@property (nonatomic, copy, nullable)   NSString *text NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                        // default is nil
@property (nonatomic, strong, nullable) UIFont   *font NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                        // default is nil (Use default font)
@property (nonatomic) NSTextAlignment   textAlignment NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;               // default is UITextAlignmentLeft
@property (nonatomic) NSLineBreakMode   lineBreakMode NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;               // default is UILineBreakModeTailTruncation
@property (nonatomic, strong, nullable) UIColor  *textColor NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                   // default is nil (text draws black)
@property (nonatomic, strong, nullable) UIColor  *selectedTextColor NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;           // default is nil (text draws white)

@property (nonatomic, strong, nullable) UIImage  *image NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                       // default is nil. appears on left next to title.
@property (nonatomic, strong, nullable) UIImage  *selectedImage NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;               // default is nil

// Use the new editingAccessoryType and editingAccessoryView instead
@property (nonatomic) BOOL              hidesAccessoryWhenEditing NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;   // default is YES

// Use the table view data source method -tableView:commitEditingStyle:forRowAtIndexPath: or the table view delegate method -tableView:accessoryButtonTappedForRowWithIndexPath: instead
@property (nonatomic, assign, nullable) id        target NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                      // target for insert/delete/accessory clicks. default is nil (i.e. go up responder chain). weak reference
@property (nonatomic, nullable) SEL               editAction NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;                  // action to call on insert/delete call. set by UITableView
@property (nonatomic, nullable) SEL               accessoryAction NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;             // action to call on accessory view clicked. set by UITableView

@end

NS_ASSUME_NONNULL_END
