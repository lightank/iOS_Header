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

#ifndef _OBJC_MESSAGE_H
#define _OBJC_MESSAGE_H

#pragma GCC system_header

#include <objc/objc.h>
#include <objc/runtime.h>

#pragma GCC system_header

#ifndef OBJC_SUPER
#define OBJC_SUPER

/// Specifies the superclass of an instance.
///指定实例的父类。
struct objc_super {
    /// Specifies an instance of a class.
    ///指定一个类的实例。
    __unsafe_unretained id receiver;
    
    /// Specifies the particular superclass of the instance to message.
    ///指定实例的特定父类消息。
#if !defined(__cplusplus)  &&  !__OBJC2__
    /* For compatibility with old objc-runtime.h header */
    /* 为了兼容旧的objc-runtime.h标头 */
    __unsafe_unretained Class class;
#else
    __unsafe_unretained Class super_class;
#endif
    /* super_class is the first class to search */
    /* super_class是第一个要搜索的类 */
};
#endif


/* Basic Messaging Primitives
 *
 * On some architectures, use objc_msgSend_stret for some struct return types.
 * On some architectures, use objc_msgSend_fpret for some float return types.
 * On some architectures, use objc_msgSend_fp2ret for some float return types.
 *
 * These functions must be cast to an appropriate function pointer type
 * before being called.
 */
/*基本信息原语
 *
 *在某些体系结构中，对于某些struct返回类型，请使用objc_msgSend_stret。
 *在某些体系结构中，对于某些浮点型返回类型，请使用objc_msgSend_fpret。
 *在某些架构上，对于某些浮点型返回类型，请使用objc_msgSend_fp2ret。
 *
 *这些函数必须被转换为适当的函数指针类型
 *被调用前。
 */
#if !OBJC_OLD_DISPATCH_PROTOTYPES
OBJC_EXPORT void objc_msgSend(void /* id self, SEL op, ... */ )
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);
OBJC_EXPORT void objc_msgSendSuper(void /* struct objc_super *super, SEL op, ... */ )
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);
#else
/**
 * Sends a message with a simple return value to an instance of a class.
 *
 * @param self A pointer to the instance of the class that is to receive the message.
 * @param op The selector of the method that handles the message.
 * @param ...
 *   A variable argument list containing the arguments to the method.
 *
 * @return The return value of the method.
 *
 * @note When it encounters a method call, the compiler generates a call to one of the
 *  functions \c objc_msgSend, \c objc_msgSend_stret, \c objc_msgSendSuper, or \c objc_msgSendSuper_stret.
 *  Messages sent to an object’s superclass (using the \c super keyword) are sent using \c objc_msgSendSuper;
 *  other messages are sent using \c objc_msgSend. Methods that have data structures as return values
 *  are sent using \c objc_msgSendSuper_stret and \c objc_msgSend_stret.
 */
/**
 *向类的实例发送一个简单返回值的消息。
 *
 * @param self指向要接收消息的类的实例的指针。
 * @param op处理消息的方法的选择器。
 * @param ...
 *包含方法参数的变量参数列表。
 *
 * @return方法的返回值。
 *
 * @note当遇到方法调用时，编译器会生成一个调用
 *函数\ c objc_msgSend，\ c objc_msgSend_stret，\ c objc_msgSendSuper或\ c objc_msgSendSuper_stret。
 *使用\ c objc_msgSendSuper发送发送到对象的超类的消息（使用\ c super关键字）
 *其他消息使用\ c objc_msgSend发送。具有数据结构作为返回值的方法
 *使用\ c objc_msgSendSuper_stret和\ c objc_msgSend_stret发送。
 */
OBJC_EXPORT id objc_msgSend(id self, SEL op, ...)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);
/**
 * Sends a message with a simple return value to the superclass of an instance of a class.
 *
 * @param super A pointer to an \c objc_super data structure. Pass values identifying the
 *  context the message was sent to, including the instance of the class that is to receive the
 *  message and the superclass at which to start searching for the method implementation.
 * @param op A pointer of type SEL. Pass the selector of the method that will handle the message.
 * @param ...
 *   A variable argument list containing the arguments to the method.
 *
 * @return The return value of the method identified by \e op.
 *
 * @see objc_msgSend
 */
/**
 *发送一个简单返回值的消息到类的实例的超类。
 *
 * @param super指向\ c objc_super数据结构的指针。通过值标识
 *发送消息的上下文，包括要接收的类的实例
 *消息和开始搜索方法实现的超类。
 * @param op类型为SEL的指针。传递处理消息的方法的选择器。
 * @param ...
 *包含方法参数的变量参数列表。
 *
 * @return由\ e op标识的方法的返回值。
 *
 * @see objc_msg发送
 */
OBJC_EXPORT id objc_msgSendSuper(struct objc_super *super, SEL op, ...)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);
#endif


/* Struct-returning Messaging Primitives
 *
 * Use these functions to call methods that return structs on the stack.
 * On some architectures, some structures are returned in registers.
 * Consult your local function call ABI documentation for details.
 *
 * These functions must be cast to an appropriate function pointer type
 * before being called.
 */
/*结构化返回信息原语
 *
 *使用这些函数调用在堆栈上返回结构体的方法。
 *在一些架构上，一些结构在寄存器中返回。
 *有关详细信息，请参阅本地函数调用ABI文档。
 *
 *这些函数必须被转换为适当的函数指针类型
 *被调用前。
 */
#if !OBJC_OLD_DISPATCH_PROTOTYPES
OBJC_EXPORT void objc_msgSend_stret(void /* id self, SEL op, ... */ )
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0)
OBJC_ARM64_UNAVAILABLE;
OBJC_EXPORT void objc_msgSendSuper_stret(void /* struct objc_super *super, SEL op, ... */ )
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0)
OBJC_ARM64_UNAVAILABLE;
#else
/**
 * Sends a message with a data-structure return value to an instance of a class.
 *
 * @see objc_msgSend
 */
/**
 *将数据结构返回值的消息发送到类的实例。
 *
 * @see objc_msg发送
 */
OBJC_EXPORT void objc_msgSend_stret(id self, SEL op, ...)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0)
OBJC_ARM64_UNAVAILABLE;

/**
 * Sends a message with a data-structure return value to the superclass of an instance of a class.
 *
 * @see objc_msgSendSuper
 */
/**
 *将数据结构返回值的消息发送到类的实例的超类。
 *
 * @see objc_msgSendSuper
 */
OBJC_EXPORT void objc_msgSendSuper_stret(struct objc_super *super, SEL op, ...)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0)
OBJC_ARM64_UNAVAILABLE;
#endif


/* Floating-point-returning Messaging Primitives
 *
 * Use these functions to call methods that return floating-point values
 * on the stack.
 * Consult your local function call ABI documentation for details.
 *
 * arm:    objc_msgSend_fpret not used
 * i386:   objc_msgSend_fpret used for `float`, `double`, `long double`.
 * x86-64: objc_msgSend_fpret used for `long double`.
 *
 * arm:    objc_msgSend_fp2ret not used
 * i386:   objc_msgSend_fp2ret not used
 * x86-64: objc_msgSend_fp2ret used for `_Complex long double`.
 *
 * These functions must be cast to an appropriate function pointer type
 * before being called.
 */
/*浮点返回信息原语
 *
 *使用这些函数调用返回浮点值的方法
 *堆叠。
 *有关详细信息，请参阅本地函数调用ABI文档。
 *
 * arm：objc_msgSend_fpret未使用
 * i386：objc_msgSend_fpret用于“float”，“double”，“long double”。
 * x86-64：objc_msgSend_fpret用于`long double`。
 *
 * arm：objc_msgSend_fp2ret未使用
 * i386：objc_msgSend_fp2ret未使用
 * x86-64：objc_msgSend_fp2ret用于`_Complex long double`。
 *
 *这些函数必须被转换为适当的函数指针类型
 *被叫前。
 */
#if !OBJC_OLD_DISPATCH_PROTOTYPES

# if defined(__i386__)

OBJC_EXPORT void objc_msgSend_fpret(void /* id self, SEL op, ... */ )
OBJC_AVAILABLE(10.4, 2.0, 9.0, 1.0);

# elif defined(__x86_64__)

OBJC_EXPORT void objc_msgSend_fpret(void /* id self, SEL op, ... */ )
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);
OBJC_EXPORT void objc_msgSend_fp2ret(void /* id self, SEL op, ... */ )
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

# endif

// !OBJC_OLD_DISPATCH_PROTOTYPES
#else
// OBJC_OLD_DISPATCH_PROTOTYPES
# if defined(__i386__)

/**
 * Sends a message with a floating-point return value to an instance of a class.
 *
 * @see objc_msgSend
 * @note On the i386 platform, the ABI for functions returning a floating-point value is
 *  incompatible with that for functions returning an integral type. On the i386 platform, therefore,
 *  you must use \c objc_msgSend_fpret for functions returning non-integral type. For \c float or
 *  \c long \c double return types, cast the function to an appropriate function pointer type first.
 */
/**
 *向类的实例发送带有浮点返回值的消息。
 *
 * @see objc_msg发送
 * @note在i386平台上，返回浮点值的函数的ABI为
 *与返回整数类型的函数不兼容。因此，在i386平台上，
 *必须对返回非整数类型的函数使用\ c objc_msgSend_fpret。对于\ c float或
 * \ c long \ c double返回类型，首先将函数转换为适当的函数指针类型。
 */
OBJC_EXPORT double objc_msgSend_fpret(id self, SEL op, ...)
OBJC_AVAILABLE(10.4, 2.0, 9.0, 1.0);

/* Use objc_msgSendSuper() for fp-returning messages to super. */
/* See also objc_msgSendv_fpret() below. */
/*使用objc_msgSendSuper（）将fp返回消息到超级。 */
/*另请参见下面的objc_msgSendv_fpret（）。 */
# elif defined(__x86_64__)
/**
 * Sends a message with a floating-point return value to an instance of a class.
 *
 * @see objc_msgSend
 */
/**
 *向类的实例发送带有浮点返回值的消息。
 *
 * @see objc_msg发送
 */
OBJC_EXPORT long double objc_msgSend_fpret(id self, SEL op, ...)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

#  if __STDC_VERSION__ >= 199901L
OBJC_EXPORT _Complex long double objc_msgSend_fp2ret(id self, SEL op, ...)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);
#  else
OBJC_EXPORT void objc_msgSend_fp2ret(id self, SEL op, ...)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);
#  endif

/* Use objc_msgSendSuper() for fp-returning messages to super. */
/* See also objc_msgSendv_fpret() below. */
/*使用objc_msgSendSuper（）将fp返回消息到超级。 */
/*另请参见下面的objc_msgSendv_fpret（）。 */
# endif

// OBJC_OLD_DISPATCH_PROTOTYPES
#endif


/* Direct Method Invocation Primitives
 * Use these functions to call the implementation of a given Method.
 * This is faster than calling method_getImplementation() and method_getName().
 *
 * The receiver must not be nil.
 *
 * These functions must be cast to an appropriate function pointer type
 * before being called.
 */
/*直接方法调用原语
 *使用这些函数调用给定方法的实现。
 *这比调用method_getImplementation（）和method_getName（）要快。
 *
 *接收机不能为零。
 *
 *这些函数必须被转换为适当的函数指针类型
 *被调用前。
 */
#if !OBJC_OLD_DISPATCH_PROTOTYPES
OBJC_EXPORT void method_invoke(void /* id receiver, Method m, ... */ )
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);
OBJC_EXPORT void method_invoke_stret(void /* id receiver, Method m, ... */ )
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0)
OBJC_ARM64_UNAVAILABLE;
#else
OBJC_EXPORT id method_invoke(id receiver, Method m, ...)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);
OBJC_EXPORT void method_invoke_stret(id receiver, Method m, ...)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0)
OBJC_ARM64_UNAVAILABLE;
#endif


/* Message Forwarding Primitives
 * Use these functions to forward a message as if the receiver did not
 * respond to it.
 *
 * The receiver must not be nil.
 *
 * class_getMethodImplementation() may return (IMP)_objc_msgForward.
 * class_getMethodImplementation_stret() may return (IMP)_objc_msgForward_stret
 *
 * These functions must be cast to an appropriate function pointer type
 * before being called.
 *
 * Before Mac OS X 10.6, _objc_msgForward must not be called directly
 * but may be compared to other IMP values.
 */
/*消息转发原语
 *使用这些功能转发消息，就好像接收方没有
 *回应
 *
 *接收机不能为零。
 *
 * class_getMethodImplementation（）可能返回（IMP）_objc_msgForward。
 * class_getMethodImplementation_stret（）可能返回（IMP）_objc_msgForward_stret
 *
 *这些函数必须被转换为适当的函数指针类型
 *被叫前。
 *
 *在Mac OS X 10.6之前，不能直接调用_objc_msgForward
 *但可以与其他IMP值进行比较。
 */
#if !OBJC_OLD_DISPATCH_PROTOTYPES
OBJC_EXPORT void _objc_msgForward(void /* id receiver, SEL sel, ... */ )
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);
OBJC_EXPORT void _objc_msgForward_stret(void /* id receiver, SEL sel, ... */ )
OBJC_AVAILABLE(10.6, 3.0, 9.0, 1.0)
OBJC_ARM64_UNAVAILABLE;
#else
OBJC_EXPORT id _objc_msgForward(id receiver, SEL sel, ...)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);
OBJC_EXPORT void _objc_msgForward_stret(id receiver, SEL sel, ...)
OBJC_AVAILABLE(10.6, 3.0, 9.0, 1.0)
OBJC_ARM64_UNAVAILABLE;
#endif


/* Variable-argument Messaging Primitives
 *
 * Use these functions to call methods with a list of arguments, such
 * as the one passed to forward:: .
 *
 * The contents of the argument list are architecture-specific.
 * Consult your local function call ABI documentation for details.
 *
 * These functions must be cast to an appropriate function pointer type
 * before being called, except for objc_msgSendv_stret() which must not
 * be cast to a struct-returning type.
 */
/*可变参数消息传递原语
 *
 *使用这些函数调用具有参数列表的方法
 *作为一个传递到前进::。
 *
 *参数列表的内容是架构特定的。
 *有关详细信息，请参阅本地函数调用ABI文档。
 *
 *这些函数必须被转换为适当的函数指针类型
 *在被调用之前，除了objc_msgSendv_stret（）不能
 *被转换为结构返回类型。
 */
typedef void* marg_list;

OBJC_EXPORT id objc_msgSendv(id self, SEL op, size_t arg_size, marg_list arg_frame) OBJC2_UNAVAILABLE;
OBJC_EXPORT void objc_msgSendv_stret(void *stretAddr, id self, SEL op, size_t arg_size, marg_list arg_frame) OBJC2_UNAVAILABLE;
/* Note that objc_msgSendv_stret() does not return a structure type,
 * and should not be cast to do so. This is unlike objc_msgSend_stret()
 * and objc_msgSendSuper_stret().
 */
/*请注意，objc_msgSendv_stret（）不返回结构类型，
 *，不应该这样做。这与objc_msgSend_stret（）不同
 *和objc_msgSendSuper_stret（）。
 */
#if defined(__i386__)
OBJC_EXPORT double objc_msgSendv_fpret(id self, SEL op, unsigned arg_size, marg_list arg_frame) OBJC2_UNAVAILABLE;
#endif


/* The following marg_list macros are of marginal utility. They
 * are included for compatibility with the old objc-class.h header. */
/*以下的marg_list宏具有边际效用。他们
 *包含与旧的objc-class.h头兼容。 */
#if !__OBJC2__

#define marg_prearg_size	0

#define marg_malloc(margs, method) \
do { \
margs = (marg_list *)malloc (marg_prearg_size + ((7 + method_getSizeOfArguments(method)) & ~7)); \
} while (0)

#define marg_free(margs) \
do { \
free(margs); \
} while (0)

#define marg_adjustedOffset(method, offset) \
(marg_prearg_size + offset)

#define marg_getRef(margs, offset, type) \
( (type *)((char *)margs + marg_adjustedOffset(method,offset) ) )

#define marg_getValue(margs, offset, type) \
( *marg_getRef(margs, offset, type) )

#define marg_setValue(margs, offset, type, value) \
( marg_getValue(margs, offset, type) = (value) )

#endif

#endif
