
#include "gtest/gtest.h"

#include "zen/either.hpp"

TEST(Either, CanConstructLeftValue) {
  zen::either<int, bool> e1 = zen::left(10);
  ASSERT_TRUE(e1.is_left());
  ASSERT_EQ(e1.left(), 10);
}

