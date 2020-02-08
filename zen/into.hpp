/// \file zen/into.hpp
/// \brief Non-trivial conversion from one type to another.
/// 
/// This file defines `zen::into`, which is an intelligent converter taking an
/// input value and producing a related value of the desired type.
///
#ifndef ZEN_INTO_HPP
#define ZEN_INTO_HPP

#include <algorithm>

#include "zen/range.hpp"
#include "zen/meta/std_extras.hpp"

namespace zen {

  template<typename T, typename R, typename Enabler = void>
  struct converter;

  template<typename T, typename R>
  struct converter<T, R, typename std::enable_if_t<is_container_<R>::value, is_range_<T>::value>> {
    static R apply(T value) {
      R result;
      std::copy(value.begin(), value.end(), default_inserter(result));
      return result;
    }
  };

  template<typename T, typename R, std::size_t N>
  struct converter<const T[N], R>  {
    static R apply(const T array[N]) {
      return R { array, array + N };
    }
  };

  template<typename R, typename T>
  inline R into(T value) {
    return converter<T, R>::apply(value);
  }

} // of namesapce zen

#endif // ZEN_INTO_HPP
