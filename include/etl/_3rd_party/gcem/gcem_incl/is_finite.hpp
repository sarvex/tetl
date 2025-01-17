/*################################################################################
  ##
  ##   Copyright (C) 2016-2020 Keith O'Hara
  ##
  ##   This file is part of the GCE-Math C++ library.
  ##
  ##   Licensed under the Apache License, Version 2.0 (the "License");
  ##   you may not use this file except in compliance with the License.
  ##   You may obtain a copy of the License at
  ##
  ##       http://www.apache.org/licenses/LICENSE-2.0
  ##
  ##   Unless required by applicable law or agreed to in writing, software
  ##   distributed under the License is distributed on an "AS IS" BASIS,
  ##   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ##   See the License for the specific language governing permissions and
  ##   limitations under the License.
  ##
  ################################################################################*/

/*
 * compile-time check if a float is not NaN-valued or +/-Inf
 */

#ifndef GCEM_is_finite_HPP
#define GCEM_is_finite_HPP

namespace internal {

template <typename T>
constexpr auto is_finite(const T x) noexcept -> bool
{
    return (!is_nan(x)) && (!is_inf(x));
}

template <typename T1, typename T2>
constexpr auto any_finite(const T1 x, const T2 y) noexcept -> bool
{
    return (is_finite(x) || is_finite(y));
}

template <typename T1, typename T2>
constexpr auto all_finite(const T1 x, const T2 y) noexcept -> bool
{
    return (is_finite(x) && is_finite(y));
}

template <typename T1, typename T2, typename T3>
constexpr auto any_finite(const T1 x, const T2 y, const T3 z) noexcept -> bool
{
    return (is_finite(x) || is_finite(y) || is_finite(z));
}

template <typename T1, typename T2, typename T3>
constexpr auto all_finite(const T1 x, const T2 y, const T3 z) noexcept -> bool
{
    return (is_finite(x) && is_finite(y) && is_finite(z));
}

} // namespace internal

#endif
