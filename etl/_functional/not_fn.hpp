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

#ifndef TETL_FUNCTIONAL_NOT_FN_HPP
#define TETL_FUNCTIONAL_NOT_FN_HPP

#include "etl/_functional/invoke.hpp"
#include "etl/_utility/forward.hpp"
#include "etl/_utility/move.hpp"

namespace etl {

namespace detail {
template <typename F>
struct not_fn_t {
    F f;

    template <typename... Args>
    constexpr auto operator()(Args&&... args) & noexcept(
        noexcept(!invoke(f, forward<Args>(args)...)))
        -> decltype(!invoke(f, forward<Args>(args)...))
    {
        return !invoke(f, forward<Args>(args)...);
    }

    template <typename... Args>
    constexpr auto operator()(Args&&... args) const& noexcept(
        noexcept(!invoke(f, forward<Args>(args)...)))
        -> decltype(!invoke(f, forward<Args>(args)...))
    {
        return !invoke(f, forward<Args>(args)...);
    }

    template <typename... Args>
    constexpr auto operator()(Args&&... args) && noexcept(
        noexcept(!invoke(move(f), forward<Args>(args)...)))
        -> decltype(!invoke(move(f), forward<Args>(args)...))
    {
        return !invoke(move(f), forward<Args>(args)...);
    }

    template <typename... Args>
    constexpr auto operator()(Args&&... args) const&& noexcept(
        noexcept(!invoke(move(f), forward<Args>(args)...)))
        -> decltype(!invoke(move(f), forward<Args>(args)...))
    {
        return !invoke(move(f), forward<Args>(args)...);
    }
};
} // namespace detail

template <typename F>
constexpr auto not_fn(F&& f) -> detail::not_fn_t<decay_t<F>>
{
    return { forward<F>(f) };
}

} // namespace etl

#endif // TETL_FUNCTIONAL_NOT_FN_HPP