// SPDX-License-Identifier: BSL-1.0

#ifndef TETL_CSTRING_MEMCPY_HPP
#define TETL_CSTRING_MEMCPY_HPP

#include "etl/_cstddef/size_t.hpp"
#include "etl/_strings/cstr_algorithm.hpp"

namespace etl {

/// \brief Copy the first n bytes pointed to by src to the buffer pointed to by
/// dest. Source and destination may not overlap. If source and destination
/// might overlap, memmove() must be used instead.
constexpr auto memcpy(void* dest, void const* src, etl::size_t n) -> void*
{
    return detail::memcpy_impl<unsigned char, etl::size_t>(dest, src, n);
}

} // namespace etl

#endif // TETL_CSTRING_MEMCPY_HPP
