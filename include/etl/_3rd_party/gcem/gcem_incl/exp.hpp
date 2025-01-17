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
 * compile-time exponential function
 */

#ifndef GCEM_exp_HPP
#define GCEM_exp_HPP

namespace internal {

template <typename T>
constexpr auto exp_cf_recur(const T x, int const depth) noexcept -> T
{
    return (depth < GCEM_EXP_MAX_ITER_SMALL ? // if
                depth == 1 ? T(1) - x / exp_cf_recur(x, depth + 1)
                           : T(1) + x / T(depth - 1) - x / depth / exp_cf_recur(x, depth + 1)
                                            :
                                            // else
                T(1));
}

template <typename T>
constexpr auto exp_cf(const T x) noexcept -> T
{
    return static_cast<T>(T(1) / exp_cf_recur(x, 1));
}

template <typename T>
constexpr auto exp_split(const T x) noexcept -> T
{
    return static_cast<T>(pow_integral(etl::numbers::e, find_whole(x)) * exp_cf(find_fraction(x)));
}

template <typename T>
constexpr auto exp_check(const T x) noexcept -> T
{
    return static_cast<T>(is_nan(x)                                    ? etl::numeric_limits<T>::quiet_NaN()
                          : is_neginf(x)                               ? T(0)
                          : etl::numeric_limits<T>::epsilon() > abs(x) ? T(1)
                          : is_posinf(x)                               ? etl::numeric_limits<T>::infinity()
                          : abs(x) < T(2)                              ? exp_cf(x)
                                                                       : exp_split(x));
}

} // namespace internal

/**
 * Compile-time exponential function
 *
 * @param x a real-valued input.
 * @return \f$ \exp(x) \f$ using \f[ \exp(x) =
 * \dfrac{1}{1-\dfrac{x}{1+x-\dfrac{\frac{1}{2}x}{1 + \frac{1}{2}x -
 * \dfrac{\frac{1}{3}x}{1 + \frac{1}{3}x - \ddots}}}} \f] The continued fraction
 * argument is split into two parts: \f$ x = n + r \f$, where \f$ n \f$ is an
 * integer and \f$ r \in [-0.5,0.5] \f$.
 */

template <typename T>
constexpr auto exp(const T x) noexcept -> return_t<T>
{
    return internal::exp_check(static_cast<return_t<T>>(x));
}

#endif
