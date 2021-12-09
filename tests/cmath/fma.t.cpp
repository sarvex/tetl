/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#include "etl/cmath.hpp"

#include "etl/cassert.hpp"
#include "etl/numbers.hpp"

#include "testing/approx.hpp"
#include "testing/testing.hpp"

template <typename T>
constexpr auto test() -> bool
{
    assert(approx(etl::fma(T(0), T(0), T(0)), T(0)));
    assert(approx(etl::fma(T(0), T(1), T(0)), T(0)));
    assert(approx(etl::fma(T(1), T(0), T(0)), T(0)));
    assert(approx(etl::fma(T(1), T(1), T(0)), T(1)));
    assert(approx(etl::fma(T(1), T(1), T(1)), T(2)));
    return true;
}

auto main() -> int
{
    static_assert(test<float>());
    static_assert(test<double>());
    static_assert(test<long double>());
    assert(test<float>());
    assert(test<double>());
    assert(test<long double>());
    return 0;
}