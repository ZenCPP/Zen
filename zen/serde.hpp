#ifndef ZEN_SERDE_HPP
#define ZEN_SERDE_HPP

#include "zen/value.hpp"
#include "zen/lens.hpp"
#include "zen/reflect.hpp"

namespace zen {

  template<typename T>
  value serialize(const T& obj) {
    zen::object out;
    for (auto& [name, lens]: reflection<T>::value) {
      out.add_prop(name, get(obj, lens));
    };
    return out;
  }

}

#endif // ZEN_SERDE_HPP
