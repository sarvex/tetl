/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP
#define TETL_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP

#include "etl/_config/builtin_functions.hpp"
#include "etl/_type_traits/bool_constant.hpp"

namespace etl {

/// https://en.cppreference.com/w/cpp/types/has_virtual_destructor
/// \group has_virtual_destructor
template <typename T>
struct has_virtual_destructor
    : etl::bool_constant<TETL_BUILTIN_HAS_VIRTUAL_DESTRUCTOR(T)> {
};

/// https://en.cppreference.com/w/cpp/types/has_virtual_destructor
/// \group has_virtual_destructor
template <typename T>
inline constexpr auto has_virtual_destructor_v
    = TETL_BUILTIN_HAS_VIRTUAL_DESTRUCTOR(T);

} // namespace etl

#endif // TETL_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP