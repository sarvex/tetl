/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_BIT_POPCOUNT_HPP
#define TETL_BIT_POPCOUNT_HPP

#include "etl/_config/all.hpp"

#include "etl/_bit/bit_uint.hpp"
#include "etl/_limits/numeric_limits.hpp"
#include "etl/_type_traits/enable_if.hpp"
#include "etl/_type_traits/is_constant_evaluated.hpp"

namespace etl {

namespace detail {
template <typename T>
[[nodiscard]] constexpr auto popcount_fallback(T val) noexcept -> int
{
    auto count = T { 0 };
    while (val) {
        count = count + (val & T { 1 });
        val   = val >> T { 1 };
    }
    return static_cast<int>(count);
}
} // namespace detail

/// \brief Returns the number of 1 bits in the value of x.
///
/// \details This overload only participates in overload resolution if T is an
/// unsigned integer type (that is, unsigned char, unsigned short, unsigned int,
/// unsigned long, unsigned long long, or an extended unsigned integer type).
///
/// \module Numeric
template <typename T, enable_if_t<detail::bit_uint_v<T>, int> = 0>
[[nodiscard]] constexpr auto popcount(T val) noexcept -> int
{
    if (is_constant_evaluated()) { return detail::popcount_fallback(val); }
#if __has_builtin(__builtin_popcount)
    return __builtin_popcount(x);
#else
    return detail::popcount_fallback(val);
#endif
}

} // namespace etl

#endif // TETL_BIT_POPCOUNT_HPP