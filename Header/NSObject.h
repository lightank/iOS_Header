/*	NSObject.h
	Copyright (c) 1994-2016, Apple Inc. All rights reserved.
 */

#include <TargetConditionals.h>
#import <objc/NSObject.h>
#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSZone.h>

@class NSInvocation, NSMethodSignature, NSCoder, NSString, NSEnumerator;
@class Protocol;

NS_ASSUME_NONNULL_BEGIN

/***************	Basic protocols		***************/

@protocol NSCopying

- (id)copyWithZone:(nullable NSZone *)zone;

@end

@protocol NSMutableCopying

- (id)mutableCopyWithZone:(nullable NSZone *)zone;

@end

@protocol NSCoding

- (void)encodeWithCoder:(NSCoder *)aCoder;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder; // NS_DESIGNATED_INITIALIZER

@end

// Objects which are safe to be encoded and decoded across privilege boundaries should adopt NSSecureCoding instead of NSCoding. Secure coders (those that respond YES to requiresSecureCoding) will only encode objects that adopt the NSSecureCoding protocol.
// NOTE: NSSecureCoding guarantees only that an archive contains the classes it claims. It makes no guarantees about the suitability for consumption by the receiver of the decoded content of the archive. Archived objects which  may trigger code evaluation should be validated independently by the consumer of the objects to verify that no malicious code is executed (i.e. by checking key paths, selectors etc. specified in the archive).

@protocol NSSecureCoding <NSCoding>
@required
// This property must return YES on all classes that allow secure coding. Subclasses of classes that adopt NSSecureCoding and override initWithCoder: must also override this method and return YES.
// The Secure Coding Guide should be consulted when writing methods that decode data.
#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
@property (class, readonly) BOOL supportsSecureCoding;
#else
+ (BOOL)supportsSecureCoding;
#endif
@end

/***********	Base class		***********/

@interface NSObject (NSCoderMethods)
/*
 Returns the version number assigned to the class.If no version has been set, the default is 0.

 Version numbers are needed for decoding or unarchiving, so older versions of an object can be detected and decoded correctly.
 
 Caution should be taken when obtaining the version from within an NSCoding protocol or other methods. Use the class name explicitly when getting a class version number:
 
 version = [MyClass version];
 Don’t simply send version to the return value of class—a subclass version number may be returned instead.
 
 Special Considerations
 The version number applies to NSArchiver/NSUnarchiver, but not to NSKeyedArchiver/NSKeyedUnarchiver. A keyed archiver does not encode class version numbers.
 */
+ (NSInteger)version;
+ (void)setVersion:(NSInteger)aVersion;
//Overridden by subclasses to substitute a class other than its own during coding. (read-only)
//被子类重写在序列化coding中代替自己的类
@property (readonly) Class classForCoder;
//Overridden by subclasses to substitute another object for itself during encoding.
//被子类重写在序列化coding中代替自己的对象
- (nullable id)replacementObjectForCoder:(NSCoder *)aCoder;
//Overridden by subclasses to substitute another object in place of the object that was decoded and subsequently received this message.
//被子类重写去代替另一个对象在一个对象被decoded和随后接收这条消息
- (nullable id)awakeAfterUsingCoder:(NSCoder *)aDecoder NS_REPLACES_RECEIVER;

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
@interface NSObject (NSDeprecatedMethods)

+ (void)poseAsClass:(Class)aClass NS_DEPRECATED(10_0, 10_5, 2_0, 2_0)
#if __OBJC2__
UNAVAILABLE_ATTRIBUTE
#endif
;

@end
#endif


/***********	Discardable Content		***********/

@protocol NSDiscardableContent
@required
- (BOOL)beginContentAccess;
- (void)endContentAccess;
- (void)discardContentIfPossible;
- (BOOL)isContentDiscarded;
@end

@interface NSObject (NSDiscardableContentProxy)
@property (readonly, retain) id autoContentAccessingProxy NS_AVAILABLE(10_6, 4_0);
@end

/***********	Object Allocation / Deallocation		*******/

FOUNDATION_EXPORT id NSAllocateObject(Class aClass, NSUInteger extraBytes, NSZone * _Nullable zone) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT void NSDeallocateObject(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT id NSCopyObject(id object, NSUInteger extraBytes, NSZone * _Nullable zone) NS_AUTOMATED_REFCOUNT_UNAVAILABLE NS_DEPRECATED(10_0, 10_8, 2_0, 6_0);

FOUNDATION_EXPORT BOOL NSShouldRetainWithZone(id anObject, NSZone * _Nullable requestedZone) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT void NSIncrementExtraRefCount(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT BOOL NSDecrementExtraRefCountWasZero(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT NSUInteger NSExtraRefCount(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

#if __has_feature(objc_arc)

// After using a CFBridgingRetain on an NSObject, the caller must take responsibility for calling CFRelease at an appropriate time.
NS_INLINE CF_RETURNS_RETAINED CFTypeRef _Nullable CFBridgingRetain(id _Nullable X) {
    return (__bridge_retained CFTypeRef)X;
}

NS_INLINE id _Nullable CFBridgingRelease(CFTypeRef CF_CONSUMED _Nullable X) {
    return (__bridge_transfer id)X;
}

#else

// This function is intended for use while converting to ARC mode only.
NS_INLINE CF_RETURNS_RETAINED CFTypeRef _Nullable CFBridgingRetain(id _Nullable X) {
    return X ? CFRetain((CFTypeRef)X) : NULL;
}

// This function is intended for use while converting to ARC mode only.
NS_INLINE id _Nullable CFBridgingRelease(CFTypeRef CF_CONSUMED _Nullable X) {
    return [(id)CFMakeCollectable(X) autorelease];
}

#endif

NS_ASSUME_NONNULL_END
