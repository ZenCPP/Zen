/**
 * @file  zen/meta.hpp
 * @brief Templates and types for rapid compile-time programming.
 *
 * The Zen++ metaprogramming library is a stand-alone library that may be used
 * to speed up the development of compex templates, type traits and other
 * metafunctions. Using this library, you can write template code in a lazily
 * evaluatated, purely functinonal language such as Haskell.
 *
 * The Zen++ metaprogramming library comes shipped with a comprehensive set of
 * pre-defined metafunctions that you can use to build more complex logic.
 * Examples include `foldl_` for performing a MapReduce, `take_` for taking the
 * first N elements of a sequence, and `permute_` for generating all
 * permutations of a given set of elements.
 *
 * @defgroup MetaPrimitives Template metaprogramming primitives
 * @brief Primitive types that are valid arguments to Zen++ template metafunctions.
 *
 * In order to both ease the development of the Zen++ metaprogramming library
 * and to simplify the design of the library, Zen++ defines some primitive
 * types that can easily be constructed from other types and expressions.
 * These types generally are the only primitive types that can be passed to a
 * Zen++ template metafunctionn. For example, instead of passing a `template
 * <typename ...> class T` as an argument, users of this library should use the
 * `template_` metafunction to lift the argument to a Zen++ primitive.
 *
 * ```
 * // Wrong: will throw a compile-time error
 * static_assert(zen::eq_v<zen::at_<1, zen::list_t<int, float, bool>>, float>);
 *
 * // Correct: 1 is lifted to a Zen++ meta-primitive
 * static_assert(zen::eq_v<zen::at_<u_<1>, zen::list_t<int, float, bool>>, float>);
 *
 * // Preffed because it is a bit easier to read
 * static_assert(zen::eq_v<zen::at_<u1_, zen::list_t<int, float, bool>>, float>);
 * ```
 *
 * @defgroup MetaContainers Containers for template metaprogramming
 * @brief Compile-time structures that allow storing an arbitrary amount of types
 *
 * When doing complex template metaprogramming, often the need arises to
 * operate on collections of types. For instance, when defining a custom
 * `variant`, you might want to store the variant types in a vector so that
 * a single type in the variant can easily be retrieved by index. The Zen++
 * template metaprogramming library offers a comprehensive set of types to
 * make it very easy to store types in some kind of structure.
 *
 * @defgroup MetaLang Template metaprogramming meta-language
 * @brief A dedicated template meta-language that makes writing templates easier than ever
 *
 * The Zen++ template meta-language is a type-level programming language that
 * makes writing custom tempalte logic much easier. Templates that make use
 * of this language generally use `defun_t` to tell the compiler that it
 * should evaluate an expression that is written in this language.
 *
 * @defgroup MetaMaybe The Maybe-type
 * @brief Types and metafunctions for working with types that might be empty.
 *
 * The maybe-type is an important abstraction that is returned by many
 * metafunctions that are defined in this library. The maybe-type is
 * comparable to `std::optional`, but works solely on the type system.
 * Therefore, by the time the compiler has finished processing your source,
 * you should know exactly whether a certain maybe-type has a value
 * associated with it.
 */

#ifndef ZEN_META_HPP
#define ZEN_META_HPP

#include <type_traits>
#include <tuple>

// TODO  Make more metafunctions accept a parameter pack
// FIXME std::tuple and list_t are essentially the same, which makes one wonder
//       how both types can be implemented using the same template
// FIXME The same issue persists in eval_<call_<...>, EnvT>. How do we tell the
//       compiler to just use the type 'next up'? Do we use std::enable_if_t or
//       do we use tag dispatching?

namespace zen {

  /**
   * @ingroup MetaPrimitives
   * @brief A type that holds a simple boolean value.
   *
   * Right now, `bool_` is aliased to `std::integral_constant`, but this
   * should be considered an implementation detail. More specifically, your
   * code should only rely on the following invariants:
   * 
   * - `bool_<B>::value` is defined and resolves to whatever value the type was instanciated with.
   * - `bool<B>::type` is defined and contains a reference to an instance of the same type.
   */
  template<bool B>
  using bool_ = std::integral_constant<bool, B>;

  /**
   * @ingroup MetaPrimitives
   * @brief A transparent boolean type that holds a value that is always true.
   * 
   * This value is the type-level equivalent of the constant expression `true`
   * that may be used in programming code at run-time.
   */
  using true_ = bool_<true>;

  /**
   * @ingroup MetaPrimitives
   * @brief A transparent boolean type that holds a value that is always false.
   *
   * This value is the type-level equivalent of the constant expression `true`
   * that may be used in programming code at run-time.
   */

  using false_ = bool_<false>;

  /**
   * @ingroup MetaPrimitives
   * @brief A type that can hold any natural number that fits into one memory cell.
   */
  template<std::size_t I>
  using u_ = std::integral_constant<std::size_t, I>;

  /**
   * @ingroup MetaPrimitives
   * @brief The type-level equivalent of the natural number `0`.
   */
  using u0_ = u_<0>;
  /**
   * @ingroup MetaPrimitives
   * @brief The type-level equivalent of the natural number `1`.
   */
  using u1_ = u_<1>;
  /**
   * @ingroup MetaPrimitives
   * @brief The type-level equivalent of the natural number `2`.
   */
  using u2_ = u_<2>;
  /**
   * @ingroup MetaPrimitives
   * @brief The type-level equivalent of the natural number `3`.
   */
  using u3_ = u_<3>;
  /**
   * @ingroup MetaPrimitives
   * @brief The type-level equivalent of the natural number `4`.
   */
  using u4_ = u_<4>;
  /**
   * @ingroup MetaPrimitives
   * @brief The type-level equivalent of the natural number `5`.
   */
  using u5_ = u_<5>;
  /**
   * @ingroup MetaPrimitives
   * @brief The type-level equivalent of the natural number `6`.
   */
  using u6_ = u_<6>;
  /**
   * @ingroup MetaPrimitives
   * @brief The type-level equivalent of the natural number `7`.
   */
  using u7_ = u_<7>;
  /**
   * @ingroup MetaPrimitives
   * @brief The type-level equivalent of the natural number `8`.
   */
  using u8_ = u_<8>;
  /**
   * @ingroup MetaPrimitives
   * @brief The type-level equivalent of the natural number `9`.
   */
  using u9_ = u_<9>;

  /**
   * @ingroup MetaPrimitives
   * @brief A type that can hold any whole number that fits into one memory cell.
   */
  template<std::ptrdiff_t D>
  using s_ = std::integral_constant<std::ptrdiff_t, D>;

  using s0_ = s_<0>;
  using s1_ = s_<1>;
  using s2_ = s_<2>;
  using s3_ = s_<3>;
  using s4_ = s_<4>;
  using s5_ = s_<5>;
  using s6_ = s_<6>;
  using s7_ = s_<7>;
  using s8_ = s_<8>;
  using s9_ = s_<9>;

  /**
   * @ingroup MetaPrimitives
   * @brief Lift a C++ template metafunction into a Zen++ callable function.
   */
  template<template<typename ...> class Template>
  struct template_ {
    template<typename ...Ts>
    struct apply {
      using type = Template<Ts...>;
    };
  };

  template<typename Fn, typename ArgL>
  struct apply_;

  template<typename Fn, typename...ArgTs>
  using apply_t = typename apply_<Fn, ArgTs...>::type;

/// Creates a type that is suitable for being used as an unique identifier in
/// calls to certain template metafunctions.
#define ZEN_TAG(name) struct name {}

  template<typename ...Ts>
  struct static_assert_helper : false_ {};

  template<typename ...Ts>
  struct or_;

  template<typename ...Ts>
  struct and_;

  template<typename TestT, typename ThenT, typename ElseT>
  struct if_ {
    using type = ElseT;
  };

  template<typename ThenT, typename ElseT>
  struct if_<std::integral_constant<bool, true>, ThenT, ElseT> {
    using type = ThenT;
  };

  template<typename TestT, typename ThenT, typename ElseT>
  using if_t = typename if_<TestT, ThenT, ElseT>::type;

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
  static_assert(static_assert_helper<type>::value, "could not find a suitable implementation for the metafuntion zen::" #name)

  /**
   * @ingroup MetaPrimitives
   * @brief Detects whether a given type is a primitive type.
   *
   */
  template<typename T>
  struct is_primitive_ : false_ {};

  template<typename T>
  inline constexpr bool is_primitive_v = is_primitive_<T>::value;

  template<typename ...Ts> struct is_primitive_<std::tuple<Ts...>> : true_ {};
  template<bool B> struct is_primitive_<bool_<B>> : true_ {};
  template<typename T, T V> struct is_primitive_<std::integral_constant<T, V>> : true_ {};
  template<template <typename ...> class T> struct is_primitive_<template_<T>> : true_ {};

  template<typename HeadT, typename TailL>
  struct cons_impl_ {
    ZEN_MISSING_IMPLEMENTATION(HeadT, cons_);
  };

  /**
   * @ingroup MetaBase
   * @brief Prepend the given sequence with the given type.
   */
  template<typename HeadT, typename TailL>
  struct cons_ : cons_impl_<HeadT, TailL> {};

  template<typename HeadT, typename TailL>
  using cons_t = typename cons_<HeadT, TailL>::type;

  template<typename T>
  struct head_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T, head_);
  };

  template<typename T>
  struct head_ {
    using type = typename head_impl_<T>::type;
  };

  template<typename T>
  struct tail_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T, tail_);
  };

  template<typename T>
  struct tail_ : tail_impl_<T> {};

  template<typename T>
  using tail_t = typename tail_<T>::type;

  /**
   * @ingroup MetaContainers
   * @brief An indexed list of types that can be populated at run-time.
   *
   * On most platforms, a list is just aliased to std::tuple. This is because
   * most standard libraries provide a very efficient implementation of this
   * type. For example, _libc++_ leverages Clang's `__at_element` compiler
   * intrinsic. However, care must be taken to not (ab)use any of the members
   * that are part of this implementation detail. If the member is not
   * documented on one of these pages, chances are that it might disappear in
   * the future.
   *
   * [1]: https://ldionne.com/2015/11/29/efficient-parameter-pack-indexing/
   */
  template<typename ...Ts>
  struct list_t : std::tuple<Ts...> {};

  template<typename ...Ts> struct is_primitive_<list_t<Ts...>> : true_ {};

  template<typename ...Ts>
  struct list_ {
     using type = list_t<Ts...>;
  };

  template<typename T, typename ...Ts>
  struct cons_impl_<T, list_t<Ts...>> : list_<T, Ts...> {};

  template<typename T, typename ...Ts>
  struct head_impl_<list_t<T, Ts...>> { using type = T; };

  template<typename T, typename ...Ts>
  struct tail_impl_<list_t<T, Ts...>> : list_<Ts...> {};

  /**
   * @ingroup MetaContainers
   * @brief A simple ordered mapping from keys to values.
   */
  template<typename ...Ts>
  struct map_t : std::tuple<Ts...> {};

  template<typename ...Ts> struct is_primitive_<map_t<Ts...>> : true_ {};

  template<typename L1, typename L2>
  struct zip_;

  template<typename L1, typename L2>
  using zip_t = typename zip_<L1, L2>::type;

  template<template<typename ...> class Template, typename ...ArgTs>
  struct apply_<template_<Template>, list_t<ArgTs...>> {
    using type = Template<ArgTs...>;
  };

  template<typename Fn, typename ...ArgTs>
  struct call_ : apply_<Fn, list_t<ArgTs...>> {};

  /**
   * @ingroup MetaLang
   * @brief A generic placeholder for a parameter to an argument.
   */
  template<std::size_t I>
  struct arg_n_ {
    static constexpr std::size_t index = I;
  };

  using _0 = arg_n_<0>;
  using _1 = arg_n_<1>;
  using _2 = arg_n_<2>;
  using _3 = arg_n_<3>;
  using _4 = arg_n_<4>;
  using _5 = arg_n_<5>;
  using _6 = arg_n_<6>;
  using _7 = arg_n_<7>;
  using _8 = arg_n_<8>;
  using _9 = arg_n_<9>;

  template<std::size_t I> struct is_primitive_<arg_n_<I>> : true_ {};

  template<typename T, typename EnvT = map_t<>>
  struct eval_;

  template<typename T, typename EnvT = map_t<>>
  using eval_t = typename eval_<T, EnvT>::type;

  template<typename T>
  struct compile_;

  template<typename T>
  using compile_t = typename compile_<T>::type;

  template<typename T>
  struct defun_t {
    using type = eval_t<compile_t<T>>;
  };

  template<typename TestT, typename ThenT, typename ElseT>
  struct $if_;

  template<typename TestT, typename ThenT>
  struct $case_;

  template<typename ThenT>
  using $else_ = $case_<true_, ThenT>;

  template<typename ...CaseTs>
  struct $cond_;

  struct $fail_;

  template<typename T1, typename T2, typename = void>
  struct eq_impl_;

  template<typename T1, typename T2>
  struct eq_;

  template<typename T1, typename T2>
  inline constexpr bool eq_v = eq_<T1, T2>::value;

  template<typename T1, typename T2>
  using eq_t = typename eq_<T1, T2>::type;

  template<typename T, typename = void>
  struct size_impl_;

  template<typename T>
  struct size_;

  template<typename T>
  inline constexpr std::size_t size_v = size_<T>::value;

  template<typename T>
  struct is_empty_;

  template<typename T>
  inline constexpr bool is_empty_v = is_empty_<T>::value;

  template<typename T>
  using head_t = typename head_<T>::type;

  template<typename T>
  struct last_;

  template<typename T>
  using last_t = typename last_<T>::type;

  template<typename I, typename T>
  struct at_;

  template<typename L>
  struct first_ : at_<u0_, L> {};

  template<typename L>
  using first_t = typename first_<L>::type;

  template<typename L>
  struct second_ : at_<u1_, L> {};

  template<typename L>
  using second_t = typename second_<L>::type;

  template<typename L>
  struct third_ : at_<u2_, L> {};

  template<typename L>
  using third_t = typename third_<L>::type;

  template<typename L>
  struct fourth_ : at_<u3_, L> {};

  template<typename L>
  using fourth_t = typename fourth_<L>::type;

  template<typename L>
  struct fifth_ : at_<u4_, L> {};

  template<typename L>
  using fifth_t = typename fifth_<L>::type;

  template<typename L>
  struct sixth_ : at_<u5_, L> {};

  template<typename L>
  using sixth_t = typename sixth_<L>::type;

  template<typename L>
  struct seventh_ : at_<u5_, L> {};

  template<typename L>
  using seventh_t = typename seventh_<L>::type;

  template<typename L>
  struct eighth_ : at_<u7_, L> {};

  template<typename L>
  using eighth_t = typename eighth_<L>::type;

  template<typename L>
  struct ninth_ : at_<u8_, L> {};

  template<typename L>
  using ninth_t = typename ninth_<L>::type;

  template<typename I, typename T>
  struct at_impl_;

  template<typename I, typename T>
  using at_t = typename at_<I, T>::type; 

  template<typename T, typename I, typename R>
  struct set_at_impl_;

  template<typename T, typename I, typename R>
  struct set_at_;

  template<typename R, typename I, typename T>
  using set_at_t = typename set_at_<R, I, T>::type;

  template<typename Fn, typename L>
  struct transform_;

  template<typename Fn, typename L>
  using transform_t = typename transform_<Fn, L>::type;

  template<typename T, typename ArgL>
  struct apply_impl_;

  template<typename FnT, typename ArgL>
  struct apply_;

  template<template <typename ...> class T>
  struct lift_;

  template<typename T1, typename T2>
  struct widen_impl_;

  /**
   * @brief Derives a type that is large enough to hold both \p T1 and \p T2.
   * For example, widening an `int` and a `long` will result in a 
   * `long`, since a `long`, by definition, is large enough to hold all
   * integers.
   */
  template<typename T1, typename T2>
  struct widen_ : widen_impl_<T1, T2> {};

  template<typename T1, typename T2>
  using widen_t = typename widen_<T1, T2>::type;

  template<typename T>
  struct constant_;

  template<typename AccFn, typename InitT, typename L>
  struct foldl_;

  template<typename AccFn, typename L>
  struct foldl1_;

  template<typename T1, typename T2>
  struct mult_impl_;

  template<typename ...Ns>
  struct mult_;

  template<typename T1, typename T2>
  struct add_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T1, add_);
  };

  template<typename ...Ts>
  struct add_;

  template<typename T1, typename T2>
  struct sub_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T1, sub_);
  };

  template<typename ...Ts>
  struct sub_;

  template<typename ...Ts>
  using mult_t = typename mult_<Ts...>::type;

  template<typename T>
  struct dec_impl_;

  template<typename T>
  using dec_ = dec_impl_<T>;

  template<typename T>
  using dec_t = typename dec_<T>::type;

  template<typename T>
  struct inc_impl_;

  template<typename T>
  using inc_ = inc_impl_<T>;

  template<typename T>
  using inc_t = typename inc_<T>::type;

  template<typename N>
  struct fac_;

  template<typename N>
  using fac_t = typename fac_<N>::type;

  template<typename N, typename IterT, typename = void>
  struct prev_n_impl_;

  template<typename N, typename IterT, typename = void>
  struct next_n_impl_;

  /// Get a pointer-like structure to the next element in a certain container.
  ///
  /// \return A maybe type that holds a pointer to the previous value if there is any.
  ///
  template<typename IterT>
  struct next_;

  template<typename IterT>
  using next_t = typename next_<IterT>::type;

  /// Get a pointer-like structure to the previous element in a certain container.
  ///
  /// \return A maybe type that holds a pointer to the next value if there is any.
  template<typename IterT>
  struct prev_;

  template<typename IterT>
  using prev_t = typename prev_<IterT>::type;

  template<typename T, typename = void>
  struct deref_impl_;

  template<typename T>
  struct deref_;

  template<typename T>
  using deref_t = typename deref_<T>::type;

  template<typename ElementT, typename RangeT, typename I>
  struct index_impl_;

  template<typename ElementT, typename RangeT>
  struct index_ : index_impl_<ElementT, RangeT, u0_> {};

  template<typename ElementT, typename RangeT>
  using index_t = typename index_<ElementT, RangeT>::type;

  // template<typename I, typename RangeT, typename = void> 
  // struct take_impl_ {
  //   ZEN_MISSING_IMPLEMENTATION(I, take_);
  // };

  template<typename I, typename L>
  struct take_ :
    defun_t<
      $cond_<
        $case_<eq_<I, u0_>, list_<>>,
        $case_<is_empty_<L>, $fail_>,
        $else_<cons_<head_<L>, take_<dec_<I>, tail_<L>>>>
      >
   > {};

  template<typename I, typename RangeT>
  using take_t = typename take_<I, RangeT>::type;

  template<typename N, typename L>
  struct drop_last_ : defun_t<take_<sub_<size_<L>, N>, L>> {};

  template<typename N, typename TupleT>
  using drop_last_t = typename drop_last_<N, TupleT>::type;

  /**
   * @ingroup MetaMaybe
   * @brief A maybe-type that indicates no value is held.
   *
   * @see none_
   * @see some_t
   * @see is_none_v
   */
  struct none_t;

  /**
   * @ingroup MetaMaybe
   * @brief Constructs a maybe-type that holds nothing.
   *
   * @see none_t
   * @see some_
   * @see is_none_
   */
  struct none_ { using type = none_; };

  template<> struct is_primitive_<none_t> : true_ {};

  template<typename T>
  struct some_t {
    static constexpr bool has_some = true;
    using value_type = T;
  };

  template<typename T> struct is_primitive_<some_t<T>> : true_ {};

  template<typename T> struct some_ { using type = some_t<T>; };

  template<typename T> struct deref_impl_<some_t<T>> { using type = T; };

  template<typename MaybeT>
  struct is_none_;

  template<typename maybet>
  inline constexpr bool is_none_v = is_none_<maybet>::value;

  template<typename MaybeT>
  struct is_some_ : false_ {};

  template<typename T>
  struct is_some_<some_t<T>> : true_ {};

  template<typename maybet>
  inline constexpr bool is_some_v = is_some_<maybet>::value;

  template<typename T>
  struct begin_impl_;

  template<typename T>
  struct end_impl_;

  template<typename ...Ts>
  struct $lambda_ {
    static_assert(sizeof...(Ts) > 0, "a lambda expression must at least contain a body");
  };

  template<typename ...CaseTs>
  struct $cond_ {
    static_assert(sizeof...(CaseTs) > 0, "a conditional must contain at least one case");
  };

  template<typename TestT, typename ThenT, typename ElseT>
  struct if_node_t;

  template<typename ParamL, typename BodyT>
  struct lambda_node_t;

  template<typename FnT, typename ArgL>
  struct apply_node_t;

  struct fail_node_t;

  template<typename ...CaseTs>
  struct compile_cond_helper_;

  template<>
  struct compile_cond_helper_<> {
    using type = fail_node_t;
  };

  template<typename TestT, typename ThenT, typename ...CaseTs>
  struct compile_cond_helper_<$case_<TestT, ThenT>, CaseTs...> {
    using type = if_node_t<compile_t<TestT>, compile_t<ThenT>, typename compile_cond_helper_<CaseTs...>::type>;
  };

  template<typename T>
  struct compile_ {
    using type = T;
  };

  template<typename ...CaseTs>
  struct compile_<$cond_<CaseTs...>> : compile_cond_helper_<CaseTs...> {};

  template<typename TestT, typename ThenT, typename ElseT>
  struct compile_<$if_<TestT, ThenT, ElseT>> {
    using type = if_node_t<compile_t<TestT>, compile_t<ThenT>, compile_t<ElseT>>;
  };

  template<typename ...Ts>
  struct compile_<$lambda_<Ts...>> {
    using type = lambda_node_t<drop_last_t<u1_, list_t<Ts...>>, compile_t<last_t<list_t<Ts...>>>>;
  };

  template<template<typename ...> class T, typename ...Ts>
  struct compile_<T<Ts...>> : std::conditional<is_primitive_v<T<Ts...>>, T<Ts...>, apply_node_t<template_<T>, list_t<compile_t<Ts>...>>> {};

  template<typename Fn, typename EnvT>
  struct closure_t {
    using func_type = Fn;
    using env_type = EnvT;
  };

  template<typename T, typename EnvT>
  struct eval_ {
    //static_assert(is_primitive_v<T>, "could not evaluate type at compile-time because it does not resolve to a primitive type");
    using type = T;
  };

  template<typename EnvT, bool B, typename ThenT, typename ElseT>
  struct eval_if_helper_ {
    using type = eval_t<ThenT, EnvT>;
  };

  template<typename EnvT, typename ThenT, typename ElseT>
  struct eval_if_helper_<EnvT, false, ThenT, ElseT> {
    using type = eval_t<ElseT, EnvT>;
  };

  template<typename EnvT, typename TestT, typename ThenT, typename ElseT>
  struct eval_<if_node_t<TestT, ThenT, ElseT>, EnvT> {
    using type = typename eval_if_helper_<EnvT, eval_t<TestT, EnvT>::value, ThenT, ElseT>::type;
  };

  template<typename FnV, typename ArgL, typename EnvT = map_t<>>
  struct eval_apply_helper_;

  template<typename EnvT, template <typename ...> class T, typename ...As>
  struct eval_apply_helper_<EnvT, template_<T>, list_t<As...>> {
    using intermediate_type = T<eval_t<As, EnvT>...>;
    using type = std::conditional_t<is_primitive_v<intermediate_type>, intermediate_type, typename intermediate_type::type>;
  };

  template<typename E, typename L>
  struct rcons_ :
    defun_t<
      $cond_<
        $case_<is_empty_<L>, list_<E>>,
        $else_<cons_<head_<L>, rcons_<E, tail_<L>>>>
      >
    > {};

  template<typename E, typename L>
  using rcons_t = typename rcons_<E, L>::type;

  template<typename T, typename ...Ts>
  constexpr auto rcons(T element, std::tuple<Ts...> list) {
    return std::tuple_cat(list, std::make_tuple(element));
  }

  template<typename F, typename L, size_t i>
  struct find_helper_ :
    defun_t<
      $cond_<
        $case_< apply_<F, head_<L> >, u_ < i > >,
        $else_ < find_helper_<F, tail_<L>, i+1 > >
      >
    > {};

  template<typename F, typename L>
  using find_ = find_helper_<F, L, 0>;

  template<typename F, typename L>
  using find_t = typename find_<F, L>::type;

  template<typename L1, typename L2>
  struct override_ :
    defun_t<
      $cond_<
        $case_<is_empty_<L2>, L1>,
        $case_<is_empty_<L1>, L2>,
        $else_<cons_<head_<L2>, override_<tail_<L1>, tail_<L2>>>>
      >
    > {};

  template<typename L1, typename L2>
  using override_t = typename override_<L1, L2>::type;

  template<typename EnvT, typename ParamL, typename BodyT, typename ArgL>
  struct eval_apply_helper_<lambda_node_t<ParamL, BodyT>, ArgL, EnvT> {
    using type = eval_t<BodyT, override_t<EnvT, apply_t<template_<map_t>, zip_t<ParamL, ArgL>>>>;
  };

  template<typename Env1, typename Fn, typename Env2, typename ArgL>
  struct eval_apply_helper_<closure_t<Fn, Env2>, ArgL, Env1> {
    using type = typename eval_apply_helper_<override_t<Env1, Env2>, Fn, ArgL>::type;
  };

  // FIXME Do we really need this?
  template<typename Fn, typename EnvT, typename ArgL>
  struct apply_<closure_t<Fn, EnvT>, ArgL> {
    using type = typename eval_apply_helper_<Fn, ArgL>::type;
  };

  template<typename EnvT, typename Fn, typename ArgL>
  struct eval_<apply_node_t<Fn, ArgL>, EnvT> {
    using type = typename eval_apply_helper_<EnvT, eval_t<Fn, EnvT>, ArgL>::type;
  };

  // template<typename EnvT, template <typename ...> class Fn, typename ...Ts>
  // struct eval_<apply_<template_<Fn>, list_t<Ts...>>, EnvT> {
  //   using intermediate_type = Fn<eval_t<Ts, EnvT>...>;
  //   using type = std::conditional_t<is_primitive_v<intermediate_type>, intermediate_type, typename intermediate_type::type>;
  // };

  // template<typename EnvT, typename ArgL, typename ...Ls>
  // struct eval_<apply_<lambda_<Ls...>, ArgL>, EnvT> {
  // 
  //   using param_types = drop_last_t<u1_, list_t<Ls...>>;
  //   using body_type = at_t<u_<sizeof...(Ls)-1>, list_t<Ls...>>;
  // 
  //   template<typename T>
  //   struct subst_binders_ {
  //     static_assert(is_primitive_v<T>, "only primitive values should use the identity substitution");
  //     using type = T;
  //   };
  // 
  //   template<typename Fn, typename ...Ts>
  //   struct subst_binders_<apply_<Fn, list_t<Ts...>>> {
  //     using type = apply_<Fn, list_t<subst_binders_<Ts>...>>;
  //   };
  // 
  //   template<typename Fn, typename ...Ts>
  //   struct subst_binders_<call_<Fn, list_t<Ts...>>> {
  //     using type = call_<Fn, subst_binders_<Ts>...>;
  //   };
  // 
  //   template<typename TestT, typename ThenT, typename ElseT>
  //   struct subst_binders_<if_<TestT, ThenT, ElseT>> {
  //     using type = if_<subst_binders_<TestT>, subst_binders_<ThenT>, subst_binders_<ElseT>>;
  //   };
  // 
  //   // FIXME When a nested lambda expression is encountered, we should remove
  //   //       any parameters that are shadowed.
  //   template<typename ...Rs>
  //   struct subst_binders_<lambda_<Rs...>> {
  //     using type = lambda_<set_at_t<u_<sizeof...(Rs)-1>, subst_binders_<last_t<list_t<Rs...>>>, list_t<Rs...>>>;
  //   };
  // 
  //   template<std::size_t I>
  //   struct subst_binders_<arg_n_<I>> {
  //     using maybe_index_type = index_t<arg_n_<I>, param_types>;
  //     static_assert(is_some_v<maybe_index_type>);
  //   public:
  //     using type = at_t<deref_t<maybe_index_type>, ArgL>;
  //     // using type = std::conditional_t<is_some_v<maybe_index_type>, at_t<deref_t<maybe_index_type>, ArgL>, arg_n_<I>>;
  //   };
  // 
  //   using type = eval_t<typename subst_binders_<body_type>::type, EnvT>;
  // 
  // };

  // template<typename EnvT, typename Fn, typename ...ArgTs>
  // struct eval_<call_<Fn, ArgTs...>, EnvT> : eval_<apply_<Fn, list_t<ArgTs...>>> {};

  template<typename EnvT>
  struct eval_<fail_node_t, EnvT> {
    static_assert(static_assert_helper<EnvT>::value, "failed to evaluate expression");
  };

  // template<typename EnvT, typename T>
  // struct eval_<defun_t<T>, EnvT> : defun_t<T> {};

  template<typename EnvT, typename ParamL, typename BodyT>
  struct eval_<lambda_node_t<ParamL, BodyT>, EnvT> {
    using type = closure_t<lambda_node_t<ParamL, BodyT>, EnvT>;
  };

  template<typename ListT, std::size_t I>
  struct list_iterator_t {
    static constexpr std::size_t index = I;
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

  template<typename EnvT, std::size_t I>
  struct eval_<arg_n_<I>, EnvT> {
    using type = deref_t<at_t<arg_n_<I>, EnvT>>;
  };

  template<typename N, typename ListT, std::size_t I>
  struct prev_n_impl_<N, list_iterator_t<ListT, I>> {
    using type = std::conditional_t <
      N::value < I,
      list_iterator_t<ListT, I - N::value>,
      none_
    >;
  };

  template<typename ...Ts>
  struct begin_impl_<list_t<Ts...>> {
    using type = list_iterator_t<list_t<Ts...>, 0>;
  };

  template<typename T1, typename T2, typename>
  struct eq_impl_ : false_ {};

  template<typename T>
  struct eq_impl_<T, T> : true_ {};

  template<typename T1, typename T2>
  struct eq_ : eq_impl_<T1, T2> {};

  template<typename T, typename>
  struct size_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T, size_);
  };

  template<typename ...Ts>
  struct size_impl_<std::tuple<Ts...>> : std::tuple_size<std::tuple<Ts...>> {};

  template<typename ...Ts>
  struct size_impl_<list_t<Ts...>> : u_<sizeof...(Ts)> {};

  template<typename ...Ts> 
  struct size_impl_<map_t<Ts...>> : u_<sizeof...(Ts)> {};

  template<typename T>
  struct size_ : size_impl_<T> {};

  template<typename T>
  struct is_empty_ : defun_t<eq_<size_<T>, u0_>> {};

  template<typename T>
  struct last_ : defun_t < $if_ < eq_ < size_ < T >, u1_ >, head_<T>, last_ < tail_ < T > > > > {};

  template<typename I, typename T>
  struct at_ : at_impl_<I, T> {};

  template<typename T, typename I>
  struct at_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T, at_);
  };

  template<std::size_t I, typename ...Ts>
  struct at_impl_<u_<I>, std::tuple<Ts...>> : std::tuple_element<I, std::tuple<Ts...>> {};

  template<std::size_t I, typename ...Ts>
  struct at_impl_<u_<I>, list_t<Ts...>> : std::tuple_element<I, std::tuple<Ts...>> {};

  template<typename T, typename I, typename R>
  struct set_at_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T, set_at_);
  };

  template<typename T, typename I, typename R>
  struct set_at_ : set_at_impl_<T, I, R> {};

  template<typename T, typename I, typename R>
  using set_at_t = typename set_at_<T, I, R>::type;

  template<typename Fn, typename L>
  struct transform_ : defun_t<
        foldl_<
          $lambda_< _1, _2, cons_<call_<Fn, _2>, _1> >,
          list_t<>,
          L
        >
      > {};

  // template<typename T, typename ArgL>
  // struct apply_impl_ {
  //   ZEN_MISSING_IMPLEMENTATION(T, call_);
  // };
  // 
  // template<template<typename ...> class TemplateT, typename ...ArgTs>
  // struct apply_impl_<template_<TemplateT>, list_t<ArgTs...>> {
  //   using type = typename TemplateT<ArgTs...>::type;
  // };

  // template<typename FnT, typename ArgL>
  // struct apply_ {};
  // 
  // template<typename FnT, typename ...ArgTs>
  // struct call_ : apply_<FnT, list_t<ArgTs...>> {};

  template<typename T1, typename T2>
  struct widen_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T1, widen_);
  };

  template<typename T>
  struct widen_impl_<T, T> {
    using type = T;
  };

  template<typename T>
  struct const_ : defun_t<$lambda_<_1, T>> {};

  template<typename AccFn, typename InitT, typename L>
  struct foldl_ :
    $if_<
      is_empty_<L>,
      InitT,
      call_ < AccFn, head_<L>, foldl_<AccFn, InitT, tail_<L>> >
    > {};

  template<typename AccFn, typename L>
  struct foldl1_ : defun_t<
      $if_<
        is_empty_< tail_ <L> >,
        head_<L>,
        call_ < AccFn, head_<L>, foldl1_<AccFn, tail_<L>> >
      >
    > {};

  template<typename T1, typename T2>
  struct mult_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T1, mult_);
  };

  template<typename T1, typename T2, T1 N1, T2 N2>
  struct mult_impl_<std::integral_constant<T1, N1>, std::integral_constant<T2, N2>>{
    using type = std::integral_constant<widen_t<T1, T2>, N1 * N2>;
  };

  template<typename ...Ns>
  struct mult_ : defun_t<
      foldl1_< lift_ < mult_impl_ >, list_<Ns...> >
    > {};

  template<typename ...Ts>
  using mult_t = typename mult_<Ts...>::type;

  template<typename T, T N>
  struct dec_impl_<std::integral_constant<T, N>> {
    static_assert(N > 0);
    using type = std::integral_constant<T, N - 1>;
  };

  template<typename T>
  using dec_ = dec_impl_<T>;

  template<typename T, T N>
  struct inc_impl_<std::integral_constant<T, N>> : std::integral_constant<T, N + 1> {};

  template<typename T>
  using inc_ = inc_impl_<T>;

  template<typename N>
  struct fac_ : defun_t<
     $cond_<
      $case_<eq_<N, u0_>, u1_>,
      $case_<eq_<N, u1_>, u1_>,
      $else_<mult_<fac_<dec_<N>>, N>>
    >
  > {};

  template<typename N>
  using fac_t = typename fac_<N>::type;

  template<typename IterT>
  struct next_impl_ : next_n_impl_<u1_, IterT> {};

  template<typename IterT>
  struct prev_impl_ : next_n_impl_<u1_, IterT> {};

  template<typename IterT>
  struct next_ : next_impl_<IterT> {};

  template<typename IterT>
  struct prev_ : prev_impl_<IterT> {};

  template<typename N, typename IterT, typename>
  struct next_n_impl_ : defun_t<
    $cond_ <
      $case_<bool_<N::value == 0>, IterT>,
      $case_<is_none_<IterT>, none_t>,
      $else_<next_n_impl_<inc_<N>, next_<IterT>>>
    >
  > {};

  template<typename N, typename IterT, typename>
  struct prev_n_impl_ : defun_t<
    $cond_<
      $case_<bool_<N::value == 0>, IterT>,
      $case_<is_none_<prev_<IterT>>, none_t>,
      $else_<prev_n_impl_<dec_<N>, prev_<IterT>>>
    >
  > {};

  template<typename T, typename>
  struct deref_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T, deref_);
  };

  template<typename T>
  struct deref_ : deref_impl_<T> {};

  template<typename BeginT, typename EndT>
  struct range_t {
    using begin_type = BeginT;
    using end_type = EndT;
  };

  template<typename BeginT, typename EndT>
  struct range_ {
    using type = range_t<BeginT, EndT>;
  };

  template<typename BeginT, typename EndT>
  struct inc_impl_<range_t<BeginT, EndT>> {
    using type = range_t<next_t<BeginT>, EndT>;
  };

  template<typename ...Ts>
  struct add_ : defun_t<foldl1_<template_<add_impl_>, list_<Ts...>>> {};

  template<typename ...Ts>
  struct sub_ : defun_t < foldl1_ < template_<sub_impl_>, list_<Ts...> > > {};

  template<typename ElementT, typename RangeT, typename I>
  struct index_impl_ : defun_t<
    $cond_<
      $case_<is_empty_<RangeT>, none_>,
      $case_<eq_<head_<RangeT>, ElementT>, some_<I>>,
      $else_<index_impl_<ElementT, tail_<RangeT>, inc_<I>>>
    >
  > {};

  template<typename L1, typename L2>
  struct zip_ :
    defun_t<
      $cond_<
        $case_<and_<is_empty_<L1>, is_empty_<L2>>, list_<>>,
        $case_<or_<is_empty_<L1>, is_empty_<L2>>, $fail_>,
        $else_<cons_<list_<head_<L1>, head_<L2>>, zip_<tail_<L1>, tail_<L2>>>>
      >
    > {};

  // The following are specializations of metafunctions that are used
  // internally by the evaluator. In order break cyclic dependencies and speed
  // up evaluation, the specializations of these metafunctions rely on nothing
  // more than a few primitives.

  template<typename T1, typename T2, T1 N1, T2 N2>
  struct add_<std::integral_constant<T1, N1>, std::integral_constant<T2, N2>> : std::integral_constant<widen_t<T1, T2>, N1 + N2> {};

  template<typename T1, typename T2, T1 N1, T2 N2>
  struct sub_<std::integral_constant<T1, N1>, std::integral_constant<T2, N2>> : std::integral_constant<widen_t<T1, T2>, N1 - N2> {};

  template<typename T1, typename T2, T1 N1, T2 N2>
  struct mult_<std::integral_constant<T1, N1>, std::integral_constant<T2, N2>> : std::integral_constant<widen_t<T1, T2>, N1 * N2> {};

  template<bool B1, bool B2>
  struct and_<std::integral_constant<bool, B1>, std::integral_constant<bool, B2>> : bool_<B1 && B2> {};

  template<bool B1, bool B2>
  struct or_<std::integral_constant<bool, B1>, std::integral_constant<bool, B2>> : bool_<B1 || B2> {};

  template<typename I, typename ...ElementTs>
  struct fast_map_at_helper_ : none_ {};

  template<typename I, typename ElementT, typename ...ElementTs>
  struct fast_map_at_helper_<I, ElementT, ElementTs...> : if_<eq_t<first_t<ElementT>, I>, some_t<second_t<ElementT>>, typename fast_map_at_helper_<I, ElementTs...>::type> {};

  template<typename I, typename ...ElementTs>
  struct at_impl_<I, map_t<ElementTs...>> : fast_map_at_helper_<I, ElementTs...> {};

// #define ZEN_MAKE_TYPENAME(i) typename ZEN_PASTE_2(T, i)
// #define ZEN_MAKE_TYPEREF(i) ZEN_PASTE_2(T, i)
// 
//   template<std::size_t I, typename R, typename TupleT>
//   struct set_tuple_element_helper_;
// 
// #define ZEN_MAKE_TUPLE_SETTER(index) \
//   template<typename R , ZEN_JOIN_ENUM(ZEN_INC(index), ZEN_MAKE_TYPENAME) , typename ...Ts> \
//   struct set_tuple_element_helper_<index, R, std::tuple<ZEN_JOIN_ENUM(ZEN_INC(index), ZEN_MAKE_TYPEREF) , Ts...>> { \
//     using type = std::tuple<ZEN_FOR_ENUM(index, ZEN_MAKE_TYPEREF) R, Ts...>; \
//   };
// 
//   ZEN_MAKE_TUPLE_SETTER(0);
//   ZEN_MAKE_TUPLE_SETTER(1);
//   ZEN_MAKE_TUPLE_SETTER(2);
//   ZEN_MAKE_TUPLE_SETTER(4);
//   ZEN_MAKE_TUPLE_SETTER(5);
//   ZEN_MAKE_TUPLE_SETTER(6);
//   ZEN_MAKE_TUPLE_SETTER(7);
//   ZEN_MAKE_TUPLE_SETTER(8);
//   ZEN_MAKE_TUPLE_SETTER(9);
// 
//   template<std::size_t I, typename R, typename TupleT>
//   using set_tuple_element_helper_t = typename set_tuple_element_helper_<I, R, TupleT>::type;

  // template<typename T1, typename T2, T1 N1, T2 N2>
  // struct div_<std::integral_constant<T1, N1>, std::integral_constant<T2, N2>> : std::integral_constant<widen_t<T1, T2>, N1 / N2> {};

  // template<>
  // struct is_empty_<list_t<>> : true_ {};
  // 
  // template<typename T1, typename ...Ts>
  // struct is_empty_<list_t<T1, Ts...>> : false_ {};
  // 
  // template<std::size_t I, typename ElementT, typename ...Ts>
  // struct fast_index_helper_ : none_ {};
  // 
  // template<std::size_t I, typename ElementT, typename T1, typename ...Ts>
  // struct fast_index_helper_<I, ElementT, T1, Ts...> : std::conditional<eq_v<ElementT, T1>, some_t<u_<I>>, typename fast_index_helper_<I+1, ElementT, Ts...>::type> {};
  // 
  // template<typename ElementT, typename ...Ts>
  // struct index_impl_<ElementT, list_t<Ts...>> : fast_index_helper_<0, ElementT, Ts...> {};
  // 
  // template<std::size_t I, typename LeftL, typename RightL>
  // // struct fast_drop_last_helper_;
  // struct fast_drop_last_helper_ 
  //   : std::conditional<
  //     I == 0,
  //     RightL,
  //     typename fast_drop_last_helper_<I-1, cons_t<head_t<RightL>, LeftL>, tail_t<RightL>>::type
  //   > {};
  //
  // template<std::size_t I, typename ...Ts>
  // struct drop_last_<u_<I>, list_t<Ts...>> : fast_drop_last_helper_<I, list_t<>, list_t<Ts...>> {};
  // 
  //
  // template<std::size_t I, typename LeftT, typename RightT = list_t<>>
  // struct take_list_helper_;
  // 
  // template<typename LeftT, typename RightT>
  // struct take_list_helper_<0, LeftT, RightT> {
  //   using type = RightT;
  // };
  // 
  // template<std::size_t N, typename L1, typename ...Ls, typename ...Rs>
  // struct take_list_helper_<N, list_t<L1, Ls...>, list_t<Rs...>> {
  //   using type = typename take_list_helper_<N-1, list_t<Ls...>, list_t<L1, Rs...>>::type;
  // };

  template<typename T1, typename T2>
  constexpr auto max(T1 x, T2 y) {
    return x > y ? x : y;
  }

} // of namespace zen

#endif // ZEN_META_HPP
