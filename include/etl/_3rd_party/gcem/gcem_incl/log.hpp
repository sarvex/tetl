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
 * compile-time natural logarithm function
 */

#ifndef GCEM_log_HPP
#define GCEM_log_HPP

namespace internal {

// continued fraction seems to be a better approximation for small x
// see http://functions.wolfram.com/ElementaryFunctions/Log/10/0005/

template <typename T>
constexpr auto log_cf_main(const T xx, int const depth) noexcept -> T
{
    return (depth < GCEM_LOG_MAX_ITER_SMALL ? // if
                T(2 * depth - 1) - T(depth * depth) * xx / log_cf_main(xx, depth + 1)
                                            :
                                            // else
                T(2 * depth - 1));
}

template <typename T>
constexpr auto log_cf_begin(const T x) noexcept -> T
{
    return (T(2) * x / log_cf_main(x * x, 1));
}

template <typename T>
constexpr auto log_main(const T x) noexcept -> T
{
    return (log_cf_begin((x - T(1)) / (x + T(1))));
}

constexpr auto log_mantissa_integer(int const x) noexcept -> long double
{
    return (x == 2    ? 0.6931471805599453094172321214581765680755L
            : x == 3  ? 1.0986122886681096913952452369225257046475L
            : x == 4  ? 1.3862943611198906188344642429163531361510L
            : x == 5  ? 1.6094379124341003746007593332261876395256L
            : x == 6  ? 1.7917594692280550008124773583807022727230L
            : x == 7  ? 1.9459101490553133051053527434431797296371L
            : x == 8  ? 2.0794415416798359282516963643745297042265L
            : x == 9  ? 2.1972245773362193827904904738450514092950L
            : x == 10 ? 2.3025850929940456840179914546843642076011L
                      : 0.0L);
}

template <typename T>
constexpr auto log_mantissa(const T x) noexcept -> T
{ // divide by the integer part of x, which will be in [1,10], then adjust using
  // tables
    return (log_main(x / T(static_cast<int>(x))) + T(log_mantissa_integer(static_cast<int>(x))));
}

template <typename T>
constexpr auto log_breakup(const T x) noexcept -> T
{ // x = a*b, where b = 10^c
    return (log_mantissa(mantissa(x)) + T(GCEM_LOG_10) * T(find_exponent(x, 0)));
}

template <typename T>
constexpr auto log_check(const T x) noexcept -> T
{
    return (is_nan(x) ? etl::numeric_limits<T>::quiet_NaN() :
                      // x < 0
                x < T(0) ? etl::numeric_limits<T>::quiet_NaN()
                         :
                         // x ~= 0
                etl::numeric_limits<T>::epsilon() > x ? -etl::numeric_limits<T>::infinity()
                                                      :
                                                      // indistinguishable from 1
                etl::numeric_limits<T>::epsilon() > abs(x - T(1)) ? T(0)
                                                                  :
                                                                  //
                x == etl::numeric_limits<T>::infinity() ? etl::numeric_limits<T>::infinity()
                                                        :
                                                        // else
                (x < T(0.5) || x > T(1.5)) ?
                                           // if
                log_breakup(x)
                                           :
                                           // else
                log_main(x));
}

} // namespace internal

/**
 * Compile-time natural logarithm function
 *
 * @param x a real-valued input.
 * @return \f$ \log_e(x) \f$ using \f[ \log\left(\frac{1+x}{1-x}\right) =
 * \dfrac{2x}{1-\dfrac{x^2}{3-\dfrac{4x^2}{5 - \dfrac{9x^3}{7 - \ddots}}}},
 * \ \ x \in [-1,1] \f] The continued fraction argument is split into two parts:
 * \f$ x = a \times 10^c \f$, where \f$ c \f$ is an integer.
 */

template <typename T>
constexpr auto log(const T x) noexcept -> return_t<T>
{
    return internal::log_check(static_cast<return_t<T>>(x));
}

#endif
