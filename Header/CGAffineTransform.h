/* CoreGraphics - CGAffineTransform.h
 Copyright (c) 1998-2011 Apple Inc.
 All rights reserved. */

#ifndef CGAFFINETRANSFORM_H_
#define CGAFFINETRANSFORM_H_

typedef struct CGAffineTransform CGAffineTransform;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGGeometry.h>
//固定桥接
//对于ARC来说，最让人迷惑和容易出错的地方大概就是桥接的概念。由于历史原因，CF对象和NSObject对象的转换一直存在一些微妙的关系，而在引入ARC之后，这些关系变得复杂起来：主要是要明确到底应该是由CF还是由NSObject来负责内存管理的问题。
//在Xcode4.4之后，之前区分到底谁拥有对象的工作可以模糊化了。在代码块区间加上CF_IMPLICIT_BRIDGING_ENABLED和CF_IMPLICIT_BRIDGING_DISABLED，在之前的桥接转换就都可以简单地写作CF和NS之间的强制转换，而不再需要加上__bridging的关键字了。谁来管这块内存呢？交给系统去头疼吧～
CF_IMPLICIT_BRIDGING_ENABLED

struct CGAffineTransform {
    CGFloat a, b, c, d;
    CGFloat tx, ty;
};

/* The identity transform: [ 1 0 0 1 0 0 ]. */
//清空所有的设置的transform(一般和动画配合使用，只能使用于transfofrm设置的画面)
CG_EXTERN const CGAffineTransform CGAffineTransformIdentity
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the transform [ a b c d tx ty ]. */
//直接生成一个新的CGAffineTransform
CG_EXTERN CGAffineTransform CGAffineTransformMake(CGFloat a, CGFloat b,
                                                  CGFloat c, CGFloat d, CGFloat tx, CGFloat ty)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return a transform which translates by `(tx, ty)':
 t' = [ 1 0 0 1 tx ty ] */
//在一个CGAffineTransform的基础上通过(tx, ty)实现平移。矩阵的六个参数为t' = [1，0，0，1，tx，ty] ;代入公式，xn=x+tx,yn=y+ty。
CG_EXTERN CGAffineTransform CGAffineTransformMakeTranslation(CGFloat tx,
                                                             CGFloat ty) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return a transform which scales by `(sx, sy)':
 t' = [ sx 0 0 sy 0 0 ] */
//在一个CGAffineTransform的基础上通过(sx, sy)实现缩放。矩阵的六个参数为t' = [ sx 0 0 sy 0 0 ] ;代入公式，xn=(sx)*x,yn=(sy)*y。
CG_EXTERN CGAffineTransform CGAffineTransformMakeScale(CGFloat sx, CGFloat sy)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return a transform which rotates by `angle' radians:
 t' = [ cos(angle) sin(angle) -sin(angle) cos(angle) 0 0 ] */
//在一个CGAffineTransform的基础上通过angle实现旋转。矩阵的六个参数为t' = [ cos(angle) sin(angle) -sin(angle) cos(angle) 0 0 ]
CG_EXTERN CGAffineTransform CGAffineTransformMakeRotation(CGFloat angle)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `t' is the identity transform, false otherwise. */
//判断是否是CGAffineTransformIdentity，返回bool值
CG_EXTERN bool CGAffineTransformIsIdentity(CGAffineTransform t)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Translate `t' by `(tx, ty)' and return the result:
 t' = [ 1 0 0 1 tx ty ] * t */
//在t的基础上通过(tx, ty)实现平移。矩阵的六个参数为t' = [1，0，0，1，tx，ty] ;代入公式，xn=x+tx,yn=y+ty。
CG_EXTERN CGAffineTransform CGAffineTransformTranslate(CGAffineTransform t,
                                                       CGFloat tx, CGFloat ty) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Scale `t' by `(sx, sy)' and return the result:
 t' = [ sx 0 0 sy 0 0 ] * t */
//在t基础上通过(sx, sy)实现缩放。矩阵的六个参数为t' = [ sx 0 0 sy 0 0 ] ;代入公式，xn=(sx)*x,yn=(sy)*y。
CG_EXTERN CGAffineTransform CGAffineTransformScale(CGAffineTransform t,
                                                   CGFloat sx, CGFloat sy) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Rotate `t' by `angle' radians and return the result:
 t' =  [ cos(angle) sin(angle) -sin(angle) cos(angle) 0 0 ] * t */
//在t的基础上通过angle实现旋转。矩阵的六个参数为t' = [ cos(angle) sin(angle) -sin(angle) cos(angle) 0 0 ]
CG_EXTERN CGAffineTransform CGAffineTransformRotate(CGAffineTransform t,
                                                    CGFloat angle) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Invert `t' and return the result. If `t' has zero determinant, then `t'
 is returned unchanged. */
/*反向的仿射矩阵比如（x，y）通过矩阵t得到了（x',y'）那么通过这个函数生成的t'作用与（x',y'）就能得到原始的(x,y).
 设 t1=CGAffineTransformInvert(t). 则若t产生放大的效果，t1产生缩小的效果。若t产生左移的效果，则t1产生右移的效果。。。
 若t有零行列式则不会产生变化
 */
CG_EXTERN CGAffineTransform CGAffineTransformInvert(CGAffineTransform t)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Concatenate `t2' to `t1' and return the result:
 t' = t1 * t2 */
//通过两个已经存在的放射矩阵生成一个新的矩阵t' = t1 * t2.就是把两种变化效果联系起来，有个动态的过渡过程
CG_EXTERN CGAffineTransform CGAffineTransformConcat(CGAffineTransform t1,
                                                    CGAffineTransform t2) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return true if `t1' and `t2' are equal, false otherwise. */
//判断两个仿射矩阵是否相等，返回布尔值
CG_EXTERN bool CGAffineTransformEqualToTransform(CGAffineTransform t1,
                                                 CGAffineTransform t2) CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Transform `point' by `t' and return the result:
 p' = p * t
 where p = [ x y 1 ]. */
/*
 在CGPoint结构上执行变换操作。p' = p * t  , where p = [ x y 1 ].
 相当于点p在第一象限，进行的变换操作。
 eg: t的效果是旋转180度，则p(x,y) ---> p'(-x,-y);
 t的效果是旋转90度， 则p(x,y) ---> p'(-y,x);
 t的效果是水平向左移动100，则p(x,y) ---> p'(x+100,y);
 t的效果是水平放大两倍，则p(x,y)--->p'(2*x,y);
 */
CG_EXTERN CGPoint CGPointApplyAffineTransform(CGPoint point,
                                              CGAffineTransform t) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Transform `size' by `t' and return the result:
 s' = s * t
 where s = [ width height 0 ]. */
//效果同上
CG_EXTERN CGSize CGSizeApplyAffineTransform(CGSize size, CGAffineTransform t)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Transform `rect' by `t' and return the result. Since affine transforms do
 not preserve rectangles in general, this function returns the smallest
 rectangle which contains the transformed corner points of `rect'. If `t'
 consists solely of scales, flips and translations, then the returned
 rectangle coincides with the rectangle constructed from the four
 transformed corners. */
/*
 CGRect rect=CGRectMake(x, y, width, height)
 若t的效果是放大缩小a倍：则rect‘＝CGRectMake(x*a, y*a, width*a, height*a)
 若t的效果是移动，例如水平移动100：则rect‘＝CGRectMake(x＋100, y+100, width, height)
 ...
 */
CG_EXTERN CGRect CGRectApplyAffineTransform(CGRect rect, CGAffineTransform t)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/*** Definitions of inline functions. ***/

CG_INLINE CGAffineTransform
__CGAffineTransformMake(CGFloat a, CGFloat b, CGFloat c, CGFloat d,
                        CGFloat tx, CGFloat ty)
{
    CGAffineTransform t;
    t.a = a; t.b = b; t.c = c; t.d = d; t.tx = tx; t.ty = ty;
    return t;
}
//CGPointApplyAffineTransform 的计算方法
//CGSizeApplyAffineTransform 的计算方法。CGRectApplyAffineTransform是两者的结合
#define CGAffineTransformMake __CGAffineTransformMake

CG_INLINE CGPoint
__CGPointApplyAffineTransform(CGPoint point, CGAffineTransform t)
{
    CGPoint p;
    p.x = (CGFloat)((double)t.a * point.x + (double)t.c * point.y + t.tx);
    p.y = (CGFloat)((double)t.b * point.x + (double)t.d * point.y + t.ty);
    return p;
}
#define CGPointApplyAffineTransform __CGPointApplyAffineTransform

CG_INLINE CGSize
__CGSizeApplyAffineTransform(CGSize size, CGAffineTransform t)
{
    CGSize s;
    s.width = (CGFloat)((double)t.a * size.width + (double)t.c * size.height);
    s.height = (CGFloat)((double)t.b * size.width + (double)t.d * size.height);
    return s;
}
#define CGSizeApplyAffineTransform __CGSizeApplyAffineTransform

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGAFFINETRANSFORM_H_ */

简介
CGAffineTransform实际上是一个矩阵,称仿射变换矩阵。
transform是view的一个重要属性,它在矩阵层面上改变view的显示状态,能实现view的缩放、旋转、平移等功能。transform是CGAffineTransform类型的。使用transform后view的frame被真实改变的。

struct CGAffineTransform {
    　　CGFloat a, b, c, d;
    　　CGFloat tx, ty;
    　　};
其中a,d表示放大缩小有关 //a表示width放大缩小的倍数，d表示height放大缩小的倍数
b,c和选择角度有关
tx,ty是和平移有关 //tx表示水平移动 ty表示垂直移动

在view可以看做有很多像素块构成，可以用(x,y)代表一个像素块，x为宽，y为高。transform就是改变每个像素块的形状。在运算过程中，[x,y,1]表示原来的像素块，而新的像素块[xn,yn,1]是由[x,y,1]乘以矩阵
　　{
    　　a, b, 0
    　　c, d, 0
    　　tx,ty,1
    　　}生成的。化简矩阵相乘，公式为
　　xn=ax+cy+tx;
　　yn=bx+dy+ty;
　　这个矩阵的第三列是固定的，所以每次变换时，只需传入前两列的六个参数[a,b,c,d,tx,ty]即可。
　　在CGAffineTransform的生成函数中，大多是两两对应的，一个带make字样，一个没有。带make字样的是直接生成一个新的CGAffineTransform，没有make字样的则是在一个CGAffineTransform的基础上生成新的。
　　函数返回值均是CGAffineTransform类型。
　 //  1:实现的是放大和缩小，在原来transform的基础上生成一个新的transform。生成新的transform相当于将t' = [sx,0,0,sy,0,0]这六个参数代入
矩阵中。则矩阵为[
         　　sx,0 ,0
         　　0 ,sy,0
         　　0 ,0 ,1
         　　];代入公式中，xn=(sx)*x,yn=(sy)*y。所以sx,sy分别代表x轴与y轴上的放大倍数。
　　CGAffineTransformScale(CGAffineTransform t,
                         　　CGFloat sx, CGFloat sy);
　　CGAffineTransformMakeScale(CGFloat sx, CGFloat sy);
　 //  2:实现的是旋转。angle为角度，angle=π则旋转180度。矩阵的六个参数为t' = [cos(angle),sin(angle),-sin(angle),cos(angle),0,0];
　　CGAffineTransformRotate(CGAffineTransform t,
                          　　CGFloat angle)
　　CGAffineTransformMakeRotation(CGFloat angle);

//  3:实现的是平移。矩阵的六个参数为t' = [1，0，0，1，tx，ty] ;代入公式，xn=x+tx,yn=y+ty。
　　CGAffineTransformTranslate(CGAffineTransform t,
                             　　CGFloat tx, CGFloat ty);
　　CGAffineTransformMakeTranslation(CGFloat tx,
                                   　　CGFloat ty);
*/

/*
 顺便记录一些常量，以后用的着！
 #define M_E         2.71828182845904523536028747135266250    e
 #define M_LOG2E     1.44269504088896340735992468100189214    log2(e)
 #define M_LOG10E    0.434294481903251827651128918916605082   log10(e)
 #define M_LN2       0.693147180559945309417232121458176568   loge(2)
 #define M_LN10      2.30258509299404568401799145468436421    loge(10)
 #define M_PI        3.14159265358979323846264338327950288    pi
 #define M_PI_2      1.57079632679489661923132169163975144    pi/2
 #define M_PI_4      0.785398163397448309615660845819875721   pi/4
 #define M_1_PI      0.318309886183790671537767526745028724   1/pi
 #define M_2_PI      0.636619772367581343075535053490057448   2/pi
 #define M_2_SQRTPI  1.12837916709551257389615890312154517    2/sqrt(pi)
 #define M_SQRT2     1.41421356237309504880168872420969808    sqrt(2)
 #define M_SQRT1_2   0.707106781186547524400844362104849039   1/sqrt(2)
 */
