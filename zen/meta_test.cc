
#include "zen/meta.hpp"

using namespace zen;

static_assert(zen::size_v<list_t<u1_, u2_>> == 2);

using p1 = rcons_t<u1_, list_t<u1_>>;

static_assert(size_v<p1> == 2);

