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
 * compile-time check if a float is +/-Inf
 */

#ifndef GCEM_is_inf_HPP
#define GCEM_is_inf_HPP

namespace internal {

template <typename T>
constexpr auto is_neginf(const T x) noexcept -> bool
{
    return x == -etl::numeric_limits<T>::infinity();
}

template <typename T1, typename T2>
constexpr auto any_neginf(const T1 x, const T2 y) noexcept -> bool
{
    return (is_neginf(x) || is_neginf(y));
}

template <typename T1, typename T2>
constexpr auto all_neginf(const T1 x, const T2 y) noexcept -> bool
{
    return (is_neginf(x) && is_neginf(y));
}

template <typename T1, typename T2, typename T3>
constexpr auto any_neginf(const T1 x, const T2 y, const T3 z) noexcept -> bool
{
    return (is_neginf(x) || is_neginf(y) || is_neginf(z));
}

template <typename T1, typename T2, typename T3>
constexpr auto all_neginf(const T1 x, const T2 y, const T3 z) noexcept -> bool
{
    return (is_neginf(x) && is_neginf(y) && is_neginf(z));
}

//

template <typename T>
constexpr auto is_posinf(const T x) noexcept -> bool
{
    return x == etl::numeric_limits<T>::infinity();
}

template <typename T1, typename T2>
constexpr auto any_posinf(const T1 x, const T2 y) noexcept -> bool
{
    return (is_posinf(x) || is_posinf(y));
}

template <typename T1, typename T2>
constexpr auto all_posinf(const T1 x, const T2 y) noexcept -> bool
{
    return (is_posinf(x) && is_posinf(y));
}

template <typename T1, typename T2, typename T3>
constexpr auto any_posinf(const T1 x, const T2 y, const T3 z) noexcept -> bool
{
    return (is_posinf(x) || is_posinf(y) || is_posinf(z));
}

template <typename T1, typename T2, typename T3>
constexpr auto all_posinf(const T1 x, const T2 y, const T3 z) noexcept -> bool
{
    return (is_posinf(x) && is_posinf(y) && is_posinf(z));
}

//

template <typename T>
constexpr auto is_inf(const T x) noexcept -> bool
{
    return (is_neginf(x) || is_posinf(x));
}

template <typename T1, typename T2>
constexpr auto any_inf(const T1 x, const T2 y) noexcept -> bool
{
    return (is_inf(x) || is_inf(y));
}

template <typename T1, typename T2>
constexpr auto all_inf(const T1 x, const T2 y) noexcept -> bool
{
    return (is_inf(x) && is_inf(y));
}

template <typename T1, typename T2, typename T3>
constexpr auto any_inf(const T1 x, const T2 y, const T3 z) noexcept -> bool
{
    return (is_inf(x) || is_inf(y) || is_inf(z));
}

template <typename T1, typename T2, typename T3>
constexpr auto all_inf(const T1 x, const T2 y, const T3 z) noexcept -> bool
{
    return (is_inf(x) && is_inf(y) && is_inf(z));
}

} // namespace internal

#endif
