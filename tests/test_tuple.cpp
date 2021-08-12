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
#include "etl/tuple.hpp"

#include "etl/cstdint.hpp"     // for int16_t, int32_t, int64_t, int8_t
#include "etl/type_traits.hpp" // for is_same_v
#include "etl/warning.hpp"     // for ignore_unused

#include "catch2/catch_template_test_macros.hpp"

TEMPLATE_TEST_CASE("tuple: constructor", "[tuple]", bool, etl::uint8_t,
    etl::int8_t, etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
    etl::uint64_t, etl::int64_t, float, double, long double)

{
    etl::tuple<TestType, float> t1 { TestType { 1 }, 2.0F };
    etl::ignore_unused(t1);
}

TEMPLATE_TEST_CASE("tuple: get", "[tuple]", bool, etl::uint8_t, etl::int8_t,
    etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t, etl::uint64_t,
    etl::int64_t, float, double, long double)
{
    auto t1 = etl::tuple<TestType, float> { TestType { 1 }, 2.0F };
    CHECK(etl::get<0>(t1) == TestType { 1 });
    CHECK(etl::get<1>(t1) == 2.0F);
}

TEMPLATE_TEST_CASE("tuple: tuple_element<tuple>", "[tuple]", bool, etl::uint8_t,
    etl::int8_t, etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
    etl::uint64_t, etl::int64_t, float, double, long double)
{
    using T = TestType;
    using etl::is_same_v;
    using etl::tuple;
    using etl::tuple_element_t;

    STATIC_REQUIRE(is_same_v<tuple_element_t<0, tuple<T, float>>, T>);
    STATIC_REQUIRE(is_same_v<tuple_element_t<1, tuple<T, float>>, float>);

    STATIC_REQUIRE(is_same_v<tuple_element_t<0, tuple<T, int>>, T>);
    STATIC_REQUIRE(is_same_v<tuple_element_t<1, tuple<T, int>>, int>);

    STATIC_REQUIRE(is_same_v<tuple_element_t<0, tuple<double, T>>, double>);
    STATIC_REQUIRE(is_same_v<tuple_element_t<1, tuple<double, T>>, T>);

    STATIC_REQUIRE(is_same_v<tuple_element_t<0, tuple<int, T, float>>, int>);
    STATIC_REQUIRE(is_same_v<tuple_element_t<1, tuple<int, T, float>>, T>);
    STATIC_REQUIRE(is_same_v<tuple_element_t<2, tuple<int, T, float>>, float>);
}

TEMPLATE_TEST_CASE("tuple: tuple_size<tuple>", "[tuple]", bool, etl::uint8_t,
    etl::int8_t, etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
    etl::uint64_t, etl::int64_t, float, double, long double)
{
    using T = TestType;

    STATIC_REQUIRE(etl::tuple_size_v<etl::tuple<T>> == 1);
    STATIC_REQUIRE(etl::tuple_size_v<etl::tuple<T, float>> == 2);
    STATIC_REQUIRE(etl::tuple_size_v<etl::tuple<T, float, char>> == 3);
    STATIC_REQUIRE(etl::tuple_size_v<etl::tuple<T, float, char, int>> == 4);
}

TEMPLATE_TEST_CASE("tuple: make_tuple", "[tuple]", bool, etl::uint8_t,
    etl::int8_t, etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
    etl::uint64_t, etl::int64_t, float, double, long double)
{
    using T = TestType;
    using etl::is_same_v;
    using etl::tuple;

    auto t1 = etl::make_tuple(T { 1 }, 'a', true);
    REQUIRE(etl::get<0>(t1) == T { 1 });
    REQUIRE(etl::get<1>(t1) == 'a');
    REQUIRE(etl::get<2>(t1) == true);
}
