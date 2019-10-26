#ifndef ZEN_EITHER_HPP
#define ZEN_EITHER_HPP

#include <type_traits>
#include <utility>

#include "zen/config.h"
#include "zen/into.hpp"

namespace zen {

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
  public:

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

    template<typename L1>
    Either(LeftT<L1> left): dir(Direction::Left), data(LeftT<L>(IntoType<L1>::template apply<L>(left.value))) {};

    template<typename R1>
    Either(RightT<R1> right): dir(Direction::Right), data(RightT<R>(IntoType<R1>::template apply<R>(right.value))) {};

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
