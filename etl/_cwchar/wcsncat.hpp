/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_CWCHAR_WCSNCAT_HPP
#define TETL_CWCHAR_WCSNCAT_HPP

#include "etl/_cassert/macro.hpp"
#include "etl/_cstddef/size_t.hpp"
#include "etl/_strings/cstr_algorithm.hpp"

namespace etl {

/// \brief Appends at most count wide characters from the wide string pointed to
/// by src to the end of the character string pointed to by dest, stopping if
/// the null terminator is copied. The wide character src[0] replaces the null
/// terminator at the end of dest. The null terminator is always appended in the
/// end (so the maximum number of wide characters the function may write is
/// count+1).
///
/// \details The destination byte string must have enough space for the contents
/// of both dest and src plus the terminating null character, except that the
/// size of src is limited to count. The behavior is undefined if the strings
/// overlap.
constexpr auto wcsncat(wchar_t* dest, wchar_t const* src, etl::size_t const count) -> wchar_t*
{
    return detail::strncat_impl<wchar_t, etl::size_t>(dest, src, count);
}

} // namespace etl

#endif // TETL_CWCHAR_WCSNCAT_HPP
