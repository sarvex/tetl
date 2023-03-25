/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_CHRONO_YEAR_MONTH_DAY_LAST_HPP
#define TETL_CHRONO_YEAR_MONTH_DAY_LAST_HPP

#include "etl/_chrono/local_t.hpp"
#include "etl/_chrono/month_day_last.hpp"
#include "etl/_chrono/system_clock.hpp"
#include "etl/_chrono/year.hpp"

namespace etl::chrono {

namespace detail {

[[nodiscard]] constexpr auto last_day_of_month(chrono::year const& y, chrono::month const& m) -> chrono::day
{
    constexpr chrono::day last_days[] = {
        chrono::day { 31 },
        chrono::day { 28 },
        chrono::day { 31 },
        chrono::day { 30 },
        chrono::day { 31 },
        chrono::day { 30 },
        chrono::day { 31 },
        chrono::day { 31 },
        chrono::day { 30 },
        chrono::day { 31 },
        chrono::day { 30 },
        chrono::day { 31 },
    };

    if (m == chrono::month { 2 } and y.is_leap()) { return chrono::day { 29 }; }
    return last_days[(static_cast<uint32_t>(m) - 1) & 0xF];
}

} // namespace detail

struct year_month_day_last {
    constexpr year_month_day_last(chrono::year const& y, chrono::month_day_last const& mdl) noexcept
        : y_ { y }, mdl_ { mdl }
    {
    }

    constexpr auto operator+=(months const& m) noexcept -> year_month_day_last&;
    constexpr auto operator-=(months const& m) noexcept -> year_month_day_last&;
    constexpr auto operator+=(years const& y) noexcept -> year_month_day_last&;
    constexpr auto operator-=(years const& y) noexcept -> year_month_day_last&;

    [[nodiscard]] constexpr auto year() const noexcept -> chrono::year { return y_; }
    [[nodiscard]] constexpr auto month() const noexcept -> chrono::month { return mdl_.month(); }
    [[nodiscard]] constexpr auto month_day_last() const noexcept -> chrono::month_day_last { return mdl_; }
    [[nodiscard]] constexpr auto day() const noexcept -> chrono::day
    {
        return detail::last_day_of_month(year(), month());
    }

    [[nodiscard]] constexpr operator sys_days() const noexcept;
    [[nodiscard]] constexpr explicit operator local_days() const noexcept;
    [[nodiscard]] constexpr auto ok() const noexcept -> bool { return y_.ok() and mdl_.ok(); }

public:
    chrono::year y_;
    chrono::month_day_last mdl_;
};

} // namespace etl::chrono

#endif // TETL_CHRONO_YEAR_MONTH_DAY_LAST_HPP