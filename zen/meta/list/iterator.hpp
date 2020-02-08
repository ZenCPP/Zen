#ifndef ZEN_META_LIST_ITERATOR_HPP
#define ZEN_META_LIST_ITERATOR_HPP

#include "zen/meta/iterator.hpp"
#include "zen/meta/list/types.hpp"

namespace zen {

  template<typename ListT, std::size_t I>
  struct list_iterator_t {
    static constexpr const std::size_t index = I;
    using container_type = ListT;
  };

  template<typename N, typename ListT, std::size_t I> 
  struct next_n_impl_<N, list_iterator_t<ListT, I>> {
    using type = std::conditional_t < 
      I + N::value >= std::tuple_size<ListT>::value,
      none_,
      list_iterator_t<ListT, I+N::value>
    >;
  };

  template<typename N, typename ListT, std::size_t I>
  struct prev_n_impl_<N, list_iterator_t<ListT, I>> {
    using type = std::conditional_t <
      N::value < I,
      list_iterator_t<ListT, I - N::value>,
      none_
    >;
  };

} // of namespace zen

#endif // ZEN_META_LIST_ITERATOR_HPP
