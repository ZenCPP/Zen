/// \file zen/into.hpp
/// \brief Type traits and functions for converting related objects to one another.
///
#ifndef ZEN_INTO_HPP
#define ZEN_INTO_HPP

#include <memory>

namespace zen {

  /// A type trait that specifies how one type can be converted into another.
  ///
  /// This is very similar to implicit casting one object to another, but much
  /// more powerful.
  ///
  /// \see zen::into() if you want to use this type in your code.
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

  /// Convert one object into another using a set of predefined rules.
  ///
  /// \see zen::Into if you want to define a new relation that is used by this function.
  template<typename R, typename T>
  R into(T value) {
    return Into<T>::template apply<R>(value);
  }

} // of namespace zen

#endif // #ifndef ZEN_INTO_HPP
