
#include "gtest/gtest.h"

#include "zen/clone_ptr.hpp"

struct Point {

  int x, y;

  Point(int x, int y): x(x), y(y) {};

  Point(const Point& other) = default;
  Point(Point&& other)      = default;

};

TEST(clone_ptr, CanPassSimpleStructByValue) {
  zen::clone_ptr<Point> p1 = zen::make_clonable<Point>(1, 2);
  ASSERT_EQ(p1->x, 1);
  ASSERT_EQ(p1->y, 2);
}

