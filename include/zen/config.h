
#pragma once

#include <stdio.h>
#include <stdlib.h>

#define ZEN_FAIL(...)                                            \
  fprintf(stderr, "%s:%i: %s", __FILE__, __LINE__, __VA_ARGS__); \
  exit(EXIT_FAILURE);

