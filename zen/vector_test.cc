
#include "gtest/gtest.h"

#include "zen/vector.hpp"

using namespace zen;

TEST(VectorTest, GrowsWhenInsertingElements) {
  Vector<int> v1(4);
  ASSERT_EQ(v1.capacity(), 4);
  v1.append(1);
  v1.append(2);
  v1.append(3);
  v1.append(4);
  v1.append(5);
  v1.append(6);
  ASSERT_EQ(v1[0], 1);
  ASSERT_EQ(v1[1], 2);
  ASSERT_EQ(v1[2], 3);
  ASSERT_EQ(v1[3], 4);
  ASSERT_EQ(v1[4], 5);
  ASSERT_EQ(v1[5], 6);
}

