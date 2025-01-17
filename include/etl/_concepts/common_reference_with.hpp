// SPDX-License-Identifier: BSL-1.0

#ifndef TETL_CONCEPTS_COMMON_REFERENCE_WITH_HPP
#define TETL_CONCEPTS_COMMON_REFERENCE_WITH_HPP

#include "etl/_concepts/convertible_to.hpp"
#include "etl/_concepts/same_as.hpp"
#include "etl/_type_traits/common_reference.hpp"

#if defined(__cpp_concepts)
namespace etl {

// clang-format off
template <typename T, typename U>
concept common_reference_with =
        same_as<common_reference_t<T, U>, common_reference_t<U, T>>
    &&  convertible_to<T, common_reference_t<T, U>>
    &&  convertible_to<U, common_reference_t<T, U>>;
// clang-format on

} // namespace etl
#endif

#endif // TETL_CONCEPTS_COMMON_REFERENCE_WITH_HPP
