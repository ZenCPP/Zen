
#include "gtest/gtest.h"

#include "zen/reflect.hpp"
#include "zen/serde.hpp"
#include "zen/test_types.hpp"

using namespace zen;

ZEN_DECLARE_FIELD(Point, x)
ZEN_DECLARE_FIELD(Point, y)
// ZEN_DECLARE_GETTER(Rect, width, get_width);
// ZEN_DECLARE_GETTER(Rect, height, get_height);

TEST(SerdeTest, CanSerializeValue) {
  
}

