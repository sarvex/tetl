// SPDX-License-Identifier: BSL-1.0

#ifndef TETL_COMPARE_NAMED_FUNCTIONS_HPP
#define TETL_COMPARE_NAMED_FUNCTIONS_HPP

#include "etl/_compare/partial_ordering.hpp"

#if defined(__cpp_impl_three_way_comparison)

namespace etl {

[[nodiscard]] constexpr auto is_eq(partial_ordering cmp) noexcept -> bool { return cmp == nullptr; }
[[nodiscard]] constexpr auto is_neq(partial_ordering cmp) noexcept -> bool { return cmp != nullptr; }
[[nodiscard]] constexpr auto is_lt(partial_ordering cmp) noexcept -> bool { return cmp < nullptr; }
[[nodiscard]] constexpr auto is_lteq(partial_ordering cmp) noexcept -> bool { return cmp <= nullptr; }
[[nodiscard]] constexpr auto is_gt(partial_ordering cmp) noexcept -> bool { return cmp > nullptr; }
[[nodiscard]] constexpr auto is_gteq(partial_ordering cmp) noexcept -> bool { return cmp >= nullptr; }

} // namespace etl

#endif

#endif // TETL_COMPARE_NAMED_FUNCTIONS_HPP
