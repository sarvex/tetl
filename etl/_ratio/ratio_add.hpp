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

#ifndef TETL_RATIO_ADD_HPP
#define TETL_RATIO_ADD_HPP

#include "etl/_ratio/ratio.hpp"

namespace etl {

/// \brief The alias template ratio_add denotes the result of adding two
/// exact rational fractions represented by the ratio specializations R1
/// and R2.
///
/// \details The result is a ratio specialization `ratio<U, V>`, such
/// that given `Num == R1::num * R2::den + R2::num * R1::den` and
/// `Denom == R1::den * R2::den` (computed without arithmetic overflow), U is
/// ratio<Num, Denom>::num and V is ratio<Num, Denom>::den.
///
/// \todo Check overflow.
template <typename R1, typename R2>
using ratio_add
    = ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den>;

} // namespace etl

#endif // TETL_RATIO_ADD_HPP