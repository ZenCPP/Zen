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
 * `Template` metafunction to lift the argument to a Zen++ primitive.
 *
 * ```
 * // Wrong: will throw a compile-time error
 * static_assert(zen::eq_v<zen::at_<1, zen::Tuple<int, float, bool>>, float>);
 *
 * // Correct: 1 is lifted to a Zen++ meta-primitive
 * static_assert(zen::eq_v<zen::at_<u_<1>, zen::Tuple<int, float, bool>>, float>);
 *
 * // Preffed because it is a bit easier to read
 * static_assert(zen::eq_v<zen::at_<u1_, zen::Tuple<int, float, bool>>, float>);
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

#include <stddef.h>

#include "zen/config.h"
#include "zen/config.h"

// TODO  Make more metafunctions accept a parameter pack
// FIXME std::tuple and Tuple are essentially the same, which makes one wonder
//       how both types can be implemented using the same template
// FIXME The same issue persists in eval_<call_<...>, EnvT>. How do we tell the
//       compiler to just use the type 'next up'? Do we use std::enable_if_t or
//       do we use tag dispatching?
// TODO  Generalize the Override metafunction

ZEN_NAMESPACE_START

template<typename ...Ts>
class Tuple;

/**
 * @ingroup MetaPrimitives
 * @brief A meta-representation of the void type.
 *
 * This utility type is mainly useful for peforming SFINAE-style casts.
 */
template<typename... Ts> struct Void { using UnderlyingType = void; };

template<typename... Ts> using VoidT = typename Void<Ts...>::UnderlyingType;

/**
 * @ingroup MetaPrimitives
 * @brief A type-level constant value of the specified type.
 *
 * This metafunction represents one of the few primitives of the metalanguage.
 * You cannot apply it but you can extract the underlying value.
 *
 * @see std::integral_constant
 */
template<typename T, T K>
struct Constant {

  using UnderlyingType = T;

  static constexpr const T value = K;

};

/**
 * @ingroup MetaPrimitives
 * @brief A metatype that holds a simple boolean value.
 */
template<bool B>
using Bool = Constant<bool, B>;

/**
 * @ingroup MetaPrimitives
 * @brief A boolean metatype that holds a value that is always true.
 * 
 * This value is the type-level equivalent of the constant expression `true`
 * that you would use at run-time.
 */
using True = Bool<true>;

/**
 * @ingroup MetaPrimitives
 * @brief A transparent boolean type that holds a value that is always false.
 *
 * This value is the type-level equivalent of the constant expression `true`
 * that you would use at run-time.
 */
using False = Bool<false>;

/**
 * @ingroup MetaPrimitives
 * @brief A metatype that can hold any natural number not larger than @ref Size.
 */
template<size_t I>
using U = Constant<size_t, I>;

/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the natural number `0`.
 */
using U0 = U<0>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the natural number `1`.
 */
using U1 = U<1>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the natural number `2`.
 */
using U2 = U<2>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the natural number `3`.
 */
using U3 = U<3>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the natural number `4`.
 */
using U4 = U<4>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the natural number `5`.
 */
using U5 = U<5>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the natural number `6`.
 */
using U6 = U<6>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the natural number `7`.
 */
using U7 = U<7>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the natural number `8`.
 */
using U8 = U<8>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the natural number `9`.
 */
using U9 = U<9>;

/**
 * @ingroup MetaPrimitives
 * @brief A type that can hold any whole number that fits into one memory cell.
 */
template<ptrdiff_t D>
using S = Constant<ptrdiff_t, D>;

/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the integer `0`.
 */
using S0 = S<0>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the integer `1`.
 */
using S1 = S<1>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the integer `2`.
 */
using S2 = S<2>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the integer `3`.
 */
using S3 = S<3>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the integer `4`.
 */
using S4 = S<4>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the integer `5`.
 */
using S5 = S<5>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the integer `6`.
 */
using S6 = S<6>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the integer `7`.
 */
using S7 = S<7>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the integer `8`.
 */
using S8 = S<8>;
/**
 * @ingroup MetaPrimitives
 * @brief The type-level equivalent of the integer number `9`.
 */
using S9 = S<9>;

/**
 * @brief A helper metatype that allows you to easily implement SFINAE-style
 * checks using a predicate.
 *
 * ```
 * template<typename T, typename Enabler = void>
 * class Foo;
 * 
 * template<typename T>
 * class Foo<
 *   T,
 *   EnableIf<IsContainer<T>::value>::Type
 * > {
 *   // Implementation of Foo<T> whenever T is a STL container
 * };
 * ```
 * 
 * @see std::enable_if
 */
template<bool B, typename T = void>
struct EnableIf {};

template<typename T>
struct EnableIf<true, T> { typedef T Type; };

#if !defined(ZEN_FEAT_DECLVAL)
template<typename _Tp, typename _Up = _Tp&&>
_Up __declval(int);  // (1)

template<typename _Tp>
_Tp __declval(long); // (2)
#endif

template<bool B, typename T = void>
using EnableIfT = typename EnableIf<B, T>::Type;

/**
 * @brief Get the given type as a reference.
 *
 * @see std::declval
 */
template<typename T>
auto declval() noexcept -> decltype(__declval<T>(0));

/**
 * @ingroup MetaPrimitives
 * @brief Lift a C++ template metafunction into a Zen++ callable function.
 */
template<template<typename ...> class C>
struct Template {
  template<typename ...Ts>
  struct Apply {
    using Type = C<Ts...>;
  };
};

/**
 * @ingroup MetaPrimitives
 * @brief Applies a function-like metatype to the given list of arguments.
 */
template<typename Fn, typename ArgL>
struct Apply;

template<typename Fn, typename...ArgTs>
using ApplyT = typename Apply<Fn, ArgTs...>::Type;

/**
 * @brief Create a type tag.
 *
 * This macro creates a new type that may be used to identify a specific
 * template specialization or function overload.
 */
#define ZEN_TAG(name) struct name {}

template<typename ...Ts>
struct Or;

template<typename ...Ts>
struct And;

/**
 * @brief Derive a type based on the result of a boolean expression.
 *
 * @see std::conditional
 */
template<bool Test, typename ThenT, typename ElseT>
struct BIf {
  using Type = ElseT;
};

template<typename ThenT, typename ElseT>
struct BIf<true, ThenT, ElseT> {
  using Type = ThenT;
};

template<bool Test, typename ThenT, typename ElseT>
using IfT = typename BIf<Test, ThenT, ElseT>::Type;

/**
 * @brief Will cause a compile-time error message to be displayed to the developer.
 *
 * The message will depend on the instanciation of whatever parameter
 * that was passed to it. This is useful when you want to add a custom
 * error message to certain temlate specializations.
 *
 * ```
 * // ...
 *
 * template<typename T>
 * template is_a_cool_num {
 *   ZEN_MISSING_IMPLEMENTATION(T, "Sorry, we can't determine if your number is cool or not.",);
 * };
 *
 * template<>
 * struct is_a_cool_num<666> : False {};
 *
 * template<>
 * struct is_a_cool_num<42> : True {};
 * ```
 */
#define ZEN_MISSING_IMPLEMENTATION(type, name) \
  static_assert( \
      _StaticAssertHelper<type>::value, \
      "could not find a suitable implementation for the metafuntion zen::" #name \
  )

template<typename ...Ts>
struct _StaticAssertHelper : False {};

/**
 * @ingroup MetaPrimitives
 * @brief Infer whether a given type is a metatype.
 *
 * This metafunction tries to guess if a given type is a metatype or just a
 * regular type. It uses SFINAE to detect the presence of a `::Type` member
 * and will return false if no such member could be found.
 */
template<typename T, typename Enabler = void>
struct IsMeta : False {};

template<typename T>
struct IsMeta<
  T,
  VoidT<typename T::Type>
> : True {};

template<typename T>
inline constexpr bool is_meta = IsMeta<T>::value;

/**
 * A compile-time sequence of whatever type was specified as the first argument.
 * 
 */
template<typename T, T...Vs>
struct Seq;

#if ZEN_FEAT_MAKE_INTEGER_SEQ

template<typename T, size_t N>
struct Ascending : __make_integer_seq<Seq, T, N> {};

#else

template<typename T, size_t N, size_t ...Is>
struct AscendImpl :
    IfT<N == 0, Seq<T, Is...>, AscendImpl<T, N-1, N, Is...>> {};

template<typename T, size_t N>
struct Ascending : AscendImpl<T, N> {};

#endif

template<typename HeadT, typename TailL>
struct PrependImpl {
  ZEN_MISSING_IMPLEMENTATION(HeadT, Prepend);
};

/**
 * @ingroup MetaPrimitives
 * @brief Prepend the given sequence with the given type
 * 
 * ```
 * // T is equivalent to Tuple<short, int, long>
 * using T = PrependT<short, Tuple<int, long>>;
 * ```
 */
template<typename HeadT, typename TailL>
struct Prepend : PrependImpl<HeadT, TailL> {};

template<typename HeadT, typename TailL>
using PrependT = typename Prepend<HeadT, TailL>::Type;

template<typename T>
struct HeadImpl {
  ZEN_MISSING_IMPLEMENTATION(T, head_);
};

/**
 * @brief Get the first metatype in a list of metatypes.
 *
 * @see First
 * @see std::tuple_element
 */
template<typename T>
struct Head : HeadImpl<T> {};

template<typename T>
struct TailImpl {
  ZEN_MISSING_IMPLEMENTATION(T, tail_);
};

template<typename T>
struct Tail : TailImpl<T> {};

template<typename T>
using TailT = typename Tail<T>::type;

template<typename T, typename ...Ts>
struct PrependImpl<T, Tuple<Ts...>> {
  using Type = Tuple<T, Ts...>;
};

template<typename T, typename ...Ts>
struct HeadImpl<Tuple<T, Ts...>> {
  using Type = T;
};

template<typename T, typename ...Ts>
struct TailImpl<Tuple<T, Ts...>> {
  using Type = Tuple<Ts...>;
};

/**
 * @ingroup MetaContainers
 * @brief A simple ordered mapping from keys to values.
 */
template<typename ...Ts>
struct map_t : Tuple<Ts...> {};

template<typename ...Ts> struct IsMeta<map_t<Ts...>> : True {};

template<typename L1, typename L2>
struct Zip;

template<typename L1, typename L2>
using ZipT = typename Zip<L1, L2>::type;

template<template<typename ...> class P, typename ...ArgTs>
struct Apply<Template<P>, Tuple<ArgTs...>> {
  using type = P<ArgTs...>;
};

template<typename Fn, typename ...ArgTs>
struct call_ : Apply<Fn, Tuple<ArgTs...>> {};

/**
 * @ingroup MetaLang
 * @brief A generic placeholder for a parameter to an argument.
 */
template<size_t I>
struct Binder {
  static constexpr size_t index = I;
};

using _0 = Binder<0>;
using _1 = Binder<1>;
using _2 = Binder<2>;
using _3 = Binder<3>;
using _4 = Binder<4>;
using _5 = Binder<5>;
using _6 = Binder<6>;
using _7 = Binder<7>;
using _8 = Binder<8>;
using _9 = Binder<9>;

template<size_t I> struct IsMeta<Binder<I>> : True {};

template<typename T, typename EnvT = map_t<>>
struct Eval;

template<typename T, typename EnvT = map_t<>>
using eval_t = typename Eval<T, EnvT>::type;

template<typename T>
struct Compile;

template<typename T>
using compile_t = typename Compile<T>::type;

template<typename T>
struct Define {
  using type = eval_t<compile_t<T>>;
};

template<typename TestT, typename ThenT, typename ElseT>
struct If;

template<typename TestT, typename ThenT>
struct Case;

template<typename ThenT>
using Else = Case<True, ThenT>;

template<typename ...CaseTs>
struct Cond;

struct $fail_;

template<typename T1, typename T2, typename = void>
struct EqImpl;

template<typename T1, typename T2>
struct Eq;

template<typename T1, typename T2>
inline constexpr bool eq_v = Eq<T1, T2>::value;

template<typename T1, typename T2>
using EqT = typename Eq<T1, T2>::type;

template<typename T, typename = void>
struct SizeImpl {
  ZEN_MISSING_IMPLEMENTATION(T, Size);
};

template<typename T>
struct Size;

template<typename T>
inline constexpr size_t size_v = Size<T>::value;

template<typename T>
struct IsEmpty;

template<typename T>
inline constexpr bool is_empty_v = IsEmpty<T>::value;

template<typename T>
using head_t = typename Head<T>::type;

template<typename T>
struct Last;

template<typename T>
using last_t = typename Last<T>::type;

template<typename I, typename T>
struct At;

template<typename L>
struct First : At<U0, L> {};

template<typename L>
using FirstT = typename First<L>::type;

template<typename L>
struct Second : At<U1, L> {};

template<typename L>
using SecondT = typename Second<L>::type;

template<typename L>
struct Third : At<U2, L> {};

template<typename L>
using ThirdT = typename Third<L>::type;

template<typename L>
struct Fourth : At<U3, L> {};

template<typename L>
using FourthT = typename Fourth<L>::type;

template<typename L>
struct Fifth : At<U4, L> {};

template<typename L>
using FifthT = typename Fifth<L>::type;

template<typename L>
struct Sixth : At<U5, L> {};

template<typename L>
using SixthT = typename Sixth<L>::type;

template<typename L>
struct Seventh : At<U5, L> {};

template<typename L>
using SeventhT = typename Seventh<L>::type;

template<typename L>
struct Eighth : At<U7, L> {};

template<typename L>
using EighthT = typename Eighth<L>::type;

template<typename L>
struct Ninth : At<U8, L> {};

template<typename L>
using NinthT = typename Ninth<L>::type;

template<typename I, typename T>
struct AtImpl;

template<typename I, typename T>
using AtT = typename At<I, T>::type; 

template<typename T, typename I, typename R>
struct SetAtImpl;

template<typename T, typename I, typename R>
struct SetAt;

template<typename R, typename I, typename T>
using set_at_t = typename SetAt<R, I, T>::type;

template<typename Fn, typename L>
struct Transform;

template<typename Fn, typename L>
using transform_t = typename Transform<Fn, L>::type;

template<typename T, typename ArgL>
struct apply_impl_;

template<typename FnT, typename ArgL>
struct Apply;

template<typename T1, typename T2>
struct WidenImpl;

/**
 * @brief Derives a type that is large enough to hold both \p T1 and \p T2.
 * 
 * For example, widening an `int` and a `long` will result in a `long`, since a
 * `long`, by definition, is large enough to hold all integers.
 */
template<typename T1, typename T2>
struct Widened : WidenImpl<T1, T2> {};

template<typename T1, typename T2>
using widen_t = typename Widened<T1, T2>::type;

template<typename AccFn, typename InitT, typename L>
struct Foldl;

template<typename AccFn, typename L>
struct Foldl1;

template<typename T1, typename T2>
struct MulImpl;

template<typename ...Ns>
struct Mul;

template<typename T1, typename T2>
struct add_impl_ {
  ZEN_MISSING_IMPLEMENTATION(T1, Add);
};

template<typename ...Ts>
struct Add;

template<typename T1, typename T2>
struct sub_impl_ {
  ZEN_MISSING_IMPLEMENTATION(T1, Sub);
};

template<typename ...Ts>
struct Sub;

template<typename ...Ts>
using mult_t = typename Mul<Ts...>::type;

template<typename T>
struct DecImpl;

template<typename T>
using dec_ = DecImpl<T>;

template<typename T>
using dec_t = typename dec_<T>::type;

template<typename T>
struct IncImpl;

template<typename T>
using inc_ = IncImpl<T>;

template<typename T>
using inc_t = typename inc_<T>::type;

template<typename N>
struct Fac;

template<typename N>
using FacT = typename Fac<N>::type;

/**
 * @brief Get a pointer-like structure to the next element in a certain container.
 * 
 * @return A maybe type that holds a pointer to the previous value if there is any.
 */
template<typename IterT>
struct Next;

template<typename IterT>
using NextT = typename Next<IterT>::type;

/**
 * @brief Get a pointer-like structure to the previous element in a certain container.
 *
 * @return A maybe type that holds a pointer to the next value if there is any.
 */
template<typename IterT>
struct Prev;

template<typename IterT>
using PrevT = typename Prev<IterT>::type;

template<typename T, typename = void>
struct DerefImpl;

template<typename T>
struct Deref;

template<typename T>
using DerefT = typename Deref<T>::type;

template<typename ElementT, typename RangeT, typename I>
struct IndexImpl;

template<typename ElementT, typename RangeT>
struct Index : IndexImpl<ElementT, RangeT, U0> {};

template<typename ElementT, typename RangeT>
using IndexT = typename Index<ElementT, RangeT>::type;

template<typename I, typename L, typename Enabler = void>
struct Take :
  Define<
    Cond<
      Case<Eq<I, U0>, Tuple<>>,
      Case<IsEmpty<L>, $fail_>,
      Else<Prepend<Head<L>, Take<dec_<I>, Tail<L>>>>
    >
 > {};

template<typename I, typename RangeT>
using TakeT = typename Take<I, RangeT>::type;

/**
 * @brief Discard a fixed amount of elements from the end of a list.
 * 
 * This metafunction constructs a new list that only contains the first K
 * elements that remain after dropping N elements from the end of the list.
 */
template<typename N, typename L>
struct DropLast : Define<Take<Sub<Size<L>, N>, L>> {};

template<typename N, typename TupleT>
using DropLastT = typename DropLast<N, TupleT>::type;

/**
 * @ingroup MetaMaybe
 * @brief A maybe-type that indicates no value is held.
 *
 * @see none_
 * @see some_t
 * @see is_none_v
 */
struct NoneTag;

/**
 * @ingroup MetaMaybe
 * @brief Constructs a maybe-type that holds nothing.
 *
 * @see none_t
 * @see Some
 * @see IsNone
 */
struct None { using type = NoneTag; };

template<> struct IsMeta<None> : True {};

template<typename T>
struct Some {

  static constexpr bool has_some = true;

  using Type = T;

};

template<typename T> struct IsMeta<Some<T>> : True {};

template<typename T> struct some_ { using type = Some<T>; };

template<typename T> struct DerefImpl<Some<T>> { using type = T; };

template<>
struct IsEmpty<None> : True {};

template<typename T>
struct IsEmpty<Some<T>> : False {};

template<typename MaybeT>
struct IsSome : False {};

template<typename T>
struct IsSome<Some<T>> : True {};

template<typename T>
struct BeginImpl;

template<typename T>
struct EndImpl;

template<typename ...Ts>
struct Lambda {
  static_assert(sizeof...(Ts) > 0, "a lambda expression must at least contain a body");
};

template<typename ...CaseTs>
struct Cond {
  static_assert(sizeof...(CaseTs) > 0, "a conditional must contain at least one case");
};

template<typename TestT, typename ThenT, typename ElseT>
struct _IfNode;

template<typename ParamL, typename BodyT>
struct _LamdaNode;

template<typename FnT, typename ArgL>
struct _ApplyNode;

struct _FailNode;

template<typename ...CaseTs>
struct _CompileCondHelper;

template<>
struct _CompileCondHelper<> {
  using Type = _FailNode;
};

template<typename TestT, typename ThenT, typename ...CaseTs>
struct _CompileCondHelper<Case<TestT, ThenT>, CaseTs...> {
  using Type = _IfNode<compile_t<TestT>, compile_t<ThenT>, typename _CompileCondHelper<CaseTs...>::type>;
};

template<typename T>
struct Compile {
  using Type = T;
};

template<typename ...CaseTs>
struct Compile<Cond<CaseTs...>> : _CompileCondHelper<CaseTs...> {};

template<typename TestT, typename ThenT, typename ElseT>
struct Compile<If<TestT, ThenT, ElseT>> {
  using Type = _IfNode<compile_t<TestT>, compile_t<ThenT>, compile_t<ElseT>>;
};

template<typename ...Ts>
struct Compile<Lambda<Ts...>> {
  using Type = _LamdaNode<DropLastT<U1, Tuple<Ts...>>, compile_t<last_t<Tuple<Ts...>>>>;
};

template<template<typename ...> class T, typename ...Ts>
struct Compile<T<Ts...>> : BIf<is_meta<T<Ts...>>, T<Ts...>, _ApplyNode<Template<T>, Tuple<compile_t<Ts>...>>> {};

template<typename Fn, typename EnvT>
struct _ClosureNode {
  using Func = Fn;
  using Env = EnvT;
};

template<typename T, typename EnvT>
struct Eval {
  //static_assert(is_primitive_v<T>, "could not evaluate type at compile-time because it does not resolve to a primitive type");
  using Type = T;
};

template<typename EnvT, bool B, typename ThenT, typename ElseT>
struct _EvalIfHelper {
  using Type = eval_t<ThenT, EnvT>;
};

template<typename EnvT, typename ThenT, typename ElseT>
struct _EvalIfHelper<EnvT, false, ThenT, ElseT> {
  using Type = eval_t<ElseT, EnvT>;
};

template<typename EnvT, typename TestT, typename ThenT, typename ElseT>
struct Eval<_IfNode<TestT, ThenT, ElseT>, EnvT> {
  using Type = typename _EvalIfHelper<EnvT, eval_t<TestT, EnvT>::value, ThenT, ElseT>::type;
};

template<typename FnV, typename ArgL, typename EnvT = map_t<>>
struct _EvalApplyHelper;

template<typename EnvT, template <typename ...> class T, typename ...As>
struct _EvalApplyHelper<EnvT, Template<T>, Tuple<As...>> {
  using _IntermediateType = T<eval_t<As, EnvT>...>;
  using Type = BIf<is_meta<_IntermediateType>, typename _IntermediateType::Type, _IntermediateType>;
};

template<typename E, typename L>
struct Append :
  Define<
    Cond<
      Case<IsEmpty<L>, Tuple<E>>,
      Else<Append<Head<L>, Prepend<E, Tail<L>>>>
    >
  > {};

template<typename E, typename L>
using AppendT = typename Append<E, L>::Type;

template<typename F, typename L, size_t i>
struct _FindHelper :
  Define<
    Cond<
      Case< Apply<F, Head<L> >, U < i > >,
      Else < _FindHelper<F, Tail<L>, i+1 > >
    >
  > {};

template<typename F, typename L>
using Find = _FindHelper<F, L, 0>;

template<typename F, typename L>
using FindT = typename Find<F, L>::type;

/**
 * @brief Override all overlapping key-value pairs in L1 with their counterparts in L1.
 * 
 * If the two lists contain the same key K, the value associated with K in L2
 * will be used in the resulting list.
 */
template<typename L1, typename L2>
struct Override :
  Define<
    Cond<
      Case<IsEmpty<L2>, L1>,
      Case<IsEmpty<L1>, L2>,
      Else<Prepend<Head<L2>, Override<Tail<L1>, Tail<L2>>>>
    >
  > {};

template<typename L1, typename L2>
using OverrideT = typename Override<L1, L2>::Type;

template<typename EnvT, typename ParamL, typename BodyT, typename ArgL>
struct _EvalApplyHelper<_LamdaNode<ParamL, BodyT>, ArgL, EnvT> {
  using type = eval_t<BodyT, OverrideT<EnvT, ApplyT<Template<map_t>, ZipT<ParamL, ArgL>>>>;
};

template<typename Env1, typename Fn, typename Env2, typename ArgL>
struct _EvalApplyHelper<_ClosureNode<Fn, Env2>, ArgL, Env1> {
  using type = typename _EvalApplyHelper<OverrideT<Env1, Env2>, Fn, ArgL>::type;
};

// FIXME Do we really need this?
template<typename Fn, typename EnvT, typename ArgL>
struct Apply<_ClosureNode<Fn, EnvT>, ArgL> {
  using Type = typename _EvalApplyHelper<Fn, ArgL>::type;
};

template<typename EnvT, typename Fn, typename ArgL>
struct Eval<_ApplyNode<Fn, ArgL>, EnvT> {
  using type = typename _EvalApplyHelper<EnvT, eval_t<Fn, EnvT>, ArgL>::type;
};

// template<typename EnvT, template <typename ...> class Fn, typename ...Ts>
// struct eval_<Apply<Template<Fn>, Tuple<Ts...>>, EnvT> {
//   using intermediate_type = Fn<eval_t<Ts, EnvT>...>;
//   using type = std::conditional_t<is_primitive_v<intermediate_type>, intermediate_type, typename intermediate_type::type>;
// };

// template<typename EnvT, typename ArgL, typename ...Ls>
// struct eval_<Apply<lambda_<Ls...>, ArgL>, EnvT> {
// 
//   using param_types = drop_last_t<u1_, Tuple<Ls...>>;
//   using body_type = at_t<u_<sizeof...(Ls)-1>, Tuple<Ls...>>;
// 
//   template<typename T>
//   struct subst_binders_ {
//     static_assert(is_primitive_v<T>, "only primitive values should use the identity substitution");
//     using type = T;
//   };
// 
//   template<typename Fn, typename ...Ts>
//   struct subst_binders_<Apply<Fn, Tuple<Ts...>>> {
//     using type = Apply<Fn, Tuple<subst_binders_<Ts>...>>;
//   };
// 
//   template<typename Fn, typename ...Ts>
//   struct subst_binders_<call_<Fn, Tuple<Ts...>>> {
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
//     using type = lambda_<set_at_t<u_<sizeof...(Rs)-1>, subst_binders_<last_t<Tuple<Rs...>>>, Tuple<Rs...>>>;
//   };
// 
//   template<size_t I>
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
// struct eval_<call_<Fn, ArgTs...>, EnvT> : eval_<Apply<Fn, Tuple<ArgTs...>>> {};

template<typename EnvT>
struct Eval<_FailNode, EnvT> {
  static_assert(_StaticAssertHelper<EnvT>::value, "failed to evaluate expression");
};

template<typename EnvT, typename ParamL, typename BodyT>
struct Eval<_LamdaNode<ParamL, BodyT>, EnvT> {
  using Type = _ClosureNode<_LamdaNode<ParamL, BodyT>, EnvT>;
};

// template<typename N, typename ListT, size_t I> 
// struct next_n_impl_<N, list_iterator_t<ListT, I>> {
//   using type = If<
//     I + N::value >= std::tuple_size<ListT>::value,
//     none_,
//     list_iterator_t<ListT, I+N::value>
//   >;
// };

template<typename EnvT, size_t I>
struct Eval<Binder<I>, EnvT> {
  using Type = DerefT<AtT<Binder<I>, EnvT>>;
};

// template<typename N, typename ListT, size_t I>
// struct prev_n_impl_<N, list_iterator_t<ListT, I>> {
//   using type = IfT<
//     N::value <I>,
//     list_iterator_t<ListT, I - N::value>,
//     none_
//   >;
// };

// template<typename ...Ts>
// struct begin_impl_<Tuple<Ts...>> {
//   using type = list_iterator_t<Tuple<Ts...>, 0>;
// };

template<typename T1, typename T2, typename>
struct EqImpl : False {};

template<typename T>
struct EqImpl<T, T> : True {};

template<typename T1, typename T2>
struct Eq : EqImpl<T1, T2> {};

template<typename ...Ts>
struct SizeImpl<Tuple<Ts...>> : U<sizeof...(Ts)> {};

template<typename ...Ts> 
struct SizeImpl<map_t<Ts...>> : U<sizeof...(Ts)> {};

template<typename T>
struct Size : SizeImpl<T> {};

template<typename T>
struct IsEmpty : Define<Eq<Size<T>, U0>> {};

template<typename T>
struct Last 
  : Define<
    If<
      Eq<Size<T>,U1>,
      Head<T>,
      Last<Tail<T>>
    >
  > {};

template<typename I, typename T>
struct At : AtImpl<I, T> {};

template<typename T, typename I>
struct AtImpl {
  ZEN_MISSING_IMPLEMENTATION(T, at_);
};

#if ZEN_FEAT_TYPE_PACK_ELEMENT
template<size_t Ix, typename ...Ts>
struct TypePackElement : __type_pack_element<Ix, Ts...> {};
#else
template<size_t Ix, typename T1, typename ...Ts>
struct TypePackElement : TypePackElement<Ix - 1, Ts...> {};

template<typename T1, typename ...Ts>
struct TypePackElement<0, T1, Ts...> {
  using Type = T1;
};
#endif

template<typename T, typename I, typename R>
struct SetAtImpl {
  ZEN_MISSING_IMPLEMENTATION(T, set_at_);
};

template<typename T, typename I, typename R>
struct SetAt : SetAtImpl<T, I, R> {};

template<typename T, typename I, typename R>
using SetAtT = typename SetAt<T, I, R>::type;

template<typename Fn, typename L>
struct Transform 
  : Define<
    Foldl<
      Lambda< _1, _2, Prepend<call_<Fn, _2>, _1> >,
      Tuple<>,
      L
    >
  > {};

// template<typename T, typename ArgL>
// struct apply_impl_ {
//   ZEN_MISSING_IMPLEMENTATION(T, call_);
// };
// 
// template<template<typename ...> class TemplateT, typename ...ArgTs>
// struct apply_impl_<Template<TemplateT>, Tuple<ArgTs...>> {
//   using type = typename TemplateT<ArgTs...>::type;
// };

// template<typename FnT, typename ArgL>
// struct Apply {};
// 
// template<typename FnT, typename ...ArgTs>
// struct call_ : Apply<FnT, Tuple<ArgTs...>> {};

template<typename T1, typename T2>
struct WidenImpl {
  ZEN_MISSING_IMPLEMENTATION(T1, widen_);
};

template<typename T>
struct WidenImpl<T, T> {
  using type = T;
};

template<typename T>
struct Const : Define<Lambda<_1, T>> {};

template<typename AccFn, typename InitT, typename L>
struct Foldl :
  If<
    IsEmpty<L>,
    InitT,
    call_ < AccFn, Head<L>, Foldl<AccFn, InitT, Tail<L>> >
  > {};

template<typename AccFn, typename L>
struct Foldl1 : Define<
    If<
      IsEmpty< Tail <L> >,
      Head<L>,
      call_ < AccFn, Head<L>, Foldl1<AccFn, Tail<L>> >
    >
  > {};

template<typename T1, typename T2>
struct MulImpl {
  ZEN_MISSING_IMPLEMENTATION(T1, Mul);
};

template<typename T1, typename T2, T1 N1, T2 N2>
struct MulImpl<Constant<T1, N1>, Constant<T2, N2>>{
  using type = Constant<widen_t<T1, T2>, N1 * N2>;
};

template<typename ...Ns>
struct Mul : Define<
    Foldl1< Template < MulImpl >, Tuple<Ns...> >
  > {};

template<typename ...Ts>
using MulT = typename Mul<Ts...>::type;

template<typename T, T N>
struct DecImpl<Constant<T, N>> {
  static_assert(N > 0);
  using type = Constant<T, N - 1>;
};

template<typename T>
using Dec = DecImpl<T>;

template<typename T, T N>
struct IncImpl<Constant<T, N>> : Constant<T, N + 1> {};

template<typename T>
using Inc = IncImpl<T>;

template<typename N>
struct Fac : Define<
   Cond<
    Case<Eq<N, U0>, U1>,
    Case<Eq<N, U1>, U1>,
    Else<Mul<Fac<Dec<N>>, N>>
  >
> {};

template<typename N>
using fac_t = typename Fac<N>::type;

template<typename IterT, typename Enabler = void>
struct NextImpl;

template<typename IterT, typename Enabler = void>
struct PrevImpl;

template<typename IterT>
struct Next : NextImpl<IterT> {};

template<typename IterT>
struct Prev : PrevImpl<IterT> {};

template<typename N, typename IterT, typename Enabler = void>
struct NextNImpl
  : Define<
    Cond <
      Case<Bool<N::value == 0>, IterT>,
      Case<IsEmpty<IterT>, None>,
      Else<NextNImpl<Inc<N>, Next<IterT>>>
    >
  > {};

template<typename N, typename IterT, typename Enabler = void>
struct PrevNImpl : Define<
  Cond<
    Case<Bool<N::value == 0>, IterT>,
    Case<IsEmpty<Prev<IterT>>, None>,
    Else<PrevNImpl<Dec<N>, Prev<IterT>>>
  >
> {};

template<typename T, typename>
struct DerefImpl {
  ZEN_MISSING_IMPLEMENTATION(T, deref_);
};

template<typename T>
struct Deref : DerefImpl<T> {};

template<typename BeginT, typename EndT>
struct RangeT {
  using Begin = BeginT;
  using End = EndT;
};

template<typename BeginT, typename EndT>
struct Range {
  using type = Range<BeginT, EndT>;
};

template<typename BeginT, typename EndT>
struct IncImpl<RangeT<BeginT, EndT>> {
  using Type = RangeT<NextT<BeginT>, EndT>;
};

template<typename ...Ts>
struct Add : Define<Foldl1<Template<add_impl_>, Tuple<Ts...>>> {};

template<typename ...Ts>
struct Sub : Define < Foldl1 < Template<sub_impl_>, Tuple<Ts...> > > {};

template<typename ElementT, typename RangeT, typename I>
struct IndexImpl
  : Define<
      Cond<
      Case<IsEmpty<RangeT>, None>,
      Case<Eq<Head<RangeT>, ElementT>, some_<I>>,
      Else<IndexImpl<ElementT, Tail<RangeT>, Inc<I>>>
    >
  > {};

template<typename L1, typename L2>
struct Zip :
  Define<
    Cond<
      Case<And<IsEmpty<L1>, IsEmpty<L2>>, Tuple<>>,
      Case<Or<IsEmpty<L1>, IsEmpty<L2>>, $fail_>,
      Else<Prepend<Tuple<Head<L1>, Head<L2>>, Zip<Tail<L1>, Tail<L2>>>>
    >
  > {};

// The following are specializations of metafunctions that are used
// internally by the evaluator. In order break cyclic dependencies and speed
// up evaluation, the specializations of these metafunctions rely on nothing
// more than a few primitives.

template<typename T1, typename T2, T1 N1, T2 N2>
struct Add<Constant<T1, N1>, Constant<T2, N2>> : Constant<widen_t<T1, T2>, N1 + N2> {};

template<typename T1, typename T2, T1 N1, T2 N2>
struct Sub<Constant<T1, N1>, Constant<T2, N2>> : Constant<widen_t<T1, T2>, N1 - N2> {};

template<typename T1, typename T2, T1 N1, T2 N2>
struct Mul<Constant<T1, N1>, Constant<T2, N2>> : Constant<widen_t<T1, T2>, N1 * N2> {};

template<bool B1, bool B2>
struct And<Constant<bool, B1>, Constant<bool, B2>> : Bool<B1 && B2> {};

template<bool B1, bool B2>
struct Or<Constant<bool, B1>, Constant<bool, B2>> : Bool<B1 || B2> {};

template<typename I, typename ...ElementTs>
struct _FastMapAtHelper : None {};

template<typename I, typename ElementT, typename ...ElementTs>
struct _FastMapAtHelper<I, ElementT, ElementTs...>
  : BIf<
      Eq<
        FirstT<ElementT>,
        I
      >::value,
      Some<
        SecondT<ElementT>
      >,
      typename _FastMapAtHelper<I, ElementTs...>::Type
    > {};

template<typename I, typename ...ElementTs>
struct AtImpl<I, map_t<ElementTs...>> : _FastMapAtHelper<I, ElementTs...> {};

// #define ZEN_MAKE_TYPENAME(i) typename ZEN_PASTE_2(T, i)
// #define ZEN_MAKE_TYPEREF(i) ZEN_PASTE_2(T, i)
// 
//   template<size_t I, typename R, typename TupleT>
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
//   template<size_t I, typename R, typename TupleT>
//   using set_tuple_element_helper_t = typename set_tuple_element_helper_<I, R, TupleT>::type;

// template<typename T1, typename T2, T1 N1, T2 N2>
// struct div_<Constant<T1, N1>, Constant<T2, N2>> : Constant<widen_t<T1, T2>, N1 / N2> {};

// template<>
// struct IsEmpty<Tuple<>> : true_ {};
// 
// template<typename T1, typename ...Ts>
// struct IsEmpty<Tuple<T1, Ts...>> : false_ {};
// 
// template<size_t I, typename ElementT, typename ...Ts>
// struct fast_index_helper_ : none_ {};
// 
// template<size_t I, typename ElementT, typename T1, typename ...Ts>
// struct fast_index_helper_<I, ElementT, T1, Ts...> : std::conditional<eq_v<ElementT, T1>, some_t<u_<I>>, typename fast_index_helper_<I+1, ElementT, Ts...>::type> {};
// 
// template<typename ElementT, typename ...Ts>
// struct index_impl_<ElementT, Tuple<Ts...>> : fast_index_helper_<0, ElementT, Ts...> {};
// 
// template<size_t I, typename LeftL, typename RightL>
// // struct fast_drop_last_helper_;
// struct fast_drop_last_helper_ 
//   : std::conditional<
//     I == 0,
//     RightL,
//     typename fast_drop_last_helper_<I-1, PrependT<head_t<RightL>, LeftL>, tail_t<RightL>>::type
//   > {};
//
// template<size_t I, typename ...Ts>
// struct drop_last_<u_<I>, Tuple<Ts...>> : fast_drop_last_helper_<I, Tuple<>, Tuple<Ts...>> {};
// 
//
// template<size_t I, typename LeftT, typename RightT = Tuple<>>
// struct take_list_helper_;
// 
// template<typename LeftT, typename RightT>
// struct take_list_helper_<0, LeftT, RightT> {
//   using type = RightT;
// };
// 
// template<size_t N, typename L1, typename ...Ls, typename ...Rs>
// struct take_list_helper_<N, Tuple<L1, Ls...>, Tuple<Rs...>> {
//   using type = typename take_list_helper_<N-1, Tuple<Ls...>, Tuple<L1, Rs...>>::type;
// };

template<typename T1, typename T2>
constexpr auto max(T1 x, T2 y) {
  return x > y ? x : y;
}

/**
 * Checks whether a structure actually has a runtime memory footprint or not.
 *
 * Usually, this metafunction relies on a compiler intrinsic because there is
 * no way for `final` classes to be extended, thus preventing SFINAE from being
 * used. See [this StackOverflow answer][1] for more information.
 * 
 * [1]: https://stackoverflow.com/a/35531415/1173521
 */
template<typename T>
struct AllocatesMemory : public Bool<__is_empty(T)> {};

template<typename T, typename = void>
struct IsCollection : False {};

template<typename T>
struct IsCollection<
  T,
  VoidT<
    decltype(declval<T&>().range()),
    decltype(declval<T&>().begin()),
    decltype(declval<T&>().end()),
    typename T::Value,
    typename T::Range,
    typename T::Iterator
  >
> : True {};

/**
 * @brief A metafunction that returns `true` if the provided type is a STL
 * container type.
 */
template <typename T, typename = void>
struct IsContainer : False {};

#if ZEN_STL

template<typename T>
struct IsContainer<T,
    VoidT<
      decltype(declval<T&>().begin()),
      decltype(declval<T&>().end()),
      typename T::value_type
    >
  > : True {};

#endif

ZEN_NAMESPACE_END

#endif // ZEN_META_HPP
