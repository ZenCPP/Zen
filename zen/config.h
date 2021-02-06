#ifndef ZEN_CONFIG_H
#define ZEN_CONFIG_H

#include <stdio.h>
#include <stdlib.h>

#if !defined(ZEN_ENABLE_ASSERTIONS) && !defined(NDEBUG)
# define ZEN_ENABLE_ASSERTIONS 1
#endif

#define ZEN_AUTO_SIZE (-1)

#endif // #ifndef ZEN_CONFIG_H
