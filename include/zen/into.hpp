#ifndef ZEN_INTO_HPP
#define ZEN_INTO_HPP

#include <memory>

namespace zen {

  template<typename T, typename Enabler = void>
  struct Into {
    template<typename R>
    static R apply(T value) {
      return value;
    }
  };

  template<typename T>
  struct IntoPtr : Into<T, typename std::enable_if<std::is_pointer<T>::value>::type> { 
    template<typename R>
    static R apply(T value) {
      return std::static_pointer_cast<R>(value);
    }
  };

  template<typename R, typename T>
  R into(T value) {
    return Into<T>::template apply<R>(value);
  }

} // of namespace zen

#endif // #ifndef ZEN_INTO_HPP
