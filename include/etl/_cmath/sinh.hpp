// SPDX-License-Identifier: BSL-1.0

#ifndef TETL_CMATH_SINH_HPP
#define TETL_CMATH_SINH_HPP

#include "etl/_3rd_party/gcem/gcem.hpp"
#include "etl/_concepts/integral.hpp"

namespace etl {

/// \brief Computes the hyperbolic sine of arg
/// https://en.cppreference.com/w/cpp/numeric/math/sinh
[[nodiscard]] constexpr auto sinh(float arg) noexcept -> float { return etl::detail::gcem::sinh(arg); }

/// \brief Computes the hyperbolic sine of arg
/// https://en.cppreference.com/w/cpp/numeric/math/sinh
[[nodiscard]] constexpr auto sinhf(float arg) noexcept -> float { return etl::detail::gcem::sinh(arg); }

/// \brief Computes the hyperbolic sine of arg
/// https://en.cppreference.com/w/cpp/numeric/math/sinh
[[nodiscard]] constexpr auto sinh(double arg) noexcept -> double { return etl::detail::gcem::sinh(arg); }

/// \brief Computes the hyperbolic sine of arg
/// https://en.cppreference.com/w/cpp/numeric/math/sinh
[[nodiscard]] constexpr auto sinh(long double arg) noexcept -> long double { return etl::detail::gcem::sinh(arg); }

/// \brief Computes the hyperbolic sine of arg
/// https://en.cppreference.com/w/cpp/numeric/math/sinh
[[nodiscard]] constexpr auto sinhl(long double arg) noexcept -> long double { return etl::detail::gcem::sinh(arg); }

/// \brief Computes the hyperbolic sine of arg
/// https://en.cppreference.com/w/cpp/numeric/math/sinh
template <integral T>
[[nodiscard]] constexpr auto sinh(T arg) noexcept -> double
{
    return etl::detail::gcem::sinh(static_cast<double>(arg));
}

} // namespace etl

#endif // TETL_CMATH_SINH_HPP
