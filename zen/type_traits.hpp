#ifndef ZEN_TYPE_TRAITS_HPP
#define ZEN_TYPE_TRAITS_HPP

#include "zen/meta/primitives.hpp"

namespace zen {

  template <typename T, typename = void>
  struct is_container_ : false_ {};

}

#endif // ZEN_TYPE_TRAITS_HPP
