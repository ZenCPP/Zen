#ifndef ZEN_META_MAYBE_TYPES_HPP
#define ZEN_META_MAYBE_TYPES_HPP

#include <type_traits>

#include "zen/meta/primitives.hpp"

namespace zen {

  template<typename T>
  struct some_ {
    static constexpr const bool has_value = true;
    using type = T;
  };

  struct none_ {
    static constexpr const bool has_value = false;
  };

  template<typename T>
  struct is_none_ : false_ {};

  template<>
  struct is_none_<none_> : true_ {};

}


#endif // ZEN_META_MAYBE_TYPES_HPP
