
#include <gtest/gtest.h>

#include "zen/either.hpp"

using namespace zen;

TEST(EitherTest, CanMakeLeftRight) {
  Either<int, float> e1 = left(1);
  Either<int, float> e2 = right(1.0);
}

class A {
public:
  virtual ~A() = 0;
};

class B {
  bool& destroyed;
public:
  B(bool& destroyed): destroyed(destroyed) {}
  virtual ~B() { 
    destroyed = true;
  }
};

Either<B, int> makeLeftB(bool& destroyed){
  return left(B(destroyed));
}

Either<int, B> makeRightB(bool& destroyed){
  return right(B(destroyed));
}

TEST(EitherTest, CallsDestructor) {
  bool destroyedRight, destroyedLeft;
  {
    auto b1 = makeLeftB(destroyedLeft);
  }
  {
    auto b2 = makeRightB(destroyedRight);
  }
  ASSERT_TRUE(destroyedLeft);
  ASSERT_TRUE(destroyedRight);
}

TEST(EitherTest, CanLeftMap) {
  

}

