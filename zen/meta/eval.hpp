#ifndef ZEN_META_EVAL_HPP
#define ZEN_META_EVAL_HPP

#include <tuple>

#include "zen/meta/common.hpp"
#include "zen/meta/primitives.hpp"
#include "zen/meta/list/types.hpp"

namespace zen {

  template<typename T, typename EnvT = list_<>>
  struct eval_;

  template<typename T, typename EnvT = list_<>>
  using eval_t = typename eval_<T, EnvT>::type;

  template<typename T>
  struct compile_;

  template<typename T>
  using compile_t = typename compile_<T>::type;

  template<typename TestT, typename ThenT, typename ElseT>
  struct if_ {};

  template<typename TestT, typename ThenT>
  struct case_ {
    using test_type = TestT;
    using then_type = ThenT;
  };

  template<typename ThenT>
  using else_ = case_<true_, ThenT>;

  template<typename ...CaseTs>
  struct cond_ {
    static_assert(sizeof...(CaseTs) > 0, "a conditional must contain at least one case");
  };

  template<typename Fn, typename ArgL>
  struct apply_;

  template<typename Fn, typename ...Ts> 
  struct apply_<Fn, list_<Ts...>> {};

  template<template<typename ...> class TemplateT, typename ...ArgTs>
  using call_ = apply_<template_<TemplateT>, list_<ArgTs...>>;

  template<typename T>
  struct fail_helper_ {};

  using fail_ = fail_helper_<true_>;

  template<typename T, typename ArgTs>
  struct subst_binders_ {
    using type = T;
  };

  template<typename T>
  struct lambda_ {};

  template<typename ...CaseTs>
  struct compile_cond_helper_;

  template<>
  struct compile_cond_helper_<> {
    using type = fail_;
  };

  template<typename CaseT, typename ...CaseTs>
  struct compile_cond_helper_<CaseT, CaseTs...> {
    using type = if_<typename CaseT::test_type, typename CaseT::then_type, typename compile_cond_helper_<CaseTs...>::type>;
  };

  template<typename T>
  struct compile_ {
    using type = T;
  };

  template<typename ...CaseTs>
  struct compile_<cond_<CaseTs...>> {
    using type = typename compile_cond_helper_<CaseTs...>::type;
  };

  template<template<typename ...> class T, typename ...Ts>
  struct compile_<T<Ts...>> {
    using type = T<compile_t<Ts>...>;
  };

  template<typename T, typename EnvT>
  struct eval_ {
    using type = T;
  };

  // template<std::size_t I, typename EnvT>
  // struct eval_<arg_n_<I>, EnvT> {
  //   using type = std::tuple_element_t<I, EnvT>;
  // };

  template<typename EnvT, bool B, typename ThenT, typename ElseT>
  struct eval_if_helper_ {
    using type = eval_t<ThenT, EnvT>;
  };

  template<typename EnvT, typename ThenT, typename ElseT>
  struct eval_if_helper_<EnvT, false, ThenT, ElseT> {
    using type = eval_t<ElseT, EnvT>;
  };

  template<typename EnvT, typename TestT, typename ThenT, typename ElseT>
  struct eval_<if_<TestT, ThenT, ElseT>, EnvT> {
    using type = typename eval_if_helper_<EnvT, eval_t<TestT, EnvT>::value, ThenT, ElseT>::type;
  };

  template<typename EnvT, typename T>
  struct eval_<lambda_<T>, EnvT> {
    using type = eval_t<T, EnvT>;
  };

  template<typename EnvT, template<typename ...> class T, typename ...Ts>
  struct eval_<T<Ts...>, EnvT> {
    using type = eval_t<typename T<eval_t<Ts, EnvT>...>::type, EnvT>;
  };

  template<typename EnvT, typename T>
  struct eval_<fail_helper_<T>, EnvT> {
    static_assert(!T::value, "failed to evaluate expression");
  };

  // template<typename ArgTs, std::size_t K>
  // struct subst_binder_<_, ArgTs, K> {
  //   using replacement_type = std::tuple_element_t<K, ArgTs>;
  //   static constexpr std::size_t next_arg_index = K+1;
  // };


  // template<std::size_t K, typename ArgListT, template <typename ...> class T, typename ...Ts>
  // struct subst_binders_<T<Ts...>, ArgListT, K> {
  //   struct type {
  //     template<typename ...ArgTs>
  //     using apply = T<subst_binders_t<Ts, ArgListT, K>...>;
  //   };
  // };
  // 
  // template<typename EnvT, typename FnT, typename ...ArgTs>
  // struct eval_<apply_<FnT, list_<ArgTs...>>, EnvT> {
  // private:
  //   using func_type = typename subst_binders_<FnT, list_<ArgTs...>>::type;
  // public:
  //   using type = eval_t<
  //     typename func_type::template apply<eval_t<ArgTs, EnvT>...>,
  //     EnvT
  //   >;
  // };

  template<typename EnvT, typename FnT, typename ...ArgTs>
  struct eval_<apply_<FnT, list_<ArgTs...>>, EnvT> {
    using type = eval_t<typename FnT::template apply<eval_t<ArgTs, EnvT>...>::type, EnvT>;
  };

  template<typename T>
  // using defun_t = eval_t<compile_t<lambda_<typename subst_binders_<T, list_<ArgTs...>>::type>>>;
  using defun_t = eval_<compile_t<lambda_<T>>>;

} // of namespace zen

#endif // ZEN_META_EVAL_HPP
