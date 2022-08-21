/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_MEMORY_CONSTRUCT_AT_HPP
#define TETL_MEMORY_CONSTRUCT_AT_HPP

#include "etl/_cassert/macro.hpp"
#include "etl/_type_traits/declval.hpp"
#include "etl/_utility/forward.hpp"

namespace etl {

/// \brief Creates a T object initialized with arguments args... at given
/// address p.
template <typename T, typename... Args, typename = decltype(::new (declval<void*>()) T(declval<Args>()...))>
[[nodiscard]] constexpr auto construct_at(T* p, Args&&... args) -> T*
{
    TETL_ASSERT(p != nullptr);
    return ::new (static_cast<void*>(p)) T(etl::forward<Args>(args)...);
}

} // namespace etl

#endif // TETL_MEMORY_CONSTRUCT_AT_HPP
