Welcome
=======

Welcome to the Zen C++ libraries. The Zen C++ libraries strive to be
well-tested and modern support libraries for serious C++ programming.
Zen++ draws many ideas from other programming languages, most notably
[Rust][1] and [Haskell][2].

The sources of the libraries are freely available on [GitHub][3]. Anyone is
welcome to contribute his or her code to the libraries, as long as you remain
respectful and understand that not all code gets autoamatically accepted.

[1]: http://rust-lang.org/
[2]: https://www.haskell.org/
[3]: https://github.com/ZenCPP/ZenCPP

## Getting Started

Zen++ is a header-only library. This might change in the future, but we'll make
sure to let you know and update this guide accordingly.  Right now, you don't
need to do anything else than [downloading the source code][4] and exctract the
`include/zen` folder to one of your include directories.

[4]: https://github.com/ZenCPP/zen-doxygen-theme/archive/master.zip

## Advanced Usage

### Metaprogramming With C Macros

Zen++ comes shipped with some very powerful [macros][5] and hacks for
automatically generating code. They have been gathered from several places, and
have been tested to work on the standard list of compilers. These macros should
cover almost all use-cases, and if you're finding yourself missing one, you can
always [open up a pull request][6].

The following example demonstrates a macro that counts the arguments that are
given to it:

```
ZEN_VA_LENGTH(a, b, c, d) // evaluates to 4
```

This might not seem very useful, but it gets more interesting when the
arguments come from another macro:

```
#define DECLARE_INT_ARRAY(...) static const int[ZEN_VA_LENGTH(__VA_ARGS__)] = { __VA_ARGS__ };

DECLARE_INT_ARRAY(a, b, c, d)
```

Of course, in the previous example we could just omit the array size from the
declaration. However there are cases when this macro is extremely useful.

[5]: macros_8h.html
[6]: https://github.com/ZenCPP/ZenCPP/pulls

