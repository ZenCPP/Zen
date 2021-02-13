#ifndef ZEN_TUPLE_HPP
#define ZEN_TUPLE_HPP

#include "zen/config.h"
#include "zen/meta.hpp"

ZEN_NAMESPACE_START

template<typename T>
struct IsEmpty;

template<size_t I, typename ValueT, bool IsEmpty = IsEmpty<ValueT>::value>
class _TupleLeaf {
    ValueT value;
};

template<size_t ...I>
struct _TupleIndices {};

template<typename Indices, typename ...Ts>
struct _TupleImpl;

template<size_t ...Indices, typename ...Ts>
struct _TupleImpl<_TupleIndices<Indices...>, Ts...> 
    : public _TupleLeaf<Indices, Ts>... {};

template<size_t N, typename T>
auto get(T value);

/**
 * @brief An indexed list of types that can be populated at run-time.
 *
 * The implementation was inspired by [this article][1] and [this article][2].
 *
 * [1]: https://ldionne.com/2015/11/29/efficient-parameter-pack-indexing/
 * [2]: https://mitchnull.blogspot.com/2012/06/c11-tuple-implementation-details-part-1.html
 */
template<typename ...Ts>
class Tuple {

    template<size_t N, typename T>
    friend auto get(T value);

    using Impl = _TupleImpl<Ascending<size_t, sizeof...(Ts)>, Ts...>;

    Impl _elements;

public:

    template<typename T>
    constexpr auto append(T element) {
      return Tuple<Ts..., T>(get<Ascending<size_t, sizeof...(Ts)>>(), element);
    }

};

template<size_t N, typename ...Ts>
auto get(Tuple<Ts...> tuple) {
    return static_cast<_TupleLeaf<N, TypePackElement<N, Ts...>>&>(tuple._elements).value;
}

ZEN_NAMESPACE_END

#if ZEN_STL

#include <tuple>

#else

namespace std {

    // Structural binding declarations require std::tuple_size<T> and
    // std::tuple_element<N, T> to be present. The compiler will use these
    // templates to automatically extract elements from a given type.

    template <typename T>
    struct tuple_size;

    template<size_t N, typename T>
    struct tuple_element;

}

#endif

#if ZEN_STL

#include <tuple>

namespace std {

    template <typename ...Ts>
    struct tuple_size< ::zen::Tuple<Ts...> > {
        static const size_t value = sizeof...(Ts);
    };

}
#endif // of #if ZEN_STL

#endif // of #ifndef ZEN_TUPLE_HPP