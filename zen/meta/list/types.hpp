#ifndef ZEN_META_LIST_TYPES_HPP
#define ZEN_META_LIST_TYPES_HPP

#include <tuple>

namespace zen {

  /// A list of indexed types that can be instanciated at run-time.
  ///
  /// Currently, a list is just aliased to std::tuple on most platforms.
  /// This is because most standard libraries provide a very efficient
  /// implementation of this type. For example, _libc++_ leverages
  /// Clang's `__nth_element` compiler intrinsic.
  ///
  /// [1]: https://ldionne.com/2015/11/29/efficient-parameter-pack-indexing/
  ///
  template<typename ...Ts>
  using list_ = std::tuple<Ts...>;

} // of namespace zen

#endif // ZEN_META_LIST_TYPES_HPP
