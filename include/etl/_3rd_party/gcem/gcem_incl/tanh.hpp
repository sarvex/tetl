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
 * compile-time hyperbolic tangent function
 */

#ifndef GCEM_tanh_HPP
#define GCEM_tanh_HPP

namespace internal {

template <typename T>
constexpr auto tanh_cf(const T xx, int const depth) noexcept -> T
{
    return (depth < GCEM_TANH_MAX_ITER ? // if
                (2 * depth - 1) + xx / tanh_cf(xx, depth + 1)
                                       :
                                       // else
                T(2 * depth - 1));
}

template <typename T>
constexpr auto tanh_begin(const T x) noexcept -> T
{
    return (x / tanh_cf(x * x, 1));
}

template <typename T>
constexpr auto tanh_check(const T x) noexcept -> T
{
    return ( // NaN check
        is_nan(x) ? etl::numeric_limits<T>::quiet_NaN() :
                  // indistinguishable from zero
            etl::numeric_limits<T>::epsilon() > abs(x) ? T(0)
                                                       :
                                                       // else
            x < T(0) ? -tanh_begin(-x)
                     : tanh_begin(x));
}

} // namespace internal

/**
 * Compile-time hyperbolic tangent function
 *
 * @param x a real-valued input.
 * @return the hyperbolic tangent function using \f[ \tanh(x) = \dfrac{x}{1 +
 * \dfrac{x^2}{3 + \dfrac{x^2}{5 + \dfrac{x^2}{7 + \ddots}}}} \f]
 */

template <typename T>
constexpr auto tanh(const T x) noexcept -> return_t<T>
{
    return internal::tanh_check(static_cast<return_t<T>>(x));
}

#endif
