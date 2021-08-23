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

#ifndef TETL_CCTYPE_TOLOWER_HPP
#define TETL_CCTYPE_TOLOWER_HPP

#include "etl/_assert/macro.hpp"
#include "etl/_cctype/isupper.hpp"

namespace etl {

/// \brief Converts the given character to lowercase according to the character
/// conversion rules defined by the default C locale.
///
/// In the default "C" locale, the following uppercase letters
/// **ABCDEFGHIJKLMNOPQRSTUVWXYZ** are replaced with respective lowercase
/// letters
/// **abcdefghijklmnopqrstuvwxyz**.
///
/// \param ch Character to classify.
///
/// \returns Lowercase version of ch or unmodified ch if no lowercase version is
/// listed in the current C locale.
///
/// https://en.cppreference.com/w/cpp/string/byte/tolower
///
/// \module Strings
[[nodiscard]] constexpr auto tolower(int ch) noexcept -> int
{
    // ch must de representable as a unsigned char
    TETL_ASSERT(static_cast<unsigned char>(ch) == ch);

    if (isupper(ch) != 0) { return static_cast<int>(ch + 32); }
    return static_cast<int>(ch);
}
} // namespace etl

#endif // TETL_CCTYPE_TOLOWER_HPP