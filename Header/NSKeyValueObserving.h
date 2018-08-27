/*
	NSKeyValueObserving.h
	Copyright (c) 2003-2016, Apple Inc.
	All rights reserved.
 */

#import <Foundation/NSArray.h>
#import <Foundation/NSOrderedSet.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSDictionary.h>

@class NSIndexSet, NSString;

NS_ASSUME_NONNULL_BEGIN
//参考自:http://www.jianshu.com/p/d104daf7a062

/* Options for use with -addObserver:forKeyPath:options:context: and -addObserver:toObjectsAtIndexes:forKeyPath:options:context:.
 */
typedef NS_OPTIONS(NSUInteger, NSKeyValueObservingOptions) {
    
    /* Whether the change dictionaries sent in notifications should contain NSKeyValueChangeNewKey and NSKeyValueChangeOldKey entries, respectively.
     */
    //Indicates that the change dictionary should provide the new attribute value, if applicable.
    //当options中包括了这个参数的时候，观察者收到的change参数中就会包含NSKeyValueChangeNewKey和它对应的值，也就是说，观察者可以得知这个property在被改变之后的新值
    NSKeyValueObservingOptionNew = 0x01,
    //Indicates that the change dictionary should contain the old attribute value, if applicable.
    //和NSKeyValueObservingOptionNew的意思类似，当包含了这个参数的时候，观察者收到的change参数中就会包含NSKeyValueChangeOldKey和它对应的值
    NSKeyValueObservingOptionOld = 0x02,
    
    /* Whether a notification should be sent to the observer immediately, before the observer registration method even returns. The change dictionary in the notification will always contain an NSKeyValueChangeNewKey entry if NSKeyValueObservingOptionNew is also specified but will never contain an NSKeyValueChangeOldKey entry. (In an initial notification the current value of the observed property may be old, but it's new to the observer.) You can use this option instead of explicitly invoking, at the same time, code that is also invoked by the observer's -observeValueForKeyPath:ofObject:change:context: method. When this option is used with -addObserver:toObjectsAtIndexes:forKeyPath:options:context: a notification will be sent for each indexed object to which the observer is being added.
     */
    //If specified, a notification should be sent to the observer immediately, before the observer registration method even returns.
    //当包含这个参数的时候，在addObserver的这个过程中，就会有一个notification被发送到观察者那里，反之则没有
    NSKeyValueObservingOptionInitial NS_ENUM_AVAILABLE(10_5, 2_0) = 0x04,
    
    /* Whether separate notifications should be sent to the observer before and after each change, instead of a single notification after the change. The change dictionary in a notification sent before a change always contains an NSKeyValueChangeNotificationIsPriorKey entry whose value is [NSNumber numberWithBool:YES], but never contains an NSKeyValueChangeNewKey entry. You can use this option when the observer's own KVO-compliance requires it to invoke one of the -willChange... methods for one of its own properties, and the value of that property depends on the value of the observed object's property. (In that situation it's too late to easily invoke -willChange... properly in response to receiving an -observeValueForKeyPath:ofObject:change:context: message after the change.)
     
     When this option is specified, the change dictionary in a notification sent after a change contains the same entries that it would contain if this option were not specified, except for ordered unique to-many relationships represented by NSOrderedSets.  For those, for NSKeyValueChangeInsertion and NSKeyValueChangeReplacement changes, the change dictionary for a will-change notification contains an NSKeyValueChangeIndexesKey (and NSKeyValueChangeOldKey in the case of Replacement where the NSKeyValueObservingOptionOld option was specified at registration time) which give the indexes (and objects) which *may* be changed by the operation.  The second notification, after the change, contains entries reporting what did actually change.  For NSKeyValueChangeRemoval changes, removals by index are precise.
     */
    //Whether separate notifications should be sent to the observer before and after each change, instead of a single notification after the change.
    //当包含这个参数的时候，在被观察的property的值改变前和改变后，系统各会给观察者发送一个change notification；在property的值改变之前发送的change notification中，change参数会包含NSKeyValueChangeNotificationIsPriorKey并且值为@YES，但不会包含NSKeyValueChangeNewKey和它对应的值
    NSKeyValueObservingOptionPrior NS_ENUM_AVAILABLE(10_5, 2_0) = 0x08
    
};

/* Possible values in the NSKeyValueChangeKindKey entry in change dictionaries. See the comments for -observeValueForKeyPath:ofObject:change:context: for more information.
 */
typedef NS_ENUM(NSUInteger, NSKeyValueChange) {
    NSKeyValueChangeSetting = 1,
    NSKeyValueChangeInsertion = 2,
    NSKeyValueChangeRemoval = 3,
    NSKeyValueChangeReplacement = 4,
};

/* Possible kinds of set mutation for use with -willChangeValueForKey:withSetMutation:usingObjects: and -didChangeValueForKey:withSetMutation:usingObjects:. Their semantics correspond exactly to NSMutableSet's -unionSet:, -minusSet:, -intersectSet:, and -setSet: method, respectively.
 */
typedef NS_ENUM(NSUInteger, NSKeyValueSetMutationKind) {
    NSKeyValueUnionSetMutation = 1,
    NSKeyValueMinusSetMutation = 2,
    NSKeyValueIntersectSetMutation = 3,
    NSKeyValueSetSetMutation = 4
};

typedef NSString * NSKeyValueChangeKey NS_STRING_ENUM;
/* Keys for entries in change dictionaries. See the comments for -observeValueForKeyPath:ofObject:change:context: for more information.
 */
//这是change中永远会包含的键值对，它的值是一个NSNumber对象，具体的数值有NSKeyValueChangeSetting、NSKeyValueChangeInsertion、NSKeyValueChangeRemoval、NSKeyValueChangeReplacement这几个，其中后三个是针对于to-many relationship的
FOUNDATION_EXPORT NSKeyValueChangeKey const NSKeyValueChangeKindKey;
//只有当addObserver的时候在optional参数中加入NSKeyValueObservingOptionNew，这个键值对才会被change参数包含；它表示这个property改变后的新值
FOUNDATION_EXPORT NSKeyValueChangeKey const NSKeyValueChangeNewKey;
//只有当addObserver的时候在optional参数中加入NSKeyValueObservingOptionOld，这个键值对才会被change参数包含；它表示这个property改变前的值
FOUNDATION_EXPORT NSKeyValueChangeKey const NSKeyValueChangeOldKey;
//被观察的property是一个ordered to-many relationship时，这个键值对才会被change参数包含；它的值是一个NSIndexSet对象。
FOUNDATION_EXPORT NSKeyValueChangeKey const NSKeyValueChangeIndexesKey;
//只有当addObserver的时候在optional参数中加入NSKeyValueObservingOptionPrior，这个键值对才会被change参数包含；它的值是@YES
FOUNDATION_EXPORT NSKeyValueChangeKey const NSKeyValueChangeNotificationIsPriorKey NS_AVAILABLE(10_5, 2_0);

@interface NSObject(NSKeyValueObserving)

/* Given that the receiver has been registered as an observer of the value at a key path relative to an object, be notified of a change to that value.
 
 The change dictionary always contains an NSKeyValueChangeKindKey entry whose value is an NSNumber wrapping an NSKeyValueChange (use -[NSNumber unsignedIntegerValue]). The meaning of NSKeyValueChange depends on what sort of property is identified by the key path:
 - For any sort of property (attribute, to-one relationship, or ordered or unordered to-many relationship) NSKeyValueChangeSetting indicates that the observed object has received a -setValue:forKey: message, or that the key-value coding-compliant set method for the key has been invoked, or that a -willChangeValueForKey:/-didChangeValueForKey: pair has otherwise been invoked.
 - For an _ordered_ to-many relationship, NSKeyValueChangeInsertion, NSKeyValueChangeRemoval, and NSKeyValueChangeReplacement indicate that a mutating message has been sent to the array returned by a -mutableArrayValueForKey: message sent to the object, or sent to the ordered set returned by a -mutableOrderedSetValueForKey: message sent to the object, or that one of the key-value coding-compliant array or ordered set mutation methods for the key has been invoked, or that a -willChange:valuesAtIndexes:forKey:/-didChange:valuesAtIndexes:forKey: pair has otherwise been invoked.
 - For an _unordered_ to-many relationship (introduced in Mac OS 10.4), NSKeyValueChangeInsertion, NSKeyValueChangeRemoval, and NSKeyValueChangeReplacement indicate that a mutating message has been sent to the set returned by a -mutableSetValueForKey: message sent to the object, or that one of the key-value coding-compliant set mutation methods for the key has been invoked, or that a -willChangeValueForKey:withSetMutation:usingObjects:/-didChangeValueForKey:withSetMutation:usingObjects: pair has otherwise been invoked.
 
 For any sort of property, the change dictionary contains an NSKeyValueChangeNewKey entry if NSKeyValueObservingOptionNew was specified at observer registration time, it's the right kind of change, and this isn't a prior notification. The change dictionary contains an NSKeyValueChangeOldKey if NSKeyValueObservingOptionOld was specified and it's the right kind of change. See the comments for the NSKeyValueObserverNotification informal protocol methods for what the values of those entries can be.
 
 For an _ordered_ to-many relationship, the change dictionary always contains an NSKeyValueChangeIndexesKey entry whose value is an NSIndexSet containing the indexes of the inserted, removed, or replaced objects, unless the change is an NSKeyValueChangeSetting.
 
 If NSKeyValueObservingOptionPrior (introduced in Mac OS 10.5) was specified at observer registration time, and this notification is one being sent prior to a change as a result, the change dictionary contains an NSKeyValueChangeNotificationIsPriorKey entry whose value is an NSNumber wrapping YES (use -[NSNumber boolValue]).
 
 context is always the same pointer that was passed in at observer registration time.
 */
/*
 观察者必须实现observeValueForKeyPath:ofObject:change:context:方法，并定义观察者应该如何响应change notification.在这个方法中，change参数会传入一个NSDictionary，代表了与property的值变化相关的信息。当被观察的property的值发生变化的时候，或者它依赖的某一个key的值发生变化的时候，observeValueForKeyPath:ofObject:change:context:方法会自动被调用
这里的改变被观察的property的值，指的应该是这样几种方式中的一种：
    调用key-value compliant的accessor方法；
    使用key-value coding方法，如setValue:forKey:、insertValue:inPropertyWithKey:；
    使用mutableArrayValueForKey:取得一个代理对象，并操作这个代理对象。
    所以如果仅仅是改变了某个property所生成的instance variable的值，自动的change notification是不会发送的。
*/
- (void)observeValueForKeyPath:(nullable NSString *)keyPath ofObject:(nullable id)object change:(nullable NSDictionary<NSKeyValueChangeKey, id> *)change context:(nullable void *)context;

@end

@interface NSObject(NSKeyValueObserverRegistration)

/* Register or deregister as an observer of the value at a key path relative to the receiver. The options determine what is included in observer notifications and when they're sent, as described above, and the context is passed in observer notifications as described above. You should use -removeObserver:forKeyPath:context: instead of -removeObserver:forKeyPath: whenever possible because it allows you to more precisely specify your intent. When the same observer is registered for the same key path multiple times, but with different context pointers each time, -removeObserver:forKeyPath: has to guess at the context pointer when deciding what exactly to remove, and it can guess wrong.
 */
//对需要观察的property注册一个观察者,这时，观察者对象和被观察的对象之间会建立联系，这种联系是针对于对象的，而不是针对于类的.其中可以指定options参数,可以指定多个NSKeyValueObservingOptions，将他们用“或”连接后，作为options参数,可以将任意对象作为context参数，它会和观察者实现的observeValueForKeyPath:ofObject:change:context:方法中的context参数指向同一个对象。观察者必须实现observeValueForKeyPath:ofObject:change:context:方法，并定义观察者应该如何响应change notification
- (void)addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(nullable void *)context;
//当不再需要这个观察者的时候，需要调用removeObserver:forKeyPath:或者removeObserver:forKeyPath:context:方法，移除这个观察者,应该尽量使用removeObserver:forKeyPath:context:方法，因为如果当同样的observer和同样的key path被多次注册，但是每次注册使用的是不同的context，这时如果使用removeObserver:forKeyPath:方法，它就需要猜测到底移除哪一个观察者，当然这很可能猜错。那些在addObserver:forKeyPath:options:context:中指定的对象，必须在deallocate之前被移除掉。
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath context:(nullable void *)context NS_AVAILABLE(10_7, 5_0);
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath;

@end

@interface NSArray<ObjectType>(NSKeyValueObserverRegistration)

/* Register or deregister as an observer of the values at a key path relative to each indexed element of the array. The options determine what is included in observer notifications and when they're sent, as described above, and the context is passed in observer notifications as described above. These are not merely convenience methods; invoking them is potentially much faster than repeatedly invoking NSObject(NSKeyValueObserverRegistration) methods. You should use -removeObserver:fromObjectsAtIndexes:forKeyPath:context: instead of -removeObserver:fromObjectsAtIndexes:forKeyPath: whenever possible for the same reason described in the NSObject(NSKeyValueObserverRegistration) comment.
 */
//Registers an observer to receive key value observer notifications for the specified key-path relative to the objects at the indexes.
//对数组中指定index的对象进行kvc观察
- (void)addObserver:(NSObject *)observer toObjectsAtIndexes:(NSIndexSet *)indexes forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(nullable void *)context;
- (void)removeObserver:(NSObject *)observer fromObjectsAtIndexes:(NSIndexSet *)indexes forKeyPath:(NSString *)keyPath context:(nullable void *)context NS_AVAILABLE(10_7, 5_0);
- (void)removeObserver:(NSObject *)observer fromObjectsAtIndexes:(NSIndexSet *)indexes forKeyPath:(NSString *)keyPath;

/* NSArrays are not observable, so these methods raise exceptions when invoked on NSArrays. Instead of observing an array, observe the ordered to-many relationship for which the array is the collection of related objects.
 */
- (void)addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(nullable void *)context;
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath context:(nullable void *)context NS_AVAILABLE(10_7, 5_0);
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath;

@end

@interface NSOrderedSet<ObjectType>(NSKeyValueObserverRegistration)

/* NSOrderedSets are not observable, so these methods raise exceptions when invoked on NSOrderedSets. Instead of observing an ordered set, observe the ordered to-many relationship for which the ordered set is the collection of related objects.
 */
- (void)addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(nullable void *)context;
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath context:(nullable void *)context NS_AVAILABLE(10_7, 5_0);
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath;

@end

@interface NSSet<ObjectType>(NSKeyValueObserverRegistration)

/* NSSets are not observable, so these methods raise exceptions when invoked on NSSets. Instead of observing a set, observe the unordered to-many relationship for which the set is the collection of related objects.
 */
- (void)addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(nullable void *)context;
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath context:(nullable void *)context NS_AVAILABLE(10_7, 5_0);
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath;

@end

@interface NSObject(NSKeyValueObserverNotification)

/* Given a key that identifies a property (attribute, to-one relationship, or ordered or unordered to-many relationship), send -observeValueForKeyPath:ofObject:change:context: notification messages of kind NSKeyValueChangeSetting to each observer registered for the key, including those that are registered with other objects using key paths that locate the keyed value in this object. Invocations of these methods must always be paired.
 
 The change dictionaries in notifications resulting from use of these methods contain optional entries if requested at observer registration time:
 - The NSKeyValueChangeOldKey entry, if present, contains the value returned by -valueForKey: at the instant that -willChangeValueForKey: is invoked (or an NSNull if -valueForKey: returns nil).
 - The NSKeyValueChangeNewKey entry, if present, contains the value returned by -valueForKey: at the instant that -didChangeValueForKey: is invoked (or an NSNull if -valueForKey: returns nil).
 */
//willChangeValueForKey:和didChangeValueForKey:调用时都会调用valueForKey:，并把得到的结果分别当成old value和new value，以告知观察者
//在property的值改变之前调用willChangeValueForKey:
- (void)willChangeValueForKey:(NSString *)key;
//在值改变之后调用didChangeValueForKey:
- (void)didChangeValueForKey:(NSString *)key;

/* Given a key that identifies an _ordered_ to-many relationship, send -observeValueForKeyPath:ofObject:change:context: notification messages of the passed-in change kind to each observer registered for the key, including those that are registered with other objects using key paths that locate the keyed value in this object. The passed-in kind must be NSKeyValueChangeInsertion, NSKeyValueChangeRemoval, or NSKeyValueChangeReplacement. The passed-in index set must be the indexes of the objects being inserted, removed, or replaced. Invocations of these methods must always be paired, with identical arguments.
 
 The change dictionaries in notifications resulting from use of these methods contain optional entries if requested at observer registration time:
 - The NSKeyValueChangeOldKey entry, if present (only for NSKeyValueChangeRemoval and NSKeyValueChangeReplacement), contains an array of the indexed objects from the array returned by -valueForKey: at the instant that -willChangeValueForKey:valuesAtIndexes:forKey: is invoked.
 - The NSKeyValueChangeNewKey entry, if present (only for NSKeyValueChangeInsertion and NSKeyValueChangeReplacement), contains an array of the indexed objects from the array returned by -valueForKey: at the instant that -didChangeValueForKey:valuesAtIndexes:forKey: is invoked.
 */
- (void)willChange:(NSKeyValueChange)changeKind valuesAtIndexes:(NSIndexSet *)indexes forKey:(NSString *)key;
- (void)didChange:(NSKeyValueChange)changeKind valuesAtIndexes:(NSIndexSet *)indexes forKey:(NSString *)key;

/* Given a key that identifies an _unordered_ to-many relationship, send -observeValueForKeyPath:ofObject:change:context: notification messages to each observer registered for the key, including those that are registered with other objects using key paths that locate the keyed value in this object. The passed-in mutation kind corresponds to an NSMutableSet method. The passed-in set must contain the set that would be passed to the corresponding NSMutableSet method. Invocations of these methods must always be paired, with identical arguments.
 
 The value of the NSKeyValueChangeKindKey entry in change dictionaries in notifications resulting from use of these methods depends on the passed-in mutationKind value:
 - NSKeyValueUnionSetMutation -> NSKeyValueChangeInsertion
 - NSKeyValueMinusSetMutation -> NSKeyValueChangeRemoval
 - NSKeyValueIntersectSetMutation -> NSKeyValueChangeRemoval
 - NSKeyValueSetSetMutation -> NSKeyValueChangeReplacement
 
 The change dictionaries may also contain optional entries:
 - The NSKeyValueChangeOldKey entry, if present (only for for NSKeyValueChangeRemoval and NSKeyValueChangeReplacement), contains the set of objects that were removed.
 - The NSKeyValueChangeNewKey entry, if present (only for NSKeyValueChangeInsertion and NSKeyValueChangeReplacement), contains the set of objects that were added.
 */
- (void)willChangeValueForKey:(NSString *)key withSetMutation:(NSKeyValueSetMutationKind)mutationKind usingObjects:(NSSet *)objects;
- (void)didChangeValueForKey:(NSString *)key withSetMutation:(NSKeyValueSetMutationKind)mutationKind usingObjects:(NSSet *)objects;

@end

@interface NSObject(NSKeyValueObservingCustomization)

/* Return a set of key paths for properties whose values affect the value of the keyed property. When an observer for the key is registered with an instance of the receiving class, KVO itself automatically observes all of the key paths for the same instance, and sends change notifications for the key to the observer when the value for any of those key paths changes. The default implementation of this method searches the receiving class for a method whose name matches the pattern +keyPathsForValuesAffecting<Key>, and returns the result of invoking that method if it is found. So, any such method must return an NSSet too. If no such method is found, an NSSet that is computed from information provided by previous invocations of the now-deprecated +setKeys:triggerChangeNotificationsForDependentKey: method is returned, for backward binary compatibility.
 
 This method and KVO's automatic use of it comprise a dependency mechanism that you can use instead of sending -willChangeValueForKey:/-didChangeValueForKey: messages for dependent, computed, properties.
 
 You can override this method when the getter method of one of your properties computes a value to return using the values of other properties, including those that are located by key paths. Your override should typically invoke super and return a set that includes any members in the set that result from doing that (so as not to interfere with overrides of this method in superclasses).
 
 You can't really override this method when you add a computed property to an existing class using a category, because you're not supposed to override methods in categories. In that case, implement a matching +keyPathsForValuesAffecting<Key> to take advantage of this mechanism.
 */

/*
 对于to-one relationship的property，重写keyPathsForValuesAffectingValueForKey:或者keyPathsForValuesAffecting<Key>方法可以定义这个key所依赖的一系列key。但是这个方法仅限于to-one relationship的property。
 
 官方示例代码：
 + (NSSet *)keyPathsForValuesAffectingFullName
 {
     return [NSSet setWithObjects:@"lastName", @"firstName", nil];
 }
 而对于to-many relationship，要么手动观察每一个依赖的key，要么利用Core Data来完成这个任务
 */
+ (NSSet<NSString *> *)keyPathsForValuesAffectingValueForKey:(NSString *)key NS_AVAILABLE(10_5, 2_0);
//
/* Return YES if the key-value observing machinery should automatically invoke -willChangeValueForKey:/-didChangeValueForKey:, -willChange:valuesAtIndexes:forKey:/-didChange:valuesAtIndexes:forKey:, or -willChangeValueForKey:withSetMutation:usingObjects:/-didChangeValueForKey:withSetMutation:usingObjects: whenever instances of the class receive key-value coding messages for the key, or mutating key-value coding-compliant methods for the key are invoked. Return NO otherwise. Starting in Mac OS 10.5, the default implementation of this method searches the receiving class for a method whose name matches the pattern +automaticallyNotifiesObserversOf<Key>, and returns the result of invoking that method if it is found. So, any such method must return BOOL too. If no such method is found YES is returned.
 */

/*
 按照上面说的方法，为某个property设立一个观察者，这个观察者就会收到系统自动发送的change notification。然而，第三方程序员也可以手动发送change notification。手动发送change notification可以更自由的控制通知发送的逻辑。
 
 如果一个类想要实现手动的change notification发送，则必须重写NSObject实现的automaticallyNotifiesObserversForKey:方法，并对需要实现手动发送的key返回NO，其余则调用super。
 
 官方示例代码：
 
 + (BOOL)automaticallyNotifiesObserversForKey:(NSString *)theKey 
 {
     BOOL automatic = NO;
     if ([theKey isEqualToString:@"openingBalance"]) 
     {
         automatic = NO;
     }
     else 
     {
     automatic = [super automaticallyNotifiesObserversForKey:theKey];
     }
     return automatic;
 }
 
 然后在property的值改变之前调用willChangeValueForKey:，在值改变之后调用didChangeValueForKey:。当然，在什么样的情况下才调用这两个方法，是由第三方程序的逻辑决定的。
 
 如果一个操作造成了多个key的值的改变，则willChangeValueForKey:和didChangeValueForKey:必须嵌套着调用。
 
 官方示例代码：
 
 - (void)setOpeningBalance:(double)theBalance 
 {
     [self willChangeValueForKey:@"openingBalance"];
     [self willChangeValueForKey:@"itemChanged"];
     _openingBalance = theBalance;
     _itemChanged = _itemChanged+1;
     [self didChangeValueForKey:@"itemChanged"];
     [self didChangeValueForKey:@"openingBalance"];
 }
 willChangeValueForKey:和didChangeValueForKey:调用时都会调用valueForKey:，并把得到的结果分别当成old value和new value，以告知观察者。
 
 做了个小实验，发现在自动发送change notification的情况下，willChangeValueForKey:和didChangeValueForKey:也会被调用，看来系统也是通过这两个方法来发送通知的。
 
 如果手动发送change notification的property是ordered to-many relationship，则不仅要指定被改变的key，还要指定改变的类型和index。类型用NSKeyValueChange来表示。
 */
+ (BOOL)automaticallyNotifiesObserversForKey:(NSString *)key;

/* Take or return a pointer that identifies information about all of the observers that are registered with the receiver, the options that were used at registration-time, etc. The default implementation of these methods store observation info in a global dictionary keyed by the receivers' pointers. For improved performance, you can override these methods to store the opaque data pointer in an instance variable. Overrides of these methods must not attempt to send Objective-C messages to the passed-in observation info, including -retain and -release.
 */
//Returns a pointer that identifies information about all of the observers that are registered with the receiver.
@property (nullable) void *observationInfo NS_RETURNS_INNER_POINTER;

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

@interface NSObject(NSDeprecatedKeyValueObservingCustomization)

/* A method that was deprecated in Mac OS 10.5, in favor of using +keyPathsForValuesAffectingValueForKey:. Registers the fact that invocations of -willChangeValueForKey:/-didChangeValueForKey:, -willChange:valuesAtIndexes:forKey:/-didChange:valuesAtIndexes:forKey:, and -willChangeValueForKey:withSetMutation:usingObjects:/-didChangeValueForKey:withSetMutation:usingObjects: for any key in the passed-in array should also send notifications for the dependent key.
 */
+ (void)setKeys:(NSArray *)keys triggerChangeNotificationsForDependentKey:(NSString *)dependentKey NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);

@end

#endif

NS_ASSUME_NONNULL_END
