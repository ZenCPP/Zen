#ifndef ZEN_BASE_TEST_UTIL_HPP
#define ZEN_BASE_TEST_UTIL_HPP

class A {
public:
  virtual ~A() {  }
  virtual A* clone() const = 0;
};

class B : public A {
  bool destroyed = false;
  int& destroyCount;
public:

  int someData = 43;

  B(int& destroyCount): destroyCount(destroyCount) {}

  ~B() override { 
    assert(!destroyed);
    destroyed = true;
    destroyCount++;
  }

  B* clone() const override {
    return new B(destroyCount);
  }

};

class C : public A {
public:
  int someData = 32;
  C* clone() const override { return new C; }
};

#endif // ZEN_BASE_TEST_UTIL_HPP

