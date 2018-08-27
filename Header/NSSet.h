/*	NSSet.h
	Copyright (c) 1994-2016, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>

/*
 集合（NSSet）和数组（NSArray）有相似之处，都是存储不同的对象的地址，不过NSArray是有序的集合，NSSet是无序的集合，同时NSSet可以保证数据的唯一性，当插入相同的数据时，不会有任何效果。集合是一种哈希表，运用散列算法，查找集合中的元素比数组速度更快，但是它没有顺序
 */
@class NSArray, NSDictionary, NSString;

/****************	Immutable Set	****************/

NS_ASSUME_NONNULL_BEGIN

@interface NSSet<__covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

@property (readonly) NSUInteger count;
//Determines whether the hash table contains a given object, and returns that object if it is present
//判断两个对象的值是否相等，用来查询set里面是否有一个对象与传入对象的值相等
- (nullable ObjectType)member:(ObjectType)object;
//返回集合中所有对象到一个NSEumerator类型的对象
- (NSEnumerator<ObjectType> *)objectEnumerator;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
//使用一组对象初始化新分配的对象
- (instancetype)initWithObjects:(const ObjectType _Nonnull [_Nullable])objects count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSSet<ObjectType> (NSExtendedSet)
//所有对象的数组属性
@property (readonly, copy) NSArray<ObjectType> *allObjects;
//返回集合中的某个对象
- (nullable ObjectType)anyObject;
//判断集合中是否有对象
- (BOOL)containsObject:(ObjectType)anObject;
//将集合转化成字符串，也可以通过改变description改变字符串
@property (readonly, copy) NSString *description;
- (NSString *)descriptionWithLocale:(nullable id)locale;
//判断在一个集合中是否可以插入另外一个集合
- (BOOL)intersectsSet:(NSSet<ObjectType> *)otherSet;
//判断两个集合是否相等
- (BOOL)isEqualToSet:(NSSet<ObjectType> *)otherSet;
//判断一个集合是否是另外一个集合的子集
- (BOOL)isSubsetOfSet:(NSSet<ObjectType> *)otherSet;
//让集合中的对象执行指定的方法（遍历）
- (void)makeObjectsPerformSelector:(SEL)aSelector NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(nullable id)argument NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");
//在集合中追加一个对象 返回set
- (NSSet<ObjectType> *)setByAddingObject:(ObjectType)anObject NS_AVAILABLE(10_5, 2_0);
//在集合中追加另外一个集合
- (NSSet<ObjectType> *)setByAddingObjectsFromSet:(NSSet<ObjectType> *)other NS_AVAILABLE(10_5, 2_0);
//在一个集合后面追加一个数组，返回一个新的集合set
- (NSSet<ObjectType> *)setByAddingObjectsFromArray:(NSArray<ObjectType> *)other NS_AVAILABLE(10_5, 2_0);
//遍历整个集合 执行在block中
- (void)enumerateObjectsUsingBlock:(void (NS_NOESCAPE ^)(ObjectType obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
//遍历整个集合 并且有遍历选项条件
- (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(ObjectType obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
//这个方法标示着传入函数的参数是一个动态对象类型和一个布尔类型，返回一个布尔类型的代码块
- (NSSet<ObjectType> *)objectsPassingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
//同上，增加了列举计算选项
- (NSSet<ObjectType> *)objectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

@end

@interface NSSet<ObjectType> (NSSetCreation)
//快速创建set
+ (instancetype)set;
//创建set并初始化一个对象
+ (instancetype)setWithObject:(ObjectType)object;
//创建set并初始化一些对象 分配大小
+ (instancetype)setWithObjects:(const ObjectType [])objects count:(NSUInteger)cnt;
//创建set并初始化一些对象 以nil结尾
+ (instancetype)setWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
//以set初始化
+ (instancetype)setWithSet:(NSSet<ObjectType> *)set;
//以数组初始化
+ (instancetype)setWithArray:(NSArray<ObjectType> *)array;
- (instancetype)initWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
- (instancetype)initWithSet:(NSSet<ObjectType> *)set;
- (instancetype)initWithSet:(NSSet<ObjectType> *)set copyItems:(BOOL)flag;
- (instancetype)initWithArray:(NSArray<ObjectType> *)array;

@end

/****************	Mutable Set	****************/

@interface NSMutableSet<ObjectType> : NSSet<ObjectType>
//可变set添加一个对象
- (void)addObject:(ObjectType)object;
//移除set对象
- (void)removeObject:(ObjectType)object;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
//为set初始化设置大小
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;

@end

@interface NSMutableSet<ObjectType> (NSExtendedMutableSet)
//为set添加对象通过数组
- (void)addObjectsFromArray:(NSArray<ObjectType> *)array;
//为set插入新的set
- (void)intersectSet:(NSSet<ObjectType> *)otherSet;
//从接受者中删除NSSet的左右成员
- (void)minusSet:(NSSet<ObjectType> *)otherSet;
//移除set的所有对象元素
- (void)removeAllObjects;
//取两个集合的并集，如果给定集合中的成员不是接收集合的成员，则将这个成员添加到接收集合中
- (void)unionSet:(NSSet<ObjectType> *)otherSet;
//将otherSet替换了set并且将两个集合的交集加到set中
- (void)setSet:(NSSet<ObjectType> *)otherSet;

@end

@interface NSMutableSet<ObjectType> (NSMutableSetCreation)
//新建集合 并且设置初始化的长度
+ (instancetype)setWithCapacity:(NSUInteger)numItems;

@end

/****************	Counted Set	****************/

@interface NSCountedSet<ObjectType> : NSMutableSet<ObjectType> {
@private
    id _table;
    void *_reserved;
}
//创建集合 并且初始化长度
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;
//创建集合 以数组初始化对象
- (instancetype)initWithArray:(NSArray<ObjectType> *)array;
//创建集合 以其他set初始化集合对象
- (instancetype)initWithSet:(NSSet<ObjectType> *)set;
//统计重复集合对象的个数
- (NSUInteger)countForObject:(ObjectType)object;
//返回一个枚举类型
- (NSEnumerator<ObjectType> *)objectEnumerator;
//添加一个对象
- (void)addObject:(ObjectType)object;
//移除一个对象
- (void)removeObject:(ObjectType)object;

@end

NS_ASSUME_NONNULL_END
