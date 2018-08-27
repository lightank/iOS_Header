/*	NSArray.h
	Copyright (c) 1994-2016, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSObjCRuntime.h>

@class NSData, NSIndexSet, NSString, NSURL;

/****************	Immutable Array		****************/

NS_ASSUME_NONNULL_BEGIN

@interface NSArray<__covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>
//数组元素个数
@property (readonly) NSUInteger count;
//返回数组指定下标的元素
- (ObjectType)objectAtIndex:(NSUInteger)index;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
//初始化数组,同时赋初值及大小
- (instancetype)initWithObjects:(const ObjectType _Nonnull [_Nullable])objects count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSArray<ObjectType> (NSExtendedArray)
//追加对象
- (NSArray<ObjectType> *)arrayByAddingObject:(ObjectType)anObject;
//追加其它数组并返回新的数组
- (NSArray<ObjectType> *)arrayByAddingObjectsFromArray:(NSArray<ObjectType> *)otherArray;
//分割数组为字符串
- (NSString *)componentsJoinedByString:(NSString *)separator;
//判断数组是否存在指定元素
- (BOOL)containsObject:(ObjectType)anObject;
//格式化属性列表
@property (readonly, copy) NSString *description;
//本地格式化为一个属性列表
- (NSString *)descriptionWithLocale:(nullable id)locale;
//本地格式化为一个属性列表，并且可以设置缩进
- (NSString *)descriptionWithLocale:(nullable id)locale indent:(NSUInteger)level;
//取出array对象跟其它数组对象第一个交集元素
- (nullable ObjectType)firstObjectCommonWithArray:(NSArray<ObjectType> *)otherArray;
//返回指定区域的对象
- (void)getObjects:(ObjectType __unsafe_unretained [])objects range:(NSRange)range NS_SWIFT_UNAVAILABLE("Use 'subarrayWithRange()' instead");
//获取指定元素的索引
- (NSUInteger)indexOfObject:(ObjectType)anObject;
//指定区域获取元素的索引
- (NSUInteger)indexOfObject:(ObjectType)anObject inRange:(NSRange)range;
//获取指定元素的索引
- (NSUInteger)indexOfObjectIdenticalTo:(ObjectType)anObject;
//指定区域获取元素的索引
- (NSUInteger)indexOfObjectIdenticalTo:(ObjectType)anObject inRange:(NSRange)range;
//判断两个数组对象是否相等
- (BOOL)isEqualToArray:(NSArray<ObjectType> *)otherArray;
//第一个对象属性
@property (nullable, nonatomic, readonly) ObjectType firstObject NS_AVAILABLE(10_6, 4_0);
//最后一个对象属性
@property (nullable, nonatomic, readonly) ObjectType lastObject;
//Returns an enumerator object that lets you access each object in the array.
//返回一个枚举对象
- (NSEnumerator<ObjectType> *)objectEnumerator;
//Returns an enumerator object that lets you access each object in the array, in reverse order.
//返回一个翻转的枚举对象
- (NSEnumerator<ObjectType> *)reverseObjectEnumerator;
//Analyzes the array and returns a “hint” that speeds the sorting of the array when the hint is supplied to sortedArrayUsingFunction:context:hint:. (read-only)
//升序排序数组元素
@property (readonly, copy) NSData *sortedArrayHint;
//调用指定方法排序数组元素
- (NSArray<ObjectType> *)sortedArrayUsingFunction:(NSInteger (NS_NOESCAPE *)(ObjectType, ObjectType, void * _Nullable))comparator context:(nullable void *)context;
//调用指定方法排序数组元素
- (NSArray<ObjectType> *)sortedArrayUsingFunction:(NSInteger (NS_NOESCAPE *)(ObjectType, ObjectType, void * _Nullable))comparator context:(nullable void *)context hint:(nullable NSData *)hint;
//指定比较方法排序数组元素
- (NSArray<ObjectType> *)sortedArrayUsingSelector:(SEL)comparator;
//返回指定区域的数组元素组成新的数组元素
- (NSArray<ObjectType> *)subarrayWithRange:(NSRange)range;
//保存数组对象到指定文件
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
//保存数组对象到指定URL
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically;
//让每个数组元素都调用指定方法
- (void)makeObjectsPerformSelector:(SEL)aSelector NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(nullable id)argument NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");
//指定索引集合返回新数组
- (NSArray<ObjectType> *)objectsAtIndexes:(NSIndexSet *)indexes;
//返回指定元素数组元素
- (ObjectType)objectAtIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);
//数组中的每个元素都执行代码块中方法 遍历
- (void)enumerateObjectsUsingBlock:(void (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
//指定块使数组每个元素都执行代码块中的代码
- (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
//遍历数组每个元素执行代码块中的方法
- (void)enumerateObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
//根据条件来获取一个NSUIndex对象，主要是根据条件进行数据遍历使用
/*
     NSArray *array = [NSArray arrayWithObjects:@"wendy",@"andy",@"tom",@"test", nil];
     NSInteger index = [array indexOfObjectPassingTest:^ BOOL (id tr,NSUInteger index, BOOL *te){
     NSString *s = (NSString *)tr;
     if([@"wendy" isEqualToString:s])
     {
        return YES;
     }
        return NO;
     }];
     NSLog(@"index==%ld",(long)index); //打印:index==0
 */
- (NSUInteger)indexOfObjectPassingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
//同上面的方法相同，区别在于，这里添加了一个参数，用来表示遍历是从前向后遍历还是从后向前遍历
- (NSUInteger)indexOfObjectWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
//这个添加了参数NSIndexSet参数，用来获取子数组，然后使用子数组进行遍历，处理数据
- (NSUInteger)indexOfObjectAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
//根据block的处理获取一个NSIndexSet对象
/*
 NSIndexSet *index = [array indexesOfObjectsPassingTest: ^ BOOL (id tr, NSUInteger index,BOOL *te){
     NSString *s = (NSString *)tr;
     if([s isEqualToString:@"andy"]){
         return YES;
     }
     return NO;
     }];
     NSLog(@"%@",index);
 打印:NSArray[5128:150086] <NSIndexSet: 0x7fb542515710>[number of indexes: 1 (in 1 ranges), indexes: (1)]
 */
- (NSIndexSet *)indexesOfObjectsPassingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
//这个方法添加了参数，用来表示是从前向后遍历还是从后向前遍历
/*
 NSIndexSet *index = [array indexesOfObjectsPassingTest: ^ BOOL (id tr, NSUInteger index,BOOL *te){
     NSString *s = (NSString *)tr;
     if([s isEqualToString:@"andy"]){
     return YES;
     }
     return NO;
 }];
 NSLog(@"%@",index);
 打印:NSArray[5283:158602] <NSIndexSet: 0x7fa540ca6bb0>[number of indexes: 1 (in 1 ranges), indexes: (1)]
 */
- (NSIndexSet *)indexesOfObjectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
//添加参数NSIndexSet用来获取子数组，使用子数组进行遍历
- (NSIndexSet *)indexesOfObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
//对数组进行排序操作，参数cmptr是一个block函数块，返回的数据类型是一个NSComparisonResult对象
- (NSArray<ObjectType> *)sortedArrayUsingComparator:(NSComparator NS_NOESCAPE)cmptr NS_AVAILABLE(10_6, 4_0);
//进行排序操作，NSSortOptions排序的参数用来表示是同时排序，还是稳定排序
/*
 NSArray *test = [array sortedArrayWithOptions:NSSortStable usingComparator:^ NSComparisonResult (NSString *s,NSString *s2){
         if(s.length < s2.length){
         return NSOrderedAscending;
         }
         if(s.length > s2.length){
         return NSOrderedDescending;
         }
         return NSOrderedSame;
 }];
 NSLog(@"%@",test);
 例如NSArray[5332:161773] (
                             tom,
                             andy,
                             test,
                             wendy
                             )

 */
- (NSArray<ObjectType> *)sortedArrayWithOptions:(NSSortOptions)opts usingComparator:(NSComparator NS_NOESCAPE)cmptr NS_AVAILABLE(10_6, 4_0);

typedef NS_OPTIONS(NSUInteger, NSBinarySearchingOptions) {
    NSBinarySearchingFirstEqual = (1UL << 8),
    NSBinarySearchingLastEqual = (1UL << 9),
    NSBinarySearchingInsertionIndex = (1UL << 10),
};
//指定区域返回通过代码块方法的索引
- (NSUInteger)indexOfObject:(ObjectType)obj inSortedRange:(NSRange)r options:(NSBinarySearchingOptions)opts usingComparator:(NSComparator NS_NOESCAPE)cmp NS_AVAILABLE(10_6, 4_0); // binary search

@end

@interface NSArray<ObjectType> (NSArrayCreation)
//快速创建一个空数组
+ (instancetype)array;
//指定一个元素创建数组对象
+ (instancetype)arrayWithObject:(ObjectType)anObject;
//指定个数从一个数组对象创建新的数组对象
+ (instancetype)arrayWithObjects:(const ObjectType [])objects count:(NSUInteger)cnt;
//指定多个元素创建数组对象
+ (instancetype)arrayWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
//生成新的另外一个数组
+ (instancetype)arrayWithArray:(NSArray<ObjectType> *)array;
//指定个数从一个数组对象创建新的数组对象
- (instancetype)initWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
//从已有数组初始化
- (instancetype)initWithArray:(NSArray<ObjectType> *)array;
//从已有数组初始化（标示作用，潜复制，还是深复制）
- (instancetype)initWithArray:(NSArray<ObjectType> *)array copyItems:(BOOL)flag;
//从文件加载数组元素
+ (nullable NSArray<ObjectType> *)arrayWithContentsOfFile:(NSString *)path;
//从URL路径加载数组元素
+ (nullable NSArray<ObjectType> *)arrayWithContentsOfURL:(NSURL *)url;
//从文件加载数据
- (nullable NSArray<ObjectType> *)initWithContentsOfFile:(NSString *)path;
//从URL路径加载数组元素
- (nullable NSArray<ObjectType> *)initWithContentsOfURL:(NSURL *)url;

@end

@interface NSArray<ObjectType> (NSDeprecated)

/* This method is unsafe because it could potentially cause buffer overruns. You should use -getObjects:range: instead.
 */
- (void)getObjects:(ObjectType __unsafe_unretained [])objects NS_SWIFT_UNAVAILABLE("Use 'as [AnyObject]' instead");

@end

/****************	Mutable Array		****************/

@interface NSMutableArray<ObjectType> : NSArray<ObjectType>
//添加对象
- (void)addObject:(ObjectType)anObject;
//指定索引位置插入对象
- (void)insertObject:(ObjectType)anObject atIndex:(NSUInteger)index;
//移除最后一个对象
- (void)removeLastObject;
//移除指定索引对象
- (void)removeObjectAtIndex:(NSUInteger)index;
//用指定对象替换指定下标对象
- (void)replaceObjectAtIndex:(NSUInteger)index withObject:(ObjectType)anObject;
//初始化对象
- (instancetype)init NS_DESIGNATED_INITIALIZER;
//初始化对象并指定大小
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSMutableArray<ObjectType> (NSExtendedMutableArray)
//追加新数组A到指定数组B后面
- (void)addObjectsFromArray:(NSArray<ObjectType> *)otherArray;
//交换指定索引的对象
- (void)exchangeObjectAtIndex:(NSUInteger)idx1 withObjectAtIndex:(NSUInteger)idx2;
//移除所有的数组数据
- (void)removeAllObjects;
//移除指定区域对象
- (void)removeObject:(ObjectType)anObject inRange:(NSRange)range;
//移除指定对象
- (void)removeObject:(ObjectType)anObject;
//移除指定区域对象
- (void)removeObjectIdenticalTo:(ObjectType)anObject inRange:(NSRange)range;
//移除指定对象
- (void)removeObjectIdenticalTo:(ObjectType)anObject;
//移除指定索引之间的对象
- (void)removeObjectsFromIndices:(NSUInteger *)indices numIndices:(NSUInteger)cnt NS_DEPRECATED(10_0, 10_6, 2_0, 4_0);
//移除数组A包含的指定数组B的元素
- (void)removeObjectsInArray:(NSArray<ObjectType> *)otherArray;
//移除指定区域所有对象
- (void)removeObjectsInRange:(NSRange)range;
//指定数组B的指定区域的元素替换为数组A指定区域元素
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(NSArray<ObjectType> *)otherArray range:(NSRange)otherRange;
//指定数组B替换数组A指定区域的元素
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(NSArray<ObjectType> *)otherArray;
//Sets the receiving array’s elements to those in another given array.
//重置数组
- (void)setArray:(NSArray<ObjectType> *)otherArray;
//指定方法升序比较
- (void)sortUsingFunction:(NSInteger (NS_NOESCAPE *)(ObjectType,  ObjectType, void * _Nullable))compare context:(nullable void *)context;
//指定方法升序比较
- (void)sortUsingSelector:(SEL)comparator;
//指定索引集合插入数组元素
- (void)insertObjects:(NSArray<ObjectType> *)objects atIndexes:(NSIndexSet *)indexes;
//移除指定索引集合元素
- (void)removeObjectsAtIndexes:(NSIndexSet *)indexes;
//替换指定索引集合的数组元素
- (void)replaceObjectsAtIndexes:(NSIndexSet *)indexes withObjects:(NSArray<ObjectType> *)objects;
//指定索引替换新的数组元素
- (void)setObject:(ObjectType)obj atIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);
//指定块方法排序数组元素
- (void)sortUsingComparator:(NSComparator NS_NOESCAPE)cmptr NS_AVAILABLE(10_6, 4_0);
//指定块比较数组
- (void)sortWithOptions:(NSSortOptions)opts usingComparator:(NSComparator NS_NOESCAPE)cmptr NS_AVAILABLE(10_6, 4_0);

@end

@interface NSMutableArray<ObjectType> (NSMutableArrayCreation)
//初始化数组并指定对象容量
+ (instancetype)arrayWithCapacity:(NSUInteger)numItems;
//指定路径文件加载数据
+ (nullable NSMutableArray<ObjectType> *)arrayWithContentsOfFile:(NSString *)path;
//指定URL加载数据
+ (nullable NSMutableArray<ObjectType> *)arrayWithContentsOfURL:(NSURL *)url;
- (nullable NSMutableArray<ObjectType> *)initWithContentsOfFile:(NSString *)path;
- (nullable NSMutableArray<ObjectType> *)initWithContentsOfURL:(NSURL *)url;

@end

NS_ASSUME_NONNULL_END
