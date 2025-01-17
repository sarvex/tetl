// SPDX-License-Identifier: BSL-1.0

#ifndef TETL_CONCEPTS_UNSIGNED_INTEGRAL_HPP
#define TETL_CONCEPTS_UNSIGNED_INTEGRAL_HPP

#include "etl/_concepts/integral.hpp"
#include "etl/_type_traits/is_unsigned.hpp"

#if defined(__cpp_concepts)
namespace etl {

/// \brief The concept unsigned_integral<T> is satisfied if and only if T is an
/// integral type and is_unsigned_v<T> is true.
template <typename T>
concept unsigned_integral = integral<T> && is_unsigned_v<T>;

} // namespace etl
#endif

#endif // TETL_CONCEPTS_UNSIGNED_INTEGRAL_HPP
