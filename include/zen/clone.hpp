#ifndef ZEN_CLONE_HPP
#define ZEN_CLONE_HPP

namespace zen {

  template<typename T, typename Enabler = void>
  struct Clone {
    static T apply(const T& value) {
      return T(value);
    }
  };

} // of namespace zen

#endif // #ifndef ZEN_CLONE_HPP
