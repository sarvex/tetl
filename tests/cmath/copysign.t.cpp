// SPDX-License-Identifier: BSL-1.0

#include "etl/cmath.hpp"

#include "etl/cassert.hpp"
#include "etl/numbers.hpp"

#include "testing/approx.hpp"
#include "testing/testing.hpp"

template <typename T>
constexpr auto test() -> bool
{
    assert(approx(etl::copysign(T(0), T(1)), T(0)));
    assert(approx(etl::copysign(T(1), T(1)), T(1)));
    assert(approx(etl::copysign(T(1), T(-1)), T(-1)));

    assert(approx(etl::detail::copysign_fallback(T(0), T(1)), T(0)));
    assert(approx(etl::detail::copysign_fallback(T(1), T(1)), T(1)));
    assert(approx(etl::detail::copysign_fallback(T(1), T(-1)), T(-1)));
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
