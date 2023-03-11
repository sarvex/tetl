/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_TYPE_TRAITS_IS_COMPOUND_HPP
#define TETL_TYPE_TRAITS_IS_COMPOUND_HPP

#include "etl/_type_traits/bool_constant.hpp"
#include "etl/_type_traits/is_fundamental.hpp"

namespace etl {

/// \brief If T is a compound type (that is, array, function, object pointer,
/// function pointer, member object pointer, member function pointer, reference,
/// class, union, or enumeration, including any cv-qualified variants), provides
/// the member constant value equal true. For any other type, value is false.
template <typename T>
struct is_compound : etl::bool_constant<!etl::is_fundamental_v<T>> { };

template <typename T>
inline constexpr bool is_compound_v = !etl::is_fundamental_v<T>;

} // namespace etl

#endif // TETL_TYPE_TRAITS_IS_COMPOUND_HPP
