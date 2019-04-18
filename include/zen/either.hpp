#ifndef ZEN_EITHER_HPP
#define ZEN_EITHER_HPP

#include <memory>
#include <cstring>
#include <type_traits>

#include "zen/config.hpp"

namespace zen {

  template<typename T>
  struct Value {
    T value;
    Value(T val): value(val) {};
  };

  template<typename T> 
  struct Left  : public Value<T> {
    Left(T val): Value<T>(val) {}
  };

  template<typename T> 
  struct Right : public Value<T> {
    Right(T val): Value<T>(val) {}
  };

  template<typename T> Left<T> left(T val) { return { val }; }
  template<typename T> Right<T> right(T val) { return { val }; }

  /// A box allows stack-allocated objects to be passed around
  /// as a supertype without loss of information.
  template<typename T>
  class Box {

    void* buf;

  public:

    template<typename R>
    Box(R val): buf(std::malloc(sizeof(R))) {
      std::memcpy(buf, reinterpret_cast<char*>(&val), sizeof(T));
    }

    operator T&() {
      return value();
    }

    T& value() {
      return *reinterpret_cast<T*>(buf);
    }

    const T& value() const {
      return *reinterpret_cast<T*>(buf);
    }

    ~Box() {
      reinterpret_cast<T*>(buf)->~T();
      delete buf;
    }

  };

  template<typename L, typename R>
  class Either {

    template<typename T>
    using StorageT = typename std::conditional<std::is_polymorphic<T>::value, Box<T>, T>::type;

    using StorageL = StorageT<L>;
    using StorageR = StorageT<R>;

    union Value {

      StorageT<L> left;
      StorageT<R> right;

      template<typename LT>
      Value(Left<LT> left): left(left.value) {}

      template<typename RT>
      Value(Right<RT> right): right(right.value) {}

      ~Value() {}

    } value;

    bool isLeft;

  public:

    template<typename LT>
    Either(Left<LT> left): isLeft(true), value(left) {}

    template<typename RT>
    Either(Right<RT> right): isLeft(true), value(right) {}

#if ZEN_EXCEPTIONS_ENABLED
    void unwrap() {
      if (isLeft) {
        throw value.left;
      }
    }
#endif

    ~Either() {
      if (isLeft) {
        value.left.~StorageL();
      } else {
        value.right.~StorageR();
      }
    }

  };

}

#endif // ZEN_EITHER_HPP
