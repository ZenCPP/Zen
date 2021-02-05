#ifndef ZEN_MAYBE_HPP
#define ZEN_MAYBE_HPP

#include <optional>

namespace zen {

  template<typename T>
  using maybe = std::optional<T>;

  template<typename T>
  constexpr zen::maybe<T> some(T& value) {
    return std::make_optional(value);
  }

  template<typename T>
  constexpr zen::maybe<T> some(T&& value) {
    return std::move(value);
  }

}

#endif // of #ifndef ZEN_MAYBE_HPP
