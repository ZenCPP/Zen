#ifndef ZEN_MAYBE_HPP
#define ZEN_MAYBE_HPP

#include <type_traits>

#include "zen/box.hpp"

namespace zen {

  ZEN_DEFINE_BOXED_TYPE(Some)

  /// A maybe type is much like a std::optional<T> type, except that it can hold 
  /// strictly polymorphic types apart from the usual types.
  template<typename T>
  class Maybe;

  template<typename T> Maybe<T> some(T val) { return { val }; }

  template<typename T>
  class Maybe {

    union {
      Box<T> _value;
    };

    bool _hasValue;

  public:

    using ValueT = typename std::remove_reference<T>::type;

    using PtrT = ValueT*;

    Maybe(): _hasValue(false) {};

    Maybe(Some<T> some): _hasValue(true), _value(some.value) {}

    Maybe(Maybe&& oth): _hasValue(oth._hasValue) {
      if (oth._hasValue) {
        _value = std::move(oth._value);
        oth._hasValue = false;
      }
    }

    Maybe(const Maybe& oth): _hasValue(oth._hasValue) {
      if (oth._hasValue) {
        _value = oth._value;
      }
    }

    PtrT operator->() const {
#ifndef NDEBUG
      assert(_hasValue);
#endif
      return &_value.reference();
    }

    T& operator*() { return get(); }
    const T& operator*() const { return get(); }

    T& get() {
#ifndef NDEBUG
      assert(_hasValue);
#endif
      return _value.reference();
    }

    const T& get() const {
#ifndef NDEBUG
      assert(_hasValue);
#endif
      return _value.reference();
    }

    ValueT orElse(ValueT alt) const {
      return _hasValue ? _value.value() : alt;
    }

    ~Maybe() {
      if (_hasValue) {
        _value.~Box<T>();
      }
    }

  };

} // namespace zen

#endif // ZEN_MAYBE_HPP
