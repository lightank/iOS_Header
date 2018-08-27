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

#ifndef _OBJC_RUNTIME_H
#define _OBJC_RUNTIME_H

#include <objc/objc.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <Availability.h>
#include <TargetConditionals.h>

#if TARGET_OS_MAC
#include <sys/types.h>
#endif


/* Types */

#if !OBJC_TYPES_DEFINED

/// An opaque type that represents a method in a class definition.
///表示类定义中的方法的不透明类型。
typedef struct objc_method *Method;

/// An opaque type that represents an instance variable.
///表示实例变量的不透明类型。
typedef struct objc_ivar *Ivar;

/// An opaque type that represents a category.
///表示类别的不透明类型。
typedef struct objc_category *Category;

/// An opaque type that represents an Objective-C declared property.
///表示Objective-C声明属性的不透明类型。
typedef struct objc_property *objc_property_t;

struct objc_class {
    Class isa  OBJC_ISA_AVAILABILITY;
    
#if !__OBJC2__
    Class super_class                                        OBJC2_UNAVAILABLE;
    const char *name                                         OBJC2_UNAVAILABLE;
    long version                                             OBJC2_UNAVAILABLE;
    long info                                                OBJC2_UNAVAILABLE;
    long instance_size                                       OBJC2_UNAVAILABLE;
    struct objc_ivar_list *ivars                             OBJC2_UNAVAILABLE;
    struct objc_method_list **methodLists                    OBJC2_UNAVAILABLE;
    struct objc_cache *cache                                 OBJC2_UNAVAILABLE;
    struct objc_protocol_list *protocols                     OBJC2_UNAVAILABLE;
#endif
    
} OBJC2_UNAVAILABLE;
/* Use `Class` instead of `struct objc_class *` */
/*使用`Class`代替`struct objc_class *`*/

#endif

#ifdef __OBJC__
@class Protocol;
#else
typedef struct objc_object Protocol;
#endif

/// Defines a method
struct objc_method_description {
    /** <方法名称*/
    SEL name;               /**< The name of the method */
    /** <方法参数的类型*/
    char *types;            /**< The types of the method arguments */
};

/// Defines a property attribute
///定义属性属性
typedef struct {
     /** <属性的名称*/
    const char *name;           /**< The name of the attribute */
    /** <属性的值（通常为空）*/
    const char *value;          /**< The value of the attribute (usually empty) */
} objc_property_attribute_t;


/* Functions */

/* Working with Instances */

/**
 * Returns a copy of a given object.
 *
 * @param obj An Objective-C object.
 * @param size The size of the object \e obj.
 *
 * @return A copy of \e obj.
 */
/* 功能 */

/*使用实例*/

/**
 *返回给定对象的副本。
 *
 * @param obj一个Objective-C对象。
 * @param size对象的大小\ e obj。
 *
 * @return \ e obj的副本。
 */
OBJC_EXPORT id object_copy(id obj, size_t size)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0)
OBJC_ARC_UNAVAILABLE;

/**
 * Frees the memory occupied by a given object.
 *
 * @param obj An Objective-C object.
 *
 * @return nil
 */
/**
 *释放给定对象占用的内存。
 *
 * @param obj一个Objective-C对象。
 *
 * @返回零
 */
OBJC_EXPORT id object_dispose(id obj)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0)
OBJC_ARC_UNAVAILABLE;

/**
 * Returns the class of an object.
 *
 * @param obj The object you want to inspect.
 *
 * @return The class object of which \e object is an instance,
 *  or \c Nil if \e object is \c nil.
 */
/**
 *返回对象的类。
 *
 * @param obj要检查的对象。
 *
 * @return其中\ e对象是一个实例的类对象，
 *或\ c如果\ e对象为\ c，则为零。
 */
OBJC_EXPORT Class object_getClass(id obj)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Sets the class of an object.
 *
 * @param obj The object to modify.
 * @param cls A class object.
 *
 * @return The previous value of \e object's class, or \c Nil if \e object is \c nil.
 */
/**
 *设置对象的类。
 *
 * @param obj要修改的对象。
 * @param cls一个类对象。
 *
 * @return \ e对象的类的前一个值，或\ c如果\ e对象为\ c，则为零。
 */
OBJC_EXPORT Class object_setClass(id obj, Class cls)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);


/**
 * Returns whether an object is a class object.
 *
 * @param obj An Objective-C object.
 *
 * @return true if the object is a class or metaclass, false otherwise.
 */
/**
 *返回对象是否是类对象。
 *
 * @param obj一个Objective-C对象。
 *
 *如果对象是类或元类，返回true，否则返回false。
 */
OBJC_EXPORT BOOL object_isClass(id obj)
OBJC_AVAILABLE(10.10, 8.0, 9.0, 1.0);


/**
 * Reads the value of an instance variable in an object.
 *
 * @param obj The object containing the instance variable whose value you want to read.
 * @param ivar The Ivar describing the instance variable whose value you want to read.
 *
 * @return The value of the instance variable specified by \e ivar, or \c nil if \e object is \c nil.
 *
 * @note \c object_getIvar is faster than \c object_getInstanceVariable if the Ivar
 *  for the instance variable is already known.
 */
/**
 *读取对象中的实例变量的值。
 *
 * @param obj包含要读取其值的实例变量的对象。
 * @param ivar描述要读取其值的实例变量的Ivar。
 *
 * @return由\ e ivar指定的实例变量的值，如果\ e对象为\ c，则为\ c nil。
 *
 * @note \ c object_getIvar比\ c object_getInstanceVariable要快，如果Ivar
 *为实例变量已知。
 */
OBJC_EXPORT id object_getIvar(id obj, Ivar ivar)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Sets the value of an instance variable in an object.
 *
 * @param obj The object containing the instance variable whose value you want to set.
 * @param ivar The Ivar describing the instance variable whose value you want to set.
 * @param value The new value for the instance variable.
 *
 * @note Instance variables with known memory management (such as ARC strong and weak)
 *  use that memory management. Instance variables with unknown memory management
 *  are assigned as if they were unsafe_unretained.
 * @note \c object_setIvar is faster than \c object_setInstanceVariable if the Ivar
 *  for the instance variable is already known.
 */
/**
 *设置对象中实例变量的值。
 *
 * @param obj包含要设置其值的实例变量的对象。
 * @param ivar描述要设置其值的实例变量的Ivar。
 * @param value实例变量的新值。
 *
 * @note具有已知内存管理的实例变量（如ARC强弱）
 *使用内存管理。具有未知内存管理的实例变量
 *被分配好像他们是不安全的。
 * @note \ c object_setIvar比\ c object_setInstanceVariable要快，如果Ivar
 *为实例变量已知。
 */
OBJC_EXPORT void object_setIvar(id obj, Ivar ivar, id value)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Sets the value of an instance variable in an object.
 *
 * @param obj The object containing the instance variable whose value you want to set.
 * @param ivar The Ivar describing the instance variable whose value you want to set.
 * @param value The new value for the instance variable.
 *
 * @note Instance variables with known memory management (such as ARC strong and weak)
 *  use that memory management. Instance variables with unknown memory management
 *  are assigned as if they were strong.
 * @note \c object_setIvar is faster than \c object_setInstanceVariable if the Ivar
 *  for the instance variable is already known.
 */
/**
 *设置对象中实例变量的值。
 *
 * @param obj包含要设置其值的实例变量的对象。
 * @param ivar描述要设置其值的实例变量的Ivar。
 * @param value实例变量的新值。
 *
 * @note具有已知内存管理的实例变量（如ARC强弱）
 *使用内存管理。具有未知内存管理的实例变量
 *被分配好像强壮一样。
 * @note \ c object_setIvar比\ c object_setInstanceVariable要快，如果Ivar
 *为实例变量已知。
 */
OBJC_EXPORT void object_setIvarWithStrongDefault(id obj, Ivar ivar, id value)
OBJC_AVAILABLE(10.12, 10.0, 10.0, 3.0);

/**
 * Changes the value of an instance variable of a class instance.
 *
 * @param obj A pointer to an instance of a class. Pass the object containing
 *  the instance variable whose value you wish to modify.
 * @param name A C string. Pass the name of the instance variable whose value you wish to modify.
 * @param value The new value for the instance variable.
 *
 * @return A pointer to the \c Ivar data structure that defines the type and
 *  name of the instance variable specified by \e name.
 *
 * @note Instance variables with known memory management (such as ARC strong and weak)
 *  use that memory management. Instance variables with unknown memory management
 *  are assigned as if they were unsafe_unretained.
 */
/**
 *更改类实例的实例变量的值。
 *
 * @param obj指向类的实例的指针。传递包含的对象
 *要修改其值的实例变量。
 * @param name一个C字符串。传递要修改其值的实例变量的名称。
 * @param value实例变量的新值。
 *
 * @return指向定义类型的\ c Ivar数据结构的指针
 *由\ e名称指定的实例变量的名称。
 *
 * @note具有已知内存管理的实例变量（如ARC强弱）
 *使用内存管理。具有未知内存管理的实例变量
 *被分配好像他们是不安全的。
 */
OBJC_EXPORT Ivar object_setInstanceVariable(id obj, const char *name, void *value)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0)
OBJC_ARC_UNAVAILABLE;

/**
 * Changes the value of an instance variable of a class instance.
 *
 * @param obj A pointer to an instance of a class. Pass the object containing
 *  the instance variable whose value you wish to modify.
 * @param name A C string. Pass the name of the instance variable whose value you wish to modify.
 * @param value The new value for the instance variable.
 *
 * @return A pointer to the \c Ivar data structure that defines the type and
 *  name of the instance variable specified by \e name.
 *
 * @note Instance variables with known memory management (such as ARC strong and weak)
 *  use that memory management. Instance variables with unknown memory management
 *  are assigned as if they were strong.
 */
/**
 *更改类实例的实例变量的值。
 *
 * @param obj指向类的实例的指针。传递包含的对象
 *要修改其值的实例变量。
 * @param name一个C字符串。传递要修改其值的实例变量的名称。
 * @param value实例变量的新值。
 *
 * @return指向定义类型的\ c Ivar数据结构的指针
 *由\ e名称指定的实例变量的名称。
 *
 * @note具有已知内存管理的实例变量（如ARC强弱）
 *使用内存管理。具有未知内存管理的实例变量
 *被分配好像强壮一样。
 */
OBJC_EXPORT Ivar object_setInstanceVariableWithStrongDefault(id obj, const char *name, void *value)
OBJC_AVAILABLE(10.12, 10.0, 10.0, 3.0)
OBJC_ARC_UNAVAILABLE;

/**
 * Obtains the value of an instance variable of a class instance.
 *
 * @param obj A pointer to an instance of a class. Pass the object containing
 *  the instance variable whose value you wish to obtain.
 * @param name A C string. Pass the name of the instance variable whose value you wish to obtain.
 * @param outValue On return, contains a pointer to the value of the instance variable.
 *
 * @return A pointer to the \c Ivar data structure that defines the type and name of
 *  the instance variable specified by \e name.
 */
/**
 获取类实例的实例变量的值。
 *
 * @param obj指向类的实例的指针。传递包含的对象
 *要获取其值的实例变量。
 * @param name一个C字符串。传递要获取其值的实例变量的名称。
 * @param outValue返回时，包含一个指向实例变量值的指针。
 *
 * @return指向定义类型和名称的\ c Ivar数据结构的指针
 *由\ e名称指定的实例变量。
 */
OBJC_EXPORT Ivar object_getInstanceVariable(id obj, const char *name, void **outValue)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0)
OBJC_ARC_UNAVAILABLE;


/* Obtaining Class Definitions */

/**
 * Returns the class definition of a specified class.
 *
 * @param name The name of the class to look up.
 *
 * @return The Class object for the named class, or \c nil
 *  if the class is not registered with the Objective-C runtime.
 *
 * @note \c objc_getClass is different from \c objc_lookUpClass in that if the class
 *  is not registered, \c objc_getClass calls the class handler callback and then checks
 *  a second time to see whether the class is registered. \c objc_lookUpClass does
 *  not call the class handler callback.
 *
 * @warning Earlier implementations of this function (prior to OS X v10.0)
 *  terminate the program if the class does not exist.
 */
/ *获取类定义* /

/**
 *返回指定类的类定义。
 *
 * @param name要查找的类的名称。
 *
 * @return指定类的Class对象，或\ c nil
 *如果该类没有在Objective-C运行时注册。
 *
 * @note \ c objc_getClass不同于\ c objc_lookUpClass，如果该类
 *未注册，\ c objc_getClass调用类处理程序回调然后检查
 *再次看看课程是否注册。 \ c objc_lookUpClass
 *不调用类处理程序回调。
 *
 * @warning此功能的早期实现（在OS X v10.0之前）
 *如果该类不存在则终止该程序。
 */
OBJC_EXPORT Class objc_getClass(const char *name)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/**
 * Returns the metaclass definition of a specified class.
 *
 * @param name The name of the class to look up.
 *
 * @return The \c Class object for the metaclass of the named class, or \c nil if the class
 *  is not registered with the Objective-C runtime.
 *
 * @note If the definition for the named class is not registered, this function calls the class handler
 *  callback and then checks a second time to see if the class is registered. However, every class
 *  definition must have a valid metaclass definition, and so the metaclass definition is always returned,
 *  whether it’s valid or not.
 */
/**
 *返回指定类的元类定义。
 *
 * @param name要查找的类的名称。
 *
 * @return指定类的元类的\ c类对象，如果是类，则为\ c nil
 *未在Objective-C运行时注册。
 *
 * @note如果指定类的定义未注册，则此函数调用类处理程序
 *回调，然后再次检查，看看课程是否注册。不过，每一班
 *定义必须具有有效的元类定义，因此总是返回元类定义，
 *是否有效
 */
OBJC_EXPORT Class objc_getMetaClass(const char *name)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/**
 * Returns the class definition of a specified class.
 *
 * @param name The name of the class to look up.
 *
 * @return The Class object for the named class, or \c nil if the class
 *  is not registered with the Objective-C runtime.
 *
 * @note \c objc_getClass is different from this function in that if the class is not
 *  registered, \c objc_getClass calls the class handler callback and then checks a second
 *  time to see whether the class is registered. This function does not call the class handler callback.
 */
/**
 *返回指定类的类定义。
 *
 * @param name要查找的类的名称。
 *
 * @return指定类的Class对象，如果该类为\ c nil
 *未在Objective-C运行时注册。
 *
 * @note \ c objc_getClass与此函数不同，因为如果类不是
 *注册，\ c objc_getClass调用类处理程序回调，然后检查一秒
 *查看班级是否注册的时间。此函数不调用类处理程序回调。
 */
OBJC_EXPORT Class objc_lookUpClass(const char *name)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/**
 * Returns the class definition of a specified class.
 *
 * @param name The name of the class to look up.
 *
 * @return The Class object for the named class.
 *
 * @note This function is the same as \c objc_getClass, but kills the process if the class is not found.
 * @note This function is used by ZeroLink, where failing to find a class would be a compile-time link error without ZeroLink.
 */
/**
 *返回指定类的类定义。
 *
 * @param name要查找的类的名称。
 *
 * @return命名类的Class对象。
 *
 * @note此函数与\ c objc_getClass相同，但如果找不到该类，则会杀死该进程。
 * @note ZeroLink使用这个功能，在没有ZeroLink的情况下，找不到类的编译时链接错误。
 */
OBJC_EXPORT Class objc_getRequiredClass(const char *name)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/**
 * Obtains the list of registered class definitions.
 *
 * @param buffer An array of \c Class values. On output, each \c Class value points to
 *  one class definition, up to either \e bufferCount or the total number of registered classes,
 *  whichever is less. You can pass \c NULL to obtain the total number of registered class
 *  definitions without actually retrieving any class definitions.
 * @param bufferCount An integer value. Pass the number of pointers for which you have allocated space
 *  in \e buffer. On return, this function fills in only this number of elements. If this number is less
 *  than the number of registered classes, this function returns an arbitrary subset of the registered classes.
 *
 * @return An integer value indicating the total number of registered classes.
 *
 * @note The Objective-C runtime library automatically registers all the classes defined in your source code.
 *  You can create class definitions at runtime and register them with the \c objc_addClass function.
 *
 * @warning You cannot assume that class objects you get from this function are classes that inherit from \c NSObject,
 *  so you cannot safely call any methods on such classes without detecting that the method is implemented first.
 */
/**
 *获取注册类定义的列表。
 *
 * @param buffer一个\ c类值的数组。在输出时，每个\ c类值指向
 *一个类定义，直到\ e bufferCount或注册类的总数，
 *以较小者为准。您可以通过\ c NULL获取注册类的总数
 *定义，而不实际检索任何类定义。
 * @param bufferCount一个整数值。传递您为其分配空间的指针数
 *在\ e缓冲区。返回时，此函数仅填充此数量的元素。如果这个数字较少
 *比注册的类的数量，这个函数返回注册类的任意子集。
 *
 * @return指示已注册类总数的整数值。
 *
 * @note Objective-C运行时库自动注册源代码中定义的所有类。
 *您可以在运行时创建类定义，并使用\ c objc_addClass函数注册它们。
 *
 * @warning你不能假定从这个函数得到的类对象是继承自\ c NSObject的类，
 *所以你不能安全地调用这些类的任何方法，而不检测方法是先执行的。
 */
OBJC_EXPORT int objc_getClassList(Class *buffer, int bufferCount)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/**
 * Creates and returns a list of pointers to all registered class definitions.
 *
 * @param outCount An integer pointer used to store the number of classes returned by
 *  this function in the list. It can be \c nil.
 *
 * @return A nil terminated array of classes. It must be freed with \c free().
 *
 * @see objc_getClassList
 */
/**
 *创建并返回指向所有注册类定义的指针列表。
 *
 * @param outCount用于存储返回的类的数目的整数指针
 *这个功能在列表中。它可以是\ c无。
 *
 * @return没有终止的类数组。它必须被释放\ c free（）。
 *
 * @see objc_getClassList
 */
OBJC_EXPORT Class *objc_copyClassList(unsigned int *outCount)
OBJC_AVAILABLE(10.7, 3.1, 9.0, 1.0);


/* Working with Classes */

/**
 * Returns the name of a class.
 *
 * @param cls A class object.
 *
 * @return The name of the class, or the empty string if \e cls is \c Nil.
 */
/*使用类*/

/**
 *返回类的名称。
 *
 * @param cls一个类对象。
 *
 * @return类的名称，如果\ e cls为\ c，则为空字符串。
 */
OBJC_EXPORT const char *class_getName(Class cls)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns a Boolean value that indicates whether a class object is a metaclass.
 *
 * @param cls A class object.
 *
 * @return \c YES if \e cls is a metaclass, \c NO if \e cls is a non-meta class,
 *  \c NO if \e cls is \c Nil.
 */
/**
 *返回一个布尔值，指示类对象是否是元类。
 *
 * @param cls一个类对象。
 *
 * @return \ c如果\ e cls是元类，\ c否如果\ e cls是非元类，
 * \ c否如果\ e cls是\ c无。
 */
OBJC_EXPORT BOOL class_isMetaClass(Class cls)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns the superclass of a class.
 *
 * @param cls A class object.
 *
 * @return The superclass of the class, or \c Nil if
 *  \e cls is a root class, or \c Nil if \e cls is \c Nil.
 *
 * @note You should usually use \c NSObject's \c superclass method instead of this function.
 */
/**
 *返回类的超类。
 *
 * @param cls一个类对象。
 *
 * @return类的超类，或\ c无如果
 * \ e cls是根类，或\ c如果\ e cls是\ c，则为零无。
 *
 * @note你应该通常使用\ c NSObject的\ c超类方法而不是这个函数。
 */
OBJC_EXPORT Class class_getSuperclass(Class cls)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Sets the superclass of a given class.
 *
 * @param cls The class whose superclass you want to set.
 * @param newSuper The new superclass for cls.
 *
 * @return The old superclass for cls.
 *
 * @warning You should not use this function.
 */
/**
 *设置给定类的超类。
 *
 * @param cls要设置其超类的类。
 * @param newSuper cls的新超类。
 *
 * @return cls的旧超类。
 *
 * @warning不应该使用这个功能。
 */
OBJC_EXPORT Class class_setSuperclass(Class cls, Class newSuper)
__OSX_DEPRECATED(10.5, 10.5, "not recommended")
__IOS_DEPRECATED(2.0, 2.0, "not recommended")
__TVOS_DEPRECATED(9.0, 9.0, "not recommended")
__WATCHOS_DEPRECATED(1.0, 1.0, "not recommended");

/**
 * Returns the version number of a class definition.
 *
 * @param cls A pointer to a \c Class data structure. Pass
 *  the class definition for which you wish to obtain the version.
 *
 * @return An integer indicating the version number of the class definition.
 *
 * @see class_setVersion
 */
/**
 *返回类定义的版本号。
 *
 * @param cls指向\ c类数据结构的指针。通过
 *您希望获取版本的类定义。
 *
 * @return指示类定义的版本号的整数。
 *
 * @see class_setVersion
 */
OBJC_EXPORT int class_getVersion(Class cls)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/**
 * Sets the version number of a class definition.
 *
 * @param cls A pointer to an Class data structure.
 *  Pass the class definition for which you wish to set the version.
 * @param version An integer. Pass the new version number of the class definition.
 *
 * @note You can use the version number of the class definition to provide versioning of the
 *  interface that your class represents to other classes. This is especially useful for object
 *  serialization (that is, archiving of the object in a flattened form), where it is important to
 *  recognize changes to the layout of the instance variables in different class-definition versions.
 * @note Classes derived from the Foundation framework \c NSObject class can set the class-definition
 *  version number using the \c setVersion: class method, which is implemented using the \c class_setVersion function.
 */
/**
 *设置类定义的版本号。
 *
 * @param cls指向Class数据结构的指针。
 *传递您要设置版本的类定义。
 * @param version一个整数。传递类定义的新版本号。
 *
 * @note可以使用类定义的版本号来提供版本控制
 *你的类代表其他类的接口。这对对象特别有用
 *序列化（即以对齐的形式归档对象），重要的是
 *识别不同类定义版本中实例变量布局的更改。
 * @note派生自Foundation框架的类\ NSObject类可以设置类定义
 *版本号使用\ c setVersion：class方法，它使用\ c class_setVersion函数实现。
 */
OBJC_EXPORT void class_setVersion(Class cls, int version)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/**
 * Returns the size of instances of a class.
 *
 * @param cls A class object.
 *
 * @return The size in bytes of instances of the class \e cls, or \c 0 if \e cls is \c Nil.
 */
/**
 *返回类的实例大小。
 *
 * @param cls一个类对象。
 *
 * @return类\ e cls的实例的大小（以字节为单位），如果\ e cls为\ c，则为\ c 0。
 */
OBJC_EXPORT size_t class_getInstanceSize(Class cls)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns the \c Ivar for a specified instance variable of a given class.
 *
 * @param cls The class whose instance variable you wish to obtain.
 * @param name The name of the instance variable definition to obtain.
 *
 * @return A pointer to an \c Ivar data structure containing information about
 *  the instance variable specified by \e name.
 */
/**
 *返回给定类的指定实例变量的\ c Ivar。
 *
 * @param cls要获取其实例变量的类。
 * @param name要获取的实例变量定义的名称。
 *
 * @return指向包含有关信息的\ c Ivar数据结构的指针
 *由\ e名称指定的实例变量。
 */
OBJC_EXPORT Ivar class_getInstanceVariable(Class cls, const char *name)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/**
 * Returns the Ivar for a specified class variable of a given class.
 *
 * @param cls The class definition whose class variable you wish to obtain.
 * @param name The name of the class variable definition to obtain.
 *
 * @return A pointer to an \c Ivar data structure containing information about the class variable specified by \e name.
 */
/**
 *返回给定类的指定类变量的Ivar。
 *
 * @param cls您想要获取类变量的类定义。
 * @param name要获取的类变量定义的名称。
 *
 * @return指向\ c Ivar数据结构的指针，其中包含有关由\ e name指定的类变量的信息。
 */
OBJC_EXPORT Ivar class_getClassVariable(Class cls, const char *name)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Describes the instance variables declared by a class.
 *
 * @param cls The class to inspect.
 * @param outCount On return, contains the length of the returned array.
 *  If outCount is NULL, the length is not returned.
 *
 * @return An array of pointers of type Ivar describing the instance variables declared by the class.
 *  Any instance variables declared by superclasses are not included. The array contains *outCount
 *  pointers followed by a NULL terminator. You must free the array with free().
 *
 *  If the class declares no instance variables, or cls is Nil, NULL is returned and *outCount is 0.
 */
/**
 *描述一个类声明的实例变量。
 *
 * @param cls要检查的类。
 * @param outCount返回时，包含返回的数组的长度。
 *如果outCount为NULL，则不返回长度。
 *
 * @return类型为Ivar的指针数组，用于描述该类声明的实例变量。
 *不包括任何由超类声明的实例变量。该数组包含* outCount
 *指针后跟一个NULL终结符。你必须用free（）释放数组。
 *
 *如果类声明没有实例变量，或者cls为Nil，则返回NULL，并且* outCount为0。
 */
OBJC_EXPORT Ivar *class_copyIvarList(Class cls, unsigned int *outCount)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns a specified instance method for a given class.
 *
 * @param cls The class you want to inspect.
 * @param name The selector of the method you want to retrieve.
 *
 * @return The method that corresponds to the implementation of the selector specified by
 *  \e name for the class specified by \e cls, or \c NULL if the specified class or its
 *  superclasses do not contain an instance method with the specified selector.
 *
 * @note This function searches superclasses for implementations, whereas \c class_copyMethodList does not.
 */
/**
 *返回给定类的指定实例方法。
 *
 * @param cls您要检查的类。
 * @param name要检索的方法的选择器。
 *
 * @return对应于由指定的选择器执行的方法
 * \ e由\ e cls指定的类的名称，或\ c如果指定的类或其名称为NULL
 *超类不包含具有指定选择器的实例方法。
 *
 * @note此函数搜索超类的实现，而\ c class_copyMethodList不。
 */
OBJC_EXPORT Method class_getInstanceMethod(Class cls, SEL name)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/**
 * Returns a pointer to the data structure describing a given class method for a given class.
 *
 * @param cls A pointer to a class definition. Pass the class that contains the method you want to retrieve.
 * @param name A pointer of type \c SEL. Pass the selector of the method you want to retrieve.
 *
 * @return A pointer to the \c Method data structure that corresponds to the implementation of the
 *  selector specified by aSelector for the class specified by aClass, or NULL if the specified
 *  class or its superclasses do not contain an instance method with the specified selector.
 *
 * @note Note that this function searches superclasses for implementations,
 *  whereas \c class_copyMethodList does not.
 */
/**
 *返回指向给定类的给定类方法的数据结构的指针。
 *
 * @param cls指向类定义的指针。传递包含您要检索的方法的类。
 * @param name类型为\ c SEL的指针。传递您要检索的方法的选择器。
 *
 * @return指向\ c的方法数据结构的指针
 *由aSelector为aClass指定的类指定的选择符，如果指定，则为NULL
 *类或其超类不包含具有指定选择器的实例方法。
 *
 * @note请注意，此函数搜索超类实现，
 *而\ c class_copyMethodList没有。
 */
OBJC_EXPORT Method class_getClassMethod(Class cls, SEL name)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/**
 * Returns the function pointer that would be called if a
 * particular message were sent to an instance of a class.
 *
 * @param cls The class you want to inspect.
 * @param name A selector.
 *
 * @return The function pointer that would be called if \c [object name] were called
 *  with an instance of the class, or \c NULL if \e cls is \c Nil.
 *
 * @note \c class_getMethodImplementation may be faster than \c method_getImplementation(class_getInstanceMethod(cls, name)).
 * @note The function pointer returned may be a function internal to the runtime instead of
 *  an actual method implementation. For example, if instances of the class do not respond to
 *  the selector, the function pointer returned will be part of the runtime's message forwarding machinery.
 */
/**
 *返回将被调用的函数指针
 *特殊消息被发送到一个类的实例。
 *
 * @param cls您要检查的类。
 * @param name一个选择器。
 *
 * @return调用函数指针，如果\ c [object name]被调用
 *与类的实例，或\ c如果\ e cls是\ c无空。
 *
 * @note \ c class_getMethodImplementation可能比\ c method_getImplementation（class_getInstanceMethod（cls，name））更快。
 * @note返回的函数指针可能是运行时内部的函数，而不是
 *实际的方法实现。例如，如果类的实例没有响应
 *选择器，返回的函数指针将成为运行时的消息转发机制的一部分。
 */
OBJC_EXPORT IMP class_getMethodImplementation(Class cls, SEL name)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns the function pointer that would be called if a particular
 * message were sent to an instance of a class.
 *
 * @param cls The class you want to inspect.
 * @param name A selector.
 *
 * @return The function pointer that would be called if \c [object name] were called
 *  with an instance of the class, or \c NULL if \e cls is \c Nil.
 */
/**
 *返回将被调用的函数指针
 *消息被发送到一个类的实例。
 *
 * @param cls您要检查的类。
 * @param name一个选择器。
 *
 * @return调用函数指针，如果\ c [object name]被调用
 *与类的实例，或\ c如果\ e cls是\ c无空。
 */
OBJC_EXPORT IMP class_getMethodImplementation_stret(Class cls, SEL name)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0)
OBJC_ARM64_UNAVAILABLE;

/**
 * Returns a Boolean value that indicates whether instances of a class respond to a particular selector.
 *
 * @param cls The class you want to inspect.
 * @param sel A selector.
 *
 * @return \c YES if instances of the class respond to the selector, otherwise \c NO.
 *
 * @note You should usually use \c NSObject's \c respondsToSelector: or \c instancesRespondToSelector:
 *  methods instead of this function.
 */
/**
 *返回一个布尔值，指示类的实例是否响应特定的选择器。
 *
 * @param cls您要检查的类。
 * @param sel A选择器。
 *
 * @return \ c如果类的实例响应选择器，否则为\ c否。
 *
 * @note通常你应该使用\ c NSObject的\ respondToSelector：或\ c instancesRespondToSelector：
 *方法而不是这个功能。
 */
OBJC_EXPORT BOOL class_respondsToSelector(Class cls, SEL sel)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Describes the instance methods implemented by a class.
 *
 * @param cls The class you want to inspect.
 * @param outCount On return, contains the length of the returned array.
 *  If outCount is NULL, the length is not returned.
 *
 * @return An array of pointers of type Method describing the instance methods
 *  implemented by the class—any instance methods implemented by superclasses are not included.
 *  The array contains *outCount pointers followed by a NULL terminator. You must free the array with free().
 *
 *  If cls implements no instance methods, or cls is Nil, returns NULL and *outCount is 0.
 *
 * @note To get the class methods of a class, use \c class_copyMethodList(object_getClass(cls), &count).
 * @note To get the implementations of methods that may be implemented by superclasses,
 *  use \c class_getInstanceMethod or \c class_getClassMethod.
 */
/**
 *描述一个类实现的实例方法。
 *
 * @param cls您要检查的类。
 * @param outCount返回时，包含返回的数组的长度。
 *如果outCount为NULL，则不返回长度。
 *
 * @return类型为Method的指针数组，描述实例方法
 *由类实现 - 不包括由超类实现的任何实例方法。
 *数组包含* outCount指针，后跟一个NULL终结符。你必须用free（）释放数组。
 *
 *如果cls不实现实例方法，或者cls是Nil，则返回NULL，并且* outCount为0。
 *
 * @note要获取类的类方法，请使用\ c class_copyMethodList（object_getClass（cls），＆count）。
 * @note要获取可能由超类实现的方法的实现，
 *使用\ c class_getInstanceMethod或\ c class_getClassMethod。
 */
OBJC_EXPORT Method *class_copyMethodList(Class cls, unsigned int *outCount)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns a Boolean value that indicates whether a class conforms to a given protocol.
 *
 * @param cls The class you want to inspect.
 * @param protocol A protocol.
 *
 * @return YES if cls conforms to protocol, otherwise NO.
 *
 * @note You should usually use NSObject's conformsToProtocol: method instead of this function.
 */
/**
 *返回一个布尔值，指示类是否符合给定的协议。
 *
 * @param cls您要检查的类。
 * @param协议一个协议。
 *
 *如果cls符合协议，则返回YES，否则为NO。
 *
 * @note你应该通常使用NSObject的conformsToProtocol：方法而不是这个函数。
 */
OBJC_EXPORT BOOL class_conformsToProtocol(Class cls, Protocol *protocol)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Describes the protocols adopted by a class.
 *
 * @param cls The class you want to inspect.
 * @param outCount On return, contains the length of the returned array.
 *  If outCount is NULL, the length is not returned.
 *
 * @return An array of pointers of type Protocol* describing the protocols adopted
 *  by the class. Any protocols adopted by superclasses or other protocols are not included.
 *  The array contains *outCount pointers followed by a NULL terminator. You must free the array with free().
 *
 *  If cls adopts no protocols, or cls is Nil, returns NULL and *outCount is 0.
 */
/**
 *描述一个类采用的协议。
 *
 * @param cls您要检查的类。
 * @param outCount返回时，包含返回的数组的长度。
 *如果outCount为NULL，则不返回长度。
 *
 * @return一个类型为Protocol *的指针数组，描述所采用的协议
 *上课超类或其他协议采用的任何协议都不包括在内。
 *数组包含* outCount指针，后跟一个NULL终结符。你必须用free（）释放数组。
 *
 *如果cls不使用任何协议，或者cls为Nil，则返回NULL，并且* outCount为0。
 */
OBJC_EXPORT Protocol * __unsafe_unretained *class_copyProtocolList(Class cls, unsigned int *outCount)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns a property with a given name of a given class.
 *
 * @param cls The class you want to inspect.
 * @param name The name of the property you want to inspect.
 *
 * @return A pointer of type \c objc_property_t describing the property, or
 *  \c NULL if the class does not declare a property with that name,
 *  or \c NULL if \e cls is \c Nil.
 */
/**
 *返回具有给定类的给定名称的属性。
 *
 * @param cls您要检查的类。
 * @param name要检查的属性的名称。
 *
 * @return描述属性的类型为\ c objc_property_t的指针，或
 * \ c如果该类没有声明具有该名称的属性，则为NULL，
 *或\ c如果\ e cls为\ c，则为空。
 */
OBJC_EXPORT objc_property_t class_getProperty(Class cls, const char *name)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Describes the properties declared by a class.
 *
 * @param cls The class you want to inspect.
 * @param outCount On return, contains the length of the returned array.
 *  If \e outCount is \c NULL, the length is not returned.
 *
 * @return An array of pointers of type \c objc_property_t describing the properties
 *  declared by the class. Any properties declared by superclasses are not included.
 *  The array contains \c *outCount pointers followed by a \c NULL terminator. You must free the array with \c free().
 *
 *  If \e cls declares no properties, or \e cls is \c Nil, returns \c NULL and \c *outCount is \c 0.
 */
/**
 *描述一个类声明的属性。
 *
 * @param cls您要检查的类。
 * @param outCount返回时，包含返回的数组的长度。
 *如果\ e outCount为\ c NULL，则不返回长度。
 *
 * @return描述属性的\ c objc_property_t类型的指针数组
 *由班级宣布任何由超类声明的属性都不包括在内。
 *数组包含\ c * outCount指针，后跟一个\ c NULL终结符。你必须用\ c free（）释放数组。
 *
 *如果\ e cls声明没有属性，或\ e cls是\ c Nil，返回\ c NULL，\ c * outCount为\ c 0。
 */
OBJC_EXPORT objc_property_t *class_copyPropertyList(Class cls, unsigned int *outCount)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns a description of the \c Ivar layout for a given class.
 *
 * @param cls The class to inspect.
 *
 * @return A description of the \c Ivar layout for \e cls.
 */
/**
 *返回给定类的\ c Ivar布局的描述。
 *
 * @param cls要检查的类。
 *
 * @return \ e cls的\ c Ivar布局的描述。
 */
OBJC_EXPORT const uint8_t *class_getIvarLayout(Class cls)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns a description of the layout of weak Ivars for a given class.
 *
 * @param cls The class to inspect.
 *
 * @return A description of the layout of the weak \c Ivars for \e cls.
 */
/**
 *返回给定类的弱Ivars布局的描述。
 *
 * @param cls要检查的类。
 *
 * @return对于\ e cls的weak \ c Ivars的布局的描述。
 */
OBJC_EXPORT const uint8_t *class_getWeakIvarLayout(Class cls)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Adds a new method to a class with a given name and implementation.
 *
 * @param cls The class to which to add a method.
 * @param name A selector that specifies the name of the method being added.
 * @param imp A function which is the implementation of the new method. The function must take at least two arguments—self and _cmd.
 * @param types An array of characters that describe the types of the arguments to the method.
 *
 * @return YES if the method was added successfully, otherwise NO
 *  (for example, the class already contains a method implementation with that name).
 *
 * @note class_addMethod will add an override of a superclass's implementation,
 *  but will not replace an existing implementation in this class.
 *  To change an existing implementation, use method_setImplementation.
 */
/**
 *添加一个新方法给具有给定名称和实现的类。
 *
 * @param cls添加方法的类。
 * @param name指定要添加的方法的名称的选择器。
 * @param imp一个函数，它是新方法的实现。该函数必须至少有两个参数 - self和_cmd。
 * @param types描述方法参数类型的字符数组。
 *
 *如果方法成功添加，则返回YES，否则为NO
 *（例如，该类已经包含具有该名称的方法实现）。
 *
 * @note class_addMethod将添加超类的实现的覆盖，
 *但不会替换此类中的现有实现。
 *要更改现有实现，请使用method_setImplementation。
 */
OBJC_EXPORT BOOL class_addMethod(Class cls, SEL name, IMP imp,
                                 const char *types)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Replaces the implementation of a method for a given class.
 *
 * @param cls The class you want to modify.
 * @param name A selector that identifies the method whose implementation you want to replace.
 * @param imp The new implementation for the method identified by name for the class identified by cls.
 * @param types An array of characters that describe the types of the arguments to the method.
 *  Since the function must take at least two arguments—self and _cmd, the second and third characters
 *  must be “@:” (the first character is the return type).
 *
 * @return The previous implementation of the method identified by \e name for the class identified by \e cls.
 *
 * @note This function behaves in two different ways:
 *  - If the method identified by \e name does not yet exist, it is added as if \c class_addMethod were called.
 *    The type encoding specified by \e types is used as given.
 *  - If the method identified by \e name does exist, its \c IMP is replaced as if \c method_setImplementation were called.
 *    The type encoding specified by \e types is ignored.
 */
/**
 *替换给定类的方法的实现。
 *
 * @param cls要修改的类。
 * @param name用于标识要替换其实现方法的选择器。
 * @param imp由cls标识的类的名称标识的方法的新实现。
 * @param types描述方法参数类型的字符数组。
 *由于函数必须至少有两个参数 - self和_cmd，第二个和第三个字符
 *必须是“@：”（第一个字符是返回类型）。
 *
 * @return由\ e cls标识的类由\ e name标识的方法的上一个实现。
 *
 * @note此函数有两种不同的方式：
 * - 如果由\ e name标识的方法尚不存在，则添加为\ c class_addMethod被调用。
 *使用\ e类型指定的类型编码作为给定。
 * - 如果由\ e name确定的方法确实存在，则其\ c IMP将被替换，就像调用了\ c method_setImplementation一样。
 *由\ e类型指定的类型编码被忽略。
 */
OBJC_EXPORT IMP class_replaceMethod(Class cls, SEL name, IMP imp,
                                    const char *types)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Adds a new instance variable to a class.
 *
 * @return YES if the instance variable was added successfully, otherwise NO
 *         (for example, the class already contains an instance variable with that name).
 *
 * @note This function may only be called after objc_allocateClassPair and before objc_registerClassPair.
 *       Adding an instance variable to an existing class is not supported.
 * @note The class must not be a metaclass. Adding an instance variable to a metaclass is not supported.
 * @note The instance variable's minimum alignment in bytes is 1<<align. The minimum alignment of an instance
 *       variable depends on the ivar's type and the machine architecture.
 *       For variables of any pointer type, pass log2(sizeof(pointer_type)).
 */
/**
 *向类添加一个新的实例变量。
 *
 * @return如果实例变量成功添加，否则否
 *（例如，该类已经包含一个具有该名称的实例变量）。
 *
 * @note此函数只能在objc_allocateClassPair之后和objc_registerClassPair之前调用。
 *不支持将实例变量添加到现有类。
 * @note类不能是元类。不支持将实例变量添加到元类。
 * @note实例变量的最小对齐方式为1 << align。一个实例的最小对齐
 *变量取决于ivar的类型和机器结构。
 *对于任何指针类型的变量，传递log2（sizeof（pointer_type））。
 */
OBJC_EXPORT BOOL class_addIvar(Class cls, const char *name, size_t size,
                               uint8_t alignment, const char *types)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Adds a protocol to a class.
 *
 * @param cls The class to modify.
 * @param protocol The protocol to add to \e cls.
 *
 * @return \c YES if the method was added successfully, otherwise \c NO
 *  (for example, the class already conforms to that protocol).
 */
/**
 *向类添加协议。
 *
 * @param cls要修改的类。
 * @param协议添加到\ e cls的协议。
 *
 * @return \ c如果方法成功添加，否则\ c否
 *（例如，该类已经符合该协议）。
 */
OBJC_EXPORT BOOL class_addProtocol(Class cls, Protocol *protocol)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Adds a property to a class.
 *
 * @param cls The class to modify.
 * @param name The name of the property.
 * @param attributes An array of property attributes.
 * @param attributeCount The number of attributes in \e attributes.
 *
 * @return \c YES if the property was added successfully, otherwise \c NO
 *  (for example, the class already has that property).
 */
/**
 *添加一个属性到一个类。
 *
 * @param cls要修改的类。
 * @param name属性的名称。
 * @param属性属性属性数组。
 * @param attributeCount \ e属性中的属性数。
 *
 * @return \ c如果属性成功添加，否则\ c否
 *（例如，该类已经拥有该属性）。
 */
OBJC_EXPORT BOOL class_addProperty(Class cls, const char *name, const objc_property_attribute_t *attributes, unsigned int attributeCount)
OBJC_AVAILABLE(10.7, 4.3, 9.0, 1.0);

/**
 * Replace a property of a class.
 *
 * @param cls The class to modify.
 * @param name The name of the property.
 * @param attributes An array of property attributes.
 * @param attributeCount The number of attributes in \e attributes.
 */
/**
 *替换类的属性。
 *
 * @param cls要修改的类。
 * @param name属性的名称。
 * @param属性属性属性数组。
 * @param attributeCount \ e属性中的属性数。
 */
OBJC_EXPORT void class_replaceProperty(Class cls, const char *name, const objc_property_attribute_t *attributes, unsigned int attributeCount)
OBJC_AVAILABLE(10.7, 4.3, 9.0, 1.0);

/**
 * Sets the Ivar layout for a given class.
 *
 * @param cls The class to modify.
 * @param layout The layout of the \c Ivars for \e cls.
 */
/**
 *设置给定类的Ivar布局。
 *
 * @param cls要修改的类。
 * @param layout \ c Ivars for \ e cls的布局。
 */
OBJC_EXPORT void class_setIvarLayout(Class cls, const uint8_t *layout)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Sets the layout for weak Ivars for a given class.
 *
 * @param cls The class to modify.
 * @param layout The layout of the weak Ivars for \e cls.
 */
/**
 *为给定类设置弱Ivars的布局。
 *
 * @param cls要修改的类。
 * @param layout \ e cls的弱Ivars的布局。
 */
OBJC_EXPORT void class_setWeakIvarLayout(Class cls, const uint8_t *layout)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Used by CoreFoundation's toll-free bridging.
 * Return the id of the named class.
 *
 * @return The id of the named class, or an uninitialized class
 *  structure that will be used for the class when and if it does
 *  get loaded.
 *
 * @warning Do not call this function yourself.
 */
/**
 *由CoreFoundation的免费桥接使用。
 *返回命名类的id。
 *
 * @return指定类的id或未初始化的类
 *结构，将用于类，当和如果它
 *加载。
 *
 * @warning不要自己调用这个功能。
 */
OBJC_EXPORT Class objc_getFutureClass(const char *name)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0)
OBJC_ARC_UNAVAILABLE;


/* Instantiating Classes */

/**
 * Creates an instance of a class, allocating memory for the class in the
 * default malloc memory zone.
 *
 * @param cls The class that you wish to allocate an instance of.
 * @param extraBytes An integer indicating the number of extra bytes to allocate.
 *  The additional bytes can be used to store additional instance variables beyond
 *  those defined in the class definition.
 *
 * @return An instance of the class \e cls.
 */
/*实例化课程*/

/**
 *创建一个类的实例，为该类分配内存
 *默认的malloc内存区域。
 *
 * @param cls您要分配一个实例的类。
 * @param extraBytes指示要分配的额外字节数的整数。
 *额外的字节可用于存储额外的实例变量
 *定义在类定义中的那些。
 *
 * @return类\ e cls的一个实例。
 */
OBJC_EXPORT id class_createInstance(Class cls, size_t extraBytes)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0)
OBJC_ARC_UNAVAILABLE;

/**
 * Creates an instance of a class at the specific location provided.
 *
 * @param cls The class that you wish to allocate an instance of.
 * @param bytes The location at which to allocate an instance of \e cls.
 *  Must point to at least \c class_getInstanceSize(cls) bytes of well-aligned,
 *  zero-filled memory.
 *
 * @return \e bytes on success, \c nil otherwise. (For example, \e cls or \e bytes
 *  might be \c nil)
 *
 * @see class_createInstance
 */
/**
 *在提供的特定位置创建一个类的实例。
 *
 * @param cls您要分配一个实例的类。
 * @param bytes分配\ e cls实例的位置。
 *必须指向至少\ c class_getInstanceSize（cls）字节的对齐，
 *零填充内存
 *
 * @return \ e成功的字节，否则为c。 （例如，\ e cls或\ e字节
 *可能是\ c nil）
 *
 * @see class_createInstance
 */
OBJC_EXPORT id objc_constructInstance(Class cls, void *bytes)
OBJC_AVAILABLE(10.6, 3.0, 9.0, 1.0)
OBJC_ARC_UNAVAILABLE;

/**
 * Destroys an instance of a class without freeing memory and removes any
 * associated references this instance might have had.
 *
 * @param obj The class instance to destroy.
 *
 * @return \e obj. Does nothing if \e obj is nil.
 *
 * @note CF and other clients do call this under GC.
 */
/**
 *销毁一个类的实例，而不释放内存并删除任何内容
 *这个实例可能有的相关联的引用。
 *
 * @param obj要破坏的类实例。
 *
 * @return \ e obj。如果\ e obj为零，则不做任何操作。
 *
 * @note CF和其他客户端在GC下称之为“
 */
OBJC_EXPORT void *objc_destructInstance(id obj)
OBJC_AVAILABLE(10.6, 3.0, 9.0, 1.0)
OBJC_ARC_UNAVAILABLE;


/* Adding Classes */

/**
 * Creates a new class and metaclass.
 *
 * @param superclass The class to use as the new class's superclass, or \c Nil to create a new root class.
 * @param name The string to use as the new class's name. The string will be copied.
 * @param extraBytes The number of bytes to allocate for indexed ivars at the end of
 *  the class and metaclass objects. This should usually be \c 0.
 *
 * @return The new class, or Nil if the class could not be created (for example, the desired name is already in use).
 *
 * @note You can get a pointer to the new metaclass by calling \c object_getClass(newClass).
 * @note To create a new class, start by calling \c objc_allocateClassPair.
 *  Then set the class's attributes with functions like \c class_addMethod and \c class_addIvar.
 *  When you are done building the class, call \c objc_registerClassPair. The new class is now ready for use.
 * @note Instance methods and instance variables should be added to the class itself.
 *  Class methods should be added to the metaclass.
 */
/ *添加类* /

/**
 *创建一个新的类和元类。
 *
 * @param superclass用作新类的超类的类，或\ c无创建新的根类。
 * @param name用作新类的名称的字符串。该字符串将被复制。
 * @param extraBytes要为索引的ivars分配的字节数
 *类和元类对象。这通常应该是\ c 0。
 *
 * @return新类，如果类无法创建，则为Nil（例如，所需名称已在使用中）。
 *
 * @note通过调用\ c object_getClass（newClass）可以获得指向新元类的指针。
 * @note要创建一个新类，首先调用\ c objc_allocateClassPair。
 *然后使用\ c class_addMethod和\ c class_addIvar等函数设置类的属性。
 *完成课程后，请调用\ c objc_registerClassPair。新课程现在可以使用了。
 * @note实例方法和实例变量应该添加到类本身。
 *类方法应该添加到元类。
 */
OBJC_EXPORT Class objc_allocateClassPair(Class superclass, const char *name,
                                         size_t extraBytes)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Registers a class that was allocated using \c objc_allocateClassPair.
 *
 * @param cls The class you want to register.
 */
/**
 *注册使用\ c objc_allocateClassPair分配的类。
 *
 * @param cls要注册的类。
 */
OBJC_EXPORT void objc_registerClassPair(Class cls)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Used by Foundation's Key-Value Observing.
 *
 * @warning Do not call this function yourself.
 */
/**
 *用于Foundation's的KVO观察。
 *
 * @warning不要自己调用这个功能。
 */
OBJC_EXPORT Class objc_duplicateClass(Class original, const char *name, size_t extraBytes)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Destroy a class and its associated metaclass.
 *
 * @param cls The class to be destroyed. It must have been allocated with
 *  \c objc_allocateClassPair
 *
 * @warning Do not call if instances of this class or a subclass exist.
 */
/**
 *销毁一个类及其相关的元类。
 *
 * @param cls要销毁的类。它必须已经分配
 * \ c objc_allocateClassPair
 *
 * @warning如果此类或子类的实例存在，请不要调用。
 */
OBJC_EXPORT void objc_disposeClassPair(Class cls)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);


/* Working with Methods */

/**
 * Returns the name of a method.
 *
 * @param m The method to inspect.
 *
 * @return A pointer of type SEL.
 *
 * @note To get the method name as a C string, call \c sel_getName(method_getName(method)).
 */
/*使用方法*/
/**
 *返回方法的名称。
 *
 * @param m要检查的方法。
 *
 * @return一个类型为SEL的指针。
 *
 * @note要将方法名称作为C字符串，请调用\ c sel_getName（method_getName（method））。
 */
OBJC_EXPORT SEL method_getName(Method m)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns the implementation of a method.
 *
 * @param m The method to inspect.
 *
 * @return A function pointer of type IMP.
 */
/**
 *返回方法的实现。
 *
 * @param m要检查的方法。
 *
 * @return IMP类型的函数指针。
 */
OBJC_EXPORT IMP method_getImplementation(Method m)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns a string describing a method's parameter and return types.
 *
 * @param m The method to inspect.
 *
 * @return A C string. The string may be \c NULL.
 */
/**
 *返回描述方法参数和返回类型的字符串。
 *
 * @param m要检查的方法。
 *
 * @返回一个C字符串。字符串可能为\ c NULL。
 */
OBJC_EXPORT const char *method_getTypeEncoding(Method m)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns the number of arguments accepted by a method.
 *
 * @param m A pointer to a \c Method data structure. Pass the method in question.
 *
 * @return An integer containing the number of arguments accepted by the given method.
 */
/**
 *返回方法接受的参数数。
 *
 * @param m指向\ c方法数据结构的指针。通过相关方法。
 *
 * @return包含给定方法接受的参数数的整数。
 */
OBJC_EXPORT unsigned int method_getNumberOfArguments(Method m)
OBJC_AVAILABLE(10.0, 2.0, 9.0, 1.0);

/**
 * Returns a string describing a method's return type.
 *
 * @param m The method to inspect.
 *
 * @return A C string describing the return type. You must free the string with \c free().
 */
/**
 *返回描述方法返回类型的字符串。
 *
 * @param m要检查的方法。
 *
 * @return描述返回类型的C字符串。你必须用\ c free（）释放字符串。
 */
OBJC_EXPORT char *method_copyReturnType(Method m)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns a string describing a single parameter type of a method.
 *
 * @param m The method to inspect.
 * @param index The index of the parameter to inspect.
 *
 * @return A C string describing the type of the parameter at index \e index, or \c NULL
 *  if method has no parameter index \e index. You must free the string with \c free().
 */
/**
 *返回描述方法的单个参数类型的字符串。
 *
 * @param m要检查的方法。
 * @param index要检查的参数的索引。
 *
 * @return描述index \ e索引处的参数类型的C字符串，或\ c NULL
 *如果方法没有参数index \ e索引。你必须用\ c free（）释放字符串。
 */
OBJC_EXPORT char *method_copyArgumentType(Method m, unsigned int index)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns by reference a string describing a method's return type.
 *
 * @param m The method you want to inquire about.
 * @param dst The reference string to store the description.
 * @param dst_len The maximum number of characters that can be stored in \e dst.
 *
 * @note The method's return type string is copied to \e dst.
 *  \e dst is filled as if \c strncpy(dst, parameter_type, dst_len) were called.
 */
/**
 *通过引用返回一个描述方法返回类型的字符串。
 *
 * @param m您要查询的方法。
 * @param dst用于存储描述的引用字符串。
 * @param dst_len可以存储在\ e dst中的最大字符数。
 *
 * @note该方法的返回类型字符串被复制到\ e dst。
 * \ e dst被填充，就像\ c strncpy（dst，parameter_type，dst_len）被调用一样。
 */
OBJC_EXPORT void method_getReturnType(Method m, char *dst, size_t dst_len)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns by reference a string describing a single parameter type of a method.
 *
 * @param m The method you want to inquire about.
 * @param index The index of the parameter you want to inquire about.
 * @param dst The reference string to store the description.
 * @param dst_len The maximum number of characters that can be stored in \e dst.
 *
 * @note The parameter type string is copied to \e dst. \e dst is filled as if \c strncpy(dst, parameter_type, dst_len)
 *  were called. If the method contains no parameter with that index, \e dst is filled as
 *  if \c strncpy(dst, "", dst_len) were called.
 */
/**
 *通过引用返回描述方法的单个参数类型的字符串。
 *
 * @param m您要查询的方法。
 * @param index要查询的参数的索引。
 * @param dst用于存储描述的引用字符串。
 * @param dst_len可以存储在\ e dst中的最大字符数。
 *
 * @note将参数类型字符串复制到\ e dst。 \ e dst被填充，就好像\ c strncpy（dst，parameter_type，dst_len）
 *被叫。如果该方法不包含该索引的参数，则\ e dst将填充为
 *如果\ c strncpy（dst，“”，dst_len）被调用。
 */
OBJC_EXPORT void method_getArgumentType(Method m, unsigned int index,
                                        char *dst, size_t dst_len)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);
OBJC_EXPORT struct objc_method_description *method_getDescription(Method m)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Sets the implementation of a method.
 *
 * @param m The method for which to set an implementation.
 * @param imp The implemention to set to this method.
 *
 * @return The previous implementation of the method.
 */
/**
 *设置方法的实现。
 *
 * @param m设置实现的方法。
 * @param imp设置为此方法的实现。
 *
 * @return先前实现的方法。
 */
OBJC_EXPORT IMP method_setImplementation(Method m, IMP imp)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Exchanges the implementations of two methods.
 *
 * @param m1 Method to exchange with second method.
 * @param m2 Method to exchange with first method.
 *
 * @note This is an atomic version of the following:
 *  \code
 *  IMP imp1 = method_getImplementation(m1);
 *  IMP imp2 = method_getImplementation(m2);
 *  method_setImplementation(m1, imp2);
 *  method_setImplementation(m2, imp1);
 *  \endcode
 */
/**
 *交换两种方法的实现。
 *
 * @param m1与第二种方法交换的方法。
 * @param m2使用第一种方法交换的方法。
 *
 * @note这是以下的原子版本：
 * \ code
 * IMP imp1 = method_getImplementation（m1）;
 * IMP imp2 = method_getImplementation（m2）;
 * method_setImplementation（m1，imp2）;
 * method_setImplementation（m2，imp1）;
 * \ endcode
 */
OBJC_EXPORT void method_exchangeImplementations(Method m1, Method m2)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);


/* Working with Instance Variables */

/**
 * Returns the name of an instance variable.
 *
 * @param v The instance variable you want to enquire about.
 *
 * @return A C string containing the instance variable's name.
 */
/*使用实例变量*/

/**
 *返回实例变量的名称。
 *
 * @param v要查询的实例变量。
 *
 * @return包含实例变量名称的C字符串。
 */
OBJC_EXPORT const char *ivar_getName(Ivar v)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns the type string of an instance variable.
 *
 * @param v The instance variable you want to enquire about.
 *
 * @return A C string containing the instance variable's type encoding.
 *
 * @note For possible values, see Objective-C Runtime Programming Guide > Type Encodings.
 */
/**
 *返回实例变量的类型字符串。
 *
 * @param v要查询的实例变量。
 *
 * @return包含实例变量的类型编码的C字符串。
 *
 * @note有关可能的值，请参阅Objective-C运行时编程指南>类型编码。
 */
OBJC_EXPORT const char *ivar_getTypeEncoding(Ivar v)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns the offset of an instance variable.
 *
 * @param v The instance variable you want to enquire about.
 *
 * @return The offset of \e v.
 *
 * @note For instance variables of type \c id or other object types, call \c object_getIvar
 *  and \c object_setIvar instead of using this offset to access the instance variable data directly.
 */
/**
 *返回实例变量的偏移量。
 *
 * @param v要查询的实例变量。
 *
 * @return \ e v。的偏移量。
 *
 * @note对于类型为\ c id或其他对象类型的变量，调用\ c object_getIvar
 *和\ c object_setIvar而不是使用此偏移量直接访问实例变量数据。
 */
OBJC_EXPORT ptrdiff_t ivar_getOffset(Ivar v)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);


/* Working with Properties */

/**
 * Returns the name of a property.
 *
 * @param property The property you want to inquire about.
 *
 * @return A C string containing the property's name.
 */
/*使用属性*/

/**
 *返回属性的名称。
 *
 * @param属性您要查询的属性。
 *
 * @return包含属性名称的C字符串。
 */
OBJC_EXPORT const char *property_getName(objc_property_t property)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns the attribute string of a property.
 *
 * @param property A property.
 *
 * @return A C string containing the property's attributes.
 *
 * @note The format of the attribute string is described in Declared Properties in Objective-C Runtime Programming Guide.
 */
/**
 *返回属性的属性字符串。
 *
 * @param属性一个属性。
 *
 * @return包含属性属性的C字符串。
 *
 * @note属性字符串的格式在Objective-C运行时编程指南中的声明属性中有描述。
 */
OBJC_EXPORT const char *property_getAttributes(objc_property_t property)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns an array of property attributes for a property.
 *
 * @param property The property whose attributes you want copied.
 * @param outCount The number of attributes returned in the array.
 *
 * @return An array of property attributes; must be free'd() by the caller.
 */
/**
 *返回属性的属性属性数组。
 *
 * @param属性要复制其属性的属性。
 * @param outCount数组中返回的属性数。
 *
 * @return属性属性数组;必须由调用者free'd（）。
 */
OBJC_EXPORT objc_property_attribute_t *property_copyAttributeList(objc_property_t property, unsigned int *outCount)
OBJC_AVAILABLE(10.7, 4.3, 9.0, 1.0);

/**
 * Returns the value of a property attribute given the attribute name.
 *
 * @param property The property whose attribute value you are interested in.
 * @param attributeName C string representing the attribute name.
 *
 * @return The value string of the attribute \e attributeName if it exists in
 *  \e property, \c nil otherwise.
 */
/**
 *返回给定属性名称的属性属性的值。
 *
 * @param属性您感兴趣的属性值的属性。
 * @param attributeName表示属性名称的C字符串。
 *
 * @return属性\ e attributeName的值字符串（如果存在）
 * \ e属性，否则为c。
 */
OBJC_EXPORT char *property_copyAttributeValue(objc_property_t property, const char *attributeName)
OBJC_AVAILABLE(10.7, 4.3, 9.0, 1.0);


/* Working with Protocols */

/**
 * Returns a specified protocol.
 *
 * @param name The name of a protocol.
 *
 * @return The protocol named \e name, or \c NULL if no protocol named \e name could be found.
 *
 * @note This function acquires the runtime lock.
 */
/ *使用协议* /

/**
 *返回指定的协议。
 *
 * @param name协议的名称。
 *
 * @return名为\ e name的协议，或\ c如果没有找到名为\ e name的协议，则为空。
 *
 * @note此函数获取运行时锁定。
 */
OBJC_EXPORT Protocol *objc_getProtocol(const char *name)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns an array of all the protocols known to the runtime.
 *
 * @param outCount Upon return, contains the number of protocols in the returned array.
 *
 * @return A C array of all the protocols known to the runtime. The array contains \c *outCount
 *  pointers followed by a \c NULL terminator. You must free the list with \c free().
 *
 * @note This function acquires the runtime lock.
 */
/**
 *返回运行时已知的所有协议的数组。
 *
 * @param outCount返回时，包含返回的数组中的协议数。
 *
 * @return运行时已知的所有协议的C数组。该数组包含\ c * outCount
 *指针后跟一个\ c NULL终结符。您必须使用\ c free（）释放列表。
 *
 * @note此函数获取运行时锁定。
 */
OBJC_EXPORT Protocol * __unsafe_unretained *objc_copyProtocolList(unsigned int *outCount)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns a Boolean value that indicates whether one protocol conforms to another protocol.
 *
 * @param proto A protocol.
 * @param other A protocol.
 *
 * @return \c YES if \e proto conforms to \e other, otherwise \c NO.
 *
 * @note One protocol can incorporate other protocols using the same syntax
 *  that classes use to adopt a protocol:
 *  \code
 *  @protocol ProtocolName < protocol list >
 *  \endcode
 *  All the protocols listed between angle brackets are considered part of the ProtocolName protocol.
 */
/**
 *返回一个布尔值，指示一个协议是否符合另一个协议。
 *
 * @param proto A协议。
 * @param其他A协议。
 *
 * @return \ c如果\ e proto符合\ e其他，否则\ c否。
 *
 * @note一个协议可以包含使用相同语法的其他协议
 该类用于采用协议：
 * \ code
 * @协议ProtocolName <协议列表>
 * \ endcode
 *在尖括号之间列出的所有协议都被认为是ProtocolName协议的一部分。
 */
OBJC_EXPORT BOOL protocol_conformsToProtocol(Protocol *proto, Protocol *other)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns a Boolean value that indicates whether two protocols are equal.
 *
 * @param proto A protocol.
 * @param other A protocol.
 *
 * @return \c YES if \e proto is the same as \e other, otherwise \c NO.
 */
/**
 *返回一个布尔值，指示两个协议是否相等。
 *
 * @param proto A协议。
 * @param其他A协议。
 *
 * @return \ c如果\ e proto与\ e other相同，否则\ c否。
 */
OBJC_EXPORT BOOL protocol_isEqual(Protocol *proto, Protocol *other)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns the name of a protocol.
 *
 * @param p A protocol.
 *
 * @return The name of the protocol \e p as a C string.
 */
/**
 *返回协议的名称。
 *
 * @param p A协议。
 *
 * @return协议\ e p的名称为C字符串。
 */
OBJC_EXPORT const char *protocol_getName(Protocol *p)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns a method description structure for a specified method of a given protocol.
 *
 * @param p A protocol.
 * @param aSel A selector.
 * @param isRequiredMethod A Boolean value that indicates whether aSel is a required method.
 * @param isInstanceMethod A Boolean value that indicates whether aSel is an instance method.
 *
 * @return An \c objc_method_description structure that describes the method specified by \e aSel,
 *  \e isRequiredMethod, and \e isInstanceMethod for the protocol \e p.
 *  If the protocol does not contain the specified method, returns an \c objc_method_description structure
 *  with the value \c {NULL, \c NULL}.
 *
 * @note This function recursively searches any protocols that this protocol conforms to.
 */
/**
 *返回给定协议的指定方法的方法描述结构。
 *
 * @param p A协议。
 * @param aSel A选择器。
 * @param isRequiredMethod一个布尔值，指示aSel是否为必需的方法。
 * @param isInstanceMethod一个布尔值，指示aSel是否为实例方法。
 *
 * @return描述由\ e aSel指定的方法的\ c objc_method_description结构，
 * \ e isRequiredMethod，\ e isInstanceMethod为协议\ e p。
 *如果协议不包含指定的方法，则返回一个\ c objc_method_description结构
 *值为\ c {NULL，\ c NULL}。
 *
 * @note此函数递归地搜索该协议符合的任何协议。
 */
OBJC_EXPORT struct objc_method_description protocol_getMethodDescription(Protocol *p, SEL aSel, BOOL isRequiredMethod, BOOL isInstanceMethod)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns an array of method descriptions of methods meeting a given specification for a given protocol.
 *
 * @param p A protocol.
 * @param isRequiredMethod A Boolean value that indicates whether returned methods should
 *  be required methods (pass YES to specify required methods).
 * @param isInstanceMethod A Boolean value that indicates whether returned methods should
 *  be instance methods (pass YES to specify instance methods).
 * @param outCount Upon return, contains the number of method description structures in the returned array.
 *
 * @return A C array of \c objc_method_description structures containing the names and types of \e p's methods
 *  specified by \e isRequiredMethod and \e isInstanceMethod. The array contains \c *outCount pointers followed
 *  by a \c NULL terminator. You must free the list with \c free().
 *  If the protocol declares no methods that meet the specification, \c NULL is returned and \c *outCount is 0.
 *
 * @note Methods in other protocols adopted by this protocol are not included.
 */
/**
 *返回一个满足给定协议给定规范的方法的方法描述数组。
 *
 * @param p A协议。
 * @param isRequiredMethod一个布尔值，指示返回的方法是否应该
 *是必需的方法（通过YES指定所需的方法）。
 * @param isInstanceMethod一个布尔值，指示返回的方法是否应该
 *是实例方法（传递YES指定实例方法）。
 * @param outCount返回时，包含返回的数组中的方法描述结构的数量。
 *
 * @return包含\ e p方法的名称和类型的\ c objc_method_description结构的C数组
 *由\ e isRequiredMethod指定，\ e isInstanceMethod。该数组包含\ c * outCount指针
 *由一个\ c NULL终结符。您必须使用\ c free（）释放列表。
 *如果协议声明没有符合规范的方法，则返回\ c NULL，并且\ c * outCount为0。
 *
 * @note不包括本协议采用的其他协议中的方法。
 */
OBJC_EXPORT struct objc_method_description *protocol_copyMethodDescriptionList(Protocol *p, BOOL isRequiredMethod, BOOL isInstanceMethod, unsigned int *outCount)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns the specified property of a given protocol.
 *
 * @param proto A protocol.
 * @param name The name of a property.
 * @param isRequiredProperty \c YES searches for a required property, \c NO searches for an optional property.
 * @param isInstanceProperty \c YES searches for an instance property, \c NO searches for a class property.
 *
 * @return The property specified by \e name, \e isRequiredProperty, and \e isInstanceProperty for \e proto,
 *  or \c NULL if none of \e proto's properties meets the specification.
 */
/**
 *返回给定协议的指定属性。
 *
 * @param proto A协议。
 * @param name属性的名称。
 * @param isRequiredProperty \ c YES搜索所需属性，\ c否搜索可选属性。
 * @param isInstanceProperty \ c YES搜索实例属性，\ c否搜索类属性。
 *
 * @return \ e name指定的属性，\ e isRequiredProperty，\ e isInstanceProperty for \ e proto，
 *或\ c如果没有\ e proto的属性符合规范，则为NULL。
 */
OBJC_EXPORT objc_property_t protocol_getProperty(Protocol *proto, const char *name, BOOL isRequiredProperty, BOOL isInstanceProperty)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns an array of the required instance properties declared by a protocol.
 *
 * @note Identical to
 * \code
 * protocol_copyPropertyList2(proto, outCount, YES, YES);
 * \endcode
 */
/**
 *返回一个协议声明的必需实例属性的数组。
 *
 * @note相同
 * \ code
 * protocol_copyPropertyList2（proto，outCount，YES，YES）;
 * \ endcode
 */
OBJC_EXPORT objc_property_t *protocol_copyPropertyList(Protocol *proto, unsigned int *outCount)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns an array of properties declared by a protocol.
 *
 * @param proto A protocol.
 * @param outCount Upon return, contains the number of elements in the returned array.
 * @param isRequiredProperty \c YES returns required properties, \c NO returns optional properties.
 * @param isInstanceProperty \c YES returns instance properties, \c NO returns class properties.
 *
 * @return A C array of pointers of type \c objc_property_t describing the properties declared by \e proto.
 *  Any properties declared by other protocols adopted by this protocol are not included. The array contains
 *  \c *outCount pointers followed by a \c NULL terminator. You must free the array with \c free().
 *  If the protocol declares no matching properties, \c NULL is returned and \c *outCount is \c 0.
 */
/**
 *返回一个协议声明的属性数组。
 *
 * @param proto A协议。
 * @param outCount返回时，包含返回数组中的元素数。
 * @param isRequiredProperty \ c YES返回必需的属性，\ c NO返回可选属性。
 * @param isInstanceProperty \ c YES返回实例属性，\ c否返回类属性。
 *
 * @return类型为\ c objc_property_t的指针的C数组，描述由\ e proto声明的属性。
 *本协议采用的其他协议声明的任何属性均不包括在内。数组包含
 * \ c * outCount指针后跟一个\ c NULL终结符。你必须用\ c free（）释放数组。
 *如果协议声明没有匹配的属性，则返回\ c NULL，\ c * outCount为\ c 0。
 */
OBJC_EXPORT objc_property_t *protocol_copyPropertyList2(Protocol *proto, unsigned int *outCount, BOOL isRequiredProperty, BOOL isInstanceProperty)
OBJC_AVAILABLE(10.12, 10.0, 10.0, 3.0);

/**
 * Returns an array of the protocols adopted by a protocol.
 *
 * @param proto A protocol.
 * @param outCount Upon return, contains the number of elements in the returned array.
 *
 * @return A C array of protocols adopted by \e proto. The array contains \e *outCount pointers
 *  followed by a \c NULL terminator. You must free the array with \c free().
 *  If the protocol declares no properties, \c NULL is returned and \c *outCount is \c 0.
 */
/**
 *返回协议采用的协议的数组。
 *
 * @param proto A协议。
 * @param outCount返回时，包含返回数组中的元素数。
 *
 * @return \ e proto采用的C数组协议。该数组包含\ e * outCount指针
 *后跟一个\ c NULL终结符。你必须用\ c free（）释放数组。
 *如果协议声明没有属性，则返回\ c NULL，并且\ c * outCount为\ c 0。
 */
OBJC_EXPORT Protocol * __unsafe_unretained *protocol_copyProtocolList(Protocol *proto, unsigned int *outCount)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Creates a new protocol instance that cannot be used until registered with
 * \c objc_registerProtocol()
 *
 * @param name The name of the protocol to create.
 *
 * @return The Protocol instance on success, \c nil if a protocol
 *  with the same name already exists.
 * @note There is no dispose method for this.
 */
/**
 *创建一个新的协议实例，直到注册才能使用
 * \ c objc_registerProtocol（）
 *
 * @param name要创建的协议的名称。
 *
 * @return协议实例成功，\ c如果一个协议
 *同名已经存在。
 * @note没有处理方法。
 */
OBJC_EXPORT Protocol *objc_allocateProtocol(const char *name)
OBJC_AVAILABLE(10.7, 4.3, 9.0, 1.0);

/**
 * Registers a newly constructed protocol with the runtime. The protocol
 * will be ready for use and is immutable after this.
 *
 * @param proto The protocol you want to register.
 */
/**
 *使用运行时注册新构建的协议。协议
 *将准备使用，并且在此之后是不可变的。
 *
 * @param proto要注册的协议。
 */
OBJC_EXPORT void objc_registerProtocol(Protocol *proto)
OBJC_AVAILABLE(10.7, 4.3, 9.0, 1.0);

/**
 * Adds a method to a protocol. The protocol must be under construction.
 *
 * @param proto The protocol to add a method to.
 * @param name The name of the method to add.
 * @param types A C string that represents the method signature.
 * @param isRequiredMethod YES if the method is not an optional method.
 * @param isInstanceMethod YES if the method is an instance method.
 */
/**
 *向协议添加一个方法。协议必须在建设中。
 *
 * @param proto将方法添加到的协议。
 * @param name要添加的方法的名称。
 * @param types表示方法签名的C字符串。
 * @param isRequiredMethod YES如果方法不是可选方法。
 * @param isInstanceMethod如果该方法是实例方法，则为YES。
 */
OBJC_EXPORT void protocol_addMethodDescription(Protocol *proto, SEL name, const char *types, BOOL isRequiredMethod, BOOL isInstanceMethod)
OBJC_AVAILABLE(10.7, 4.3, 9.0, 1.0);

/**
 * Adds an incorporated protocol to another protocol. The protocol being
 * added to must still be under construction, while the additional protocol
 * must be already constructed.
 *
 * @param proto The protocol you want to add to, it must be under construction.
 * @param addition The protocol you want to incorporate into \e proto, it must be registered.
 */
/**
 *将并入协议添加到另一个协议。协议是
 *添加到仍然在建设中，而附加协议
 *必须已经建成。
 *
 * @param proto要添加的协议，它必须正在建设中。
 * @param addition你想要合并到\ e proto的协议，它必须被注册。
 */
OBJC_EXPORT void protocol_addProtocol(Protocol *proto, Protocol *addition)
OBJC_AVAILABLE(10.7, 4.3, 9.0, 1.0);

/**
 * Adds a property to a protocol. The protocol must be under construction.
 *
 * @param proto The protocol to add a property to.
 * @param name The name of the property.
 * @param attributes An array of property attributes.
 * @param attributeCount The number of attributes in \e attributes.
 * @param isRequiredProperty YES if the property (accessor methods) is not optional.
 * @param isInstanceProperty YES if the property (accessor methods) are instance methods.
 *  This is the only case allowed fo a property, as a result, setting this to NO will
 *  not add the property to the protocol at all.
 */
/**
 *向协议添加属性。协议必须在建设中。
 *
 * @param proto将属性添加到的协议。
 * @param name属性的名称。
 * @param属性属性属性数组。
 * @param attributeCount \ e属性中的属性数。
 * @param isRequiredProperty YES如果属性（访问方法）不是可选的。
 * @param isInstanceProperty YES如果属性（访问器方法）是实例方法。
 *这是财产允许的唯一情况，因此将其设置为否
 *根本不添加该协议的属性。
 */
OBJC_EXPORT void protocol_addProperty(Protocol *proto, const char *name, const objc_property_attribute_t *attributes, unsigned int attributeCount, BOOL isRequiredProperty, BOOL isInstanceProperty)
OBJC_AVAILABLE(10.7, 4.3, 9.0, 1.0);


/* Working with Libraries */

/**
 * Returns the names of all the loaded Objective-C frameworks and dynamic
 * libraries.
 *
 * @param outCount The number of names returned.
 *
 * @return An array of C strings of names. Must be free()'d by caller.
 */
/ *使用库* /

/**
 *返回所有加载的Objective-C框架和动态的名称
 *图书馆。
 *
 * @param outCount返回的名称数。
 *
 * @return一组C字符串的名称。必须由调用者free（）'d。
 */
OBJC_EXPORT const char **objc_copyImageNames(unsigned int *outCount)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns the dynamic library name a class originated from.
 *
 * @param cls The class you are inquiring about.
 *
 * @return The name of the library containing this class.
 */
/**
 *返回一个类源自的动态库名称。
 *
 * @param cls您正在查询的课程。
 *
 * @return包含此类的库的名称。
 */
OBJC_EXPORT const char *class_getImageName(Class cls)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Returns the names of all the classes within a library.
 *
 * @param image The library or framework you are inquiring about.
 * @param outCount The number of class names returned.
 *
 * @return An array of C strings representing the class names.
 */
/**
 *返回库中所有类的名称。
 *
 * @param image您正在查询的图书馆或框架。
 * @param outCount返回的类名数。
 *
 * @return表示类名的C字符串数组。
 */
OBJC_EXPORT const char **objc_copyClassNamesForImage(const char *image,
                                                     unsigned int *outCount)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);


/* Working with Selectors */

/**
 * Returns the name of the method specified by a given selector.
 *
 * @param sel A pointer of type \c SEL. Pass the selector whose name you wish to determine.
 *
 * @return A C string indicating the name of the selector.
 */
/*使用选择器*/

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
 * Returns a Boolean value that indicates whether two selectors are equal.
 *
 * @param lhs The selector to compare with rhs.
 * @param rhs The selector to compare with lhs.
 *
 * @return \c YES if \e lhs and \e rhs are equal, otherwise \c NO.
 *
 * @note sel_isEqual is equivalent to ==.
 */
/**
 *返回一个布尔值，指示两个选择器是否相等。
 *
 * @param lhs与rhs进行比较的选择器。
 * @param rhs与lhs进行比较的选择器。
 *
 * @return \ c如果\ e lhs和\ e rhs相等，否则\ c否。
 *
 * @note sel_isEqual等效于==。
 */
OBJC_EXPORT BOOL sel_isEqual(SEL lhs, SEL rhs)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);


/* Objective-C Language Features */

/**
 * This function is inserted by the compiler when a mutation
 * is detected during a foreach iteration. It gets called
 * when a mutation occurs, and the enumerationMutationHandler
 * is enacted if it is set up. A fatal error occurs if a handler is not set up.
 *
 * @param obj The object being mutated.
 *
 */
/* Objective-C语言特性*/

/**
 *这个功能是由编译器插入的一个突变
 *在foreach迭代期间被检测到。它被称为
 *发生突变时，和枚举MANGHANDler
 *如果设置成立。如果未设置处理程序，则会发生致命错误。
 *
 * @param obj被突变的对象。
 *
 */
OBJC_EXPORT void objc_enumerationMutation(id obj)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Sets the current mutation handler.
 *
 * @param handler Function pointer to the new mutation handler.
 */
/**
 *设置当前的突变处理程序。
 *
 * @param handler函数指向新的突变处理程序的指针。
 */
OBJC_EXPORT void objc_setEnumerationMutationHandler(void (*handler)(id))
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Set the function to be called by objc_msgForward.
 *
 * @param fwd Function to be jumped to by objc_msgForward.
 * @param fwd_stret Function to be jumped to by objc_msgForward_stret.
 *
 * @see message.h::_objc_msgForward
 */
/**
 *设置由objc_msgForward调用的函数。
 *
 * @param fwd要由objc_msgForward跳转的功能。
 * @param fwd_stret要由objc_msgForward_stret跳转到的功能。
 *
 * @see message.h :: _ objc_msgForward
 */
OBJC_EXPORT void objc_setForwardHandler(void *fwd, void *fwd_stret)
OBJC_AVAILABLE(10.5, 2.0, 9.0, 1.0);

/**
 * Creates a pointer to a function that will call the block
 * when the method is called.
 *
 * @param block The block that implements this method. Its signature should
 *  be: method_return_type ^(id self, method_args...).
 *  The selector is not available as a parameter to this block.
 *  The block is copied with \c Block_copy().
 *
 * @return The IMP that calls this block. Must be disposed of with
 *  \c imp_removeBlock.
 */
/**
 *创建一个指向调用该块的函数的指针
 *调用方法时。
 *
 * @param block实现此方法的块。它的签名应该
 * be：method_return_type ^（id self，method_args ...）。
 *选择器不可用作此块的参数。
 *块用\ c Block_copy（）复制。
 *
 * @return调用此块的IMP。必须处理
 * \ c imp_removeBlock。
 */
OBJC_EXPORT IMP imp_implementationWithBlock(id block)
OBJC_AVAILABLE(10.7, 4.3, 9.0, 1.0);

/**
 * Return the block associated with an IMP that was created using
 * \c imp_implementationWithBlock.
 *
 * @param anImp The IMP that calls this block.
 *
 * @return The block called by \e anImp.
 */
/**
 *返回与使用创建的IMP关联的块
 * \ c imp_implementationWithBlock。
 *
 * @param anImp调用此块的IMP。
 *
 * @return由\ e anImp调用的块。
 */
OBJC_EXPORT id imp_getBlock(IMP anImp)
OBJC_AVAILABLE(10.7, 4.3, 9.0, 1.0);

/**
 * Disassociates a block from an IMP that was created using
 * \c imp_implementationWithBlock and releases the copy of the
 * block that was created.
 *
 * @param anImp An IMP that was created using \c imp_implementationWithBlock.
 *
 * @return YES if the block was released successfully, NO otherwise.
 *  (For example, the block might not have been used to create an IMP previously).
 */
/**
 *从使用创建的IMP解除一个块
 * \ c imp_implementationWithBlock并释放该副本
 *已创建的块。
 *
 * @param anImp使用\ c imp_implementationWithBlock创建的IMP。
 *
 * @返回YES如果块成功释放，否则否。
 *（例如，块可能以前没有用于创建IMP）。
 */
OBJC_EXPORT BOOL imp_removeBlock(IMP anImp)
OBJC_AVAILABLE(10.7, 4.3, 9.0, 1.0);

/**
 * This loads the object referenced by a weak pointer and returns it, after
 * retaining and autoreleasing the object to ensure that it stays alive
 * long enough for the caller to use it. This function would be used
 * anywhere a __weak variable is used in an expression.
 *
 * @param location The weak pointer address
 *
 * @return The object pointed to by \e location, or \c nil if \e location is \c nil.
 */
/**
 *这将加载由弱指针引用的对象，然后返回它
 *保留和自动释放对象，以确保其保持活动
 *足够长时间让呼叫者使用它。将使用此功能
 *在表达式中使用__weak变量的任何位置。
 *
 * @param位置弱指针地址
 *
 * @return \ e位置指向的对象，如果\ e位置为\ c，则为\ c nil。
 */
OBJC_EXPORT id objc_loadWeak(id *location)
OBJC_AVAILABLE(10.7, 5.0, 9.0, 1.0);

/**
 * This function stores a new value into a __weak variable. It would
 * be used anywhere a __weak variable is the target of an assignment.
 *
 * @param location The address of the weak pointer itself
 * @param obj The new object this weak ptr should now point to
 *
 * @return The value stored into \e location, i.e. \e obj
 */
/**
 *此函数将一个新值存储到__weak变量中。它会
 *在__weak变量是作业目标的任何地方使用。
 *
 * @param location弱指针本身的地址
 * @param obj这个弱ptr的新对象现在应该指向
 *
 * @return存储到\ e位置的值，即\ e obj
 */
OBJC_EXPORT id objc_storeWeak(id *location, id obj)
OBJC_AVAILABLE(10.7, 5.0, 9.0, 1.0);


/* Associative References */

/**
 * Policies related to associative references.
 * These are options to objc_setAssociatedObject()
 */
/*关联参考*/

/**
 *与关联参考相关的政策。
 *这些是objc_setAssociatedObject（）的选项
 */
typedef OBJC_ENUM(uintptr_t, objc_AssociationPolicy) {
    /** <指定对关联对象的弱引用。 */
    OBJC_ASSOCIATION_ASSIGN = 0,           /**< Specifies a weak reference to the associated object. */
    /** <指定对关联对象的强引用。*协会不是原子的。 */
    OBJC_ASSOCIATION_RETAIN_NONATOMIC = 1, /**< Specifies a strong reference to the associated object.
                                            *   The association is not made atomically. */
    /** <指定相关对象被复制。*协会不是原子的 */
    OBJC_ASSOCIATION_COPY_NONATOMIC = 3,   /**< Specifies that the associated object is copied.
                                            *   The association is not made atomically. */
    /** <指定对相关对象的强引用。*协会是原子性的 */
    OBJC_ASSOCIATION_RETAIN = 01401,       /**< Specifies a strong reference to the associated object.
                                            *   The association is made atomically. */
    /** <指定相关对象被复制。*协会是原子性的 */
    OBJC_ASSOCIATION_COPY = 01403          /**< Specifies that the associated object is copied.
                                            *   The association is made atomically. */
};

/**
 * Sets an associated value for a given object using a given key and association policy.
 *
 * @param object The source object for the association.
 * @param key The key for the association.
 * @param value The value to associate with the key key for object. Pass nil to clear an existing association.
 * @param policy The policy for the association. For possible values, see “Associative Object Behaviors.”
 *
 * @see objc_setAssociatedObject
 * @see objc_removeAssociatedObjects
 */
/**
 *使用给定的键和关联策略设置给定对象的关联值。
 *
 * @param object关联的源对象。
 * @param key关联的关键。
 * @param value与对象的键值相关联的值。通过零以清除现有的关联。
 * @param policy该关联的策略。有关可能的值，请参阅“关联对象行为”。
 *
 * @see objc_setAssociatedObject
 * @see objc_removeAssociatedObjects
 */
OBJC_EXPORT void objc_setAssociatedObject(id object, const void *key, id value, objc_AssociationPolicy policy)
OBJC_AVAILABLE(10.6, 3.1, 9.0, 1.0);

/**
 * Returns the value associated with a given object for a given key.
 *
 * @param object The source object for the association.
 * @param key The key for the association.
 *
 * @return The value associated with the key \e key for \e object.
 *
 * @see objc_setAssociatedObject
 */
/**
 *返回与给定键的给定对象相关联的值。
 *
 * @param object关联的源对象。
 * @param key关联的关键。
 *
 * @return与\ e对象的键\ e键相关联的值。
 *
 * @see objc_setAssociatedObject
 */
OBJC_EXPORT id objc_getAssociatedObject(id object, const void *key)
OBJC_AVAILABLE(10.6, 3.1, 9.0, 1.0);

/**
 * Removes all associations for a given object.
 *
 * @param object An object that maintains associated objects.
 *
 * @note The main purpose of this function is to make it easy to return an object
 *  to a "pristine state”. You should not use this function for general removal of
 *  associations from objects, since it also removes associations that other clients
 *  may have added to the object. Typically you should use \c objc_setAssociatedObject
 *  with a nil value to clear an association.
 *
 * @see objc_setAssociatedObject
 * @see objc_getAssociatedObject
 */
/**
 *删除给定对象的所有关联。
 *
 * @param object维护关联对象的对象。
 *
 * @note这个功能的主要目的是为了方便返回一个对象
 *到“原始状态”，您不应该使用此功能进行一般删除
 *来自对象的关联，因为它还会删除其他客户端的关联
 *可能已添加到对象。通常你应该使用\ c objc_setAssociatedObject
 *用零值清除关联。
 *
 * @see objc_setAssociatedObject
 * @see objc_getAssociatedObject
 */
OBJC_EXPORT void objc_removeAssociatedObjects(id object)
OBJC_AVAILABLE(10.6, 3.1, 9.0, 1.0);


#define _C_ID       '@'
#define _C_CLASS    '#'
#define _C_SEL      ':'
#define _C_CHR      'c'
#define _C_UCHR     'C'
#define _C_SHT      's'
#define _C_USHT     'S'
#define _C_INT      'i'
#define _C_UINT     'I'
#define _C_LNG      'l'
#define _C_ULNG     'L'
#define _C_LNG_LNG  'q'
#define _C_ULNG_LNG 'Q'
#define _C_FLT      'f'
#define _C_DBL      'd'
#define _C_BFLD     'b'
#define _C_BOOL     'B'
#define _C_VOID     'v'
#define _C_UNDEF    '?'
#define _C_PTR      '^'
#define _C_CHARPTR  '*'
#define _C_ATOM     '%'
#define _C_ARY_B    '['
#define _C_ARY_E    ']'
#define _C_UNION_B  '('
#define _C_UNION_E  ')'
#define _C_STRUCT_B '{'
#define _C_STRUCT_E '}'
#define _C_VECTOR   '!'
#define _C_CONST    'r'


/* Obsolete types */
/*过时类型*/

#if !__OBJC2__

#define CLS_GETINFO(cls,infomask)        ((cls)->info & (infomask))
#define CLS_SETINFO(cls,infomask)        ((cls)->info |= (infomask))

// class is not a metaclass
#define CLS_CLASS               0x1
// class is a metaclass
#define CLS_META                0x2
// class's +initialize method has completed
#define CLS_INITIALIZED         0x4
// class is posing
#define CLS_POSING              0x8
// unused
#define CLS_MAPPED              0x10
// class and subclasses need cache flush during image loading
#define CLS_FLUSH_CACHE         0x20
// method cache should grow when full
#define CLS_GROW_CACHE          0x40
// unused
#define CLS_NEED_BIND           0x80
// methodLists is array of method lists
#define CLS_METHOD_ARRAY        0x100
// the JavaBridge constructs classes with these markers
#define CLS_JAVA_HYBRID         0x200
#define CLS_JAVA_CLASS          0x400
// thread-safe +initialize
#define CLS_INITIALIZING        0x800
// bundle unloading
#define CLS_FROM_BUNDLE         0x1000
// C++ ivar support
#define CLS_HAS_CXX_STRUCTORS   0x2000
// Lazy method list arrays
#define CLS_NO_METHOD_ARRAY     0x4000
// +load implementation
#define CLS_HAS_LOAD_METHOD     0x8000
// objc_allocateClassPair API
#define CLS_CONSTRUCTING        0x10000
// class compiled with bigger class structure
#define CLS_EXT                 0x20000


struct objc_method_description_list {
    int count;
    struct objc_method_description list[1];
};


struct objc_protocol_list {
    struct objc_protocol_list *next;
    long count;
    __unsafe_unretained Protocol *list[1];
};


struct objc_category {
    char *category_name                                      OBJC2_UNAVAILABLE;
    char *class_name                                         OBJC2_UNAVAILABLE;
    struct objc_method_list *instance_methods                OBJC2_UNAVAILABLE;
    struct objc_method_list *class_methods                   OBJC2_UNAVAILABLE;
    struct objc_protocol_list *protocols                     OBJC2_UNAVAILABLE;
}                                                            OBJC2_UNAVAILABLE;


struct objc_ivar {
    char *ivar_name                                          OBJC2_UNAVAILABLE;
    char *ivar_type                                          OBJC2_UNAVAILABLE;
    int ivar_offset                                          OBJC2_UNAVAILABLE;
#ifdef __LP64__
    int space                                                OBJC2_UNAVAILABLE;
#endif
}                                                            OBJC2_UNAVAILABLE;

struct objc_ivar_list {
    int ivar_count                                           OBJC2_UNAVAILABLE;
#ifdef __LP64__
    int space                                                OBJC2_UNAVAILABLE;
#endif
    /* variable length structure */
    struct objc_ivar ivar_list[1]                            OBJC2_UNAVAILABLE;
}                                                            OBJC2_UNAVAILABLE;


struct objc_method {
    SEL method_name                                          OBJC2_UNAVAILABLE;
    char *method_types                                       OBJC2_UNAVAILABLE;
    IMP method_imp                                           OBJC2_UNAVAILABLE;
}                                                            OBJC2_UNAVAILABLE;

struct objc_method_list {
    struct objc_method_list *obsolete                        OBJC2_UNAVAILABLE;
    
    int method_count                                         OBJC2_UNAVAILABLE;
#ifdef __LP64__
    int space                                                OBJC2_UNAVAILABLE;
#endif
    /* variable length structure */
    struct objc_method method_list[1]                        OBJC2_UNAVAILABLE;
}                                                            OBJC2_UNAVAILABLE;


typedef struct objc_symtab *Symtab                           OBJC2_UNAVAILABLE;

struct objc_symtab {
    unsigned long sel_ref_cnt                                OBJC2_UNAVAILABLE;
    SEL *refs                                                OBJC2_UNAVAILABLE;
    unsigned short cls_def_cnt                               OBJC2_UNAVAILABLE;
    unsigned short cat_def_cnt                               OBJC2_UNAVAILABLE;
    void *defs[1] /* variable size */                        OBJC2_UNAVAILABLE;
}                                                            OBJC2_UNAVAILABLE;


typedef struct objc_cache *Cache                             OBJC2_UNAVAILABLE;

#define CACHE_BUCKET_NAME(B)  ((B)->method_name)
#define CACHE_BUCKET_IMP(B)   ((B)->method_imp)
#define CACHE_BUCKET_VALID(B) (B)
#ifndef __LP64__
#define CACHE_HASH(sel, mask) (((uintptr_t)(sel)>>2) & (mask))
#else
#define CACHE_HASH(sel, mask) (((unsigned int)((uintptr_t)(sel)>>3)) & (mask))
#endif
struct objc_cache {
    unsigned int mask /* total = mask + 1 */                 OBJC2_UNAVAILABLE;
    unsigned int occupied                                    OBJC2_UNAVAILABLE;
    Method buckets[1]                                        OBJC2_UNAVAILABLE;
};


typedef struct objc_module *Module                           OBJC2_UNAVAILABLE;

struct objc_module {
    unsigned long version                                    OBJC2_UNAVAILABLE;
    unsigned long size                                       OBJC2_UNAVAILABLE;
    const char *name                                         OBJC2_UNAVAILABLE;
    Symtab symtab                                            OBJC2_UNAVAILABLE;
}                                                            OBJC2_UNAVAILABLE;

#else

struct objc_method_list;

#endif


/* Obsolete functions */
/*过时函数*/

OBJC_EXPORT IMP class_lookupMethod(Class cls, SEL sel)
__OSX_DEPRECATED(10.0, 10.5, "use class_getMethodImplementation instead")
__IOS_DEPRECATED(2.0, 2.0, "use class_getMethodImplementation instead")
__TVOS_DEPRECATED(9.0, 9.0, "use class_getMethodImplementation instead")
__WATCHOS_DEPRECATED(1.0, 1.0, "use class_getMethodImplementation instead");
OBJC_EXPORT BOOL class_respondsToMethod(Class cls, SEL sel)
__OSX_DEPRECATED(10.0, 10.5, "use class_respondsToSelector instead")
__IOS_DEPRECATED(2.0, 2.0, "use class_respondsToSelector instead")
__TVOS_DEPRECATED(9.0, 9.0, "use class_respondsToSelector instead")
__WATCHOS_DEPRECATED(1.0, 1.0, "use class_respondsToSelector instead");
OBJC_EXPORT void _objc_flush_caches(Class cls)
__OSX_DEPRECATED(10.0, 10.5, "not recommended")
__IOS_DEPRECATED(2.0, 2.0, "not recommended")
__TVOS_DEPRECATED(9.0, 9.0, "not recommended")
__WATCHOS_DEPRECATED(1.0, 1.0, "not recommended");

OBJC_EXPORT id object_copyFromZone(id anObject, size_t nBytes, void *z)
__OSX_DEPRECATED(10.0, 10.5, "use object_copy instead")
__IOS_UNAVAILABLE __TVOS_UNAVAILABLE __WATCHOS_UNAVAILABLE
OBJC_ARC_UNAVAILABLE;
OBJC_EXPORT id object_realloc(id anObject, size_t nBytes)    OBJC2_UNAVAILABLE;
OBJC_EXPORT id object_reallocFromZone(id anObject, size_t nBytes, void *z) OBJC2_UNAVAILABLE;

#define OBSOLETE_OBJC_GETCLASSES 1
OBJC_EXPORT void *objc_getClasses(void)                      OBJC2_UNAVAILABLE;
OBJC_EXPORT void objc_addClass(Class myClass)                OBJC2_UNAVAILABLE;
OBJC_EXPORT void objc_setClassHandler(int (*)(const char *)) OBJC2_UNAVAILABLE;
OBJC_EXPORT void objc_setMultithreaded (BOOL flag)           OBJC2_UNAVAILABLE;

OBJC_EXPORT id class_createInstanceFromZone(Class, size_t idxIvars, void *z)
__OSX_DEPRECATED(10.0, 10.5, "use class_createInstance instead")
__IOS_UNAVAILABLE __TVOS_UNAVAILABLE __WATCHOS_UNAVAILABLE
OBJC_ARC_UNAVAILABLE;

OBJC_EXPORT void class_addMethods(Class, struct objc_method_list *) OBJC2_UNAVAILABLE;
OBJC_EXPORT void class_removeMethods(Class, struct objc_method_list *) OBJC2_UNAVAILABLE;
OBJC_EXPORT void _objc_resolve_categories_for_class(Class cls)  OBJC2_UNAVAILABLE;

OBJC_EXPORT Class class_poseAs(Class imposter, Class original) OBJC2_UNAVAILABLE;

OBJC_EXPORT unsigned int method_getSizeOfArguments(Method m) OBJC2_UNAVAILABLE;
OBJC_EXPORT unsigned method_getArgumentInfo(struct objc_method *m, int arg, const char **type, int *offset) OBJC2_UNAVAILABLE;

OBJC_EXPORT Class objc_getOrigClass(const char *name)        OBJC2_UNAVAILABLE;
#define OBJC_NEXT_METHOD_LIST 1
OBJC_EXPORT struct objc_method_list *class_nextMethodList(Class, void **) OBJC2_UNAVAILABLE;
// usage for nextMethodList
//
// void *iterator = 0;
// struct objc_method_list *mlist;
// while ( mlist = class_nextMethodList( cls, &iterator ) )
//    ;

OBJC_EXPORT id (*_alloc)(Class, size_t)                      OBJC2_UNAVAILABLE;
OBJC_EXPORT id (*_copy)(id, size_t)                          OBJC2_UNAVAILABLE;
OBJC_EXPORT id (*_realloc)(id, size_t)                       OBJC2_UNAVAILABLE;
OBJC_EXPORT id (*_dealloc)(id)                               OBJC2_UNAVAILABLE;
OBJC_EXPORT id (*_zoneAlloc)(Class, size_t, void *)          OBJC2_UNAVAILABLE;
OBJC_EXPORT id (*_zoneRealloc)(id, size_t, void *)           OBJC2_UNAVAILABLE;
OBJC_EXPORT id (*_zoneCopy)(id, size_t, void *)              OBJC2_UNAVAILABLE;
OBJC_EXPORT void (*_error)(id, const char *, va_list)        OBJC2_UNAVAILABLE;

#endif
