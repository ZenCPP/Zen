
#include "zen/empty.hpp"
#include "zen/test_types.hpp"

namespace zen {

  // Test the nullability of built-in types

  // TODO complete this by testing all built-in types

  static_assert(!is_nullable_v<char>);
  static_assert(!is_nullable_v<signed char>);
  static_assert(!is_nullable_v<unsigned char>);
  static_assert(!is_nullable_v<unsigned int>);
  static_assert(!is_nullable_v<signed int>);
  static_assert(!is_nullable_v<int>);
  static_assert(!is_nullable_v<float>);
  static_assert(!is_nullable_v<double>);
  static_assert(!is_nullable_v<char>);

  // Test the public API for adding a nullable type

  template<>
  struct is_nullable_impl_<point> : true_ {};

  static_assert(is_nullable_v<point>);

}
