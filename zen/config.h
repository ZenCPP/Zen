#ifndef ZEN_CONFIG_H
#define ZEN_CONFIG_H

#include <stdio.h>
#include <stdlib.h>

#if !defined(ZEN_ENABLE_ASSERTIONS) && !defined(NDEBUG)
# define ZEN_ENABLE_ASSERTIONS 1
#endif

#endif // #ifndef ZEN_CONFIG_H
