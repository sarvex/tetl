// SPDX-License-Identifier: BSL-1.0

#ifndef TETL_CCTYPE_ISXDIGIT_HPP
#define TETL_CCTYPE_ISXDIGIT_HPP

namespace etl {
/// \brief Checks if the given character is a hexadecimal numeric character
/// (0123456789abcdefABCDEF).
///
/// \param ch Character to classify.
///
/// \returns Non-zero value if the character is a hexadecimal numeric character,
/// zero otherwise.
///
/// https://en.cppreference.com/w/cpp/string/byte/isxdigit
[[nodiscard]] constexpr auto isxdigit(int ch) noexcept -> int
{
    auto const isDigit    = ch >= '0' && ch <= '9';
    auto const isHexLower = ch >= 'a' && ch <= 'f';
    auto const isHexUpper = ch >= 'A' && ch <= 'F';

    return static_cast<int>(isDigit || isHexLower || isHexUpper);
}
} // namespace etl

#endif // TETL_CCTYPE_ISXDIGIT_HPP
