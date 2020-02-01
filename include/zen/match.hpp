#ifndef ZEN_MATCH_HPP
#define ZEN_MATCH_HPP

#include <type_traits>

#include "zen/config.h"
#include "zen/macros.h"

#define ZEN_MATCH_DECLARE_FOR_PATTERN(i,pattern) \
  using zen__pattern__ ## i = decltype(pattern); \
  zen__pattern__ ## i :: value_type match ## i; \
  ZEN_UNUSED(match ## i);

#define Match(...) \
  { \
    ZEN_FOR_EACH(ZEN_MATCH_DECLARE_FOR_PATTERN, __VA_ARGS__) \
    int zen__branch__target = 0; \
    switch (0) { \
      default: { \

#define ZEN_GENERATE_CASE_CONDITION(i, pattern) \
  pattern.matches(zen__expr__ ## i)

#define ZEN_GENERATE_BINDINGS(i, pattern) \
  ;

#define Case(...) \
  } \
  if (ZEN_REPEAT_WITH(&&, ZEN_VA_LENGTH(__VA_ARGS__), ZEN_GENERATE_CASE_CONDITION, __VA_ARGS__) && (ZEN_ENUM_EACH(ZEN_GENERATE_BINDINGS, __VA_ARGS__))) { \
    ZEN_FOR_EACH(ZEN_GENERATE_CASE_BINDING, __VA_ARGS__);

#define Otherwise() \
  } \
  if (zen__branch__target == 0) {

#define EndMatch \
      } \
      break; \
    } \
  }

namespace zen {

  template<typename T>
  struct Bindings;

  template<typename T>
  struct IsPoly {
    static constexpr const bool value = false;
  };

  template<typename T>
  struct TypeOfKind {
    using type = int;
  };

  template<typename T>
  struct IsOfType {
    template<typename R>
    static bool apply(const T& value) {
      return false;
    }
  };

} // of namespace zen

#endif // #ifndef ZEN_MATCH_HPP
