#ifndef ZEN_VALUE_PTR_HPP
#define ZEN_VALUE_PTR_HPP

#include <utility>

#include "zen/clone.hpp"

namespace zen {

  template<typename T>
  class ValuePtr {

    T* ptr;

  public:

    ValuePtr(T* ptr): ptr(ptr) {};

    ValuePtr(const ValuePtr<T>& other): ptr(clone(other.ptr)) {};

    ValuePtr(ValuePtr<T>&& other): ptr(std::move(other.ptr)) {
      other.ptr = nullptr;
    };

    T* operator->() {
      return ptr;
    }

    T& operator*() {
      return *ptr;
    }

    ~ValuePtr() {
      if (ptr != nullptr) {
        delete ptr;
      }
    }

  };

  template<typename T, typename ...Args> 
  ValuePtr<T> make_value_ptr(Args&& ...args) {
    return ValuePtr<T>(new T(std::forward<Args>(args)...));
  }

} // of namespace zen

#endif // ZEN_VALUE_PTR_HPP
