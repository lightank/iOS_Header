/*	NSObject.h
	Copyright (c) 1994-2012, Apple Inc. All rights reserved.
 */

#ifndef _OBJC_NSOBJECT_H_
#define _OBJC_NSOBJECT_H_

#if __OBJC__

#include <objc/objc.h>
#include <objc/NSObjCRuntime.h>

@class NSString, NSMethodSignature, NSInvocation;

//参考自:http://www.jianshu.com/p/64d6bae3960a http://www.jianshu.com/p/6d9a99ba3f06

@protocol NSObject
//"=="判断是否是同一个对象，比较的是内存地址。"isEqual"判断两个对像是否相同，比较的是成员变量的值是否相同
- (BOOL)isEqual:(id)object;
//Returns an integer that can be used as a table address in a hash table structure.
//Hash Table的key,用于set和dictionary,默认是对象在内存中的地址，保证了唯一性。
@property (readonly) NSUInteger hash;
//对象的父类， NSObject实例的superclass为NULL
@property (readonly) Class superclass;
//获得对象的类。‘+(Class)class;’获得的是类对象的元类；
- (Class)class OBJC_SWIFT_UNAVAILABLE("use 'type(of: anObject)' instead");
//获得对象自己
- (instancetype)self;
//使对象调用某个方法，object是参数，最多有两个
- (id)performSelector:(SEL)aSelector;
- (id)performSelector:(SEL)aSelector withObject:(id)object;
- (id)performSelector:(SEL)aSelector withObject:(id)object1 withObject:(id)object2;
//是否是NSProxy的实例;NSObject是大多数类的基类，例外一部分就是NSProxy的实例了。NSProxy是一个非常神奇的类，可以用来模仿多继承，因为它可以转发消息，指定一个实例执行消息
- (BOOL)isProxy;
//判断某个对象是否是某个类或者子类的实例。
- (BOOL)isKindOfClass:(Class)aClass;
// 判断某个对象是否是某个类的实例.
- (BOOL)isMemberOfClass:(Class)aClass;
//判断某个实例是否遵守协议，是否实现了协议里的方法不一定。这个方法只能判断是否声明了协议了里的方法，是否实现得用"respondsToSelector"判断
- (BOOL)conformsToProtocol:(Protocol *)aProtocol;
//是否响应了某个方法。代理传值之前，必须判断是否是响应了协议里的方法，否则会崩溃
- (BOOL)respondsToSelector:(SEL)aSelector;
//现在都是ARC了，还调用MRC才能使用的方法，真是太落伍了
- (instancetype)retain OBJC_ARC_UNAVAILABLE;
- (oneway void)release OBJC_ARC_UNAVAILABLE;
- (instancetype)autorelease OBJC_ARC_UNAVAILABLE;
- (NSUInteger)retainCount OBJC_ARC_UNAVAILABLE;

- (struct _NSZone *)zone OBJC_ARC_UNAVAILABLE;
// description是代码打印输出实例的时候调用的方法，debugDescription是控制台也就是po的时候输出实例的时候调用的方法，都可以自定义。其实NSObject协议里的方法都可以根据自己的需求自定义
@property (readonly, copy) NSString *description;
@optional
@property (readonly, copy) NSString *debugDescription;

@end


OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0)
OBJC_ROOT_CLASS
OBJC_EXPORT
@interface NSObject <NSObject> {
    Class isa  OBJC_ISA_AVAILABILITY;
}
/*
 Invoked whenever a class or category is added to the Objective-C runtime; implement this method to perform class-specific behavior upon loading.
 
 The load message is sent to classes and categories that are both dynamically loaded and statically linked, but only if the newly loaded class or category implements a method that can respond.
 
 The order of initialization is as follows:
 
     1. All initializers in any framework you link to.
     
     2. All +load methods in your image.
     
     3. All C++ static initializers and C/C++ __attribute__(constructor) functions in your image.
     
     4. All initializers in frameworks that link to you.
 
 In addition:
 
     A class’s +load method is called after all of its superclasses’ +load methods.
     
     A category +load method is called after the class’s own +load method.
     
     In a custom implementation of load you can therefore safely message other unrelated classes from the same image, but any load methods implemented by those classes may not have run yet.
 */
/*
 当class或者category添加到runtime的时候会被唤醒。对于动态库和静态库中的class和category都有效。程序代码加载的顺序为：
     1.调用所有Framework中的初始化函数
     2.调用镜像中所有类的+load函数
     3.调用C++静态初始化函数和C/C++ __attribute__(constructor)函数
     4.调用所有链接到目标文件的Framework中的初始化函数
 换句话来说，load方法是在这个文件被程序装载时调用，因此load方法是在main方法之前调用
 load函数的加载顺序为：superClass -> class -> category,很明显系统会先调用所有类的+load()方法，然后再根据类调用相应的category，并且也是父类的+load()方法先被调用
 
 load 可以说我们在日常开发中可以接触到的调用时间最靠前的方法，在主函数运行之前，load 方法就会调用。由于它的调用不是惰性的，且其只会在程序调用期间调用一次，最最重要的是，如果在类与分类中都实现了 load 方法，它们都会被调用，不像其它的在分类中实现的方法会被覆盖，这就使 load 方法成为了方法调剂的绝佳时机。但是由于 load 方法的运行时间过早，所以这里可能不是一个理想的环境，因为某些类可能需要在在其它类之前加载，但是这是我们无法保证的。不过在这个时间点，所有的 framework 都已经加载到了运行时中，所以调用 framework 中的方法都是安全的
 
 镜像images:
 ...
 (const dyld_image_info) $53 = {
     imageLoadAddress = 0x00007fff946d9000
     imageFilePath = 0x00007fff946d9480 "/usr/lib/liblangid.dylib"
     imageFileModDate = 1452737618
 }
 (const dyld_image_info) $54 = {
     imageLoadAddress = 0x00007fff88016000
     imageFilePath = 0x00007fff88016d40 "/System/Library/Frameworks/Foundation.framework/Versions/C/Foundation"
     imageFileModDate = 1452737917
 }
 ...
 
 Q：load 方法是如何被调用的？
 
 A：当 Objective-C 运行时初始化的时候，会通过 dyld_register_image_state_change_handler 在每次有新的镜像加入运行时的时候，进行回调。执行 load_images 将所有包含 load 方法的文件加入列表 loadable_classes ，然后从这个列表中找到对应的 load 方法的实现，调用 load 方法。
 
 加载的管理:
 ObjC 对于加载的管理，主要使用了两个列表，分别是 loadable_classes 和 loadable_categories。
 方法的调用过程也分为两个部分，准备 load 方法和调用 load 方法，我更觉得这两个部分比较像生产者与消费者
 add_class_to_loadable_list 方法负责将类加入 loadable_classes 集合，而 call_class_loads 负责消费集合中的元素,而对于分类来说，其模型也是类似的，只不过使用了另一个列表 loadable_categories,
 “生产” loadable_class
 在调用 load_images -> load_images_nolock -> prepare_load_methods -> schedule_class_load -> add_class_to_loadable_list 的时候会将未加载的类添加到 loadable_classes 数组中
 
 方法刚被调用时：
 
 会从 class 中获取 load 方法： method = cls->getLoadMethod();
 判断当前 loadable_classes 这个数组是否已经被全部占用了：loadable_classes_used == loadable_classes_allocated
 在当前数组的基础上扩大数组的大小：realloc
 把传入的 class 以及对应的方法的实现加到列表中
 另外一个用于保存分类的列表 loadable_categories 也有一个类似的方法 add_category_to_loadable_list。
 
 实现几乎与 add_class_to_loadable_list 完全相同。
 
 到这里我们完成了对 loadable_classes 以及 loadable_categories 的提供，下面会开始消耗列表中的元素。
 
 “消费” loadable_class
 
 调用 load 方法的过程就是“消费” loadable_classes 的过程，load_images -> call_load_methods -> call_class_loads 会从 loadable_classes 中取出对应类和方法，执行 load。
 
 上述方法对所有在 loadable_classes 以及 loadable_categories 中的类以及分类执行 load 方法。
 
 调用顺序如下：
 
 不停调用类的 + load 方法，直到 loadable_classes 为空
 调用一次 call_category_loads 加载分类
 如果有 loadable_classes 或者更多的分类，继续调用 load 方法
 相比于类 load 方法的调用，分类中 load 方法的调用就有些复杂了：
 
 这个方法有些长，我们来分步解释方法的作用：
 
 获取当前可以加载的分类列表
 如果当前类是可加载的 cls  &&  cls->isLoadable() 就会调用分类的 load 方法
 将所有加载过的分类移除 loadable_categories 列表
 为 loadable_categories 重新分配内存，并重新设置它的值
 
 值得注意的是 (*load_method)(cls, SEL_load)，load方法是直接使用函数指针调用，也就是走C语言函数调用的流程，不是发送消息，并不会走消息转发的流程，也就是说，如果一个类实现了load函数就会调用，如果没有实现也不会调用该类的父类load函数实现，如果父类实现了load函数的话。category调用load方法也是一样的道理。
 */
+ (void)load;

/*
 Initializes the class before it receives its first message.
 
 The runtime sends initialize to each class in a program just before the class, or any class that inherits from it, is sent its first message from within the program. The runtime sends the initialize message to classes in a thread-safe manner. Superclasses receive this message before their subclasses. The superclass implementation may be called multiple times if subclasses do not implement initialize—the runtime will call the inherited implementation—or if subclasses explicitly call [super initialize]. If you want to protect yourself from being run multiple times, you can structure your implementation along these lines:
 由于initialize函数可能会被调用多次，所以，如果想保证initialize函数只被调用一次，苹果建议这样做
 + (void)initialize {
 if (self == [ClassName self]) {
 // ... do the initialization ...
     }
 }
 Because initialize is called in a thread-safe manner and the order of initialize being called on different classes is not guaranteed, it’s important to do the minimum amount of work necessary in initialize methods. Specifically, any code that takes locks that might be required by other classes in their initialize methods is liable to lead to deadlocks. Therefore you should not rely on initialize for complex initialization, and should instead limit it to straightforward, class local initialization.
 
 Special Considerations
 initialize is invoked only once per class. If you want to perform independent initialization for the class and for categories of the class, you should implement load methods.
 

 这个函数是懒加载，只有当类接收了第一个消息的时候才会调用initialize函数，否则一直不会调用.
 initialize函数的调用顺序为：superClass -> class。这里没有分类，因为一个类的initialize函数只会调用一次，如果需要实现独立的class和category的初始化就需要实现load函数。还需要注意的一点就是，如果subClass没有实现initialize函数，则父类的initialize函数会被调用两次
 initialize是线程安全的，有可能阻塞线程，所以，initialize函数应该限制做一些简单，不复杂的类初始化的前期准备工作
 callInitialize函数的工作相当简单，就是发送消息，这是和load函数实现不一样的地方，load函数的调用直接是函数指针的调用，而initialize函数是消息的转发。所以，class的子类就算没有实现initialize函数，也会调用父类的initialize函数，如果子类实现了initialize函数，则子类不会调用父类的initialize函数。
 
 总结
 
 通过分别对load和initialize源代码的实现细节，我们知道了它们各自的特点，总的如下：
 1.load在被添加到runtime的时候加载，initialize是类第一次收到消息的时候被加载，load是在main函数之前，initialize是在main函数之后。
 2.load方法的调用顺序是：superClass -> class -> category；initialize方法的调用顺序是：superClass -> class。都不需要显示调用父类的方法，系统会自动调用，load方法是函数指针调用，initialize是发送消息。子类如果没有实现load函数，子类是不会调用父类的load函数的，但是子类没有实现initialize函数，则会调用父类的initialize函数。
 3.load和initialize内部实现都加了线程锁，是线程安全的，因此，这两个函数应该做一些简单的工作，不适合复杂的工作。
 4.load函数通常用来进行Method Swizzle，initialize函数则通常初始化一些全局变量，静态变量。
 
 */
+ (void)initialize;
/*
 大部分情况下，我们都不希望所有成员变量都是零，所以 init 方法会做真正的初使化工作，让对象的成员变量的值符合我们程序逻辑中的初始化状态。例如，NSMutableString 可能就会额外再申请一块字符数组，用于动态修改字符串。
 init 还有一个需要注意的问题。某些情况下，init 会造成 alloc 的原本空间不够用，而第二次分配内存空间。所以下面的写法是错的：
     NSString * s = [NSString alloc];
     [s init]; // 这儿 init 返回的地址可能会变。s 原本的指针地址可能是无效的地址。
 为此，苹果引入了一个编程规范，让大家写的时候将 alloc 和 init 写在一行。所以上面的代码正确的写法是
     NSString * s = [[NSString alloc] init];

 */
- (instancetype)init
#if NS_ENFORCE_NSOBJECT_DESIGNATED_INITIALIZER
NS_DESIGNATED_INITIALIZER
#endif
;
//Allocates a new instance of the receiving class, sends it an init message, and returns the initialized object.
//This method is a combination of alloc and init. Like alloc, it initializes the isa instance variable of the new object so it points to the class data structure. It then invokes the init method to complete the initialization process.
//
/*
 在后来，苹果也引入了类方法：new。但是由于历史原因，init 方法是实例方法而非类方法，所以作为类方法的 new，只能简单地等价于 alloc + init，不能指定 init 的参数，所以用处不大。苹果在设计上也禁止多次调用 init 方法，例如如下代码会抛出 NSInvalidArgumentException。
     NSString * str = [NSString new];
     str = [str initWithString:@"Bar"];

 */
+ (instancetype)new OBJC_SWIFT_UNAVAILABLE("use object initializers instead");
//Returns a new instance of the receiving class.
//This method exists for historical reasons; memory zones are no longer used by Objective-C. You should not override this method.
/*
 自从 Mac OS X 10.5 上引入了垃圾回收机制后，苹果就不建议程序员使用 allocWithZone 了，事实上，cocoa 框架也会忽略 allocWithZone 指定的分区。苹果在文档中也 提到，allocWithZone 仅仅是一个历史遗留设计了。下图是苹果的文档截图：
 */
+ (instancetype)allocWithZone:(struct _NSZone *)zone OBJC_SWIFT_UNAVAILABLE("use object initializers instead");
/*
 Returns a new instance of the receiving class.
 
 The isa instance variable of the new instance is initialized to a data structure that describes the class; memory for all other instance variables is set to 0.
 
 You must use an init... method to complete the initialization process. For example:
 
 TheClass *newObject = [[TheClass alloc] init];
 Do not override alloc to include initialization code. Instead, implement class-specific versions of init... methods.
 
 For historical reasons, alloc invokes allocWithZone:.
 */
/*
 根据苹果的 官方文档。当对象创建时，cocoa 会从应用程序的虚拟地址空间上为该对象分配足够的内存。cocoa 会遍历该对象所有的成员变量，通过成员变量的类型来计算所需占用的内存。
 当我们通过 alloc 或 allocWithZone 方法创建对象时，cocoa 会返回一个未” 初使化 “过的对象。在这个过程中，cocoa 除了上面提到的申请了一块足够大的内存外，还做了以下 3 件事：
     将该新对象的引用计数 (Retain Count) 设置成 1。
     将该新对象的 isa 成员变量指向它的类对象。
     将该新对象的所有其它成员变量的值设置成零。（根据成员变量类型，零有可能是指 nil 或 Nil 或 0.0）
 isa 成员变量是在 NSObject 中定义的，所以保证 Cocoa 的所有对象都带有此成员变量。借助该变量可以实现 Cocoa 对象在运行时的自省 (Introspection) 功能。
 */
+ (instancetype)alloc OBJC_SWIFT_UNAVAILABLE("use object initializers instead");
//Deallocates the memory occupied by the receiver.
//This method first invokes didTurnIntoFault.
//You should typically not override this method—instead you should put “clean-up” code in prepareForDeletion or didTurnIntoFault.
//释放消息接收者占用的内存
- (void)dealloc OBJC_SWIFT_UNAVAILABLE("use 'deinit' to define a de-initializer");
/*
 The garbage collector invokes this method on the receiver before disposing of the memory it uses.
 
 Garbage collection is deprecated in OS X v10.8; instead, you should use Automatic Reference Counting—see Transitioning to ARC Release Notes.
 */
- (void)finalize OBJC_DEPRECATED("Objective-C garbage collection is no longer supported");
/*
 Returns the object returned by copyWithZone:.
 This is a convenience method for classes that adopt the NSCopying protocol. An exception is raised if there is no implementation for copyWithZone:.
 
 NSObject does not itself support the NSCopying protocol. Subclasses must support the protocol and implement the copyWithZone: method. A subclass version of the copyWithZone: method should send the message to super first, to incorporate its implementation, unless the subclass descends directly from NSObject.
 */
- (id)copy;
/*
 Returns the object returned by mutableCopyWithZone:.
 The object returned by the NSMutableCopying protocol method mutableCopyWithZone:.

 This is a convenience method for classes that adopt the NSMutableCopying protocol. An exception is raised if there is no implementation for mutableCopyWithZone:.
 */
- (id)mutableCopy;

+ (id)copyWithZone:(struct _NSZone *)zone OBJC_ARC_UNAVAILABLE;
+ (id)mutableCopyWithZone:(struct _NSZone *)zone OBJC_ARC_UNAVAILABLE;
//Returns a Boolean value that indicates whether instances of the receiver are capable of responding to a given selector.
+ (BOOL)instancesRespondToSelector:(SEL)aSelector;
//Returns a Boolean value that indicates whether the receiver conforms to a given protocol.
//
+ (BOOL)conformsToProtocol:(Protocol *)protocol;
//Locates and returns the address of the receiver’s implementation of a method so it can be called as a function.
//
- (IMP)methodForSelector:(SEL)aSelector;
//Locates and returns the address of the implementation of the instance method identified by a given selector.
//
+ (IMP)instanceMethodForSelector:(SEL)aSelector;
/*
 Handles messages the receiver doesn’t recognize.
 
 The runtime system invokes this method whenever an object receives an aSelector message it can’t respond to or forward. This method, in turn, raises an NSInvalidArgumentException, and generates an error message.
 
 Any doesNotRecognizeSelector: messages are generally sent only by the runtime system. However, they can be used in program code to prevent a method from being inherited. For example, an NSObject subclass might renounce the copy or init method by re-implementing it to include a doesNotRecognizeSelector: message as follows:
 
 - (id)copy
 {
     [self doesNotRecognizeSelector:_cmd];
 }
 The _cmd variable is a hidden argument passed to every method that is the current selector; in this example, it identifies the selector for the copy method. This code prevents instances of the subclass from responding to copy messages or superclasses from forwarding copy messages—although respondsToSelector: will still report that the receiver has access to a copy method.
 
 If you override this method, you must call super or raise an NSInvalidArgumentException exception at the end of your implementation. In other words, this method must not return normally; it must always result in an exception being thrown.
 */
- (void)doesNotRecognizeSelector:(SEL)aSelector;
/*
 Returns the object to which unrecognized messages should first be directed.
 
 If an object implements (or inherits) this method, and returns a non-nil (and non-self) result, that returned object is used as the new receiver object and the message dispatch resumes to that new object. (Obviously if you return self from this method, the code would just fall into an infinite loop.)
 
 If you implement this method in a non-root class, if your class has nothing to return for the given selector then you should return the result of invoking super’s implementation.
 
 This method gives an object a chance to redirect an unknown message sent to it before the much more expensive forwardInvocation: machinery takes over. This is useful when you simply want to redirect messages to another object and can be an order of magnitude faster than regular forwarding. It is not useful where the goal of the forwarding is to capture the NSInvocation, or manipulate the arguments or return value during the forwarding.
 */
- (id)forwardingTargetForSelector:(SEL)aSelector OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);
/*
 Overridden by subclasses to forward messages to other objects.
 
 When an object is sent a message for which it has no corresponding method, the runtime system gives the receiver an opportunity to delegate the message to another receiver. It delegates the message by creating an NSInvocation object representing the message and sending the receiver a forwardInvocation: message containing this NSInvocation object as the argument. The receiver’s forwardInvocation: method can then choose to forward the message to another object. (If that object can’t respond to the message either, it too will be given a chance to forward it.)
 
 The forwardInvocation: message thus allows an object to establish relationships with other objects that will, for certain messages, act on its behalf. The forwarding object is, in a sense, able to “inherit” some of the characteristics of the object it forwards the message to.
 
 IMPORTANT
 To respond to methods that your object does not itself recognize, you must override methodSignatureForSelector: in addition to forwardInvocation:. The mechanism for forwarding messages uses information obtained from methodSignatureForSelector: to create the NSInvocation object to be forwarded. Your overriding method must provide an appropriate method signature for the given selector, either by pre formulating one or by asking another object for one.
 
 An implementation of the forwardInvocation: method has two tasks:
 
 To locate an object that can respond to the message encoded in anInvocation. This object need not be the same for all messages.
 
 To send the message to that object using anInvocation. anInvocation will hold the result, and the runtime system will extract and deliver this result to the original sender.
 
 In the simple case, in which an object forwards messages to just one destination (such as the hypothetical friend instance variable in the example below), a forwardInvocation: method could be as simple as this:
 
 - (void)forwardInvocation:(NSInvocation *)invocation
 {
     SEL aSelector = [invocation selector];
     
     if ([friend respondsToSelector:aSelector])
     [invocation invokeWithTarget:friend];
     else
     [super forwardInvocation:invocation];
 }
 The message that’s forwarded must have a fixed number of arguments; variable numbers of arguments (in the style of printf()) are not supported.
 
 The return value of the forwarded message is returned to the original sender. All types of return values can be delivered to the sender: id types, structures, double-precision floating-point numbers.
 
 Implementations of the forwardInvocation: method can do more than just forward messages. forwardInvocation: can, for example, be used to consolidate code that responds to a variety of different messages, thus avoiding the necessity of having to write a separate method for each selector. A forwardInvocation: method might also involve several other objects in the response to a given message, rather than forward it to just one.
 
 NSObject’s implementation of forwardInvocation: simply invokes the doesNotRecognizeSelector: method; it doesn’t forward any messages. Thus, if you choose not to implement forwardInvocation:, sending unrecognized messages to objects will raise exceptions.
 */
- (void)forwardInvocation:(NSInvocation *)anInvocation OBJC_SWIFT_UNAVAILABLE("");
/*
 Returns an NSMethodSignature object that contains a description of the method identified by a given selector.
 This method is used in the implementation of protocols. This method is also used in situations where an NSInvocation object must be created, such as during message forwarding. If your object maintains a delegate or is capable of handling messages that it does not directly implement, you should override this method to return an appropriate method signature.
 */
- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector OBJC_SWIFT_UNAVAILABLE("");
/*
 Returns an NSMethodSignature object that contains a description of the instance method identified by a given selector.
 */
+ (NSMethodSignature *)instanceMethodSignatureForSelector:(SEL)aSelector OBJC_SWIFT_UNAVAILABLE("");

- (BOOL)allowsWeakReference UNAVAILABLE_ATTRIBUTE;
- (BOOL)retainWeakReference UNAVAILABLE_ATTRIBUTE;

+ (BOOL)isSubclassOfClass:(Class)aClass;

+ (BOOL)resolveClassMethod:(SEL)sel OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);
+ (BOOL)resolveInstanceMethod:(SEL)sel OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

+ (NSUInteger)hash;
+ (Class)superclass;
+ (Class)class OBJC_SWIFT_UNAVAILABLE("use 'aClass.self' instead");
+ (NSString *)description;
+ (NSString *)debugDescription;

@end

#endif

#endif
