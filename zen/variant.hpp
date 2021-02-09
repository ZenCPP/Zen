#ifndef ZEN_VARIANT_HPP
#define ZEN_VARIANT_HPP

#include <variant>

ZEN_NAMESPACE_START

template<typename ...Ts>
using variant = std::variant<Ts...>;

ZEN_NAMESPACE_END

#endif // of #ifndef ZEN_VARIANT_HPP
