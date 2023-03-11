/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_FUNCTIONAL_IDENTITY_HPP
#define TETL_FUNCTIONAL_IDENTITY_HPP

#include "etl/_utility/forward.hpp"

namespace etl {

/// \brief etl::identity is a function object type whose operator() returns its
/// argument unchanged.
struct identity {
    using is_transparent = void;

    template <typename T>
    [[nodiscard]] constexpr auto operator()(T&& t) const noexcept -> T&&
    {
        return forward<T>(t);
    }
};

} // namespace etl

#endif // TETL_FUNCTIONAL_IDENTITY_HPP