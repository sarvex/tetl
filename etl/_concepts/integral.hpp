/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_CONCEPTS_INTEGRAL_HPP
#define TETL_CONCEPTS_INTEGRAL_HPP

#include "etl/_type_traits/is_integral.hpp"

#if defined(__cpp_concepts)
namespace etl {

/// \brief The concept integral<T> is satisfied if and only if T is an integral
/// type.
template <typename T>
concept integral = is_integral_v<T>;

} // namespace etl
#endif

#endif // TETL_CONCEPTS_INTEGRAL_HPP
