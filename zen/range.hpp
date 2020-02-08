#ifndef ZEN_RANGE_HPP
#define ZEN_RANGE_HPP

#include <type_traits>

namespace zen {

  template <typename T, typename = void>
  struct is_range_ : std::false_type {};

  template <typename T>
  struct is_range_<T,
      std::void_t<
           decltype(std::declval<T&>().begin()),
           decltype(std::declval<T&>().end()),
           typename T::value_type
         >>
      : std::true_type {};

  template<typename T>
  using is_range_v = typename is_range_<T>::value;

  template<typename Range, typename Fn, typename OutIt>
  inline typename std::invoke_result<Fn(typename Range::value_type)>::type transform(Range range, Fn transformer, OutIt out) {
    for (auto& element: range) {
      *out = transformer(element);
    }
  }

} // of namespace zen

#endif // ZEN_RANGE_HPP
