//
//  UIBezierPath.h
//  UIKit
//
//  Copyright (c) 2009-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
/*
 使用UIBezierPath类可以创建基于矢量的路径，这个类在UIKit中。此类是Core Graphics框架关于path的一个封装。使用此类可以定义简单的形状，如椭圆或者矩形，或者有多个直线和曲线段组成的形状。   UIBezierPath对象是CGPathRef数据类型的封装。path如果是基于矢量形状的，都用直线和曲线段去创建。我们使用直线段去创建矩形和多边形，使用曲线段去创建弧（arc），圆或者其他复杂的曲线形状。每一段都包括一个或者多个点，绘图命令定义如何去诠释这些点。每一个直线段或者曲线段的结束的地方是下一个的开始的地方。每一个连接的直线或者曲线段的集合成为subpath。一个UIBezierPath对象定义一个完整的路径包括一个或者多个subpaths。
 UIBezierPath的好处:首先它是OC语言的，相对于c语言的Core Graphics来说更为平易近人。 * 其次它能够使用ARC，如果我们直接使用CGPathRef的话，还要自己负责在合适的时候释放。
 */
NS_ASSUME_NONNULL_BEGIN
//渲染的角
typedef NS_OPTIONS(NSUInteger, UIRectCorner) {
    UIRectCornerTopLeft     = 1 << 0,
    UIRectCornerTopRight    = 1 << 1,
    UIRectCornerBottomLeft  = 1 << 2,
    UIRectCornerBottomRight = 1 << 3,
    UIRectCornerAllCorners  = ~0UL
};

NS_CLASS_AVAILABLE_IOS(3_2) @interface UIBezierPath : NSObject<NSCopying, NSCoding>
// 创建path
/*
 //1.画条线
 // 创建path
 UIBezierPath*path1=[UIBezierPath bezierPath];
 //添加路径的起点
 [path1 moveToPoint:CGPointMake(10, 10)];
 //路径设置为一条线并设置线的终点
 [path1 addLineToPoint:CGPointMake(100, 10)];
 // 设置描边色
 [[UIColor magentaColor] setStroke];
 //将path绘制出来
 [path1 stroke];
 */
+ (instancetype)bezierPath;
/*
 //2.根据一个矩形画曲线
 UIBezierPath*path1=[UIBezierPath bezierPathWithRect:CGRectMake(10, 10, 100, 100)];
 //设置描边色
 [[UIColor blueColor]setStroke];
 //将path绘制出来
 [path1 stroke];
 */
+ (instancetype)bezierPathWithRect:(CGRect)rect;
/*
 //3.根据矩形框的内切圆画曲线(画出的是圆形)
 UIBezierPath*path1=[UIBezierPath bezierPathWithOvalInRect:CGRectMake(10, 10, 100, 100)];
 [[UIColor brownColor]setStroke];
 [path1 stroke];
 */
+ (instancetype)bezierPathWithOvalInRect:(CGRect)rect;
/*
 //4.根据矩形画带圆角的曲线 ，四个角的圆角弧度一样
 UIBezierPath*path1=[UIBezierPath bezierPathWithRoundedRect:CGRectMake(10, 10, 100, 100) cornerRadius:5.0f];
 [[UIColor greenColor]setStroke];
 [path1 stroke];
 */
+ (instancetype)bezierPathWithRoundedRect:(CGRect)rect cornerRadius:(CGFloat)cornerRadius; // rounds all corners with the same horizontal and vertical radius
/*
 //5.在矩形中，可以针对四角中的某个角加圆角(参数：corners:枚举值，可以选择某个角。cornerRadii:圆角的大小)
 UIBezierPath*path1=[UIBezierPath bezierPathWithRoundedRect:CGRectMake(10, 10, 100, 100) byRoundingCorners:(UIRectCornerTopLeft|UIRectCornerTopRight) cornerRadii:CGSizeMake(10, 10)];
 [[UIColor greenColor]setStroke];
 [path1 stroke];
 */
+ (instancetype)bezierPathWithRoundedRect:(CGRect)rect byRoundingCorners:(UIRectCorner)corners cornerRadii:(CGSize)cornerRadii;
/*
 //6.以某个中心点画弧线(参数：center:弧线中心点的坐标。radius:弧线所在圆的半径。startAngle:弧线开始的角度值。endAngle:弧线结束的角
 度值。clockwise:是否顺时针画弧线)
 //M_PI 代表pi ,M_PI_2代表pi/2 ,M_PI_4代表pi/4
 UIBezierPath*path1=[UIBezierPath bezierPathWithArcCenter:self.center radius:50.0f startAngle:0 endAngle:M_PI clockwise:YES];
 [[UIColor purpleColor]setStroke];
 [path1 stroke];
 */
+ (instancetype)bezierPathWithArcCenter:(CGPoint)center radius:(CGFloat)radius startAngle:(CGFloat)startAngle endAngle:(CGFloat)endAngle clockwise:(BOOL)clockwise;
+ (instancetype)bezierPathWithCGPath:(CGPathRef)CGPath;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

// Returns an immutable CGPathRef which is only valid until the UIBezierPath is further mutated.
// Setting the path will create an immutable copy of the provided CGPathRef, so any further mutations on a provided CGMutablePathRef will be ignored.
@property(nonatomic) CGPathRef CGPath;
- (CGPathRef)CGPath NS_RETURNS_INNER_POINTER CF_RETURNS_NOT_RETAINED;

// Path construction
//添加路径的起点
- (void)moveToPoint:(CGPoint)point;
//路径设置为一条线并设置线的终点
- (void)addLineToPoint:(CGPoint)point;
//以三个点画一段曲线，一般和moveToPoint配合使用(参数：endPoint:曲线的终点。controlPoint1:画曲线的第一个基准点。controlPoint2:画曲线的第二个基准点。)
- (void)addCurveToPoint:(CGPoint)endPoint controlPoint1:(CGPoint)controlPoint1 controlPoint2:(CGPoint)controlPoint2;
//添加二阶贝塞尔曲线.画二元曲线，一般和moveToPoint配合使用(参数：endPoint:曲线的终点。controlPoint:画曲线的基准点)
- (void)addQuadCurveToPoint:(CGPoint)endPoint controlPoint:(CGPoint)controlPoint;
//添加三阶贝塞尔曲线,画圆弧
- (void)addArcWithCenter:(CGPoint)center radius:(CGFloat)radius startAngle:(CGFloat)startAngle endAngle:(CGFloat)endAngle clockwise:(BOOL)clockwise NS_AVAILABLE_IOS(4_0);
- (void)closePath;

- (void)removeAllPoints;

// Appending paths

- (void)appendPath:(UIBezierPath *)bezierPath;

// Modified paths

- (UIBezierPath *)bezierPathByReversingPath NS_AVAILABLE_IOS(6_0);

// Transforming paths

- (void)applyTransform:(CGAffineTransform)transform;

// Path info

@property(readonly,getter=isEmpty) BOOL empty;
@property(nonatomic,readonly) CGRect bounds;
@property(nonatomic,readonly) CGPoint currentPoint;
- (BOOL)containsPoint:(CGPoint)point;

// Drawing properties
//线条宽度
@property(nonatomic) CGFloat lineWidth;
//线端点类型
@property(nonatomic) CGLineCap lineCapStyle;
//线连接类型
@property(nonatomic) CGLineJoin lineJoinStyle;
@property(nonatomic) CGFloat miterLimit; // Used when lineJoinStyle is kCGLineJoinMiter
@property(nonatomic) CGFloat flatness;
@property(nonatomic) BOOL usesEvenOddFillRule; // Default is NO. When YES, the even-odd fill rule is used for drawing, clipping, and hit testing.

- (void)setLineDash:(nullable const CGFloat *)pattern count:(NSInteger)count phase:(CGFloat)phase;
- (void)getLineDash:(nullable CGFloat *)pattern count:(nullable NSInteger *)count phase:(nullable CGFloat *)phase;

// Path operations on the current graphics context
//填充
- (void)fill;
//描边（将path绘制出来）
- (void)stroke;

// These methods do not affect the blend mode or alpha of the current graphics context
- (void)fillWithBlendMode:(CGBlendMode)blendMode alpha:(CGFloat)alpha;
- (void)strokeWithBlendMode:(CGBlendMode)blendMode alpha:(CGFloat)alpha;

- (void)addClip;

@end

NS_ASSUME_NONNULL_END




应用举例
1.设置矩形视图的某个角或某几个角为圆角
UIView*view=[[UIViewalloc]initWithFrame:CGRectMake(100,100,80,30)];
view.backgroundColor=[UIColorblackColor];
[self.viewaddSubview:view];
UIBezierPath *maskPath = [UIBezierPathbezierPathWithRoundedRect:view.boundsbyRoundingCorners:UIRectCornerTopRight |UIRectCornerBottomLeft cornerRadii:CGSizeMake(view.frame.size.width/3,view.frame.size.width/3)];
CAShapeLayer *maskLayer = [[CAShapeLayeralloc] init];
maskLayer.frame = view.bounds;
maskLayer.path = maskPath.CGPath;
view.layer.mask = maskLayer;
