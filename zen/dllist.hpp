#ifndef ZEN_DLLIST_HPP
#define ZEN_DLLIST_HPP

#include <cstdint>

#include "zen/config.h"
#include "zen/macros.h"
#include "zen/allocator.hpp"
#include "zen/range.hpp"

ZEN_NAMESPACE_START

template<
  typename T,
  typename SizeT = size_t,
  typename AllocatorT = DefaultAllocator<T>
>
class DLList;

template<typename T>
struct DLListNode {
  T value;
  DLListNode* prev_node;
  DLListNode* next_node;
};

template<
  typename T,
  typename SizeT,
  typename AllocatorT
>
class DLIter {

  friend class DLList<T, size_t,  AllocatorT>;

  DLListNode<T>* current;

public:

  using Value = T;

  using value_type = Value;

  inline DLIter(DLListNode<T>* current):
    current(current) {}

  bool operator==(const DLIter& other) {
    return other.current == current;
  }

  bool operator!=(const DLIter& other) {
    return other.current != current;
  }

  T& operator*() {
    return current->value;
  }

  DLIter& operator++() {
    ZEN_ASSERT(current != nullptr);
    current = current->next_node;
    return *this;
  }

  DLIter operator+(SizeT count) {
    auto result = current;
    for (SizeT i = 0; i < count; i++) {
      ZEN_ASSERT(result != nullptr);
      result = result->next_node;
    }
    return DLIter(result);
  }

};

template<
  typename T,
  typename SizeT,
  typename AllocatorT
>
class DLList {
public:

  using Value = T;
  using Iter = DLIter<T, SizeT, AllocatorT>;
  using Range = IterRange<Iter>;

private:

  DLListNode<T>* _first;
  DLListNode<T>* _last;
  std::size_t _sz;

public:

  inline DLList():
    _first(nullptr), _last(nullptr), _sz(0) {}

  void append(T element) {
    auto new_node = new DLListNode<T> {
      .value = element,
      .next_node = nullptr
    };
    if (_first == nullptr) {
      new_node->prev_node = nullptr;
      _first = _last = new_node;
    } else {
      new_node->prev_node = _last;
      _last->next_node = new_node;
      _last = new_node;
    }
    _sz++;
  }

  void prepend(T element) {
    auto to_prepend = new DLListNode<T> {
      .value = element,
      .prev_node = nullptr
    };
    if (_first == nullptr) {
      to_prepend->next_node = nullptr;
      _first = _last = to_prepend;
    } else {
      to_prepend->next_node = _last;
      _first->prev_node = to_prepend;
      _first = to_prepend;
    }
    _sz++;
  }

  SizeT size() {
    return _sz;
  }

  inline Range range() {
    return make_iter_range(begin(), end());
  }

  inline Iter begin() {
    return Iter(_first);
  }

  inline Iter end() {
    return Iter(_last);
  }

  inline T& operator[](size_t index) {
    ZEN_ASSERT(index < _sz);
    return *(begin() + index);
  }

  inline void insert_after(Iter pos, Value value) {
    ZEN_ASSERT(pos.current != nullptr);
    auto to_insert_next = pos.current->next_node;
    auto to_insert = new DLListNode<T> {
      .value = value,
      .prev_node = pos.current,
      .next_node = pos.current->next_node,
    };
    pos.current->next_node = to_insert;
    to_insert_next->prev_node = to_insert;
    _sz++;
  }

  inline Value first() {
    ZEN_ASSERT(_first != nullptr);
    return _first->value;
  }

  inline Value last() {
    ZEN_ASSERT(_last = nullptr);
    return _last->value;
  }

};

ZEN_NAMESPACE_END

#endif // of #ifndef ZEN_DLLIST_HPP
