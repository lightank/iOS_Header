/*	NSDictionary.h
	Copyright (c) 1994-2016, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>

@class NSArray<ObjectType>, NSSet<ObjectType>, NSString, NSURL;

/****************	Immutable Dictionary	****************/

NS_ASSUME_NONNULL_BEGIN

@interface NSDictionary<__covariant KeyType, __covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

@property (readonly) NSUInteger count;
//Returns the value for the given key stored in the record.
//利用指定的key寻找对应的value
- (nullable ObjectType)objectForKey:(KeyType)aKey;
//Returns an enumerator object that lets you access each key in the map table.
//将词典的所有KEY储存在NSEnumerator中，NSEnumerator很像Java语言 中的迭代器，使用快速枚举可以遍历词典中所有储存KEY值
//keyEnumerator得到一个字典的所有键值
- (NSEnumerator<KeyType> *)keyEnumerator;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
//条件编译根据不同情况来初始化字典
#if TARGET_OS_WIN32
- (instancetype)initWithObjects:(const ObjectType _Nonnull [_Nullable])objects forKeys:(const KeyType _Nonnull [_Nullable])keys count:(NSUInteger)cnt;
#else
- (instancetype)initWithObjects:(const ObjectType _Nonnull [_Nullable])objects forKeys:(const KeyType <NSCopying> _Nonnull [_Nullable])keys count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
#endif
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSDictionary<KeyType, ObjectType> (NSExtendedDictionary)
//所有key数组
@property (readonly, copy) NSArray<KeyType> *allKeys;
//根据所填入的object返回对应所有的key键值
- (NSArray<KeyType> *)allKeysForObject:(ObjectType)anObject;
//所有value数组
@property (readonly, copy) NSArray<ObjectType> *allValues;
//字符串描述
@property (readonly, copy) NSString *description;
//字符串描述文件格式
@property (readonly, copy) NSString *descriptionInStringsFileFormat;
//Returns a string that represents the contents of the array, formatted as a property list.
//以plist格式返回数组内容的字符串
- (NSString *)descriptionWithLocale:(nullable id)locale;
//Returns a string that represents the contents of the array, formatted as a property list.
/**
 @param locale An NSLocale object or an NSDictionary object that specifies options used for formatting each of the array’s elements (where recognized). Specify nil if you don’t want the elements formatted.
 @param level A level of indent, to make the output more readable: set level to 0 to use four spaces to indent, or 1 to indent the output with a tab character.
 */
- (NSString *)descriptionWithLocale:(nullable id)locale indent:(NSUInteger)level;
//判断字典是否相等
- (BOOL)isEqualToDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
//Returns an enumerator object that lets you access each object in the array.
//得到一个字典的所有values
- (NSEnumerator<ObjectType> *)objectEnumerator;
//Returns the set of objects from the dictionary that corresponds to the specified keys as an NSArray.
//字典将某个特定的数组作为key值传进去得到对应的value，如果某个key找不到对应的key，就用notFoundMarker提前设定的值代替
- (NSArray<ObjectType> *)objectsForKeys:(NSArray<KeyType> *)keys notFoundMarker:(ObjectType)marker;
//将字典写进特定的路径path
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically; // the atomically flag is ignored if url of a type that cannot be written atomically.
//Returns an array of the dictionary’s keys, in the order they would be in if the dictionary were sorted by its values.

/**
 @param comparator A selector that specifies the method to use to compare the values in the dictionary.
 
 The comparator method should return NSOrderedAscending if the dictionary value is smaller than the argument, NSOrderedDescending if the dictionary value is larger than the argument, and NSOrderedSame if they are equal.
 */
//字典按照value的大小顺序来对keys键值进行排序（通过value排序，返回key集合）
/*
 NSDictionary里的keysSortedByValueUsingSelector排序使用
 @implementation NSString(compare)
 -(NSComparisonResult)floatCompare:(NSString*)other
 {
     float myValue = [self floatValue];
     float otherValue= [other floatValue];
     if(myValue == otherValue) return NSOrderedSame;
     return (myValue < otherValue ? NSOrderedAscending : NSOrderedDescending);
 }
 @end
 
 NSString* names[] = ", @"220091111", @"5", @"7",nil};
 NSString* values[] = ", @"23.5", @"89.12", @"333.2", nil};
 NSDictionary* dic = [NSDictionary dictionaryWithObjects:(id*)names forKeys:(id*)values count:4];
 NSArray* res = [dic keysSortedByValueUsingSelector:@selector(floatCompare:)];
 NSLog(@"%@", res);
 NSLog(@"%@", dic);
 */
- (NSArray<KeyType> *)keysSortedByValueUsingSelector:(SEL)comparator;
// count refers to the number of elements in the dictionary
- (void)getObjects:(ObjectType __unsafe_unretained [])objects andKeys:(KeyType __unsafe_unretained [])keys count:(NSUInteger)count NS_AVAILABLE(10_7, 5_0) NS_SWIFT_UNAVAILABLE("Use 'allKeys' and/or 'allValues' instead");
//Returns the value for the given key stored in the record.
- (nullable ObjectType)objectForKeyedSubscript:(KeyType)key NS_AVAILABLE(10_8, 6_0);
//利用block对字典进行遍历
- (void)enumerateKeysAndObjectsUsingBlock:(void (NS_NOESCAPE ^)(KeyType key, ObjectType obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
//同上一样利用block对字典进行遍历，不过加了排序的顺序选项options正反序
- (void)enumerateKeysAndObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(KeyType key, ObjectType obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
//都是利用value对keys进行排序，只不过这个加上了一个可设定的NSComparato参数条件来比较
- (NSArray<KeyType> *)keysSortedByValueUsingComparator:(NSComparator NS_NOESCAPE)cmptr NS_AVAILABLE(10_6, 4_0);
//通过values对字典的keys进行排序，可以有排序的选择，还可添加设定的NSComparato参数条件来比较
- (NSArray<KeyType> *)keysSortedByValueWithOptions:(NSSortOptions)opts usingComparator:(NSComparator NS_NOESCAPE)cmptr NS_AVAILABLE(10_6, 4_0);
//这是一个很好的对字典进行过滤的方法,返回keys的集合，这些keys符合参数block的约束，在block内部在特定的条件下返回yes，返回的这个集合会保留当前遍历到那个字典对象的信息
/*
 NSDictionary * numsDic =@{@(2):@"second",@(4):@"first",@(1):@"thrid"};
 NSSet * filteredKeys = [numsDic keysOfEntriesPassingTest:^BOOL(id key,id obj, BOOL *stop) {
     BOOL result = NO;
     NSNumber * numKey = key;
     if (numKey.integerValue >2) {
     result =YES;
     }
     return YES;
 }];
 NSLog(@"filteredKeys.description----%@",filteredKeys.description);
 //打印:
 2015-06-08 17:34:37.741 NSDictionary[4085:193311] filteredKeys.description----{(
 4
 )}
 */
- (NSSet<KeyType> *)keysOfEntriesPassingTest:(BOOL (NS_NOESCAPE ^)(KeyType key, ObjectType obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
//用法同上，增加了一个列举的选项选择
- (NSSet<KeyType> *)keysOfEntriesWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(KeyType key, ObjectType obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

@end

@interface NSDictionary<KeyType, ObjectType> (NSDeprecated)
/// This method is unsafe because it could potentially cause buffer overruns. You should use -getObjects:andKeys:count:
- (void)getObjects:(ObjectType __unsafe_unretained [])objects andKeys:(KeyType __unsafe_unretained [])keys  NS_SWIFT_UNAVAILABLE("Use 'allKeys' and/or 'allValues' instead");
@end

@interface NSDictionary<KeyType, ObjectType> (NSDictionaryCreation)
//快速创建一个空字典
+ (instancetype)dictionary;
//快速创建字典并且赋初值
+ (instancetype)dictionaryWithObject:(ObjectType)object forKey:(KeyType <NSCopying>)key;
//条件编译 不同情况创建字典的几种方法
#if TARGET_OS_WIN32
+ (instancetype)dictionaryWithObjects:(const ObjectType [])objects forKeys:(const KeyType [])keys count:(NSUInteger)cnt;
#else
+ (instancetype)dictionaryWithObjects:(const ObjectType [])objects forKeys:(const KeyType <NSCopying> [])keys count:(NSUInteger)cnt;
#endif

+ (instancetype)dictionaryWithObjectsAndKeys:(id)firstObject, ... NS_REQUIRES_NIL_TERMINATION NS_SWIFT_UNAVAILABLE("Use dictionary literals instead");
//使用另一个字典初始化字典
+ (instancetype)dictionaryWithDictionary:(NSDictionary<KeyType, ObjectType> *)dict;
//创建字典，通过数组赋值values和keys
+ (instancetype)dictionaryWithObjects:(NSArray<ObjectType> *)objects forKeys:(NSArray<KeyType <NSCopying>> *)keys;
//使用指定的以nil为结尾的对象与键对列表初始化列表
- (instancetype)initWithObjectsAndKeys:(id)firstObject, ... NS_REQUIRES_NIL_TERMINATION;
//使用另一个字典初始化字典
- (instancetype)initWithDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
//使用另一个字典初始化字典，还可以为每个对象创建新的副本
- (instancetype)initWithDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary copyItems:(BOOL)flag;
//使用指定的对象与键初始化字典
- (instancetype)initWithObjects:(NSArray<ObjectType> *)objects forKeys:(NSArray<KeyType <NSCopying>> *)keys;
//使用本地文件的内容初始化字典
+ (nullable NSDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfFile:(NSString *)path;
//使用URL的内容初始化字典
+ (nullable NSDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfURL:(NSURL *)url;
//使用本地文件的内容初始化字典
- (nullable NSDictionary<KeyType, ObjectType> *)initWithContentsOfFile:(NSString *)path;
//使用URL的内容初始化字典
- (nullable NSDictionary<KeyType, ObjectType> *)initWithContentsOfURL:(NSURL *)url;

@end

/****************	Mutable Dictionary	****************/

@interface NSMutableDictionary<KeyType, ObjectType> : NSDictionary<KeyType, ObjectType>
//根据对应的key删除对应的value以及自身的key
- (void)removeObjectForKey:(KeyType)aKey;
//在可变字典中，改变对应的key的value
- (void)setObject:(ObjectType)anObject forKey:(KeyType <NSCopying>)aKey;
//创建字典初始化
- (instancetype)init NS_DESIGNATED_INITIALIZER;
//初始化字典并且指定大小
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;
//序列化对象
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSMutableDictionary<KeyType, ObjectType> (NSExtendedMutableDictionary)
//一个字典整体拼接另一个字典中
- (void)addEntriesFromDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
//删除字典所有的数据
- (void)removeAllObjects;
//根据指定的数据keys删除对应的values
- (void)removeObjectsForKeys:(NSArray<KeyType> *)keyArray;
//Sets the contents of the receiving dictionary to entries in a given dictionary.
//使用另一个字典重置当前字典
- (void)setDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
//以数组下标的形式来访问相应键的值
- (void)setObject:(nullable ObjectType)obj forKeyedSubscript:(KeyType <NSCopying>)key NS_AVAILABLE(10_8, 6_0);

@end

@interface NSMutableDictionary<KeyType, ObjectType> (NSMutableDictionaryCreation)
//快速创建可变字典并且初始化大小
+ (instancetype)dictionaryWithCapacity:(NSUInteger)numItems;
//快速创建可变字典通过指定的文件路径
+ (nullable NSMutableDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfFile:(NSString *)path;
//快速创建可变字典通过URL
+ (nullable NSMutableDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfURL:(NSURL *)url;
- (nullable NSMutableDictionary<KeyType, ObjectType> *)initWithContentsOfFile:(NSString *)path;
- (nullable NSMutableDictionary<KeyType, ObjectType> *)initWithContentsOfURL:(NSURL *)url;

@end

@interface NSDictionary<KeyType, ObjectType> (NSSharedKeySetDictionary)

/*  Use this method to create a key set to pass to +dictionaryWithSharedKeySet:.
 The keys are copied from the array and must be copyable.
 If the array parameter is nil or not an NSArray, an exception is thrown.
 If the array of keys is empty, an empty key set is returned.
 The array of keys may contain duplicates, which are ignored (it is undefined which object of each duplicate pair is used).
 As for any usage of hashing, is recommended that the keys have a well-distributed implementation of -hash, and the hash codes must satisfy the hash/isEqual: invariant.
 Keys with duplicate hash codes are allowed, but will cause lower performance and increase memory usage.
 */
//Creates a shared key set object for the specified keys.
//keys: The array of keys. If the parameter is nil, an exception is thrown. If the array of keys is empty, an empty key set is returned.
+ (id)sharedKeySetForKeys:(NSArray<KeyType <NSCopying>> *)keys NS_AVAILABLE(10_8, 6_0);

@end

@interface NSMutableDictionary<KeyType, ObjectType> (NSSharedKeySetDictionary)

/*  Create a mutable dictionary which is optimized for dealing with a known set of keys.
 Keys that are not in the key set can still be set into the dictionary, but that usage is not optimal.
 As with any dictionary, the keys must be copyable.
 If keyset is nil, an exception is thrown.
 If keyset is not an object returned by +sharedKeySetForKeys:, an exception is thrown.
 */
+ (NSMutableDictionary<KeyType, ObjectType> *)dictionaryWithSharedKeySet:(id)keyset NS_AVAILABLE(10_8, 6_0);

@end

NS_ASSUME_NONNULL_END
