//
//  UIScreen.h
//  UIKit
//
//  Copyright (c) 2007-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITraitCollection.h>
#import <UIKit/UIView.h>

NS_ASSUME_NONNULL_BEGIN

@class UIScreenMode, CADisplayLink, UIView;

// Object is the UIScreen that represents the new screen. Connection notifications are not sent for screens present when the application is first launched
UIKIT_EXTERN NSNotificationName const UIScreenDidConnectNotification NS_AVAILABLE_IOS(3_2);
// Object is the UIScreen that represented the disconnected screen.
UIKIT_EXTERN NSNotificationName const UIScreenDidDisconnectNotification NS_AVAILABLE_IOS(3_2);
// Object is the UIScreen which changed. [object currentMode] is the new UIScreenMode.
UIKIT_EXTERN NSNotificationName const UIScreenModeDidChangeNotification NS_AVAILABLE_IOS(3_2);
UIKIT_EXTERN NSNotificationName const UIScreenBrightnessDidChangeNotification NS_AVAILABLE_IOS(5_0);

// when the connected screen is overscanning, UIScreen can attempt to compensate for the overscan to avoid clipping
typedef NS_ENUM(NSInteger, UIScreenOverscanCompensation) {
    UIScreenOverscanCompensationScale,                           // the final composited framebuffer for the screen is scaled to avoid clipping
    UIScreenOverscanCompensationInsetBounds,                     // the screen's bounds will be inset in the framebuffer to avoid clipping. no scaling will occur
    UIScreenOverscanCompensationNone NS_ENUM_AVAILABLE_IOS(9_0), // no scaling will occur. use overscanCompensationInsets to determine the necessary insets to avoid clipping
    
    UIScreenOverscanCompensationInsetApplicationFrame NS_ENUM_DEPRECATED_IOS(5_0, 9_0, "Use UIScreenOverscanCompensationNone") = 2,
};

/*
 UIScreen对象定义了基于硬件显示的相关属性。iOS设备有一个主屏幕和零个或多个附带屏幕。tvOS设备有一个主屏幕，就是设备相连接的电视。使用这个类来获取每一个设备显示屏幕的对象。每一个屏幕对象定义了相关的边界矩形和其它有趣的属性，例如它的亮度。
 
 在iOS8之前，屏幕的bounds总能反映出屏幕尺寸，这个方向总是向上的，旋转设备和颠倒设备都不会改变。在iOS8之后，屏幕的bounds属性会被屏幕的方向而影响，这意味着设备的bounds在横屏的时候会不一样。如果App依赖于屏幕尺寸的话，可以使用fixedCoordinateSpace属性座位一个固定的参考点作为计算。
 
 当用户连接或断开一个显示iOS的设备，系统会发送通知给App，使用一个长生命周期的对象去监听它，例如AppDelegate。在任何时候都有可能收到连接和断开的通知，甚至在你的App后台运行着。如果你的App暂停通知到来后,通知再次排队，直到你的App开始前台运行，它就会被送到你的观察者对象那里。
 
 当你收到一个通知告诉你新的外部显示器已连接,你尽你所能去使用更多的屏幕空间。为了使用空间，你要创建一个窗口对象,分配新的屏幕的屏幕属性和去显示窗口。这样做会导致当你App前台运行时显示在窗口的内容。如果你不为额外的屏幕创建一个窗口,或者如果你创建一个窗口,但没有表现出来,一个黑色的字段显示在新的外部显示器。
 
 handling connect和disconnect notifications的通知告诉你两个简单处理通知的方法。连接处理的方法创建了一个二级窗口，将它与新连接的屏幕，询问其中一个应用程序的视图控制器(由自定义viewController属性)来添加一些内容的窗口，并显示它。断开处理的方法释放窗口和通知主要视图控制器，以便它可以相应地调整其界面。
 - (void)handleScreenConnectNotification:(NSNotification*)aNotification {
     UIScreen*    newScreen = [aNotification object];
     CGRect        screenBounds = newScreen.bounds;
     
     if (!_secondWindow) {
         _secondWindow = [[UIWindow alloc] initWithFrame:screenBounds];
         _secondWindow.screen = newScreen;
         
         //设置并显示初始界面窗口
         [self.viewController displaySelectionInSecondaryWindow:_secondWindow];
         [_secondWindow makeKeyAndVisible];
     }
 }
 
 - (void)handleScreenDisconnectNotification:(NSNotification*)aNotification {
     if (_secondWindow) {
         //隐藏和删除窗口
         _secondWindow.hidden = YES;
         [_secondWindow release];
         _secondWindow = nil;
         
         //更新主屏幕的显示
         [self.viewController displaySelectionOnMainScreen];
     }
 }
 
 配置外置屏幕显示模式:多个屏幕支持多个分辨率，有一些使用不同的分辨率。屏幕对象在默认情况下使用常用的现实模式，但是你可以改变这一模式以适配你的内容。例如，如果你使用OpenGL ES去编写你的游戏，而游戏是根据640*480去设计的，你可能需要更改屏幕模式。
 如果你打算使用一个非默认模式下的屏幕模式，在连接窗口之前你就应该更改完毕。UIScreenMode这个类定义一个单一的屏幕模式。你可以从它的availableModes属性中获取屏幕支持的模式列表，并在其中找到你所需要的模式。
 想了解更多的屏幕模式，请看UIScreenMode类的介绍

 */
NS_CLASS_AVAILABLE_IOS(2_0) @interface UIScreen : NSObject <UITraitEnvironment>

#if UIKIT_DEFINE_AS_PROPERTIES
//Returns an array containing all of the screens attached to the device.
//返回包含连接到设备的所有屏幕的数组。
@property(class, nonatomic, readonly) NSArray<UIScreen *> *screens NS_AVAILABLE_IOS(3_2);          // all screens currently attached to the device
//该设备的内部屏幕
@property(class, nonatomic, readonly) UIScreen *mainScreen;      // the device's internal screen
#else
+ (NSArray<UIScreen *> *)screens NS_AVAILABLE_IOS(3_2);          // all screens currently attached to the device
+ (UIScreen *)mainScreen;      // the device's internal screen
#endif

@property(nonatomic,readonly) CGRect  bounds;                // Bounds of entire screen in points
//This value reflects the scale factor needed to convert from the default logical coordinate space into the device coordinate space of this screen. The default logical coordinate space is measured using points. For standard-resolution displays, the scale factor is 1.0 and one point equals one pixel. For Retina displays, the scale factor is 2.0 and one point is represented by four pixels.
//该值反映了将默认逻辑坐标空间转换为该屏幕的设备坐标空间所需的比例因子。 使用点测量默认逻辑坐标空间。 对于标准分辨率显示，比例因子为1.0，一点等于一个像素。 对于Retina显示，比例因子为2.0，一个点由四个像素表示。
//The natural scale factor associated with the screen. (read-only)
//与屏幕相关的自然比例因子。 （只读）
@property(nonatomic,readonly) CGFloat scale NS_AVAILABLE_IOS(4_0);
//The display modes that can be associated with the screen. (read-only)
//可以与屏幕相关联的显示模式数组。 （只读）
@property(nonatomic,readonly,copy) NSArray<UIScreenMode *> *availableModes NS_AVAILABLE_IOS(3_2) __TVOS_PROHIBITED;             // The list of modes that this screen supports
//The preferred display mode for the screen. (read-only)
//此屏幕的首选模式。 选择此模式可能会产生最佳效果
@property(nullable, nonatomic,readonly,strong) UIScreenMode *preferredMode NS_AVAILABLE_IOS(4_3) __TVOS_PROHIBITED;       // Preferred mode of this screen. Choosing this mode will likely produce the best results
#if TARGET_OS_TV
//The current screen mode associated with the screen.
@property(nullable,nonatomic,readonly,strong) UIScreenMode *currentMode NS_AVAILABLE_IOS(3_2);                  // Current mode of this screen
#else
@property(nullable,nonatomic,strong) UIScreenMode *currentMode NS_AVAILABLE_IOS(3_2);                  // Current mode of this screen
#endif
//For an external screen, this property sets the desired technique to compensate for overscan.
//对于外部屏幕，此属性设置所需的技术来补偿过扫描。
//默认为UIScreenOverscanCompensationScale。 确定连接的显示屏是否超扫描时屏幕的行为
@property(nonatomic) UIScreenOverscanCompensation overscanCompensation NS_AVAILABLE_IOS(5_0); // Default is UIScreenOverscanCompensationScale. Determines how the screen behaves if the connected display is overscanning
//The edge inset values needed to avoid clipping the rectangle. (read-only)
//边缘插入值，以避免剪切矩形。 （只读）
@property(nonatomic,readonly) UIEdgeInsets overscanCompensationInsets NS_AVAILABLE_IOS(9_0);  // The amount that should be inset to avoid clipping
//The screen being mirrored by an external display. (read-only)
//屏幕由外部显示器镜像。 （只读）
@property(nullable, nonatomic,readonly,strong) UIScreen *mirroredScreen NS_AVAILABLE_IOS(4_3);          // The screen being mirrored by the receiver. nil if mirroring is disabled or unsupported. Moving a UIWindow to this screen will disable mirroring
//The brightness level of the screen.
//屏幕亮度:0-1.0,1.0为最大值
@property(nonatomic) CGFloat brightness NS_AVAILABLE_IOS(5_0) __TVOS_PROHIBITED;        // 0 .. 1.0, where 1.0 is maximum brightness. Only supported by main screen.
//A Boolean value that indicates whether the screen may be dimmed lower than the hardware is normally capable of by emulating it in software.
//一个布尔值，指示屏幕是否可能比硬件更暗，通常可以通过软件进行仿真。
//默认为NO。 如果是，则必须使用低于硬件能力的亮度级别进行软件仿真。 启用后可能需要执行
@property(nonatomic) BOOL wantsSoftwareDimming NS_AVAILABLE_IOS(5_0) __TVOS_PROHIBITED; // Default is NO. If YES, brightness levels lower than that of which the hardware is capable are emulated in software, if neccessary. Having enabled may entail performance cost.
//The current coordinate space of the screen. (read-only)
//屏幕的当前坐标空间。 （只读）
//The screen’s current coordinate space always reflects any interface orientations applied to the device. Therefore, the bounds of this coordinate space match the bounds property of the screen itself.
//屏幕的当前坐标空间总是反映应用于设备的任何接口方向。 因此，该坐标空间的边界与屏幕本身的边界属性相匹配。
@property (readonly) id <UICoordinateSpace> coordinateSpace NS_AVAILABLE_IOS(8_0);
//The fixed coordinate space of the screen. (read-only)
//屏幕的固定坐标空间。 （只读）
//The bounds of this coordinate space always reflect the screen dimensions of the device in a portrait-up orientation. You can use this coordinate space in places where you need a fixed frame of reference. For example, if your app saves screen coordinate values to disk, convert those values to the fixed coordinate space before doing so. Saving them in the fixed coordinate space ensures that when your app reads the values later, it can convert them to the current coordinate space correctly.
//此坐标空间的范围始终以纵向向上反映设备的屏幕尺寸。 您可以在需要固定参考框架的地方使用此坐标空间。 例如，如果您的应用程序将屏幕坐标值保存到磁盘，则在执行此操作之前将这些值转换为固定坐标空间。 将它们保存在固定坐标空间中可确保当您的应用程序稍后读取值时，可以将它们正确地转换为当前的坐标空间。
@property (readonly) id <UICoordinateSpace> fixedCoordinateSpace NS_AVAILABLE_IOS(8_0);
//The bounding rectangle of the physical screen, measured in pixels. (read-only)
//物理屏幕的边界矩形，以像素为单位。即分辨率 （只读）eg:iPhone 7 Plus中 po [[UIScreen mainScreen] nativeBounds] 打印如下: (origin = (x = 0, y = 0), size = (width = 1242, height = 2208)) ;;;;; po [[UIScreen mainScreen] bounds] 打印如下:(origin = (x = 0, y = 0), size = (width = 414, height = 736));;;;;po [[UIScreen mainScreen] nativeScale] 打印如下:3
@property(nonatomic,readonly) CGRect  nativeBounds NS_AVAILABLE_IOS(8_0);  // Native bounds of the physical screen in pixels
//The native scale factor for the physical screen. (read-only)
//物理屏幕的原生比例因子。 （只读）
@property(nonatomic,readonly) CGFloat nativeScale  NS_AVAILABLE_IOS(8_0);  // Native scale factor of the physical screen
//Returns a display link object for the current screen.
//返回当前屏幕的显示链接对象。
//You use display link objects to synchronize your drawing code to the screen’s refresh rate. The newly constructed display link retains the target.
//您可以使用显示链接对象将绘图代码与画面的刷新率进行同步。 新建的显示链接保留目标。
- (nullable CADisplayLink *)displayLinkWithTarget:(id)target selector:(SEL)sel NS_AVAILABLE_IOS(4_0);
//屏幕最大刷新帧率
@property (readonly) NSInteger maximumFramesPerSecond  NS_AVAILABLE_IOS(10_3); // The maximumFramesPerSecond this screen is capable of

@property (nullable, nonatomic, weak, readonly) id<UIFocusItem> focusedItem NS_AVAILABLE_IOS(10_0);
//The view that is currently focused. (read-only)
//焦点视图。 （只读）
//如果focusedItem不是视图，则返回该项目包含的视图。 否则他们是平等的。
@property (nullable, nonatomic, weak, readonly) UIView *focusedView NS_AVAILABLE_IOS(9_0); // If focusedItem is not a view, this returns that item's containing view. Otherwise they are equal.
//A Boolean value that indicates whether the screen supports focus-based inputs. (read-only)
//一个布尔值，指示屏幕是否支持基于焦点的输入。 （只读）
@property (readonly, nonatomic) BOOL supportsFocus NS_AVAILABLE_IOS(9_0);
//同bounds
@property(nonatomic,readonly) CGRect applicationFrame NS_DEPRECATED_IOS(2_0, 9_0, "Use -[UIScreen bounds]") __TVOS_PROHIBITED;

@end

@interface UIScreen (UISnapshotting)
// Please see snapshotViewAfterScreenUpdates: in UIView.h for some important details on the behavior of this method when called from layoutSubviews.
//Returns a snapshot view based on the current screen contents.
//请参阅snapshotViewAfterScreenUpdates：在UIView.h中，从layoutSubviews调用此方法的行为的一些重要细节。
//根据当前屏幕内容返回快照视图。
- (UIView *)snapshotViewAfterScreenUpdates:(BOOL)afterUpdates NS_AVAILABLE_IOS(7_0);
@end

NS_ASSUME_NONNULL_END
