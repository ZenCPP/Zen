#ifndef ZEN_LINKED_LIST_HPP
#define ZEN_LINKED_LIST_HPP

#include <utility>

#include "zen/empty.hpp"
#include "zen/meta/maybe/types.hpp"
#include "zen/meta/iterator.hpp"
#include "zen/meta/range.hpp"

namespace zen {

  struct nil_ {};

  template<typename HeadT, typename TailT>
  using cons_ = std::pair<HeadT, TailT>;

  template<typename HeadT, typename TailT>
  struct begin_impl_<cons_<HeadT, TailT>> {
    using type = cons_<HeadT, TailT>;
  };

  template<>
  struct begin_impl_<nil_> {
    using type = nil_;
  };

  template<typename HeadT, typename TailT>
  struct end_impl_<cons_<HeadT, TailT>> {
    using type = nil_;
  };

  template<>
  struct end_impl_<nil_> {
    using type = nil_;
  };

} // of namespace zen

#endif // ZEN_LINKED_LIST_HPP
