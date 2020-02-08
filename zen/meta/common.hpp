#ifndef ZEN_META_COMMON_HPP
#define ZEN_META_COMMON_HPP

#include <type_traits>
#include <utility>

#include "zen/macros.h"

namespace zen {

/// Creates a type that is suitable for being used as an unique identifier in
/// calls to certain template metafunctions.
#define ZEN_TAG(name) struct name {}

  template<typename ...Ts>
  struct static_assert_helper : std::false_type {};

  /// Will cause a compile-time error message to be displayed to the developer.
  ///
  /// The message will depend on the instanciation of whatever parameter
  /// that was passed to it. This is useful when you want to add a custom
  /// error message to certain temlate specializations.
  ///
  /// ```
  /// // ...
  ///
  /// template<typename T>
  /// template is_a_cool_num {
  ///   ZEN_INSTANCIATION_ERROR(T, "Sorry, we can't determine if your number is cool or not.",);
  /// };
  ///
  /// template<>
  /// struct is_a_cool_num<666> : std::false_type {};
  ///
  /// template<>
  /// struct is_a_cool_num<42> : std::true_type {};
  /// ```
#define ZEN_MISSING_IMPLEMENTATION(type, name) \
static_assert(static_assert_helper<type>::value, "could not find an implementation for the metafuntion zen::" #name)

  // template<typename T>
  // struct type_traits {
  //   ZEN_INSTANCIATION_ERROR(T, "Could not deduce any type traits that are needed for the given algorithm to work.");
  // };

  // template<typename T>
  // struct get_tag_type {
  //   ZEN_INSTANCIATION_ERROR(T, "Could not deduce the meta tag type of the provided type.");
  // };


  template<typename T>
  struct constant_ {
    using type = T;
  };

  template<typename T1, typename T2>
  struct widen_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T1, widen_);
  };

  /// Derives a type that can hold both \p T1 and \p T2.
  //
  /// For example, widening an `int` and a `long` will result in a 
  /// `long`, since a `long`, by definition, can hold all integers.
  ///
  template<typename T1, typename T2>
  struct widen_ {
    using type = typename widen_impl_<T1, T2>::type;
  };

  template<typename T>
  struct widen_<T, T> {
    using type = T;
  };

  template<typename T1, typename T2>
  using widen_t = typename widen_<T1, T2>::type;

  template<typename AccFn, typename InitT, typename SeqT>
  struct fold_ {
    using type = InitT;
  };

  template<typename AccFn, typename InitT, typename T1, typename ...Ts>
  struct fold_<AccFn, InitT, std::tuple<T1, Ts...>> {
    using type = typename AccFn::template apply<T1, typename fold_<AccFn, InitT, Ts...>::type>::type;
  };


#define ZEN_MAKE_TYPENAME(i) typename ZEN_PASTE_2(T, i)
#define ZEN_MAKE_TYPEREF(i) ZEN_PASTE_2(T, i)

  template<std::size_t I, typename R, typename TupleT>
  struct set_tuple_element_helper_;

#define ZEN_MAKE_TUPLE_SETTER(index) \
  template<typename R , ZEN_JOIN_ENUM(ZEN_INC(index), ZEN_MAKE_TYPENAME) , typename ...Ts> \
  struct set_tuple_element_helper_<index, R, std::tuple<ZEN_JOIN_ENUM(ZEN_INC(index), ZEN_MAKE_TYPEREF) , Ts...>> { \
    using type = std::tuple<ZEN_FOR_ENUM(index, ZEN_MAKE_TYPEREF) R, Ts...>; \
  };

  ZEN_MAKE_TUPLE_SETTER(0);
  ZEN_MAKE_TUPLE_SETTER(1);
  ZEN_MAKE_TUPLE_SETTER(2);
  ZEN_MAKE_TUPLE_SETTER(4);
  ZEN_MAKE_TUPLE_SETTER(5);
  ZEN_MAKE_TUPLE_SETTER(6);
  ZEN_MAKE_TUPLE_SETTER(7);
  ZEN_MAKE_TUPLE_SETTER(8);
  ZEN_MAKE_TUPLE_SETTER(9);

  template<std::size_t I, typename R, typename TupleT>
  using set_tuple_element_helper_t = typename set_tuple_element_helper_<I, R, TupleT>::type;

} // of namespace zen

#endif // ZEN_META_COMMON_HPP
