/*	NSObject.h
	Copyright (c) 1994-2012, Apple Inc. All rights reserved.
 */

#ifndef _OBJC_NSOBJECT_H_
#define _OBJC_NSOBJECT_H_

#if __OBJC__

#include <objc/objc.h>
#include <objc/NSObjCRuntime.h>

@class NSString, NSMethodSignature, NSInvocation;

@protocol NSObject
//Returns a Boolean value that indicates whether the receiver and a given object are equal.
//This method defines what it means for instances to be equal. For example, a container object might define two containers as equal if their corresponding objects all respond YES to an isEqual: request. See the NSData, NSDictionary, NSArray, and NSString class specifications for examples of the use of this method.
//If two objects are equal, they must have the same hash value. This last point is particularly important if you define isEqual: in a subclass and intend to put instances of that subclass into a collection. Make sure you also define hash in your subclass.
//返回一个布尔值，指示接收方和给定对象是否相等。
//这个方法定义了实例相等的含义。 例如，容器对象可以将两个容器定义为相等，如果对应的对象都对isEqual：请求响应YES。 有关使用此方法的示例，请参阅NSData，NSDictionary，NSArray和NSString类规范。
//如果两个对象相等，则它们必须具有相同的哈希值。 如果在子类中定义isEqual：并将该子类的实例放入集合中，最后一点尤为重要。 确保您还在子类中定义哈希。
- (BOOL)isEqual:(id)object;
//Returns an integer that can be used as a table address in a hash table structure.
//If two objects are equal (as determined by the isEqual: method), they must have the same hash value. This last point is particularly important if you define hash in a subclass and intend to put instances of that subclass into a collection.
//If a mutable object is added to a collection that uses hash values to determine the object’s position in the collection, the value returned by the hash method of the object must not change while the object is in the collection. Therefore, either the hash method must not rely on any of the object’s internal state information or you must make sure the object’s internal state information does not change while the object is in the collection. Thus, for example, a mutable dictionary can be put in a hash table but you must not change it while it is in there. (Note that it can be difficult to know whether or not a given object is in a collection.)
//返回可用作哈希表结构中的表地址的整数。
//如果两个对象相等（由isEqual：方法确定），则它们必须具有相同的哈希值。 如果您在子类中定义散列并打算将该子类的实例放入集合中，则最后一点尤为重要。
//如果将可变对象添加到使用哈希值确定对象在集合中的位置的集合中，则对象在集合中的散列方法返回的值不能更改。 因此，散列方法不能依赖对象的任何内部状态信息，或者必须确保对象的内部状态信息在对象位于集合中时不会更改。 因此，例如，可以将一个可变字典放在一个哈希表中，但是当它在那里时不能更改它。 （注意，可能难以知道给定对象是否在集合中。）
@property (readonly) NSUInteger hash;
//Returns the class object for the receiver’s superclass.
//返回其父类
@property (readonly) Class superclass;
//Returns the class object for the receiver’s class.
//返回接收者的类
- (Class)class OBJC_SWIFT_UNAVAILABLE("use 'type(of: anObject)' instead");
//Returns the receiver.
//返回接收者
- (instancetype)self;
//Sends a specified message to the receiver and returns the result of the message.
//向接收方发送指定的消息，并返回消息的结果。
- (id)performSelector:(SEL)aSelector;
//Sends a message to the receiver with an object as the argument.
//以某个对象作为参数向接收方发送消息。
- (id)performSelector:(SEL)aSelector withObject:(id)object;
//Sends a message to the receiver with two objects as arguments.
//以两个对象作为参数向接收者发送消息。
- (id)performSelector:(SEL)aSelector withObject:(id)object1 withObject:(id)object2;
//Returns a Boolean value that indicates whether the receiver does not descend from NSObject
//返回一个布尔值，指示接收者是否不会从NSObject继承。
- (BOOL)isProxy;
//Returns a Boolean value that indicates whether the receiver is an instance of given class or an instance of any class that inherits from that class.
//YES if the receiver is an instance of aClass or an instance of any class that inherits from aClass, otherwise NO.
//返回一个布尔值，该值指示接收方是给定类的实例还是从该类继承的任何类的实例。
//如果接收者是aClass的实例或继承自aClass的任何类的实例，否则为否。
- (BOOL)isKindOfClass:(Class)aClass;
//Returns a Boolean value that indicates whether the receiver is an instance of a given class.
//YES if the receiver is an instance of aClass, otherwise NO.
//返回一个布尔值，指示接收者是否是给定类的实例。
//如果接收者是aClass的一个实例，否则为NO。
- (BOOL)isMemberOfClass:(Class)aClass;
//Returns a Boolean value that indicates whether the receiver conforms to a given protocol.
//This method works identically to the conformsToProtocol: class method declared in NSObject. It’s provided as a convenience so that you don’t need to get the class object to find out whether an instance can respond to a given set of messages.
//返回一个布尔值，指示接收器是否符合给定的协议。
//该方法与NSObject中声明的conformsToProtocol：class方法相同。 它是为了方便而提供的，因此您不需要获取类对象来确定实例是否可以响应给定的一组消息。
- (BOOL)conformsToProtocol:(Protocol *)aProtocol;
//Returns a Boolean value that indicates whether the receiver implements or inherits a method that can respond to a specified message.
//返回一个布尔值，指示接收者是否实现或继承可以响应指定消息的方法。
- (BOOL)respondsToSelector:(SEL)aSelector;
//Increments the receiver’s reference count.
//增加接收者的引用计数。
- (instancetype)retain OBJC_ARC_UNAVAILABLE;
//Decrements the receiver’s reference count.
//减少接收者的引用计数。
//oneway is used with the distributed objects API, which allows use of Objective-C objects between different threads or applications. It tells the system that it should not block the calling thread until the method returns. Without it, the caller will block, even though the method's return type is void. Obviously, it is never used with anything other than void, as doing so would mean the method returns something, but the caller doesn't get it.
//oneway分布式对象API一起使用，它允许在不同的线程或应用程序之间使用Objective-C对象。 它告诉系统它不应该阻止调用线程，直到方法返回。 没有它，调用者将阻止，即使方法的返回类型是无效的。 显然，它从来没有使用除void之外的任何东西，因为这样做意味着该方法返回一些东西，但是调用者没有得到它。
- (oneway void)release OBJC_ARC_UNAVAILABLE;
//Decrements the receiver’s retain count at the end of the current autorelease pool block.
//在当前自动释放池块的末尾减少接收者的保留计数。
- (instancetype)autorelease OBJC_ARC_UNAVAILABLE;
//The receiver’s reference count.
//接收者的保留计数
- (NSUInteger)retainCount OBJC_ARC_UNAVAILABLE;
//Zones are deprecated and ignored by most classes that have it as a parameter.
//大多数类作为一个参数都不再使用和忽略区域。
- (struct _NSZone *)zone OBJC_ARC_UNAVAILABLE;
//Returns a string that describes the contents of the receiver.
//返回描述接收器内容的字符串。
@property (readonly, copy) NSString *description;
@optional
//Returns a string that describes the contents of the receiver for presentation in the debugger.
//返回一个字符串，描述接收器的内容以在调试器中显示。
@property (readonly, copy) NSString *debugDescription;

@end


OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0)
OBJC_ROOT_CLASS
OBJC_EXPORT
@interface NSObject <NSObject> {
    Class isa  OBJC_ISA_AVAILABILITY;
}
//Invoked whenever a class or category is added to the Objective-C runtime; implement this method to perform class-specific behavior upon loading.
/*
 The load message is sent to classes and categories that are both dynamically loaded and statically linked, but only if the newly loaded class or category implements a method that can respond.
 
 The order of initialization is as follows:
     1.All initializers in any framework you link to.
     2.All +load methods in your image.
     3.All C++ static initializers and C/C++ __attribute__(constructor) functions in your image.
     4.All initializers in frameworks that link to you.
 In addition:
     i.A class’s +load method is called after all of its superclasses’ +load methods.
     ii.A category +load method is called after the class’s own +load method.
 
 In a custom implementation of load you can therefore safely message other unrelated classes from the same image, but any load methods implemented by those classes may not have run yet.
 */
//每当将类或类添加到Objective-C运行时时调用;实现此方法在加载时执行类特定的行为。
/*
 加载消息被发送到动态加载和静态链接的类和类别，但只有当新加载的类或类实现可以响应的方法时。
 
 初始化顺序如下：
     1.任何框架中的所有初始化程序，您链接到。
     2.图像中的所有+加载方法。
     3.您的图像中的所有C ++静态初始化程序和C / C ++ __attribute __（构造函数）函数。
     4.在链接到您的框架中的所有初始化程序。
 此外：
     i.A类的+加载方法在其所有超类+加载方法之后被调用。
     ii.类+加载方法在类自己的+加载方法之后调用。
 
 在自定义的加载实现中，您可以安全地从同一个映像中消息其他不相关的类，但是这些类实现的任何加载方法可能尚未运行。
 */
+ (void)load;
/*
 Initializes the class before it receives its first message.
 The runtime sends initialize to each class in a program just before the class, or any class that inherits from it, is sent its first message from within the program. The runtime sends the initialize message to classes in a thread-safe manner. Superclasses receive this message before their subclasses. The superclass implementation may be called multiple times if subclasses do not implement initialize—the runtime will call the inherited implementation—or if subclasses explicitly call [super initialize]. If you want to protect yourself from being run multiple times, you can structure your implementation along these lines:
 
 + (void)initialize {
     if (self == [ClassName self]) {
         // ... do the initialization ...
     }
 }
 Because initialize is called in a thread-safe manner and the order of initialize being called on different classes is not guaranteed, it’s important to do the minimum amount of work necessary in initialize methods. Specifically, any code that takes locks that might be required by other classes in their initialize methods is liable to lead to deadlocks. Therefore you should not rely on initialize for complex initialization, and should instead limit it to straightforward, class local initialization.
 
 Special Considerations
 initialize is invoked only once per class. If you want to perform independent initialization for the class and for categories of the class, you should implement load methods.
 */
/*
 在收到第一条消息之前初始化该类。
  运行时在程序之前的程序中向程序集中的每个类发送初始化，或从其继承的任何类从程序中发送其第一个消息。运行时以线程安全的方式将初始化消息发送给类。超类在他们的子类之前收到这个消息。如果子类不实现初始化，则可以多次调用父类实现 - 运行时将调用继承的实现 - 或者如果子类明确调用[super initialize]。如果要保护自己不要多次运行，可以按照以下方式构建您的实现：
  
  +（void）initialize {
      if（self == [ClassName self]）{
          // ...做初始化...
      }
  }
  因为初始化以线程安全的方式调用，并且不保证在不同类上调用初始化顺序，所以在初始化方法中进行最少量的工作很重要。具体来说，在初始化方法中使用其他类可能需要的锁的任何代码都可能导致死锁。因此，您不应该依赖初始化复杂的初始化，而应该将其限制为简单的类本地初始化。
  
  特别注意事项
  初始化每个类只调用一次。如果要对类和类的类执行独立初始化，则应实现加载方法。
 */
+ (void)initialize;
/*
 Designated Initializer,Implemented by subclasses to initialize a new object (the receiver) immediately after memory for it has been allocated.
 An init message is coupled with an alloc (or allocWithZone:) message in the same line of code:
 
 TheClass *newObject = [[TheClass alloc] init];
 An object isn’t ready to be used until it has been initialized. The init method defined in the NSObject class does no initialization; it simply returns self.
 
 In a custom implementation of this method, you must invoke super’s designated initializer then initialize and return the new object. If the new object can’t be initialized, the method should return nil. For example, a hypothetical BuiltInCamera class might return nil from its init method if run on a device that has no camera.
 
 - (id)init {
     self = [super init];
     if (self) {
         // Initialize self.
     }
     return self;
 }
 In some cases, an init method might return a substitute object. You must therefore always use the object returned by init, and not the one returned by alloc or allocWithZone:, in subsequent code.
 */
/*
 指定的初始化器，由子类实现，用于在内存被分配之后立即初始化新对象（接收器）。
  init消息与同一行代码中的alloc（或allocWithZone :)消息相结合：
  
  TheClass * newObject = [[TheClass alloc] init];
  一个对象在初始化之前还没有准备好使用。 NSObject类中定义的init方法不会初始化;它只是返回自我。
  
  在这种方法的自定义实现中，您必须调用super的指定的初始化程序，然后初始化并返回新对象。如果新对象无法初始化，则该方法应返回nil。例如，假设的BuiltInCamera类如果在没有相机的设备上运行，则可能会从其init方法返回nil。
  
 - (id)init {
     self = [super init];
     if (self) {
         // Initialize self.
     }
     return self;
 }
  在某些情况下，init方法可能会返回一个替换对象。因此，必须始终使用init返回的对象，而不是在后续代码中由alloc或allocWithZone：返回的对象。
 */
- (instancetype)init
#if NS_ENFORCE_NSOBJECT_DESIGNATED_INITIALIZER
NS_DESIGNATED_INITIALIZER
#endif
;
/*
 Allocates a new instance of the receiving class, sends it an init message, and returns the initialized object.
 This method is a combination of alloc and init. Like alloc, it initializes the isa instance variable of the new object so it points to the class data structure. It then invokes the init method to complete the initialization process.
 */
/*
   分配接收类的新实例，发送一个初始化消息，并返回已初始化的对象。
   这种方法是alloc和init的组合。 像alloc一样，它初始化新对象的isa实例变量，以便它指向类数据结构。 然后调用init方法来完成初始化过程。
  */
+ (instancetype)new OBJC_SWIFT_UNAVAILABLE("use object initializers instead");
//Returns a new instance of the receiving class.This method exists for historical reasons; memory zones are no longer used by Objective-C. You should not override this method.
//返回接收类的新实例。该方法由于历史原因而存在; 内存区不再被Objective-C使用。 您不应该覆盖此方法。
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
 返回接收类的新实例。
   新实例的isa实例变量被初始化为描述类的数据结构; 所有其他实例变量的内存设置为0。
  
   您必须使用init ...方法来完成初始化过程。 例如：
  
       TheClass * newObject = [[TheClass alloc] init];
   不要重写alloc来包含初始化代码。 而是实现init ...方法的特定于类的版本。
  
   由于历史原因，alloc调用allocWithZone：。
 */
+ (instancetype)alloc OBJC_SWIFT_UNAVAILABLE("use object initializers instead");
- (void)dealloc OBJC_SWIFT_UNAVAILABLE("use 'deinit' to define a de-initializer");
/*
 The garbage collector invokes this method on the receiver before disposing of the memory it uses.
 
 Garbage collection is deprecated in OS X v10.8; instead, you should use Automatic Reference Counting—see Transitioning to ARC Release Notes.
 
 The garbage collector invokes this method on the receiver before disposing of the memory it uses. When garbage collection is enabled, this method is invoked instead of dealloc.
 
 You can override this method to relinquish resources the receiver has obtained, as shown in the following example:
 
 - (void)finalize {
     if (log_file != NULL) {
         fclose(log_file);
         log_file = NULL;
     }
     [super finalize];
 }
 Typically, however, you are encouraged to relinquish resources prior to finalization if at all possible. For more details, see Implementing a finalize Method.
 
 Special Considerations
 It is an error to store self into a new or existing live object (colloquially known as “resurrection”), which implies that this method will be called only once. However, the receiver may be messaged after finalization by other objects also being finalized at this time, so your override should guard against future use of resources that have been reclaimed, as shown by the log_file = NULL statement in the example. The finalize method itself will never be invoked more than once for a given object.
 
 IMPORTANT
 finalize methods must be thread-safe.
 */
/*
 垃圾收集器在处理使用的内存之前在接收器上调用此方法。
 
 垃圾收集已在OS X v10.8中弃用;相反，您应该使用自动参考计数 - 请参阅转换到ARC发行说明。
 
 垃圾收集器在处理使用的内存之前在接收器上调用此方法。当启用垃圾收集时，将调用此方法而不是dealloc。
 
 您可以覆盖此方法以放弃接收方获得的资源，如以下示例所示：
 
 - (void)finalize {
     if (log_file != NULL) {
         fclose(log_file);
         log_file = NULL;
     }
     [super finalize];
 }
 但是，通常情况下，如果可能，您将被鼓励在最终确定之前放弃资源。有关详细信息，请参阅实现finalize方法。
 
 特别注意事项
 将自己存入新的或现有的活体（俗称“复活”）是一个错误，这意味着这种方法只会被调用一次。然而，接收方在最终确定后也可能会在此时被其他对象确定，因此您的覆盖应该防止将来使用已被回收的资源，如示例中的log_file = NULL语句所示。对于给定的对象，finalize方法本身不会被多次调用。
 
 重要
 finalize方法必须是线程安全的。
 */
- (void)finalize OBJC_DEPRECATED("Objective-C garbage collection is no longer supported");
/*
 Returns the object returned by copyWithZone:.
 This is a convenience method for classes that adopt the NSCopying protocol. An exception is raised if there is no implementation for copyWithZone:.
 
 NSObject does not itself support the NSCopying protocol. Subclasses must support the protocol and implement the copyWithZone: method. A subclass version of the copyWithZone: method should send the message to super first, to incorporate its implementation, unless the subclass descends directly from NSObject.
 */
/*
   返回由copyWithZone返回的对象。
   这是采用NSCopying协议的类的方便方法。 如果没有执行copyWithZone：，则会引发异常。
  
   NSObject本身不支持NSCopying协议。 子类必须支持协议并实现copyWithZone：方法。 copyWithZone：方法的子类版本首先应该将消息发送到父类，以包含其实现，除非子类直接从NSObject下降。
  */
- (id)copy;
/*
 Returns the object returned by mutableCopyWithZone:.
 This is a convenience method for classes that adopt the NSMutableCopying protocol. An exception is raised if there is no implementation for mutableCopyWithZone:.
 */
/*
 返回mutableCopyWithZone返回的对象：。
   这是采用NSMutableCopying协议的类的方便方法。 如果mutableCopyWithZone没有实现，则会引发异常。
 */
- (id)mutableCopy;
/*
 Returns the receiver.
 This method exists so class objects can be used in situations where you need an object that conforms to the NSCopying protocol. For example, this method lets you use a class object as a key to an NSDictionary object. You should not override this method.
 */
/*
   返回接收器。
   存在这种方法，所以在需要符合NSCopying协议的对象的情况下，可以使用类对象。 例如，该方法允许您使用类对象作为NSDictionary对象的键。 您不应该覆盖此方法。
*/
+ (id)copyWithZone:(struct _NSZone *)zone OBJC_ARC_UNAVAILABLE;
/*
 Returns the receiver.
 This method exists so class objects can be used in situations where you need an object that conforms to the NSMutableCopying protocol. For example, this method lets you use a class object as a key to an NSDictionary object. You should not override this method.
 */
/*
   返回接收器。
   存在这种方法，所以在需要符合NSMutableCopying协议的对象的情况下，可以使用类对象。 例如，该方法允许您使用类对象作为NSDictionary对象的键。 您不应该覆盖此方法。
 */
+ (id)mutableCopyWithZone:(struct _NSZone *)zone OBJC_ARC_UNAVAILABLE;
/*
 Returns a Boolean value that indicates whether instances of the receiver are capable of responding to a given selector.
 If aSelector messages are forwarded to other objects, instances of the class are able to receive those messages without error even though this method returns NO.
 
 To ask the class whether it, rather than its instances, can respond to a particular message, send to the class instead the NSObject protocol instance method respondsToSelector:.
 */
/*
   返回一个布尔值，指示接收器的实例是否能够响应给定的选择器。
   如果aSelector消息转发到其他对象，则该类的实例能够无错误地接收这些消息，即使该方法返回NO。
  
   要求类是否，而不是它的实例可以响应一个特定的消息，发送到类，而不是NSObject协议实例方法respondToSelector：。
*/
+ (BOOL)instancesRespondToSelector:(SEL)aSelector;
/*
 Returns a Boolean value that indicates whether the receiver conforms to a given protocol.
 
 A class is said to “conform to” a protocol if it adopts the protocol or inherits from another class that adopts it. Protocols are adopted by listing them within angle brackets after the interface declaration. For example, here MyClass adopts the (fictitious) AffiliationRequests and Normalization protocols:
 
     @interface MyClass : NSObject <AffiliationRequests, Normalization>
 A class also conforms to any protocols that are incorporated in the protocols it adopts or inherits. Protocols incorporate other protocols in the same way classes adopt them. For example, here the AffiliationRequests protocol incorporates the Joining protocol:
 
     @protocol AffiliationRequests <Joining>
 If a class adopts a protocol that incorporates another protocol, it must also implement all the methods in the incorporated protocol or inherit those methods from a class that adopts it.
 
 This method determines conformance solely on the basis of the formal declarations in header files, as illustrated above. It doesn’t check to see whether the methods declared in the protocol are actually implemented—that’s the programmer’s responsibility.
 
 The protocol required as this method’s argument can be specified using the @protocol() directive:
 
     BOOL canJoin = [MyClass conformsToProtocol:@protocol(Joining)];
 */
/*
 返回一个布尔值，指示接收机是否符合给定的协议。
 
 一个类被称为“符合”一个协议，如果它采用协议或继承自另一个采用它的类。通过在接口声明之后将它们列在尖括号中来采用协议。例如，这里MyClass采用（虚构的）AffiliationRequests和规范化协议：
 
     @interface MyClass：NSObject <AffiliationRequests，Normalization>
 类也符合所采用或继承的协议中所包含的任何协议。协议以与采用它们相同的方式并入其他协议。例如，这里的AffiliationRequests协议包含加入协议：
 
     @Protocol AffiliationRequests <Join>
 如果一个类采用包含另一个协议的协议，那么它也必须实现所合并的协议中的所有方法，或者从采用它的类继承这些方法。
 
 该方法仅仅根据头文件中的形式声明确定一致性，如上所示。它不检查协议中声明的方法是否实际实现 - 程序员的责任。
 
 可以使用@protocol（）伪指令来指定此方法参数所需的协议：
 
     BOOL canJoin = [MyClass conformsToProtocol：@protocol（Join）];
 */
+ (BOOL)conformsToProtocol:(Protocol *)protocol;
/*
 Locates and returns the address of the receiver’s implementation of a method so it can be called as a function.
 If the receiver is an instance, aSelector should refer to an instance method; if the receiver is a class, it should refer to a class method.
 */
/*
   查找并返回接收方实现方法的地址，以便可以将其称为函数。
   如果接收者是一个实例，aSelector应该引用一个实例方法; 如果接收者是一个类，它应该引用一个类的方法。
 */
- (IMP)methodForSelector:(SEL)aSelector;
/*
 Locates and returns the address of the implementation of the instance method identified by a given selector.
 An error is generated if instances of the receiver can’t respond to aSelector messages.
 
 Use this method to ask the class object for the implementation of instance methods only. To ask the class for the implementation of a class method, send the methodForSelector: instance method to the class instead.
 */
/*
   找到并返回由给定选择器标识的实例方法的实现地址。
   如果接收方的实例无法响应选择器消息，则会生成错误。
  
   使用这个方法只要求类对象来实现实例方法。 要求类实现一个类方法，请将methodForSelector：instance方法发送给该类。
  */
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
/*
 处理收件人无法识别的邮件。
 每当对象收到一个无法响应或转发的aSelector消息时，运行时系统将调用此方法。反过来，此方法会引发NSInvalidArgumentException异常，并生成错误消息。
 
 任何不可忽略的选择器：消息通常仅由运行时系统发送。但是，它们可以在程序代码中使用，以防止继承方法。例如，NSObject子类可以通过重新实现它来包含一个doNotRecognizeSelector：消息来放弃copy或init方法，如下所示：
 
  - （id）副本
 {
     [self doesNotRecognizeSelector：_cmd];
 }
 _cmd变量是传递给当前选择器的每个方法的隐藏参数;在此示例中，它标识复制方法的选择器。此代码防止子类的实例响应复制消息或超类转发复制消息 - 尽管respondToSelector：仍将报告接收方可以访问复制方法。
 
 如果您重写此方法，则必须在执行结束时调用super或引发NSInvalidArgumentException异常。换句话说，这种方法不能正常返回;它必须总是导致抛出异常。
 */
- (void)doesNotRecognizeSelector:(SEL)aSelector;
/*
 Returns the object to which unrecognized messages should first be directed.
 
 If an object implements (or inherits) this method, and returns a non-nil (and non-self) result, that returned object is used as the new receiver object and the message dispatch resumes to that new object. (Obviously if you return self from this method, the code would just fall into an infinite loop.)
 
 If you implement this method in a non-root class, if your class has nothing to return for the given selector then you should return the result of invoking super’s implementation.
 
 This method gives an object a chance to redirect an unknown message sent to it before the much more expensive forwardInvocation: machinery takes over. This is useful when you simply want to redirect messages to another object and can be an order of magnitude faster than regular forwarding. It is not useful where the goal of the forwarding is to capture the NSInvocation, or manipulate the arguments or return value during the forwarding.
 */
/*
 返回无法识别的消息应首先被引导到的对象。
 
 如果对象实现（或继承）此方法，并返回非零（和非自身）结果，则返回的对象将用作新的接收方对象，并且消息分派将恢复到该新对象。 （显然，如果你从这个方法返回自己，代码将会陷入一个无限循环。）
 
 如果您在非根类中实现此方法，如果您的类对于给定的选择器没有任何返回值，那么您应该返回调用super的实现的结果。
 
 这种方法使对象有机会重定向发送给它的未知消息，然后更昂贵的forwardInvocation：机械接管。当您只想将消息重定向到另一个对象时，这比常规转发速度快一个数量级。在转发的目标是捕获NSInvocation或在转发期间操纵参数或返回值，这是不实用的。
 */
- (id)forwardingTargetForSelector:(SEL)aSelector OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);
/*
 Overridden by subclasses to forward messages to other objects.
 
 When an object is sent a message for which it has no corresponding method, the runtime system gives the receiver an opportunity to delegate the message to another receiver. It delegates the message by creating an NSInvocation object representing the message and sending the receiver a forwardInvocation: message containing this NSInvocation object as the argument. The receiver’s forwardInvocation: method can then choose to forward the message to another object. (If that object can’t respond to the message either, it too will be given a chance to forward it.)
 
 The forwardInvocation: message thus allows an object to establish relationships with other objects that will, for certain messages, act on its behalf. The forwarding object is, in a sense, able to “inherit” some of the characteristics of the object it forwards the message to.
 
     IMPORTANT
     To respond to methods that your object does not itself recognize, you must override methodSignatureForSelector: in addition to forwardInvocation:. The mechanism for forwarding messages uses information obtained from methodSignatureForSelector: to create the NSInvocation object to be forwarded. Your overriding method must provide an appropriate method signature for the given selector, either by pre formulating one or by asking another object for one.
 
 An implementation of the forwardInvocation: method has two tasks:
 
    * To locate an object that can respond to the message encoded in anInvocation. This object need not be the same for all messages.
 
    * To send the message to that object using anInvocation. anInvocation will hold the result, and the runtime system will extract and deliver this result to the original sender.
 
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
/*
 由子类覆盖，将消息转发到其他对象。
 
 当对象被发送一个没有相应方法的消息时，运行时系统给予接收者一个机会，将消息委托给另一个接收方。它通过创建表示消息的NSInvocation对象来发送消息，并将接收者发送包含此NSInvocation对象的forwardInvocation：消息作为参数。接收方的forwardInvocation：方法可以选择将消息转发到另一个对象。 （如果该对象不能响应该消息，也将有机会转发它。）
 
 forwardInvocation：消息因此允许对象与其他对象建立关系，对于某些消息，该对象将代表其行为。在某种意义上，转发对象能够“继承”转发消息的对象的一些特征。
 
     重要
     要响应对象本身不识别的方法，除了forwardInvocation：之外，还必须覆盖methodSignatureForSelector：。转发消息的机制使用从methodSignatureForSelector获取的信息：创建要转发的NSInvocation对象。您的首选方法必须为给定的选择器提供适当的方法签名，方法是通过预先制定一个或通过向另一个对象询问另一个对象。
 
 forwardInvocation：方法的实现有两个任务：
 
    *定位可以响应anInvocation中编码的消息的对象。所有消息的对象不一定相同。
 
    *使用anvocation将消息发送到该对象。 anInvocation将保存结果，并且运行时系统将提取并将此结果传递给原始发件人。
 
 在简单的情况下，一个对象将消息转发到一个目的地（例如下面的示例中的假设朋友实例变量），forwardInvocation：方法可能很简单：
 
     - (void)forwardInvocation:(NSInvocation *)invocation
     {
     SEL aSelector = [invocation selector];
     
     if ([friend respondsToSelector:aSelector])
         [invocation invokeWithTarget:friend];
     else
         [super forwardInvocation:invocation];
     }
 转发的消息必须有固定数量的参数;不支持可变数量的参数（在printf（）的样式）。
 
 转发邮件的返回值返回给原始发件人。所有类型的返回值都可以传递给发件人：id类型，结构，双精度浮点数。
 
 forwardInvocation：方法的实现不仅可以转发消息。 forwardInvocation：例如，可以用于合并响应各种不同消息的代码，从而避免必须为每个选择器编写单独的方法。 forwardInvocation：方法也可能涉及到给定消息的响应中的其他几个对象，而不是将其转发到一个。
 
 NSObject的forwardInvocation的实现：只需调用doesNotRecognizeSelector：方法;它不转发任何消息。因此，如果您选择不实现forwardInvocation：，将无法识别的消息发送到对象将引发异常。
 */
- (void)forwardInvocation:(NSInvocation *)anInvocation OBJC_SWIFT_UNAVAILABLE("");
/*
 Returns an NSMethodSignature object that contains a description of the method identified by a given selector.
 
 This method is used in the implementation of protocols. This method is also used in situations where an NSInvocation object must be created, such as during message forwarding. If your object maintains a delegate or is capable of handling messages that it does not directly implement, you should override this method to return an appropriate method signature.
 */
/*
   返回一个NSMethodSignature对象，该对象包含给定选择器标识的方法的描述。
  
   该方法用于协议的实现。 此方法也用于必须创建NSInvocation对象的情况，例如在消息转发期间。 如果您的对象维护委托或能够处理不直接实现的消息，则应该覆盖此方法以返回适当的方法签名。
  */
- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector OBJC_SWIFT_UNAVAILABLE("");
/*
 Returns an NSMethodSignature object that contains a description of the instance method identified by a given selector.
 */
/*
   返回一个NSMethodSignature对象，其中包含由给定选择器标识的实例方法的描述。
  */
+ (NSMethodSignature *)instanceMethodSignatureForSelector:(SEL)aSelector OBJC_SWIFT_UNAVAILABLE("");

- (BOOL)allowsWeakReference UNAVAILABLE_ATTRIBUTE;
- (BOOL)retainWeakReference UNAVAILABLE_ATTRIBUTE;

//Returns a Boolean value that indicates whether the receiving class is a subclass of, or identical to, a given class.
//返回一个布尔值，指示接收类是否为给定类的子类，或者等同于给定类。
+ (BOOL)isSubclassOfClass:(Class)aClass;
//Dynamically provides an implementation for a given selector for a class method.
//This method allows you to dynamically provide an implementation for a given selector. See resolveInstanceMethod: for further discussion.
//为类方法动态地为给定的选择器提供一个实现。
//此方法允许您动态提供给定选择器的实现。 请参见resolveInstanceMethod：进一步讨论。
+ (BOOL)resolveClassMethod:(SEL)sel OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);
/*
 Dynamically provides an implementation for a given selector for an instance method.
 
 This method and resolveClassMethod: allow you to dynamically provide an implementation for a given selector.
 
 An Objective-C method is simply a C function that take at least two arguments—self and _cmd. Using the class_addMethod function, you can add a function to a class as a method. Given the following function:
 
     void dynamicMethodIMP(id self, SEL _cmd)
     {
         // implementation ....
     }
 you can use resolveInstanceMethod: to dynamically add it to a class as a method (called resolveThisMethodDynamically) like this:
 
     + (BOOL) resolveInstanceMethod:(SEL)aSEL
     {
         if (aSEL == @selector(resolveThisMethodDynamically))
         {
             class_addMethod([self class], aSEL, (IMP) dynamicMethodIMP, "v@:");
             return YES;
         }
         return [super resolveInstanceMethod:aSel];
     }
 Special Considerations
 This method is called before the Objective-C forwarding mechanism is invoked. If respondsToSelector: or instancesRespondToSelector: is invoked, the dynamic method resolver is given the opportunity to provide an IMP for the given selector first.
 */
/*
 动态地为实例方法提供给定选择器的实现。
 
 此方法和resolveClassMethod：允许您为给定的选择器动态提供一个实现。
 
 Objective-C方法只是一个C函数，它至少需要两个参数self和_cmd。使用class_addMethod函数，您可以将一个函数添加到类作为方法。给出以下功能：
 
     void dynamicMethodIMP(id self, SEL _cmd)
     {
         // implementation ....
     }
 您可以使用resolveInstanceMethod：将其动态添加到类作为方法（称为resolveThisMethodDynamically），如下所示：
 
     + (BOOL) resolveInstanceMethod:(SEL)aSEL
     {
         if (aSEL == @selector(resolveThisMethodDynamically))
         {
             class_addMethod([self class], aSEL, (IMP) dynamicMethodIMP, "v@:");
             return YES;
         }
         return [super resolveInstanceMethod:aSel];
     }

 特别注意事项
 在调用Objective-C转发机制之前调用此方法。如果调用respondToSelector：或instancesRespondToSelector：，动态方法解析器就有机会首先为给定的选择器提供IMP。
 */
+ (BOOL)resolveInstanceMethod:(SEL)sel OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

+ (NSUInteger)hash;
+ (Class)superclass;
+ (Class)class OBJC_SWIFT_UNAVAILABLE("use 'aClass.self' instead");
+ (NSString *)description;
+ (NSString *)debugDescription;

@end

#endif

#endif
