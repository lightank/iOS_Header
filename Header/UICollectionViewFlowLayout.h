//
//  UICollectionViewFlowLayout.h
//  UIKit
//
//  Copyright (c) 2011-2016 Apple Inc. All rights reserved.
//

#import <UIKit/UICollectionViewLayout.h>
#import <UIKit/UICollectionView.h>
#import <UIKit/UIKitDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN NSString *const UICollectionElementKindSectionHeader NS_AVAILABLE_IOS(6_0);
UIKIT_EXTERN NSString *const UICollectionElementKindSectionFooter NS_AVAILABLE_IOS(6_0);
UIKIT_EXTERN const CGSize UICollectionViewFlowLayoutAutomaticSize  NS_AVAILABLE_IOS(10_0);

//滚动方向
typedef NS_ENUM(NSInteger, UICollectionViewScrollDirection) {
    UICollectionViewScrollDirectionVertical,    //垂直
    UICollectionViewScrollDirectionHorizontal   //水平
};

NS_CLASS_AVAILABLE_IOS(7_0) @interface UICollectionViewFlowLayoutInvalidationContext : UICollectionViewLayoutInvalidationContext

@property (nonatomic) BOOL invalidateFlowLayoutDelegateMetrics; // if set to NO, flow layout will not requery the collection view delegate for size information etc.
@property (nonatomic) BOOL invalidateFlowLayoutAttributes; // if set to NO, flow layout will keep all layout information, effectively not invalidating - useful for a subclass which invalidates only a piece of itself

@end

@protocol UICollectionViewDelegateFlowLayout <UICollectionViewDelegate>
@optional
// 返回单元格的size
- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath;
//返回整组单元格上下左右边距，可以通过section判断设定
- (UIEdgeInsets)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout insetForSectionAtIndex:(NSInteger)section;
// 设定指定区内Cell的最小行距，也可以直接设置UICollectionViewFlowLayout的minimumLineSpacing属性
//间隔代理，返回同一组内单元格上下
- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout minimumLineSpacingForSectionAtIndex:(NSInteger)section;
// 设定指定区内Cell的最小间距，也可以直接设置UICollectionViewFlowLayout的minimumInteritemSpacing属性
//间隔代理，返回同一组内单元格左右间隔
- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout minimumInteritemSpacingForSectionAtIndex:(NSInteger)section;
//返回组内头视图的size
- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout referenceSizeForHeaderInSection:(NSInteger)section;
//返回组内尾视图的size
- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout referenceSizeForFooterInSection:(NSInteger)section;

@end

//如果不使用代理也可以使用固定的方法来设置布局，通常在布局都是统一的情况下使用
NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionViewFlowLayout : UICollectionViewLayout
// 行间距,也可以通过collectionView: layout:minimumLineSpacingForSectionAtIndex:
//设置单元格上下间距,eg:[layout setMinimumLineSpacing:0];
@property (nonatomic) CGFloat minimumLineSpacing;
// 设置单元格所有间距,eg:[layout setMinimumInteritemSpacing:0];
@property (nonatomic) CGFloat minimumInteritemSpacing;
// 定义每一个item的大小。通过设定itemSize可以全局地改变所有cell的尺寸，如果想要对某个cell制定尺寸，
//可以使用-collectionView:layout:sizeForItemAtIndexPath:方法。
//设置单元格高度、宽度
@property (nonatomic) CGSize itemSize;
//宽高预估值
@property (nonatomic) CGSize estimatedItemSize NS_AVAILABLE_IOS(8_0); // defaults to CGSizeZero - setting a non-zero size enables cells that self-size via -preferredLayoutAttributesFittingAttributes:
// 滚动方向，默认是水平
// UICollectionViewScrollDirectionVertical
// UICollectionViewScrollDirectionHorizontal
//设置集视图的滚动方向，默认垂直滚动，可设置水平滚动
@property (nonatomic) UICollectionViewScrollDirection scrollDirection; // default is UICollectionViewScrollDirectionVertical
// 根据滚动方向不同，header和footer的高和宽中只有一个会起作用。
// 垂直滚动时section间宽度为该尺寸的高，而水平滚动时为宽度起作用，
//组内头视图的宽高
@property (nonatomic) CGSize headerReferenceSize;
//组内尾视图的宽高
@property (nonatomic) CGSize footerReferenceSize;
//设置整组上左下右边距
@property (nonatomic) UIEdgeInsets sectionInset;

// Set these properties to YES to get headers that pin to the top of the screen and footers that pin to the bottom while scrolling (similar to UITableView).
/*
 默认NO，设置每组组头和组尾是否在整组滚动出屏幕外后随之消失或者固定组头或组尾。
 例如：一个可向上滚动的多组集视图在向上滚动视图并且第0组全部单元还未完全消失的情况下该组的组头始终显示在集视图的Frame顶部。尾部设置同理，但是主要体现在集视图Frame最下方。
 */
@property (nonatomic) BOOL sectionHeadersPinToVisibleBounds NS_AVAILABLE_IOS(9_0);
@property (nonatomic) BOOL sectionFootersPinToVisibleBounds NS_AVAILABLE_IOS(9_0);

@end

NS_ASSUME_NONNULL_END
