//
//  UITableView.h
//  UIKit
//
//  Copyright (c) 2005-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIScrollView.h>
#import <UIKit/UISwipeGestureRecognizer.h>
#import <UIKit/UITableViewCell.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UITableViewStyle) {
    //普通类型
    UITableViewStylePlain,          // regular table view
    //分组类型
    UITableViewStyleGrouped         // preferences style table view
};

typedef NS_ENUM(NSInteger, UITableViewScrollPosition) {
    //The table view scrolls the row of interest to be fully visible with a minimum of movement. If the row is already fully visible, no scrolling occurs. For example, if the row is above the visible area, the behavior is identical to that specified by UITableViewScrollPositionTop. This is the default.
    //效果同UITableViewScrollPositionTop
    UITableViewScrollPositionNone,
    //定位完成后，将定位的行尽量显示在tableView的顶部
    UITableViewScrollPositionTop,
    //定位完成后，将定位的行尽量显示在tableView的中间
    UITableViewScrollPositionMiddle,
    //定位完成后，将定位的行尽量显示在tableView的最下面
    UITableViewScrollPositionBottom
};                // scroll so row of interest is completely visible at top/center/bottom of view

typedef NS_ENUM(NSInteger, UITableViewRowAnimation) {
    //淡入淡出
    UITableViewRowAnimationFade,
    //从右滑入
    UITableViewRowAnimationRight,           // slide in from right (or out to right)
    //从左滑入
    UITableViewRowAnimationLeft,
    //从上滑入
    UITableViewRowAnimationTop,
    //从下滑入
    UITableViewRowAnimationBottom,
    //没有动画
    UITableViewRowAnimationNone,            // available in iOS 3.0
    UITableViewRowAnimationMiddle,          // available in iOS 3.2.  attempts to keep cell centered in the space it will/did occupy
    //自动选择合适的动画
    UITableViewRowAnimationAutomatic = 100  // available in iOS 5.0.  chooses an appropriate animation style for you
};

// Including this constant string in the array of strings returned by sectionIndexTitlesForTableView: will cause a magnifying glass icon to be displayed at that location in the index.
// This should generally only be used as the first title in the index.
UIKIT_EXTERN NSString *const UITableViewIndexSearch NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;

// Returning this value from tableView:heightForHeaderInSection: or tableView:heightForFooterInSection: results in a height that fits the value returned from
// tableView:titleForHeaderInSection: or tableView:titleForFooterInSection: if the title is not nil.
UIKIT_EXTERN const CGFloat UITableViewAutomaticDimension NS_AVAILABLE_IOS(5_0);

@class UITableView;
@class UINib;
@protocol UITableViewDataSource;
@protocol UITableViewDataSourcePrefetching;
@class UILongPressGestureRecognizer;
@class UITableViewHeaderFooterView;
@class UIRefreshControl;
@class UIVisualEffect;

typedef NS_ENUM(NSInteger, UITableViewRowActionStyle) {
    UITableViewRowActionStyleDefault = 0,
    UITableViewRowActionStyleDestructive = UITableViewRowActionStyleDefault,
    UITableViewRowActionStyleNormal
} NS_ENUM_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED;

NS_CLASS_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED @interface UITableViewRowAction : NSObject <NSCopying>

+ (instancetype)rowActionWithStyle:(UITableViewRowActionStyle)style title:(nullable NSString *)title handler:(void (^)(UITableViewRowAction *action, NSIndexPath *indexPath))handler;

@property (nonatomic, readonly) UITableViewRowActionStyle style;
@property (nonatomic, copy, nullable) NSString *title;
@property (nonatomic, copy, nullable) UIColor *backgroundColor; // default background color is dependent on style
@property (nonatomic, copy, nullable) UIVisualEffect* backgroundEffect;

@end

NS_CLASS_AVAILABLE_IOS(9_0) @interface UITableViewFocusUpdateContext : UIFocusUpdateContext

@property (nonatomic, strong, readonly, nullable) NSIndexPath *previouslyFocusedIndexPath;
@property (nonatomic, strong, readonly, nullable) NSIndexPath *nextFocusedIndexPath;

@end

//_______________________________________________________________________________________________________________
// this represents the display and behaviour of the cells.

@protocol UITableViewDelegate<NSObject, UIScrollViewDelegate>

@optional

// Display customization
//即将显示indexPath处的cell时触发
- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath;
//即将显示section处的Header时触发
- (void)tableView:(UITableView *)tableView willDisplayHeaderView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);
//即将显示section处的Footer时触发
- (void)tableView:(UITableView *)tableView willDisplayFooterView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);
//结束显示indexPath处的cell时触发
- (void)tableView:(UITableView *)tableView didEndDisplayingCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath*)indexPath NS_AVAILABLE_IOS(6_0);
//结束显示section处的Header时触发
- (void)tableView:(UITableView *)tableView didEndDisplayingHeaderView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);
//结束显示section处的Footer时触发
- (void)tableView:(UITableView *)tableView didEndDisplayingFooterView:(UIView *)view forSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);

// Variable height support
//该方法返回值决定指定indexPath对应的row的高度
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;
//该方法返回值决定指定isection对应的Header的高度
- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section;
//该方法返回值决定指定section对应的Footer的高度
- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section;

// Use the estimatedHeight methods to quickly calcuate guessed values which will allow for fast load times of the table.
// If these methods are implemented, the above -tableView:heightForXXX calls will be deferred until views are ready to be displayed, so more expensive logic can be placed there.
//设置一个行高的估计值(默认为0，表示没有估计,7.0之后可用)
//注意：这个属性官方的解释是如果你的tableView的行高是可变的，那么设计一个估计高度可以加快代码的运行效率。
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(7_0);
//下面这两个属性和上面相似，分别设置分区头视图和尾视图的估计高度(7.0之后可用)
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForHeaderInSection:(NSInteger)section NS_AVAILABLE_IOS(7_0);
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForFooterInSection:(NSInteger)section NS_AVAILABLE_IOS(7_0);

// Section header & footer information. Views are preferred over title should you decide to provide both
//该方法返回值决定指定isection对应的Header视图
- (nullable UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section;   // custom view for header. will be adjusted to default or specified header height
//该方法返回值决定指定section对应的Footer视图
- (nullable UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section;   // custom view for footer. will be adjusted to default or specified footer height

// Accessories (disclosures).
//已弃用
- (UITableViewCellAccessoryType)tableView:(UITableView *)tableView accessoryTypeForRowWithIndexPath:(NSIndexPath *)indexPath NS_DEPRECATED_IOS(2_0, 3_0) __TVOS_PROHIBITED;
//accessoryButton的点击事件
- (void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath;

// Selection

// -tableView:shouldHighlightRowAtIndexPath: is called when a touch comes down on a row.
// Returning NO to that message halts the selection process and does not cause the currently selected row to lose its selected look while the touch is down.
// Cell高亮的回调，一般式在选择的时候才高亮
- (BOOL)tableView:(UITableView *)tableView shouldHighlightRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(6_0);
- (void)tableView:(UITableView *)tableView didHighlightRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(6_0);
- (void)tableView:(UITableView *)tableView didUnhighlightRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(6_0);

// Called before the user changes the selection. Return a new indexPath, or nil, to change the proposed selection.
// Cell选中和取消选择的回调
- (nullable NSIndexPath *)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath;
- (nullable NSIndexPath *)tableView:(UITableView *)tableView willDeselectRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(3_0);
// Called after the user changes the selection.
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;
- (void)tableView:(UITableView *)tableView didDeselectRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(3_0);

// Editing

// Allows customization of the editingStyle for a particular cell located at 'indexPath'. If not implemented, all editable cells will have UITableViewCellEditingStyleDelete set for them when the table has editing property set to YES.
//该方法返回值决定了 indexPath处的cell的编辑状态  返回值为枚举类型 分别为 None Delete Insert
- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath;
//删除按钮上的文字
- (nullable NSString *)tableView:(UITableView *)tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;
//返回一个UITableViewRowAction数组，每一个"Action"代表一个侧滑删除的Button。这样侧滑每一行Cell可以有更多按钮提供给用户交互。
- (nullable NSArray<UITableViewRowAction *> *)tableView:(UITableView *)tableView editActionsForRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED; // supercedes -tableView:titleForDeleteConfirmationButtonForRowAtIndexPath: if return value is non-nil

// Controls whether the background is indented while editing.  If not implemented, the default is YES.  This is unrelated to the indentation level below.  This method only applies to grouped style table views.
//该方法决定了 cell处于被编辑状态时是否应该缩进 若未重写 所有cell处于编辑状态时都会缩进
- (BOOL)tableView:(UITableView *)tableView shouldIndentWhileEditingRowAtIndexPath:(NSIndexPath *)indexPath;

// The willBegin/didEnd methods are called whenever the 'editing' property is automatically changed by the table (allowing insert/delete/move). This is done by a swipe activating a single row
- (void)tableView:(UITableView *)tableView willBeginEditingRowAtIndexPath:(NSIndexPath *)indexPath __TVOS_PROHIBITED;
- (void)tableView:(UITableView *)tableView didEndEditingRowAtIndexPath:(nullable NSIndexPath *)indexPath __TVOS_PROHIBITED;

// Moving/reordering

// Allows customization of the target row for a particular row as it is being moved/reordered
- (NSIndexPath *)tableView:(UITableView *)tableView targetIndexPathForMoveFromRowAtIndexPath:(NSIndexPath *)sourceIndexPath toProposedIndexPath:(NSIndexPath *)proposedDestinationIndexPath;

// Indentation

- (NSInteger)tableView:(UITableView *)tableView indentationLevelForRowAtIndexPath:(NSIndexPath *)indexPath; // return 'depth' of row for hierarchies

// Copy/Paste.  All three methods must be implemented by the delegate.

- (BOOL)tableView:(UITableView *)tableView shouldShowMenuForRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(5_0);
- (BOOL)tableView:(UITableView *)tableView canPerformAction:(SEL)action forRowAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender NS_AVAILABLE_IOS(5_0);
- (void)tableView:(UITableView *)tableView performAction:(SEL)action forRowAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender NS_AVAILABLE_IOS(5_0);

// Focus

- (BOOL)tableView:(UITableView *)tableView canFocusRowAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0);
- (BOOL)tableView:(UITableView *)tableView shouldUpdateFocusInContext:(UITableViewFocusUpdateContext *)context NS_AVAILABLE_IOS(9_0);
- (void)tableView:(UITableView *)tableView didUpdateFocusInContext:(UITableViewFocusUpdateContext *)context withAnimationCoordinator:(UIFocusAnimationCoordinator *)coordinator NS_AVAILABLE_IOS(9_0);
- (nullable NSIndexPath *)indexPathForPreferredFocusedViewInTableView:(UITableView *)tableView NS_AVAILABLE_IOS(9_0);

@end

UIKIT_EXTERN NSNotificationName const UITableViewSelectionDidChangeNotification;


//_______________________________________________________________________________________________________________

NS_CLASS_AVAILABLE_IOS(2_0) @interface UITableView : UIScrollView <NSCoding>
//UITableView创建，创建的时候必须指明style（默认UITableViewStylePlain）
- (instancetype)initWithFrame:(CGRect)frame style:(UITableViewStyle)style NS_DESIGNATED_INITIALIZER; // must specify style at creation. -initWithFrame: calls this with UITableViewStylePlain
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
//UITableView风格(只读)
@property (nonatomic, readonly) UITableViewStyle style;
//UITableView数据源
@property (nonatomic, weak, nullable) id <UITableViewDataSource> dataSource;
//UITableView代理
@property (nonatomic, weak, nullable) id <UITableViewDelegate> delegate;
@property (nonatomic, weak) id<UITableViewDataSourcePrefetching> prefetchDataSource NS_AVAILABLE_IOS(10_0);
//设置表视图cell的高度，统一的高度默认44px
@property (nonatomic) CGFloat rowHeight;             // will return the default value if unset
//设置UITableView种section的头部的高度
@property (nonatomic) CGFloat sectionHeaderHeight;   // will return the default value if unset
//设置UITableView种section的尾部的高度
@property (nonatomic) CGFloat sectionFooterHeight;   // will return the default value if unset
//设置一个行高的估计值(默认为0，表示没有估计,7.0之后可用)
//注意：这个属性官方的解释是如果你的tableView的行高是可变的，那么设计一个估计高度可以加快代码的运行效率。
@property (nonatomic) CGFloat estimatedRowHeight NS_AVAILABLE_IOS(7_0); // default is 0, which means there is no estimate
//下面这两个属性和上面相似，分别设置分区头视图和尾视图的估计高度(7.0之后可用)
@property (nonatomic) CGFloat estimatedSectionHeaderHeight NS_AVAILABLE_IOS(7_0); // default is 0, which means there is no estimate
@property (nonatomic) CGFloat estimatedSectionFooterHeight NS_AVAILABLE_IOS(7_0); // default is 0, which means there is no estimate
//设置分割线的位置
@property (nonatomic) UIEdgeInsets separatorInset NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR; // allows customization of the frame of cell separators
//设置UITableView的背景
@property (nonatomic, strong, nullable) UIView *backgroundView NS_AVAILABLE_IOS(3_2); // the background view will be automatically resized to track the size of the table view.  this will be placed as a subview of the table view behind all cells and headers/footers.  default may be non-nil for some devices.

// Data
//刷新整个tableView
- (void)reloadData; // reloads everything from scratch. redisplays visible rows. because we only keep info about visible rows, this is cheap. will adjust offset if table shrinks
//重载索引栏
- (void)reloadSectionIndexTitles NS_AVAILABLE_IOS(3_0);   // reloads the index bar.

// Info

@property (nonatomic, readonly) NSInteger numberOfSections;
//每个分区section有多少行
- (NSInteger)numberOfRowsInSection:(NSInteger)section;
//获取分区的大小(包括头视图，所有行和尾视图)
- (CGRect)rectForSection:(NSInteger)section;                                    // includes header, footer and all rows
//根据分区分别获取头视图，尾视图和行的高度
- (CGRect)rectForHeaderInSection:(NSInteger)section;
- (CGRect)rectForFooterInSection:(NSInteger)section;
- (CGRect)rectForRowAtIndexPath:(NSIndexPath *)indexPath;
//获取某个点在tableView中的位置信息
- (nullable NSIndexPath *)indexPathForRowAtPoint:(CGPoint)point;                         // returns nil if point is outside of any row in the table
//获取某个cell在tableView中的位置信息
- (nullable NSIndexPath *)indexPathForCell:(UITableViewCell *)cell;                      // returns nil if cell is not visible
//根据一个矩形范围返回一个信息数组，数组中是每一行row的位置信息
- (nullable NSArray<NSIndexPath *> *)indexPathsForRowsInRect:(CGRect)rect;                              // returns nil if rect not valid
//通过位置路径获取cell
- (nullable __kindof UITableViewCell *)cellForRowAtIndexPath:(NSIndexPath *)indexPath;   // returns nil if cell is not visible or index path is out of range
//获取所有可见的cell
@property (nonatomic, readonly) NSArray<__kindof UITableViewCell *> *visibleCells;
//获取所有可见行的位置信息
@property (nonatomic, readonly, nullable) NSArray<NSIndexPath *> *indexPathsForVisibleRows;
//根据分区获取头视图
- (nullable UITableViewHeaderFooterView *)headerViewForSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);
//根据分区获取尾视图
- (nullable UITableViewHeaderFooterView *)footerViewForSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);
//使表视图定位到某一位置(行)
//注意：indexPah参数是定位的位置，决定于分区和行号。animated参数决定是否有动画。scrollPosition参数决定定位的相对位置，它使一个枚举
- (void)scrollToRowAtIndexPath:(NSIndexPath *)indexPath atScrollPosition:(UITableViewScrollPosition)scrollPosition animated:(BOOL)animated;
- (void)scrollToNearestSelectedRowAtScrollPosition:(UITableViewScrollPosition)scrollPosition animated:(BOOL)animated;

// Row insertion/deletion/reloading.
//调用 tableView 的 beginUpdates 和 endUpdates，重新计算 cell 的高度
//开始块标志
//Call this method if you want subsequent insertions, deletion, and selection operations (for example, cellForRowAtIndexPath: and indexPathsForVisibleRows) to be animated simultaneously. You can also use this method followed by the endUpdates method to animate the change in the row heights without reloading the cell. This group of methods must conclude with an invocation of endUpdates. These method pairs can be nested. If you do not make the insertion, deletion, and selection calls inside this block, table attributes such as row count might become invalid. You should not call reloadData within the group; if you call this method within the group, you must perform any animations yourself.
//如果要将后续插入，删除和选择操作（例如，cellForRowAtIndexPath：和indexPathsForVisibleRows）同时动画化，请调用此方法。 您还可以使用此方法，然后使用endUpdates方法来对行高度进行动画处理，而无需重新加载单元格。 这组方法必须以endUpdates的调用结束。 这些方法对可以嵌套。 如果您不在此块内进行插入，删除和选择调用，则表属性（如行计数）可能会变为无效。 你不应该在组内调用reloadData; 如果您在组内调用此方法，则必须自己执行任何动画。
- (void)beginUpdates;   // allow multiple insert/delete of rows and sections to be animated simultaneously. Nestable
//结束快标志
- (void)endUpdates;     // only call insert/delete/reload calls or change the editing state inside an update block.  otherwise things like row count, etc. may be invalid.
//指定的indexSet所包含的一个或多个分区号对应的位置插入分区
- (void)insertSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation;
//删除指定indexSet所包含的一个或多个分区号所对应的分区
- (void)deleteSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation;
- (void)reloadSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation NS_AVAILABLE_IOS(3_0);
//将指定分区移动到另一个位置
- (void)moveSection:(NSInteger)section toSection:(NSInteger)newSection NS_AVAILABLE_IOS(5_0);
//插入一些行，animation参数是一个枚举
- (void)insertRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation;
//删除一些行，animation参数是一个枚举
- (void)deleteRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation;
//重载一些行，animation参数是一个枚举
- (void)reloadRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation NS_AVAILABLE_IOS(3_0);
//移动某行
- (void)moveRowAtIndexPath:(NSIndexPath *)indexPath toIndexPath:(NSIndexPath *)newIndexPath NS_AVAILABLE_IOS(5_0);

// Editing. When set, rows show insert/delete/reorder controls based on data source queries
/*
 当我们调用的上面的函数时，tableView会立刻调用代理方法进行刷新，如果其中我们所做的操作是删除某行，而然数据源数组我们可能并没有刷新，程序就会崩溃掉，原因是代理返回的信息和我们删除后不符
 */
//设置是否是编辑状态(编辑状态下的cell左边会出现一个减号，点击右边会划出删除按钮)
@property (nonatomic, getter=isEditing) BOOL editing;                             // default is NO. setting is not animated.
- (void)setEditing:(BOOL)editing animated:(BOOL)animated;
//设置cell是否可以被选中(默认为YES)
@property (nonatomic) BOOL allowsSelection NS_AVAILABLE_IOS(3_0);  // default is YES. Controls whether rows can be selected when not in editing mode
//设置cell编辑模式下是否可以被选中
@property (nonatomic) BOOL allowsSelectionDuringEditing;                                 // default is NO. Controls whether rows can be selected when in editing mode
//设置是否支持多选
@property (nonatomic) BOOL allowsMultipleSelection NS_AVAILABLE_IOS(5_0);                // default is NO. Controls whether multiple rows can be selected simultaneously
//设置cell编辑模式下是否支持多选
@property (nonatomic) BOOL allowsMultipleSelectionDuringEditing NS_AVAILABLE_IOS(5_0);   // default is NO. Controls whether multiple rows can be selected simultaneously in editing mode

// Selection
//获取选中cell的位置信息
@property (nonatomic, readonly, nullable) NSIndexPath *indexPathForSelectedRow; // returns nil or index path representing section and row of selection.
//获取多选cell的位置信息
@property (nonatomic, readonly, nullable) NSArray<NSIndexPath *> *indexPathsForSelectedRows NS_AVAILABLE_IOS(5_0); // returns nil or a set of index paths representing the sections and rows of the selection.

// Selects and deselects rows. These methods will not call the delegate methods (-tableView:willSelectRowAtIndexPath: or tableView:didSelectRowAtIndexPath:), nor will it send out a notification.
//代码手动选中与取消选中某行
- (void)selectRowAtIndexPath:(nullable NSIndexPath *)indexPath animated:(BOOL)animated scrollPosition:(UITableViewScrollPosition)scrollPosition;
- (void)deselectRowAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;

// Appearance
//tableView附件的相关方法
//设置索引栏最小显示行数
@property (nonatomic) NSInteger sectionIndexMinimumDisplayRowCount;                                                      // show special section index list on right when row count reaches this value. default is 0
//设置索引栏字体颜色
@property (nonatomic, strong, nullable) UIColor *sectionIndexColor NS_AVAILABLE_IOS(6_0) UI_APPEARANCE_SELECTOR;                   // color used for text of the section index
//设置索引栏背景颜色
@property (nonatomic, strong, nullable) UIColor *sectionIndexBackgroundColor NS_AVAILABLE_IOS(7_0) UI_APPEARANCE_SELECTOR;         // the background color of the section index while not being touched
//设置索引栏被选中时的颜色
@property (nonatomic, strong, nullable) UIColor *sectionIndexTrackingBackgroundColor NS_AVAILABLE_IOS(6_0) UI_APPEARANCE_SELECTOR; // the background color of the section index while it is being touched
//设置分割线的风格,这个风格是一个枚举,eg:隐藏自带的:tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
@property (nonatomic) UITableViewCellSeparatorStyle separatorStyle __TVOS_PROHIBITED; // default is UITableViewCellSeparatorStyleSingleLine
//设置分割线颜色
@property (nonatomic, strong, nullable) UIColor *separatorColor UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED; // default is the standard separator gray
//设置分割线毛玻璃效果(IOS8之后可用)
@property (nonatomic, copy, nullable) UIVisualEffect *separatorEffect NS_AVAILABLE_IOS(8_0) UI_APPEARANCE_SELECTOR __TVOS_PROHIBITED; // effect to apply to table separators

@property (nonatomic) BOOL cellLayoutMarginsFollowReadableWidth NS_AVAILABLE_IOS(9_0); // if cell margins are derived from the width of the readableContentGuide.
//设置tableView头视图
@property (nonatomic, strong, nullable) UIView *tableHeaderView;                           // accessory view for above row content. default is nil. not to be confused with section header
//设置tableView尾视图
@property (nonatomic, strong, nullable) UIView *tableFooterView;                           // accessory view below content. default is nil. not to be confused with section footer
//从复用池中取cell
- (nullable __kindof UITableViewCell *)dequeueReusableCellWithIdentifier:(NSString *)identifier;  // Used by the delegate to acquire an already allocated cell, in lieu of allocating a new one.
//获取一个已注册的cell
- (__kindof UITableViewCell *)dequeueReusableCellWithIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(6_0); // newer dequeue method guarantees a cell is returned and resized properly, assuming identifier is registered
//从复用池获取头视图或尾视图
- (nullable __kindof UITableViewHeaderFooterView *)dequeueReusableHeaderFooterViewWithIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(6_0);  // like dequeueReusableCellWithIdentifier:, but for headers/footers

// Beginning in iOS 6, clients can register a nib or class for each cell.
// If all reuse identifiers are registered, use the newer -dequeueReusableCellWithIdentifier:forIndexPath: to guarantee that a cell instance is returned.
// Instances returned from the new dequeue method will also be properly sized when they are returned.
//通过xib文件注册cell
- (void)registerNib:(nullable UINib *)nib forCellReuseIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(5_0);
//通过OC类注册cell
- (void)registerClass:(nullable Class)cellClass forCellReuseIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(6_0);
//通过xib文件和OC类获取注册头视图和尾视图
- (void)registerNib:(nullable UINib *)nib forHeaderFooterViewReuseIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(6_0);
- (void)registerClass:(nullable Class)aClass forHeaderFooterViewReuseIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(6_0);

// Focus

@property (nonatomic) BOOL remembersLastFocusedIndexPath NS_AVAILABLE_IOS(9_0); // defaults to NO. If YES, when focusing on a table view the last focused index path is focused automatically. If the table view has never been focused, then the preferred focused index path is used.

@end

//_______________________________________________________________________________________________________________
// this protocol represents the data model object. as such, it supplies no information about appearance (including the cells)

@protocol UITableViewDataSource<NSObject>   //数据模型
//必须实现的方法
@required
//每个组（section）有多少行（row）
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section;

// Row display. Implementers should *always* try to reuse cells by setting each cell's reuseIdentifier and querying for available reusable cells with dequeueReusableCellWithIdentifier:
// Cell gets various attributes set automatically based on table (separators) and data source (accessory views, editing controls)
//每行的显示，通常通过设置reuseIdentifier进行cell的重复利用
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;
//选择实现的方法
@optional
//有多少组（section），默认1
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView;              // Default is 1 if not implemented
//设置每组的头标题
- (nullable NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section;    // fixed font style. use custom view (UILabel) if you want something different
//设置每组的尾标题
- (nullable NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section;

// Editing

// Individual rows can opt out of having the -editing property set for them. If not implemented, all rows are assumed to be editable.
//该方法返回值决定指定indexPath对应的cell是否可以编辑
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath;

// Moving/reordering

// Allows the reorder accessory view to optionally be shown for a particular row. By default, the reorder control will be shown only if the datasource implements -tableView:moveRowAtIndexPath:toIndexPath:
//该方法返回值决定指定indexPath对应的cell是否可以移动
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath;

// Index
//右边一竖列索引显示的内容（eg：‘a’－‘z’）
- (nullable NSArray<NSString *> *)sectionIndexTitlesForTableView:(UITableView *)tableView;                               // return list of section titles to display in section index view (e.g. "ABCD...Z#")
//把每一组和右边的索引关联起来（eg：‘a’对应第一组），告诉tableview哪个section符合右边的某个索引标题
- (NSInteger)tableView:(UITableView *)tableView sectionForSectionIndexTitle:(NSString *)title atIndex:(NSInteger)index;  // tell table which section corresponds to section title/index (e.g. "B",1))

// Data manipulation - insert and delete support

// After a row has the minus or plus button invoked (based on the UITableViewCellEditingStyle for the cell), the dataSource must commit the change
// Not called for edit actions using UITableViewRowAction - the action's handler will be invoked instead
//当用户对指定表格行编辑(包括插入和删除)时触发该方法
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath;

// Data manipulation - reorder / moving support
//该方法触发移动  通常对数据进行处理
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath *)destinationIndexPath;

@end


// _______________________________________________________________________________________________________________
// this protocol can provide information about cells before they are displayed on screen.

@protocol UITableViewDataSourcePrefetching <NSObject>

@required

// indexPaths are ordered ascending by geometric distance from the table view
- (void)tableView:(UITableView *)tableView prefetchRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;

@optional

// indexPaths that previously were considered as candidates for pre-fetching, but were not actually used; may be a subset of the previous call to -tableView:prefetchRowsAtIndexPaths:
- (void)tableView:(UITableView *)tableView cancelPrefetchingForRowsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;

@end


//_______________________________________________________________________________________________________________

// This category provides convenience methods to make it easier to use an NSIndexPath to represent a section and row
//NSIndexPath类别，提供更方便的办法，用NSIndexPath去描绘section和row
@interface NSIndexPath (UITableView)

+ (instancetype)indexPathForRow:(NSInteger)row inSection:(NSInteger)section;

@property (nonatomic, readonly) NSInteger section;
@property (nonatomic, readonly) NSInteger row;

@end

NS_ASSUME_NONNULL_END
