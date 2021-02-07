#ifndef ZEN_MAYBE_HPP
#define ZEN_MAYBE_HPP

#include <utility>

#include "zen/macros.h"

namespace zen {

  template<typename T>
  class maybe {

    bool has_value;

    union {
      T value;
    };

  public:

    inline maybe():
      has_value(false) {}

    inline maybe(T&& value):
      has_value(true), value(std::move(value)) {}

    inline maybe(T& value):
      has_value(true), value(value) {}

    inline maybe(const maybe<T>& other):
      has_value(other.has_value) {
        if (other.has_value) {
          new(&value)T(other.value);
        }
      }

    inline maybe(maybe<T>&& other):
      has_value(std::move(other.has_value)) {
        if (other.has_value) {
          new(&value)T(std::move(other.value));
        }
      }

    template<typename T2>
    inline maybe(const maybe<T2>& other):
      has_value(other.has_value) {
        if (other.has_value) {
          value = other.value;
        }
      }

    template<typename T2>
    inline maybe(maybe<T2>&& other):
      has_value(std::move(other.has_value)) {
        if (has_value) {
          value = std::move(other.value);
        }
      }

    maybe<T>& operator=(const maybe<T>& other) {
      has_value = other.has_value;
      if (has_value) {
        value = other.value;
      }
      return *this;
    }

    maybe<T>& operator=(maybe<T>&& other) {
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

    ~maybe() {
      if (has_value) {
        value.~T();
      }
    }

  };

  template<typename T>
  constexpr maybe<T> some(T& value) {
    return value;
  }

  template<typename T>
  constexpr maybe<T> some(T&& value) {
    return maybe<T> { std::move(value) };
  }

}

#endif // of #ifndef ZEN_MAYBE_HPP
