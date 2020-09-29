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

#include "catch2/catch.hpp"

#include "etl/algorithm.hpp"    // for for_each
#include "etl/definitions.hpp"  // for size_t
#include "etl/string.hpp"       // for static_string

TEST_CASE("string/char_traits: <char>::length", "[string]")
{
    STATIC_REQUIRE(etl::char_traits<char>::length("") == 0);
    STATIC_REQUIRE(etl::char_traits<char>::length("a") == 1);
    STATIC_REQUIRE(etl::char_traits<char>::length("to") == 2);
    STATIC_REQUIRE(etl::char_traits<char>::length("xxxxxxxxxx") == 10);
}

TEST_CASE("string/char_traits: <char>::eq", "[string]")
{
    STATIC_REQUIRE(etl::char_traits<char>::eq('a', 'a') == true);
    STATIC_REQUIRE(etl::char_traits<char>::eq('a', 'b') == false);
    STATIC_REQUIRE(etl::char_traits<char>::eq('b', 'a') == false);
}

TEST_CASE("string/char_traits: <char>::lt", "[string]")
{
    STATIC_REQUIRE(etl::char_traits<char>::lt('a', 'a') == false);
    STATIC_REQUIRE(etl::char_traits<char>::lt('a', 'b') == true);
    STATIC_REQUIRE(etl::char_traits<char>::lt('b', 'a') == false);
}

TEST_CASE("string/char_traits: <char>::assign(char,char)", "[string]")
{
    auto ch = [](char const& b) {
        auto a = 'a';
        etl::char_traits<char>::assign(a, b);
        return a;
    };

    STATIC_REQUIRE(ch('b') == 'b');
}

TEMPLATE_TEST_CASE("string: ctor - default", "[string]", etl::static_string<12>,
                   etl::static_string<32>, etl::static_string<12> const,
                   etl::static_string<32> const)
{
    TestType str {};

    REQUIRE(str.empty() == true);
    REQUIRE(str.capacity() == str.max_size());
    REQUIRE(str.size() == etl::size_t(0));
    REQUIRE(str.length() == etl::size_t(0));
}

TEMPLATE_TEST_CASE("string: ctor - char const*", "[string]", etl::static_string<12>,
                   etl::static_string<32>, etl::static_string<12> const,
                   etl::static_string<32> const)
{
    TestType str {"abc"};

    REQUIRE(str.empty() == false);
    REQUIRE(str.capacity() == str.max_size());
    REQUIRE(str.size() == etl::size_t(3));
    REQUIRE(str.length() == etl::size_t(3));
    REQUIRE(str[0] == 'a');
    REQUIRE(str[1] == 'b');
    REQUIRE(str[2] == 'c');
    REQUIRE(str[3] == char(0));
}

TEMPLATE_TEST_CASE("string: ctor - char const*, size_t", "[string]",
                   etl::static_string<12>, etl::static_string<32>,
                   etl::static_string<12> const, etl::static_string<32> const)
{
    TestType str {"abc", 3};

    REQUIRE(str.empty() == false);
    REQUIRE(str.capacity() == str.max_size());
    REQUIRE(str.size() == etl::size_t(3));
    REQUIRE(str.length() == etl::size_t(3));
    REQUIRE(str[0] == 'a');
    REQUIRE(str[1] == 'b');
    REQUIRE(str[2] == 'c');
    REQUIRE(str[3] == char(0));
}

TEMPLATE_TEST_CASE("string: constexpr", "[string]", etl::static_string<8>,
                   etl::static_string<12>, etl::static_string<32>)
{
    constexpr TestType str1 {};

    STATIC_REQUIRE(str1.empty() == true);
    STATIC_REQUIRE(str1.capacity() == str1.max_size());
    STATIC_REQUIRE(str1.size() == 0);
    STATIC_REQUIRE(str1.length() == 0);

    constexpr auto str2 = []() {
        TestType str {};
        // APPEND 4 CHARACTERS
        const char* cptr = "C-string";
        str.append(cptr, 4);
        return str;
    }();

    STATIC_REQUIRE(str2.empty() == false);
    STATIC_REQUIRE(str2.capacity() == str1.max_size());
    STATIC_REQUIRE(str2.size() == 4);
    STATIC_REQUIRE(str2.length() == 4);
    STATIC_REQUIRE(str2[0] == 'C');
    STATIC_REQUIRE(str2[1] == '-');
    STATIC_REQUIRE(str2[2] == 's');
    STATIC_REQUIRE(str2[3] == 't');
    STATIC_REQUIRE(str2[4] == 0);
    STATIC_REQUIRE(str2.at(4) == 0);
}

TEMPLATE_TEST_CASE("string: at", "[string]", etl::static_string<12>,
                   etl::static_string<32>, etl::static_string<12> const,
                   etl::static_string<32> const)
{
    TestType str {"abc"};
    REQUIRE(str.at(0) == 'a');
    REQUIRE(str.at(1) == 'b');
    REQUIRE(str.at(2) == 'c');
    REQUIRE(str.at(3) == 0);
}

TEMPLATE_TEST_CASE("string: operator[]", "[string]", etl::static_string<12>,
                   etl::static_string<32>, etl::static_string<12> const,
                   etl::static_string<32> const)
{
    TestType str {"abc"};
    REQUIRE(str[0] == 'a');
    REQUIRE(str[1] == 'b');
    REQUIRE(str[2] == 'c');
    REQUIRE(str[3] == 0);
}

TEMPLATE_TEST_CASE("string: begin/end", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    TestType str {};

    etl::for_each(str.begin(), str.end(), [](auto& c) { REQUIRE(c == char(0)); });
}

TEMPLATE_TEST_CASE("string: cbegin/cend", "[string]", etl::static_string<12>,
                   etl::static_string<32>, etl::static_string<12> const,
                   etl::static_string<32> const)
{
    TestType str {};

    etl::for_each(str.cbegin(), str.cend(), [](auto const& c) { REQUIRE(c == char(0)); });
}

TEMPLATE_TEST_CASE("string: append(count, CharType)", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    auto str = TestType {};
    str.append(4, 'a');

    REQUIRE(str.size() == etl::size_t(4));
    REQUIRE(str.length() == etl::size_t(4));
    REQUIRE(str[0] == 'a');
    REQUIRE(str[1] == 'a');
    REQUIRE(str[2] == 'a');
    REQUIRE(str[3] == 'a');
    REQUIRE(str[4] == char(0));
}

TEMPLATE_TEST_CASE("string: append(const_pointer, count)", "[string]",
                   etl::static_string<8>, etl::static_string<12>, etl::static_string<32>)
{
    TestType str {};

    // APPEND 4 CHARACTERS
    const char* cptr = "C-string";
    str.append(cptr, 4);

    REQUIRE(str.empty() == false);
    REQUIRE(str.capacity() == str.max_size());
    REQUIRE(str.size() == etl::size_t(4));
    REQUIRE(str.length() == etl::size_t(4));
    REQUIRE(str[0] == 'C');
    REQUIRE(str[1] == '-');
    REQUIRE(str[2] == 's');
    REQUIRE(str[3] == 't');
    REQUIRE(str[4] == char(0));
}

TEMPLATE_TEST_CASE("string: append(const_pointer)", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    TestType str {};
    const char* cptr = "C-string";
    str.append(cptr);

    REQUIRE(str.size() == etl::strlen(cptr));
    REQUIRE(str.length() == etl::strlen(cptr));
    REQUIRE(str[0] == 'C');
    REQUIRE(str[1] == '-');
    REQUIRE(str[2] == 's');
    REQUIRE(str[3] == 't');
}

TEMPLATE_TEST_CASE("string: algorithms", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    // setup
    TestType str {"aaaaaa"};
    etl::for_each(str.begin(), str.end(), [](auto& c) { c++; });

    // test
    etl::for_each(str.cbegin(), str.cend(), [](auto const& c) { REQUIRE(c == 'b'); });

    REQUIRE(str.front() == 'b');
    REQUIRE(str.back() == 'b');
}

TEMPLATE_TEST_CASE("string: front/back", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    TestType str {"junk"};
    CHECK(str.front() == 'j');
    CHECK(etl::as_const(str).front() == 'j');

    CHECK(str.back() == 'k');
    CHECK(etl::as_const(str).back() == 'k');
}

TEMPLATE_TEST_CASE("string: data/c_str", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    TestType str {"junk"};
    CHECK(str.data() == str.c_str());
    CHECK(str.c_str() != nullptr);
    CHECK(str.c_str()[0] == 'j');
}

TEMPLATE_TEST_CASE("string: operator string_view", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    TestType str {"junk"};
    auto sv = etl::string_view {str};
    CHECK(sv.data()[0] == 'j');
}

TEMPLATE_TEST_CASE("string: clear", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    // setup
    TestType str {"junk"};
    REQUIRE(str.empty() == false);

    // test
    str.clear();
    REQUIRE(str.capacity() == str.max_size());
    REQUIRE(str.empty() == true);
    REQUIRE(str.size() == etl::size_t(0));
}

TEMPLATE_TEST_CASE("string: push_back", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    TestType str {""};
    str.push_back('a');
    str.push_back('b');
    REQUIRE(str == TestType("ab"));
    REQUIRE(str.size() == 2);
}

TEMPLATE_TEST_CASE("string: pop_back", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    TestType str {"abc"};
    str.pop_back();
    str.pop_back();
    REQUIRE(str == TestType("a"));
    REQUIRE(str == "a");
    REQUIRE(str.size() == 1);
}

TEMPLATE_TEST_CASE("string: insert(index, count, CharType)", "[string]",
                   etl::static_string<12>, etl::static_string<32>)
{
    auto str = TestType {};
    REQUIRE(str.empty() == true);

    str.insert(0, 4, 'a');
    REQUIRE(str.empty() == false);
    REQUIRE(str.size() == 4);
    REQUIRE(str[0] == 'a');
    REQUIRE(str[1] == 'a');
    REQUIRE(str[2] == 'a');
    REQUIRE(str[3] == 'a');
    REQUIRE(str[4] == 0);
}

TEMPLATE_TEST_CASE("string: insert(index, CharType const*)", "[string]",
                   etl::static_string<12>, etl::static_string<32>)
{
    auto str = TestType {};
    REQUIRE(str.empty() == true);

    str.insert(0, "abcd");
    REQUIRE(str.empty() == false);
    REQUIRE(str.size() == 4);
    REQUIRE(str[0] == 'a');
    REQUIRE(str[1] == 'b');
    REQUIRE(str[2] == 'c');
    REQUIRE(str[3] == 'd');
    REQUIRE(str[4] == 0);
}

TEMPLATE_TEST_CASE("string: insert(index, CharType const*, count)", "[string]",
                   etl::static_string<12>, etl::static_string<32>)
{
    auto str = TestType {};
    REQUIRE(str.empty() == true);

    str.insert(0, "abcd", 3);
    REQUIRE(str.empty() == false);
    REQUIRE(str.size() == 3);
    REQUIRE(str[0] == 'a');
    REQUIRE(str[1] == 'b');
    REQUIRE(str[2] == 'c');
    REQUIRE(str[3] == 0);
    REQUIRE(str[4] == 0);
}

TEMPLATE_TEST_CASE("string: resize", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    SECTION("default char")
    {
        auto str = TestType {};
        CHECK(str.empty() == true);

        // grow
        str.resize(2);
        CHECK(str.empty() == false);
        CHECK(str.size() == 2);
        CHECK(str[0] == '\0');
        CHECK(str[1] == '\0');

        // shrink
        str.resize(1);
        CHECK(str.empty() == false);
        CHECK(str.size() == 1);
        CHECK(str[0] == '\0');
    }

    SECTION("provided char")
    {
        auto str = TestType {};
        CHECK(str.empty() == true);

        // grow
        str.resize(2, 'a');
        CHECK(str.empty() == false);
        CHECK(str.size() == 2);
        CHECK(str[0] == 'a');
        CHECK(str[1] == 'a');

        // shrink
        str.resize(1, 'a');
        CHECK(str.empty() == false);
        CHECK(str.size() == 1);
        CHECK(str[0] == 'a');
    }
}

TEMPLATE_TEST_CASE("string: starts_with", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    using namespace etl::literals;

    SECTION("empty string")
    {
        auto str = TestType {};
        CHECK_FALSE(str.starts_with("foo"_sv));
        CHECK_FALSE(str.starts_with("foo"));
        CHECK_FALSE(str.starts_with('f'));
    }

    SECTION("false")
    {
        auto str = TestType {"test"};
        CHECK_FALSE(str.starts_with("foo"_sv));
        CHECK_FALSE(str.starts_with("foo"));
        CHECK_FALSE(str.starts_with('f'));
    }

    SECTION("true")
    {
        auto str1 = TestType {"foo"};
        CHECK(str1.starts_with("foo"_sv));
        CHECK(str1.starts_with("foo"));
        CHECK(str1.starts_with('f'));

        auto str2 = TestType {"foobar"};
        CHECK(str2.starts_with("foo"_sv));
        CHECK(str2.starts_with("foo"));
        CHECK(str2.starts_with('f'));
    }
}

TEMPLATE_TEST_CASE("string: ends_with", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    using namespace etl::literals;

    SECTION("empty string")
    {
        auto str = TestType {};
        CHECK_FALSE(str.ends_with("foo"_sv));
        CHECK_FALSE(str.ends_with("foo"));
        CHECK_FALSE(str.ends_with('o'));
    }

    SECTION("false")
    {
        auto str = TestType {"test"};
        CHECK_FALSE(str.ends_with("foo"_sv));
        CHECK_FALSE(str.ends_with("foo"));
        CHECK_FALSE(str.ends_with('o'));
    }

    SECTION("true")
    {
        auto str = TestType {"foo"};
        CHECK(str.ends_with("foo"_sv));
        CHECK(str.ends_with("foo"));
        CHECK(str.ends_with('o'));

        auto str2 = TestType {"barfoo"};
        CHECK(str2.ends_with("foo"_sv));
        CHECK(str2.ends_with("foo"));
        CHECK(str2.ends_with('o'));
    }
}

TEMPLATE_TEST_CASE("string: substr", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    using namespace etl::literals;

    SECTION("empty ")
    {
        auto str = TestType {};
        CHECK(str.substr().size() == 0);
        CHECK(str.substr(1).size() == 0);
        CHECK(str.substr(10).size() == 0);
    }

    SECTION("non empty")
    {
        auto str = TestType {"abcd"};
        CHECK(str.size() == 4);
        CHECK(str.substr(0, 1).size() == 1);
        CHECK(str.substr(1).size() == 3);
        CHECK(str.substr(10).size() == 0);
    }
}

TEMPLATE_TEST_CASE("string: copy", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    SECTION("empty")
    {
        char destination[32] = {};
        auto str             = TestType {};
        CHECK(str.empty());
        CHECK(str.copy(destination, 0, 0) == 0);
        CHECK(str.copy(destination, 1, 0) == 0);
        CHECK(str.copy(destination, 10, 1) == 0);
    }

    SECTION("non empty")
    {
        char destination[32] = {};
        auto str             = TestType {"abcd"};
        CHECK(str.size() == 4);

        CHECK(str.copy(destination, 1, 100) == 0);
        CHECK(destination[0] == '\0');

        CHECK(str.copy(destination, 1, 0) == 1);
        CHECK(destination[0] == 'a');
        CHECK(destination[1] == '\0');

        CHECK(str.copy(destination, 2, 2) == 2);
        CHECK(destination[0] == 'c');
        CHECK(destination[1] == 'd');
        CHECK(destination[2] == '\0');

        CHECK(str.copy(destination, str.size()) == 4);
        CHECK(destination[0] == 'a');
        CHECK(destination[1] == 'b');
        CHECK(destination[2] == 'c');
        CHECK(destination[3] == 'd');
        CHECK(destination[4] == '\0');
    }
}

TEMPLATE_TEST_CASE("string: swap", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    SECTION("empty")
    {
        auto lhs = TestType {};
        auto rhs = TestType {};
        CHECK(lhs.empty());
        CHECK(rhs.empty());

        lhs.swap(rhs);
        CHECK(lhs.empty());
        CHECK(rhs.empty());
    }

    SECTION("same size")
    {
        auto lhs = TestType {"abc"};
        auto rhs = TestType {"def"};
        CHECK(lhs.size() == rhs.size());

        etl::swap(lhs, rhs);
        CHECK(lhs.size() == rhs.size());

        CHECK(lhs == "def");
        CHECK(rhs == "abc");
    }

    SECTION("different size")
    {
        auto lhs = TestType {"foo"};
        auto rhs = TestType {"barbaz"};
        CHECK(lhs.size() != rhs.size());

        lhs.swap(rhs);
        CHECK(lhs.size() != rhs.size());

        CHECK(lhs == "barbaz");
        CHECK(rhs == "foo");
    }
}

TEMPLATE_TEST_CASE("string: compare(string)", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    SECTION("empty string same capacity")
    {
        auto lhs = TestType {};
        auto rhs = TestType {};

        CHECK(lhs.compare(rhs) == 0);
        CHECK(rhs.compare(lhs) == 0);
    }

    SECTION("empty string different capacity")
    {
        auto lhs = TestType {};
        auto rhs = etl::static_string<2> {};

        CHECK(lhs.compare(rhs) == 0);
        CHECK(rhs.compare(lhs) == 0);
    }
}

TEMPLATE_TEST_CASE("string: find(string)", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    SECTION("empty string")
    {
        auto str = TestType {};
        CHECK(str.find(TestType {}, 0) == 0);
        CHECK(str.find(TestType {}, 1) == TestType::npos);
        CHECK(str.find(TestType {""}) == 0);
    }

    SECTION("not found")
    {
        auto str = TestType {"def"};
        CHECK(str.find(TestType {"abc"}, 0) == TestType::npos);
        CHECK(str.find(TestType {"abc"}, 1) == TestType::npos);
        CHECK(str.find(TestType {"abc"}) == TestType::npos);
    }

    SECTION("found")
    {
        auto str = TestType {"abcd"};
        CHECK(str.find(TestType {"abc"}, 0) == 0);
        CHECK(str.find(TestType {"bc"}, 1) == 1);
        CHECK(str.find(TestType {"cd"}) == 2);
    }
}

TEMPLATE_TEST_CASE("string: find(char const*)", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    SECTION("empty string")
    {
        auto str = TestType {};
        CHECK(str.find("") == 0);
        CHECK(str.find("", 0) == 0);
        CHECK(str.find("", 1) == TestType::npos);
    }

    SECTION("not found")
    {
        auto str = TestType {"def"};
        CHECK(str.find("abc", 0) == TestType::npos);
        CHECK(str.find("abc", 1) == TestType::npos);
        CHECK(str.find("abc") == TestType::npos);
    }

    SECTION("found")
    {
        auto str = TestType {"abcd"};
        CHECK(str.find("abc", 0) == 0);
        CHECK(str.find("bc", 1) == 1);
        CHECK(str.find("cd") == 2);
    }
}

TEMPLATE_TEST_CASE("string: find(char)", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    SECTION("empty string")
    {
        auto str = TestType {};
        CHECK(str.find('a', 0) == TestType::npos);
        CHECK(str.find('a', 1) == TestType::npos);
        CHECK(str.find('a') == TestType::npos);
    }

    SECTION("not found")
    {
        auto str = TestType {"bcdef"};
        CHECK(str.find('a', 0) == TestType::npos);
        CHECK(str.find('a', 1) == TestType::npos);
        CHECK(str.find('a') == TestType::npos);
    }

    SECTION("found")
    {
        auto str = TestType {"abcd"};
        CHECK(str.find('a', 0) == 0);
        CHECK(str.find('b', 1) == 1);
        CHECK(str.find('c') == 2);
    }
}

TEMPLATE_TEST_CASE("string: rfind(string)", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    SECTION("empty string")
    {
        auto str = TestType {"test"};
        CHECK(str.rfind(TestType {}) == 0);
        CHECK(str.rfind(TestType {}, 0) == 0);
        CHECK(str.rfind(TestType {}, TestType::npos) == str.size());
    }

    SECTION("not found")
    {
        auto str = TestType {"def"};
        CHECK(str.rfind(TestType {"abc"}, 0) == TestType::npos);
        CHECK(str.rfind(TestType {"abc"}, 1) == TestType::npos);
        CHECK(str.rfind(TestType {"abc"}) == TestType::npos);
    }

    SECTION("found")
    {
        // auto const str = TestType {"test"};
        // CHECK(str.rfind(TestType {"t"}) == 3);
        // CHECK(str.rfind(TestType {"est"}) == 1);

        // CHECK(str.rfind(TestType {"st"}, 12) == 2);
        // CHECK(str.rfind(TestType {"st"}, 12) == 2);
    }
}

TEMPLATE_TEST_CASE("string: rfind(char const*)", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    SECTION("empty string")
    {
        auto str = TestType {"test"};
        CHECK(str.rfind("") == 0);
        CHECK(str.rfind("", 0) == 0);
        CHECK(str.rfind("", TestType::npos) == str.size());
    }

    SECTION("not found")
    {
        auto str = TestType {"def"};
        CHECK(str.rfind("abc", 0) == TestType::npos);
        CHECK(str.rfind("abc", 1) == TestType::npos);
        CHECK(str.rfind("abc") == TestType::npos);
    }

    SECTION("found")
    {
        auto const str = TestType {"test"};
        CHECK(str.rfind("t") == 0);
        // CHECK(str.rfind("t", 1) == 3);
        // CHECK(str.rfind("est") == 1);

        // CHECK(str.rfind("st", 12) == 2);
        // CHECK(str.rfind("st", 12) == 2);
    }
}

TEMPLATE_TEST_CASE("string: find_first_of(string)", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    SECTION("empty string")
    {
        auto str = TestType {};
        CHECK(str.find_first_of(TestType {}, 0) == TestType::npos);
        CHECK(str.find_first_of(TestType {}, 1) == TestType::npos);
        CHECK(str.find_first_of(TestType {""}) == TestType::npos);
    }

    SECTION("not found")
    {
        auto str = TestType {"def"};
        CHECK(str.find_first_of(TestType {"abc"}, 0) == TestType::npos);
        CHECK(str.find_first_of(TestType {"abc"}, 1) == TestType::npos);
        CHECK(str.find_first_of(TestType {"abc"}) == TestType::npos);
    }

    SECTION("found")
    {
        auto str = TestType {"abcd"};
        CHECK(str.find_first_of(TestType {"abc"}, 0) == 0);
        CHECK(str.find_first_of(TestType {"bc"}, 1) == 1);
        CHECK(str.find_first_of(TestType {"cd"}) == 2);
    }
}

TEMPLATE_TEST_CASE("string: find_first_of(char const*)", "[string]",
                   etl::static_string<12>, etl::static_string<32>)
{
    SECTION("empty string")
    {
        auto str = TestType {};
        CHECK(str.find_first_of("", 0) == TestType::npos);
        CHECK(str.find_first_of("", 1) == TestType::npos);
        CHECK(str.find_first_of("") == TestType::npos);
    }

    SECTION("not found")
    {
        auto str = TestType {"def"};
        CHECK(str.find_first_of("abc", 0) == TestType::npos);
        CHECK(str.find_first_of("abc", 1) == TestType::npos);
        CHECK(str.find_first_of("abc") == TestType::npos);
    }

    SECTION("found")
    {
        auto str = TestType {"abcd"};
        CHECK(str.find_first_of("abc", 0) == 0);
        CHECK(str.find_first_of("bc", 1) == 1);
        CHECK(str.find_first_of("cd") == 2);
    }
}

TEMPLATE_TEST_CASE("string: find_first_of(char)", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    SECTION("empty string")
    {
        auto str = TestType {};
        CHECK(str.find_first_of('a', 0) == TestType::npos);
        CHECK(str.find_first_of('a', 1) == TestType::npos);
        CHECK(str.find_first_of('a') == TestType::npos);
    }

    SECTION("not found")
    {
        auto str = TestType {"def"};
        CHECK(str.find_first_of('a', 0) == TestType::npos);
        CHECK(str.find_first_of('a', 1) == TestType::npos);
        CHECK(str.find_first_of('a') == TestType::npos);
    }

    SECTION("found")
    {
        auto str = TestType {"abcd"};
        CHECK(str.find_first_of('a', 0) == 0);
        CHECK(str.find_first_of('b', 1) == 1);
        CHECK(str.find_first_of('c') == 2);
    }
}

TEMPLATE_TEST_CASE("string: operator==/!=", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    SECTION("empty string same capacity")
    {
        auto lhs = TestType {};
        auto rhs = TestType {};

        CHECK(lhs == "");
        CHECK(lhs == rhs);
        CHECK_FALSE(lhs != rhs);
        CHECK(rhs == lhs);
        CHECK_FALSE(rhs != lhs);
    }

    SECTION("empty string different capacity")
    {
        auto lhs = TestType {};
        auto rhs = etl::static_string<2> {};

        CHECK(lhs == "");
        CHECK(rhs == "");
        CHECK(lhs == rhs);
        CHECK_FALSE(lhs != rhs);
        CHECK_FALSE(lhs != "");
        CHECK(rhs == lhs);
        CHECK_FALSE(rhs != lhs);
    }
}

TEMPLATE_TEST_CASE("string: operator<", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    using string = TestType;

    SECTION("empty string")
    {
        CHECK_FALSE(string {} < "");
        CHECK_FALSE(string {} < string {});
        CHECK_FALSE(string {} < etl::static_string<2> {});
        CHECK_FALSE(etl::static_string<4> {} < string {});
    }

    SECTION("string same capacity")
    {
        CHECK(string {"abc"} < "def");
        CHECK(string {"abc"} < string {"def"});
        CHECK(string {"abc"} < string {"defg"});
    }

    SECTION("string different capacity")
    {
        CHECK_FALSE(string {"def"} < "a");
        CHECK_FALSE(string {"def"} < etl::static_string<2> {"a"});
        CHECK(etl::static_string<2> {"a"} < string {"test"});
    }
}

TEMPLATE_TEST_CASE("string: operator<=", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    using string = TestType;

    SECTION("empty string")
    {
        CHECK(string {} <= "");
        CHECK(string {} <= string {});
        CHECK(string {} <= etl::static_string<2> {});
        CHECK(etl::static_string<4> {} <= string {});
    }

    SECTION("string same capacity")
    {
        CHECK(string {"abc"} <= "def");
        CHECK(string {"abc"} <= string {"def"});
        CHECK(string {"abc"} <= string {"defg"});
        CHECK(string {"abc"} <= string {"abc"});
    }

    SECTION("string different capacity")
    {
        CHECK_FALSE(string {"def"} <= "a");
        CHECK_FALSE(string {"def"} <= etl::static_string<2> {"a"});
        CHECK(etl::static_string<2> {"a"} <= string {"test"});
    }
}

TEMPLATE_TEST_CASE("string: operator>", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    using string = TestType;

    SECTION("empty string")
    {
        CHECK_FALSE(string {} > "");
        CHECK_FALSE(string {} > string {});
        CHECK_FALSE(string {} > etl::static_string<2> {});
        CHECK_FALSE(etl::static_string<4> {} > string {});
    }

    SECTION("string same capacity")
    {
        CHECK_FALSE(string {"abc"} > "def");
        CHECK_FALSE(string {"abc"} > string {"def"});
        CHECK_FALSE(string {"abc"} > string {"defg"});
        CHECK_FALSE(string {"abc"} > string {"abc"});
    }

    SECTION("string different capacity")
    {
        CHECK(string {"def"} > etl::static_string<2> {"a"});
        CHECK_FALSE(etl::static_string<2> {"a"} > string {"test"});
    }
}

TEMPLATE_TEST_CASE("string: operator>=", "[string]", etl::static_string<12>,
                   etl::static_string<32>)
{
    using string = TestType;

    SECTION("empty string")
    {
        CHECK(string {} >= "");
        CHECK(string {} >= string {});
        CHECK(string {} >= etl::static_string<2> {});
        CHECK(etl::static_string<4> {} >= string {});
    }

    SECTION("string same capacity")
    {
        CHECK(string {"abc"} >= "abc");
        CHECK(string {"abc"} >= string {"abc"});
        CHECK_FALSE(string {"abc"} >= string {"def"});
        CHECK_FALSE(string {"abc"} >= string {"defg"});
    }

    SECTION("string different capacity")
    {
        CHECK(string {"def"} >= etl::static_string<2> {"a"});
        CHECK_FALSE(etl::static_string<2> {"a"} >= string {"test"});
    }
}