
#include "gtest/gtest.h"

#include "zen/value_ptr.hpp"

struct Point {

  int x, y;

  Point(int x, int y): x(x), y(y) {};

  Point(const Point& other) = default;
  Point(Point&& other)      = default;

};

TEST(ValuePtr, CanPassSimpleStructByValue) {
  zen::ValuePtr<Point> p1 = zen::make_value_ptr<Point>(1, 2);
  ASSERT_EQ(p1->x, 1);
  ASSERT_EQ(p1->y, 2);
}

