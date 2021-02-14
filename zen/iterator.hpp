/**
 * @file iterator.hpp
 * @brief Tools and utilities for working with iterators.
 */
#ifndef ZEN_ITERATOR_HPP
#define ZEN_ITERATOR_HPP

#include <stddef.h>

#if ZEN_STL
#include <iterator>
#endif

#include "zen/config.h"
#include "zen/meta.hpp"

ZEN_NAMESPACE_START

/// Creates an insert_iterator for any container type.
//template<typename Container>
//std::back_insert_iterator<Container> default_inserter(Container& container) {
//  return std::back_inserter(container);
//}

template<typename IterT>
struct IterTraits {
  using Value = typename IterT::Value;
  using Size = typename IterT::Size;
  using Diff = typename IterT::Diff;
};

template<typename T>
struct IterTraits<T*> {
  using Value = T;
  using Size = size_t;
  using Diff = ptrdiff_t;
};

template<typename IterT>
concept Iterator = requires(IterT a, IterT b) {
  { a == b } -> SameAs<bool>;
  { a != b } -> SameAs<bool>;
  { *a } -> SameAs<typename IterT::Value>;
  { a++ } -> SameAs<IterT>;
};

#if ZEN_STL

#endif

ZEN_NAMESPACE_END

#endif // ZEN_ITERATOR_HPP
