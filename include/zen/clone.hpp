#ifndef ZEN_BASE_CLONE_HPP
#define ZEN_BASE_CLONE_HPP

#include <type_traits>

namespace zen {

  template<typename T, typename Enabler = void>
  struct Clonable {
    static T* clone(const T& val) {
      return new T(val);
    }
  };

  template<typename T>
  struct Clonable<T, typename std::enable_if<std::is_polymorphic<T>::value>::type> {
    static T* clone(const T& val) {
      return val.clone();
    }
  };

  template<typename T>
  T* clone(const T& value) {
    return Clonable<T>::clone(value);
  }

}

#endif // ZEN_BASE_CLONE_HPP
