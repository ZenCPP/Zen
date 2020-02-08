#ifndef ZEN_ITERATOR_HPP
#define ZEN_ITERATOR_HPP

#include <iterator>

namespace zen {

  /// Creates an insert_iterator for any container type.
  template<typename Container>
  std::back_insert_iterator<Container> default_inserter(Container& container) {
    return std::back_inserter(container);
  }

} // of namesapce zen

#endif // ZEN_ITERATOR_HPP
