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

#ifndef TETL_TUPLE_TUPLE_HPP
#define TETL_TUPLE_TUPLE_HPP

#include "etl/_tuple/ignore.hpp"
#include "etl/_tuple/tuple_element.hpp"
#include "etl/_tuple/tuple_size.hpp"

namespace etl {
template <typename First, typename... Rest>
struct tuple : public tuple<Rest...> {
    tuple() = default;
    tuple(First f, Rest... rest) : tuple<Rest...>(rest...), first(f) { }

    First first;
};

template <typename First>
struct tuple<First> {
    tuple() = default;
    tuple(First f) : first(f) { }

    First first;
};

namespace detail {
template <int Index, typename First, typename... Rest>
struct get_impl {
    static constexpr auto value(tuple<First, Rest...> const* t)
        -> decltype(get_impl<Index - 1, Rest...>::value(t))
    {
        return get_impl<Index - 1, Rest...>::value(t);
    }
};

template <typename First, typename... Rest>
struct get_impl<0, First, Rest...> {
    static constexpr auto value(tuple<First, Rest...> const* t) -> First
    {
        return t->first;
    }
};

} // namespace detail

template <int Index, typename First, typename... Rest>
constexpr auto get(tuple<First, Rest...> const& t)
    -> decltype(detail::get_impl<Index, First, Rest...>::value(&t))
{
    return detail::get_impl<Index, First, Rest...>::value(&t);
}

template <etl::size_t I, typename Head, typename... Tail>
struct tuple_element<I, etl::tuple<Head, Tail...>>
    : etl::tuple_element<I - 1, etl::tuple<Tail...>> {
};

template <typename Head, typename... Tail>
struct tuple_element<0, etl::tuple<Head, Tail...>> {
    using type = Head;
};

} // namespace etl

#endif // TETL_TUPLE_TUPLE_HPP