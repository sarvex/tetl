/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_ITERATOR_PREV_HPP
#define TETL_ITERATOR_PREV_HPP

#include "etl/_iterator/advance.hpp"
#include "etl/_iterator/iterator_traits.hpp"

namespace etl {

/// \brief Return the nth predecessor of iterator it.
template <typename BidirIt>
[[nodiscard]] constexpr auto prev(BidirIt it, typename iterator_traits<BidirIt>::difference_type n = 1) -> BidirIt
{
    advance(it, -n);
    return it;
}
} // namespace etl

#endif // TETL_ITERATOR_PREV_HPP