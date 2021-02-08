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

  /// @brief A range derived from two STL iterators
  ///
  /// This wrapper type enables passing down an iterator pair to other
  /// functions in a single parameter.
  template<typename IterT>
  class IterRange {
  public:

    using Iter = IterT;
    using Value = typename IterT::value_type;

    using value_type = Value;

  private:

    Iter begin_iter;
    Iter end_iter;

  public:

    inline IterRange(Iter begin_iter, Iter end_iter):
      begin_iter(begin_iter), end_iter(end_iter) {}

    inline Iter begin() {
      return begin_iter;
    }

    inline Iter end() {
      return end_iter;
    }

  };

  template<typename IterT>
  inline IterRange<IterT> make_iter_range(IterT begin, IterT end) {
    return IterRange<IterT> { begin, end };
  }

} // of namespace zen

#endif // ZEN_RANGE_HPP
