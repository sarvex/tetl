/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt

#ifndef TETL_CWCTYPE_ISWBLANK_HPP
#define TETL_CWCTYPE_ISWBLANK_HPP

#include "etl/_cwchar/wint_t.hpp"

namespace etl {
/// \brief Checks if the given wide character is classified as blank character
/// (that is, a whitespace character used to separate words in a sentence) by
/// the current C locale. In the default C locale, only space (0x20) and
/// horizontal tab (0x09) are blank characters.
///
/// \details If the value of ch is neither representable as a wchar_t nor equal
/// to the value of the macro WEOF, the behavior is undefined.
///
/// https://en.cppreference.com/w/cpp/string/wide/iswblank
///
/// \module Strings
[[nodiscard]] constexpr auto iswblank(wint_t ch) noexcept -> int
{
    return static_cast<int>(ch == L' ' || ch == L'\t');
}
} // namespace etl

#endif // TETL_CWCTYPE_ISWBLANK_HPP