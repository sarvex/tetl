// SPDX-License-Identifier: BSL-1.0

#ifndef ETL_EXPERIMENTAL_MPL_TYPES_TYPE_HPP
#define ETL_EXPERIMENTAL_MPL_TYPES_TYPE_HPP

#include "etl/experimental/mpl/types/integral_constant.hpp"

#include "etl/tuple.hpp"
#include "etl/type_traits.hpp"

namespace etl::experimental::mpl {

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

} // namespace etl::experimental::mpl

#endif // ETL_EXPERIMENTAL_MPL_TYPES_TYPE_HPP
