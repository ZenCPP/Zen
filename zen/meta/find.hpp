#ifndef ZEN_META_FIND_HPP
#define ZEN_META_FIND_HPP

#include "zen/meta/primitives.hpp"
#include "zen/meta/common.hpp"
#include "zen/meta/lambda.hpp"
#include "zen/meta/iterator.hpp"
#include "zen/meta/range.hpp"

namespace zen {

  namespace meta {

    template<typename PredT, typename RangeT>
    struct find_ {
      using type = cond_t<
        case_<bool_<size_<RangeT>::value == 0>, none_>,
        case_<apply_<PredT, deref_t<RangeT>>, some_<deref_t<RangeT>>>,
        case_<true_, typename find_<PredT, inc_t<RangeT>>::type>
      >;
    };

    template<typename PredT, typename RangeT>
    using find_t = typename find_<PredT, RangeT>::type;

  } // of namespace meta

} // of namespace zen

#endif // ZEN_META_FIND_HPP
