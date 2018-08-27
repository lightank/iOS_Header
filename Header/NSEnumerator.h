/*	NSEnumerator.h
	Copyright (c) 1995-2016, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>;

NS_ASSUME_NONNULL_BEGIN

/*
 * The fast enumeration protocol NSFastEnumeration is adopted and
 * implemented by objects wishing to make use of a fast and safe
 * enumeration style.  The language "foreach" construct then can
 * be used with such objects.
 *
 * The abstract class NSEnumerator itself is taught how to do this
 * for convenience by using -nextObject to return items one at a time.
 */

typedef struct {
    unsigned long state;
    id __unsafe_unretained _Nullable * _Nullable itemsPtr;
    unsigned long * _Nullable mutationsPtr;
    unsigned long extra[5];
} NSFastEnumerationState;

@protocol NSFastEnumeration
//Returns by reference a C array of objects over which the sender should iterate, and as the return value the number of objects in the array.
/**
 <#Description#>

 @param state Context information that is used in the enumeration to, in addition to other possibilities, ensure that the collection has not been mutated.

 @param buffer A C array of objects over which the sender is to iterate.

 @param len The maximum number of objects to return in stackbuf.

 @return The number of objects returned in stackbuf. Returns 0 when the iteration is finished.
 
 */
- (NSUInteger)countByEnumeratingWithState:(NSFastEnumerationState *)state objects:(id __unsafe_unretained _Nullable [_Nonnull])buffer count:(NSUInteger)len;

@end
//迭代器
@interface NSEnumerator<ObjectType> : NSObject <NSFastEnumeration>
//下个元素
- (nullable ObjectType)nextObject;

@end

@interface NSEnumerator<ObjectType> (NSExtendedEnumerator)
//迭代器中所有元素
@property (readonly, copy) NSArray<ObjectType> *allObjects;

@end

NS_ASSUME_NONNULL_END
