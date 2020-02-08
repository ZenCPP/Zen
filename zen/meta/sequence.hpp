#ifndef ZEN_META_SEQUENCE_HPP
#define ZEN_META_SEQUENCE_HPP

#include "zen/meta/primitives.hpp"
#include "zen/meta/common.hpp"

namespace zen {

  template<typename T, typename I>
  struct nth_;

  // NOTE The following is unused and thus commented out, but it might 
  //      become useful in the future.
  //
  // template<typename T, typename = void>
  // struct is_sequence_ : false_ {};
  // 
  // template<typename T>
  // struct is_sequence_<T, std::void_t<nth_<T, u0_>>> : true_ {};
  // 
  // template<typename T>
  // using is_sequence_v = typename is_sequence_<T>::value;

  template<typename T, typename I>
  struct nth_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T, nth_);
  };

  template<typename T, typename I>
  struct nth_ {
    using type = typename nth_impl_<T, I>::type;
  };

  template<typename T, typename I>
  using nth_t = typename nth_<T, I>::type; 

  template<typename T, typename I, typename R>
  struct set_nth_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T, set_nth_);
  };

  template<typename T, typename I, typename R>
  using set_nth_ = set_nth_impl_<T, I, T>;

  template<typename T, typename I, typename R>
  using set_nth_t = typename set_nth_<T, I, R>::type;

} // of namespace zen

#endif // ZEN_META_SEQUENCE_HPP
