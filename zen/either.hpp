/// \file zen/either.hpp
/// \brief Encapsulation for computations that may fail.
///
/// A common idiom is to use the type defined in this header on functions that
/// can fail, as an alternatve to exception handling. Some hold that this is a
/// good practice for several reasons:
///
/// - Absence of `throw`-statements may allow compilers to better reason
///   about your program, possibly resulting in faster code.
/// - Consumers of your API know immediately that a function might fail, and have to 
///   deal with it explicitly.
/// - Because the exception is encoded in the type, some bugs can be captured at
///   compile-time that might otherwise be more subtle.
///
/// ### Working With Computations That May Fail
///
/// Often, you find yourself interfacing with external systems, such as a network
/// service or the file system. Doing operations on these objects can result in
/// failures, e.g. an `ENOENT` returned from a call to `stat()`.
///
/// In C, it is very common to store the actual result in one of the function's
/// parameters and return an error code, like so:
///
/// ```c
/// int read_some(const char* filename, char* output) {
///   int fd, error;
///   fd = open(in, O_RDONLY);
///   if (fd < 0) {
///     return -1;
///   }
///   error = read(fd, output, 4);
///   if (error < 0) {
///     return -1;
///   }
///   return 0;
/// }
/// ```
///
/// In C++ another common idiom is returning a `nullptr` whenever a heap-allocated
/// object could not be created. These approaches have obvious drawbacks. In the
/// case of returning an error code instead of the result, we have to make sure our
/// variable can be kept as a reference, leading to more code.
///
/// The generic solution to this problem is to introduce a new type, called
/// `Either`, that can hold both a result and an error code, without wasting
/// precious memory. This is exactly what `zen::Either<L, R>` was made for.
///
/// ```cpp
/// Either<int, std::string> writeSome(std::string filename) {
///   int fd = open(in, O_RDONLY);
///   if (fd < 0) {
///     return zen::left(-1)
///   }
///   char buf[4];
///   read(fd, buf, 4);
///   return zen::right(std::string(output, 4));
/// }
/// ```
///
/// We can further improve upon our code snippet by declaring an `enum` that lists
/// all possible errors that might occur. The errors might even be full classes
/// using virtual inheritance; something which we'll see later on.
///
/// ```cpp
/// enum class Error {
///   OpenFailed,
///   ReadFailed,
/// }
///
/// Either<int, std::string> writeSome(std::string filename) {
///   int fd = open(in, O_RDONLY);
///   if (fd < 0) {
///     return zen::left(Error::OpenFailed)
///   }
///   char buf[4];
///   if (read(fd, buf, 4) < 0) {
///     return zen::left(Error::ReadFailed)
///   }
///   return zen::right(std::string(output, 4));
/// }
/// ```
///
/// Finally, we encapsulate our error type in a custom `Result`-type that will be
/// used thoughout our application:
///
/// ```cpp
/// template<typename T>
/// using Result = Either<Error, T>;
/// ```
///
/// That's it! You've learned how to write simple C++ code the Zen way!

#ifndef ZEN_EITHER_HPP
#define ZEN_EITHER_HPP

#include <type_traits>
#include <utility>

#include "zen/macros.h"

namespace zen {

  template<typename L>
  struct Left {
    L value;
    inline Left(L value): value(std::move(value)) {};
  };

  template<typename R>
  struct Right {
    R value;
    inline Right(R&& value): value(std::move(value)) {};
    inline Right(const R& value): value(value) {};
  };

  template<>
  struct Right<void> {};

  template<typename L, typename R>
  class Either {

    template<typename L2, typename R2>
    friend
    class either;

    struct dummy {};

    union {
      L left_value;
      R right_value;
    };

    bool has_right_v;

  public:

    template<typename L2>
    inline Either(Left<L2>&& value): left_value(std::move(value.value)), has_right_v(false) {};

    template<typename R2>
    inline Either(Right<R2>&& value): right_value(std::move(value.value)), has_right_v(true) {};

    Either(Either &&other) : has_right_v(std::move(other.has_right_v)) {
      if (has_right_v) {
        new(&right_value)R(std::move(other.right_value));
      } else {
        new(&left_value)L(std::move(other.left_value));
      }
    }

//    either(const either &other) : has_right_v(other.has_right_v) {
//      if (has_right_v) {
//        new(&right_value)R(other.right_value);
//      } else {
//        new(&left_value)L(other.left_value);
//      }
//    }

    template<typename L2, typename R2>
    Either(Either<L2, R2>&& other): has_right_v(std::move(other.has_right_v)) {
      if (has_right_v) {
        new(&right_value)R(std::move(other.right_value));
      } else {
        new(&left_value)L(std::move(other.left_value));
      }
    }

    template<typename L2, typename R2>
    Either(const Either<L2, R2> &other): has_right_v(other.has_right_v) {
      if (has_right_v) {
        new(&right_value)R(other.right_value);
      } else {
        new(&left_value)L(other.left_value);
      }
    }

    Either<L, R>& operator=(const Either<L, R>& other) {
      if (has_right_v) {
        new(&right_value)R(other.right_value);
      } else {
        new(&left_value)L(other.left_value);
      }
      return *this;
    }

    Either<L, R>& operator=(Either<L, R>&& other) {
      if (has_right_v) {
        new(&right_value)R(std::move(other.right_value));
      } else {
        new(&left_value)L(std::move(other.left_value));
      }
      return *this;
    }

    R* operator->() {
      ZEN_ASSERT(has_right_v);
      return &right_value;
    }

    R &operator*() {
      ZEN_ASSERT(has_right_v);
      return right_value;
    }

    bool is_left() { return !has_right_v; }

    bool is_right() { return has_right_v; }

    R unwrap() {
      if (!has_right_v) {
        ZEN_PANIC("trying to unwrap a zen::either which is left-valued");
      }
      return right_value;
    }

    L &left() {
      ZEN_ASSERT(!has_right_v);
      return left_value;
    }

    R &right() {
      ZEN_ASSERT(has_right_v);
      return right_value;
    }

    ~Either() {
      if (has_right_v) {
        right_value.~R();
      } else {
        left_value.~L();
      }
    }

  };

  template<typename L>
  class Either<L, void> {

    struct dummy {};

    union {
      L left_value;
    };

    bool has_left;

  public:

    inline Either(Left<L> data): left_value(data.value), has_left(true) {};
    inline Either(Right<void>): has_left(false) {};

    Either(Either&& other): has_left(other.has_left) {
      if (other.has_left) {
        left_value = std::move(other.data.left);
      }
    }

    Either(const Either& other): has_left(other.has_left) {
      if (other.has_left) {
        left_value = other.data.left;
      }
    }

    bool is_left() { return has_left; }
    bool is_right() { return !has_left; }

    L& left() {
      ZEN_ASSERT(has_left);
      return left_value;
    }

    ~Either() {
      if (has_left) {
        left_value.~L();
      }
    }

  };

  template<typename L>
  Left<L> left(L& value) {
    return Left<L> { value };
  }

  template<typename L>
  Left<L> left(L&& value) {
    return Left<L> { std::move(value) };
  }

  /// Construct a right-valued either type that has no contents.
  inline Right<void> right() {
    return Right<void> {};
  }

  template<typename R>
  Right<R> right(R& value) {
    return Right<R> { value };
  }

  template<typename R>
  Right<R> right(R&& value) {
    return Right<R> { std::move(value) };
  }

#define ZEN_TRY(value) \
  { \
    if (value.is_left()) { \
      return ::zen::left(std::move(value.left())); \
    } \
  }

#define ZEN_TRY2(expr) \
  { \
    auto zen__either__result = (expr); \
    if (zen__either__result.is_left()) { \
      return ::zen::left(std::move(zen__either__result.left())); \
    } \
  }

#define ZEN_UNWRAP(value) \
  if (value.is_left()) { \
    ZEN_PANIC("unwrapping a left-valued object"); \
  }

} // of namespace zen

#endif // ZEN_EITHER_HPP
