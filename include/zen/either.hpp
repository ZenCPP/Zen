#ifndef ZEN_EITHER_HPP
#define ZEN_EITHER_HPP

#include <memory>
#include <cstdlib>
#include <type_traits>
#include <exception>

#include "zen/config.hpp"
#include "zen/box.hpp"
#include "zen/maybe.hpp"

namespace zen {

  // template<typename T> struct Left  : public Box<T> { };
  // template<typename T> struct Right : public Box<T> { };

  ZEN_DEFINE_BOXED_TYPE(Left);
  ZEN_DEFINE_BOXED_TYPE(Right);

  template<typename T> Left<T> left(T val) { return { val }; }
  template<typename T> Right<T> right(T val) { return { val }; }

  template<typename L, typename R>
  class Either {

    union {
      Box<L> _left;
      Box<R> _right;
    };

    bool _isLeft;

  public:

    using LeftT = L;
    using RightT = R;

    template<typename LT>
    Either(Left<LT> left): _isLeft(true), _left(left.value) {}

    template<typename RT>
    Either(Right<RT> right): _isLeft(false), _right(right.value) {}

    Either(const Either<L, R>& oth): _isLeft(oth._isLeft) {
      if (_isLeft) {
        _left = oth._left;
      } else {
        _right = oth._right;
      }
    }

    Either(Either<L, R>&& oth): _isLeft(oth._isLeft) {
      if (_isLeft) {
        _left = std::move(oth._left);
      } else {
        _right = std::move(oth._right);
      }
    }

#if ZEN_EXCEPTIONS_ENABLED
    R unwrap() {
      if (_isLeft) {
        throw _left;
      }
      return _right;
    }
#endif

//     L getLeft() { 
// #ifndef NDEBUG
//       assert(_isLeft);
// #endif
//       return _left; 
//     }
// 
//     L getRight() { 
// #ifndef NDEBUG
//       assert(_isLeft);
// #endif
//       return _right;
//     }

    static Either<L, R> fromLeft(L left) {
      return Left<L>(left);
    }

    static Either<L, R> fromRight(R right) {
      return Right<R>(right);
    }

    Maybe<L> left() const { 
      if (!_isLeft)
        return {};
      return Some<L>(_left);
    }

    Maybe<R> right() const { 
      if (_isLeft)
        return {};
      return Some<R>(_right);
    }

    template<typename F>
    Either<typename std::invoke_result<F,L>::type, R> mapLeft(F const& f) {
      using Mapped = Either<typename std::invoke_result<F,L>::type, R>;
      return _isLeft ? Mapped::fromLeft(f(_left.value())) : Mapped::fromRight(_right.value());
    }

    template<typename F>
    Either<L, typename std::invoke_result<F,R>::type> mapRight(F const& f) {
      using Mapped = Either<L, typename std::invoke_result<F,R>::type>;
      return _isLeft ? Mapped::fromLeft(_left.value()) : Mapped::fromRight(f(_right.value()));
    }

    inline bool isRight() const { return !_isLeft; }
    inline bool isLeft() const { return _isLeft; }

    ~Either() {
      if (_isLeft) {
        _left.~Box<L>();
      } else {
        _right.~Box<R>();
      }
    }

  };

  template<typename T>
  using Result = Either<std::exception, T>;

}

#endif // ZEN_EITHER_HPP

