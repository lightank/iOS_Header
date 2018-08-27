//
//  UICollectionView.h
//  UIKit
//
//  Copyright (c) 2011-2016 Apple Inc. All rights reserved.
//

#import <UIKit/UIScrollView.h>
#import <UIKit/UIKitDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
//滚动的位置
typedef NS_OPTIONS(NSUInteger, UICollectionViewScrollPosition) {
    //无
    UICollectionViewScrollPositionNone                 = 0,
    
    // The vertical positions are mutually exclusive to each other, but are bitwise or-able with the horizontal scroll positions.
    // Combining positions from the same grouping (horizontal or vertical) will result in an NSInvalidArgumentException.
    //垂直布局时使用的 对应上中下
    UICollectionViewScrollPositionTop                  = 1 << 0,
    UICollectionViewScrollPositionCenteredVertically   = 1 << 1,
    UICollectionViewScrollPositionBottom               = 1 << 2,
    
    // Likewise, the horizontal positions are mutually exclusive to each other.
     //水平布局时使用的  对应左中右
    UICollectionViewScrollPositionLeft                 = 1 << 3,
    UICollectionViewScrollPositionCenteredHorizontally = 1 << 4,
    UICollectionViewScrollPositionRight                = 1 << 5
};

@class UICollectionView;
@class UICollectionViewCell;
@class UICollectionViewLayout;
@class UICollectionViewTransitionLayout;
@class UICollectionViewLayoutAttributes;
@class UITouch;
@class UINib;
@class UICollectionReusableView;

// layout transition block signature
//布局过渡块签名
typedef void (^UICollectionViewLayoutInteractiveTransitionCompletion)(BOOL completed, BOOL finished);

// collectionView 焦点更新内容
// 提供相关的从一个视图到另一个特别关注更新信息。他们是更新完成后，通常是短暂的丢弃的对象。
NS_CLASS_AVAILABLE_IOS(9_0) @interface UICollectionViewFocusUpdateContext : UIFocusUpdateContext
// 上一个交互的索引
@property (nonatomic, strong, readonly, nullable) NSIndexPath *previouslyFocusedIndexPath;
// 下一个交互的索引
@property (nonatomic, strong, readonly, nullable) NSIndexPath *nextFocusedIndexPath;

@end

//UICollectionView 的数据源协议
@protocol UICollectionViewDataSource <NSObject>
@required
// 返回每一组有多少个小区
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section;

// The cell that is returned must be retrieved from a call to -dequeueReusableCellWithReuseIdentifier:forIndexPath:
/*
//返回的单元格必须从对-dequeueReusableCellWithReuseIdentifier的调用中检索：forIndexPath：
必须提前注册Cell并设置重用标识
注册Cell的三种方式：
1> 用 XIB 来注册Cell，表示Cell如何去创建， 在注册同时必须给小区设置重用标识
2> 用类（纯代码）来注册Cell，表示Cell用代码来创建，在注册同时必须Cell设置重用标识
3> 在storyboard中给Cell，设置重用标识时会同时注册Cell
// 苹果强烈建议我们利用Cell的循环利用机制
*/
// 返回每一组的每一个电池
- (__kindof UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath;

@optional
// 返回有多少组
- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView;

// The view that is returned must be retrieved from a call to -dequeueReusableSupplementaryViewOfKind:withReuseIdentifier:forIndexPath:
//返回的视图必须从对-dequeueReusableSupplementaryViewOfKind的调用中检索：withReuseIdentifier：forIndexPath：
// 返回的CollectionView 的haderView 和footerView，也必须提前注册
- (UICollectionReusableView *)collectionView:(UICollectionView *)collectionView viewForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath;
//cell是否可以移动
- (BOOL)collectionView:(UICollectionView *)collectionView canMoveItemAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0);
//移动cell从sourceIndexPath到destinationIndexPath
- (void)collectionView:(UICollectionView *)collectionView moveItemAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath*)destinationIndexPath NS_AVAILABLE_IOS(9_0);

/// Returns a list of index titles to display in the index view (e.g. ["A", "B", "C" ... "Z", "#"])
//返回索引数组
- (nullable NSArray<NSString *> *)indexTitlesForCollectionView:(UICollectionView *)collectionView API_AVAILABLE(tvos(10.2));

/// Returns the index path that corresponds to the given title / index. (e.g. "B",1)
/// Return an index path with a single index to indicate an entire section, instead of a specific item.
//索引文字对应的IndexPath
- (NSIndexPath *)collectionView:(UICollectionView *)collectionView indexPathForIndexTitle:(NSString *)title atIndex:(NSInteger)index API_AVAILABLE(tvos(10.2));

@end

@protocol UICollectionViewDataSourcePrefetching <NSObject>
@required
// indexPaths are ordered ascending by geometric distance from the collection view
//indexPaths从collectionView中按几何举例升序排序
- (void)collectionView:(UICollectionView *)collectionView prefetchItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths NS_AVAILABLE_IOS(10_0);

@optional
// indexPaths that previously were considered as candidates for pre-fetching, but were not actually used; may be a subset of the previous call to -collectionView:prefetchItemsAtIndexPaths:
//indexPaths数组开始时被预选排序的,但是并未被使用,可能是调用-collectionView:prefetchItemsAtIndexPaths:的子集
- (void)collectionView:(UICollectionView *)collectionView cancelPrefetchingForItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths  NS_AVAILABLE_IOS(10_0);

@end


@protocol UICollectionViewDelegate <UIScrollViewDelegate>
@optional

// Methods for notification of selection/deselection and highlight/unhighlight events.
// The sequence of calls leading to selection from a user touch is:
//
// (when the touch begins)
// 1. -collectionView:shouldHighlightItemAtIndexPath:
// 2. -collectionView:didHighlightItemAtIndexPath:
//
// (when the touch lifts)
// 3. -collectionView:shouldSelectItemAtIndexPath: or -collectionView:shouldDeselectItemAtIndexPath:
// 4. -collectionView:didSelectItemAtIndexPath: or -collectionView:didDeselectItemAtIndexPath:
// 5. -collectionView:didUnhighlightItemAtIndexPath:
/*
 /*
 事件的处理顺序如下：
 
 1.手指按下,当触摸开始
 2.shouldHighlightItemAtIndexPath (如果返回YES则向下执行，否则执行到这里为止)
 3.didHighlightItemAtIndexPath (高亮)
 4.手指松开,当触摸抬起
 5.didUnhighlightItemAtIndexPath (取消高亮)
 6.shouldSelectItemAtIndexPath (如果返回YES则向下执行，否则执行到这里为止)
 7.didSelectItemAtIndexPath (执行选择事件)
 */
 */
// 下面是三个和高亮有关的方法：
- (BOOL)collectionView:(UICollectionView *)collectionView shouldHighlightItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)collectionView:(UICollectionView *)collectionView didHighlightItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)collectionView:(UICollectionView *)collectionView didUnhighlightItemAtIndexPath:(NSIndexPath *)indexPath;
//返回这个UICollectionView是否可以被选择
- (BOOL)collectionView:(UICollectionView *)collectionView shouldSelectItemAtIndexPath:(NSIndexPath *)indexPath;
- (BOOL)collectionView:(UICollectionView *)collectionView shouldDeselectItemAtIndexPath:(NSIndexPath *)indexPath; // called when the user taps on an already-selected item in multi-select mode
// 当指定indexPath处的item被选择时触发
- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)collectionView:(UICollectionView *)collectionView didDeselectItemAtIndexPath:(NSIndexPath *)indexPath;
//cell将要显示
- (void)collectionView:(UICollectionView *)collectionView willDisplayCell:(UICollectionViewCell *)cell forItemAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(8_0);
//Tells the delegate that the specified supplementary view is about to be displayed in the collection view.
// headerView / FooterView 将要显示
- (void)collectionView:(UICollectionView *)collectionView willDisplaySupplementaryView:(UICollectionReusableView *)view forElementKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(8_0);
- (void)collectionView:(UICollectionView *)collectionView didEndDisplayingCell:(UICollectionViewCell *)cell forItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)collectionView:(UICollectionView *)collectionView didEndDisplayingSupplementaryView:(UICollectionReusableView *)view forElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)indexPath;

// These methods provide support for copy/paste actions on cells.
// All three should be implemented if any are.
//这些方法提供了对Cell的复制/粘贴操作的支持。
//所有三个都应该实现，如果有的话。
// 复制粘贴Cell
- (BOOL)collectionView:(UICollectionView *)collectionView shouldShowMenuForItemAtIndexPath:(NSIndexPath *)indexPath;
- (BOOL)collectionView:(UICollectionView *)collectionView canPerformAction:(SEL)action forItemAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender;
- (void)collectionView:(UICollectionView *)collectionView performAction:(SEL)action forItemAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender;

// support for custom transition layout
//支持自定义过渡布局
// 自定义转换布局
- (nonnull UICollectionViewTransitionLayout *)collectionView:(UICollectionView *)collectionView transitionLayoutForOldLayout:(UICollectionViewLayout *)fromLayout newLayout:(UICollectionViewLayout *)toLayout;

// Focus
//焦点
- (BOOL)collectionView:(UICollectionView *)collectionView canFocusItemAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0);
- (BOOL)collectionView:(UICollectionView *)collectionView shouldUpdateFocusInContext:(UICollectionViewFocusUpdateContext *)context NS_AVAILABLE_IOS(9_0);
- (void)collectionView:(UICollectionView *)collectionView didUpdateFocusInContext:(UICollectionViewFocusUpdateContext *)context withAnimationCoordinator:(UIFocusAnimationCoordinator *)coordinator NS_AVAILABLE_IOS(9_0);
- (nullable NSIndexPath *)indexPathForPreferredFocusedViewInCollectionView:(UICollectionView *)collectionView NS_AVAILABLE_IOS(9_0);

- (NSIndexPath *)collectionView:(UICollectionView *)collectionView targetIndexPathForMoveFromItemAtIndexPath:(NSIndexPath *)originalIndexPath toProposedIndexPath:(NSIndexPath *)proposedIndexPath NS_AVAILABLE_IOS(9_0);

- (CGPoint)collectionView:(UICollectionView *)collectionView targetContentOffsetForProposedContentOffset:(CGPoint)proposedContentOffset NS_AVAILABLE_IOS(9_0); // customize the content offset to be applied during transition or update animations

@end

NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionView : UIScrollView
//初始化方法,需要frame,布局对象
- (instancetype)initWithFrame:(CGRect)frame collectionViewLayout:(UICollectionViewLayout *)layout NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
//布局对象
@property (nonatomic, strong) UICollectionViewLayout *collectionViewLayout;
//代理
@property (nonatomic, weak, nullable) id <UICollectionViewDelegate> delegate;
//数据源
@property (nonatomic, weak, nullable) id <UICollectionViewDataSource> dataSource;
//The object that acts as the prefetching data source for the collection view, receiving notifications of upcoming cell data requirements.
@property (nonatomic, weak, nullable) id<UICollectionViewDataSourcePrefetching> prefetchDataSource NS_AVAILABLE_IOS(10_0);
@property (nonatomic, getter=isPrefetchingEnabled) BOOL prefetchingEnabled NS_AVAILABLE_IOS(10_0);
//背景视图
@property (nonatomic, strong, nullable) UIView *backgroundView; // will be automatically resized to track the size of the collection view and placed behind all cells and supplementary views.

// For each reuse identifier that the collection view will use, register either a class or a nib from which to instantiate a cell.
// If a nib is registered, it must contain exactly 1 top level object which is a UICollectionViewCell.
// If a class is registered, it will be instantiated via alloc/initWithFrame:
//注册cell
- (void)registerClass:(nullable Class)cellClass forCellWithReuseIdentifier:(NSString *)identifier;
- (void)registerNib:(nullable UINib *)nib forCellWithReuseIdentifier:(NSString *)identifier;
//Registers a class for use in creating supplementary views for the collection view.
- (void)registerClass:(nullable Class)viewClass forSupplementaryViewOfKind:(NSString *)elementKind withReuseIdentifier:(NSString *)identifier;
//Registers a nib file for use in creating supplementary views for the collection view.
- (void)registerNib:(nullable UINib *)nib forSupplementaryViewOfKind:(NSString *)kind withReuseIdentifier:(NSString *)identifier;
//Returns a reusable cell object located by its identifier
//根据id返回已注册的复用cell
- (__kindof UICollectionViewCell *)dequeueReusableCellWithReuseIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath;
//Returns a reusable supplementary view located by its identifier and kind.
//根据id返回已注册的复用辅助类型cell
- (__kindof UICollectionReusableView *)dequeueReusableSupplementaryViewOfKind:(NSString *)elementKind withReuseIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath;

// These properties control whether items can be selected, and if so, whether multiple items can be simultaneously selected.
//是否允许选择
@property (nonatomic) BOOL allowsSelection; // default is YES
//是否允许多选
@property (nonatomic) BOOL allowsMultipleSelection; // default is NO

#if UIKIT_DEFINE_AS_PROPERTIES
//返回当前选择的item下标数组
@property (nonatomic, readonly, nullable) NSArray<NSIndexPath *> *indexPathsForSelectedItems; // returns nil or an array of selected index paths
#else
- (nullable NSArray<NSIndexPath *> *)indexPathsForSelectedItems; // returns nil or an array of selected index paths
#endif
//Selects the item at the specified index path and optionally scrolls it into view.
//选中Cell，并滚动到选中单元的什么位置
- (void)selectItemAtIndexPath:(nullable NSIndexPath *)indexPath animated:(BOOL)animated scrollPosition:(UICollectionViewScrollPosition)scrollPosition;
//取消选中Cell
- (void)deselectItemAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;
//重新刷新表格（弃用之前所有单元格，重新调用数据源方法
- (void)reloadData; // discard the dataSource and delegate data and requery as necessary
// 设置的CollectionView 的布局
- (void)setCollectionViewLayout:(UICollectionViewLayout *)layout animated:(BOOL)animated; // transition from one layout to another
- (void)setCollectionViewLayout:(UICollectionViewLayout *)layout animated:(BOOL)animated completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(7_0);
//转场动画
- (UICollectionViewTransitionLayout *)startInteractiveTransitionToCollectionViewLayout:(UICollectionViewLayout *)layout completion:(nullable UICollectionViewLayoutInteractiveTransitionCompletion)completion NS_AVAILABLE_IOS(7_0);
- (void)finishInteractiveTransition NS_AVAILABLE_IOS(7_0);
- (void)cancelInteractiveTransition NS_AVAILABLE_IOS(7_0);

// Information about the current state of the collection view.
//关于集合视图的当前状态的信息
#if UIKIT_DEFINE_AS_PROPERTIES
// 返回有多少组
@property (nonatomic, readonly) NSInteger numberOfSections;
#else
- (NSInteger)numberOfSections;
#endif
// 返回某一个组有多少个cell
- (NSInteger)numberOfItemsInSection:(NSInteger)section;
// 返回指定下标cell的布局属性
- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForItemAtIndexPath:(NSIndexPath *)indexPath;
// 返回指定页眉/页脚的布局属性
- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath;
// 返回指定位置的cell索引
- (nullable NSIndexPath *)indexPathForItemAtPoint:(CGPoint)point;
// 返回cell的索引
- (nullable NSIndexPath *)indexPathForCell:(UICollectionViewCell *)cell;
//返回指定索引的cell
- (nullable UICollectionViewCell *)cellForItemAtIndexPath:(NSIndexPath *)indexPath;
#if UIKIT_DEFINE_AS_PROPERTIES
//可视范围内所有cell
@property (nonatomic, readonly) NSArray<__kindof UICollectionViewCell *> *visibleCells;
//可视范围内所有cell的索引数组
@property (nonatomic, readonly) NSArray<NSIndexPath *> *indexPathsForVisibleItems;
#else
- (NSArray<__kindof UICollectionViewCell *> *)visibleCells;
- (NSArray<NSIndexPath *> *)indexPathsForVisibleItems;
#endif
// 返回指定索引的页眉/页脚
- (nullable UICollectionReusableView *)supplementaryViewForElementKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0);
// 返回可视范围内的所有页眉/页脚
- (NSArray<UICollectionReusableView *> *)visibleSupplementaryViewsOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(9_0);
// 返回可视范围内所有页眉/页脚的索引
- (NSArray<NSIndexPath *> *)indexPathsForVisibleSupplementaryElementsOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(9_0);

// Interacting with the collection view.
//与collection view进行交互
// 滚动到指定索引的细胞的某个位置
- (void)scrollToItemAtIndexPath:(NSIndexPath *)indexPath atScrollPosition:(UICollectionViewScrollPosition)scrollPosition animated:(BOOL)animated;

// These methods allow dynamic modification of the current set of items in the collection view
// 插入一组
- (void)insertSections:(NSIndexSet *)sections;
// 删除一组
- (void)deleteSections:(NSIndexSet *)sections;
// 刷新某组
- (void)reloadSections:(NSIndexSet *)sections;
- (void)moveSection:(NSInteger)section toSection:(NSInteger)newSection;
// 在指定位置插入单个或多个cell
- (void)insertItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
// 删除单个或多个位置的cell
- (void)deleteItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
// 删除单个或多个位置的cell
- (void)reloadItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
// 移动某个cell到什么位置
- (void)moveItemAtIndexPath:(NSIndexPath *)indexPath toIndexPath:(NSIndexPath *)newIndexPath;
// 执行多个插入/ 删除/ 恢复/ 移动单元可以同时动画。可嵌套的
//允许多次插入/删除/重新加载/移动 以同时动画调用。可嵌套。
- (void)performBatchUpdates:(void (^ __nullable)(void))updates completion:(void (^ __nullable)(BOOL finished))completion; // allows multiple insert/delete/reload/move calls to be animated simultaneously. Nestable.

// Support for reordering
//支持重新排序
//如果重新排序被禁止，则返回NO - 否则为YES
- (BOOL)beginInteractiveMovementForItemAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0); // returns NO if reordering was prevented from beginning - otherwise YES
- (void)updateInteractiveMovementTargetPosition:(CGPoint)targetPosition NS_AVAILABLE_IOS(9_0);
- (void)endInteractiveMovement NS_AVAILABLE_IOS(9_0);
- (void)cancelInteractiveMovement NS_AVAILABLE_IOS(9_0);

// Support for Focus
//是否记住上一个焦点index
@property (nonatomic) BOOL remembersLastFocusedIndexPath NS_AVAILABLE_IOS(9_0); // defaults to NO. If YES, when focusing on a collection view the last focused index path is focused automatically. If the collection view has never been focused, then the preferred focused index path is used.

@end

@interface NSIndexPath (UICollectionViewAdditions)

+ (instancetype)indexPathForItem:(NSInteger)item inSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);

@property (nonatomic, readonly) NSInteger item NS_AVAILABLE_IOS(6_0);

@end

NS_ASSUME_NONNULL_END
