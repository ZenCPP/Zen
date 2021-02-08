#ifndef ZEN_MAYBE_HPP
#define ZEN_MAYBE_HPP

#include <utility>

#include "zen/macros.h"

namespace zen {

  struct Empty {};

  template<typename T>
  class Maybe {

    bool has_value;

    union {
      T value;
    };

  public:

    inline Maybe():
      has_value(false) {}

    inline Maybe(Empty):
      has_value(false) {}

    inline Maybe(T&& value):
      has_value(true), value(std::move(value)) {}

    inline Maybe(T& value):
      has_value(true), value(value) {}

    inline Maybe(const Maybe<T>& other):
      has_value(other.has_value) {
        if (other.has_value) {
          new(&value)T(other.value);
        }
      }

    inline Maybe(Maybe<T>&& other):
      has_value(std::move(other.has_value)) {
        if (other.has_value) {
          new(&value)T(std::move(other.value));
        }
      }

    template<typename T2>
    inline Maybe(const Maybe<T2>& other):
      has_value(other.has_value) {
        if (other.has_value) {
          value = other.value;
        }
      }

    template<typename T2>
    inline Maybe(Maybe<T2>&& other):
      has_value(std::move(other.has_value)) {
        if (has_value) {
          value = std::move(other.value);
        }
      }

    Maybe<T>& operator=(const Maybe<T>& other) {
      has_value = other.has_value;
      if (has_value) {
        value = other.value;
      }
      return *this;
    }

    Maybe<T>& operator=(Maybe<T>&& other) {
      has_value = std::move(other.has_value);
      if (has_value) {
        new(&value)T(std::move(other.value));
      }
      other.has_value = false;
      return *this;
    }


    inline bool is_some() const {
      return has_value;
    }

    inline bool is_empty() const {
      return !has_value;
    }

    T& operator*() {
      ZEN_ASSERT(has_value);
      return value;
    }

    T& unwrap() {
      if (!has_value) {
        ZEN_PANIC("trying to unwrap a zen::maybe that has no value");
      }
      return value;
    }

    ~Maybe() {
      if (has_value) {
        value.~T();
      }
    }

  };

  template<typename T>
  constexpr Maybe<T> some(T& value) {
    return value;
  }

  template<typename T>
  constexpr Maybe<T> some(T&& value) {
    return Maybe<T> { std::move(value) };
  }

}

#endif // of #ifndef ZEN_MAYBE_HPP
