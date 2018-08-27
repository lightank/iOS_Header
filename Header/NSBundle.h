/*	NSBundle.h
	Copyright (c) 1994-2016, Apple Inc.  All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSProgress.h>
#import <Foundation/NSNotification.h>

@class NSString, NSURL, NSError, NSUUID, NSLock, NSNumber;

/*
 // 2.NSBundle
 NSDictionary *info_dic = [[NSBundle mainBundle] infoDictionary]; // 获取当前设备的信息字典
 NSDictionary *localized_info_dic = [[NSBundle mainBundle] localizedInfoDictionary]; // 本地化的信息字典
 
 NSString *app_name = [info_dic objectForKey:@"CFBundleDisplayName"]; // 应用名称 @"Demo"
 NSString *app_version = [info_dic objectForKey:@"CFBundleShortVersionString"]; // 应用版本 @"1.0"
 NSString *app_build_version = [info_dic objectForKey:@"CFBundleVersion"]; // 应用build版本 @"1"
 */

NS_ASSUME_NONNULL_BEGIN

/* Because NSBundle caches allocated instances, subclasses should be prepared
 to receive an already initialized object back from [super initWithPath:] */
@interface NSBundle : NSObject {
@private
    NSUInteger		_flags;
    id		        _cfBundle;
    NSUInteger		_reserved2;
    Class		_principalClass;
    id                  _initialPath;
    id                  _resolvedPath;
    id                  _reserved3;
    id                  _lock;
}

/* Methods for creating or retrieving bundle instances. */
/**  用于创建或检索bundle实例对象  */
#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
//Returns the NSBundle object that corresponds to the directory where the current application executable is located.
//返回当前app所在的bundle
@property (class, readonly, strong) NSBundle *mainBundle;
#endif
//Returns an NSBundle object that corresponds to the specified directory.
+ (nullable instancetype)bundleWithPath:(NSString *)path;
//Returns an NSBundle object initialized to correspond to the specified directory.
- (nullable instancetype)initWithPath:(NSString *)path NS_DESIGNATED_INITIALIZER;
//Returns an NSBundle object that corresponds to the specified file URL.
+ (nullable instancetype)bundleWithURL:(NSURL *)url NS_AVAILABLE(10_6, 4_0);
//Returns an NSBundle object initialized to correspond to the specified file URL.
- (nullable instancetype)initWithURL:(NSURL *)url NS_AVAILABLE(10_6, 4_0);
//Returns the NSBundle object with which the specified class is associated.
+ (NSBundle *)bundleForClass:(Class)aClass;
//Returns the NSBundle instance that has the specified bundle identifier
+ (nullable NSBundle *)bundleWithIdentifier:(NSString *)identifier;

#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
//Returns an array of all the application’s non-framework bundles.
@property (class, readonly, copy) NSArray<NSBundle *> *allBundles;
//Returns an array of all of the application’s bundles that represent frameworks.
@property (class, readonly, copy) NSArray<NSBundle *> *allFrameworks;
#endif

/* Methods for loading and unloading bundles. */
- (BOOL)load;
@property (readonly, getter=isLoaded) BOOL loaded;
- (BOOL)unload;
//Returns a Boolean value indicating whether the bundle’s executable code could be loaded successfully.
- (BOOL)preflightAndReturnError:(NSError **)error NS_AVAILABLE(10_5, 2_0);
//Loads the bundle’s executable code and returns any errors.
- (BOOL)loadAndReturnError:(NSError **)error NS_AVAILABLE(10_5, 2_0);

/* Methods for locating various components of a bundle. */
/*
 (lldb) po NSHomeDirectory
 /Users/maimaiti/Library/Developer/CoreSimulator/Devices/121EDE35-480D-4CBE-B1C6-3AF3D708E0A9/data/Containers/Data/Application/A9BB3DD6-8B63-450D-971F-A8AC05F23E97
 
 (lldb) po bundleURL
 file:///Users/username/Library/Developer/CoreSimulator/Devices/121EDE35-480D-4CBE-B1C6-3AF3D708E0A9/data/Containers/Bundle/Application/034B8CAD-B59D-4586-A76D-1106102A4DD6/testAPP.app/
 (lldb) po bundlePath
 /Users/username/Library/Developer/CoreSimulator/Devices/121EDE35-480D-4CBE-B1C6-3AF3D708E0A9/data/Containers/Bundle/Application/CE25B38C-E48C-434D-B532-8900D03EDAB8/testAPP.app
 
 (lldb) po resourceURL
 file:///Users/username/Library/Developer/CoreSimulator/Devices/121EDE35-480D-4CBE-B1C6-3AF3D708E0A9/data/Containers/Bundle/Application/CE25B38C-E48C-434D-B532-8900D03EDAB8/testAPP.app/
 (lldb) po resourcePath
 /Users/username/Library/Developer/CoreSimulator/Devices/121EDE35-480D-4CBE-B1C6-3AF3D708E0A9/data/Containers/Bundle/Application/CE25B38C-E48C-434D-B532-8900D03EDAB8/testAPP.app
 
 (lldb) po executableURL
 file:///Users/username/Library/Developer/CoreSimulator/Devices/121EDE35-480D-4CBE-B1C6-3AF3D708E0A9/data/Containers/Bundle/Application/CE25B38C-E48C-434D-B532-8900D03EDAB8/testAPP.app/testAPP
 (lldb) po executablePath
 /Users/username/Library/Developer/CoreSimulator/Devices/121EDE35-480D-4CBE-B1C6-3AF3D708E0A9/data/Containers/Bundle/Application/FFEAF488-AC41-4393-8AE2-5D21A9D7F832/testAPP.app/testAPP
 */

//The full URL of the receiver’s bundle directory. (read-only)
//获取app包路径,跟resourceURL打印地址一样
@property (readonly, copy) NSURL *bundleURL NS_AVAILABLE(10_6, 4_0);
//The file URL of the bundle’s subdirectory containing resource files. (read-only)
//app资源目录路径
@property (nullable, readonly, copy) NSURL *resourceURL NS_AVAILABLE(10_6, 4_0);
//The file URL of the receiver's executable file. (read-only)
@property (nullable, readonly, copy) NSURL *executableURL NS_AVAILABLE(10_6, 4_0);
//Returns the file URL of the executable with the specified name in the receiver’s bundle.
- (nullable NSURL *)URLForAuxiliaryExecutable:(NSString *)executableName NS_AVAILABLE(10_6, 4_0);
//The file URL of the bundle’s subdirectory containing private frameworks. (read-only)
@property (nullable, readonly, copy) NSURL *privateFrameworksURL NS_AVAILABLE(10_6, 4_0);
//The file URL of the receiver's subdirectory containing shared frameworks. (read-only)
@property (nullable, readonly, copy) NSURL *sharedFrameworksURL NS_AVAILABLE(10_6, 4_0);
//The file URL of the bundle’s subdirectory containing shared support files. (read-only)
@property (nullable, readonly, copy) NSURL *sharedSupportURL NS_AVAILABLE(10_6, 4_0);
//The file URL of the receiver's subdirectory containing plug-ins. (read-only)
@property (nullable, readonly, copy) NSURL *builtInPlugInsURL NS_AVAILABLE(10_6, 4_0);
//The file URL for the bundle’s App Store receipt. (read-only)
@property (nullable, readonly, copy) NSURL *appStoreReceiptURL NS_AVAILABLE(10_7, 7_0);

@property (readonly, copy) NSString *bundlePath;
//The full pathname of the bundle’s subdirectory containing resources.
@property (nullable, readonly, copy) NSString *resourcePath;
@property (nullable, readonly, copy) NSString *executablePath;
- (nullable NSString *)pathForAuxiliaryExecutable:(NSString *)executableName;
//The full pathname of the bundle’s subdirectory containing private frameworks. (read-only)
@property (nullable, readonly, copy) NSString *privateFrameworksPath;
//The full pathname of the bundle’s subdirectory containing shared frameworks. (read-only)
@property (nullable, readonly, copy) NSString *sharedFrameworksPath;
//The full pathname of the bundle’s subdirectory containing shared support files. (read-only)
@property (nullable, readonly, copy) NSString *sharedSupportPath;
//The full pathname of the receiver's subdirectory containing plug-ins. (read-only)
@property (nullable, readonly, copy) NSString *builtInPlugInsPath;

/* Methods for locating bundle resources.  Instance methods locate resources in the bundle indicated by the receiver; class methods take an argument pointing to a bundle on disk.  In the class methods, bundleURL is a URL pointing to the location of a bundle on disk, and may not be nil; bundlePath is the path equivalent of bundleURL, an absolute path pointing to the location of a bundle on disk.  By contrast, subpath is a relative path to a subdirectory inside the relevant global or localized resource directory, and should be nil if the resource file in question is not in a subdirectory.  Where appropriate, localizationName is the name of a .lproj directory in the bundle, minus the .lproj extension; passing nil for localizationName retrieves only global resources, whereas using a method without this argument retrieves both global and localized resources (using the standard localization search algorithm).  */
+ (nullable NSURL *)URLForResource:(nullable NSString *)name withExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath inBundleWithURL:(NSURL *)bundleURL NS_AVAILABLE(10_6, 4_0);
+ (nullable NSArray<NSURL *> *)URLsForResourcesWithExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath inBundleWithURL:(NSURL *)bundleURL NS_AVAILABLE(10_6, 4_0);

- (nullable NSURL *)URLForResource:(nullable NSString *)name withExtension:(nullable NSString *)ext NS_AVAILABLE(10_6, 4_0);
//Returns the file URL for the resource file identified by the specified name and extension and residing in a given bundle directory.
- (nullable NSURL *)URLForResource:(nullable NSString *)name withExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath NS_AVAILABLE(10_6, 4_0);
- (nullable NSURL *)URLForResource:(nullable NSString *)name withExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath localization:(nullable NSString *)localizationName NS_AVAILABLE(10_6, 4_0);

- (nullable NSArray<NSURL *> *)URLsForResourcesWithExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath NS_AVAILABLE(10_6, 4_0);
- (nullable NSArray<NSURL *> *)URLsForResourcesWithExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath localization:(nullable NSString *)localizationName NS_AVAILABLE(10_6, 4_0);

+ (nullable NSString *)pathForResource:(nullable NSString *)name ofType:(nullable NSString *)ext inDirectory:(NSString *)bundlePath;
+ (NSArray<NSString *> *)pathsForResourcesOfType:(nullable NSString *)ext inDirectory:(NSString *)bundlePath;

- (nullable NSString *)pathForResource:(nullable NSString *)name ofType:(nullable NSString *)ext;
- (nullable NSString *)pathForResource:(nullable NSString *)name ofType:(nullable NSString *)ext inDirectory:(nullable NSString *)subpath;
- (nullable NSString *)pathForResource:(nullable NSString *)name ofType:(nullable NSString *)ext inDirectory:(nullable NSString *)subpath forLocalization:(nullable NSString *)localizationName;

- (NSArray<NSString *> *)pathsForResourcesOfType:(nullable NSString *)ext inDirectory:(nullable NSString *)subpath;
- (NSArray<NSString *> *)pathsForResourcesOfType:(nullable NSString *)ext inDirectory:(nullable NSString *)subpath forLocalization:(nullable NSString *)localizationName;

/* Method for retrieving localized strings. */
- (NSString *)localizedStringForKey:(NSString *)key value:(nullable NSString *)value table:(nullable NSString *)tableName NS_FORMAT_ARGUMENT(1);

/* Methods for obtaining various information about a bundle. */
//The source’s bundle identifier. (read-only)
@property (nullable, readonly, copy) NSString *bundleIdentifier;
//A dictionary, constructed from the bundle's Info.plist file, that contains information about the receiver. (read-only)
@property (nullable, readonly, copy) NSDictionary<NSString *, id> *infoDictionary;
//A dictionary with the keys from the bundle’s localized property list. (read-only)
@property (nullable, readonly, copy) NSDictionary<NSString *, id> *localizedInfoDictionary;
//Returns the value associated with the specified key in the receiver's information property list.
- (nullable id)objectForInfoDictionaryKey:(NSString *)key;
//Returns the Class object for the specified name.
- (nullable Class)classNamed:(NSString *)className;
/*
 main函数:
 int main(int argc, char * argv[]) {
 @autoreleasepool {
 return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
 }
 main函数的两个参数，iOS中没有用到，包括这两个参数是为了与标准ANSI C保持一致。
 UIApplicationMain函数，前两个和main函数一样，重点是后两个，官方说明是这样的：
 // If nil is specified for principalClassName, the value for NSPrincipalClass from the Info.plist is used. If there is no
 // NSPrincipalClass key specified, the UIApplication class is used. The delegate class will be instantiated using init.
 UIKIT_EXTERN int UIApplicationMain(int argc, char *argv[], NSString *principalClassName, NSString *delegateClassName);
 
 后两个参数分别表示程序的主要类(principal class)和代理类(delegate class)。如果主要类(principal class)为nil，将从Info.plist中获取，如果Info.plist中不存在对应的key，则默认为UIApplication；如果代理类(delegate class)将在新建工程时创建。
 根据UIApplicationMain函数，程序将进入AppDelegate.m，这个文件是xcode新建工程时自动生成的。AppDelegate.m文件关乎着应用程序的生命周期。
 */
//The bundle’s principal class. (read-only)
@property (nullable, readonly) Class principalClass;

/* Methods for dealing with localizations. */
//An ordered list of preferred localizations contained in the bundle. (read-only)
//
@property (readonly, copy) NSArray<NSString *> *preferredLocalizations;	// a subset of this bundle's localizations, re-ordered into the preferred order for this process's current execution environment; the main bundle's preferred localizations indicate the language (of text) the user is most likely seeing in the UI
//A list of all the localizations contained in the bundle. (read-only)
//项目的PROJECT -> Info -> Localizations中添加的语言包
@property (readonly, copy) NSArray<NSString *> *localizations;		// list of language names this bundle appears to be localized to
//The localization for the development language. (read-only)
@property (nullable, readonly, copy) NSString *developmentLocalization;
//Returns one or more localizations from the specified list that a bundle object would use to locate resources for the current user.
+ (NSArray<NSString *> *)preferredLocalizationsFromArray:(NSArray<NSString *> *)localizationsArray;
//Returns the localizations that a bundle object would prefer, given the specified bundle and user’s language preferences.
+ (NSArray<NSString *> *)preferredLocalizationsFromArray:(NSArray<NSString *> *)localizationsArray forPreferences:(nullable NSArray<NSString *> *)preferencesArray;

/* Method for determining executable architectures. */
enum {
    NSBundleExecutableArchitectureI386      = 0x00000007,
    NSBundleExecutableArchitecturePPC       = 0x00000012,
    NSBundleExecutableArchitectureX86_64    = 0x01000007,
    NSBundleExecutableArchitecturePPC64     = 0x01000012
};
//An array of numbers indicating the architecture types supported by the bundle’s executable. (read-only)
@property (nullable, readonly, copy) NSArray<NSNumber *> *executableArchitectures NS_AVAILABLE(10_5, 2_0);

@end

#define NSLocalizedString(key, comment) \
[NSBundle.mainBundle localizedStringForKey:(key) value:@"" table:nil]
#define NSLocalizedStringFromTable(key, tbl, comment) \
[NSBundle.mainBundle localizedStringForKey:(key) value:@"" table:(tbl)]
#define NSLocalizedStringFromTableInBundle(key, tbl, bundle, comment) \
[bundle localizedStringForKey:(key) value:@"" table:(tbl)]
#define NSLocalizedStringWithDefaultValue(key, tbl, bundle, val, comment) \
[bundle localizedStringForKey:(key) value:(val) table:(tbl)]

@interface NSString (NSBundleExtensionMethods)

/* For strings with length variations, such as from a stringsdict file, this method returns the variant at the given width. If there is no variant at the given width, the one for the next smaller width is returned. And if there are none smaller, the smallest available is returned. For strings without variations, this method returns self. The unit that width is expressed in is decided by the application or framework. But it is intended to be some measurement indicative of the context a string would fit best to avoid truncation and wasted space.
 */
- (NSString *)variantFittingPresentationWidth:(NSInteger)width NS_AVAILABLE(10_11, 9_0);

@end

FOUNDATION_EXPORT NSNotificationName const NSBundleDidLoadNotification;
//This constant is provided in the userInfo dictionary of the NSBundleDidLoadNotification notification.
FOUNDATION_EXPORT NSString * const NSLoadedClasses;	// notification key


/*
 The NSBundleResourceRequest class is used to interact with the on demand resource loading system.
 
 The purpose of the system is to allow an application to download certain resources on demand, when they are required. This also means that the system can purge a resource from disk when it is no longer required, which will save disk space. This class describes which resources are required, makes the request and reports progress, allows the app to specify how long during its execution that they are required.
 
 Resources are downloaded into the application container, and are made available via the standard NSBundle resource lookup API.
 
 The request object itself is lightweight. You may create as many as you need, for example to request the same set of tags in different components of your application.
 */
//NSBundleResourceRequest是iOS9的新特性，主要用于按需加载资源的下载控制。按需加载资源是由App Store托管的内容，它和下载的app bundle是分开的。app请求一系列按需加载资源，而下载和存储资源是由操作系统来管理。这些资源可以是除可执行代码外，bundle支持的任何类型。
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NSBundleResourceRequest : NSObject <NSProgressReporting>

- (instancetype)init NS_UNAVAILABLE;

/*
 A tag and bundle are required arguments to the init methods. The tag argument is required and it must exist in the manifest of the specified bundle. The bundle argument describes an existing bundle which was built with on demand resources support. Any resources downloaded can be found using the standard NSBundle resource lookup API once the request is completed. If no bundle is specified then the main bundle is used.
 */
//Initializes a resource request for managing the on-demand resources marked with any of the set of specified tags. The managed resources are loaded into the main bundle.
- (instancetype)initWithTags:(NSSet<NSString *> *)tags;
//Initializes a resource request for managing the on-demand resources marked with any of the set of specified tags. The managed resources are loaded into the specified bundle.
- (instancetype)initWithTags:(NSSet<NSString *> *)tags bundle:(NSBundle *)bundle NS_DESIGNATED_INITIALIZER;

/*
 Provides a hint to the resource loading system as to the loading priority of this request. Values are limited to between 0 and 1, with 1 being the highest priority. The default priority is 0.5.
 
 The exact meaning of the value is up to your application. The system will prefer to act on requests that have a higher priority (from the same application). You may change the priority at any time, even after a request has started. The system will make a best attempt to take the new priority into account.
 */
//A hint to the system of the relative priority of the resource request.
@property double loadingPriority;

/*
 The tags this request will load.
 */
@property (readonly, copy) NSSet<NSString *> *tags;

/*
 The bundle object that will hold the requested resources. After the -beginAccessingResourcesWithCompletionHandler: callback is invoked, you may use the standard bundle lookup APIs on this bundle object to find your resources.
 */
@property (readonly, strong) NSBundle *bundle;

/*
 Ask the system to fetch the resources that were part of the tag set in this request. Resources will not be purged while in use by the application (as indicated by the application using this begin API paired with a call to -endAccessingResources). If an application has too many fetched resources and the system is unable to reserve enough space for newly requested tags, the request may return an error.
 
 When you are finished with the resources and they may be purged off the disk, invoke -endAccessingResources. If the request object is deallocated, it will also inform the system that the resources are no longer in use.
 
 The completion block will be invoked on a non-main serial queue when the resources are available or an error has occurred. An example of a possible error that may be reported is the lack of a network connection or a problem connecting to the on-demand servers.
 
 Fetch requests are reference counted across the application. So if you have two requests outstanding with the same set of tags, each may be used independently without having to know about any global state. However, each NSBundleResourceRequest object may only be used once.
 
 If you cancel an outstanding request (via the cancel method on the NSProgress object, or cancelling a parent progress object you have created) the completion handler argument to this method will be called back with an NSUserCancelledError in the NSCocoaErrorDomain.
 
 Be sure to always invoke the -endAccessingResources method to balance a call to the begin method, even in the case of an error in the completion handler.
 
 If you want to access the resources again, create a new NSBundleResourceRequest object.
 */
- (void)beginAccessingResourcesWithCompletionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/*
 Inform the system that you wish to begin accessing the resources that are part of this request, but do not attempt to download any content over the network. The completion handler will be invoked with a YES argument if the resources are available.
 
 If the resources were available, then you must invoke the -endAccessingResources method once you are done accessing them. If the resources were not available, then you may invoke the -beginAccessingResourcesWithCompletionHandler: method to initiate a download of the resources.
 */
- (void)conditionallyBeginAccessingResourcesWithCompletionHandler:(void (^)(BOOL resourcesAvailable))completionHandler;

/*
 Informs the system that you are finished with the resources that were part of the tag set in this request. Call this after you no longer need the resources to be available on disk. It is important to invoke this method to make room for newly requested resources. This method may only be invoked if you have received a callback from -beginAccessingResourcesWithCompletionHandler:. To cancel an in-progress request, invoke cancel on the -progress property.
 */
- (void)endAccessingResources;

/*
 Progress for the request. The progress object will be valid at initialization and begin updating after the -beginAccessingResourcesWithCompletionHandler: method is called.
 */
@property (readonly, strong) NSProgress *progress;

@end

@interface NSBundle (NSBundleResourceRequestAdditions)

/* Set a preservation priority for tags that are included in this bundle for the On Demand Resources system. Preservation priorities may be between 0.0 and 1.0, with higher values being the last choice for purging by the system. The exact meaning of this value is up to your application as it only has meaning within the set of tags your application uses.
 
 The default value is 0.0.
 
 This method will throw an exception if the receiver bundle has no on demand resource tag information.
 */
- (void)setPreservationPriority:(double)priority forTags:(NSSet<NSString *> *)tags NS_AVAILABLE(NA, 9_0);
- (double)preservationPriorityForTag:(NSString *)tag NS_AVAILABLE(NA, 9_0);

@end

/*
 This notification is posted to the default notification center when the resource request system detects a low disk space condition.
 
 If the application is in the background, the system needs more space, and the application does not free up enough in response to the notification then the application may be killed. The application can free up space by calling -endAccessingResources on any outstanding requests. This will inform the system that you are done with those resources and it may purge the content to make room for a new request.
 
 Note that this notification may not be the same as low disk space on the system, as applications can have a smaller quota.
 */
FOUNDATION_EXPORT NSNotificationName const NSBundleResourceRequestLowDiskSpaceNotification NS_AVAILABLE(NA, 9_0);

/* Use this value for the loadingPriority property if the user is doing nothing but waiting on the result of this request. The system will dedicate the maximum amount of resources available to finishing this request as soon as possible.
 */
FOUNDATION_EXPORT double const NSBundleResourceRequestLoadingPriorityUrgent NS_AVAILABLE(NA, 9_0);

NS_ASSUME_NONNULL_END
