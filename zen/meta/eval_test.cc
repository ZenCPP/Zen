
#include "zen/meta/eval.hpp"
#include "zen/meta/math.hpp"

using namespace zen;

// static_assert(eq_<int, int>::value);
// static_assert(!eq_<float, int>::value);
// static_assert(eq_<u1_, u1_>::value);
// static_assert(!eq_<u1_, u2_>::value);

static_assert(mult_t<u1_, u2_>::value == 2);

static_assert(eval_t<u1_>::value == 1);

// static_assert(eval_t<_1, list_<u0_>>::value == 0);

static_assert(eval_t<mult_<inc_<u2_>, u3_>>::value == 9);

static_assert(fac_t<u2_>::value == 2);

// Test whether mutual recursion works as expected

template<typename N>
struct is_even_;

template<typename N>
struct is_odd_;

template<typename N>
struct is_even_ : defun_t< if_<eq_<N, u0_>, true_, is_odd_<dec_<N>>> > {};

template<typename N>
struct is_odd_ : defun_t< if_<eq_<N, u0_>, false_, is_even_<dec_<N>>> > {};

static_assert(is_odd_<u0_>::type::value == false);
static_assert(is_odd_<u1_>::type::value == true);
static_assert(is_odd_<u2_>::type::value == false);
static_assert(is_odd_<u3_>::type::value == true);
static_assert(is_even_<u0_>::type::value == true);
static_assert(is_even_<u1_>::type::value == false);
static_assert(is_even_<u2_>::type::value == true);
static_assert(is_even_<u3_>::type::value == false);

// template<typename N>
// struct fac_test_ : defun_t<
//    compile_t<
//      cond_<
//         case_<eq_<_1, u0_>, u1_>,
//         case_<eq_<_1, u1_>, u1_>,
//         else_<mult_<call_<fac_test_, dec_<_1>>, _1>>
//       >
//     >,
//     N
//   > {}; 

