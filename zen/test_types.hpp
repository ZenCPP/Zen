#ifndef ZEN_TEST_TYPES_HPP
#define ZEN_TEST_TYPES_HPP

#include <utility>

namespace zen {

  class point {
  public:

    int x;
    int y;

    inline point(int x, int y):
      x(x), y(y) {};

    inline point(point&& other):
      x(std::move(other.x)), y(std::move(other.y)) {};
  
    inline point(const point& other):
      x(other.x), y(other.y) {};

  };

  class shape {
  public:
    virtual ~shape() {};
  };

  class rect : public shape {
  public:

    int width;
    int height;

    rect(int width, int height):
      width(width), height(height) {};

   };

}

#endif // ZEN_TEST_TYPES_HPP
