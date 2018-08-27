/*
 * Copyright (c) 1999-2007 Apple Inc.  All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 *	objc.h
 *	Copyright 1988-1996, NeXT Software, Inc.
 */

#ifndef _OBJC_OBJC_H_
#define _OBJC_OBJC_H_

#include <sys/types.h>      // for __DARWIN_NULL
#include <Availability.h>
#include <objc/objc-api.h>
#include <stdbool.h>

#if !OBJC_TYPES_DEFINED
/// An opaque type that represents an Objective-C class.
///表示Objective-C类的不透明类型。
typedef struct objc_class *Class;

/// Represents an instance of a class.
///表示类的一个实例。
struct objc_object {
    Class isa  OBJC_ISA_AVAILABILITY;
};

/// A pointer to an instance of a class.
///指向类的实例的指针。
typedef struct objc_object *id;
#endif

/// An opaque type that represents a method selector.
///表示方法选择器的不透明类型。
typedef struct objc_selector *SEL;

/// A pointer to the function of a method implementation.
///指向方法实现的函数的指针。
#if !OBJC_OLD_DISPATCH_PROTOTYPES
typedef void (*IMP)(void /* id, SEL, ... */ );
#else
typedef id (*IMP)(id, SEL, ...);
#endif

/// Type to represent a boolean value.
///键入以表示布尔值。

#if defined(__OBJC_BOOL_IS_BOOL)
// Honor __OBJC_BOOL_IS_BOOL when available.
//荣誉__OBJC_BOOL_IS_BOOL当其可用时
#   if __OBJC_BOOL_IS_BOOL
#       define OBJC_BOOL_IS_BOOL 1
#   else
#       define OBJC_BOOL_IS_BOOL 0
#   endif
#else
// __OBJC_BOOL_IS_BOOL not set.
// __OBJC_BOOL_IS_BOOL未设置。
#   if TARGET_OS_OSX || (TARGET_OS_IOS && !__LP64__ && !__ARM_ARCH_7K)
#      define OBJC_BOOL_IS_BOOL 0
#   else
#      define OBJC_BOOL_IS_BOOL 1
#   endif
#endif

#if OBJC_BOOL_IS_BOOL
typedef bool BOOL;
#else
#   define OBJC_BOOL_IS_CHAR 1
typedef signed char BOOL;
// BOOL is explicitly signed so @encode(BOOL) == "c" rather than "C"
// even if -funsigned-char is used.
// BOOL被明确地签名，所以@encode（BOOL）==“c”而不是“C”
//即使使用-funsigned-char。
#endif

#define OBJC_BOOL_DEFINED

#if __has_feature(objc_bool)
#define YES __objc_yes
#define NO  __objc_no
#else
#define YES ((BOOL)1)
#define NO  ((BOOL)0)
#endif

#ifndef Nil
# if __has_feature(cxx_nullptr)
#   define Nil nullptr
# else
#   define Nil __DARWIN_NULL
# endif
#endif

#ifndef nil
# if __has_feature(cxx_nullptr)
#   define nil nullptr
# else
#   define nil __DARWIN_NULL
# endif
#endif

#ifndef __strong
# if !__has_feature(objc_arc)
#   define __strong /* empty */
# endif
#endif

#ifndef __unsafe_unretained
# if !__has_feature(objc_arc)
#   define __unsafe_unretained /* empty */
# endif
#endif

#ifndef __autoreleasing
# if !__has_feature(objc_arc)
#   define __autoreleasing /* empty */
# endif
#endif


/**
 * Returns the name of the method specified by a given selector.
 *
 * @param sel A pointer of type \c SEL. Pass the selector whose name you wish to determine.
 *
 * @return A C string indicating the name of the selector.
 */
/**
 *返回给定选择器指定的方法的名称。
 *
 * @param sel类型为\ c SEL的指针。通过您想要确定的名称的选择器。
 *
 * @return指示选择器名称的C字符串。
 */
OBJC_EXPORT const char *sel_getName(SEL sel)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/**
 * Registers a method with the Objective-C runtime system, maps the method
 * name to a selector, and returns the selector value.
 *
 * @param str A pointer to a C string. Pass the name of the method you wish to register.
 *
 * @return A pointer of type SEL specifying the selector for the named method.
 *
 * @note You must register a method name with the Objective-C runtime system to obtain the
 *  method’s selector before you can add the method to a class definition. If the method name
 *  has already been registered, this function simply returns the selector.
 */
/**
 *使用Objective-C运行时系统注册方法，映射方法
 *名称给选择器，并返回选择器值。
 *
 * @param str指向C字符串的指针。传递您要注册的方法的名称。
 *
 * @return类型为SEL的指针指定命名方法的选择器。
 *
 * @note您必须使用Objective-C运行时系统注册方法名称才能获取
 *方法的选择器，然后可以将方法添加到类定义。如果方法名称
 *已经被注册，这个功能只是返回选择器。
 */
OBJC_EXPORT SEL sel_registerName(const char *str)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/**
 * Returns the class name of a given object.
 *
 * @param obj An Objective-C object.
 *
 * @return The name of the class of which \e obj is an instance.
 */
/**
 *返回给定对象的类名。
 *
 * @param obj一个Objective-C对象。
 *
 * @return其中\ e obj是一个实例的类的名称。
 */
OBJC_EXPORT const char *object_getClassName(id obj)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/**
 * Returns a pointer to any extra bytes allocated with an instance given object.
 *
 * @param obj An Objective-C object.
 *
 * @return A pointer to any extra bytes allocated with \e obj. If \e obj was
 *   not allocated with any extra bytes, then dereferencing the returned pointer is undefined.
 *
 * @note This function returns a pointer to any extra bytes allocated with the instance
 *  (as specified by \c class_createInstance with extraBytes>0). This memory follows the
 *  object's ordinary ivars, but may not be adjacent to the last ivar.
 * @note The returned pointer is guaranteed to be pointer-size aligned, even if the area following
 *  the object's last ivar is less aligned than that. Alignment greater than pointer-size is never
 *  guaranteed, even if the area following the object's last ivar is more aligned than that.
 * @note In a garbage-collected environment, the memory is scanned conservatively.
 */
/**
 *返回指向分配给实例给对象的任何额外字节的指针。
 *
 * @param obj一个Objective-C对象。
 *
 * @return指向使用\ e obj分配的任何额外字节的指针。如果\ e obj是
 *未分配任何额外的字节，然后取消引用返回的指针是未定义的。
 *
 * @note此函数返回指向实例分配的任何额外字节的指针
 *（由\ c class_createInstance指定为extraBytes> 0）。这个记忆跟着
 *对象的普通ivars，但可能不会与最后一个ivar相邻。
 * @note返回的指针保证是指针大小对齐，即使以下区域
 *对象的最后一个ivar不太一致。大于指针大小的对齐方式从不
 *保证，即使对象的最后一个ivar之后的区域比对齐更多。
 * @note在垃圾回收的环境中，内存被保守扫描。
 */
OBJC_EXPORT void *object_getIndexedIvars(id obj)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0)
OBJC_ARC_UNAVAILABLE;

/**
 * Identifies a selector as being valid or invalid.
 *
 * @param sel The selector you want to identify.
 *
 * @return YES if selector is valid and has a function implementation, NO otherwise.
 *
 * @warning On some platforms, an invalid reference (to invalid memory addresses) can cause
 *  a crash.
 */
/**
 *将选择器标识为有效或无效。
 *
 * @param sel要标识的选择器。
 *
 * @return YES如果选择器有效并具有函数实现，否则否。
 *
 * @warning在某些平台上，无效的引用（对无效的内存地址）可能导致
 *崩溃
 */
OBJC_EXPORT BOOL sel_isMapped(SEL sel)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/**
 * Registers a method name with the Objective-C runtime system.
 *
 * @param str A pointer to a C string. Pass the name of the method you wish to register.
 *
 * @return A pointer of type SEL specifying the selector for the named method.
 *
 * @note The implementation of this method is identical to the implementation of \c sel_registerName.
 * @note Prior to OS X version 10.0, this method tried to find the selector mapped to the given name
 *  and returned \c NULL if the selector was not found. This was changed for safety, because it was
 *  observed that many of the callers of this function did not check the return value for \c NULL.
 */
/**
 *使用Objective-C运行时系统注册方法名称。
 *
 * @param str指向C字符串的指针。传递您要注册的方法的名称。
 *
 * @return类型为SEL的指针指定命名方法的选择器。
 *
 * @note此方法的实现与\ c sel_registerName的实现相同。
 * @note在OS X版本10.0之前，此方法尝试找到映射到给定名称的选择器
 *并返回\ c如果未找到选择器，则返回NULL。这是为了安全而改变的，因为它是
 *观察到，这个函数的很多调用者没有检查\ c NULL的返回值。
 */
OBJC_EXPORT SEL sel_getUid(const char *str)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

typedef const void* objc_objectptr_t;


// Obsolete ARC conversions.

OBJC_EXPORT id objc_retainedObject(objc_objectptr_t obj)
OBJC_UNAVAILABLE("use CFBridgingRelease() or a (__bridge_transfer id) cast instead");
OBJC_EXPORT id objc_unretainedObject(objc_objectptr_t obj)
OBJC_UNAVAILABLE("use a (__bridge id) cast instead");
OBJC_EXPORT objc_objectptr_t objc_unretainedPointer(id obj)
OBJC_UNAVAILABLE("use a __bridge cast instead");


#if !__OBJC2__

// The following declarations are provided here for source compatibility.
//此处提供以下声明，以获得源兼容性。

#if defined(__LP64__)
typedef long arith_t;
typedef unsigned long uarith_t;
#   define ARITH_SHIFT 32
#else
typedef int arith_t;
typedef unsigned uarith_t;
#   define ARITH_SHIFT 16
#endif

typedef char *STR;

#define ISSELECTOR(sel) sel_isMapped(sel)
#define SELNAME(sel)	sel_getName(sel)
#define SELUID(str)	sel_getUid(str)
#define NAMEOF(obj)     object_getClassName(obj)
#define IV(obj)         object_getIndexedIvars(obj)

#endif

#endif  /* _OBJC_OBJC_H_ */
