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
 * compile-time find_exponent function
 */

#ifndef GCEM_find_exponent_HPP
#define GCEM_find_exponent_HPP

namespace internal {

template <typename T>
constexpr auto find_exponent(const T x, const llint_t exponent) noexcept -> llint_t
{
    return (x < T(1)    ? find_exponent(x * T(10), exponent - llint_t(1))
            : x > T(10) ? find_exponent(x / T(10), exponent + llint_t(1))
                        :
                        // else
                exponent);
}

} // namespace internal

#endif
