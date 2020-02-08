#ifndef ZEN_VECTOR_HPP
#define ZEN_VECTOR_HPP

#include <vector>

#include "zen/meta/primitives.hpp"
#include "zen/type_traits.hpp"

namespace zen {

  template<typename T, typename Allocator = std::allocator<T>>
  using vector = std::vector<T, Allocator>;

  template<typename T, typename Allocator>
  struct is_container_<std::vector<T, Allocator>> : true_ {};

}

#endif // ZEN_VECTOR_HPP
