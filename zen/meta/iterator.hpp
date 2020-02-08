#ifndef ZEN_META_ITERATOR_HPP
#define ZEN_META_ITERATOR_HPP

#include "zen/meta/common.hpp"
#include "zen/meta/primitives.hpp"
#include "zen/meta/math.hpp"
#include "zen/meta/maybe/types.hpp"

namespace zen {

  template<typename N, typename IterT>
  struct prev_n_impl_;

  template<typename N, typename IterT>
  struct next_n_impl_;

  template<typename IterT>
  struct next_impl_ {
    using type = typename next_n_impl_<u1_, IterT>::type;
  };

  template<typename IterT>
  struct prev_impl_ {
    using type = typename prev_n_impl_<u1_, IterT>::type;
  };

  /// Get a pointer-like structure to the next element in a certain container.
  ///
  /// \return A maybe type that holds a pointer to the previous value if there is any.
  ///
  template<typename IterT>
  using next_ = next_impl_<IterT>;

  template<typename IterT>
  using next_t = typename next_<IterT>::type;

  /// Get a pointer-like structure to the previous element in a certain container.
  ///
  /// \return A maybe type that holds a pointer to the next value if there is any.
  template<typename IterT>
  using prev_ = prev_impl_<IterT>;

  template<typename IterT>
  using prev_t = typename prev_<IterT>::type;

  template<typename N, typename IterT>
  struct next_n_impl_ {
    using type = cond_ <
      case_<bool_<N::value == 0>, IterT>,
      case_<is_none_<IterT>, none_>,
      case_<true_, next_n_impl_<inc_<N>, next_<IterT>>>
    >;
  };

  template<typename N, typename IterT>
  struct prev_n_impl_ {
    using type = cond_<
      case_<bool_<N::value == 0>, IterT>,
      case_<is_none_<prev_<IterT>>, none_>,
      case_<true_, prev_n_impl_<dec_<N>, prev_<IterT>>>
    >;
  };

  template<typename T, typename = void>
  struct deref_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T, deref_);
  };

  template<typename T>
  using deref_ = typename deref_impl_<T>::type;

  template<typename T>
  using deref_t = typename deref_<T>::type;

} // namespace zen

#endif // ZEN_META_ITERATOR_HPP
