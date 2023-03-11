/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_CHRONO_TIME_POINT_CAST_HPP
#define TETL_CHRONO_TIME_POINT_CAST_HPP

#include "etl/_chrono/duration_cast.hpp"
#include "etl/_chrono/time_point.hpp"
#include "etl/_concepts/requires.hpp"

namespace etl::chrono {

template <typename ToDuration, typename Clock, typename Duration,
    TETL_REQUIRES_(detail::is_duration<ToDuration>::value)>
[[nodiscard]] constexpr auto time_point_cast(time_point<Clock, Duration> const& tp) -> ToDuration
{
    using time_point_t = time_point<Clock, ToDuration>;
    return time_point_t(duration_cast<ToDuration>(tp.time_since_epoch()));
}

} // namespace etl::chrono

#endif // TETL_CHRONO_TIME_POINT_CAST_HPP