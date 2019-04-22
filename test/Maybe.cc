
#include <gtest/gtest.h>

#include "zen/maybe.hpp"
#include "util.hpp"

TEST(MaybeTest, CanHoldPoly) {
  int destroyCount = 0;
  zen::Maybe<B> m1 = zen::some(B(destroyCount));
  ASSERT_EQ(m1.get().someData, 43);
}

TEST(MaybeTest, OrElseWorks) {
  ASSERT_EQ(zen::some(1).orElse(2), 1);
  ASSERT_EQ(zen::Maybe<int>().orElse(2), 2);
}

