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

#ifndef TETL_NET_BUFFER_HPP
#define TETL_NET_BUFFER_HPP

#include "etl/version.hpp"

#include "etl/array.hpp"
#include "etl/vector.hpp"

#include "etl/experimental/net/buffer_const.hpp"
#include "etl/experimental/net/buffer_mutable.hpp"

namespace etl::experimental::net {
inline auto make_buffer(void* data, size_t size) noexcept -> mutable_buffer
{
    return mutable_buffer { data, size };
}

inline auto make_buffer(void const* data, size_t size) noexcept -> const_buffer
{
    return const_buffer { data, size };
}

template <typename T, ::etl::size_t Size>
inline auto make_buffer(etl::array<T, Size>& array) noexcept -> mutable_buffer
{
    return mutable_buffer { array.data(), array.size() };
}

template <typename T, ::etl::size_t Size>
inline auto make_buffer(etl::array<T, Size> const& array) noexcept -> const_buffer
{
    return const_buffer { array.data(), array.size() };
}

template <typename T, ::etl::size_t Size>
inline auto make_buffer(etl::static_vector<T, Size>& vec) noexcept
    -> mutable_buffer
{
    return mutable_buffer { vec.data(), vec.size() };
}

template <typename T, ::etl::size_t Size>
inline auto make_buffer(etl::static_vector<T, Size> const& vec) noexcept
    -> const_buffer
{
    return const_buffer { vec.data(), vec.size() };
}

} // namespace etl::experimental::net

#endif // TETL_NET_BUFFER_HPP
