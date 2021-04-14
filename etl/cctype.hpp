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

#ifndef TETL_CCTYPE_HPP
#define TETL_CCTYPE_HPP

#include "etl/version.hpp"

#include "etl/cassert.hpp"
#include "etl/limits.hpp"

namespace etl
{
/// \brief Checks if the given character is an alphanumeric character as
/// classified by the default C locale.
/// \returns Non-zero value if the character is an alphanumeric character, 0
/// otherwise.
/// \notes
/// [cppreference.com/w/cpp/string/byte/isalnum](https://en.cppreference.com/w/cpp/string/byte/isalnum)
/// \module Strings
[[nodiscard]] constexpr auto isalnum(int ch) noexcept -> int
{
  // ch must de representable as a unsigned char
  TETL_ASSERT(static_cast<unsigned char>(ch) == ch);

  auto isDigit = ch >= '0' && ch <= '9';
  auto isLower = ch >= 'a' && ch <= 'z';
  auto isUpper = ch >= 'A' && ch <= 'Z';

  return static_cast<int>(isDigit || isLower || isUpper);
}

/// \brief Checks if the given character is an alphabetic character as
/// classified by the default C locale.
/// \returns Non-zero value if the character is an alphabetic character, 0
/// otherwise.
/// \notes
/// [cppreference.com/w/cpp/string/byte/isalpha](https://en.cppreference.com/w/cpp/string/byte/isalpha)
/// \module Strings
[[nodiscard]] constexpr auto isalpha(int ch) noexcept -> int
{
  // ch must de representable as a unsigned char
  TETL_ASSERT(static_cast<unsigned char>(ch) == ch);

  auto isLower = ch >= 'a' && ch <= 'z';
  auto isUpper = ch >= 'A' && ch <= 'Z';

  return static_cast<int>(isLower || isUpper);
}

/// \brief Checks if the given character is classified as a lowercase character
/// according to the default C locale.
/// \returns Non-zero value if the character is a lowercase letter, zero
/// otherwise.
/// \notes
/// [cppreference.com/w/cpp/string/byte/islower](https://en.cppreference.com/w/cpp/string/byte/islower)
/// \module Strings
[[nodiscard]] constexpr auto islower(int ch) noexcept -> int
{
  // ch must de representable as a unsigned char
  TETL_ASSERT(static_cast<unsigned char>(ch) == ch);
  return static_cast<int>(ch >= 'a' && ch <= 'z');
}

/// \brief Checks if the given character is classified as a uppercase character
/// according to the default C locale.
/// \returns Non-zero value if the character is a uppercase letter, zero
/// otherwise.
/// \notes
/// [cppreference.com/w/cpp/string/byte/isupper](https://en.cppreference.com/w/cpp/string/byte/isupper)
/// \module Strings
[[nodiscard]] constexpr auto isupper(int ch) noexcept -> int
{
  // ch must de representable as a unsigned char
  TETL_ASSERT(static_cast<unsigned char>(ch) == ch);
  return static_cast<int>(ch >= 'A' && ch <= 'Z');
}

/// \brief Checks if the given character is one of the 10 decimal digits:
/// 0123456789.
/// \returns Non-zero value if the character is a numeric character, zero
/// otherwise.
/// \notes
/// [cppreference.com/w/cpp/string/byte/isdigit](https://en.cppreference.com/w/cpp/string/byte/isdigit)
/// \module Strings
[[nodiscard]] constexpr auto isdigit(int ch) noexcept -> int
{
  // ch must de representable as a unsigned char
  TETL_ASSERT(static_cast<unsigned char>(ch) == ch);
  return static_cast<int>(ch >= '0' && ch <= '9');
}

/// \brief Checks if the given character is a hexadecimal numeric character
/// (0123456789abcdefABCDEF).
/// \returns Non-zero value if the character is a hexadecimal numeric character,
/// zero otherwise.
/// \notes
/// [cppreference.com/w/cpp/string/byte/isxdigit](https://en.cppreference.com/w/cpp/string/byte/isxdigit)
/// \module Strings
[[nodiscard]] constexpr auto isxdigit(int ch) noexcept -> int
{
  // ch must de representable as a unsigned char
  TETL_ASSERT(static_cast<unsigned char>(ch) == ch);

  auto const isDigit    = ch >= '0' && ch <= '9';
  auto const isHexLower = ch >= 'a' && ch <= 'f';
  auto const isHexUpper = ch >= 'A' && ch <= 'F';

  return static_cast<int>(isDigit || isHexLower || isHexUpper);
}

/// \brief Checks if the given character is whitespace character as classified
/// by the default C locale.
/// \returns Non-zero value if the character is a whitespace character, zero
/// otherwise.
/// \notes
/// [cppreference.com/w/cpp/string/byte/isspace](https://en.cppreference.com/w/cpp/string/byte/isspace)
/// \module Strings
[[nodiscard]] constexpr auto isspace(int ch) noexcept -> int
{
  // ch must de representable as a unsigned char
  TETL_ASSERT(static_cast<unsigned char>(ch) == ch);

  auto const space          = ch == ' ';
  auto const formFeed       = ch == '\f';
  auto const lineFeed       = ch == '\n';
  auto const carriageReturn = ch == '\r';
  auto const horizontalTab  = ch == '\t';
  auto const verticalTab    = ch == '\v';

  return static_cast<int>(space || formFeed || lineFeed || carriageReturn
                          || horizontalTab || verticalTab);
}

/// \brief Checks if the given character is a blank character as classified by
/// the currently installed C locale. Blank characters are whitespace characters
/// used to separate words within a sentence. In the default C locale, only
/// space (0x20) and horizontal tab (0x09) are classified as blank characters.
/// \returns Non-zero value if the character is a blank character, zero
/// otherwise.
/// \notes
/// [cppreference.com/w/cpp/string/byte/isblank](https://en.cppreference.com/w/cpp/string/byte/isblank)
/// \module Strings
[[nodiscard]] constexpr auto isblank(int ch) noexcept -> int
{
  // ch must de representable as a unsigned char
  TETL_ASSERT(static_cast<unsigned char>(ch) == ch);

  auto const space         = ch == ' ';
  auto const horizontalTab = ch == '\t';

  return static_cast<int>(space || horizontalTab);
}

/// \brief Checks if the given character is a punctuation character as
/// classified by the current C locale.
///
/// The default C locale classifies the characters
/// !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~ as punctuation.
/// \returns Non-zero value if the character is a punctuation character, zero
/// otherwise.
/// \notes
/// [cppreference.com/w/cpp/string/byte/ispunct](https://en.cppreference.com/w/cpp/string/byte/ispunct)
/// \module Strings
[[nodiscard]] constexpr auto ispunct(int ch) noexcept -> int
{
  // ch must de representable as a unsigned char
  TETL_ASSERT(static_cast<unsigned char>(ch) == ch);

  auto const sec1 = ch >= '!' && ch <= '/';
  auto const sec2 = ch >= ':' && ch <= '@';
  auto const sec3 = ch >= '[' && ch <= '`';
  auto const sec4 = ch >= '{' && ch <= '~';

  return static_cast<int>(sec1 || sec2 || sec3 || sec4);
}

/// \brief Checks if the given character is graphic (has a graphical
/// representation) as classified by the default C locale.
/// \returns Non-zero value if the character is a punctuation character, zero
/// otherwise.
/// \notes
/// [cppreference.com/w/cpp/string/byte/isgraph](https://en.cppreference.com/w/cpp/string/byte/isgraph)
/// \module Strings
[[nodiscard]] constexpr auto isgraph(int ch) noexcept -> int
{
  // ch must de representable as a unsigned char
  TETL_ASSERT(static_cast<unsigned char>(ch) == ch);

  auto const isDigit = isdigit(ch) != 0;
  auto const isUpper = isupper(ch) != 0;
  auto const isLower = islower(ch) != 0;
  auto const isPunct = ispunct(ch) != 0;

  return static_cast<int>(isDigit || isLower || isUpper || isPunct);
}

/// \brief Checks if ch is a printable character as classified by the default C
/// locale.
/// \returns Non-zero value if the character is a punctuation character, zero
/// otherwise.
/// \notes
/// [cppreference.com/w/cpp/string/byte/isprint](https://en.cppreference.com/w/cpp/string/byte/isprint)
/// \module Strings
[[nodiscard]] constexpr auto isprint(int ch) noexcept -> int
{
  // ch must de representable as a unsigned char
  TETL_ASSERT(static_cast<unsigned char>(ch) == ch);

  return static_cast<int>(etl::isgraph(ch) != 0 || ch == ' ');
}

/// \brief Checks if the given character is a control character as classified by
/// the currently installed C locale. In the default, "C" locale, the control
/// characters are the characters with the codes 0x00-0x1F and 0x7F.
/// \returns Non-zero value if the character is a control character, zero
/// otherwise.
/// \notes
/// [cppreference.com/w/cpp/string/byte/iscntrl](https://en.cppreference.com/w/cpp/string/byte/iscntrl)
/// \module Strings
[[nodiscard]] constexpr auto iscntrl(int ch) noexcept -> int
{
  // ch must de representable as a unsigned char
  TETL_ASSERT(static_cast<unsigned char>(ch) == ch);

  return static_cast<int>((ch >= 0x00 && ch <= 0x1f) || ch == 0x7F);
}

/// \brief Converts the given character to lowercase according to the character
/// conversion rules defined by the default C locale.
///
/// In the default "C" locale, the following uppercase letters
/// **ABCDEFGHIJKLMNOPQRSTUVWXYZ** are replaced with respective lowercase
/// letters
/// **abcdefghijklmnopqrstuvwxyz**.
/// \returns Lowercase version of ch or unmodified ch if no lowercase version is
/// listed in the current C locale.
/// \notes
/// [cppreference.com/w/cpp/string/byte/tolower](https://en.cppreference.com/w/cpp/string/byte/tolower)
/// \module Strings
[[nodiscard]] constexpr auto tolower(int ch) noexcept -> int
{
  // ch must de representable as a unsigned char
  TETL_ASSERT(static_cast<unsigned char>(ch) == ch);

  if (isupper(ch) != 0) { return static_cast<int>(ch + 32); }
  return static_cast<int>(ch);
}

/// \brief Converts the given character to uppercase according to the character
/// conversion rules defined by the default C locale.
///
/// In the default "C" locale, the following lowercase letters
/// **abcdefghijklmnopqrstuvwxyz** are replaced with respective uppercase
/// letters
/// **ABCDEFGHIJKLMNOPQRSTUVWXYZ**.
/// \returns Converted character or ch if no uppercase version is defined by the
/// current C locale.
/// \notes
/// [cppreference.com/w/cpp/string/byte/toupper](https://en.cppreference.com/w/cpp/string/byte/toupper)
/// \module Strings
[[nodiscard]] constexpr auto toupper(int ch) noexcept -> int
{
  // ch must de representable as a unsigned char
  TETL_ASSERT(static_cast<unsigned char>(ch) == ch);

  if (islower(ch) != 0) { return static_cast<int>(ch - 32); }
  return static_cast<int>(ch);
}
}  // namespace etl
#endif  // TETL_CCTYPE_HPP
