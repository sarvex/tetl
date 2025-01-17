// SPDX-License-Identifier: BSL-1.0

#ifndef TETL_TUPLE_TIE_HPP
#define TETL_TUPLE_TIE_HPP

#include "etl/_tuple/tuple.hpp"

namespace etl {

template <typename... Args>
constexpr auto tie(Args&... args) noexcept -> tuple<Args&...>
{
    return { args... };
}

} // namespace etl

#endif // TETL_TUPLE_TIE_HPP
