
#include <gtest/gtest.h>

#include "zen/either.hpp"
#include "util.hpp"

TEST(EitherTest, CanMakeLeftRight) {
  zen::Either<int, float> e1 = zen::left(1);
  zen::Either<int, float> e2 = zen::right(1.0);
}

TEST(EitherTest, CallsDestructor) {
  int leftDestrCnt = 0, rightDestrCnt = 0;
  {
    zen::left(B(leftDestrCnt));
  }
  {
    zen::right(B(rightDestrCnt));
  }
  ASSERT_GT(leftDestrCnt, 0);
  ASSERT_GT(rightDestrCnt, 0);
}

TEST(EitherTest, RetainsEntirePolyDuringCopy) {
  zen::Either<int, A> e1 = zen::right(C {});
  e1.right();
  // ASSERT_EQ(static_cast<C&>(a1.get()).someData, 0x34);
  // zen::Either<A, int> e2 = zen::left(C {});
  // auto a2 = e2.left();
  // ASSERT_EQ(static_cast<C&>(a2.get()).someData, 0x34);
}

TEST(EitherTest, CanLeftMap) {
  zen::Either<int, float> e1 = zen::left(1);
  int res = e1.mapLeft([](int val) { return val + 1; }).left().orElse(3);
  ASSERT_EQ(res, 2);
}

TEST(EitherTest, CanRightMap) {
  zen::Either<int, float> e1 = zen::right(1);
  int res = e1.mapRight([](int val) { return val + 1; }).right().orElse(3);
  ASSERT_EQ(res, 2);
}

