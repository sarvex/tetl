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

#ifndef ETL_EXPERIMENTAL_META_TYPES_TYPE_HPP
#define ETL_EXPERIMENTAL_META_TYPES_TYPE_HPP

#include "etl/experimental/meta/types/integral_constant.hpp"

#include "etl/tuple.hpp"
#include "etl/type_traits.hpp"

namespace etl::experimental::meta {

template <typename T>
struct type {
    using name = T;
};

template <typename T>
inline constexpr auto type_c = type<T> {};

template <typename T, typename U>
constexpr auto operator==(type<T> /*lhs*/, type<U> /*rhs*/) -> etl::false_type
{
    return {};
}
template <typename T>
constexpr auto operator==(type<T> /*lhs*/, type<T> /*rhs*/) -> etl::true_type
{
    return {};
}

template <typename T, typename U>
constexpr auto operator!=(type<T> /*lhs*/, type<U> /*rhs*/) -> etl::true_type
{
    return {};
}
template <typename T>
constexpr auto operator!=(type<T> /*lhs*/, type<T> /*rhs*/) -> etl::false_type
{
    return {};
}

template <typename T>
constexpr auto type_id(T&& /*t*/)
{
    return type_c<remove_cvref_t<T>>;
}

template <typename T>
constexpr auto type_id(type<T>&& /*t*/)
{
    return type_c<remove_reference_t<T>>;
}

template <typename T>
constexpr auto size_of(type<T> /*t*/)
{
    return size_c<sizeof(T)>;
}

template <typename... Types>
[[nodiscard]] constexpr auto make_type_tuple()
{
    return etl::tuple<type<etl::decay_t<Types>>...>();
}

} // namespace etl::experimental::meta

#endif // ETL_EXPERIMENTAL_META_TYPES_TYPE_HPP