//
//  UIViewController.h
//  UIKit
//
//  Copyright (c) 2007-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/NSExtensionRequestHandling.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIStateRestoration.h>
#import <UIKit/UITraitCollection.h>
#import <UIKit/UIFocus.h>

/*
 UIViewController is a generic controller base class that manages a view.  It has methods that are called
 when a view appears or disappears.
 
 Subclasses can override -loadView to create their custom view hierarchy, or specify a nib name to be loaded
 automatically.  This class is also a good place for delegate & datasource methods, and other controller
 stuff.
 */
/*
 UIViewController是一个通用的管理一个view的控制器的基类,在view出现或消失的时候将会有方法被调用.
 
 子类可以重新-loadView方法去
 */


/*
 参考自:http://www.jianshu.com/p/b3a31eed945f
 NS_ASSUME_NONNULL_BEGIN && NS_ASSUME_NONNULL_END
 {//begin
 Swift中存在Option类型(可选值类型:使用？和！声明的变量),而OC里面没有这个特征,故在XCODE6.3新增关键词定义用于OC转SWIFT时候可以区分到底是什么类型
 __nullable && ___nonnull
 
 __nullable:对象可以为NULL或者为nil
 __nonnull:对象不能为NULL
 当我们不遵循这一规则时，编译器就会给出警告。
 eg:
 - (id)itemWithName:(NSString * __nonnull)name;
 [self itemWithName:nil];    // 编译器警告：Null passed to a callee that requires a non-null argument
 事实上，在任何可以使用const关键字的地方都可以使用__nullable和__nonnull，不过这两个关键字仅限于使用在指针类型上。而在方法的声明中，我们还可以使用不带下划线的nullable和nonnull，如下所示：
 - (nullable id)itemWithName:(NSString * nonnull)name
 在属性声明中，也增加了两个相应的特性，因此上例中的items属性可以如下声明:
 @property (nonatomic, copy, nonnull) NSArray *items;
 当然也可以用以下这种方式：
 @property (nonatomic, copy) NSArray * __nonnull items;
 推荐使用nonnull这种方式，这样可以让属性声明看起来更清晰。
 
 Non null区域设置(Audited Regions)
 如果需要每个属性或每个方法都去指定nonnull和nullable，是一件非常繁琐的事。苹果为了减轻我们的工作量，专门提供了两个宏：NS_ASSUME_NONNULL_BEGIN和NS_ASSUME_NONNULL_END。在这两个宏之间的代码，所有简单指针对象都被假定为nonnull，因此我们只需要去指定那些nullable的指针。如下代码所示：
 
 NS_ASSUME_NONNULL_BEGIN
 @interface TestNullabilityClass ()
 @property (nonatomic, copy) NSArray *items;
 - (id)itemWithName:(nullable NSString *)name;
 @end
 NS_ASSUME_NONNULL_END
 
 在上面的代码中，items属性默认是non null的，itemWithName:方法的返回值也是non null，而参数是指定为nullable的。
 
 不过，为了安全起见，苹果还制定了几条规则：
 
 typedef定义的类型的nullability特性通常依赖于上下文，即使是在Audited Regions中，也不能假定它为nonnull。
 复杂的指针类型(如id *)必须显示去指定是nonnull还是nullable。例如，指定一个指向nullable对象的nonnull指针，可以使用
 
 __nullable id * __nonnull
 我们经常使用的NSError **通常是被假定为一个指向nullable NSError对象的nullable指针。
 兼容性
 
 因为Nullability Annotations是Xcode 6.3新加入的，所以我们需要考虑之前的老代码。实际上，苹果已以帮我们处理好了这种兼容问题，我们可以安全地使用它们：
 
 老代码仍然能正常工作， 即使对nonnull对象使用了nil也没有问题。
 老代码在需要和swift混编时，在新的swift编译器下会给出一个警告。
 nonnull不会影响性能。事实上，我们仍然可以在运行时去判断我们的对象是否为nil。
 事实上，我们可以将nonnull/nullable与我们的断言和异常一起看待，其需要处理的问题都是同一个：违反约定是一个程序员的错误。特别是，返回值是我们可控的东西，如果返回值是nonnull的，则我们不应该返回nil，除非是为了向后兼容。
 //end}
 
 
 NS_ENUM_AVAILABLE_IOS:从单词的字面可以看出使用这个宏说明这个枚举开始IOS的版本
 IOS版本如下 7_0 代表7.0的版本.用_替换
 参数只有一个NS_ENUM_AVAILABLE_IOS(2_0) 代表>=2.0开始
 
 
 NS_ENUM_DEPRECATED_IOS:代表枚举类型已经过时的API 第一个参数是开始的时候，第二个参数是过时的时候
 NS_ENUM_DEPRECATED_IOS(2_0,7_0) 代表开始于IOS2.0废弃于IOS7.0 也就是>=2.0 <=7.0
 
 __TVOS_PROHIBITED:代表这个枚举或者类，方法，参数在TVOS系统上面不能使用
 typedef NS_ENUM(NSInteger, UIStatusBarStyle) {
 UIStatusBarStyleDefault                                     = 0, // Dark content, for use on light backgrounds
 UIStatusBarStyleLightContent     NS_ENUM_AVAILABLE_IOS(7_0) = 1, // Light content, for use on dark backgrounds
 UIStatusBarStyleBlackTranslucent NS_ENUM_DEPRECATED_IOS(2_0, 7_0, "Use UIStatusBarStyleLightContent") = 1,
 UIStatusBarStyleBlackOpaque      NS_ENUM_DEPRECATED_IOS(2_0, 7_0, "Use UIStatusBarStyleLightContent") = 2,
 } __TVOS_PROHIBITED;
 
 
 UIKIT_EXTERN:extern这个是定义字符串变量,比#define更加的高效.但是UIKIT_EXTERN是根据是否是C语言宏定义,根据语言区分,比extern更加的高效
 eg:
 UIKIT_EXTERN NSString *const UIApplicationInvalidInterfaceOrientationException NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
 上面的代码一般定义在.h 在.m实现,实现要去掉UIKIT_EXTERN.代表IOS6.0之后可以用，在TVOS系统不可用。
 
 
 NS_CLASS_AVAILABLE_IOS:代表类开始的API
 eg:
 NS_CLASS_AVAILABLE_IOS(2_0) @interface UIApplication : UIResponder
 
 
 NS_EXTENSION_UNAVAILABLE_IOS:标记IOS插件不能使用这些API,后面有一个参数，可以作为提示，用什么API替换
 eg:
 + (UIApplication *)sharedApplication NS_EXTENSION_UNAVAILABLE_IOS("Use view controller based solutions where appropriate instead.");
 
 __kindof:参考自:http://blog.csdn.net/leikezhu1981/article/details/47418011
 {//begin
 _kindof 这修饰符还是很实用的，解决了一个长期以来的小痛点，拿原来的 UITableView 的这个方法来说：
 - (id)dequeueReusableCellWithIdentifier:(NSString *)identifier;
 使用时前面基本会使用 UITableViewCell 子类型的指针来接收返回值，所以这个 API 为了让开发者不必每次都蛋疼的写显式强转，把返回值定义成了 id 类型，而这个 API 实际上的意思是返回一个 UITableViewCell 或 UITableViewCell 子类的实例，于是新的 __kindof 关键字解决了这个问题：
 - (__kindof UITableViewCell *)dequeueReusableCellWithIdentifier:(NSString *)identifier;
 既明确表明了返回值，又让使用者不必写强转。再举个带泛型的例子，UIView 的 subviews 属性被修改成了：

 @property (nonatomic, readonly, copy) NSArray<__kindof UIView *> *subviews;
 这样，写下面的代码时就没有任何警告了：
 UIButton *button = view.subviews.lastObject;
 
 Where to go
 有了上面介绍的这些新特性以及如 instancetype 这样的历史更新，Objective-C 这门古老语言的类型检测和类型推断终于有所长进，现在不论是接口还是代码中的 id 类型都越来越少，更多潜在的类型错误可以被编译器的静态检查发现。
 同时，个人感觉新版的 Xcode 对继承链构造器的检测也加强了，NS_DESIGNATED_INITIALIZER 这个宏并不是新面孔，可以使用它标志出像 Swift 一样的指定构造器和便捷构造器。
 最后，附上一段用上了所有新特性的代码，Swift 是发展趋势，如果你暂时依然要写 Objective-C 代码，把所有新特性都用上，或许能让你到新语言的迁移更无痛一点。
 @class IMTeam, IMMeber;
 NS_ASSUME_NONNULL_BEGIN
 
 @interface IMDashboardModel : NSObject
 
 @property (nonatomic, readonly, strong) IMTeam *team;
 @property (nonatomic, readonly, copy) NSArray<__kindof IMMeber *> *memebers;
 
 - (void)updateAllDashboardDataThen:(nullable void (^)(NSError * __nullable error))then;
 
 @end
 
 NS_ASSUME_NONNULL_END
 //end}
 
 泛型:
 {//begin
 Xcode 7新的特性Lightweight Generics 轻量级泛型:Lightweight Generics 轻量级泛型，轻量是因为这是个纯编译器的语法支持（llvm 7.0），和 Nullability 一样，没有借助任何 objc runtime 的升级，也就是说，这个新语法在 Xcode 7 上可以使用且完全向下兼容（更低的 iOS 版本）
 自定义泛型类:
 比起使用系统的泛型容器，更好玩的是自定义一个泛型类，目前这里还没什么文档，但拦不住我们写测试代码，假设我们要自定义一个 Stack 容器类：:
 @interface Stack<ObjectType> : NSObject
 - (void)pushObject:(ObjectType)object;
 - (ObjectType)popObject;
 @property (nonatomic, readonly) NSArray<ObjectType> *allObjects;
 @end
 这个 ObjectType 是传入类型的 placeholder，它只能在 @interface 上定义（类声明、类扩展、Category），如果你喜欢用 T 表示也 ok，这个类型在 @interface 和 @end 区间的作用域有效，可以把它作为入参、出参、甚至内部 NSArray 属性的泛型类型，应该说一切都是符合预期的。我们还可以给 ObjectType 增加类型限制，比如：
 // 只接受 NSNumber * 的泛型
 @interface Stack<ObjectType: NSNumber *> : NSObject
 // 只接受满足 NSCopying 协议的泛型
 @interface Stack<ObjectType: id<NSCopying>> : NSObject
 若什么都不加，表示接受任意类型 ( id )；当类型不满足时编译器将产生 error。
 实例化一个 Stack，一切工作正常：
 Stack<NSString *> *stringStack = [[Stack alloc] init];
 [stringStack pushObject:<#(NSString *)#>];
 对于多参数的泛型，用逗号隔开，其他都一样，可以参考 NSDictionary 的头文件
 协变性和逆变性:
 当类支持泛型后，它们的 Type 发生了变化，比如下面三个对象看上去都是 Stack，但实际上属于三个Type：
 Stack *stack; // Stack *
 Stack<NSString *> *stringStack; // Stack<NSString *>
 Stack<NSMutableString *> *mutableStringStack; // Stack<NSMutableString *>
 当其中两种类型做类型转化时，编译器需要知道哪些转化是允许的，哪些是禁止的，比如，默认情况下：
 Stack *stack;
 Stack<NSString *> *stringStack;
 Stack<NSMutableString *> *mutalbeStringStack;
 
 stack = stringStack;
 stack = mutalbeStringStack;
 stringStack = stack;
 stringStack = mutalbeStringStack;
 mutalbeStringStack = stack;
 mutalbeStringStack = stringStack;

 我们可以看到，不指定泛型类型的 Stack 可以和任意泛型类型转化，但指定了泛型类型后，两个不同类型间是不可以强转的，假如你希望主动控制转化关系，就需要使用泛型的协变性和逆变性修饰符了：
 __covariant - 协变性，子类型可以强转到父类型（里氏替换原则）
 __contravariant - 逆变性，父类型可以强转到子类型（WTF?）
 
 协变：
 @interface Stack<__covariant ObjectType> : NSObject
 效果：
 Stack<NSString *> *stringStack;
 Stack<NSMutableString *> *mutalbeStringStack;

 stringStack = mutalbeStringStack;
 mutalbeStringStack = stringStack;
 
 逆变：
 @interface Stack<__contravariant ObjectType> : NSObject
 效果：
 Stack<NSString *> *stringStack;
 Stack<NSMutableString *> *mutalbeStringStack;
 
 stringStack = mutalbeStringStack;
 mutalbeStringStack = stringStack;
 
 协变是非常好理解的，像 NSArray 的泛型就用了协变的修饰符，而逆变我还没有想到有什么实际的使用场景。
 //end}

 NS_REQUIRES_SUPER:定义函数时，希望子类override该方法时候，必须调用super，否则编译器直接报警告⚠️
 
 SDK_HIDE_TIDE:暂定 没查到干什么的 字面上是在SDK隐藏
 
 NS_DESIGNATED_INITIALIZER:用来定义一些初始化方法只能过来这些标记的初始化
 */

NS_ASSUME_NONNULL_BEGIN     //#define NS_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")

@class UIView;
@class UINavigationItem, UIBarButtonItem, UITabBarItem;     //UINavigationItem导航控制器的导航栏,UINavigationItem导航栏的基本元素,UITabBarItem是UITabBarController分栏控制器底部切换item按钮
@class UISearchDisplayController;       //专为UITableView搜索封装的一个类,在iOS 8.0被弃用,使用UISearchController代替
@class UIPopoverController;     //UIPopverController是IPad特有的类,负责控制Popover视图。Popover是一种临时视图，它以“漂浮”的形式出现在视图里面,继承自NSObject,iOS 9被弃用
@class UIStoryboard, UIStoryboardSegue, UIStoryboardUnwindSegueSource;      //UIStoryboard是iOS5以后新增的内容，是以故事版的形式来展示界面之间的逻辑业务关系，前端开发目前有三种方式（纯代码，代码+xib，UIStoryboard），UIStoryboard为其中一种
@class UIScrollView;        //UIScrollView在UIKit中是UIScrollView类，是容器类型的视图。它有三个子类—UITextView，UITableview和UICollectionView，它们在内容超出屏幕时提供水平或垂直滚动条
@protocol UIViewControllerTransitionCoordinator;        //涉及到自定义控制器转场，iOS7引入的新特性自定义控制器转场.遵守该协议的对象需实现控制器转场相关的动画.特别的是,使用者无需在自定义的类中遵守该协议.当您在present或dismiss一个控制器的时候,UIKit将会自动创建一个transition coordinator object,并赋值给这个控制器的transitionCoordinator属性,这个对象仅在发生转场动画时存在

typedef NS_ENUM(NSInteger, UIModalTransitionStyle) {            //弹出模态控制器时的四种动画风格
    UIModalTransitionStyleCoverVertical = 0,                    //默认的，垂直从下往上
    UIModalTransitionStyleFlipHorizontal __TVOS_PROHIBITED,     //垂直翻转
    UIModalTransitionStyleCrossDissolve,                        //淡入淡出
    UIModalTransitionStylePartialCurl NS_ENUM_AVAILABLE_IOS(3_2) __TVOS_PROHIBITED,     //卷曲
};

typedef NS_ENUM(NSInteger, UIModalPresentationStyle) {      //弹出模态控制器时弹出风格
    UIModalPresentationFullScreen = 0,                                          //弹出VC时，presented VC充满全屏，如果弹出VC的wantsFullScreenLayout设置为YES的，则会填充到状态栏下边，否则不会填充到状态栏之下,会自动将原来的ViewController的view给unload掉
    UIModalPresentationPageSheet NS_ENUM_AVAILABLE_IOS(3_2) __TVOS_PROHIBITED,  //弹出VC时，presented VC的高度和当前屏幕高度相同，宽度和竖屏模式下屏幕宽度相同，剩余未覆盖区域将会变暗并阻止用户点击，这种弹出模式下，竖屏时跟 UIModalPresentationFullScreen的效果一样，横屏时候两边则会留下变暗的区域。
    UIModalPresentationFormSheet NS_ENUM_AVAILABLE_IOS(3_2) __TVOS_PROHIBITED,  //presented VC的高度和宽度均会小于屏幕尺寸，presented VC居中显示，四周留下变暗区域
    UIModalPresentationCurrentContext NS_ENUM_AVAILABLE_IOS(3_2),               //presented VC的弹出方式和presenting VC的父VC的方式相同,（跳转之后覆盖当前内容,除导航栏和标签栏部分）          注:这四种方式在iPad上面统统有效，但在iPhone和iPod touch上面系统始终已UIModalPresentationFullScreen模式显示presented VC
    UIModalPresentationCustom NS_ENUM_AVAILABLE_IOS(7_0),       //通过类UIPercentDrivenInteractiveTransition与协议UIViewControllerInteractiveTransitioning,协议UIViewControllerTransitioningDelegate自定义过场动画,参考:http://www.cnblogs.com/breezemist/p/3460497.html 跳转之后显示自定制视图（默认是覆盖整个屏幕），可以透明
    UIModalPresentationOverFullScreen NS_ENUM_AVAILABLE_IOS(8_0),       //效果跟UIModalPresentationFullScreen一样,不将原来的ViewController的view给unload掉,
    UIModalPresentationOverCurrentContext NS_ENUM_AVAILABLE_IOS(8_0),   //效果跟UIModalPresentationCurrentContext一样,不将原来的ViewController的view给unload掉
    UIModalPresentationPopover NS_ENUM_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED,    //以iPad形式弹出,参考:http://www.jianshu.com/p/d22cf0979787
    UIModalPresentationNone NS_ENUM_AVAILABLE_IOS(7_0) = -1,
};

@protocol UIContentContainer <NSObject>     //iOS8后加入的一组新协议，UIViewController对这组协议提供了默认的实现，我们自定义ViewConttroller的时候可以重写这些方法来调整视图布局

@property (nonatomic, readonly) CGSize preferredContentSize NS_AVAILABLE_IOS(8_0);      //容器期望的内容大小,我们可以使用preferredContentSize来设置我们期望的childViewController的界面的大小,控制器有一个可写的同名属性
- (void)preferredContentSizeDidChangeForChildContentContainer:(id <UIContentContainer>)container NS_AVAILABLE_IOS(8_0);     //这个方法告诉当前容器viewController期望的内容大小变了，我们可以在这个方法里根据新的size对界面进行调整

/*
 Intended as a bridge for a view controller that does not use auto layout presenting a child that does use auto layout.
 
 If the child's view is using auto layout and the -systemLayoutSizeFittingSize: of the view
 changes, -systemLayoutFittingSizeDidChangeForChildContentContainer: will be sent to the view controller's parent.
 */
/*
 给没有使用自动布局的控制器在present一个使用自动布局的控制器时候一个桥梁
 如果子控制器的视图在使用自动布局,并systemLayoutSizeFittingSize有变化的时候,将会调用这个方法通知视图的控制器的父控制器
 */
- (void)systemLayoutFittingSizeDidChangeForChildContentContainer:(id <UIContentContainer>)container NS_AVAILABLE_IOS(8_0);

/*
 When the content container forwards viewWillTransitionToSize:withTransitionCoordinator: to its children, it will call this method to determine what size to send them.
 
 If the returned size is the same as the child container's current size, viewWillTransitionToSize:withTransitionCoordinator: will not be called.
 */
/*
 在当前内容容器转发viewWillTransitionToSize:withTransitionCoordinator:消息到它的子内容时,将会调用这个方法决定发送什么size给子内容
 如果返回的size跟子内容当前size大小一致,那么将不会调用viewWillTransitionToSize:withTransitionCoordinator:
 依旧因为iOS8上size class概念的提出，UIViewConteroller支持了UIConntentContainer这样一组新的协议，重写这些方法可以调整视图布局，一个容器viewController可以使用这个方法设置childViewController的size，当容器viewControllerViewWillTransitionTosize：withTransitionCoordinator：被调用时（我们重写这个方法时要调用super），sizeForChildContentContainer方法将被调用。然后我们可以把需要设置desire发送给childViewController。当我们设置的这个size和当前childViewController的size一样，那么childViewController的viewWillTransitionToSize方法将不会被调用。sizeForChildContentContainer默认的实现是返回parentSize
 */
- (CGSize)sizeForChildContentContainer:(id <UIContentContainer>)container withParentContainerSize:(CGSize)parentSize NS_AVAILABLE_IOS(8_0);

/*
 This method is called when the view controller's view's size is changed by its parent (i.e. for the root view controller when its window rotates or is resized).
 
 If you override this method, you should either call super to propagate the change to children or manually forward the change to children.
 */
/*
 viewController的view的size被他的parent Controller改变时，会触发这个方法（比如rootViewController在它的window旋转或重新调整了size的时候）
 重写这个方法时，确保要调用super来保证size改变的这条消息能够正常传递给它的子内容,或者手动转发这些变化到它的子内容。
 */
- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id <UIViewControllerTransitionCoordinator>)coordinator NS_AVAILABLE_IOS(8_0);

/*
 This method is called when the view controller's trait collection is changed by its parent.
 
 If you override this method, you should either call super to propagate the change to children or manually forward the change to children.
 */
/*
 当viewController的traitCollection的值被它的父内容改变时会调用这个方法
 */
- (void)willTransitionToTraitCollection:(UITraitCollection *)newCollection withTransitionCoordinator:(id <UIViewControllerTransitionCoordinator>)coordinator NS_AVAILABLE_IOS(8_0);

@end

// Sometimes view controllers that are using showViewController:sender and showDetailViewController:sender: will need to know when the split view controller environment above it has changed. This notification will be posted when that happens (for example, when a split view controller is collapsing or expanding). The NSNotification's object will be the view controller that caused the change.
//有时控制器在使用showViewController:sender和showDetailViewController:sender:时需要知道在它上面的the split view controller environment 已经改变了,这个通知就会被发出(比如,当一个split view controller在折叠或展开的时候),这个通知的对象将会是导致这些变化的控制器
UIKIT_EXTERN NSNotificationName const UIViewControllerShowDetailTargetDidChangeNotification NS_AVAILABLE_IOS(8_0);
//UIViewController继承自UIResponder类，并实现NSCoding（实现归档操作），UIAppearanceContainer（允许开发者对UI控件通过定制都可以呈现各种外观），UITraitEnvironment（SizeClasses适配理念，通过内部的traitCollection属性，可以拿到对应的UITraitCollection对象，从而得知当前的SizeClass，进一步确定界面的布局），UIContentContainer协议（调整视图布局）,UIFocusEnvironment协议(定义视图图层的按压行为)
NS_CLASS_AVAILABLE_IOS(2_0) @interface UIViewController : UIResponder <NSCoding, UIAppearanceContainer, UITraitEnvironment, UIContentContainer, UIFocusEnvironment>

/*
 The designated initializer. If you subclass UIViewController, you must call the super implementation of this
 method, even if you aren't using a NIB.  (As a convenience, the default init method will do this for you,
 and specify nil for both of this methods arguments.) In the specified NIB, the File's Owner proxy should
 have its class set to your view controller subclass, with the view outlet connected to the main view. If you
 invoke this method with a nil nib name, then this class' -loadView method will attempt to load a NIB whose
 name is the same as your view controller's class. If no such NIB in fact exists then you must either call
 -setView: before -view is invoked, or override the -loadView method to set up your views programatically.
 */
/*
 指定构造器,如果你要继承UIViewController,那么即使你不使用xib也必须super调用这个方法.(为了方法,默认的init构造方法将会帮你传2个nil做为参数),如果指定了xib,那么这个xib拥有者必须有继承自控制器的类,这样可以连线到它的主view.如果调用这个方法时传入了一个空的xib名字,那么这个类的-loadView将会尝试去加载与你类名同名的xib.如果没有同名的xib,那么你必须调用在-view之前调用-setView:,或者重写-loadView方法去手动设置你的view
 */
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_DESIGNATED_INITIALIZER; //指定构造器
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
//如果这个view尚未设置,那么第一次get的时候回调用[self loadView],在重写它的setter或getter方法时,子类必须调用super
@property(null_resettable, nonatomic,strong) UIView *view; // The getter first invokes [self loadView] if the view hasn't been set yet. Subclasses must call super if they override the setter or getter.
//不应该直接调用.如果子类没有使用xib,那么在这里创建自己的视图图层
- (void)loadView; // This is where subclasses should create their custom view hierarchy if they aren't using a nib. Should never be called directly.
//如果视图还没有设置,那么久加载控制器的视图
- (void)loadViewIfNeeded NS_AVAILABLE_IOS(9_0); // Loads the view controller's view if it has not already been set.
//如果控制器视图已经加载,那么久返回它,否则返回nil
@property(nullable, nonatomic, readonly, strong) UIView *viewIfLoaded NS_AVAILABLE_IOS(9_0); // Returns the view controller's view if loaded, nil if not.
//视图将要被销毁,已弃用
- (void)viewWillUnload NS_DEPRECATED_IOS(5_0,6_0) __TVOS_PROHIBITED;
//视图已经被销毁,已弃用
- (void)viewDidUnload NS_DEPRECATED_IOS(3_0,6_0) __TVOS_PROHIBITED; // Called after the view controller's view is released and set to nil. For example, a memory warning which causes the view to be purged. Not invoked as a result of -dealloc.
//这个方法在view加载完毕后调用，如果是纯代码,将在-loadView后调用,xib的话讲在解压设置完视图后调用
- (void)viewDidLoad; // Called after the view has been loaded. For view controllers created in code, this is after -loadView. For view controllers unarchived from a nib, this is after the view is set.
#if UIKIT_DEFINE_AS_PROPERTIES  //如果作为属性的话
@property(nonatomic, readonly, getter=isViewLoaded) BOOL viewLoaded NS_AVAILABLE_IOS(3_0);
#else   //不作为属性调用
- (BOOL)isViewLoaded NS_AVAILABLE_IOS(3_0);
#endif
//用来实例化view的xib名字
@property(nullable, nonatomic, readonly, copy) NSString *nibName;     // The name of the nib to be loaded to instantiate the view.
//xib所在的资源路径,bundle是一个资源目录，包含nib文件
@property(nullable, nonatomic, readonly, strong) NSBundle *nibBundle; // The bundle from which to load the nib.
//实例化控制器的storyboard
@property(nullable, nonatomic, readonly, strong) UIStoryboard *storyboard NS_AVAILABLE_IOS(5_0);
//使用storyboard时利用segue进行页面跳转的方法
- (void)performSegueWithIdentifier:(NSString *)identifier sender:(nullable id)sender NS_AVAILABLE_IOS(5_0);
//在实例化一个segue前立即调用,决定是否执行segeue的动作。返回no则不执行segue动作,默认返回yes，执行动作.当使用-performSegueWithIdentifier:sender:时不会调用这个方法
- (BOOL)shouldPerformSegueWithIdentifier:(NSString *)identifier sender:(nullable id)sender NS_AVAILABLE_IOS(6_0); // Invoked immediately prior to initiating a segue. Return NO to prevent the segue from firing. The default implementation returns YES. This method is not invoked when -performSegueWithIdentifier:sender: is used.
//当segue快要触发前前，系统会自动调用这个方法
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(nullable id)sender NS_AVAILABLE_IOS(5_0);

// View controllers will receive this message during segue unwinding. The default implementation returns the result of -respondsToSelector: - controllers can override this to perform any ancillary checks, if necessary.
//在segue解包前控制器将会收到消息.默认的实现是返回-respondsToSelector:的结果,乳沟有必要,控制器可以重写这个方法做辅助的检查
- (BOOL)canPerformUnwindSegueAction:(SEL)action fromViewController:(UIViewController *)fromViewController withSender:(id)sender NS_AVAILABLE_IOS(6_0);

// Returns a subset of the receiver's childViewControllers in the order they should be searched for an unwind destination.
// The default implementation first sends itself -childViewControllerContainingSegueSource:, then returns a copy of its childViewControllers array excluding that object. A custom container view controller can override this method to affect the order in which its children are searched, or to modify the result of the default implementation.
// For compatibility, if a view controller overrides the deprecated -viewControllerForUnwindSegueAction:fromViewController:sender: method, but does not override this method, it will receive the deprecated method instead of this method.
// To affect this view controller's eligibility as an unwind destination, override -canPerformUnwindSegueAction:fromViewController:withSender: instead.
//按顺序返回接受者的可被实例化的子控制器集合
//默认的实现,第一个是返回控制器自己,其次是返回不包含自己的子控制器数组.自定义视图的控制器可以重写这个方法去改建被搜索子控制器的顺序,或者改名后面实现的结果
//为了兼容,如果控制器重写了被遗弃的 -viewControllerForUnwindSegueAction:fromViewController:sender:方法,但是不重写这个方法,将会收到此方法已经被遗弃,并用这个方法代替
//重写-canPerformUnwindSegueAction:fromViewController:withSender:方法可以让一个控制器可以成为一个可被解压的目标
- (NSArray<UIViewController *> *)allowedChildViewControllersForUnwindingFromSource:(UIStoryboardUnwindSegueSource *)source NS_AVAILABLE_IOS(9_0);

// Returns the child view controller that contains the provided segue source.
// Custom container view controllers should call this method from their implementation of -allowedChildViewControllersForUnwindingFromSource: to exclude the result from the returned array, as well as to determine the order of the returned array's contents.
// Do not try to re-implement or override this method; it takes special care to handle situations such as unwinding from a modally-presented view controller.
//返回包含被参数中segue的子控制器数组
//自定义视图控制器应该实现-allowedChildViewControllersForUnwindingFromSource:将这个结果从返回的数组中去掉,同时也确定了返回数组内容的顺序
//不要重试取重新实现或重写这个方法.在解包一个被modal出来的控制器时需要特别关注
- (nullable UIViewController *)childViewControllerContainingSegueSource:(UIStoryboardUnwindSegueSource *)source NS_AVAILABLE_IOS(9_0);

// Deprecated. Returns a direct child of the receiver that responds YES to -canPerformUnwindSegueAction:fromViewController:withSender:, or self if no children respond YES but the receiver itself does. If this method has been overridden, UIViewController's implementation does not consult child view controllers at all, and skips straight to sending -canPerformUnwindSegueAction:... to self.
//
//该方法已经被遗弃了.返回一个响应-allowedChildViewControllersForUnwindingFromSource:结果YES直接的子控制器接收者,如果没有自控制器子控制器返回YES,而自身响应返回YES则返回控制器本身.如果这个方面被重写,控制器的实现将不会查询子控制器,而是直接发送-canPerformUnwindSegueAction:...到自身
- (nullable UIViewController *)viewControllerForUnwindSegueAction:(SEL)action fromViewController:(UIViewController *)fromViewController withSender:(nullable id)sender NS_DEPRECATED_IOS(6_0, 9_0);

// Custom container view controllers should override this method to modify themselves as part of an ongoing unwind segue. The subsequentVC is the parent, child, or presented view controller closest to the receiver in the direction of the segue's destinationViewController. For example, UINavigationController's implementation of this method will pop any necessary view controllers to reveal the subsequentVC.
//自定义视图控制器应该重写这个方法去改变自己作为一个解包中的segue.subsequentVC是父控制器,子控制器,或被present出来的控制器中在segue目标控制器中最靠近的接收者.例如,导航控制器这个方法的实现将会pop出任何必要的视图取找到subsequentVC
- (void)unwindForSegue:(UIStoryboardSegue *)unwindSegue towardsViewController:(UIViewController *)subsequentVC NS_AVAILABLE_IOS(9_0);

// Deprecated. Returns a segue that will unwind from the source to destination view controller via the -unwindForSegue:towardViewController: method. When performing an unwind segue defined in a storyboard, if any view controller along the unwind path has overridden this method and returns non-nil, the runtime will use that segue object instead of constructing an instance of the class specified in Interface Builder.
//该方法以及被遗弃.返回一个通过-unwindForSegue:towardViewController:从资源处将要解包的segue.当在实现storyboard中segue动作时,如果任由要通过解包路径的控制器重写了这个方法而且返回非空值,那么运行时将会实例化IB中绑定的对象
- (nullable UIStoryboardSegue *)segueForUnwindingToViewController:(UIViewController *)toViewController fromViewController:(UIViewController *)fromViewController identifier:(nullable NSString *)identifier NS_DEPRECATED_IOS(6_0, 9_0);
//在视图马上可见的时候调用,默认不做任何事情
- (void)viewWillAppear:(BOOL)animated;    // Called when the view is about to made visible. Default does nothing
//在视图完全显示在屏幕上的时候调用,默认不做任何事情
- (void)viewDidAppear:(BOOL)animated;     // Called when the view has been fully transitioned onto the screen. Default does nothing
//在视图将要被transitioned,被覆盖或者其它形式的隐藏,默认不做任何事情
- (void)viewWillDisappear:(BOOL)animated; // Called when the view is dismissed, covered or otherwise hidden. Default does nothing
//在视图已经被transitioned,被覆盖或者其它形式的隐藏,默认不做任何事情
- (void)viewDidDisappear:(BOOL)animated;  // Called after the view was dismissed, covered or otherwise hidden. Default does nothing

// Called just before the view controller's view's layoutSubviews method is invoked. Subclasses can implement as necessary. The default is a nop.
//在控制器视图的layoutSubviews方法调用前调用.如果有必要,子类可以实现这个方法,默认不做任何事情
- (void)viewWillLayoutSubviews NS_AVAILABLE_IOS(5_0);
// Called just after the view controller's view's layoutSubviews method is invoked. Subclasses can implement as necessary. The default is a nop.
//在控制器视图的layoutSubviews方法调用后调用.如果有必要,子类可以实现这个方法,默认不做任何事情
- (void)viewDidLayoutSubviews NS_AVAILABLE_IOS(5_0);
//给父控制器使用的本地化标题
@property(nullable, nonatomic,copy) NSString *title;  // Localized title for use by a parent controller.
//当app在收到内存警告时调用,在iOS 6后默认不再清空视图
- (void)didReceiveMemoryWarning; // Called when the parent application receives a memory warning. On iOS 6.0 it will no longer clear the view by default.

/*
 If this view controller is a child of a containing view controller (e.g. a navigation controller or tab bar
 controller,) this is the containing view controller.  Note that as of 5.0 this no longer will return the
 presenting view controller.
 */
//如果控制器作为内容控制器(如导航控制器,分栏控制器)的子控制器,那么这个就是正包含这个控制器的内容控制器.注意,iOS 5后不再返回present这个控制器的控制器
@property(nullable,nonatomic,weak,readonly) UIViewController *parentViewController;

// This property has been replaced by presentedViewController.
//这个属性已经被presentedViewController代替了
@property(nullable, nonatomic,readonly) UIViewController *modalViewController NS_DEPRECATED_IOS(2_0, 6_0) __TVOS_PROHIBITED;

// The view controller that was presented by this view controller or its nearest ancestor.
//被这个控制器present出来的控制器,或者它的最近的父类
@property(nullable, nonatomic,readonly) UIViewController *presentedViewController  NS_AVAILABLE_IOS(5_0);

// The view controller that presented this view controller (or its farthest ancestor.)
//present这个控制器的控制器,或者这个控制器最远的父类
@property(nullable, nonatomic,readonly) UIViewController *presentingViewController NS_AVAILABLE_IOS(5_0);

/*
 Determines which parent view controller's view should be presented over for presentations of type
 UIModalPresentationCurrentContext.  If no ancestor view controller has this flag set, then the presenter
 will be the root view controller.
 */
//决定父控制器的视图是否被覆盖的presentations类型,如果没有父控制器有这个标识符,那么这个控制器将会是根控制器
@property(nonatomic,assign) BOOL definesPresentationContext NS_AVAILABLE_IOS(5_0);

// A controller that defines the presentation context can also specify the modal transition style if this property is true.
//如果这是属性是true,那么这个控制器决定了presentation上下文或指定modal transition 类型
@property(nonatomic,assign) BOOL providesPresentationContextTransitionStyle NS_AVAILABLE_IOS(5_0);

// If YES, when this view controller becomes visible and focusable, focus will be automatically restored to the item that was last focused. For example, when an item in this view controller is focused, and then another view controller is presented and dismissed, the original item will become focused again. Defaults to YES.
//如果为YES,当这个控制器变成可见或可按压的,按压事件将自动存储到这个最后按压的对象.例如,当控制器视图中一个空间被按压了,然后下一个控制器被present出来然后dismiss后,这个原来的可见将保持按压状态,默认是YES
@property (nonatomic) BOOL restoresFocusAfterTransition NS_AVAILABLE_IOS(10_0);

/*
 These four methods can be used in a view controller's appearance callbacks to determine if it is being
 presented, dismissed, or added or removed as a child view controller. For example, a view controller can
 check if it is disappearing because it was dismissed or popped by asking itself in its viewWillDisappear:
 method by checking the expression ([self isBeingDismissed] || [self isMovingFromParentViewController]).
 */
/*
 这四个方法将会用于控制器的出现回调将决定它是否被present,dismiss,或作为子控制器被添加或移除.例如,一个控制器可以检查它是否正在消失,因为它是否要被dismiss,或被pop,将在-viewWillDisappear:方法中通过检查表达式([self isBeingDismissed] || [self isMovingFromParentViewController])来问自己
 */
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly, getter=isBeingPresented) BOOL beingPresented NS_AVAILABLE_IOS(5_0);
@property(nonatomic, readonly, getter=isBeingDismissed) BOOL beingDismissed NS_AVAILABLE_IOS(5_0);

@property(nonatomic, readonly, getter=isMovingToParentViewController) BOOL movingToParentViewController NS_AVAILABLE_IOS(5_0);
@property(nonatomic, readonly, getter=isMovingFromParentViewController) BOOL movingFromParentViewController NS_AVAILABLE_IOS(5_0);
#else
- (BOOL)isBeingPresented NS_AVAILABLE_IOS(5_0);
- (BOOL)isBeingDismissed NS_AVAILABLE_IOS(5_0);

- (BOOL)isMovingToParentViewController NS_AVAILABLE_IOS(5_0);
- (BOOL)isMovingFromParentViewController NS_AVAILABLE_IOS(5_0);
#endif

/*
 The next two methods are replacements for presentModalViewController:animated and
 dismissModalViewControllerAnimated: The completion handler, if provided, will be invoked after the presented
 controllers viewDidAppear: callback is invoked.
 */
/*
 接下来的两个方法是方法presentModalViewController:animated 和 dismissModalViewControllerAnimated:方法的替代品.如果提供了回调,那么被present的控制器的viewDidAppear:调用后,这个回调将会被调用
 */
- (void)presentViewController:(UIViewController *)viewControllerToPresent animated: (BOOL)flag completion:(void (^ __nullable)(void))completion NS_AVAILABLE_IOS(5_0);
// The completion handler, if provided, will be invoked after the dismissed controller's viewDidDisappear: callback is invoked.
//如果提供了回调,那么被dismiss的控制器的viewDidAppear:调用后,这个回调将会被调用
- (void)dismissViewControllerAnimated: (BOOL)flag completion: (void (^ __nullable)(void))completion NS_AVAILABLE_IOS(5_0);

// Display another view controller as a modal child. Uses a vertical sheet transition if animated.This method has been replaced by presentViewController:animated:completion:
//将另一个控制器作为模态控制器展示出来,如果有动画的话,将会使用垂直转场动画,这个方法已经被presentViewController:animated:completion:代替
- (void)presentModalViewController:(UIViewController *)modalViewController animated:(BOOL)animated NS_DEPRECATED_IOS(2_0, 6_0) __TVOS_PROHIBITED;

// Dismiss the current modal child. Uses a vertical sheet transition if animated. This method has been replaced by dismissViewControllerAnimated:completion:
//dismiss当前模态控制器,如果有动画的话,将会使用垂直转场动画,这个方法已经被dismissViewControllerAnimated:completion:代替
- (void)dismissModalViewControllerAnimated:(BOOL)animated NS_DEPRECATED_IOS(2_0, 6_0) __TVOS_PROHIBITED;

/*
 Defines the transition style that will be used for this view controller when it is presented modally. Set
 this property on the view controller to be presented, not the presenter.  Defaults to
 UIModalTransitionStyleCoverVertical.
 */
/*
 决定这个控制器被present时的转场动画,而不是将被present的控制器,默认是UIModalTransitionStyleCoverVertical
 */
@property(nonatomic,assign) UIModalTransitionStyle modalTransitionStyle NS_AVAILABLE_IOS(3_0);
@property(nonatomic,assign) UIModalPresentationStyle modalPresentationStyle NS_AVAILABLE_IOS(3_2);
// This controls whether this view controller takes over control of the status bar's appearance when presented non-full screen on another view controller. Defaults to NO.
//当控制器被present到一个非全屏的控制器视图上时,这个控制器是否可以控制状态栏的出现情况,默认是NO
@property(nonatomic,assign) BOOL modalPresentationCapturesStatusBarAppearance NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;

// Presentation modes may keep the keyboard visible when not required. Default implementation affects UIModalPresentationFormSheet visibility.
//Presentation类型可以保留键盘可见即使没有必要的时候.默认实现影响UIModalPresentationFormSheet可视化效果
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic,assign) BOOL disablesAutomaticKeyboardDismissal NS_AVAILABLE_IOS(4_3);
#else
- (BOOL)disablesAutomaticKeyboardDismissal NS_AVAILABLE_IOS(4_3);
#endif
//在iOS 7时被遗弃,被下面的属性代替
@property(nonatomic,assign) BOOL wantsFullScreenLayout NS_DEPRECATED_IOS(3_0, 7_0) __TVOS_PROHIBITED; // Deprecated in 7_0, Replaced by the following:
//枚举,默认是UIRectEdgeAll
@property(nonatomic,assign) UIRectEdge edgesForExtendedLayout NS_AVAILABLE_IOS(7_0); // Defaults to UIRectEdgeAll
//默认是NO,但是Bars在7.0后默认是半透明的
// 不管navigationBar的backgroundImage如何设置，都让布局撑到屏幕顶部，方便布局的统一
@property(nonatomic,assign) BOOL extendedLayoutIncludesOpaqueBars NS_AVAILABLE_IOS(7_0); // Defaults to NO, but bars are translucent by default on 7_0.
//默认是YES,在有导航控制器的控制器视图中有scrollView时是否自动调整布局
@property(nonatomic,assign) BOOL automaticallyAdjustsScrollViewInsets NS_AVAILABLE_IOS(7_0); // Defaults to YES

/* The preferredContentSize is used for any container laying out a child view controller.
 */
/*preferredContentSize用于任何在布局子控制器的容器
 */
@property (nonatomic) CGSize preferredContentSize NS_AVAILABLE_IOS(7_0);

// These methods control the attributes of the status bar when this view controller is shown. They can be overridden in view controller subclasses to return the desired status bar attributes.
//在控制器可见时,这些方法管理状态栏的状态,控制器的子类可以重写这些方法来得到想要的状态栏属性
#if UIKIT_DEFINE_AS_PROPERTIES
//枚举,默认值是UIStatusBarStyleDefault
@property(nonatomic, readonly) UIStatusBarStyle preferredStatusBarStyle NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED; // Defaults to UIStatusBarStyleDefault
//默认是NO
@property(nonatomic, readonly) BOOL prefersStatusBarHidden NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED; // Defaults to NO
// Override to return the type of animation that should be used for status bar changes for this view controller. This currently only affects changes to prefersStatusBarHidden.
//重写取返回当控制器的状态栏发送变化时的动画类型,这个现在只影响prefersStatusBarHidden的变化,默认是UIStatusBarAnimationFade
@property(nonatomic, readonly) UIStatusBarAnimation preferredStatusBarUpdateAnimation NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED; // Defaults to UIStatusBarAnimationFade
#else
- (UIStatusBarStyle)preferredStatusBarStyle NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED; // Defaults to UIStatusBarStyleDefault
- (BOOL)prefersStatusBarHidden NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED; // Defaults to NO
// Override to return the type of animation that should be used for status bar changes for this view controller. This currently only affects changes to prefersStatusBarHidden.
- (UIStatusBarAnimation)preferredStatusBarUpdateAnimation NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED; // Defaults to UIStatusBarAnimationFade
#endif

// This should be called whenever the return values for the view controller's status bar attributes have changed. If it is called from within an animation block, the changes will be animated along with the rest of the animation block.
//这个方法将在控制器的状态栏属性值变化的时候调用,如果这是在动画回调中调用,这些变化持续时间将会跟动画时间一样长
- (void)setNeedsStatusBarAppearanceUpdate NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;

/* This method returns either itself or the nearest ancestor that can perform the given action and, if applicable, has overridden UIViewController's default implementation of the action method. View controllers can return NO from canPerformAction:withSender: to opt out of being a target for a given action. */
/*这个方法将会返回可以执行指定的动画的控制器本身或者最近的父类.如果适用,重写控制器对这个动作的默认实现.控制器可以从-canPerformAction:withSender:返回NO来不成为这个给定动作的目标
 */
- (nullable UIViewController *)targetViewControllerForAction:(SEL)action sender:(nullable id)sender NS_AVAILABLE_IOS(8_0);

/* This method will show a view controller appropriately for the current size-class environment. It's implementation calls
 `[self targetViewControllerForAction:sender:]` first and redirects accordingly if the return value is not `self`, otherwise it will present the vc. */
/*这个方法将会在当前size-class环境中恰当的展示一个控制器.这个实现第一个调用是在[self targetViewControllerForAction:sender:]中,如果返回的不是自己,那么将会立即调整,换句话说就会present这个控制器*/
- (void)showViewController:(UIViewController *)vc sender:(nullable id)sender NS_AVAILABLE_IOS(8_0);

/* This method will show a view controller within the semantic "detail" UI associated with the current size-class environment. It's implementation calls  `[self targetViewControllerForAction:sender:]` first and redirects accordingly if the return value is not `self`, otherwise it will present the vc.  */
/*这个方法将会在当前size-class环境中在"detail"语意上取展示一个控制器.这个实现第一个调用是在[self targetViewControllerForAction:sender:]中,如果返回的不是自己,那么将会立即调整,换句话说就会present这个控制器*/
- (void)showDetailViewController:(UIViewController *)vc sender:(nullable id)sender NS_AVAILABLE_IOS(8_0);

@end

// To make it more convenient for applications to adopt rotation, a view controller may implement the below methods. Your UIWindow's frame should use [UIScreen mainScreen].bounds as its frame.
//为了让app更好的去适应旋转,一个控制器可以实现下面的方法,你的UIWindow's frame 应该使用 [UIScreen mainScreen].bounds 作为它的值.
@interface UIViewController (UIViewControllerRotation)

// call this method when your return value from shouldAutorotateToInterfaceOrientation: changes
// if the current interface orientation does not match the current device orientation, a rotation may occur provided all relevant view controllers now return YES from shouldAutorotateToInterfaceOrientation:
//当shouldAutorotateToInterfaceOrientation:的返回值变化的时候将会调用这个方法
//如果当前的用户视图界面屏幕方向不符合设备方向,一个旋转将会发生在所有相关的shouldAutorotateToInterfaceOrientation:返回YES的控制器
+ (void)attemptRotationToDeviceOrientation NS_AVAILABLE_IOS(5_0) __TVOS_PROHIBITED;

// Applications should use supportedInterfaceOrientations and/or shouldAutorotate..
//app应该使用supportedInterfaceOrientations或者shouldAutorotate
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation NS_DEPRECATED_IOS(2_0, 6_0) __TVOS_PROHIBITED;

// New Autorotation support.
//新的自动旋转提供的api
#if UIKIT_DEFINE_AS_PROPERTIES
//应该自动旋转
@property(nonatomic, readonly) BOOL shouldAutorotate NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
@property(nonatomic, readonly) UIInterfaceOrientationMask supportedInterfaceOrientations NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
// Returns interface orientation masks.
//返回界面旋转面具
@property(nonatomic, readonly) UIInterfaceOrientation preferredInterfaceOrientationForPresentation NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
#else
- (BOOL)shouldAutorotate NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
- (UIInterfaceOrientationMask)supportedInterfaceOrientations NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
// Returns interface orientation masks.
- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
#endif

// The rotating header and footer views will slide out during the rotation and back in once it has completed.
//旋转的头和尾视图将会在旋转期间滑出,并在旋转完成时回来
//必须在视图图层中,默认返回nil
- (nullable UIView *)rotatingHeaderView NS_DEPRECATED_IOS(2_0,8_0, "Header views are animated along with the rest of the view hierarchy") __TVOS_PROHIBITED;     // Must be in the view hierarchy. Default returns nil.
- (nullable UIView *)rotatingFooterView NS_DEPRECATED_IOS(2_0,8_0, "Footer views are animated along with the rest of the view hierarchy") __TVOS_PROHIBITED;     // Must be in the view hierarchy. Default returns nil.

@property(nonatomic,readonly) UIInterfaceOrientation interfaceOrientation NS_DEPRECATED_IOS(2_0,8_0) __TVOS_PROHIBITED;

// Notifies when rotation begins, reaches halfway point and ends.
//在旋转开始,中途点和终点时的通知
- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration NS_DEPRECATED_IOS(2_0,8_0, "Implement viewWillTransitionToSize:withTransitionCoordinator: instead") __TVOS_PROHIBITED;
- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation NS_DEPRECATED_IOS(2_0,8_0) __TVOS_PROHIBITED;

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration NS_DEPRECATED_IOS(3_0,8_0, "Implement viewWillTransitionToSize:withTransitionCoordinator: instead") __TVOS_PROHIBITED;

- (void)willAnimateFirstHalfOfRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration NS_DEPRECATED_IOS(2_0, 5_0) __TVOS_PROHIBITED;
//旋转的头视图和尾视图已经离屏
- (void)didAnimateFirstHalfOfRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation NS_DEPRECATED_IOS(2_0, 5_0) __TVOS_PROHIBITED; // The rotating header and footer views are offscreen.
//在这时,我们的视图已经设置到新的旋转方向上了
- (void)willAnimateSecondHalfOfRotationFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation duration:(NSTimeInterval)duration NS_DEPRECATED_IOS(2_0, 5_0) __TVOS_PROHIBITED; // A this point, our view orientation is set to the new orientation.

@end

// Many view controllers have a view that may be in an editing state or not- for example, a UITableView.  These view
// controllers can track the editing state, and generate an Edit|Done button to be used in a navigation bar.
//很多控制器有子视图也许有编辑状态,例如,一个tableview.这些控制器可以跟涨这些编辑状态,然后生成一个编辑或完成按钮在导航栏上
@interface UIViewController (UIViewControllerEditing)
//如果有必要,更新变化或完成按钮.重写这个的必须先调用super
@property(nonatomic,getter=isEditing) BOOL editing;
- (void)setEditing:(BOOL)editing animated:(BOOL)animated; // Updates the appearance of the Edit|Done button item as necessary. Clients who override it must call super first.

#if UIKIT_DEFINE_AS_PROPERTIES
//返回在导航栏上可用编辑或完成自定义按钮.默认这些动作触发带有编辑的动画
@property(nonatomic, readonly) UIBarButtonItem *editButtonItem; // Return an Edit|Done button that can be used as a navigation item's custom view. Default action toggles the editing state with animation.
#else
- (UIBarButtonItem *)editButtonItem; // Return an Edit|Done button that can be used as a navigation item's custom view. Default action toggles the editing state with animation.
#endif

@end

@interface UIViewController (UISearchDisplayControllerSupport)

@property(nullable, nonatomic, readonly, strong) UISearchDisplayController *searchDisplayController NS_DEPRECATED_IOS(3_0,8_0) __TVOS_PROHIBITED;

@end


/*
 This exception is raised when a child view controller's view is added into the view hierarchy and the first
 superview of the child view controller's view that has a view controller is NOT the child view controller's
 parent.
 */
/*这个表达式将会在子控制器的视图被加入到视图图层中,而且它的第一个父视图的控制器不是这个控制器的父控制器时调用
 */
UIKIT_EXTERN NSExceptionName const UIViewControllerHierarchyInconsistencyException NS_AVAILABLE_IOS(5_0);

/*
 The methods in the UIContainerViewControllerProtectedMethods and the UIContainerViewControllerCallbacks
 categories typically should only be called by subclasses which are implementing new container view
 controllers. They may be overridden but must call super.
 */
/*这个UIContainerViewControllerProtectedMethods协议中的方法和UIContainerViewControllerCallbacks的分类应该仅在实现了添加新的控制器的子类中调用
 */
@interface UIViewController (UIContainerViewControllerProtectedMethods)

// An array of children view controllers. This array does not include any presented view controllers.
//一个子控制器的数字.这个数组不包括任何被这个控制器present出来的控制器
@property(nonatomic,readonly) NSArray<__kindof UIViewController *> *childViewControllers NS_AVAILABLE_IOS(5_0);

/*
 If the child controller has a different parent controller, it will first be removed from its current parent
 by calling removeFromParentViewController. If this method is overridden then the super implementation must
 be called.
 */
/*如果子控制器的当前父控制器不是这个控制器,它应该先调用removeFromParentViewController从当前控制器中移除.如果这个方面被重写,必须调用super
 */
- (void)addChildViewController:(UIViewController *)childController NS_AVAILABLE_IOS(5_0);

/*
 Removes the the receiver from its parent's children controllers array. If this method is overridden then
 the super implementation must be called.
 */
/*将当前控制器从它的父控制器的子控制器数组中移除,如果这个方法被重写,必须调用super
 */
- (void)removeFromParentViewController NS_AVAILABLE_IOS(5_0);

/*
 This method can be used to transition between sibling child view controllers. The receiver of this method is
 their common parent view controller. (Use [UIViewController addChildViewController:] to create the
 parent/child relationship.) This method will add the toViewController's view to the superview of the
 fromViewController's view and the fromViewController's view will be removed from its superview after the
 transition completes. It is important to allow this method to add and remove the views. The arguments to
 this method are the same as those defined by UIView's block animation API. This method will fail with an
 NSInvalidArgumentException if the parent view controllers are not the same as the receiver, or if the
 receiver explicitly forwards its appearance and rotation callbacks to its children. Finally, the receiver
 should not be a subclass of an iOS container view controller. Note also that it is possible to use the
 UIView APIs directly. If they are used it is important to ensure that the toViewController's view is added
 to the visible view hierarchy while the fromViewController's view is removed.
 */
/*这个方法使用在同一个控制器的子控制器数组中两个兄弟控制器转场中.方法的接收者有相同的父控制器.(可以使用[UIViewController addChildViewController:]去创建父/子控制器关系)这个方法将会添加toViewController的视图到fromViewController视图的父视图上,在转场完成后fromViewController的视图也会从它的父视图上移除.如果接收者对它的子控制器有明确的转发回调跟转场回调,这些方法参数跟UIView动画回调API中的一样.最后,接收者一个不应该是视图控制器UIViewController的子类.注意的是.它也有可能直接使用UIView的API.如果要使用他们,确保当toViewController's的视图被移除是,toViewController的视图被添加到的是一个可见的视图图层是非常重要的
 */
- (void)transitionFromViewController:(UIViewController *)fromViewController toViewController:(UIViewController *)toViewController duration:(NSTimeInterval)duration options:(UIViewAnimationOptions)options animations:(void (^ __nullable)(void))animations completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(5_0);

// If a custom container controller manually forwards its appearance callbacks, then rather than calling
// viewWillAppear:, viewDidAppear: viewWillDisappear:, or viewDidDisappear: on the children these methods
// should be used instead. This will ensure that descendent child controllers appearance methods will be
// invoked. It also enables more complex custom transitions to be implemented since the appearance callbacks are
// now tied to the final matching invocation of endAppearanceTransition.
//如果自定义控制器需手动转发它的出现回调,那么子控制器的viewWillAppear:, viewDidAppear: viewWillDisappear:, or viewDidDisappear:方法应该被代替.这个会确保派生的子控制器的声明周期方法会被调用,同时也保证了更复杂的自定义转场将会被调用及时声明周期函数被绑定在endAppearanceTransition的最终实现上
- (void)beginAppearanceTransition:(BOOL)isAppearing animated:(BOOL)animated __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
- (void)endAppearanceTransition __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

// Override to return a child view controller or nil. If non-nil, that view controller's status bar appearance attributes will be used. If nil, self is used. Whenever the return values from these methods change, -setNeedsUpdatedStatusBarAttributes should be called.
//重写去返回一个将要用于控制状态栏状态的子控制器或nil,如果nil.那么将使用当前控制器的状态栏状态.任何时候返回的值改变的时候方法-setNeedsUpdatedStatusBarAttributes将会被调用
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly, nullable) UIViewController *childViewControllerForStatusBarStyle NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
@property(nonatomic, readonly, nullable) UIViewController *childViewControllerForStatusBarHidden NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
#else
- (nullable UIViewController *)childViewControllerForStatusBarStyle NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
- (nullable UIViewController *)childViewControllerForStatusBarHidden NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
#endif

// Call to modify the trait collection for child view controllers.
//调用去改变子控制器集合的特征
- (void)setOverrideTraitCollection:(nullable UITraitCollection *)collection forChildViewController:(UIViewController *)childViewController NS_AVAILABLE_IOS(8_0);
- (nullable UITraitCollection *)overrideTraitCollectionForChildViewController:(UIViewController *)childViewController NS_AVAILABLE_IOS(8_0);

@end

@interface UIViewController (UIContainerViewControllerCallbacks)

/*
 This method is consulted to determine if a view controller manually forwards its containment callbacks to
 any children view controllers. Subclasses of UIViewController that implement containment logic may override
 this method. The default implementation returns YES. If it is overridden and returns NO, then the subclass is
 responsible for forwarding the following methods as appropriate - viewWillAppear: viewDidAppear: viewWillDisappear:
 viewDidDisappear: willRotateToInterfaceOrientation:duration:
 willAnimateRotationToInterfaceOrientation:duration: didRotateFromInterfaceOrientation:
 */
/*
 这个方法将被咨询取确定是否控制器手动转发它的内容回调到它的子控制器.实现内容逻辑的控制器的子类可以重写这个方法.默认的实现是否返回YES.如果它被重写了,而且返回了NO,那么这个子类需要对下面方法负责:- viewWillAppear: viewDidAppear: viewWillDisappear:
 viewDidDisappear: willRotateToInterfaceOrientation:duration:
 willAnimateRotationToInterfaceOrientation:duration: didRotateFromInterfaceOrientation:
 */
- (BOOL)automaticallyForwardAppearanceAndRotationMethodsToChildViewControllers NS_DEPRECATED_IOS(5_0,6_0) __TVOS_PROHIBITED;
- (BOOL)shouldAutomaticallyForwardRotationMethods NS_DEPRECATED_IOS(6_0,8_0, "Manually forward viewWillTransitionToSize:withTransitionCoordinator: if necessary") __TVOS_PROHIBITED;

#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) BOOL shouldAutomaticallyForwardAppearanceMethods NS_AVAILABLE_IOS(6_0);
#else
- (BOOL)shouldAutomaticallyForwardAppearanceMethods NS_AVAILABLE_IOS(6_0);
#endif


/*
 These two methods are public for container subclasses to call when transitioning between child
 controllers. If they are overridden, the overrides should ensure to call the super. The parent argument in
 both of these methods is nil when a child is being removed from its parent; otherwise it is equal to the new
 parent view controller.
 
 addChildViewController: will call [child willMoveToParentViewController:self] before adding the
 child. However, it will not call didMoveToParentViewController:. It is expected that a container view
 controller subclass will make this call after a transition to the new child has completed or, in the
 case of no transition, immediately after the call to addChildViewController:. Similarly,
 removeFromParentViewController does not call [self willMoveToParentViewController:nil] before removing the
 child. This is also the responsibilty of the container subclass. Container subclasses will typically define
 a method that transitions to a new child by first calling addChildViewController:, then executing a
 transition which will add the new child's view into the view hierarchy of its parent, and finally will call
 didMoveToParentViewController:. Similarly, subclasses will typically define a method that removes a child in
 the reverse manner by first calling [child willMoveToParentViewController:nil].
 */
/*
 这两个方法在同一个内容中的子控制器中发生转场的时候调用的.如果被重写了,必须调用super.参数parent在子控制器被移除后都会是nil,另外它等价于它的新父控制器.
 addChildViewController: 将会在加入新的子控制器前调用[child willMoveToParentViewController:self].然而,它不会调用didMoveToParentViewController:.内容控制器的子类应该在子控制器转场后让这个方法调用,或者在调用完addChildViewController:立即调用这个方法.同样的,removeFromParentViewController也不会在移除子控制器前调用[self willMoveToParentViewController:nil].这个应该由内容中子类来实现.内容子类应该特别定义一个方法:在添加一个子控制器时第一次调用addChildViewController:后执行把子控制器的视图添加到父控制器的视图层级上时执行一个转场动画,然后最后调用didMoveToParentViewController:.同样的,子类应该特别定义一个方法:在第一次调用[child willMoveToParentViewController:nil]以相反的方式移除子控制器
 */
//当addChildViewController:接口建立了逻辑上的父子关系，接口的逻辑中会自动调用willMoveToParentViewController这个方法，在即将移动显示ParentViewController的时候调用
- (void)willMoveToParentViewController:(nullable UIViewController *)parent NS_AVAILABLE_IOS(5_0);
- (void)didMoveToParentViewController:(nullable UIViewController *)parent NS_AVAILABLE_IOS(5_0);

@end
//UIStateRestoration提供持久数据的接口
@interface UIViewController (UIStateRestoration) <UIStateRestoring>
//这个属性是用来标示是否支持保存、恢复视图状态信息
@property (nullable, nonatomic, copy) NSString *restorationIdentifier NS_AVAILABLE_IOS(6_0);
@property (nullable, nonatomic, readwrite, assign) Class<UIViewControllerRestoration> restorationClass NS_AVAILABLE_IOS(6_0);
//保存视图状态相关信息
- (void) encodeRestorableStateWithCoder:(NSCoder *)coder NS_AVAILABLE_IOS(6_0);
//恢复和保持视图状态相关信息
- (void) decodeRestorableStateWithCoder:(NSCoder *)coder NS_AVAILABLE_IOS(6_0);
//对象解码完成后，系统会调用此方法
- (void) applicationFinishedRestoringState NS_AVAILABLE_IOS(7_0);
@end
//增加分类基于布局约束的核心方法
@interface UIViewController (UIConstraintBasedLayoutCoreMethods)
/* Base implementation sends -updateConstraints to the view.
 When a view has a view controller, this message is sent to the view controller during
 the autolayout updateConstraints pass in lieu of sending updateConstraints directly
 to the view.
 You may override this method in a UIViewController subclass for updating custom
 constraints instead of subclassing your view and overriding -[UIView updateConstraints].
 Overrides must call super or send -updateConstraints to the view.
 */
/*
 基本实现是发送-updateConstraints给视图
 当视图被控制器管理的时候,这个消息将会在更新约束时会发给控制器而不是直接发给视图
 在控制器子类中重写这个方法去更新自定义约束而不是在这是视图子类中重写-[UIView updateConstraints]
 重写必须调用super,或者发送-updateConstraints给视图
 */
- (void)updateViewConstraints NS_AVAILABLE_IOS(6_0);
@end
//viewController过渡的代理协议
@protocol UIViewControllerTransitioningDelegate;

@interface UIViewController(UIViewControllerTransitioning)
//实例化协议属性
@property (nullable, nonatomic, weak) id <UIViewControllerTransitioningDelegate> transitioningDelegate NS_AVAILABLE_IOS(7_0);

@end

@interface UIViewController (UILayoutSupport)
// These objects may be used as layout items in the NSLayoutConstraint API
//这个属性是通过计算viewController->view->top到覆盖这个view最下层的那个bar-bottom的距离
@property(nonatomic,readonly,strong) id<UILayoutSupport> topLayoutGuide NS_AVAILABLE_IOS(7_0);
//这个属性是通过计算viewController->view->bottom到覆盖这个biew上层那个bar-top的距离
@property(nonatomic,readonly,strong) id<UILayoutSupport> bottomLayoutGuide NS_AVAILABLE_IOS(7_0);
@end
//自定义快捷键
@interface UIViewController (UIKeyCommand)

- (void)addKeyCommand:(UIKeyCommand *)keyCommand NS_AVAILABLE_IOS(9_0);
- (void)removeKeyCommand:(UIKeyCommand *)keyCommand NS_AVAILABLE_IOS(9_0);

@end
//引入NSExtensionContext类，iOS8新增的一个跨站上下文属性的extensionContext，来处理containing app与扩展之间的通信，上下文的类型是NSExtensionContext。
@class NSExtensionContext;

@interface UIViewController(NSExtensionAdditions) <NSExtensionRequestHandling>

// Returns the extension context. Also acts as a convenience method for a view controller to check if it participating in an extension request.
//实例化NSExtensionContext属性,同时为控制器检查是否参加了一个拓展请求提供了方便
@property (nullable, nonatomic,readonly,strong) NSExtensionContext *extensionContext NS_AVAILABLE_IOS(8_0);

@end

@class UIPresentationController, UIPopoverPresentationController;

@interface UIViewController (UIAdaptivePresentations)
//最近的管理当前控制器的presentation控制器,如果这个控制器并不是由presentation管理的,那么就是nil
@property (nullable, nonatomic,readonly) UIPresentationController *presentationController NS_AVAILABLE_IOS(8_0);
////最近的管理当前控制器的popover presentation控制器
@property (nullable, nonatomic,readonly) UIPopoverPresentationController *popoverPresentationController NS_AVAILABLE_IOS(8_0);
@end


@protocol UIViewControllerPreviewingDelegate;

@protocol UIViewControllerPreviewing <NSObject>

// This gesture can be used to cause the previewing presentation to wait until one of your gestures fails or to allow simultaneous recognition during the initial phase of the preview presentation.
//这个手势可以在手势未失效前一直有预览展示,或者在初始化预览展示的同时同时识别手势
@property (nonatomic, readonly) UIGestureRecognizer *previewingGestureRecognizerForFailureRelationship NS_AVAILABLE_IOS(9_0);

@property (nonatomic, readonly) id<UIViewControllerPreviewingDelegate> delegate NS_AVAILABLE_IOS(9_0);
@property (nonatomic, readonly) UIView *sourceView NS_AVAILABLE_IOS(9_0);

// This rect will be set to the bounds of sourceView before each call to
// -previewingContext:viewControllerForLocation:
//这个rect可以用在来调用-previewingContext:viewControllerForLocation:前设置sourceView的bounds
@property (nonatomic) CGRect sourceRect NS_AVAILABLE_IOS(9_0);

@end


NS_CLASS_AVAILABLE_IOS(9_0) @protocol UIViewControllerPreviewingDelegate <NSObject>

// If you return nil, a preview presentation will not be performed
//如果返回nil,那么将不会有预览
- (nullable UIViewController *)previewingContext:(id <UIViewControllerPreviewing>)previewingContext viewControllerForLocation:(CGPoint)location NS_AVAILABLE_IOS(9_0);
- (void)previewingContext:(id <UIViewControllerPreviewing>)previewingContext commitViewController:(UIViewController *)viewControllerToCommit NS_AVAILABLE_IOS(9_0);

@end

@interface UIViewController (UIViewControllerPreviewingRegistration)

// Registers a view controller to participate with 3D Touch preview (peek) and commit (pop).
//注册一个控制器给3D Touch去预言与提交
- (id <UIViewControllerPreviewing>)registerForPreviewingWithDelegate:(id<UIViewControllerPreviewingDelegate>)delegate sourceView:(UIView *)sourceView NS_AVAILABLE_IOS(9_0);
- (void)unregisterForPreviewingWithContext:(id <UIViewControllerPreviewing>)previewing NS_AVAILABLE_IOS(9_0);

@end

@protocol UIPreviewActionItem;

@interface UIViewController ()

#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) NSArray <id <UIPreviewActionItem>> *previewActionItems NS_AVAILABLE_IOS(9_0);
#else
- (NSArray <id <UIPreviewActionItem>> *)previewActionItems NS_AVAILABLE_IOS(9_0);
#endif

@end


NS_CLASS_AVAILABLE_IOS(9_0) @protocol UIPreviewActionItem <NSObject>
@property(nonatomic, copy, readonly) NSString *title;
@end

typedef NS_ENUM(NSInteger,UIPreviewActionStyle) {
    UIPreviewActionStyleDefault=0,
    UIPreviewActionStyleSelected,
    UIPreviewActionStyleDestructive,
} NS_ENUM_AVAILABLE_IOS(9_0);

NS_CLASS_AVAILABLE_IOS(9_0) @interface UIPreviewAction : NSObject <NSCopying,UIPreviewActionItem>

@property(nonatomic, copy, readonly) void (^handler)(id<UIPreviewActionItem> action, UIViewController *previewViewController);

+ (instancetype)actionWithTitle:(NSString *)title style:(UIPreviewActionStyle)style handler:(void (^)(UIPreviewAction *action, UIViewController *previewViewController))handler;

@end

NS_CLASS_AVAILABLE_IOS(9_0) @interface UIPreviewActionGroup : NSObject <NSCopying,UIPreviewActionItem>
+ (instancetype)actionGroupWithTitle:(NSString *)title style:(UIPreviewActionStyle)style actions:(NSArray<UIPreviewAction *> *)actions;
@end

NS_ASSUME_NONNULL_END       //#define NS_ASSUME_NONNULL_END   _Pragma("clang assume_nonnull end")
