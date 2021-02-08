
#include "gtest/gtest.h"

#include "zen/dllist.hpp"

using namespace zen;

TEST(DLListTest, ReportsCorrectSize) {
  DLList<int> l1;
  ASSERT_EQ(l1.size(), 0);
  l1.append(1);
  ASSERT_EQ(l1.size(), 1);
  l1.append(2);
  ASSERT_EQ(l1.size(), 2);
  l1.append(3);
  ASSERT_EQ(l1.size(), 3);
  l1.append(4);
  ASSERT_EQ(l1.size(), 4);
}

TEST(DLListTest, CanIterate) {
  std::size_t k = 1;
  DLList<int> l1;
  l1.append(1);
  l1.append(2);
  l1.append(3);
  l1.append(4);
  for (auto i: l1) {
    ASSERT_EQ(i, k);
    k++;
  }
}

TEST(DLListTest, CanInsert) {
  DLList<int> l1;
  l1.append(1);
  l1.append(3);
  l1.append(4);
  l1.insert_after(l1.begin(), 2);
  ASSERT_EQ(l1[0], 1);
  ASSERT_EQ(l1[1], 2);
  ASSERT_EQ(l1[2], 3);
  ASSERT_EQ(l1[3], 4);
}

