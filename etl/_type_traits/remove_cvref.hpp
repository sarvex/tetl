/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_TYPE_TRAITS_REMOVE_CVREF_HPP
#define TETL_TYPE_TRAITS_REMOVE_CVREF_HPP

#include "etl/_type_traits/remove_cv.hpp"
#include "etl/_type_traits/remove_reference.hpp"

namespace etl {

/// \brief If the type T is a reference type, provides the member typedef type
/// which is the type referred to by T with its topmost cv-qualifiers removed.
/// Otherwise type is T with its topmost cv-qualifiers removed.
///
/// \details The behavior of a program that adds specializations for
/// remove_cvref is undefined.
template <typename T>
struct remove_cvref {
    using type = etl::remove_cv_t<etl::remove_reference_t<T>>;
};

template <typename T>
using remove_cvref_t = etl::remove_cv_t<etl::remove_reference_t<T>>;

} // namespace etl

#endif // TETL_TYPE_TRAITS_REMOVE_CVREF_HPP