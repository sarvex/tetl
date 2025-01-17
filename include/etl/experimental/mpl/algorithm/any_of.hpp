// SPDX-License-Identifier: BSL-1.0

#ifndef ETL_EXPERIMENTAL_MPL_ALGORITHM_ANY_OF_HPP
#define ETL_EXPERIMENTAL_MPL_ALGORITHM_ANY_OF_HPP

#include "etl/cstddef.hpp"
#include "etl/tuple.hpp"
#include "etl/type_traits.hpp"

namespace etl::experimental::mpl {

namespace detail {

template <etl::size_t... Is, typename... Ts, typename F>
constexpr auto any_of_impl(etl::index_sequence<Is...> /*is*/, tuple<Ts...>& t, F f)
{
    constexpr auto trueT = type<true_type>();
    if constexpr (((type<decltype(f(get<Is>(t)))> {} == trueT) || ...)) {
        return true_c;
    } else {
        return false_c;
    }
}

} // namespace detail

template <typename... Ts, typename F>
constexpr auto any_of(tuple<Ts...>& t, F f)
{
    constexpr auto indices = etl::make_index_sequence<sizeof...(Ts)> {};
    return detail::any_of_impl(indices, t, f);
}

} // namespace etl::experimental::mpl

#endif // ETL_EXPERIMENTAL_MPL_ALGORITHM_ANY_OF_HPP
