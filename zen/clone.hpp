#ifndef ZEN_CLONE_HPP
#define ZEN_CLONE_HPP

namespace zen {

  template<typename T, typename Enabler = void>
  struct cloner {

    static_assert(!std::is_rvalue_reference_v<T>, "it is not possible to clone an r-value reference (hint: you can simply use the value directly)");

    static T apply(const T& value) {
      return T(value);
    }

  };

  template<typename T>
  T clone(const T& value) {
    return cloner<T>::apply(value);
  }

} // of namespace zen

#endif // ZEN_CLONE_HPP
