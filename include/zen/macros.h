/// \file macros.h
/// \brief Generic macros used throughout the Zen C++ libraries.
/// 
/// Zen++ comes shipped with some very powerful macros and hacks for
/// automatically generating code. They have been gathered from several places, and
/// have been tested to work on the standard list of compilers. These macros should
/// cover almost all use-cases, and if you're finding yourself missing one, you can
/// always [open up a pull request][1].
///
/// [1]: https://github.com/ZenCPP/ZenCPP/pulls
///
/// All documented macros can be used in your own code and enable
/// advanced compile-time programming. For example, the 
/// following code makes use of the ZEN_FOR_EACH macro:
///
/// ```
/// #define DECLARE_INT(i, value) int var ## i = value;
/// ZEN_FOR_EACH(DECLARE_INT, 1, 2, 3, 4)
/// ```
///
/// This snippet generates the following code at compile-time:
/// 
/// ```
/// int foo0 = 1;
/// int foo1 = 2;
/// int foo2 = 3;
/// int foo3 = 4;
/// ```
///
/// ## Macro Primer
///
/// There are two kinds of macros: object-like macros and function-like macros.
///
/// An object-like macro is a basic macro that does not contain any
/// parentheses after the name, like the following example: 
///
/// ```
/// #define FOO 42
/// ```
///
/// Function-like macros are more complex macros that, just like regular C functions, 
/// can accept a limited amount of arguments, which then will be substituted in the
/// macro's body.
///
/// ```
/// #define ASSIGN(a, b) a = b;
/// ```
///
/// Object-like macros are always expanded as soon as possible, with a few exceptions.
/// Function-like macros, on the other hand, can only be expanded when we explicitly provide
/// some arguments to it. Therefore, function-like macros are much more powerful, and are 
/// generally preferred over object-like macros when doing this kind of programming.
///
/// ## The Zen Macros
/// 
/// The following example demonstrates a macro that counts the arguments that are
/// given to it:
/// 
/// ```cpp
/// ZEN_VA_LENGTH(a, b, c, d) // evaluates to 4
/// ```
/// 
/// This might not seem very useful, but it gets more interesting when the
/// arguments come from another macro:
/// 
/// ```cpp
/// #define DECLARE_INT_ARRAY(name,...) static const int name[ZEN_VA_LENGTH(__VA_ARGS__)] = { __VA_ARGS__ };
/// 
/// DECLARE_INT_ARRAY(a, b, c, d)
/// ```
/// 
/// Of course, in the previous example we could just omit the array size from the
/// declaration. However there are cases when this macro is extremely useful.
/// 

// This file was auto-generated on Nov 03 2019 12:02:14.
//
// It is recommended not to edit this file by hand, but instead to
// tweak the generator.


#ifndef ZEN_MACRO_H
#define ZEN_MACRO_H

// The following macros were inspired Laurent Deniau's original idea
// Hattip to Yuri Solodkyy for pointing me in the right direction
// https://groups.google.com/forum/#!topic/comp.std.c/d-6Mj5Lko_s

/// Counts how many aguments are passed to this macro.
///
/// Usually, you want to call this function with some variant of `__VA_ARGS__`.
///
/// Example:
///
/// ```c
/// ZEN_STATIC_ASSERT(ZEN_VA_LENGTH(1, 2, 3, 4) == 4);
/// ```
#define ZEN_VA_LENGTH(...) ZEN_VA_LENGTH_IMPL(__VA_ARGS__,ZEN_RSEQ_N())
#define ZEN_VA_LENGTH_IMPL(...) ZEN_ARG_N(__VA_ARGS__)
#define ZEN_ARG_N(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,N,...) N
#define ZEN_RSEQ_N() 20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1

#define ZEN_EMPTY()

/// This macro delays substitution of an object-like macro until
/// ZEN_EVAL is called.
///
#define ZEN_DEFER(...) __VA_ARGS__ ZEN_EMPTY()
#define ZEN_DEFER_2(...) __VA_ARGS__ ZEN_DEFER ()
#define ZEN_DEFER_3(...) __VA_ARGS__ ZEN_DEFER_2() ()
#define ZEN_DEFER_4(...) __VA_ARGS__ ZEN_DEFER_3() ()
#define ZEN_DEFER_5(...) __VA_ARGS__ ZEN_DEFER_4() ()
#define ZEN_DEFER_6(...) __VA_ARGS__ ZEN_DEFER_5() ()
#define ZEN_DEFER_7(...) __VA_ARGS__ ZEN_DEFER_6() ()
#define ZEN_DEFER_8(...) __VA_ARGS__ ZEN_DEFER_7() ()
#define ZEN_DEFER_9(...) __VA_ARGS__ ZEN_DEFER_8() ()
#define ZEN_DEFER_10(...) __VA_ARGS__ ZEN_DEFER_9() ()
#define ZEN_DEFER_11(...) __VA_ARGS__ ZEN_DEFER_10() ()
#define ZEN_DEFER_12(...) __VA_ARGS__ ZEN_DEFER_11() ()
#define ZEN_DEFER_13(...) __VA_ARGS__ ZEN_DEFER_12() ()
#define ZEN_DEFER_14(...) __VA_ARGS__ ZEN_DEFER_13() ()
#define ZEN_DEFER_15(...) __VA_ARGS__ ZEN_DEFER_14() ()
#define ZEN_DEFER_16(...) __VA_ARGS__ ZEN_DEFER_15() ()
#define ZEN_DEFER_17(...) __VA_ARGS__ ZEN_DEFER_16() ()
#define ZEN_DEFER_18(...) __VA_ARGS__ ZEN_DEFER_17() ()
#define ZEN_DEFER_19(...) __VA_ARGS__ ZEN_DEFER_18() ()
#define ZEN_DEFER_N(n, ...) ZEN_CONCAT(ZEN_DEFER_, n)(__VA_ARGS__)



#define ZEN_EXPAND(x) x

#define ZEN_EVAL(...) __VA_ARGS__

/// Concatenates one identifier to another. The identifiers may be
/// complex expressions, as they will be evaluated before concatenation
/// takes place.
#define ZEN_CONCAT(a, b) ZEN_CONCAT_IMPL(a, b)

#define ZEN_CONCAT_IMPL(a, b) a ## b

/// Performs a simple assertion at compile-time, with an
/// easy-to-comprehend message about what went wrong if the assertion
/// failed.
#define ZEN_STATIC_ASSERT(stmt) static_assert(stmt, "Compile-time assertion failed: " #stmt)

/// A macro to disable the 'unused variable' warning in certain compilers.
///
/// This is mainly useful in situations where a lot of variables are
/// auto-generated and it is impossible to predict which ones will be used.
/// 
/// ```
/// #define GENERATE_FOOS(n) ZEN_REPEAT(n, GENERATE_ONE_FOO)
///
/// #define GENERATE_ONE_FOO(i) \
///   int foo ## i = 42; \
///   ZEN_UNUSED(foo ## i);
/// ```
#define ZEN_UNUSED(x) (void)x;

/// Indicates how many arguments can be present in a __VA_ARG__ macro variable,
/// and as such how much arguments are supported by this library.
///
/// Note that the C++ standard currently does not specify any
/// requirements about the minimum amount of arguments that is
/// supported, and that different compilers may have very different ///
/// settings.
#define ZEN_VA_MAX_LENGH 20

#define ZEN_REPEAT_WITH_0(s,m,...)
#define ZEN_REPEAT_WITH_1(s,m,...) m(0,__VA_ARGS__)
#define ZEN_REPEAT_WITH_2(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__)
#define ZEN_REPEAT_WITH_3(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__)
#define ZEN_REPEAT_WITH_4(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__)
#define ZEN_REPEAT_WITH_5(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__) s m(4,__VA_ARGS__)
#define ZEN_REPEAT_WITH_6(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__) s m(4,__VA_ARGS__) s m(5,__VA_ARGS__)
#define ZEN_REPEAT_WITH_7(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__) s m(4,__VA_ARGS__) s m(5,__VA_ARGS__) s m(6,__VA_ARGS__)
#define ZEN_REPEAT_WITH_8(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__) s m(4,__VA_ARGS__) s m(5,__VA_ARGS__) s m(6,__VA_ARGS__) s m(7,__VA_ARGS__)
#define ZEN_REPEAT_WITH_9(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__) s m(4,__VA_ARGS__) s m(5,__VA_ARGS__) s m(6,__VA_ARGS__) s m(7,__VA_ARGS__) s m(8,__VA_ARGS__)
#define ZEN_REPEAT_WITH_10(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__) s m(4,__VA_ARGS__) s m(5,__VA_ARGS__) s m(6,__VA_ARGS__) s m(7,__VA_ARGS__) s m(8,__VA_ARGS__) s m(9,__VA_ARGS__)
#define ZEN_REPEAT_WITH_11(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__) s m(4,__VA_ARGS__) s m(5,__VA_ARGS__) s m(6,__VA_ARGS__) s m(7,__VA_ARGS__) s m(8,__VA_ARGS__) s m(9,__VA_ARGS__) s m(10,__VA_ARGS__)
#define ZEN_REPEAT_WITH_12(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__) s m(4,__VA_ARGS__) s m(5,__VA_ARGS__) s m(6,__VA_ARGS__) s m(7,__VA_ARGS__) s m(8,__VA_ARGS__) s m(9,__VA_ARGS__) s m(10,__VA_ARGS__) s m(11,__VA_ARGS__)
#define ZEN_REPEAT_WITH_13(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__) s m(4,__VA_ARGS__) s m(5,__VA_ARGS__) s m(6,__VA_ARGS__) s m(7,__VA_ARGS__) s m(8,__VA_ARGS__) s m(9,__VA_ARGS__) s m(10,__VA_ARGS__) s m(11,__VA_ARGS__) s m(12,__VA_ARGS__)
#define ZEN_REPEAT_WITH_14(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__) s m(4,__VA_ARGS__) s m(5,__VA_ARGS__) s m(6,__VA_ARGS__) s m(7,__VA_ARGS__) s m(8,__VA_ARGS__) s m(9,__VA_ARGS__) s m(10,__VA_ARGS__) s m(11,__VA_ARGS__) s m(12,__VA_ARGS__) s m(13,__VA_ARGS__)
#define ZEN_REPEAT_WITH_15(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__) s m(4,__VA_ARGS__) s m(5,__VA_ARGS__) s m(6,__VA_ARGS__) s m(7,__VA_ARGS__) s m(8,__VA_ARGS__) s m(9,__VA_ARGS__) s m(10,__VA_ARGS__) s m(11,__VA_ARGS__) s m(12,__VA_ARGS__) s m(13,__VA_ARGS__) s m(14,__VA_ARGS__)
#define ZEN_REPEAT_WITH_16(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__) s m(4,__VA_ARGS__) s m(5,__VA_ARGS__) s m(6,__VA_ARGS__) s m(7,__VA_ARGS__) s m(8,__VA_ARGS__) s m(9,__VA_ARGS__) s m(10,__VA_ARGS__) s m(11,__VA_ARGS__) s m(12,__VA_ARGS__) s m(13,__VA_ARGS__) s m(14,__VA_ARGS__) s m(15,__VA_ARGS__)
#define ZEN_REPEAT_WITH_17(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__) s m(4,__VA_ARGS__) s m(5,__VA_ARGS__) s m(6,__VA_ARGS__) s m(7,__VA_ARGS__) s m(8,__VA_ARGS__) s m(9,__VA_ARGS__) s m(10,__VA_ARGS__) s m(11,__VA_ARGS__) s m(12,__VA_ARGS__) s m(13,__VA_ARGS__) s m(14,__VA_ARGS__) s m(15,__VA_ARGS__) s m(16,__VA_ARGS__)
#define ZEN_REPEAT_WITH_18(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__) s m(4,__VA_ARGS__) s m(5,__VA_ARGS__) s m(6,__VA_ARGS__) s m(7,__VA_ARGS__) s m(8,__VA_ARGS__) s m(9,__VA_ARGS__) s m(10,__VA_ARGS__) s m(11,__VA_ARGS__) s m(12,__VA_ARGS__) s m(13,__VA_ARGS__) s m(14,__VA_ARGS__) s m(15,__VA_ARGS__) s m(16,__VA_ARGS__) s m(17,__VA_ARGS__)
#define ZEN_REPEAT_WITH_19(s,m,...) m(0,__VA_ARGS__) s m(1,__VA_ARGS__) s m(2,__VA_ARGS__) s m(3,__VA_ARGS__) s m(4,__VA_ARGS__) s m(5,__VA_ARGS__) s m(6,__VA_ARGS__) s m(7,__VA_ARGS__) s m(8,__VA_ARGS__) s m(9,__VA_ARGS__) s m(10,__VA_ARGS__) s m(11,__VA_ARGS__) s m(12,__VA_ARGS__) s m(13,__VA_ARGS__) s m(14,__VA_ARGS__) s m(15,__VA_ARGS__) s m(16,__VA_ARGS__) s m(17,__VA_ARGS__) s m(18,__VA_ARGS__)
#define ZEN_REPEAT_WITH(s,n,m,...) ZEN_CONCAT(ZEN_REPEAT_WITH_, n)(s,m,__VA_ARGS__)
#define ZEN_REPEAT(n,m,...) ZEN_REPEAT_WITH(,n,m,__VA_ARGS__)

#define ZEN_ENUM_IMPL_0(m,...)
#define ZEN_ENUM_IMPL_1(m,...) m(0, __VA_ARGS__)
#define ZEN_ENUM_IMPL_2(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__)
#define ZEN_ENUM_IMPL_3(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__)
#define ZEN_ENUM_IMPL_4(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__)
#define ZEN_ENUM_IMPL_5(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__) , m(4, __VA_ARGS__)
#define ZEN_ENUM_IMPL_6(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__) , m(4, __VA_ARGS__) , m(5, __VA_ARGS__)
#define ZEN_ENUM_IMPL_7(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__) , m(4, __VA_ARGS__) , m(5, __VA_ARGS__) , m(6, __VA_ARGS__)
#define ZEN_ENUM_IMPL_8(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__) , m(4, __VA_ARGS__) , m(5, __VA_ARGS__) , m(6, __VA_ARGS__) , m(7, __VA_ARGS__)
#define ZEN_ENUM_IMPL_9(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__) , m(4, __VA_ARGS__) , m(5, __VA_ARGS__) , m(6, __VA_ARGS__) , m(7, __VA_ARGS__) , m(8, __VA_ARGS__)
#define ZEN_ENUM_IMPL_10(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__) , m(4, __VA_ARGS__) , m(5, __VA_ARGS__) , m(6, __VA_ARGS__) , m(7, __VA_ARGS__) , m(8, __VA_ARGS__) , m(9, __VA_ARGS__)
#define ZEN_ENUM_IMPL_11(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__) , m(4, __VA_ARGS__) , m(5, __VA_ARGS__) , m(6, __VA_ARGS__) , m(7, __VA_ARGS__) , m(8, __VA_ARGS__) , m(9, __VA_ARGS__) , m(10, __VA_ARGS__)
#define ZEN_ENUM_IMPL_12(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__) , m(4, __VA_ARGS__) , m(5, __VA_ARGS__) , m(6, __VA_ARGS__) , m(7, __VA_ARGS__) , m(8, __VA_ARGS__) , m(9, __VA_ARGS__) , m(10, __VA_ARGS__) , m(11, __VA_ARGS__)
#define ZEN_ENUM_IMPL_13(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__) , m(4, __VA_ARGS__) , m(5, __VA_ARGS__) , m(6, __VA_ARGS__) , m(7, __VA_ARGS__) , m(8, __VA_ARGS__) , m(9, __VA_ARGS__) , m(10, __VA_ARGS__) , m(11, __VA_ARGS__) , m(12, __VA_ARGS__)
#define ZEN_ENUM_IMPL_14(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__) , m(4, __VA_ARGS__) , m(5, __VA_ARGS__) , m(6, __VA_ARGS__) , m(7, __VA_ARGS__) , m(8, __VA_ARGS__) , m(9, __VA_ARGS__) , m(10, __VA_ARGS__) , m(11, __VA_ARGS__) , m(12, __VA_ARGS__) , m(13, __VA_ARGS__)
#define ZEN_ENUM_IMPL_15(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__) , m(4, __VA_ARGS__) , m(5, __VA_ARGS__) , m(6, __VA_ARGS__) , m(7, __VA_ARGS__) , m(8, __VA_ARGS__) , m(9, __VA_ARGS__) , m(10, __VA_ARGS__) , m(11, __VA_ARGS__) , m(12, __VA_ARGS__) , m(13, __VA_ARGS__) , m(14, __VA_ARGS__)
#define ZEN_ENUM_IMPL_16(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__) , m(4, __VA_ARGS__) , m(5, __VA_ARGS__) , m(6, __VA_ARGS__) , m(7, __VA_ARGS__) , m(8, __VA_ARGS__) , m(9, __VA_ARGS__) , m(10, __VA_ARGS__) , m(11, __VA_ARGS__) , m(12, __VA_ARGS__) , m(13, __VA_ARGS__) , m(14, __VA_ARGS__) , m(15, __VA_ARGS__)
#define ZEN_ENUM_IMPL_17(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__) , m(4, __VA_ARGS__) , m(5, __VA_ARGS__) , m(6, __VA_ARGS__) , m(7, __VA_ARGS__) , m(8, __VA_ARGS__) , m(9, __VA_ARGS__) , m(10, __VA_ARGS__) , m(11, __VA_ARGS__) , m(12, __VA_ARGS__) , m(13, __VA_ARGS__) , m(14, __VA_ARGS__) , m(15, __VA_ARGS__) , m(16, __VA_ARGS__)
#define ZEN_ENUM_IMPL_18(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__) , m(4, __VA_ARGS__) , m(5, __VA_ARGS__) , m(6, __VA_ARGS__) , m(7, __VA_ARGS__) , m(8, __VA_ARGS__) , m(9, __VA_ARGS__) , m(10, __VA_ARGS__) , m(11, __VA_ARGS__) , m(12, __VA_ARGS__) , m(13, __VA_ARGS__) , m(14, __VA_ARGS__) , m(15, __VA_ARGS__) , m(16, __VA_ARGS__) , m(17, __VA_ARGS__)
#define ZEN_ENUM_IMPL_19(m,...) m(0, __VA_ARGS__) , m(1, __VA_ARGS__) , m(2, __VA_ARGS__) , m(3, __VA_ARGS__) , m(4, __VA_ARGS__) , m(5, __VA_ARGS__) , m(6, __VA_ARGS__) , m(7, __VA_ARGS__) , m(8, __VA_ARGS__) , m(9, __VA_ARGS__) , m(10, __VA_ARGS__) , m(11, __VA_ARGS__) , m(12, __VA_ARGS__) , m(13, __VA_ARGS__) , m(14, __VA_ARGS__) , m(15, __VA_ARGS__) , m(16, __VA_ARGS__) , m(17, __VA_ARGS__) , m(18, __VA_ARGS__)
#define ZEN_ENUM(n,m,...) ZEN_CONCAT(ZEN_ENUM_IMPL_, n)(m,__VA_ARGS__)

#define ZEN_GET_VA_ARG_0(arg0,...) arg0
#define ZEN_GET_VA_ARG_1(arg0, arg1,...) arg1
#define ZEN_GET_VA_ARG_2(arg0, arg1, arg2,...) arg2
#define ZEN_GET_VA_ARG_3(arg0, arg1, arg2, arg3,...) arg3
#define ZEN_GET_VA_ARG_4(arg0, arg1, arg2, arg3, arg4,...) arg4
#define ZEN_GET_VA_ARG_5(arg0, arg1, arg2, arg3, arg4, arg5,...) arg5
#define ZEN_GET_VA_ARG_6(arg0, arg1, arg2, arg3, arg4, arg5, arg6,...) arg6
#define ZEN_GET_VA_ARG_7(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,...) arg7
#define ZEN_GET_VA_ARG_8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8,...) arg8
#define ZEN_GET_VA_ARG_9(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9,...) arg9
#define ZEN_GET_VA_ARG_10(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10,...) arg10
#define ZEN_GET_VA_ARG_11(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11,...) arg11
#define ZEN_GET_VA_ARG_12(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12,...) arg12
#define ZEN_GET_VA_ARG_13(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13,...) arg13
#define ZEN_GET_VA_ARG_14(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14,...) arg14
#define ZEN_GET_VA_ARG_15(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15,...) arg15
#define ZEN_GET_VA_ARG_16(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16,...) arg16
#define ZEN_GET_VA_ARG_17(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17,...) arg17
#define ZEN_GET_VA_ARG_18(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18,...) arg18
#define ZEN_GET_VA_ARG_19(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19,...) arg19

/// Gets a specific argument from a list of arguments.
///
/// Usually, `__VA_ARGS__` is passed as the second argument to this macro.
///
/// The following example fetches the last argument in the list and
/// ignores all previous arguments except the first:
///
/// ```c
/// #define FOO(name, ...) static const int last__ ## name = ZEN_GET_VA_ARG(ZEN_PRED(ZEN_VA_LENGTH(__VA_ARGS__)), __VA_ARGS__);
/// ```
/// 
/// \see ZEN_VA_LENGTH for getting the length of `__VA_ARGS__`.
/// \see ZEN_PRED and ZEN_SUCC increasing or decreasing the argument offset.
#define ZEN_GET_VA_ARG(n,...) ZEN_CONCAT(ZEN_GET_VA_ARG_, n)(__VA_ARGS__)


#define ZEN_FOR_EACH_IMPL(i, m, ...) ZEN_FOR_EACH_IMPL2(i, m, ZEN_GET_VA_ARG(i, __VA_ARGS__))
#define ZEN_FOR_EACH_IMPL2(i, m, ...) m(i, arg)

/// The same as ZEN_FOR_EACH but the generated code fragments are seperated by \p s.
///
/// \see ZEN_FOR_EACH
#define ZEN_FOR_EACH_WITH(s, m, ...) ZEN_REPEAT_WITH(s, ZEN_VA_LENGTH(__VA_ARGS__), ZEN_FOR_EACH_IMPL, m, __VA_ARGS__)

/// Generates code fragments by applying the macro \p m to each individual argument passed to ZEN_FOR_EACH.
///
/// The macro receives an optional argument \p i that indicates the offset of the argument in the list.
///
/// ```
/// #define DECLARE_INT(i, value) int var ## i = value;
/// ZEN_FOR_EACH(DECLARE_INT, 1, 2, 3, 4)
/// ```
///
/// This snippet generates the following code at compile-time:
/// 
/// ```
/// int foo0 = 1;
/// int foo1 = 2;
/// int foo2 = 3;
/// int foo3 = 4;
/// ```
#define ZEN_FOR_EACH(m, ...) ZEN_FOR_EACH_WITH(, m, __VA_ARGS__)

/// The same as an invocation to ZEN_FOR_EACH_WITH where \p s equals a comma.
///
/// This macro exists because the parser confuses the comma for an empty argument.
///
/// \see ZEN_FOR_EACH_WITH if you need to use a seperator other than a comma.
/// \see ZEN_FOR_EACH if you require no seperators.
#define ZEN_FOR_EACH_ENUM(m, ...) ZEN_ENUM(ZEN_VA_LENGTH(__VA_ARGS__), ZEN_FOR_EACH_IMPL, m, __VA_ARGS__)


#endif // #ifndef ZEN_MACRO_H
