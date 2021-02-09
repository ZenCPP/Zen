#ifndef ZEN_ITERATOR_HPP
#define ZEN_ITERATOR_HPP

#include "zen/config.h"

ZEN_NAMESPACE_START

/// Creates an insert_iterator for any container type.
//template<typename Container>
//std::back_insert_iterator<Container> default_inserter(Container& container) {
//  return std::back_inserter(container);
//}

template<typename IterT>
struct IterTraits {
  using Value = typename IterT::Value;
};

template<typename T>
struct IterTraits<T*> {
  using Value = T;
};

ZEN_NAMESPACE_END

#endif // ZEN_ITERATOR_HPP
