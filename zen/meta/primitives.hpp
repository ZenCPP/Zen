#ifndef ZEN_META_PRIMITIVES_HPP
#define ZEN_META_PRIMITIVES_HPP

#include <type_traits>
#include <tuple>

namespace zen {

  template<bool B>
  using bool_ = std::integral_constant<bool, B>;

  struct true_ : bool_<true> {};
  struct false_ : bool_<false> {};

  template<std::size_t I>
  using u_ = std::integral_constant<std::size_t, I>;

  using u0_ = u_<0>;
  using u1_ = u_<1>;
  using u2_ = u_<2>;
  using u3_ = u_<3>;
  using u4_ = u_<4>;
  using u5_ = u_<5>;
  using u6_ = u_<6>;
  using u7_ = u_<7>;
  using u8_ = u_<8>;
  using u9_ = u_<9>;

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

  template<template<typename ...> class Template>
  struct template_ {
    template<typename ...Ts>
    struct apply {
      using type = Template<Ts...>;
    };

  };

} // of namespace zen

#endif // ZEN_META_PRIMITIVES_HPP
