//
//  UIDevice.h
//  UIKit
//
//  Copyright (c) 2007-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIDeviceOrientation) {
    UIDeviceOrientationUnknown,
    // 设备垂直，home键在下
    UIDeviceOrientationPortrait,            // Device oriented vertically, home button on the bottom
    // 设备翻转，home键在上
    UIDeviceOrientationPortraitUpsideDown,  // Device oriented vertically, home button on the top
    // 设备水平，home件在左
    UIDeviceOrientationLandscapeLeft,       // Device oriented horizontally, home button on the right
    // 设备水平，home件在右
    UIDeviceOrientationLandscapeRight,      // Device oriented horizontally, home button on the left
    // 设备平放，面朝上
    UIDeviceOrientationFaceUp,              // Device oriented flat, face up
    // 设备平放，面朝下
    UIDeviceOrientationFaceDown             // Device oriented flat, face down
} __TVOS_PROHIBITED;

typedef NS_ENUM(NSInteger, UIDeviceBatteryState) {
    //无法取得充电状态情况
    UIDeviceBatteryStateUnknown,
    //使用电池,非充电状态
    UIDeviceBatteryStateUnplugged,   // on battery, discharging
    //充电状态,电池未满100%
    UIDeviceBatteryStateCharging,    // plugged in, less than 100%
    //充电状态,电池满100%
    UIDeviceBatteryStateFull,        // plugged in, at 100%
} __TVOS_PROHIBITED;              // available in iPhone 3.0

/*
 if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone)
 {
 // iPhone设备
 } else
 {
 // iPad 设备
 }
 */
//设备类型
typedef NS_ENUM(NSInteger, UIUserInterfaceIdiom) {
    //Used when an object has a trait collection, but it is not in an environment yet. For example, a view that is created, but not put into a view hierarchy.
    //当对象具有特征集合但不在环境中时使用。 例如，创建但不放入视图层次结构的视图。
    UIUserInterfaceIdiomUnspecified = -1,
    //The user interface should be designed for iPhone and iPod touch.
    //用户界面应设计为iPhone和iPod touch
    UIUserInterfaceIdiomPhone NS_ENUM_AVAILABLE_IOS(3_2), // iPhone and iPod touch style UI
    //The user interface should be designed for iPad.
    //用户界面应为iPad设计
    UIUserInterfaceIdiomPad NS_ENUM_AVAILABLE_IOS(3_2), // iPad style UI
    //The user interface should be designed for Apple TV.
    //用户界面应设计为Apple TV
    UIUserInterfaceIdiomTV NS_ENUM_AVAILABLE_IOS(9_0), // Apple TV style UI
    //The user interface should be designed for an in-car experience.
    //用户界面应设计为车载体验
    UIUserInterfaceIdiomCarPlay NS_ENUM_AVAILABLE_IOS(9_0), // CarPlay style UI
};

static inline BOOL UIDeviceOrientationIsPortrait(UIDeviceOrientation orientation)  __TVOS_PROHIBITED {
return ((orientation) == UIDeviceOrientationPortrait || (orientation) == UIDeviceOrientationPortraitUpsideDown);
}

static inline BOOL UIDeviceOrientationIsLandscape(UIDeviceOrientation orientation)  __TVOS_PROHIBITED {
return ((orientation) == UIDeviceOrientationLandscapeLeft || (orientation) == UIDeviceOrientationLandscapeRight);
}

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIDevice : NSObject

#if UIKIT_DEFINE_AS_PROPERTIES
@property(class, nonatomic, readonly) UIDevice *currentDevice;
#else
+ (UIDevice *)currentDevice;
#endif

@property(nonatomic,readonly,strong) NSString    *name;              // e.g. "My iPhone"
@property(nonatomic,readonly,strong) NSString    *model;             // e.g. @"iPhone", @"iPod touch"
// 本地化的设备模式
@property(nonatomic,readonly,strong) NSString    *localizedModel;    // localized version of model
@property(nonatomic,readonly,strong) NSString    *systemName;        // e.g. @"iOS"
@property(nonatomic,readonly,strong) NSString    *systemVersion;     // e.g. @"4.0"
// 返回当前的设备方向，如果还没有产生设备方向通知(设备方向未发生改变)的话返回UIDeviceOrientationUnknown
@property(nonatomic,readonly) UIDeviceOrientation orientation __TVOS_PROHIBITED;       // return current device orientation.  this will return UIDeviceOrientationUnknown unless device orientation notifications are being generated.
// 可用于唯一标识设备的一个UUID
@property(nullable, nonatomic,readonly,strong) NSUUID      *identifierForVendor NS_AVAILABLE_IOS(6_0);      // a UUID that may be used to uniquely identify the device, same across apps from a single vendor.

/*
 测试实例代码
     // 1.UIDevice
     UIDevice *device = [UIDevice currentDevice]; // 获取当前的device
 
     // 设备基本信息
    NSString *name = [device name];// @"iPhone 5S"
    NSString *model = [device model];// @"iPhone"
    NSString *localizedModel = [device localizedModel];// @"iPhone"
    NSString *systemName = [device systemName];// @"iPhone OS"
    NSString *systemVersion = [device systemVersion];// @"9.3.2"

    // 设备方向
    UIDeviceOrientation orientation = [device orientation]; // UIDeviceOrientationUnknown

    // 设备ID
    NSUUID *identifierForVendor = [device identifierForVendor];
 */
//A Boolean value that indicates whether the receiver generates orientation notifications (YES) or not (NO). (read-only)
//是否生成设备转向通知,YES才生成通知,通知在调用 beginGeneratingDeviceOrientationNotifications and endGeneratingDeviceOrientationNotifications方法中产生
@property(nonatomic,readonly,getter=isGeneratingDeviceOrientationNotifications) BOOL generatesDeviceOrientationNotifications __TVOS_PROHIBITED;
/*
 //获得设备状态栏方向
 UIInterfaceOrientation orientation = [[UIApplicationsharedApplication] statusBarOrientation];
 

 if (![UIDevice currentDevice].generatesDeviceOrientationNotifications) {
 [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
 }
 NSLog(@"%d",[UIDevice currentDevice].orientation);
 
 [[UIDevice currentDevice] endGeneratingDeviceOrientationNotifications];
 */
//Begins the generation of notifications of device orientation changes.
//开始生成设备转向通知
//You must call this method before attempting to get orientation data from the receiver. This method enables the device’s accelerometer hardware and begins the delivery of acceleration events to the receiver. The receiver subsequently uses these events to post UIDeviceOrientationDidChangeNotification notifications when the device orientation changes and to update the orientation property.
//You may nest calls to this method safely, but you should always match each call with a corresponding call to the endGeneratingDeviceOrientationNotifications method.
//在获取转向数据时,必须先调用这个方法去驱动应急生成加速器事件给接收者
//在尝试从接收器获取方向数据之前，您必须调用此方法。 该方法使设备的加速度计硬件开始向接收机传递加速事件。 接收者随后使用这些事件在设备方向更改时发布UIDeviceOrientationDidChangeNotification通知，并更新方向属性。
//您可以安全地将呼叫嵌套到此方法，但是您应该始终将每个呼叫与对EndGeneratingDeviceOrientationNotifications方法的相应调用相匹配。
- (void)beginGeneratingDeviceOrientationNotifications __TVOS_PROHIBITED;      // nestable
//Ends the generation of notifications of device orientation changes.
//This method stops the posting of UIDeviceOrientationDidChangeNotification notifications and notifies the system that it can power down the accelerometer hardware if it is not in use elsewhere. You call this method after a previous call to the beginGeneratingDeviceOrientationNotifications method.
//结束生成设备转向通知
//此方法停止发布UIDeviceOrientationDidChangeNotification通知，并通知系统如果加速度计硬件在其他地方没有使用，它可以关闭加速度计硬件。 在先前调用beginGeneratingDeviceOrientationNotifications方法之后调用此方法。
- (void)endGeneratingDeviceOrientationNotifications __TVOS_PROHIBITED;
/*
 UIDevice * device = [UIDevice currentDevice];
 device.batteryMonitoringEnabled = YES;
 //0.0-1.0取得失败的适合为-1.0
 NSLog(@"%f", device.batteryLevel);
 
 NSLog(@"%ld", (long)device.batteryState);
 //监视电池剩余电量
 [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(action1:) name:UIDeviceBatteryLevelDidChangeNotification object:nil];
 //监视充电状态
 [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(action2:) name:UIDeviceBatteryStateDidChangeNotification object:nil];
 */
//A Boolean value indicating whether battery monitoring is enabled (YES) or not (NO).
//是否允许监听电池
@property(nonatomic,getter=isBatteryMonitoringEnabled) BOOL batteryMonitoringEnabled NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;  // default is NO
//电池状态
@property(nonatomic,readonly) UIDeviceBatteryState          batteryState NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;  // UIDeviceBatteryStateUnknown if monitoring disabled
//电池剩余电量
@property(nonatomic,readonly) float                         batteryLevel NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;  // 0 .. 1.0. -1.0 if UIDeviceBatteryStateUnknown
//A Boolean value indicating whether proximity monitoring is enabled (YES) or not (NO).
//是否启动接近监控（例如接电话时脸靠近屏幕），默认为NO
@property(nonatomic,getter=isProximityMonitoringEnabled) BOOL proximityMonitoringEnabled NS_AVAILABLE_IOS(3_0); // default is NO
// 如果设备不具备接近感应器，则总是返回NO
@property(nonatomic,readonly)                            BOOL proximityState NS_AVAILABLE_IOS(3_0);  // always returns NO if no proximity detector
// 是否支持多任务
@property(nonatomic,readonly,getter=isMultitaskingSupported) BOOL multitaskingSupported NS_AVAILABLE_IOS(4_0);
// 当前用户界面模式
@property(nonatomic,readonly) UIUserInterfaceIdiom userInterfaceIdiom NS_AVAILABLE_IOS(3_2);
// 在点击屏幕上可视的可编辑输入框时播放一个输入的声音
- (void)playInputClick NS_AVAILABLE_IOS(4_2);  // Plays a click only if an enabling input view is on-screen and user has enabled input clicks.

@end

@protocol UIInputViewAudioFeedback <NSObject>
@optional
// 实现该方法，返回YES则自定义的视图能够播放输入的声音
@property (nonatomic, readonly) BOOL enableInputClicksWhenVisible; // If YES, an input view will enable playInputClick.

@end

/* The UI_USER_INTERFACE_IDIOM() function is provided for use when deploying to a version of the iOS less than 3.2. If the earliest version of iPhone/iOS that you will be deploying for is 3.2 or greater, you may use -[UIDevice userInterfaceIdiom] directly.
 */
static inline UIUserInterfaceIdiom UI_USER_INTERFACE_IDIOM() {
    return ([[UIDevice currentDevice] respondsToSelector:@selector(userInterfaceIdiom)] ?
            [[UIDevice currentDevice] userInterfaceIdiom] :
            UIUserInterfaceIdiomPhone);
}
//屏幕转向
UIKIT_EXTERN NSNotificationName const UIDeviceOrientationDidChangeNotification __TVOS_PROHIBITED;
//电池状态改变
UIKIT_EXTERN NSNotificationName const UIDeviceBatteryStateDidChangeNotification   NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;
//电池电量改变
UIKIT_EXTERN NSNotificationName const UIDeviceBatteryLevelDidChangeNotification   NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;
//距离感应区状态改变
UIKIT_EXTERN NSNotificationName const UIDeviceProximityStateDidChangeNotification NS_AVAILABLE_IOS(3_0);

NS_ASSUME_NONNULL_END
