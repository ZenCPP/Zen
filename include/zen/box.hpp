#ifndef ZEN_BOX_HPP
#define ZEN_BOX_HPP

#include <cstdlib>
#include <cstring>
#include <utility>

#include "zen/clone.hpp"

namespace zen {

  template<typename T> struct IsPlainReference : std::false_type {};
  template<typename T> struct IsPlainReference<T&> : std::true_type {};

  template<typename T> struct IsPlainConstReference : std::false_type {};
  template<typename T> struct IsPlainConstReference<const T&> : std::true_type {};

  template<typename T> struct Value { T data; Value(T val): data(val) {} };

  /// A box allows stack-allocated objects to be passed around
  /// as a supertype without loss of information.
  template<typename T, typename Enabler = void>
  class Box;

  namespace box_detail {
    
    struct PlainBoxTag {};
    struct PlainValueTag{};
    struct ConstBoxRefTag{};
    struct BoxMoveTag {};

    template<typename T> struct GetTag { using type = PlainValueTag; };
    template<typename T> struct GetTag<Box<T>> { using type = PlainBoxTag; };
    template<typename T> struct GetTag<Box<T>&&> { using type = BoxMoveTag; };
    template<typename T> struct GetTag<const Box<T>&> { using type = ConstBoxRefTag; };

  }

  template<typename T>
  class Box<T, typename std::enable_if<!std::is_reference<T>::value && !std::is_polymorphic<T>::value>::type> {

    T _value;

    template<typename R, typename Enabler>
    friend class Box;

  public:

    using Type = T;

    // Box(const Box& oth): _value(oth._value) {}

    // Box(Box&& oth): _value(std::move(oth._value)) {}

    template<typename R>
    Box(R value): Box(typename box_detail::GetTag<R>::type {}, value) {}

    template<typename R>
    Box(box_detail::BoxMoveTag, R oth): _value(std::move(oth._value())) {}

    template<typename R>
    Box(box_detail::PlainBoxTag, R oth): _value(oth._value) {}

    template<typename R>
    Box(box_detail::ConstBoxRefTag, R oth): _value(oth._value) {}

    template<typename R>
    Box(box_detail::PlainValueTag, R val): _value(val) {}

    T value() const {
      return _value;
    }

    T& reference() {
      return _value;
    }

    const T& reference() const {
      return _value;
    }

  };

  template<typename T>
  class Box<T, typename std::enable_if<std::is_polymorphic<T>::value>::type> {

    T* ptr;

    template<typename R, typename Enabler>
    friend class Box;

  public:

    using Type = T;

    Box(const Box& oth): ptr(clone(*oth.ptr)) {
      printf("Copying Box (%p => %p)\n", &oth, this);
    }

    Box(Box&& oth): ptr(std::exchange(oth.ptr, nullptr)) {
      printf("Moving Box (%p => %p)", &oth, this);
    }

    template<typename R, typename = typename std::enable_if<std::is_convertible<R, T>::value>::type>
    Box(R val): ptr(clone(val)) {
      printf("Creating Box (%p)\n", this);
    };

    template<typename R>
    Box(const Box<R>& oth): ptr(clone(*oth.ptr)) {
      printf("Copying Box (%p => %p)\n", &oth, this);
    }

    template<typename R>
    Box(Box<R>&& oth): ptr(std::exchange(oth.ptr, nullptr)) {
      printf("Moving Box (%p => %p)", &oth, this);
    };

//       template<typename R>
//       R as() const {
// #if !defined(NDEBUG) && ZEN_RTTI_ENABLED
//         auto r = dynamic_cast<const R*>(ptr);
//         assert(r != nullptr);
//         return *r;
// #else
//         return *static_cast<const R*>(ptr);
// #endif
//       }

    // T value() const { return *ptr; }

    T& reference() { return *ptr; }
    const T& reference() const { return *ptr; }

    ~Box() {
      printf("~Box (%p)\n", ptr);
      if (ptr != nullptr) {
        delete ptr;
      }
    }

  };

  template<typename T>
  class Box<T, typename std::enable_if<IsPlainReference<T>::value>::type> {
  public:

    using ValueT = typename std::remove_reference<T>::type;

  protected:

    using PtrT = ValueT*;

    PtrT ptr;

  public:

    using Type = T;

    Box(const Box& oth): ptr(oth.ptr) { }

    Box(Box&& oth): ptr(std::move(oth.ptr)) {};

    Box(T ref): ptr(&ref) {}

    operator T() {
      return *ptr;
    }

    T value() const {
      return *ptr;
    }

    T reference() {
      return *ptr;
    }

  };

// name(Box<T>&& val): value(std::move(val)) {} 

#define ZEN_DEFINE_BOXED_TYPE(name) \
  template<typename T> \
  struct name { \
    Box<T> value; \
    name(const Box<T>& val): value(val) {} \
    name(T val): value(val) {} \
    ~name() { printf("~" #name "\n"); } \
  };

} // namespace zen

#endif // ZEN_BOX_HPP
