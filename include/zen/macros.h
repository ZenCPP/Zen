
// This file was auto-generated on Nov 02 2019 14:41:14.
//
// It is recommended not to edit this file by hand, but instead to
// tweak the generator.

/// Generic macros used throughout the Zen C++ libraries.
///
/// All documented macros can be used in your own code and enable
/// highly advanced compile-time programming,

#ifndef ZEN_MACRO_H
#define ZEN_MACRO_H

// The following macros were inspired Laurent Deniau's original idea
// Hattip to Yuri Solodkyy for pointing me in the right direction
// https://groups.google.com/forum/#!topic/comp.std.c/d-6Mj5Lko_s

#define ZEN_VA_LENGTH(...) ZEN_VA_LENGTH_IMPL(__VA_ARGS__,ZEN_RSEQ_N())
#define ZEN_VA_LENGTH_IMPL(...) ZEN_ARG_N(__VA_ARGS__)
#define ZEN_ARG_N(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,N,...) N
#define ZEN_RSEQ_N() 20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1

#define ZEN_EMPTY()

/// This macro delays substitution of an object-like macro until
/// ZEN_EVAL is called.
///
/// An object-like macro is a basic macro that does not contain any
/// parentheses after the name, like in the following example: 
///
/// ```
/// #define FOO 42
/// ```
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

/// A macro disable the 'unused variable' warning in certain compilers.
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
#define ZEN_GET_VA_ARG(n,...) ZEN_CONCAT(ZEN_GET_VA_ARG_, n)(__VA_ARGS__)


#define ZEN_FOR_EACH_IMPL(i, m, ...) ZEN_FOR_EACH_IMPL2(i, m, ZEN_GET_VA_ARG(i, __VA_ARGS__))
#define ZEN_FOR_EACH_IMPL2(i, m, ...) m(i, arg)
#define ZEN_FOR_EACH_WITH(s, m, ...) ZEN_REPEAT_WITH(s, ZEN_VA_LENGTH(__VA_ARGS__), ZEN_FOR_EACH_IMPL, m, __VA_ARGS__)
#define ZEN_FOR_EACH(m, ...) ZEN_FOR_EACH_WITH(, m, __VA_ARGS__)
#define ZEN_FOR_EACH_ENUM(m, ...) ZEN_ENUM(ZEN_VA_LENGTH(__VA_ARGS__), ZEN_FOR_EACH_IMPL, m, __VA_ARGS__)



#endif // #ifndef ZEN_MACRO_H
