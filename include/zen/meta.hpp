#ifndef ZEN_META_HPP
#define ZEN_META_HPP

#include <type_traits>

#include <array>
#include <vector>
#include <forward_list>
#include <list>
#include <deque>
#include <queue>
#include <set>

#include "zen/macros.h"

namespace zen {

#define ZEN_MAKE_TAG(name) struct name {};

#define ZEN_TAG(...) \
  ZEN_EACH(ZEN_MAKE_TAG, __VA_ARGS__)

  ZEN_TAG(_);

  template<std::size_t N>
  struct type_binder : std::integral_constant<std::size_t, N> {};

#define ZEN_DECLARE_TYPE_BINDER(n) \
  struct _ ## n : type_binder<n> {};

  ZEN_FOR(10, ZEN_DECLARE_TYPE_BINDER);

  template<typename T>
  struct is_type_binder : std::false_type {};

  template<std::size_t N>
  struct is_type_binder<type_binder<N>> : std::true_type {};

  template<typename T1, typename ...Ts>
  struct has_type_binder  {
    static constexpr const bool value = is_type_binder<T1>::value || has_type_binder<Ts...>::value;
  };

  template<typename T>
  struct is_lambda_expr : std::false_type {};

  template<template<typename ...> class K, typename ...Ts>
  struct is_lambda_expr<K<Ts...>> : has_type_binder<Ts...>;

  template<typename P, typename R, typename T>
  struct set_at;

  template<std::size_t N, typename R, typename T>
  struct set_tuple_element;

  template<typename R, typename T1, typename ...Ts>
  struct set_tuple_element<0, R, std::tuple<T1, Ts...>> {
    using type = std::tuple<R, Ts...>;
  };


  template<typename P, typename R, typename Ts>
  struct set_at<P, R, std::tuple<Ts...>> {
    using type = std::tuple
  };


  template<std::size_t I, std::size_t K, typename ParamTs, typename ArgTs>
  struct apply_lambda_helper {
    static_assert(I == std::tuple_size_v<ParamTs> && I < std::tuple_size_v<ArgTs>, "too many arguments provided to lambda expression");
    static_assert(I == std::tuple_size_v<ParamTs> && I > std::tuple_size_v<ArgTs>, "too few arguments provided to lambda expression");
    using param_type = std::tuple_element_t<I, ParamTs>;
    using type = cond_t<
        case_t<std::is_same_v<param_type, _>, apply_lambda_helper<I+1, K+1, set_at<I, ParamTs, std::tuple_element_t<K, ArgTs>>,
        >;
  };

  template<typename ParamTs, typename ArgTs>
  struct apply_lambda_helper<std::tuple_size_v<ParamTs>

  template<std::size_t N, typename ...ArgTs>
  struct apply_lambda_helper<type_binder<N>, ArgTs...> {
    static_assert(N < std::tuple_size_v<ArgTs...>, "too many arguments provided to lambda expresssion");
    using type = std::tuple_element<N, std::tuple<ArgTs...>>;
  };

  template<typename Fn, typename ...ArgTs>
  struct apply_lambda;

  template<template<typename ...> class K, typename ...Ts, typename ...ArgTs>
  struct apply_lambda<K<Ts...>, ArgTs...> {
    using type = K<apply_lambda_helper<0, 0, std::tuple<Ts...>, std::tuple<ArgTs...>>::type>>;
  };

  template<typename H, typename ...Ts>
  constexpr auto cons(H head, std::tuple<Ts...> tail) {
    return std::tuple_cat(head, tail);
  };

  template<typename H, typename T>
  struct cons_helper;

  template<typename H, typename ...Ts>
  struct cons_helper<H, std::tuple<Ts...>> {
    using type = std::tuple<H, Ts...>;
  };

  template<typename H, typename T>
  using cons_t = typename cons_helper<H, T>::type;

  template<typename H, typename T>
  struct rcons_helper;

  template<typename H, typename ...Ts>
  struct rcons_helper<H, std::tuple<Ts...>> {
    using type = std::tuple<H, Ts...>;
  };

  template<typename H, typename T>
  using rcons_t = typename rcons_helper<H, T>::type;

  template<template<typename ElementT> class Fn, typename Seq>
  struct map_type;

  template<template<typename T> class Fn, typename ...Ts>
  struct map_type<Fn, std::tuple<Ts...>> {
    using type = std::tuple<Fn<Ts>...>;
  };

  template<typename T>
  using get_value_type = typename T::value_type;

  template <typename T, typename = void>
  struct is_container : std::false_type {};

  template<typename T, std::size_t N> 
  struct is_container<std::array<T, N>> : std::true_type {};

  template<typename T, typename Allocator> 
  struct is_container<std::forward_list<T, Allocator>> : std::true_type {};

  template<typename T, typename Allocator> 
  struct is_container<std::vector<T, Allocator>> : std::true_type {};

  template<typename T, typename Allocator> 
  struct is_container<std::deque<T, Allocator>> : std::true_type {};

  template<typename T, typename Allocator> 
  struct is_container<std::list<T, Allocator>> : std::true_type {};


  template< class Key, class Compare, class Allocator >
  struct is_container<std::set<Key, Compare, Allocator>> : std::true_type {};

  template<typename T>
  using is_container_v = typename is_container<T>::value;

  template <typename T, typename = void>
  struct is_range : std::false_type {};

  template <typename T>
  struct is_range<T,
      std::void_t<
           decltype(std::declval<T&>().begin()),
           decltype(std::declval<T&>().end()),
           typename T::value_type
         >>
      : std::true_type {};

  template<typename T>
  using is_range_v = typename is_range<T>::value;

  template<typename Range, typename Fn, typename OutIt>
  inline typename std::invoke_result<Fn(typename Range::value_type)>::type transform(Range range, Fn transformer, OutIt out) {
    for (auto& element: range) {
      *out = transformer(element);
    }
  }

  // template<typename F, typename S>
  // inline constexpr F first(std::pair<F, S> pair) {
  //   return pair.first;
  // }

  template<typename Container>
  std::back_insert_iterator<Container> default_inserter(Container& container) {
    return std::back_inserter(container);
  }

  template<typename T, typename R, typename Enabler = void>
  struct converter;

  template<typename T, typename R>
  struct converter<T, R, typename std::enable_if_t<is_container<R>::value && is_range<T>::value>> {
    static R apply(T value) {
      R result;
      std::copy(value.begin(), value.end(), default_inserter(result));
      return result;
    }
  };

  template<typename T, typename R, std::size_t N>
  struct converter<const T[N], R, std::enable_if_t<is_container<R>::value>>  {
    static R apply(const T array[N]) {
      return R { array, array + N };
    }
  };

  template<typename R>
  struct converter<const char*, R, std::enable_if_t<is_container<R>::value>> {
    static R apply(const char* str) {
      R result;
      for (const char* ptr = str; *ptr != '\0'; ++ptr) {
        // FIXME should be generalised for other containers such as sets
        result.push_back(*ptr);
      }
      return result;
    }
  };

  template<typename R>
  struct converter<const char16_t*, R, std::enable_if_t<is_container<R>::value>> {
    static R apply(const char16_t* str) {
      R result;
      for (const char16_t* ptr = str; *ptr != '\0'; ++ptr) {
        // FIXME should be generalised for other containers such as sets
        result.push_back(*ptr);
      }
      return result;
    }
  };

  template<typename R>
  struct converter<const char32_t*, R, std::enable_if_t<is_container<R>::value>> {
    static R apply(const char32_t* str) {
      R result;
      for (const char32_t* ptr = str; *ptr != '\0'; ++ptr) {
        // FIXME should be generalised for other containers such as sets
        result.push_back(*ptr);
      }
      return result;
    }
  };

  template<typename R, typename T>
  R into(T value) {
    return converter<T, R>::apply(value);
  }

  template<typename T, typename Enabler = void>
  struct is_pointer : std::false_type {};

  template<typename T>
  struct is_pointer<T, std::enable_if_t<std::is_pointer<T>::value>> : std::true_type {};

  template<typename T>
  struct is_pointer<std::shared_ptr<T>> : std::true_type {};

  template<typename T>
  struct is_pointer<std::unique_ptr<T>> : std::true_type {};

  template<typename T>
  inline constexpr bool is_pointer_v = is_pointer<T>::value;

  template<typename T, typename Enabler = void>
  struct is_nullable : std::false_type {};

  template<typename T>
  struct is_nullable<T, typename std::enable_if_t<is_pointer<T>::value>> : std::true_type {};

  template<typename T>
  inline constexpr bool is_nullable_v = is_nullable<T>::value;

  template<typename T, typename Enabler = void>
  struct empty_holder;

  template<typename T>
  struct empty_holder<T, std::enable_if_t<is_pointer<T>::value>> {
    inline static const T value = nullptr;
  };

  struct empty {};

  template<typename T>
  inline constexpr T make_empty() {
    return empty_holder<T>::value;
  }

  template<typename T, typename Enabler = void>
  struct cloner {
    static void apply(const T& value) {
      return T(value);
    }
  };

  template<typename T>
  struct cloner<T, std::enable_if_t<is_pointer<T>::value>> {
    static T apply(const T& value) {
      using R = std::remove_pointer_t<T>;
      return T(new R(*value));
    }
  };

  template<typename T>
  T clone(const T& value) {
    return cloner<T>::apply(value);
  }

}

#endif // ZEN_META_HPP
