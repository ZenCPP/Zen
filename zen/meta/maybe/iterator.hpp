#ifndef ZEN_META_MAYBE_ITERATOR_HPP
#define ZEN_META_MAYBE_ITERATOR_HPP

#include <type_traits>

#include "zen/meta/iterator.hpp"
#include "zen/meta/range.hpp"
#include "zen/meta/maybe/types.hpp"

namespace zen {

  template<typename MaybeT, bool IsBeyond>
  struct maybe_iterator_t {
    static constexpr const bool is_beyond = IsBeyond;
    using container_type = MaybeT;
  };

  template<typename MaybeT>
  struct next_impl_<maybe_iterator_t<MaybeT, false>> {
    using type = some_<maybe_iterator_t<MaybeT, true>>;
  };

  template<typename MaybeT>
  struct next_impl_<maybe_iterator_t<MaybeT, true>> {
    using type = none_;
  };

  template<typename MaybeT>
  struct prev_impl_<maybe_iterator_t<MaybeT, true>> {
    using type = some_<maybe_iterator_t<MaybeT, false>>;
  };

  template<typename MaybeT>
  struct prev_impl_<maybe_iterator_t<MaybeT, false>> {
    using type = none_;
  };

  template<typename T>
  struct begin_impl_<some_<T>> {
    using type = maybe_iterator_t<some_<T>, false>;
  };

  template<>
  struct begin_impl_<none_> {
    using type = maybe_iterator_t<none_, false>;
  };

  template<typename T>
  struct end_impl_<some_<T>> {
    using type = maybe_iterator_t<some_<T>, true>;
  };

  template<>
  struct end_impl_<none_> {
    using type = maybe_iterator_t<none_, true>;
  };

} // of namespace zen

#endif // ZEN_META_MAYBE_ITERATOR_HPP
