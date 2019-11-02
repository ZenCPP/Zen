#!/usr/bin/env python3

import os, sys
from textwrap import dedent
from datetime import datetime

PROJECT_DIR = os.path.abspath(os.path.dirname(__file__))

def generate_macro_header(out, max_va_args=20):
    out.write(dedent("""
        // This file was auto-generated on {}.
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
    """.format(datetime.now().strftime("%b %d %Y %H:%M:%S"))))

    out.write('#define ZEN_ARG_N(')
    for i in range(0, max_va_args):
        out.write('_{},'.format(i))
    out.write('N,...) N\n')

    out.write('#define ZEN_RSEQ_N() ')
    for i in range(0, max_va_args):
        if i > 0:
            out.write(',')
        out.write(str(max_va_args-i))

    out.write(dedent("""

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
    """))

    out.write('#define ZEN_DEFER(...) __VA_ARGS__ ZEN_EMPTY()\n')
    out.write('#define ZEN_DEFER_2(...) __VA_ARGS__ ZEN_DEFER ()\n')
    for i in range(3, max_va_args):
        out.write('#define ZEN_DEFER_{}(...) __VA_ARGS__ ZEN_DEFER_{}() ()\n'.format(i, i-1))
    out.write('#define ZEN_DEFER_N(n, ...) ZEN_CONCAT(ZEN_DEFER_, n)(__VA_ARGS__)\n\n')
    out.write(dedent("""

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
        /// #define GENERATE_ONE_FOO(i) \\
        ///   int foo ## i = 42; \\
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
        #define ZEN_VA_MAX_LENGH {}

    """.format(max_va_args)))

    # ZEN_REPEAT_WITH
    for i in range(0, max_va_args):
        out.write('#define ZEN_REPEAT_WITH_{}(s,m,...)'.format(i))
        for j in range(0, i):
            if j > 0:
                out.write(' s')
            out.write(" m({},__VA_ARGS__)".format(j))
        out.write('\n')
    out.write("#define ZEN_REPEAT_WITH(s,n,m,...) ZEN_CONCAT(ZEN_REPEAT_WITH_, n)(s,m,__VA_ARGS__)\n")

    # ZEN_REPEAT
    out.write("#define ZEN_REPEAT(n,m,...) ZEN_REPEAT_WITH(,n,m,__VA_ARGS__)\n\n")

    # ZEN_ENUM
    for i in range(0, max_va_args):
        out.write('#define ZEN_ENUM_IMPL_{}(m,...)'.format(i))
        for j in range(0, i):
            if j > 0:
                out.write(' ,')
            out.write(" m({}, __VA_ARGS__)".format(j))
        out.write('\n')
    out.write("#define ZEN_ENUM(n,m,...) ZEN_CONCAT(ZEN_ENUM_IMPL_, n)(m,__VA_ARGS__)\n\n")

    # ZEN_GET_VA_ARG
    for i in range(0, max_va_args):
        out.write('#define ZEN_GET_VA_ARG_{}({},...) {}\n'.format(i, ', '.join('arg' + str(j) for j in range(0, i+1)), 'arg' + str(i)))
    out.write("#define ZEN_GET_VA_ARG(n,...) ZEN_CONCAT(ZEN_GET_VA_ARG_, n)(__VA_ARGS__)\n\n")

    # ZEN_FOR_EACH
    # ZEN_FRO_EACH_ENUM
    out.write(dedent(
        """
        #define ZEN_FOR_EACH_IMPL(i, m, ...) ZEN_FOR_EACH_IMPL2(i, m, ZEN_GET_VA_ARG(i, __VA_ARGS__))
        #define ZEN_FOR_EACH_IMPL2(i, m, ...) m(i, arg)
        #define ZEN_FOR_EACH_WITH(s, m, ...) ZEN_REPEAT_WITH(s, ZEN_VA_LENGTH(__VA_ARGS__), ZEN_FOR_EACH_IMPL, m, __VA_ARGS__)
        #define ZEN_FOR_EACH(m, ...) ZEN_FOR_EACH_WITH(, m, __VA_ARGS__)
        #define ZEN_FOR_EACH_ENUM(m, ...) ZEN_ENUM(ZEN_VA_LENGTH(__VA_ARGS__), ZEN_FOR_EACH_IMPL, m, __VA_ARGS__)


        """
    ))

    #  for i in range(0, max_va_args):
    #      out.write('#define ZEN_FOR_EACH_IMPL{i}(s,i,m,...) m(i, ZEN_GET_VA_ARG_{i}(__VA_ARGS__))\n'.format(i=i))
    #  out.write('#define ZEN_FOR_EACH_WITH(s,m,...) ZEN_FOR_EACH(ZEN_VA_LENGTH(__VA_ARGS__), __VA_ARGS__)\n')
    #  out.write('#define ZEN_FOR_EACH(m,...) ZEN_FOR_EACH_WITH(,m,__VA_ARGS__)\n\n')
    #  for i in range(1, max_va_args):
    #      out.write('#define ZEN_FOR_EACH_ENUM_{i}(i,m,...) m(i, ZEN_GET_VA_ARG_{i}(__VA_ARGS__))\n'.format(i=i))
    #  out.write('#define ZEN_FOR_EACH_ENUM_(m,...) ZEN_FOR_EACH_ENUM_(ZEN_VA_LENGTH(__VA_ARGS__), __VA_ARGS__)\n\n')

    #  for i in range(0, max_va_args):
    #      out.write('#define ZEN_PRED_{} {}\n'.format(i+1, i))
    #  out.write('#define ZEN_PRED(i) ZEN_CONCAT(ZEN_PRED_, i)\n\n')

    out.write(dedent("""
        #endif // #ifndef ZEN_MACRO_H
    """))

with open(os.path.join(PROJECT_DIR, 'include/zen/macros.h'), 'w') as out:
    generate_macro_header(out)

