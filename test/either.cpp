
#include "gtest/gtest.h"

#include "zen/either.hpp"

TEST(Either, CanConstructLeftValue) {
  zen::Either<int, bool> e1 = zen::make_left(10);
  ASSERT_TRUE(e1.is_left());
  ASSERT_EQ(e1.unwrap_left(), 10);
}

