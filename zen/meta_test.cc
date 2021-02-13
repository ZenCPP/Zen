
#if ZEN_STL
#include <string>
#endif

#include "zen/meta.hpp"

using namespace ZEN_NAMESPACE;

static_assert(Size<Tuple<U1, U2>>::value == 2);

using P1 = PrependT<U1, Tuple<U1>>;

static_assert(Size<P1>::value == 2);

#if ZEN_STL
static_assert(IsContainer<std::string>::value == true);
#endif