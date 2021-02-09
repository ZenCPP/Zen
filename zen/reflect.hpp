#ifndef ZEN_REFLECT_HPP
#define ZEN_REFLECT_HPP

#include <any>

#include "zen/config.h"
#include "zen/lens.hpp"
#include "zen/sequence_map.hpp"

ZEN_NAMESPACE_START

  template<typename T>
  using Reflection = sequence_map<std::string, Lens<T, std::any>>;

  template<typename T>
  struct base_class;

  template<typename T>
  static Reflection<T> reflection;

  template<typename T>
  inline Reflection<T>& get_reflection() {
    return reflection<T>;
  }

#define ZEN_DECLARE_REFLECTION(type) \
    template<> \
    struct Reflect<type> { \
      static const reflect<type> value; \
    };

#define ZEN_REFLECT_INIT(type) \
  const Reflection<type> Reflect<type>::value = 

#define ZEN_DECLARE_FIELD(classname, fieldname) \
  ZEN_STATIC_BLOCK { \
    reflection<classname>.emplace(#fieldname, make_any_lens(&classname::fieldname)); \
  }

#define ZEN_DECLARE_BASE_CLASS(derived, base) \
  template<> \
  struct base_class<derived> { \
    using type = base; \
  };

ZEN_NAMESPACE_END

#endif // ZEN_REFLECT_HPP
