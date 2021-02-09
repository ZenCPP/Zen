
#include "gtest/gtest.h"

#include "zen/either.hpp"

using namespace ZEN_NAMESPACE;

TEST(Either, CanConstructLeftValue) {
  Either<int, bool> e1 = left(10);
  ASSERT_TRUE(e1.is_left());
  ASSERT_EQ(e1.left(), 10);
}

