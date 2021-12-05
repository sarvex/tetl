/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_COROUTINE_SUSPEND_NEVER_HPP
#define TETL_COROUTINE_SUSPEND_NEVER_HPP

#include "etl/_coroutine/coroutine_handle.hpp"

#if defined(__cpp_coroutines)

namespace etl {

struct suspend_never {
    constexpr auto await_ready() const noexcept -> bool { return true; }
    constexpr auto await_suspend(coroutine_handle<>) const noexcept -> void { }
    constexpr auto await_resume() const noexcept -> void { }
};

} // namespace etl

#endif // defined(__cpp_coroutines)

#endif // TETL_COROUTINE_SUSPEND_NEVER_HPP