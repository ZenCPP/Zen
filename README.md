Zen Base Libraries
==================

This is a set of headers that you can freely use in your own projects. It
contains some classes and utilities that are widely used in the other Zen C++
libraries.

## Installation

Currently, we recommend using the [Bazel build tool](https://bazel.build) for
both fast and secure builds.

Add the following to your `WORKSPACE`-file, usually located in the directory 
containing all of your related projects:

```
git_repository(
    name = "zen_base",
    remote = "https://github.com/ZenCPP/base",
    tag = "v0.0.1",
)
```

## Usage

### zen::Either<L, K>

`#include "zen/either.hpp"`

A type that produce one of two results depending on the given input.

A common idiom is to use this type on functions that can fail, instead of
exception handling. This is recommended for a few reasons:

 - Absence of `throw`-statements allows compilers to better reason
   about your program, possibly resulting in faster code.
 - Consumers of your API know immediately that a function might fail, and have to 
   deal with it explicitly.
 - Because the exception type is encoded in the type, some bugs can be captured at
   compile-time.

Internally, the `Either`-object will try to allocate on the stack as much as possbile,
falling back on the heap for objects that might have different layouts at runtime.

```
Either<std::string, int> sendNotification(std::string msg) {
  // ...
  if (status == E_QUEUE_FULL) {
    return left("Could not send message: the queue is full.")
  }
  return right(notificationId)
}
```

### zen::left(T val)

`#include "zen/either.hpp"`

Construct an `Either`-object with its left-hand-side initialized to the given value.

### zen::right(T val)

`#include "zen/either.hpp"`

Construct an `Either`-object with its right-hand-side initialized to the given value.

## License

This library is licensed under the very permissive MIT license, in the hope
that it will be usefull to other developers. Giving credit to the developers
behind it is always much appreciated.

    Copyright <YEAR> <COPYRIGHT HOLDER>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

