#ifndef ZEN_STL_HPP
#define ZEN_STL_HPP

#include "zen/meta.hpp"
#include "zen/common.hpp"
#include "zen/range.hpp"

ZEN_NAMESPACE_START

template <typename T, typename = void>
struct is_container_ : false_ {};

template<typename T, typename R>
struct Into<T, R, typename std::enable_if_t<is_container_<R>::value, typename is_range_<T>::value>> {
  static R apply(T value) {
    R result;
    std::copy(value.begin(), value.end(), default_inserter(result));
    return result;
  }
};

ZEN_NAMESPACE_END

#endif // ZEN_STL_HPP
