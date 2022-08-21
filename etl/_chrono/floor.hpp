/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_CHRONO_FLOOR_HPP
#define TETL_CHRONO_FLOOR_HPP

#include "etl/_chrono/duration_cast.hpp"
#include "etl/_chrono/time_point_cast.hpp"
#include "etl/_type_traits/enable_if.hpp"
#include "etl/_type_traits/is_arithmetic.hpp"

namespace etl::chrono {

/// \brief Returns the greatest duration t representable in ToDuration that is
/// less or equal to d. The function does not participate in the overload
/// resolution unless ToDuration is an instance of etl::chrono::duration.
template <typename To, typename Rep, typename Period, enable_if_t<detail::is_duration_v<To>, int> = 0>
[[nodiscard]] constexpr auto floor(duration<Rep, Period> const& d) noexcept(
    is_arithmetic_v<Rep>&& is_arithmetic_v<typename To::rep>) -> To
{
    auto const t { duration_cast<To>(d) };
    if (t > d) { return To(t.count() - static_cast<typename To::rep>(1)); }
    return t;
}

template <typename To, typename Clock, typename Duration, enable_if_t<detail::is_duration_v<To>, int> = 0>
[[nodiscard]] constexpr auto floor(time_point<Clock, Duration> const& tp) -> time_point<Clock, To>
{
    return time_point<Clock, To>(floor<To>(tp.time_since_epoch()));
}

} // namespace etl::chrono

#endif // TETL_CHRONO_FLOOR_HPP
