
#include "gtest/gtest.h"

#include "zen/test_types.hpp"
#include "zen/clone.hpp"

using namespace zen;

TEST(Clone, CanCloneSharedPtr) {
  auto ptr1 = std::make_shared<rect>(500,100);
  auto ptr2 = zen::clone(ptr1);
}

TEST(Clone, CanCloneLValue) {
  rect rect1 { 500, 100 };
  rect rect2 = zen::clone(rect1);
  ASSERT_EQ(rect2.width, 500);
  ASSERT_EQ(rect2.height, 100);
}

