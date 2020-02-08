
#include "zen/meta/math.hpp"

using namespace zen;

static_assert(zen::fac_t<zen::u3_>::value == 6);
static_assert(zen::eval_t<zen::if_<zen::bool_<1 == 1>, zen::u1_, zen::u2_>>::value == 1, "");


