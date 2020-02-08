#ifndef ZEN_LIST_HPP
#define ZEN_LIST_HPP

#include <tuple>

#include "zen/macros.h"
#include "zen/meta/sequence.hpp"
#include "zen/meta/list/iterator.hpp"

namespace zen {

  template<typename ...Ts>
  struct begin_impl_<list_<Ts...>> {
    using type = list_iterator_t<list_<Ts...>, 0>;
  };

  template<typename I, typename R, typename ...Ts>
  struct set_nth_impl_<list_<Ts...>, I, R> {
    using type = set_tuple_element_helper_t<I::value, R, list_<Ts...>>;
  };

} // namespace zen

#endif // ZEN_LIST_HPP
