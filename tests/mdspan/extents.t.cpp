// SPDX-License-Identifier: BSL-1.0

#include <etl/mdspan.hpp>

#include "testing/testing.hpp"

template <typename SizeType>
constexpr auto test_extents() -> bool
{
    auto ed1 = etl::extents<SizeType, etl::dynamic_extent> {};
    assert(ed1.rank() == 1);
    assert(ed1.rank_dynamic() == 1);
    assert(ed1.static_extent(0) == etl::dynamic_extent);

    auto ed2 = etl::extents<SizeType, etl::dynamic_extent, etl::dynamic_extent> {};
    assert(ed2.rank() == 2);
    assert(ed2.rank_dynamic() == 2);
    assert(ed2.static_extent(0) == etl::dynamic_extent);
    assert(ed2.static_extent(1) == etl::dynamic_extent);

    auto es1 = etl::extents<SizeType, 2> {};
    assert(es1.rank() == 1);
    assert(es1.rank_dynamic() == 0);
    assert(es1.static_extent(0) == 2);

    auto es2 = etl::extents<SizeType, 2, 4> {};
    assert(es2.rank() == 2);
    assert(es2.rank_dynamic() == 0);
    assert(es2.static_extent(0) == 2);
    assert(es2.static_extent(1) == 4);

    auto es3 = etl::extents<SizeType, 2, 2, 2> {};
    assert(es3.rank() == 3);
    assert(es3.rank_dynamic() == 0);

    auto eds2 = etl::extents<SizeType, 2, etl::dynamic_extent> {};
    assert(eds2.rank() == 2);
    assert(eds2.rank_dynamic() == 1);

    return true;
}

constexpr auto test_all() -> bool
{
    assert(test_extents<etl::uint8_t>());
    assert(test_extents<etl::uint16_t>());
    assert(test_extents<etl::uint32_t>());
    assert(test_extents<etl::uint64_t>());

    assert(test_extents<etl::int8_t>());
    assert(test_extents<etl::int16_t>());
    assert(test_extents<etl::int32_t>());
    assert(test_extents<etl::int64_t>());

    assert(test_extents<etl::size_t>());
    assert(test_extents<etl::ptrdiff_t>());
    return true;
}

auto main() -> int
{
    assert(test_all());
    static_assert(test_all());
    return 0;
}
