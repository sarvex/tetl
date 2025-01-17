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

#ifndef GCEM_binomial_coef_HPP
#define GCEM_binomial_coef_HPP

namespace internal {

template <typename T>
constexpr auto binomial_coef_recur(const T n, const T k) noexcept -> T
{
    return (                           // edge cases
        (k == T(0) || n == k) ? T(1) : // deals with 0 choose 0 case
            n == T(0) ? T(0)
                      :
                      // else
            binomial_coef_recur(n - 1, k - 1) + binomial_coef_recur(n - 1, k));
}

template <typename T, typename etl::enable_if<etl::is_integral<T>::value>::type* = nullptr>
constexpr auto binomial_coef_check(const T n, const T k) noexcept -> T
{
    return binomial_coef_recur(n, k);
}

template <typename T, typename etl::enable_if<!etl::is_integral<T>::value>::type* = nullptr>
constexpr auto binomial_coef_check(const T n, const T k) noexcept -> T
{
    return ( // NaN check; removed due to MSVC problems; template not being
             // ignored in <int> cases (is_nan(n) || is_nan(k)) ?
             // etl::numeric_limits<T>::quiet_NaN() :
             //
        static_cast<T>(binomial_coef_recur(static_cast<ullint_t>(n), static_cast<ullint_t>(k))));
}

template <typename T1, typename T2, typename TC = common_t<T1, T2>>
constexpr auto binomial_coef_type_check(const T1 n, const T2 k) noexcept -> TC
{
    return binomial_coef_check(static_cast<TC>(n), static_cast<TC>(k));
}

} // namespace internal

/**
 * Compile-time binomial coefficient
 *
 * @param n integral-valued input.
 * @param k integral-valued input.
 * @return computes the Binomial coefficient
 * \f[ \binom{n}{k} = \frac{n!}{k!(n-k)!} \f]
 * also known as '\c n choose \c k '.
 */

template <typename T1, typename T2>
constexpr auto binomial_coef(const T1 n, const T2 k) noexcept -> common_t<T1, T2>
{
    return internal::binomial_coef_type_check(n, k);
}

#endif
