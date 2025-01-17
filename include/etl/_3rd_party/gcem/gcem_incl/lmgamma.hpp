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
 * log multivariate gamma function
 */

#ifndef GCEM_lmgamma_HPP
#define GCEM_lmgamma_HPP

namespace internal {

// see https://en.wikipedia.org/wiki/Multivariate_gamma_function

template <typename T1, typename T2>
constexpr auto lmgamma_recur(const T1 a, const T2 p) noexcept -> T1
{
    return ( // NaN check
        is_nan(a) ? etl::numeric_limits<T1>::quiet_NaN() :
                  //
            p == T2(1) ? lgamma(a)
        : p < T2(1)    ? etl::numeric_limits<T1>::quiet_NaN()
                       :
                    // else
            T1(GCEM_LOG_PI) * (p - T1(1)) / T1(2) + lgamma(a) + lmgamma_recur(a - T1(0.5), p - T2(1)));
}

} // namespace internal

/**
 * Compile-time log multivariate gamma function
 *
 * @param a a real-valued input.
 * @param p integral-valued input.
 * @return computes log-multivariate gamma function via recursion
 * \f[ \Gamma_p(a) = \pi^{(p-1)/2} \Gamma(a) \Gamma_{p-1}(a-0.5) \f]
 * where \f$ \Gamma_1(a) = \Gamma(a) \f$.
 */

template <typename T1, typename T2>
constexpr auto lmgamma(const T1 a, const T2 p) noexcept -> return_t<T1>
{
    return internal::lmgamma_recur(static_cast<return_t<T1>>(a), p);
}

#endif
