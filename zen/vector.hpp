#ifndef ZEN_VECTOR_HPP
#define ZEN_VECTOR_HPP

#include "zen/config.h"
#include "zen/allocator.hpp"
#include "zen/macros.h"
#include "zen/range.hpp"

#include <initializer_list>
#include <utility>

ZEN_NAMESPACE_START

template<typename T>
void swap(T& a, T& b) {
  auto keep = std::move(a);
  a = std::move(b);
  b = std::move(keep);
}

template<typename RangeT, typename OutIter>
void move_n(RangeT range, OutIter out) {
  for (auto&& element: range) {
    *out++ = std::move(element);
  }
}

template<typename RangeT, typename OutIter>
void copy(RangeT range, OutIter out) {
  for (auto&& element: range) {
    *out++ = element;
  }
}

template<
  typename T,
  typename SizeT = size_t,
  typename AllocatorT = DefaultAllocator<T>
>
class Vector {
public:

  using Value = T;
  using Size = SizeT;
  using Iter = T*;

  using value_type = T;
  using size_type = SizeT;

private:

  AllocatorT _allocator;
  SizeT _capacity;
  SizeT _sz;
  T* _ptr;

public:

  template<typename RangeT>
  Vector(std::enable_if_t<IsRange<RangeT>::value, RangeT> range, AllocatorT allocator = AllocatorT()):
    _allocator(allocator),
    _capacity(range.size()),
    _sz(range.size()),
    _ptr(allocator.allocate(range.size())) {
      ZEN_ASSERT(_ptr != nullptr);
      SizeT k = 0;
      for (auto element: range) {
        _ptr[k++] = element;
      }
    }

  inline Vector<SizeT>(SizeT init_capacity = 256, AllocatorT allocator = AllocatorT()):
    _allocator(allocator),
    _capacity(init_capacity),
    _sz(0),
    _ptr(allocator.allocate(_capacity)) {
      ZEN_ASSERT(_ptr != nullptr);
    }

  inline Vector(const Vector& other):
    _allocator(other._allocator),
    _capacity(other._sz),
    _sz(other._sz),
    _ptr(_allocator.allocate(other._sz)) {
      ZEN_ASSERT(_ptr != nullptr);
    }

  inline Vector(std::initializer_list<T> elements, AllocatorT allocator = AllocatorT()):
    Vector(elements.size(), allocator) {
      SizeT k = 0;
      for (auto element: elements) {
        _ptr[k++] = element;
      }
    }

  inline void ensure_capacity(SizeT new_capacity) {
    if (_capacity < new_capacity) {
      auto new_ptr = _allocator.allocate(new_capacity);
      copy(make_iter_range(_ptr, _ptr + _sz), new_ptr);
      _ptr = new_ptr;
    }
  }

  inline T& operator[](SizeT index) {
    ZEN_ASSERT(index >= 0 && index < _sz);
    return _ptr[index];
  }

  inline void append(T element) {
    ensure_capacity(_sz+1);
    _ptr[_sz] = element;
    _sz++;
  }

  inline void prepend(T element) {
    auto new_capacity = _capacity + 1;
    if (_capacity < new_capacity) {
      auto new_ptr = _allocator.allocate(new_capacity);
      copy(make_iter_range(_ptr, _ptr + _sz), new_ptr+1);
      _ptr = new_ptr;
    }
    _ptr[0] = element;
    _sz++;
  }

  inline SizeT capacity() const {
    return _capacity;
  }

  inline Iter begin() {
    return _ptr;
  }

  inline Iter end() {
    return _ptr + _sz;
  }

  inline SizeT size() const {
    return _sz;
  }

};

ZEN_NAMESPACE_END

#endif // ZEN_VECTOR_HPP
