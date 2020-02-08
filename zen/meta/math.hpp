#ifndef ZEN_META_MATH_HPP
#define ZEN_META_MATH_HPP

#include <type_traits>

#include "zen/meta/common.hpp"
#include "zen/meta/primitives.hpp"
#include "zen/meta/eval.hpp"

namespace zen {

  template<typename T1, typename T2, typename = void>
  struct eq_impl_ : false_ {};

  template<typename T>
  struct eq_impl_<T, T> : true_ {};

  template<typename T1, typename T2>
  using eq_ = eq_impl_<T1, T2>;

  // template<typename Ns...>
  // struct mult_ {
  //   using type = fold_<mult_acc_helper_, list_<Ns...>, 0>;
  // };

  template<typename T1, typename T2>
  struct mult_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T1, mult_);
  };

  template<typename T1, typename T2, T1 N1, T2 N2>
  struct mult_impl_<std::integral_constant<T1, N1>, std::integral_constant<T2, N2>>{
    using type = std::integral_constant<widen_t<T1, T2>, N1 * N2>;
  };

  template<typename T1, typename T2>
  using mult_ = mult_impl_<T1, T2>;

  template<typename T1, typename T2>
  using mult_t = typename mult_<T1, T2>::type;

  template<typename T>
  struct dec_impl_ {
    using type = std::integral_constant<typename T::value_type, T::value - 1>;
  };

  template<typename T>
  using dec_ = dec_impl_<T>;
  
  template<typename T>
  using dec_t = typename dec_<T>::type;

  template<typename T>
  struct inc_impl_ {
    using type = std::integral_constant<typename T::value_type, T::value + 1>;
  };

  template<typename T>
  using inc_ = inc_impl_<T>;

  template<typename T>
  using inc_t = typename inc_<T>::type;

  template<typename N>
  struct fac_ : defun_t<
     cond_<
      case_<eq_<N, u0_>, u1_>,
      case_<eq_<N, u1_>, u1_>,
      else_<mult_<call_<fac_, dec_<N>>, N>>
    >
  > {}; 

  template<typename N>
  using fac_t = typename fac_<N>::type;

} // of namespace zen


#endif // ZEN_META_MATH_HPP
