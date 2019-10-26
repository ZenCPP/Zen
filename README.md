Zen C++ Libraries
=================

The Zen C++ libraries are a set of C++ headers that you can freely use in your
own projects. The libraries try to fill missing pieces in the existing C++
ecosystem, based on ideas taken from Haskell and Rust.

🧪 These headers are experimental and currently require a modern compiler
supporting a modern C++ standard.

## Examples

Say we have the following types defined:

```cpp
class Shape {

  virtual ~Shape() {};

  // ...

};

class Rect : public Shape {

  Rect(std::size_t width, std::size_t height);

  ~Shape() {  }

   // ...

};

class Triangle : public Shape {

  Triangle(std::size_t side1, std::size_t side2, std::size_t side3);

  ~Triangle() {  }

  // ...

};
```

The `zen::ValuePtr`-type allows you to pass arbitrary values between different functions by-value.

```cpp
zen::ValuePtr<Shape> my_shape = zen::make_value_ptr<Rect>(4, 6);
```

The pattern matching facilities allow you to very efficiently check the kind of object you're holding:

```cpp
Match (*my_shape) {
  Case (C<Rect>()) {
    std::cerr << "I am holding a rectangle!" << std::endl;
    break;
  }
  Case (C<Triangle>()) {
    std::cerr << "I am holding a triangle!" << std::endl;
    break;
  }
}
```

Using the `zen::Either`-type, we can safely express computations that can fail:

```cpp
enum class MyError {
  SomeCheckHasFailed,
}

template<typename T>
using MyResult = zen::Either<MyError, T>;

MyResult<int> computation_that_may_fail() {
  if (some_check_that_may_fail) {
    return zen::left(MyError::SomeCheckHasFailed);
  }
  return zen::right(42);
}
```

Combining these facilities, we can write some very powerful code:

```cpp
MyResult<zen::ValuePtr<Shape>> another_computation_that_may_fail() {
  Match (computation_that_may_fail()) {
    Case (C<zen::Left>(error))
      return zen::make_left(error);
    Case (C<zen::Right>(result)) {
      return zen::make_right(zen::make_value_ptr<Rect>(result, result * 2));
    }
  }
}

```

## Installation and Usage 

Currently, the preferred method for using these libraries is by downloading a
release tarball and checking in the sources into your project (e.g. in a folder
called `third_party/zen`).

## Coding standard

We try to adhere to the [C++ Core Guidelines][1], which are recommended by the
Standard C++ Foundation. As a rule of thumb, we use the following conventions:

 - Functions are written in snake-case.
 - Library types have their first letter capitalised to distinguish them from
   the standard library types.
 - Indentation is consistently 2 spaces over the entire code base.

[1]: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

## API Reference

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

```cpp
zen::Either<std::string, int> send_notification(std::string msg) {
  // ...
  if (status == E_QUEUE_FULL) {
    return zen::left("Could not send message: the queue is full.")
  }
  return right(...)
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
that it will be useful to other developers. Giving credit to the developers
behind it is always much appreciated.

See [the LICENSE file][1] for more information.

[2]: https://github.com/ZenCPP/ZenCPP/blob/master/LICENSE

