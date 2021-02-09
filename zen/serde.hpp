#ifndef ZEN_SERDE_HPP
#define ZEN_SERDE_HPP

#include "zen/value.hpp"
#include "zen/lens.hpp"
#include "zen/reflect.hpp"

namespace zen {

  template<typename T>
  Value serialize(const T& obj) {
    Object out;
    for (auto& [name, lens]: get_reflection<T>()) {
      out.set_property(name, get(obj, lens));
    };
    return out;
  }

}

#endif // ZEN_SERDE_HPP
