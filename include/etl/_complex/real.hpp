// SPDX-License-Identifier: BSL-1.0

#ifndef TETL_COMPLEX_REAL_HPP
#define TETL_COMPLEX_REAL_HPP

#include "etl/_complex/complex.hpp"
#include "etl/_complex/double_or_int.hpp"

namespace etl {

template <typename T>
[[nodiscard]] constexpr auto real(complex<T> const& z) -> T
{
    return z.real();
}

template <typename T>
    requires(detail::double_or_int<T>)
[[nodiscard]] constexpr auto real(T z) -> double
{
    return static_cast<double>(z);
}

[[nodiscard]] constexpr auto real(float z) -> float { return z; }

[[nodiscard]] constexpr auto real(long double z) -> long double { return z; }

} // namespace etl

#endif // TETL_COMPLEX_REAL_HPP
