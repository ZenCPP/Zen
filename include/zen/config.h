#ifndef ZEN_CONFIG_H
#define ZEN_CONFIG_H

#include <stdio.h>
#include <stdlib.h>

#define ZEN_FAIL(...)                                            \
  fprintf(stderr, "%s:%i: %s", __FILE__, __LINE__, __VA_ARGS__); \
  exit(EXIT_FAILURE);

#if !defined(ZEN_ENABLE_ASSERTIONS) && !defined(NDEBUG)
# define ZEN_ENABLE_ASSERTIONS 1
#endif

#if ZEN_ENABLE_ASSERTIONS
# define ZEN_ASSERT(cond)                      \
    if (!(cond)) {                             \
      ZEN_FAIL("assertion " #cond " failed"); \
    }
#else
# define ZEN_ASSERT(cond)
#endif

#endif // #ifndef ZEN_CONFIG_H
