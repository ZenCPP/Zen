/// \file  zen/empty.hpp
/// \brief Types, classes and functions for working with nullable objects.
///
/// This file defines the zen::empty-type. The empty-type is a collection of
/// specialisations of certain types. The types that fall within this collection
/// are said to be _nullable_. The specialisation requires an unique member to exist
/// that is seperate from all other possible values that a specific type can take.
///
/// A `std::shared_ptr` is a good example of a type that is nullable. As a consequence,
/// it is a member of the `zen::empty` type family, and you can use
/// `zen::make_empty()` to construct it. In this case, `zen::make_empty` will
/// construct a `std::shared_ptr` using a `nullptr`.
//
/// ## Making a Type Nullable
/// 
/// Zen++ can automatically detect whether a newly defined class is nullable by
/// checking if it accepts the `zen::emtpy` special type as an argument to one of 
/// its constructors.
/// 
/// As an example, say we want to wrap the `int`-type in such a way that the
/// highest number (`0xf...ff`) becomes a special empty value. The following code
/// suffices for `zen::is_nullable`, `zen:::make_empty`, etc. to work.
///
/// ```
/// class int_wrapper {
///   int data;
///   int_wrapper(zen::empty): data(-1) {};
/// }
/// ```
///

#ifndef ZEN_EMPTY_HPP
#define ZEN_EMPTY_HPP

#include "zen/meta.hpp"

namespace zen {

  /// A type that may be accepted by certain classes, such that they will
  /// explicitly construct themselves as if they had the empty value.
  ///
  /// A class that accepts zen::empty is expected to 
  struct empty {};

  template<typename T, typename Enabler = void>
  struct empty_holder;

  template<typename T>
  inline constexpr auto make_empty() {
    return empty_holder<T>::value;
  }

  /// Determine wether a structure can hold an empty structure, as determined by zen::empty.
  template<typename T, typename Enabler = void>
  struct is_nullable_impl_ : false_ {};

  template<typename T>
  using is_nullable_ = is_nullable_impl_<T>;

  template<typename T>
  inline constexpr bool is_nullable_v = is_nullable_<T>::value;

} // of namespace zen

#endif // ZEN_EMPTY_HPP
