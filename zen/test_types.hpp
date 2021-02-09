#ifndef ZEN_TEST_TYPES_HPP
#define ZEN_TEST_TYPES_HPP

#include <utility>

namespace zen {

  class Point {
  public:

    int x;
    int y;

    inline Point(int x, int y):
      x(x), y(y) {}

    inline Point(const Point& other):
      x(other.x), y(other.y) {}

    inline Point(Point&& other):
      x(std::move(other.x)), y(std::move(other.y)) {}

  };

  class Shape {
  public:
    virtual ~Shape() {}
  };

  class Rect : public Shape {
  public:

    int width;
    int height;

    Rect(int width, int height):
      width(width), height(height) {}

   };

}

#endif // ZEN_TEST_TYPES_HPP
