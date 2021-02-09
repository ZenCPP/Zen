#ifndef ZEN_BYTE_HPP
#define ZEN_BYTE_HPP

#include "zen/config.h"

ZEN_NAMESPACE_START

using Byte = unsigned char;

#define ZEN_BYTE_LITERAL(literal) ((const Byte*)(literal))

ZEN_NAMESPACE_END

#endif // of #ifndef ZEN_BYTE_HPP
