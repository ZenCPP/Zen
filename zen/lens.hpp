#ifndef ZEN_LENS_HPP
#define ZEN_LENS_HPP

#include <functional>
#include <optional>
#include <any>

#include "zen/config.h"

ZEN_NAMESPACE_START

template<typename T, typename R>
using getter = std::function<R(const T&)>;

template<typename T, typename R>
using setter = std::function<void(T&, R&&)>;

template<typename T, typename R>
using Lens = std::pair<getter<T, R>, std::optional<setter<T, R>>>;

template<typename T, typename R>
Lens<T, R>  make_lens(R T::*ptr) {
  return std::make_pair(
      [ptr](const T& obj) { return obj.*ptr; },
      [ptr](T& obj, R&& val) { obj.*ptr = std::move(val); }
  );
}

template<typename T, typename R>
Lens<T, std::any> make_any_lens(R T::*ptr) {
  return std::make_pair(
      [ptr](const T& obj) { return obj.*ptr; },
      [ptr](T& obj, std::any&& val) { obj.*ptr = std::move(std::any_cast<R>(val)); }
  );
}

template<typename T, typename R>
Lens<T, std::any> make_any_lens(R(T::*ptr)() const) {
  return std::make_pair(ptr, std::nullopt);
}

template<typename T, typename R>
R get(const T& obj, Lens<T, R> prop) {
  auto& [getter, setter] = prop;
  return getter(obj);
}

template<typename T, typename R>
void set(T& obj, Lens<T, R> prop, R&& value) {
  auto& [getter, setter] = prop;
  setter(obj, std::move(value));
}

ZEN_NAMESPACE_END

#endif // ZEN_LENS_HPP
