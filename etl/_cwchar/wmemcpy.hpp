/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_CWCHAR_WMEMCPY_HPP
#define TETL_CWCHAR_WMEMCPY_HPP

#include "etl/_cstddef/size_t.hpp"
#include "etl/_strings/cstr_algorithm.hpp"

namespace etl {

/// \brief Copies exactly count successive wide characters from the wide
/// character array pointed to by src to the wide character array pointed to by
/// dest. If the objects overlap, the behavior is undefined. If count is zero,
/// the function does nothing.
///
/// https://en.cppreference.com/w/cpp/string/wide/wmemcpy
constexpr auto wmemcpy(wchar_t* dest, const wchar_t* src, etl::size_t count) noexcept -> wchar_t*
{
    return detail::strncpy_impl(dest, src, count);
}
} // namespace etl
#endif // TETL_CWCHAR_WMEMCPY_HPP