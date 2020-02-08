#ifndef ZEN_META_LAMBDA_HPP
#define ZEN_META_LAMBDA_HPP

#include <type_traits>
#include <tuple>

#include "zen/meta/primitives.hpp"
#include "zen/meta/common.hpp"
#include "zen/meta/eval.hpp"
#include "zen/meta/list/types.hpp"

namespace zen {

  struct _ {};

  template<std::size_t I>
  struct arg_n_ {};

  using _1 = arg_n_<0>;
  using _2 = arg_n_<1>;
  using _3 = arg_n_<2>;
  using _4 = arg_n_<3>;
  using _5 = arg_n_<4>;
  using _6 = arg_n_<5>;
  using _7 = arg_n_<6>;
  using _8 = arg_n_<7>;
  using _9 = arg_n_<8>;

  template<typename T>
  struct is_type_binder : false_ {};

  template<std::size_t N>
  struct is_type_binder<arg_n_<N>> : true_ {};

  template<typename ...Ts>
  struct has_type_binder : std::false_type {};

  template<typename T1, typename ...Ts>
  struct has_type_binder<T1, Ts...>  {
    static constexpr const bool value = is_type_binder<T1>::value || has_type_binder<Ts...>::value;
  };

  template<typename T>
  struct is_lambda_expr_ : false_ {};

  template<template<typename ...> class K, typename ...Ts>
  struct is_lambda_expr_<K<Ts...>> : has_type_binder<Ts...> {};

  template<std::size_t I, std::size_t K, typename ParamTs, typename ArgTs>
  struct substitute_parameters_ : 
    defun_t <
        cond_<
            case_<
              bool_<I == std::tuple_size_v<ParamTs>>,
              ParamTs
            >,
            case_<
              std::is_same<std::tuple_element_t<I, ParamTs>, _>,
              substitute_parameters_<I+1, K+1, set_tuple_element_helper_t<I, std::tuple_element_t<K, ArgTs>, ParamTs>, ArgTs>
            >,
            case_<
              true_,
              substitute_parameters_<I+1, K, ParamTs, ArgTs>
            >
          >
        > {};

  // template<std::size_t N, typename ...ArgTs>
  // struct apply_helper<type_binder<N>, ArgTs...> {
  //   static_assert(N < std::tuple_size_v<ArgTs...>, "too many arguments provided to lambda expresssion");
  //   using type = std::tuple_element<N, std::tuple<ArgTs...>>;
  // };

  template<template<typename ...> class Fn, typename T>
  struct apply_sequence;

  template<template <typename ...> class Fn, typename ...Ts>
  struct apply_sequence<Fn, std::tuple<Ts...>> {
    using type = Fn<Ts...>;
  };

  template<template<typename ...> class Fn, typename T>
  using apply_sequence_t = typename apply_sequence<Fn, T>::type;

  template<typename Fn, typename ...ArgTs>
  struct apply_lambda_;

  template<template<typename ...> class Fn, typename ...ParamTs, typename ...ArgTs>
  struct apply_lambda_<Fn<ParamTs...>, ArgTs...> {
    using type = apply_sequence_t<
      Fn, 
      typename substitute_parameters_<
          0,
          0,
          std::tuple<ParamTs...>,
          std::tuple<ArgTs...>
        >::type
      >;
  };

  template<typename Fn, typename ...ArgTs>
  using apply_lambda_t = typename apply_lambda_<Fn, ArgTs...>::type;

} // of namespace zen

#endif // ZEN_META_LAMBDA_HPP
