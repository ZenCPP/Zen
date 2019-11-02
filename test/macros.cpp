
#include "zen/macros.h"

#include "gtest/gtest.h"

ZEN_STATIC_ASSERT(ZEN_VA_LENGTH(0,1,2,3) == 4);
ZEN_STATIC_ASSERT(ZEN_VA_LENGTH(foo,bar,baz) == 3);

ZEN_STATIC_ASSERT(ZEN_GET_VA_ARG(0, 1,2,3,4) == 1);
ZEN_STATIC_ASSERT(ZEN_GET_VA_ARG(1, 1,2,3,4) == 2);
ZEN_STATIC_ASSERT(ZEN_GET_VA_ARG(2, 1,2,3,4) == 3);
ZEN_STATIC_ASSERT(ZEN_GET_VA_ARG(3, 1,2,3,4) == 4);

// Some macros can only be tested by actually generating code.
// We try to infer if the generated code is correct by performing
// some run-time tests on it.

#define ZEN_ASSIGN_INDEXED(i, value, ...) var ## i = value

TEST(Macro, EnumMacroWorks) {

  bool ZEN_ENUM(3, ZEN_ASSIGN_INDEXED, true);

  ASSERT_TRUE(var0);
  ASSERT_TRUE(var1);
  ASSERT_TRUE(var2);
}

#define ZEN_ADD_CONST_TO_INDEX(i, k, ...) i * k

TEST(Macro, RepeatWithMacroWorks) {
  int result = ZEN_REPEAT_WITH(+, 3, ZEN_ADD_CONST_TO_INDEX, 4);
  ASSERT_EQ(result, 12);
}

TEST(Macro, RepeatWithMacroWorksWithNonTrivialAmount) {
  int result = ZEN_REPEAT_WITH(+, ZEN_VA_LENGTH(foo,bar,baz), ZEN_ADD_CONST_TO_INDEX, 4);
  ASSERT_EQ(result, 12);
}

#define ZEN_INIT_BOOL(i, value, ...) bool var ## i = value;

TEST(Macro, RepeatMacroWorks) {

  ZEN_REPEAT(3, ZEN_INIT_BOOL, true)

  ASSERT_TRUE(var0);
  ASSERT_TRUE(var1);
  ASSERT_TRUE(var2);
}

#define DECLARE_VARS_NUMBERED(i, name) bool name ## i = true;

TEST(Macro, ForEachMacroWorks) {
  ZEN_FOR_EACH(DECLARE_VARS_NUMBERED, foo, bar, baz);
  // ASSERT_TRUE(foo0);
  // ASSERT_TRUE(bar1);
  // ASSERT_TRUE(baz2);
}

