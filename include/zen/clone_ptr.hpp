#ifndef ZEN_VALUE_PTR_HPP
#define ZEN_VALUE_PTR_HPP

#include "zen/meta.hpp"

namespace zen {

  template<typename T>
  class clone_ptr {

    T* ptr;

  public:

    clone_ptr(T* ptr):
      ptr(ptr) {};

    inline clone_ptr(clone_ptr&& other):
        ptr(std::move(other.ptr)) {
      other.ptr = nullptr;
    }

    inline clone_ptr(const clone_ptr& other):
      ptr(clone(other.ptr)) {};

    inline clone_ptr& operator=(clone_ptr&& other) {
      ptr = std::move(other.ptr);
      other.ptr = nullptr;
      return *this;
    }

    inline clone_ptr& operator=(const clone_ptr& other) {
      ptr = clone(other.ptr);
      return *this;
    }

    inline T* operator->() const {
      return ptr;
    }

    inline T* get() const {
      return ptr;
    }

    inline T& operator*() {
      return *ptr;
    }

    ~clone_ptr() {
      delete ptr;
    }

  };

  template<typename T, typename ...ForwardArg>
  clone_ptr<T> make_clonable(ForwardArg&& ...args) {
    return clone_ptr<T>(new T(std::forward<ForwardArg>(args)...));
  }

}

#endif // ZEN_VALUE_PTR_HPP
