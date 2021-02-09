
#include "gtest/gtest.h"

#include "zen/common.hpp"

#include "zen/test_types.hpp"

using namespace zen;

TEST(Clone, CanCloneSharedPtr) {
  auto ptr1 = std::make_shared<Rect>(500,100);
  auto ptr2 = clone(ptr1);
}

TEST(Clone, CanCloneLValue) {
  Rect rect1 { 500, 100 };
  Rect rect2 = clone(rect1);
  ASSERT_EQ(rect2.width, 500);
  ASSERT_EQ(rect2.height, 100);
}

