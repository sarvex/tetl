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
 * find the whole number part of x = n + r, where -0.5 <= r <= 0.5
 */

#ifndef GCEM_find_whole_HPP
#define GCEM_find_whole_HPP

namespace internal {

template <typename T>
constexpr auto find_whole(const T x) noexcept -> llint_t
{
    return (abs(x - internal::floor_check(x)) >= T(0.5) ? // if
                static_cast<llint_t>(internal::floor_check(x) + sgn(x))
                                                        :
                                                        // else
                static_cast<llint_t>(internal::floor_check(x)));
}

} // namespace internal

#endif
