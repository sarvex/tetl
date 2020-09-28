/*
Copyright (c) 2019-2020, Tobias Hienzsch
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
DAMAGE.
*/

#include "etl/algorithm.hpp"
#include "etl/array.hpp"
#include "etl/iterator.hpp"
#include "etl/numeric.hpp"
#include "etl/static_vector.hpp"
#include "etl/string.hpp"

#include "catch2/catch.hpp"

TEMPLATE_TEST_CASE("algorithm: iter_swap", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    auto data = etl::array {TestType(1), TestType(2)};
    CHECK(data[0] == TestType(1));
    CHECK(data[1] == TestType(2));
    etl::iter_swap(begin(data), begin(data) + 1);
    CHECK(data[0] == TestType(2));
    CHECK(data[1] == TestType(1));
}

TEMPLATE_TEST_CASE("algorithm: for_each", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    etl::static_vector<TestType, 16> vec;
    vec.push_back(TestType(1));
    vec.push_back(TestType(2));
    vec.push_back(TestType(3));
    vec.push_back(TestType(4));

    // Check how often for_each calls the unary function
    int counter {};
    auto increment_counter = [&counter](auto& /*unused*/) { counter += 1; };

    // for_each
    etl::for_each(vec.begin(), vec.end(), increment_counter);
    REQUIRE(counter == 4);

    // for_each_n
    counter = 0;
    etl::for_each_n(vec.begin(), 2, increment_counter);
    REQUIRE(counter == 2);
}

TEMPLATE_TEST_CASE("algorithm: transform", "[algorithm]", etl::uint8_t, etl::uint16_t,
                   etl::int16_t, etl::uint32_t, etl::int32_t, etl::uint64_t, etl::int64_t,
                   float, double, long double)
{
    etl::array<TestType, 4> a;
    a.fill(2);
    etl::transform(begin(a), end(a), begin(a), [](auto const& val) { return val * 2; });
    REQUIRE(etl::all_of(begin(a), end(a), [](auto const& val) { return val == 4; }));

    etl::small_string str("hello");
    etl::static_vector<TestType, 8> vec;
    etl::transform(begin(str), end(str), etl::back_inserter(vec),
                   [](auto c) -> TestType { return static_cast<TestType>(c); });

    REQUIRE(vec[0] == static_cast<TestType>('h'));
    REQUIRE(vec[1] == static_cast<TestType>('e'));
    REQUIRE(vec[2] == static_cast<TestType>('l'));
    REQUIRE(vec[3] == static_cast<TestType>('l'));
    REQUIRE(vec[4] == static_cast<TestType>('o'));

    etl::transform(cbegin(vec), cend(vec), cbegin(vec), begin(vec), etl::plus<> {});

    REQUIRE(vec[0] == static_cast<TestType>('h') * 2);
    REQUIRE(vec[1] == static_cast<TestType>('e') * 2);
    REQUIRE(vec[2] == static_cast<TestType>('l') * 2);
    REQUIRE(vec[3] == static_cast<TestType>('l') * 2);
    REQUIRE(vec[4] == static_cast<TestType>('o') * 2);
}

TEMPLATE_TEST_CASE("algorithm: generate", "[algorithm]", etl::uint8_t, etl::uint16_t,
                   etl::int16_t, etl::uint32_t, etl::int32_t, etl::uint64_t, etl::int64_t)
{
    auto data = etl::array<TestType, 4> {};
    etl::generate(begin(data), end(data), [n = TestType {0}]() mutable { return n++; });
    REQUIRE(data[0] == 0);
    REQUIRE(data[1] == 1);
    REQUIRE(data[2] == 2);
    REQUIRE(data[3] == 3);
}

TEMPLATE_TEST_CASE("algorithm: generate_n", "[algorithm]", etl::uint8_t, etl::uint16_t,
                   etl::int16_t, etl::uint32_t, etl::int32_t, etl::uint64_t, etl::int64_t)
{
    auto data = etl::static_vector<TestType, 4> {};
    auto rng  = []() { return TestType {42}; };
    etl::generate_n(etl::back_inserter(data), 4, rng);

    REQUIRE(data[0] == TestType {42});
    REQUIRE(data[1] == TestType {42});
    REQUIRE(data[2] == TestType {42});
    REQUIRE(data[3] == TestType {42});
}

TEMPLATE_TEST_CASE("algorithm: count", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double)
{
    auto data = etl::array<TestType, 4> {};
    etl::iota(begin(data), end(data), TestType {0});
    REQUIRE(etl::count(begin(data), end(data), TestType {0}) == 1);
    REQUIRE(etl::count(begin(data), end(data), TestType {1}) == 1);
    REQUIRE(etl::count(begin(data), end(data), TestType {2}) == 1);
    REQUIRE(etl::count(begin(data), end(data), TestType {3}) == 1);
    REQUIRE(etl::count(begin(data), end(data), TestType {4}) == 0);
}

TEMPLATE_TEST_CASE("algorithm: count_if", "[algorithm]", etl::uint8_t, etl::uint16_t,
                   etl::int16_t, etl::uint32_t, etl::int32_t, etl::uint64_t, etl::int64_t,
                   float, double)
{
    auto data = etl::array<TestType, 4> {};
    etl::iota(begin(data), end(data), TestType {0});

    auto p1 = [](auto const& val) { return val < TestType {2}; };
    auto p2 = [](auto const& val) -> bool { return static_cast<int>(val) % 2; };

    REQUIRE(etl::count_if(begin(data), end(data), p1) == 2);
    REQUIRE(etl::count_if(begin(data), end(data), p2) == 2);
}

TEMPLATE_TEST_CASE("algorithm: find", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    etl::static_vector<TestType, 16> vec;
    vec.push_back(TestType(1));
    vec.push_back(TestType(2));
    vec.push_back(TestType(3));
    vec.push_back(TestType(4));

    const auto* result1 = etl::find(vec.cbegin(), vec.cend(), TestType(3));
    REQUIRE_FALSE(result1 == vec.cend());

    auto* result2 = etl::find(vec.begin(), vec.end(), TestType(5));
    REQUIRE(result2 == vec.end());
}

TEMPLATE_TEST_CASE("algorithm: find_if", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t)
{
    etl::static_vector<TestType, 16> vec;
    vec.push_back(TestType(1));
    vec.push_back(TestType(2));
    vec.push_back(TestType(3));
    vec.push_back(TestType(4));

    // find_if
    auto* result3 = etl::find_if(
        vec.begin(), vec.end(), [](auto& x) -> bool { return static_cast<bool>(x % 2); });
    REQUIRE_FALSE(result3 == vec.end());

    auto* result4 = etl::find_if(vec.begin(), vec.end(), [](auto& x) -> bool {
        return static_cast<bool>(x == 100);
    });
    REQUIRE(result4 == vec.end());
}

TEMPLATE_TEST_CASE("algorithm: find_if_not", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t)
{
    etl::static_vector<TestType, 16> vec;
    vec.push_back(TestType(1));
    vec.push_back(TestType(2));
    vec.push_back(TestType(3));
    vec.push_back(TestType(4));
    // find_if_not
    auto* result5 = etl::find_if_not(
        vec.begin(), vec.end(), [](auto& x) -> bool { return static_cast<bool>(x % 2); });
    REQUIRE_FALSE(result5 == vec.end());

    auto* result6 = etl::find_if_not(vec.begin(), vec.end(), [](auto& x) -> bool {
        return static_cast<bool>(x == 100);
    });
    REQUIRE_FALSE(result6 == vec.end());

    auto* result7 = etl::find_if_not(vec.begin(), vec.end(), [](auto& x) -> bool {
        return static_cast<bool>(x != 100);
    });
    REQUIRE(result7 == vec.end());
}

TEMPLATE_TEST_CASE("algorithm: max", "[algorithm]", etl::int8_t, etl::int16_t,
                   etl::int32_t, etl::int64_t, float, double, long double)
{
    REQUIRE(etl::max<TestType>(1, 5) == 5);
    REQUIRE(etl::max<TestType>(-10, 5) == 5);
    REQUIRE(etl::max<TestType>(-10, -20) == -10);

    auto cmp = [](auto x, auto y) { return etl::abs(x) < etl::abs(y) ? y : x; };
    REQUIRE(etl::max<TestType>(-10, -20, cmp) == -20);
    REQUIRE(etl::max<TestType>(10, -20, cmp) == -20);
}

TEMPLATE_TEST_CASE("algorithm: max_element", "[algorithm]", etl::int8_t, etl::int16_t,
                   etl::int32_t, etl::int64_t, float, double, long double)
{
    etl::static_vector<TestType, 16> vec;
    vec.push_back(TestType(1));
    vec.push_back(TestType(2));
    vec.push_back(TestType(3));
    vec.push_back(TestType(4));
    vec.push_back(TestType(-5));

    auto const cmp = [](auto a, auto b) -> bool { return etl::abs(a) < etl::abs(b); };
    REQUIRE(*etl::max_element(vec.begin(), vec.end()) == TestType(4));
    REQUIRE(*etl::max_element(vec.begin(), vec.end(), cmp) == TestType(-5));
}

TEMPLATE_TEST_CASE("algorithm: min", "[algorithm]", etl::int8_t, etl::int16_t,
                   etl::int32_t, etl::int64_t, float, double, long double)
{
    REQUIRE(etl::min<TestType>(1, 5) == 1);
    REQUIRE(etl::min<TestType>(-10, 5) == -10);
    REQUIRE(etl::min<TestType>(-10, -20) == -20);

    auto cmp = [](auto x, auto y) { return etl::abs(x) < etl::abs(y); };
    REQUIRE(etl::min<TestType>(-10, -20, cmp) == -10);
    REQUIRE(etl::min<TestType>(10, -20, cmp) == 10);
}

TEMPLATE_TEST_CASE("algorithm: min_element", "[algorithm]", etl::int8_t, etl::int16_t,
                   etl::int32_t, etl::int64_t, float, double, long double)
{
    etl::static_vector<TestType, 16> vec;
    vec.push_back(TestType {1});
    vec.push_back(TestType {2});
    vec.push_back(TestType {3});
    vec.push_back(TestType {4});
    vec.push_back(TestType {-5});

    auto const cmp = [](auto a, auto b) -> bool { return etl::abs(a) < etl::abs(b); };
    REQUIRE(*etl::min_element(vec.begin(), vec.end()) == TestType {-5});
    REQUIRE(*etl::min_element(vec.begin(), vec.end(), cmp) == TestType {1});
}

TEMPLATE_TEST_CASE("algorithm: clamp", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    REQUIRE(etl::clamp<TestType>(55, 0, 20) == TestType {20});
    REQUIRE(etl::clamp<TestType>(55, 0, 100) == TestType {55});
    STATIC_REQUIRE(etl::clamp<TestType>(55, 0, 20) == TestType {20});
    STATIC_REQUIRE(etl::clamp<TestType>(55, 0, 100) == TestType {55});
}

TEMPLATE_TEST_CASE("algorithm: all_of", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    etl::static_vector<TestType, 16> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    auto const p1 = [](auto a) { return etl::abs(a) > 0; };
    REQUIRE(etl::all_of(vec.begin(), vec.end(), p1));

    auto const p2 = [](auto a) { return etl::abs(a) > 10; };
    REQUIRE_FALSE(etl::all_of(vec.begin(), vec.end(), p2));
}

TEMPLATE_TEST_CASE("algorithm: any_of", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    etl::static_vector<TestType, 16> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    auto const p1 = [](auto a) { return etl::abs(a) > 0; };
    REQUIRE(etl::any_of(vec.begin(), vec.end(), p1));
    auto const p2 = [](auto a) { return etl::abs(a) > 10; };
    REQUIRE_FALSE(etl::any_of(vec.begin(), vec.end(), p2));
}

TEMPLATE_TEST_CASE("algorithm: none_of", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    etl::static_vector<TestType, 16> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    auto const p1 = [](auto a) { return etl::abs(a) > 10; };
    REQUIRE(etl::none_of(vec.begin(), vec.end(), p1));

    auto const p2 = [](auto a) { return a < 10; };
    REQUIRE_FALSE(etl::none_of(vec.begin(), vec.end(), p2));
}

TEMPLATE_TEST_CASE("algorithm: rotate", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    etl::array<TestType, 16> arr;
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;

    REQUIRE(arr[0] == 1);
    etl::rotate(begin(arr), begin(arr) + 1, end(arr));
    REQUIRE(arr[0] == 2);
}

TEMPLATE_TEST_CASE("algorithm: reverse", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    SECTION("built-in")
    {
        auto data = etl::array<TestType, 4> {};
        etl::iota(begin(data), end(data), TestType {0});
        etl::reverse(begin(data), end(data));

        CHECK(data[0] == 3);
        CHECK(data[1] == 2);
        CHECK(data[2] == 1);
        CHECK(data[3] == 0);
    }

    SECTION("struct")
    {
        struct S
        {
            TestType data;
        };

        auto arr = etl::array {
            S {TestType(1)},
            S {TestType(2)},
        };

        etl::reverse(begin(arr), end(arr));

        CHECK(arr[0].data == TestType(2));
        CHECK(arr[1].data == TestType(1));
    }
}

TEMPLATE_TEST_CASE("algorithm: reverse_copy", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    SECTION("built-in")
    {
        auto source = etl::array<TestType, 4> {};
        etl::iota(begin(source), end(source), TestType {0});

        auto destination = etl::array<TestType, 4> {};
        etl::reverse_copy(begin(source), end(source), begin(destination));

        CHECK(destination[0] == 3);
        CHECK(destination[1] == 2);
        CHECK(destination[2] == 1);
        CHECK(destination[3] == 0);
    }

    SECTION("struct")
    {
        struct S
        {
            TestType data;
        };

        auto source = etl::array {
            S {TestType(1)},
            S {TestType(2)},
        };

        decltype(source) destination {};
        etl::reverse_copy(begin(source), end(source), begin(destination));

        CHECK(destination[0].data == TestType(2));
        CHECK(destination[1].data == TestType(1));
    }
}

TEMPLATE_TEST_CASE("algorithm: unique", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    using T = TestType;

    SECTION("equal_to")
    {
        auto data = etl::array {T(1), T(1), T(1), T(2), T(3)};
        etl::unique(begin(data), end(data));
        CHECK(data[0] == T(1));
        CHECK(data[1] == T(2));
        CHECK(data[2] == T(3));
    }

    SECTION("not_equal_to")
    {
        auto data = etl::array {T(1), T(1), T(1), T(2), T(3)};
        etl::unique(begin(data), end(data), etl::not_equal_to<> {});
        CHECK(data[0] == T(1));
        CHECK(data[1] == T(1));
        CHECK(data[2] == T(1));
    }
}

TEMPLATE_TEST_CASE("algorithm: unique_copy", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    using T = TestType;

    SECTION("equal_to")
    {
        auto source = etl::array {T(1), T(1), T(1), T(2), T(3)};
        decltype(source) dest {};

        etl::unique_copy(begin(source), end(source), begin(dest));
        CHECK(dest[0] == T(1));
        CHECK(dest[1] == T(2));
        CHECK(dest[2] == T(3));
    }

    SECTION("not_equal_to")
    {
        auto source = etl::array {T(1), T(1), T(1), T(2), T(3)};
        decltype(source) dest {};

        etl::unique_copy(begin(source), end(source), begin(dest), etl::not_equal_to<> {});
        CHECK(dest[0] == T(1));
        CHECK(dest[1] == T(1));
        CHECK(dest[2] == T(1));
    }
}

TEMPLATE_TEST_CASE("algorithm: partition", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    etl::array<TestType, 7> arr;
    arr[0] = 11;
    arr[1] = 1;
    arr[2] = 12;
    arr[3] = 13;
    arr[4] = 2;
    arr[5] = 3;
    arr[6] = 4;

    etl::partition(begin(arr), end(arr), [](auto n) { return n < 10; });
    REQUIRE(arr[0] == 1);
    REQUIRE(arr[1] == 2);
    REQUIRE(arr[2] == 3);
    REQUIRE(arr[3] == 4);
}

TEMPLATE_TEST_CASE("algorithm: stable_partition", "[algorithm]", etl::uint8_t,
                   etl::int8_t, etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    etl::array<TestType, 7> arr;
    arr[0] = 11;
    arr[1] = 1;
    arr[2] = 12;
    arr[3] = 13;
    arr[4] = 2;
    arr[5] = 3;
    arr[6] = 4;

    etl::stable_partition(begin(arr), end(arr), [](auto n) { return n < 10; });
    REQUIRE(arr[0] == 1);
    REQUIRE(arr[1] == 2);
    REQUIRE(arr[2] == 3);
    REQUIRE(arr[3] == 4);
    REQUIRE(arr[4] == 11);
    REQUIRE(arr[5] == 12);
    REQUIRE(arr[6] == 13);
}

TEMPLATE_TEST_CASE("algorithm: copy", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    using vector_t = etl::static_vector<TestType, 4>;

    auto source = etl::array<TestType, 4> {};
    source[0]   = TestType {1};
    source[1]   = TestType {2};
    source[2]   = TestType {3};
    source[3]   = TestType {4};

    SECTION("copy to c array")
    {
        TestType dest[4] = {};
        etl::copy(begin(source), end(source), etl::begin(dest));
        REQUIRE(dest[0] == TestType {1});
        REQUIRE(dest[1] == TestType {2});
        REQUIRE(dest[2] == TestType {3});
        REQUIRE(dest[3] == TestType {4});
    }

    SECTION("copy to vector")
    {
        auto dest = vector_t {};
        REQUIRE(dest.size() == 0);
        etl::copy(begin(source), end(source), etl::back_inserter(dest));
        REQUIRE(dest.size() == 4);
        REQUIRE(dest[0] == TestType {1});
        REQUIRE(dest[1] == TestType {2});
        REQUIRE(dest[2] == TestType {3});
        REQUIRE(dest[3] == TestType {4});
    }
}

TEMPLATE_TEST_CASE("algorithm: copy_if", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    using vector_t = etl::static_vector<TestType, 4>;

    auto source = etl::array<TestType, 4> {};
    source[0]   = TestType {1};
    source[1]   = TestType {7};
    source[2]   = TestType {3};
    source[3]   = TestType {9};

    auto predicate = [](auto const& val) { return static_cast<int>(val) >= 5; };

    SECTION("copy_if to c array")
    {
        TestType dest[4] = {};
        auto* res = etl::copy_if(begin(source), end(source), etl::begin(dest), predicate);
        REQUIRE(res == &dest[2]);
        REQUIRE(dest[0] == TestType {7});
        REQUIRE(dest[1] == TestType {9});
        REQUIRE(dest[2] == TestType {0});
        REQUIRE(dest[3] == TestType {0});
    }

    SECTION("copy_if to vector")
    {
        auto dest = vector_t {};
        REQUIRE(dest.size() == 0);
        etl::copy_if(begin(source), end(source), etl::back_inserter(dest), predicate);
        REQUIRE(dest.size() == 2);
        REQUIRE(dest[0] == TestType {7});
        REQUIRE(dest[1] == TestType {9});
    }
}

TEMPLATE_TEST_CASE("algorithm: copy_n", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    using vector_t = etl::static_vector<TestType, 4>;

    auto source = etl::array<TestType, 4> {};
    source[0]   = TestType {1};
    source[1]   = TestType {2};
    source[2]   = TestType {3};
    source[3]   = TestType {4};

    SECTION("copy_n to c array")
    {
        SECTION("all elements")
        {
            TestType dest[4] = {};
            etl::copy_n(begin(source), 4, etl::begin(dest));
            REQUIRE(dest[0] == TestType {1});
            REQUIRE(dest[1] == TestType {2});
            REQUIRE(dest[2] == TestType {3});
            REQUIRE(dest[3] == TestType {4});
        }

        SECTION("2 elements")
        {
            TestType dest[3] = {};
            etl::copy_n(begin(source), 2, etl::begin(dest));
            REQUIRE(dest[0] == TestType {1});
            REQUIRE(dest[1] == TestType {2});
            REQUIRE(dest[2] == TestType {0});
        }
    }

    SECTION("copy_n to vector")
    {
        auto dest = vector_t {};
        REQUIRE(dest.size() == 0);
        etl::copy_n(begin(source), source.size(), etl::back_inserter(dest));
        REQUIRE(dest.size() == 4);
        REQUIRE(dest[0] == TestType {1});
        REQUIRE(dest[1] == TestType {2});
        REQUIRE(dest[2] == TestType {3});
        REQUIRE(dest[3] == TestType {4});
    }
}

TEMPLATE_TEST_CASE("algorithm: copy_backward", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    auto source = etl::array<TestType, 4> {};
    source[0]   = TestType {1};
    source[1]   = TestType {2};
    source[2]   = TestType {3};
    source[3]   = TestType {4};

    SECTION("copy_backward to c array")
    {
        TestType dest[4] = {};
        etl::copy_backward(begin(source), end(source), etl::end(dest));
        REQUIRE(dest[0] == TestType {1});
        REQUIRE(dest[1] == TestType {2});
        REQUIRE(dest[2] == TestType {3});
        REQUIRE(dest[3] == TestType {4});
    }
}

TEMPLATE_TEST_CASE("algorithm: equal", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    auto lhs = etl::array<TestType, 2> {TestType {0}, TestType {1}};
    auto rhs = etl::array<TestType, 2> {TestType {0}, TestType {1}};
    auto cmp = etl::not_equal_to<> {};

    CHECK(etl::equal(begin(lhs), end(lhs), begin(rhs)));
    CHECK_FALSE(etl::equal(begin(lhs), end(lhs), begin(rhs), cmp));

    CHECK(etl::equal(begin(lhs), end(lhs), begin(rhs), end(rhs)));
    CHECK_FALSE(etl::equal(begin(lhs), end(lhs), begin(rhs), end(rhs), cmp));
}

TEMPLATE_TEST_CASE("algorithm: fill", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    SECTION("c array")
    {
        TestType source[4] = {};
        etl::fill(etl::begin(source), etl::end(source), TestType {42});

        auto const all_42
            = etl::all_of(etl::begin(source), etl::end(source),
                          [](auto const& val) { return val == TestType {42}; });

        REQUIRE(all_42);
    }

    SECTION("etl::array")
    {
        auto source = etl::array<TestType, 4> {};
        etl::fill(begin(source), end(source), TestType {42});

        auto const all_42 = etl::all_of(begin(source), end(source), [](auto const& val) {
            return val == TestType {42};
        });

        REQUIRE(all_42);
    }
}

TEMPLATE_TEST_CASE("algorithm: sort", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    SECTION("already sorted")
    {
        auto source = etl::array<TestType, 4> {};
        source[0]   = TestType {1};
        source[1]   = TestType {2};
        source[2]   = TestType {3};
        source[3]   = TestType {4};

        etl::sort(begin(source), end(source), etl::less<TestType> {});
        REQUIRE(source[0] == TestType {1});
        REQUIRE(source[1] == TestType {2});
        REQUIRE(source[2] == TestType {3});
        REQUIRE(source[3] == TestType {4});
    }

    SECTION("reversed")
    {
        auto source = etl::array<TestType, 4> {};
        source[0]   = TestType {4};
        source[1]   = TestType {3};
        source[2]   = TestType {2};
        source[3]   = TestType {1};

        etl::sort(begin(source), end(source));
        REQUIRE(source[0] == TestType {1});
        REQUIRE(source[1] == TestType {2});
        REQUIRE(source[2] == TestType {3});
        REQUIRE(source[3] == TestType {4});
    }

    SECTION("custom compare")
    {
        auto source = etl::array<TestType, 4> {};
        source[0]   = TestType {1};
        source[1]   = TestType {1};
        source[2]   = TestType {56};
        source[3]   = TestType {42};

        etl::sort(begin(source), end(source),
                  [](auto const& lhs, auto const& rhs) { return lhs > rhs; });
        REQUIRE(source[0] == TestType {56});
        REQUIRE(source[1] == TestType {42});
        REQUIRE(source[2] == TestType {1});
        REQUIRE(source[3] == TestType {1});
    }
}

TEMPLATE_TEST_CASE("algorithm: is_sorted", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    SECTION("already is_sorteded")
    {
        auto source = etl::array<TestType, 4> {
            TestType {1},
            TestType {2},
            TestType {3},
            TestType {4},
        };

        CHECK(etl::is_sorted(begin(source), end(source), etl::less<TestType> {}));
    }

    SECTION("reversed")
    {
        auto source = etl::array<TestType, 4> {
            TestType {4},
            TestType {3},
            TestType {2},
            TestType {1},
        };

        CHECK(etl::is_sorted(begin(source), end(source), etl::greater<> {}));
        CHECK_FALSE(etl::is_sorted(begin(source), end(source)));
    }

    SECTION("custom compare")
    {
        auto source = etl::array<TestType, 4> {
            TestType {1},
            TestType {1},
            TestType {56},
            TestType {42},
        };

        CHECK_FALSE(etl::is_sorted(begin(source), end(source), etl::greater<> {}));
    }
}

TEMPLATE_TEST_CASE("algorithm: includes", "[algorithm]", etl::uint8_t, etl::int8_t,
                   etl::uint16_t, etl::int16_t, etl::uint32_t, etl::int32_t,
                   etl::uint64_t, etl::int64_t, float, double, long double)
{
    SECTION("char")
    {
        auto const v1 = etl::array {'a', 'b', 'c', 'f', 'h', 'x'};
        auto const v2 = etl::array {'a', 'b', 'c'};
        auto const v3 = etl::array {'a', 'c'};
        auto const v4 = etl::array {'a', 'a', 'b'};
        auto const v5 = etl::array {'g'};
        auto const v6 = etl::array {'a', 'c', 'g'};
        auto const v7 = etl::array {'A', 'B', 'C'};

        auto no_case = [](char a, char b) { return std::tolower(a) < std::tolower(b); };

        CHECK(etl::includes(v1.begin(), v1.end(), v2.begin(), v2.end()));
        CHECK(etl::includes(v1.begin(), v1.end(), v3.begin(), v3.end()));
        CHECK(etl::includes(v1.begin(), v1.end(), v7.begin(), v7.end(), no_case));

        CHECK_FALSE(etl::includes(v1.begin(), v1.end(), v4.begin(), v4.end()));
        CHECK_FALSE(etl::includes(v1.begin(), v1.end(), v5.begin(), v5.end()));
        CHECK_FALSE(etl::includes(v1.begin(), v1.end(), v6.begin(), v6.end()));
    }

    SECTION("TestType")
    {
        using T       = TestType;
        auto const v1 = etl::array {T(1), T(2), T(3), T(6), T(8), T(24)};
        auto const v2 = etl::array {T(1), T(2), T(3)};
        auto const v3 = etl::array {T(1), T(3)};
        auto const v4 = etl::array {T(1), T(1), T(2)};
        auto const v5 = etl::array {T(7)};
        auto const v6 = etl::array {T(1), T(3), T(7)};

        CHECK(etl::includes(v1.begin(), v1.end(), v2.begin(), v2.end()));
        CHECK(etl::includes(v1.begin(), v1.end(), v3.begin(), v3.end()));

        CHECK_FALSE(etl::includes(v1.begin(), v1.end(), v4.begin(), v4.end()));
        CHECK_FALSE(etl::includes(v1.begin(), v1.end(), v5.begin(), v5.end()));
        CHECK_FALSE(etl::includes(v1.begin(), v1.end(), v6.begin(), v6.end()));
    }
}
