#ifndef ZEN_SERDE_HPP
#define ZEN_SERDE_HPP

#include "zen/config.h"
#include "zen/value.hpp"
#include "zen/lens.hpp"
#include "zen/reflect.hpp"

ZEN_NAMESPACE_START

template<typename T>
Value serialize(const T& obj) {
  Object out;
  for (auto& [name, lens]: get_reflection<T>()) {
    out.set_property(name, get(obj, lens));
  };
  return out;
}

ZEN_NAMESPACE_END

#endif // ZEN_SERDE_HPP
