#ifndef ZEN_META_MEMORY_HPP
#define ZEN_META_MEMORY_HPP

#include <type_traits>
#include <memory>

#include "zen/meta/primitives.hpp"
#include "zen/clone.hpp"
#include "zen/empty.hpp"

namespace zen {

  template<typename T, typename Enabler = void>
  struct is_pointer_impl_ : false_ {};

  /// Determine whether a certain type is a pointer-like structure.
  ///
  /// This metafunction is highly similar to std::is_pointer. However
  /// std::is_pointer had to retain backwards compatibility, which is why it
  /// won't work for certain pointers. This function is meant to be a better
  /// replacement with more predictable behaviour.
  template<typename T>
  using is_pointer_ = is_pointer_impl_<T>;

  template<typename T>
  struct is_pointer_impl_<T, std::enable_if_t<std::is_pointer<T>::value>> : true_ {};

  template<typename T>
  struct is_pointer_impl_<std::shared_ptr<T>> : true_ {};

  template<typename T>
  struct is_pointer_impl_<std::unique_ptr<T>> : true_ {};

  template<typename T>
  inline constexpr bool is_pointer_v = is_pointer_<T>::value;

  template<typename T, typename = void>
  struct pointee_ {
    using type = std::remove_reference_t<decltype(*std::declval<T>())>;
  };

  template<typename T>
  using pointee_t = typename pointee_<T>::type;

  template<typename T>
  struct empty_holder<T, std::enable_if_t<is_pointer_v<T>>> {
    inline static const T value = nullptr;
  };

  template<typename T>
  struct is_nullable_impl_<T, typename std::enable_if_t<is_pointer_v<T>>> : true_ {};

  template<typename T>
  struct cloner<T, std::enable_if_t<is_pointer_v<T>>> {
    static T apply(const T& value) {
      using R = pointee_t<T>;
      return T(new R(*value));
    }
  };

} // of namespace zen

#endif // ZEN_META_MEMORY_HPP
