/* CoreGraphics - CGGeometry.h
 Copyright (c) 1998-2011 Apple Inc.
 All rights reserved. */

#ifndef CGGEOMETRY_H_
#define CGGEOMETRY_H_

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Points. */
//定义一个点，设置x坐标和y坐标
struct CGPoint {
    CGFloat x;
    CGFloat y;
};
typedef struct CGPoint CGPoint;

/* Sizes. */
//定义一个尺寸，设置宽度和高度
struct CGSize {
    CGFloat width;
    CGFloat height;
};
typedef struct CGSize CGSize;

/* Vectors. */
//定义一个二维矢量
#define CGVECTOR_DEFINED 1

struct CGVector {
    CGFloat dx;
    CGFloat dy;
};
typedef struct CGVector CGVector;

/* Rectangles. */
//定义一个矩形
struct CGRect {
    CGPoint origin;
    CGSize size;
};
typedef struct CGRect CGRect;

/* Rectangle edges. */

typedef CF_ENUM(uint32_t, CGRectEdge) {
    CGRectMinXEdge, CGRectMinYEdge, CGRectMaxXEdge, CGRectMaxYEdge
};

/* The "zero" point -- equivalent to CGPointMake(0, 0). */
//零点，与CGPointMake(0, 0)等效
CG_EXTERN const CGPoint CGPointZero
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* The "zero" size -- equivalent to CGSizeMake(0, 0). */
//零尺寸，与CGSizeMake(0, 0)等效
CG_EXTERN const CGSize CGSizeZero
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* The "zero" rectangle -- equivalent to CGRectMake(0, 0, 0, 0). */
//零矩形，与CGRectMake(0, 0, 0, 0)等效
CG_EXTERN const CGRect CGRectZero
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* The "empty" rect. This is the rectangle returned when, for example, we
 intersect two disjoint rectangles. Note that the null rect is not the
 same as the zero rect. */
//空矩形，这个和零矩形并不相同，当我们返回两个不相交矩形的交集时，会返回空矩形。
CG_EXTERN const CGRect CGRectNull
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* The infinite rectangle. */
//无限的矩形
CG_EXTERN const CGRect CGRectInfinite
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Make a point from `(x, y)'. */
//创建一个点
CG_INLINE CGPoint CGPointMake(CGFloat x, CGFloat y);

/* Make a size from `(width, height)'. */
//创建一个尺寸
CG_INLINE CGSize CGSizeMake(CGFloat width, CGFloat height);

/* Make a vector from `(dx, dy)'. */
//创建一个矢量
CG_INLINE CGVector CGVectorMake(CGFloat dx, CGFloat dy);

/* Make a rect from `(x, y; width, height)'. */
//创建一个矩形
CG_INLINE CGRect CGRectMake(CGFloat x, CGFloat y, CGFloat width,
                            CGFloat height);

/* Return the leftmost x-value of `rect'. */
//获得矩形最左边的x值
CG_EXTERN CGFloat CGRectGetMinX(CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the midpoint x-value of `rect'. */
//获取矩形中点的x值
CG_EXTERN CGFloat CGRectGetMidX(CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the rightmost x-value of `rect'. */
//获取矩形最右端的x值
CG_EXTERN CGFloat CGRectGetMaxX(CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the bottommost y-value of `rect'. */
//获取矩形最上端的y值
CG_EXTERN CGFloat CGRectGetMinY(CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the midpoint y-value of `rect'. */
//获取矩形中心点的y值
CG_EXTERN CGFloat CGRectGetMidY(CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the topmost y-value of `rect'. */
//获取矩形最下端的y值
CG_EXTERN CGFloat CGRectGetMaxY(CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the width of `rect'. */
//获取矩形宽度
CG_EXTERN CGFloat CGRectGetWidth(CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the height of `rect'. */
//获取矩形高度
CG_EXTERN CGFloat CGRectGetHeight(CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `point1' and `point2' are the same, false otherwise. */
//判断两个点是否相等
CG_EXTERN bool CGPointEqualToPoint(CGPoint point1, CGPoint point2)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `size1' and `size2' are the same, false otherwise. */
//判断两个尺寸是否相等
CG_EXTERN bool CGSizeEqualToSize(CGSize size1, CGSize size2)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `rect1' and `rect2' are the same, false otherwise. */
//判断两个矩形是否相等
CG_EXTERN bool CGRectEqualToRect(CGRect rect1, CGRect rect2)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Standardize `rect' -- i.e., convert it to an equivalent rect which has
 positive width and height. */
//根据一个矩形创建一个标准的矩形
CG_EXTERN CGRect CGRectStandardize(CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `rect' is empty (that is, if it has zero width or height),
 false otherwise. A null rect is defined to be empty. */
//判断是否为零矩形
CG_EXTERN bool CGRectIsEmpty(CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `rect' is the null rectangle, false otherwise. */
//判断是否为空矩形
CG_EXTERN bool CGRectIsNull(CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `rect' is the infinite rectangle, false otherwise. */
//判断是否为无限矩形
CG_EXTERN bool CGRectIsInfinite(CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Inset `rect' by `(dx, dy)' -- i.e., offset its origin by `(dx, dy)', and
 decrease its size by `(2*dx, 2*dy)'. */
//创建一个内嵌的矩形，中心和rect参数的中心一样，dx，dy对应内嵌的宽度和高度
/*
 比如：CGRect rect=CGRectInset(CGRectMake(0,0,100, 100), 10, 10);
 会创建出的rect为（10，10，80，80），dx，dy也可以为负值，则是创建出来的矩形会大于原矩形范围。
 */
CG_EXTERN CGRect CGRectInset(CGRect rect, CGFloat dx, CGFloat dy)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Expand `rect' to the smallest rect containing it with integral origin and
 size. */
//根据一个矩形，返回四个参数都是整数的矩形
CG_EXTERN CGRect CGRectIntegral(CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the union of `r1' and `r2'. */
//返回两个矩形的并集
CG_EXTERN CGRect CGRectUnion(CGRect r1, CGRect r2)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the intersection of `r1' and `r2'. This may return a null rect. */
//返回两个矩形的交集，如果没有交集，返回空矩形
CG_EXTERN CGRect CGRectIntersection(CGRect r1, CGRect r2)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Offset `rect' by `(dx, dy)'. */
//返回一个矩形，偏移量相对于rect
CG_EXTERN CGRect CGRectOffset(CGRect rect, CGFloat dx, CGFloat dy)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Make two new rectangles, `slice' and `remainder', by dividing `rect' with
 a line that's parallel to one of its sides, specified by `edge' -- either
 `CGRectMinXEdge', `CGRectMinYEdge', `CGRectMaxXEdge', or
 `CGRectMaxYEdge'. The size of `slice' is determined by `amount', which
 measures the distance from the specified edge. */
//这个函数用来分割矩形，参数rect是源矩形，slice和remainder是分割后的两部分矩形，amount是分割线，edge是分割选项。
/*
 注意：1、edge是一个宏，定义了分割的方式如下：
 typedef CF_ENUM(uint32_t, CGRectEdge) {
     //从x的最小处进行垂直分割
     CGRectMinXEdge,
     //从y的最小处进行水平分割
     CGRectMinYEdge,
     //从x最大处进行垂直分割
     CGRectMaxXEdge,
     //从y最大处进行水平分割
     CGRectMaxYEdge
 };
 2、slice和remainder是地址。
 3、举例如下，将会分割出两个矩形分别为(40,0,60,100)(0,0,40,100);
     CGRect rect = CGRectMake(0, 0, 100, 100);
     CGRect slice ;
     CGRect remainder;
     CGRectDivide(rect, &slice, &remainder, 60, CGRectMaxXEdge);
 */
CG_EXTERN void CGRectDivide(CGRect rect, CGRect *  slice,
                            CGRect *  remainder, CGFloat amount, CGRectEdge edge)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `point' is contained in `rect', false otherwise. */
//判断点是否在矩形内
CG_EXTERN bool CGRectContainsPoint(CGRect rect, CGPoint point)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `rect2' is contained in `rect1', false otherwise. `rect2'
 is contained in `rect1' if the union of `rect1' and `rect2' is equal to
 `rect1'. */
//判断矩形1是否包含矩形2
CG_EXTERN bool CGRectContainsRect(CGRect rect1, CGRect rect2)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `rect1' intersects `rect2', false otherwise. `rect1'
 intersects `rect2' if the intersection of `rect1' and `rect2' is not the
 null rect. */
//判断矩形1和矩形2是否相交
CG_EXTERN bool CGRectIntersectsRect(CGRect rect1, CGRect rect2)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/*** Persistent representations. ***/

/* Return a dictionary representation of `point'. */
//返回一个表示点的字典
CG_EXTERN CFDictionaryRef  CGPointCreateDictionaryRepresentation(
                                                                 CGPoint point)
CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Make a CGPoint from the contents of `dict' (presumably returned earlier
 from `CGPointCreateDictionaryRepresentation') and store the value in
 `point'. Returns true on success; false otherwise. */
//将字典转换为点
CG_EXTERN bool CGPointMakeWithDictionaryRepresentation(
                                                       CFDictionaryRef cg_nullable dict, CGPoint * cg_nullable point)
CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return a dictionary representation of `size'. */
//返回一个表示尺寸的字典
CG_EXTERN CFDictionaryRef  CGSizeCreateDictionaryRepresentation(CGSize size)
CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Make a CGSize from the contents of `dict' (presumably returned earlier
 from `CGSizeCreateDictionaryRepresentation') and store the value in
 `size'. Returns true on success; false otherwise. */
//将字典转换为尺寸
CG_EXTERN bool CGSizeMakeWithDictionaryRepresentation(
                                                      CFDictionaryRef cg_nullable dict, CGSize * cg_nullable size)
CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return a dictionary representation of `rect'. */
//返回一个表示矩形的字典
CG_EXTERN CFDictionaryRef  CGRectCreateDictionaryRepresentation(CGRect)
CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Make a CGRect from the contents of `dict' (presumably returned earlier
 from `CGRectCreateDictionaryRepresentation') and store the value in
 `rect'. Returns true on success; false otherwise. */
//将字典转化为矩形
CG_EXTERN bool CGRectMakeWithDictionaryRepresentation(
                                                      CFDictionaryRef cg_nullable dict, CGRect * cg_nullable rect)
CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/*** Definitions of inline functions. ***/

CG_INLINE CGPoint
CGPointMake(CGFloat x, CGFloat y)
{
    CGPoint p; p.x = x; p.y = y; return p;
}

CG_INLINE CGSize
CGSizeMake(CGFloat width, CGFloat height)
{
    CGSize size; size.width = width; size.height = height; return size;
}

CG_INLINE CGVector
CGVectorMake(CGFloat dx, CGFloat dy)
{
    CGVector vector; vector.dx = dx; vector.dy = dy; return vector;
}

CG_INLINE CGRect
CGRectMake(CGFloat x, CGFloat y, CGFloat width, CGFloat height)
{
    CGRect rect;
    rect.origin.x = x; rect.origin.y = y;
    rect.size.width = width; rect.size.height = height;
    return rect;
}

CG_INLINE bool
__CGPointEqualToPoint(CGPoint point1, CGPoint point2)
{
    return point1.x == point2.x && point1.y == point2.y;
}
#define CGPointEqualToPoint __CGPointEqualToPoint

CG_INLINE bool
__CGSizeEqualToSize(CGSize size1, CGSize size2)
{
    return size1.width == size2.width && size1.height == size2.height;
}

#define CGSizeEqualToSize __CGSizeEqualToSize

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGGEOMETRY_H_ */
