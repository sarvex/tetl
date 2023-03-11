/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef ETL_EXPERIMENTAL_META_TYPES_INTEGRAL_CONSTANT_HPP
#define ETL_EXPERIMENTAL_META_TYPES_INTEGRAL_CONSTANT_HPP

#include "etl/type_traits.hpp"

namespace etl::experimental::meta {

using etl::integral_constant;

template <int Val>
inline constexpr auto int_c = integral_constant<int, Val> {};

template <etl::size_t Size>
inline constexpr auto size_c = integral_constant<etl::size_t, Size> {};

} // namespace etl::experimental::meta

#endif // ETL_EXPERIMENTAL_META_TYPES_INTEGRAL_CONSTANT_HPP