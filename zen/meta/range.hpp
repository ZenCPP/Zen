#ifndef ZEN_META_RANGE_HPP
#define ZEN_META_RANGE_HPP

#include "zen/meta/common.hpp"
#include "zen/meta/math.hpp"
#include "zen/meta/iterator.hpp"

namespace zen {

  template<typename T>
  struct size_impl_ {
    ZEN_MISSING_IMPLEMENTATION(T, size);
  };

  template<typename T>
  using size_ = typename size_impl_<T>::type;

  template<typename T>
  using size_v = typename size_<T>::value;

  template<typename T>
  struct begin_impl_;

  template<typename T>
  using begin_ = begin_impl_<T>;

  template<typename T>
  struct end_impl_;

  template<typename T>
  using end_ = end_impl_<T>;

  template<typename BeginT, typename EndT>
  struct range_t {
    using begin_type = BeginT;
    using end_type = EndT;
  };

  template<typename BeginT, typename EndT>
  struct range_ {
    using type = range_t<BeginT, EndT>;
  };

  template<typename BeginT, typename EndT>
  struct inc_impl_<range_t<BeginT, EndT>> {
    using type = range_t<next_t<BeginT>, EndT>;
  };

} // of namespace zen

#endif // ZEN_META_RANGE_HPP
