// SPDX-License-Identifier: BSL-1.0

#ifndef TETL_CMATH_SIN_HPP
#define TETL_CMATH_SIN_HPP

#include "etl/_3rd_party/gcem/gcem.hpp"
#include "etl/_concepts/integral.hpp"

namespace etl {

/// \brief Computes the sine of arg (measured in radians).
/// https://en.cppreference.com/w/cpp/numeric/math/sin
[[nodiscard]] constexpr auto sin(float arg) noexcept -> float { return etl::detail::gcem::sin(arg); }

/// \brief Computes the sine of arg (measured in radians).
/// https://en.cppreference.com/w/cpp/numeric/math/sin
[[nodiscard]] constexpr auto sinf(float arg) noexcept -> float { return etl::detail::gcem::sin(arg); }

/// \brief Computes the sine of arg (measured in radians).
/// https://en.cppreference.com/w/cpp/numeric/math/sin
[[nodiscard]] constexpr auto sin(double arg) noexcept -> double { return etl::detail::gcem::sin(arg); }

/// \brief Computes the sine of arg (measured in radians).
/// https://en.cppreference.com/w/cpp/numeric/math/sin
[[nodiscard]] constexpr auto sin(long double arg) noexcept -> long double { return etl::detail::gcem::sin(arg); }

/// \brief Computes the sine of arg (measured in radians).
/// https://en.cppreference.com/w/cpp/numeric/math/sin
[[nodiscard]] constexpr auto sinl(long double arg) noexcept -> long double { return etl::detail::gcem::sin(arg); }

/// \brief Computes the sine of arg (measured in radians).
/// https://en.cppreference.com/w/cpp/numeric/math/sin
template <integral T>
[[nodiscard]] constexpr auto sin(T arg) noexcept -> double
{
    return etl::detail::gcem::sin(static_cast<double>(arg));
}

} // namespace etl

#endif // TETL_CMATH_SIN_HPP
