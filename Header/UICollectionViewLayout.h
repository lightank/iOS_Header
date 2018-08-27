//
//  UICollectionViewLayout.h
//  UIKit
//
//  Copyright (c) 2011-2016 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <QuartzCore/CATransform3D.h>
#import <UIKit/UIDynamicBehavior.h>

// The UICollectionViewLayout class is provided as an abstract class for subclassing to define custom collection layouts.
// Defining a custom layout is an advanced operation intended for applications with complex needs.

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, UICollectionElementCategory) {
    UICollectionElementCategoryCell,
    UICollectionElementCategorySupplementaryView,
    UICollectionElementCategoryDecorationView
};

@class UICollectionViewLayoutAttributes;
@class UICollectionView;
@class UINib;

/*
 可以看到，UICollectionViewLayoutAttributes的实例中包含了诸如边框，中心点，大小，形状，透明度，层次关系和是否隐藏等信息。
 1.一个cell对应一个UICollectionViewLayoutAttributes对象
 2.UICollectionViewLayoutAttributes对象决定了cell的摆设位置（frame）
 */
NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionViewLayoutAttributes : NSObject <NSCopying, UIDynamicItem>
//配置item的布局位置
@property (nonatomic) CGRect frame;
//配置item的中心
@property (nonatomic) CGPoint center;
//配置item的尺寸
@property (nonatomic) CGSize size;
//配置item的3D效果
@property (nonatomic) CATransform3D transform3D;
//配置item的bounds
@property (nonatomic) CGRect bounds NS_AVAILABLE_IOS(7_0);
//配置item的旋转
@property (nonatomic) CGAffineTransform transform NS_AVAILABLE_IOS(7_0);
// 透明度
@property (nonatomic) CGFloat alpha;
//配置item的z坐标
@property (nonatomic) NSInteger zIndex; // default is 0
// 是否隐藏
@property (nonatomic, getter=isHidden) BOOL hidden; // As an optimization, UICollectionView might not create a view for items whose hidden attribute is YES
//item的indexpath
@property (nonatomic, strong) NSIndexPath *indexPath;
//获取item的类型
@property (nonatomic, readonly) UICollectionElementCategory representedElementCategory;
@property (nonatomic, readonly, nullable) NSString *representedElementKind; // nil when representedElementCategory is UICollectionElementCategoryCell
//一些初始化方法
+ (instancetype)layoutAttributesForCellWithIndexPath:(NSIndexPath *)indexPath;
+ (instancetype)layoutAttributesForSupplementaryViewOfKind:(NSString *)elementKind withIndexPath:(NSIndexPath *)indexPath;
+ (instancetype)layoutAttributesForDecorationViewOfKind:(NSString *)decorationViewKind withIndexPath:(NSIndexPath *)indexPath;

@end

//更新事件类型
typedef NS_ENUM(NSInteger, UICollectionUpdateAction) {
    //插入cell
    UICollectionUpdateActionInsert,
    //删除cell
    UICollectionUpdateActionDelete,
    //刷新cell
    UICollectionUpdateActionReload,
    //移动cell
    UICollectionUpdateActionMove,
    //无
    UICollectionUpdateActionNone
};

NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionViewUpdateItem : NSObject
//刷新前的索引
@property (nonatomic, readonly, nullable) NSIndexPath *indexPathBeforeUpdate; // nil for UICollectionUpdateActionInsert
//刷新后的索引
@property (nonatomic, readonly, nullable) NSIndexPath *indexPathAfterUpdate; // nil for UICollectionUpdateActionDelete
//刷新的事件类型
@property (nonatomic, readonly) UICollectionUpdateAction updateAction;

@end

NS_CLASS_AVAILABLE_IOS(7_0) @interface UICollectionViewLayoutInvalidationContext : NSObject

//A Boolean that indicates that all layout data should be marked as invalid. (read-only)
//是否让所有布局数据失效
@property (nonatomic, readonly) BOOL invalidateEverything; // set to YES when invalidation occurs because the collection view is sent -reloadData
//如果是，布局应该从CollectionView重新查询section和item 数量,CollectionView在插入或删除item时执行-reloadData时，设置为YES
@property (nonatomic, readonly) BOOL invalidateDataSourceCounts; // if YES, the layout should requery section and item counts from the collection view - set to YES when the collection view is sent -reloadData and when items are inserted or deleted
//Adds the cells at the specified index paths to the list of invalid items.
//把指定索引的cell数组添加到失效item数组中
- (void)invalidateItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths NS_AVAILABLE_IOS(8_0);
//Adds the supplementary views at the specified index paths to the list of invalid items.
- (void)invalidateSupplementaryElementsOfKind:(NSString *)elementKind atIndexPaths:(NSArray<NSIndexPath *> *)indexPaths NS_AVAILABLE_IOS(8_0);
//Adds the decoration views at the specified index paths to the list of invalid items.
- (void)invalidateDecorationElementsOfKind:(NSString *)elementKind atIndexPaths:(NSArray<NSIndexPath *> *)indexPaths NS_AVAILABLE_IOS(8_0);
@property (nonatomic, readonly, nullable) NSArray<NSIndexPath *> *invalidatedItemIndexPaths NS_AVAILABLE_IOS(8_0);
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, NSArray<NSIndexPath *> *> *invalidatedSupplementaryIndexPaths NS_AVAILABLE_IOS(8_0); // keys are element kind strings - values are NSArrays of NSIndexPaths
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, NSArray<NSIndexPath *> *> *invalidatedDecorationIndexPaths NS_AVAILABLE_IOS(8_0); // keys are element kind strings - values are NSArrays of NSIndexPaths

@property (nonatomic) CGPoint contentOffsetAdjustment NS_AVAILABLE_IOS(8_0); // delta to be applied to the collection view's current contentOffset - default is CGPointZero
@property (nonatomic) CGSize contentSizeAdjustment NS_AVAILABLE_IOS(8_0); // delta to be applied to the current content size - default is CGSizeZero

// Reordering support
//An array of index paths representing the previous location of moving items in the collection view. (read-only)
@property (nonatomic, readonly, copy, nullable) NSArray<NSIndexPath *> *previousIndexPathsForInteractivelyMovingItems NS_AVAILABLE_IOS(9_0); // index paths of moving items prior to the invalidation
//An array of index paths representing the new location of moving items in the collection view. (read-only)
@property (nonatomic, readonly, copy, nullable) NSArray<NSIndexPath *> *targetIndexPathsForInteractivelyMovingItems NS_AVAILABLE_IOS(9_0); // index paths of moved items following the invalidation
//The current point used to determine the placement of moving items. (read-only)
@property (nonatomic, readonly) CGPoint interactiveMovementTarget NS_AVAILABLE_IOS(9_0);

@end

NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionViewLayout : NSObject <NSCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

// Methods in this class are meant to be overridden and will be called by its collection view to gather layout information.
// To get the truth on the current state of the collection view, call methods on UICollectionView rather than these.

@property (nullable, nonatomic, readonly) UICollectionView *collectionView;

// Call -invalidateLayout to indicate that the collection view needs to requery the layout information.
// Subclasses must always call super if they override.
//Invalidates the current layout and triggers a layout update.
- (void)invalidateLayout;
//Invalidates the current layout using the information in the provided context object.
- (void)invalidateLayoutWithContext:(UICollectionViewLayoutInvalidationContext *)context NS_AVAILABLE_IOS(7_0);

- (void)registerClass:(nullable Class)viewClass forDecorationViewOfKind:(NSString *)elementKind;
- (void)registerNib:(nullable UINib *)nib forDecorationViewOfKind:(NSString *)elementKind;

@end

@interface UICollectionViewLayout (UISubclassingHooks)

#if UIKIT_DEFINE_AS_PROPERTIES
//Returns the class to use when creating layout attributes objects.
@property(class, nonatomic, readonly) Class layoutAttributesClass; // override this method to provide a custom class to be used when instantiating instances of UICollectionViewLayoutAttributes
//Returns the class to use when creating an invalidation context for the layout.
@property(class, nonatomic, readonly) Class invalidationContextClass NS_AVAILABLE_IOS(7_0); // override this method to provide a custom class to be used for invalidation contexts
#else
//Returns the class to use when creating layout attributes objects.
+ (Class)layoutAttributesClass; // override this method to provide a custom class to be used when instantiating instances of UICollectionViewLayoutAttributes
//Returns the class to use when creating an invalidation context for the layout.
+ (Class)invalidationContextClass NS_AVAILABLE_IOS(7_0); // override this method to provide a custom class to be used for invalidation contexts
#endif

// The collection view calls -prepareLayout once at its first layout as the first message to the layout instance.
// The collection view calls -prepareLayout again after layout is invalidated and before requerying the layout information.
// Subclasses should always call super if they override.
/*
 顾名思义这个方法就是当你的布局快要生效的时候调用，所以我们需要在这个方法里计算好每个Item的position和CollectionView的size。并且将其缓存下来，这种做法可以提升滚动流畅性。
 注意：这一步切记要调用[super prepareLayout]
 */
- (void)prepareLayout;

// UICollectionView calls these four methods to determine the layout information.
// Implement -layoutAttributesForElementsInRect: to return layout attributes for for supplementary or decoration views, or to perform layout in an as-needed-on-screen fashion.
// Additionally, all layout subclasses should implement -layoutAttributesForItemAtIndexPath: to return layout attributes instances on demand for specific index paths.
// If the layout supports any supplementary or decoration view types, it should also implement the respective atIndexPath: methods for those types.
// 返回rect中的所有的元素的布局属性
/*
 返回的是包含UICollectionViewLayoutAttributes的NSArray
 UICollectionViewLayoutAttributes可以是cell，追加视图或装饰
 视图的信息，通过不同的UICollectionViewLayoutAttributes初始
 化方法可以得到不同类型的UICollectionViewLayoutAttributes：
 */
- (nullable NSArray<__kindof UICollectionViewLayoutAttributes *> *)layoutAttributesForElementsInRect:(CGRect)rect; // return an array layout attributes instances for all the views in the given rect
// 返回对应于indexPath的位置的cell的布局属性
- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForItemAtIndexPath:(NSIndexPath *)indexPath;
//返回对应于indexPath的位置的追加视图的布局属性，如果没有追加视图可不重载
- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForSupplementaryViewOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)indexPath;
// 返回对应于indexPath的位置的装饰视图的布局属性，如果没有装饰视图可不重载
- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForDecorationViewOfKind:(NSString*)elementKind atIndexPath:(NSIndexPath *)indexPath;
// 当边界发生改变时，是否应该刷新布局。如果YES则在边界变化（一般是scroll到其他地方）时，将重新计算需要的布局信息。
- (BOOL)shouldInvalidateLayoutForBoundsChange:(CGRect)newBounds; // return YES to cause the collection view to requery the layout for geometry information
- (UICollectionViewLayoutInvalidationContext *)invalidationContextForBoundsChange:(CGRect)newBounds NS_AVAILABLE_IOS(7_0);
//Asks the layout object if changes to a self-sizing cell require a layout update.
- (BOOL)shouldInvalidateLayoutForPreferredLayoutAttributes:(UICollectionViewLayoutAttributes *)preferredAttributes withOriginalAttributes:(UICollectionViewLayoutAttributes *)originalAttributes NS_AVAILABLE_IOS(8_0);
//Returns a context object that identifies the portions of the layout that should change in response to dynamic cell changes.
- (UICollectionViewLayoutInvalidationContext *)invalidationContextForPreferredLayoutAttributes:(UICollectionViewLayoutAttributes *)preferredAttributes withOriginalAttributes:(UICollectionViewLayoutAttributes *)originalAttributes NS_AVAILABLE_IOS(8_0);
//Returns the point at which to stop scrolling.
- (CGPoint)targetContentOffsetForProposedContentOffset:(CGPoint)proposedContentOffset withScrollingVelocity:(CGPoint)velocity; // return a point at which to rest after scrolling - for layouts that want snap-to-point scrolling behavior
//Returns the content offset to use after an animated layout update or change.
- (CGPoint)targetContentOffsetForProposedContentOffset:(CGPoint)proposedContentOffset NS_AVAILABLE_IOS(7_0); // a layout can return the content offset to be applied during transition or update animations

#if UIKIT_DEFINE_AS_PROPERTIES
//Returns the width and height of the collection view’s contents.
@property(nonatomic, readonly) CGSize collectionViewContentSize; // Subclasses must override this method and use it to return the width and height of the collection view’s content. These values represent the width and height of all the content, not just the content that is currently visible. The collection view uses this information to configure its own content size to facilitate scrolling.
#else
// 返回collectionView的内容的尺寸
- (CGSize)collectionViewContentSize; // Subclasses must override this method and use it to return the width and height of the collection view’s content. These values represent the width and height of all the content, not just the content that is currently visible. The collection view uses this information to configure its own content size to facilitate scrolling.
#endif

@end

@interface UICollectionViewLayout (UIUpdateSupportHooks)

// This method is called when there is an update with deletes/inserts to the collection view.
// It will be called prior to calling the initial/final layout attribute methods below to give the layout an opportunity to do batch computations for the insertion and deletion layout attributes.
// The updateItems parameter is an array of UICollectionViewUpdateItem instances for each element that is moving to a new index path.
//Notifies the layout object that the contents of the collection view are about to change.
- (void)prepareForCollectionViewUpdates:(NSArray<UICollectionViewUpdateItem *> *)updateItems;
//Performs any additional animations or clean up needed during a collection view update.
- (void)finalizeCollectionViewUpdates; // called inside an animation block after the update
//Prepares the layout object for animated changes to the view’s bounds or the insertion or deletion of items.
- (void)prepareForAnimatedBoundsChange:(CGRect)oldBounds; // UICollectionView calls this when its bounds have changed inside an animation block before displaying cells in its new bounds
//Cleans up after any animated changes to the view’s bounds or after the insertion or deletion of items.
- (void)finalizeAnimatedBoundsChange; // also called inside the animation block

// UICollectionView calls this when prior the layout transition animation on the incoming and outgoing layout
//Tells the layout object that it is about to be removed as the layout for the collection view.
- (void)prepareForTransitionToLayout:(UICollectionViewLayout *)newLayout NS_AVAILABLE_IOS(7_0);
//Tells the layout object to prepare to be installed as the layout for the collection view.
- (void)prepareForTransitionFromLayout:(UICollectionViewLayout *)oldLayout NS_AVAILABLE_IOS(7_0);
//Tells the layout object to perform any final steps before the transition animations occur.
- (void)finalizeLayoutTransition NS_AVAILABLE_IOS(7_0);  // called inside an animation block after the transition


// This set of methods is called when the collection view undergoes an animated transition such as a batch update block or an animated bounds change.
// For each element on screen before the invalidation, finalLayoutAttributesForDisappearingXXX will be called and an animation setup from what is on screen to those final attributes.
// For each element on screen after the invalidation, initialLayoutAttributesForAppearingXXX will be called and an animation setup from those initial attributes to what ends up on screen.
//Returns the starting layout information for an item being inserted into the collection view.
- (nullable UICollectionViewLayoutAttributes *)initialLayoutAttributesForAppearingItemAtIndexPath:(NSIndexPath *)itemIndexPath;
//Returns the final layout information for an item that is about to be removed from the collection view.
- (nullable UICollectionViewLayoutAttributes *)finalLayoutAttributesForDisappearingItemAtIndexPath:(NSIndexPath *)itemIndexPath;
//Returns the starting layout information for a supplementary view being inserted into the collection view.
- (nullable UICollectionViewLayoutAttributes *)initialLayoutAttributesForAppearingSupplementaryElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)elementIndexPath;
//Returns the final layout information for a supplementary view that is about to be removed from the collection view.
- (nullable UICollectionViewLayoutAttributes *)finalLayoutAttributesForDisappearingSupplementaryElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)elementIndexPath;
//Returns the starting layout information for a decoration view being inserted into the collection view.
- (nullable UICollectionViewLayoutAttributes *)initialLayoutAttributesForAppearingDecorationElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)decorationIndexPath;
//Returns the final layout information for a decoration view that is about to be removed from the collection view.
- (nullable UICollectionViewLayoutAttributes *)finalLayoutAttributesForDisappearingDecorationElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)decorationIndexPath;

// These methods are called by collection view during an update block.
// Return an array of index paths to indicate views that the layout is deleting or inserting in response to the update.
//Returns an array of index paths representing the supplementary views to remove.
- (NSArray<NSIndexPath *> *)indexPathsToDeleteForSupplementaryViewOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(7_0);
//Returns an array of index paths representing the decoration views to remove.
- (NSArray<NSIndexPath *> *)indexPathsToDeleteForDecorationViewOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(7_0);
//Returns an array of index paths for the supplementary views you want to add to the layout.
- (NSArray<NSIndexPath *> *)indexPathsToInsertForSupplementaryViewOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(7_0);
//Returns an array of index paths representing the decoration views to add.
- (NSArray<NSIndexPath *> *)indexPathsToInsertForDecorationViewOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(7_0);

@end

@interface UICollectionViewLayout (UIReorderingSupportHooks)
//Returns the index path to for an item when it is at the specified location in the collection view’s bounds.
- (NSIndexPath *)targetIndexPathForInteractivelyMovingItem:(NSIndexPath *)previousIndexPath withPosition:(CGPoint)position NS_AVAILABLE_IOS(9_0);
//Returns the layout attributes of an item when it is being moved interactively by the user.
- (UICollectionViewLayoutAttributes *)layoutAttributesForInteractivelyMovingItemAtIndexPath:(NSIndexPath *)indexPath withTargetPosition:(CGPoint)position NS_AVAILABLE_IOS(9_0);
//Returns a context object that identifies the items that are being interactively moved in the layout.
- (UICollectionViewLayoutInvalidationContext *)invalidationContextForInteractivelyMovingItems:(NSArray<NSIndexPath *> *)targetIndexPaths withTargetPosition:(CGPoint)targetPosition previousIndexPaths:(NSArray<NSIndexPath *> *)previousIndexPaths previousPosition:(CGPoint)previousPosition NS_AVAILABLE_IOS(9_0);
//Returns a context object that identifies the items that were moved
- (UICollectionViewLayoutInvalidationContext *)invalidationContextForEndingInteractiveMovementOfItemsToFinalIndexPaths:(NSArray<NSIndexPath *> *)indexPaths previousIndexPaths:(NSArray<NSIndexPath *> *)previousIndexPaths movementCancelled:(BOOL)movementCancelled NS_AVAILABLE_IOS(9_0);

@end

NS_ASSUME_NONNULL_END
