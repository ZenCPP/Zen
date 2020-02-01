#ifndef ZEN_REFLECT_HPP
#define ZEN_REFLECT_HPP

#include <any>

#include "zen/lens.hpp"

namespace zen {

  template<typename T>
  using reflect = sequence_map<std::string, lens<T, std::any>>;

  template<typename T>
  struct base_class;

  template<typename T>
  struct reflection;

#define ZEN_DECLARE_REFLECTION(type) \
    template<> \
    struct reflection<type> { \
      static const reflect<type> value; \
    };

#define ZEN_REFLECT_INIT(type) \
  const reflect<type> reflection<type>::value =

#define ZEN_DECLARE_BASE_CLASS(derived, base) \
  template<> \
  struct base_class<derived> { \
    using type = base; \
  };

}

#endif // ZEN_REFLECT_HPP
