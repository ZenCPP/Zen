#ifndef ZEN_CLONE_HPP
#define ZEN_CLONE_HPP

#include <algorithm>
#include <utility>

#include "zen/meta.hpp"

ZEN_NAMESPACE_START

using size_t = std::size_t;

/// \brief Custom logic for cloning a specific type.
template<typename T, typename Enabler = void>
struct Clone {

  static_assert(!std::is_rvalue_reference_v<T>, "it is not possible to clone an r-value reference (hint: you can simply use the value directly)");

  static T apply(const T& value) {
    return T(value);
  }

};

/// \brief Make an exact copy of the given value in a new memory location.
template<typename T>
T clone(const T& value) {
  return Clone<T>::apply(value);
}

/// \brief Non-trivial conversions from one type to another.
template<typename T, typename R, typename Enabler = void>
struct Into;

template<typename T, typename R, std::size_t N>
struct Into<const T[N], R>  {
  static R apply(const T array[N]) {
    return R { array, array + N };
  }
};

/// \brief Take an input value and produce a related value of the desired type.
template<typename R, typename T>
inline R into(T value) {
  return Into<T, R>::apply(value);
}

#if ZEN_STL

template<typename T, typename R>
struct Into<T, R, EnableIf<IsContainer<R>::value>> {
  static R apply(T value) {
    R result;
    std::copy(value.begin(), value.end(), default_inserter(result));
    return result;
  }
};

#endif

ZEN_NAMESPACE_END

#endif // ZEN_CLONE_HPP
