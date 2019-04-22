
#include <gtest/gtest.h>

#include "zen/box.hpp"

#include "util.hpp"

static_assert(!zen::IsPlainReference<int>::value, "");
static_assert(zen::IsPlainReference<int&>::value, "");
static_assert(!zen::IsPlainReference<int&&>::value, "");
static_assert(!zen::IsPlainReference<A>::value, "");
static_assert(zen::IsPlainReference<A&>::value, "");
static_assert(!zen::IsPlainReference<A&&>::value, "");

TEST(BoxTest, CanAssignToReference) {
  zen::Box<int> i(1);
  i.reference() = 2;
  ASSERT_EQ(i.value(), 2);
}

TEST(BoxTest, CanMoveCastObject) {
  zen::Box<float> f(1);
  zen::Box<int> i(std::move(f));
  ASSERT_EQ(i.value(), 1);
}

TEST(BoxTest, CanCastObject) {
  zen::Box<float> f(1);
  zen::Box<int> i(f);
  ASSERT_EQ(f.value(), (float)1.0);
}

TEST(BoxTest, CanInstantiateDerived) {
  zen::Box<A> c(C {});
  ASSERT_EQ(static_cast<C&>(c.reference()).someData, 32);
}

TEST(BoxTest, CanMoveDerivedToBase) {
  zen::Box<C> c(C {});
  zen::Box<A> a(std::move(c));
  ASSERT_EQ(static_cast<C&>(a.reference()).someData, 32);
}

TEST(BoxTest, CanCopyDerivedToBase) {
  zen::Box<C> c(C {});
  zen::Box<A> a(c);
  ASSERT_EQ(static_cast<C&>(a.reference()).someData, 32);
}

TEST(BoxTest, CallsPolyDestructor) { 
  int destroyCount = 0;
  {
    zen::Box<B> b(B { destroyCount });
  }
  ASSERT_GT(destroyCount, 0);
}

TEST(BoxTest, CanCreateRefFromDerived) {
  C c1;
  zen::Box<A&> boxed1(c1);
  ASSERT_EQ(static_cast<C&>(boxed1.reference()).someData, 32);

  C c2;
  const zen::Box<A&> boxed2(c2);
  ASSERT_EQ(static_cast<const C&>(boxed2.reference()).someData, 32);
}

TEST(BoxTest, CanCopyRefBox) {
  C c1;
  zen::Box<A&> boxed1(c1);
  zen::Box<C&> boxed2(boxed1);
  ASSERT_EQ(boxed2.reference().someData, 32);
}

