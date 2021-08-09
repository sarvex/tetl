// Copyright (c) Tobias Hienzsch. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//  * Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.

#ifndef TETL_DETAIL_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
#define TETL_DETAIL_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP

#include "etl/detail/type_traits/bool_constant.hpp"
#include "etl/detail/type_traits/declval.hpp"
#include "etl/detail/type_traits/void_t.hpp"

namespace etl {

namespace detail {
template <typename, typename T, typename... Args>
struct is_constructible_helper : ::etl::false_type {
};

template <typename T, typename... Args>
struct is_constructible_helper<
    ::etl::void_t<decltype(T(::etl::declval<Args>()...))>, T, Args...>
    : ::etl::true_type {
};
} // namespace detail

template <typename T, typename... Args>
using is_constructible = detail::is_constructible_helper<void_t<>, T, Args...>;

template <typename T, typename... Args>
inline constexpr bool is_constructible_v = is_constructible<T, Args...>::value;

} // namespace etl

#endif // TETL_DETAIL_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP