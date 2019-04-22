
#include <gtest/gtest.h>

#include "zen/box.hpp"

using namespace zen;

namespace box_test {

  class A {
  public:
    virtual ~A() {  };
    virtual A* clone() const = 0;
  };

  class B : public A {
  public:
    int someData = 43;
    ~B() override {  }
    B* clone() const override { return new B(); }
  };

  class C : public A {
    int& destroyCount;
  public:
    C(int& destroyCount): destroyCount(destroyCount) {}
    ~C() override {
      destroyCount++;
    }
    C* clone() const override { return new C(destroyCount); }
  };

}

using namespace box_test;

static_assert(!IsPlainReference<int>::value, "");
static_assert(IsPlainReference<int&>::value, "");
static_assert(!IsPlainReference<int&&>::value, "");
static_assert(!IsPlainReference<A>::value, "");
static_assert(IsPlainReference<A&>::value, "");
static_assert(!IsPlainReference<A&&>::value, "");

TEST(BoxTest, CanCreateRef) {
  Box<int> i(1);
  i.reference() = 2;
  ASSERT_EQ(i.value(), 2);
}

TEST(BoxTest, CanHoldPoly) {
  Box<B> b(B {});
  ASSERT_EQ(b.reference().someData, 43);
  ASSERT_EQ(b.reference().someData, 43);
}

TEST(BoxTest, CanAssignPolyBase) {
  Box<B> b(B {});
  Box<A> a(b);
  A& aRef = a.reference();
  ASSERT_EQ(static_cast<B&>(aRef).someData, 43);
}

TEST(BoxTest, CallsPolyDestructor) { 
  int destroyCount = 0;
  {
    Box<C> c(C { destroyCount });
  }
  // we did one copy, so it should be destroyed twice
  ASSERT_EQ(destroyCount, 2);
}

