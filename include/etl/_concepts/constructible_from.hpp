// SPDX-License-Identifier: BSL-1.0

#ifndef TETL_CONCEPTS_CONSTRUCTIBLE_FROM_HPP
#define TETL_CONCEPTS_CONSTRUCTIBLE_FROM_HPP

#include "etl/_concepts/destructible.hpp"
#include "etl/_type_traits/is_constructible.hpp"

#if defined(__cpp_concepts)
namespace etl {

/// \brief The constructible_from concept specifies that a variable of type T
/// can be initialized with the given set of argument types Args....
template <typename T, typename... Args>
concept constructible_from = destructible<T> && is_constructible_v<T, Args...>;

} // namespace etl
#endif

#endif // TETL_CONCEPTS_CONSTRUCTIBLE_FROM_HPP
