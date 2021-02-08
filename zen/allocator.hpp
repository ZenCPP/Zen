/// \file allocator.hpp
/// \brief Generic types for working with heap memory.
///
/// The allocator concept is another C++ concept that is closely related to the
/// STL counterpart.
///
/// ## Defining Your Own Allocator
///
/// You are allowed to define your own allocators that may be more efficient
/// than the provided allocators in certain circumstances. In order to do so,
/// you must make sure your new template adheres to the following constraints:
///
/// - The allocator must be default-constructable. In the case that it does not
///   make sense to default-construct a specific allocator, dispatch to
///   ZEN_PANIC.
/// - The allocator must have a `T* allocate(zen::size_t sz)`-method
/// - The allocator must have a `void free(zen::size_t sz)`-method
///
/// If the above requirements are fulfilled, you can use the allocator with any
/// container in this library.

#ifndef ZEN_ALLOCATOR_HPP
#define ZEN_ALLOCATOR_HPP

#include <stddef.h>
#include <malloc.h>

namespace zen {

  template<typename T>
  class SystemAllocator {
  public:

    inline T* allocate(size_t sz) {
      return malloc(sz);
    }

    inline void free(T* ptr, size_t sz) {
      free(ptr);
    }

  };

  template<typename T>
  using DefaultAllocator = SystemAllocator<T>;

}

#endif // of #ifndef ZEN_ALLOCATOR_HPP
