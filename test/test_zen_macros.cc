
#include <gtest/gtest.h>

#include "zen/macros.h"

// Tests for ZEN_HAS_COMMA

static_assert(ZEN_HAS_COMMA() == 0);
static_assert(ZEN_HAS_COMMA(a) == 0);
static_assert(ZEN_HAS_COMMA(,) == 1);
static_assert(ZEN_HAS_COMMA(a,) == 1);
static_assert(ZEN_HAS_COMMA(,b) == 1);
static_assert(ZEN_HAS_COMMA(a,b) == 1);
static_assert(ZEN_HAS_COMMA(a,b,) == 1);

// Tests for ZEN_NARGS

static_assert(ZEN_NARGS() == 1);
static_assert(ZEN_NARGS(a) == 1);
static_assert(ZEN_NARGS(a,b) == 2);
static_assert(ZEN_NARGS(a,b,c) == 3);
static_assert(ZEN_NARGS(a,b,c,d) == 4);
static_assert(ZEN_NARGS(a,b,c,d,e) == 5);

static_assert(ZEN_NARGS(,) == 2);
static_assert(ZEN_NARGS(,,) == 3);

#define PAIR1 (1, 2)
#define PAIR2 (3, 4)
#define PAIR3 (5, 6)

static_assert(ZEN_NARGS(PAIR1, PAIR2, PAIR3) == 3);

// Tests for the ZEN_IS_EMPTY helper macro

static_assert(ZEN_IS_EMPTY() == 1);
static_assert(ZEN_IS_EMPTY(a) == 0);

// Tests for ZEN_NARG that relies on the previous macros

static_assert(ZEN_NARG() == 0);
static_assert(ZEN_NARG(a) == 1);
static_assert(ZEN_NARG(a,b) == 2);
static_assert(ZEN_NARG(a,b,c) == 3);
static_assert(ZEN_NARG(a,b,c,d) == 4);
static_assert(ZEN_NARG(a,b,c,d,e) == 5);

static_assert(ZEN_NARG(,) == 2);
static_assert(ZEN_NARG(,,) == 3);

static_assert(ZEN_NARG(1, 2, 3) == 3);

// The following tests are runtime tests because some of them generate
// code that cannot be evaluated by the compiler.

TEST(Macro, CanUseForLoop) {
  int test[] = { 0,0,0,0 };
#define FOR_CALLBACK(i,name) name[i] = i;
  ZEN_FOR(4,FOR_CALLBACK,test);
  ASSERT_EQ(test[0], 0);
  ASSERT_EQ(test[1], 1);
  ASSERT_EQ(test[2], 2);
  ASSERT_EQ(test[3], 3);
}

TEST(Macro, CanUseForLoopNoArg) {
  int foo[] = { 0,0,0,0 };
#define FOR_CALLBACK2(i) foo[i] = i;
  ZEN_FOR(4, FOR_CALLBACK2)
  ASSERT_EQ(foo[0], 0);
  ASSERT_EQ(foo[1], 1);
  ASSERT_EQ(foo[2], 2);
  ASSERT_EQ(foo[3], 3);
}

TEST(Macro, CanUseForLoopWithComma) {
#define FOR_ENUM_CALLBACK(i,value) i + value
  int test[] = { ZEN_JOIN_ENUM(4, FOR_ENUM_CALLBACK, 1) };
  ASSERT_EQ(test[0], 1);
  ASSERT_EQ(test[1], 2);
  ASSERT_EQ(test[2], 3);
  ASSERT_EQ(test[3], 4);
}

TEST(Macro, CanUseForLoopWithCusomSeparator) {
#define FOR_WITH_CALLBACK(i,value) (i + value)
  ASSERT_EQ(ZEN_JOIN(+,4,FOR_WITH_CALLBACK,1), 10);
}

TEST(Macro, CanUseEeachLoop) {
#define ZEN_EACH_CALLBACK(name) int name = 42;
  ZEN_EACH(ZEN_EACH_CALLBACK, foo, bar, baz);
  ASSERT_EQ(foo, 42);
  ASSERT_EQ(bar, 42);
  ASSERT_EQ(baz, 42);
}

TEST(Macro, CanUseEachLoopWithComma) {
#define ZEN_EACH_ENUM_CALLBACK(x) x + 1
  int foo[] = { ZEN_EACH_ENUM(ZEN_EACH_ENUM_CALLBACK, 1, 2, 3, 4) };
  ASSERT_EQ(foo[0], 2);
  ASSERT_EQ(foo[1], 3);
  ASSERT_EQ(foo[2], 4);
  ASSERT_EQ(foo[3], 5);
}

TEST(Macro, CanUseEachLoopWithCustomSeparator) {
#define ZEN_EACH_WITH_CALLBACK(x) x + 1
  ASSERT_EQ(ZEN_EACH_WITH(+, ZEN_EACH_WITH_CALLBACK, 0, 1, 2, 3), 10);
}

