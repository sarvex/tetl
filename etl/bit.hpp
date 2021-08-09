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

#ifndef TETL_BIT_HPP
#define TETL_BIT_HPP

#include "etl/version.hpp"

#include "etl/cstring.hpp"
#include "etl/limits.hpp"
#include "etl/type_traits.hpp"

#include "etl/detail/sfinae.hpp"

namespace etl {
/// \brief Indicates the endianness of all scalar types. If all scalar types are
/// little-endian, `endian::native` equals `endian::little`. If all scalar types
/// are big-endian, `endian::native` equals `endian::big`.
///
/// \notes
/// [cppreference.com/w/cpp/types/endian](https://en.cppreference.com/w/cpp/types/endian)
/// \module Numeric
enum struct endian {
#ifdef _WIN32
    little = 0,
    big    = 1,
    native = little
#else
    little = __ORDER_LITTLE_ENDIAN__,
    big    = __ORDER_BIG_ENDIAN__,
    native = __BYTE_ORDER__
#endif
};

/// \brief Obtain a value of type To by reinterpreting the object representation
/// of from. Every bit in the value representation of the returned To object is
/// equal to the corresponding bit in the object representation of from.
///
/// \details The values of padding bits in the returned To object are
/// unspecified. If there is no value of type To corresponding to the value
/// representation produced, the behavior is undefined. If there are multiple
/// such values, which value is produced is unspecified. This overload only
/// participates in overload resolution if sizeof(To) == sizeof(From) and both
/// To and From are TriviallyCopyable types.
///
/// \notes
/// [cppreference.com/w/cpp/numeric/bit_cast](https://en.cppreference.com/w/cpp/numeric/bit_cast)
/// \module Numeric
template <typename To, typename From>
constexpr auto bit_cast(From const& src) noexcept -> enable_if_t<
    (sizeof(To) == sizeof(From))
        and is_trivially_copyable_v<From> and is_trivially_copyable_v<To>,
    To>
{
    static_assert(is_trivially_constructible_v<To>,
        "This implementation additionally requires destination type to be "
        "trivially constructible");

    To dst;
    etl::memcpy(&dst, &src, sizeof(To));
    return dst;
}

namespace detail {
template <typename T>
using bit_unsigned_int
    = etl::bool_constant<etl::disjunction_v<etl::is_same<T, unsigned char>,
        etl::is_same<T, unsigned short>, etl::is_same<T, unsigned int>,
        etl::is_same<T, unsigned long>, etl::is_same<T, unsigned long long>>>;

template <typename T>
inline constexpr auto bit_unsigned_int_v = bit_unsigned_int<T>::value;

} // namespace detail

/// \brief Computes the result of bitwise left-rotating the value of x by s
/// positions. This operation is also known as a left circular shift.
/// \module Numeric
template <typename T>
constexpr auto rotl(T t, int s) noexcept
    -> enable_if_t<detail::bit_unsigned_int_v<T>, T>
{
    auto const cnt    = static_cast<unsigned>(s);
    auto const digits = static_cast<unsigned>(etl::numeric_limits<T>::digits);
    if ((cnt % digits) == 0) { return t; }
    return (t << (cnt % digits)) | (t >> (digits - (cnt % digits)));
}

/// \brief Computes the result of bitwise right-rotating the value of x by s
/// positions. This operation is also known as a right circular shift.
/// \module Numeric
template <typename T>
constexpr auto rotr(T t, int s) noexcept
    -> enable_if_t<detail::bit_unsigned_int_v<T>, T>
{
    auto const cnt    = static_cast<unsigned>(s);
    auto const digits = static_cast<unsigned>(etl::numeric_limits<T>::digits);
    if ((cnt % digits) == 0) { return t; }
    return (t >> (cnt % digits)) | (t << (digits - (cnt % digits)));
}

/// \brief Returns the number of 1 bits in the value of x.
///
/// \details This overload only participates in overload resolution if T is an
/// unsigned integer type (that is, unsigned char, unsigned short, unsigned int,
/// unsigned long, unsigned long long, or an extended unsigned integer type).
///
/// \module Numeric
template <typename T>
[[nodiscard]] constexpr auto popcount(T input) noexcept
    -> enable_if_t<detail::bit_unsigned_int_v<T>, int>
{
    auto count = T { 0 };
    while (input) {
        count = count + (input & T(1));
        input = input >> T(1);
    }
    return static_cast<int>(count);
}

/// \brief Checks if x is an integral power of two.
///
/// \details This overload only participates in overload resolution if T is an
/// unsigned integer type (that is, unsigned char, unsigned short, unsigned int,
/// unsigned long, unsigned long long, or an extended unsigned integer type).
///
/// \returns true if x is an integral power of two; otherwise false.
/// \module Numeric
template <typename T>
[[nodiscard]] constexpr auto has_single_bit(T x) noexcept
    -> enable_if_t<detail::bit_unsigned_int_v<T>, bool>
{
    return popcount(x) == 1;
}

/// \brief Returns the number of consecutive 0 bits in the value of x, starting
/// from the most significant bit ("left").
///
/// \details This overload only participates in overload resolution if T is an
/// unsigned integer type (that is, unsigned char, unsigned short, unsigned int,
/// unsigned long, unsigned long long, or an extended unsigned integer type).
///
/// \returns The number of consecutive 0 bits in the value of x, starting from
/// the most significant bit.
/// \module Numeric
template <typename T>
[[nodiscard]] constexpr auto countl_zero(T x) noexcept
    -> enable_if_t<detail::bit_unsigned_int_v<T>, int>
{
    auto const totalBits = etl::numeric_limits<T>::digits;
    if (x == T { 0 }) { return etl::numeric_limits<T>::digits; }

    int res = 0;
    while (!(x & (T { 1 } << (totalBits - 1)))) {
        x = (x << T { 1 });
        res++;
    }

    return res;
}

/// \brief Returns the number of consecutive 1 ("one") bits in the value of x,
/// starting from the most significant bit ("left").
///
/// \details This overload only participates in overload resolution if T is an
/// unsigned integer type (that is, unsigned char, unsigned short, unsigned int,
/// unsigned long, unsigned long long, or an extended unsigned integer type).
///
/// \returns The number of consecutive 1 bits in the value of x, starting from
/// the most significant bit.
/// \module Numeric
template <typename T>
[[nodiscard]] constexpr auto countl_one(T x) noexcept
    -> enable_if_t<detail::bit_unsigned_int_v<T>, int>
{
    auto const totalBits = etl::numeric_limits<T>::digits;
    if (x == etl::numeric_limits<T>::max()) { return totalBits; }

    int res = 0;
    while (x & (T { 1 } << (totalBits - 1))) {
        x = (x << T { 1 });
        res++;
    }

    return res;
}

/// \brief If x is not zero, calculates the number of bits needed to store the
/// value x, that is, 1+⌊log2(x)⌋. If x is zero, returns zero.
///
/// \details This overload only participates in overload resolution if T is an
/// unsigned integer type (that is, unsigned char, unsigned short, unsigned int,
/// unsigned long, unsigned long long, or an extended unsigned integer type).
/// \module Numeric
template <typename T>
[[nodiscard]] constexpr auto bit_width(T x) noexcept
    -> enable_if_t<detail::bit_unsigned_int_v<T>, int>
{
    return etl::numeric_limits<T>::digits - etl::countl_zero(x);
}

/// \brief Calculates the smallest integral power of two that is not smaller
/// than x. If that value is not representable in T, the behavior is undefined.
/// Call to this function is permitted in constant evaluation only if the
/// undefined behavior does not occur.
///
/// \details This overload only participates in overload resolution if T is an
/// unsigned integer type (that is, unsigned char, unsigned short, unsigned int,
/// unsigned long, unsigned long long, or an extended unsigned integer type).
///
/// \returns The smallest integral power of two that is not smaller than x.
/// \module Numeric
template <typename T>
[[nodiscard]] constexpr auto bit_ceil(T x) noexcept
    -> enable_if_t<detail::bit_unsigned_int_v<T>, T>
{
    if (x <= 1U) { return T(1); }

    if constexpr (is_same_v<T, decltype(+x)>) {
        //
        return T(1) << bit_width(T(x - 1));
    } else {
        // for types subject to integral promotion
        auto offset
            = numeric_limits<unsigned>::digits - numeric_limits<T>::digits;
        return T(1U << (bit_width(T(x - 1)) + offset) >> offset);
    }
}

/// \brief If x is not zero, calculates the largest integral power of two that
/// is not greater than x. If x is zero, returns zero.
///
/// \details This overload only participates in overload resolution if T is an
/// unsigned integer type (that is, unsigned char, unsigned short, unsigned int,
/// unsigned long, unsigned long long, or an extended unsigned integer type).
///
/// \returns Zero if x is zero; otherwise, the largest integral power of two
/// that is not greater than x.
/// \module Numeric
template <typename T>
[[nodiscard]] constexpr auto bit_floor(T x) noexcept
    -> enable_if_t<detail::bit_unsigned_int_v<T>, T>
{
    if (x != 0) { return T { 1 } << (bit_width(x) - 1); }
    return 0;
}
} // namespace etl

#endif // TETL_BIT_HPP