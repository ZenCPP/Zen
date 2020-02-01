/// \file zen/either.hpp
/// \brief Encapsulation for computations that may fail.
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

#include "zen/config.h"
#include "zen/into.hpp"

namespace zen {

  /// The base type for returning results that might contain an error
  /// object.
  ///
  /// The type holds the following union:
  /// ```
  /// union {
  ///   L left;
  ///   R right;
  /// }
  /// ```
  ///
  /// This makes sure as little memory as possible is used.kept
  ///
  /// \see zen/either.hpp for an introduction
  template<typename L, typename R>
  class Either;

#define EDEN_DEFINE_EITHER_TAG(name)                        \
  template<typename T>                                      \
  class name {                                              \
    template<typename L1, typename R1> friend class Either; \
    T value;                                                \
  public:                                                   \
    inline name(T value): value(value) {};                  \
  };

  EDEN_DEFINE_EITHER_TAG(LeftT)
  EDEN_DEFINE_EITHER_TAG(RightT)

  template<typename L, typename R>
  class Either {
  private:

    enum class Direction {
      Left,
      Right,
    };

    union DataT {

      L left;
      R right;

      DataT() {};

      DataT(LeftT<L> left): left(left.value) {};
      DataT(RightT<R> right): right(right.value) {};

      ~DataT() {}

    };

    Direction dir;
    DataT data;

  public:

    template<typename L1>
    Either(LeftT<L1> left): dir(Direction::Left), data(LeftT<L>(into<L>(left.value))) {};

    template<typename R1>
    Either(RightT<R1> right): dir(Direction::Right), data(RightT<R>(into<R>(right.value))) {};

    Either(const Either<L, R>& other): dir(other.dir) {
      switch (other.dir) {
        case Direction::Left:
          data.left = other.data.left;
          break;
        case Direction::Right:
          data.right = other.data.right;
          break;
      }
    }

    Either(Either<L, R>&& other): dir(std::move(other.dir)) {
      switch (other.dir) {
        case Direction::Left:
          data.left = std::move(other.data.left);
          break;
        case Direction::Right:
          data.right = std::move(other.data.right);
          break;
      }
    }

    bool is_left() {
      return dir == Direction::Left;
    }

    bool is_right() {
      return dir == Direction::Right;
    }

    L unwrap_left() {
      ZEN_ASSERT(dir == Direction::Left);
      return data.left;
    }

    R unwrap_right() {
      ZEN_ASSERT(dir == Direction::Right);
      return data.right;
    }

    R operator*() {
      return unwrap();
    }

    R unwrap() {
      ZEN_ASSERT(dir == Direction::Right);
      return data.right;
    }

    ~Either() {
      switch (dir) {
        case Direction::Left:
          data.left.~L();
          break;
        case Direction::Right:
          data.right.~R();
          break;
      }
    }

  };

  template<typename L>
  LeftT<L> make_left(L value) {
    return LeftT<L>(value);
  }

  template<typename R>
  RightT<R> make_right(R value) {
    return RightT<R>(value);
  }

#define EDEN_TRY(name, expr)       \
    auto name = expr;              \
    if (name.isLeft()) {           \
      return left(name.getLeft()); \
    }

  struct Left {};
  struct Right {};

} // of namespace zen

#endif // #ifndef ZEN_EITHER_HPP
