/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_TYPE_TRAITS_IS_VOID_HPP
#define TETL_TYPE_TRAITS_IS_VOID_HPP

#include "etl/_type_traits/is_same.hpp"
#include "etl/_type_traits/remove_cv.hpp"

namespace etl {

/// \brief Define a member typedef only if a boolean constant is true.
/// \group is_void
template <typename T>
struct is_void : etl::is_same<void, etl::remove_cv_t<T>> {
};

/// \group is_void
template <typename T>
inline constexpr bool is_void_v = etl::is_same_v<void, etl::remove_cv_t<T>>;

} // namespace etl

#endif // TETL_TYPE_TRAITS_IS_VOID_HPP