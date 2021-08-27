/// \copyright Tobias Hienzsch 2019-2021
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt
#include "etl/variant.hpp"

#include "catch2/catch_template_test_macros.hpp"

TEST_CASE("variant: monostate", "[variant]")
{
    // All instances of etl::monostate compare equal.
    auto lhs = etl::monostate {};
    auto rhs = etl::monostate {};

    CHECK(lhs == rhs);
    CHECK(lhs <= rhs);
    CHECK(lhs >= rhs);

    CHECK_FALSE(lhs != rhs);
    CHECK_FALSE(lhs < rhs);
    CHECK_FALSE(lhs > rhs);
}

TEST_CASE("variant: sizeof", "[variant]")
{
    if constexpr (sizeof(etl::size_t) == 8) {
        STATIC_REQUIRE(sizeof(etl::variant<etl::monostate, int>) == 16);
        STATIC_REQUIRE(sizeof(etl::variant<etl::monostate, int, float>) == 16);
        STATIC_REQUIRE(sizeof(etl::variant<etl::monostate, int, double>) == 16);

        struct S {
            float data[4];
        };

        STATIC_REQUIRE(sizeof(etl::variant<etl::monostate, S, double>) == 24);
    }
}

TEST_CASE("variant: construct", "[variant]")
{
    SECTION("monostate")
    {
        auto var
            = etl::variant<etl::monostate, int, float> { etl::monostate {} };
        CHECK(etl::holds_alternative<etl::monostate>(var));
        CHECK(*etl::get_if<etl::monostate>(&var) == etl::monostate {});
    }

    SECTION("int")
    {
        auto var = etl::variant<etl::monostate, int, float> { 42 };
        CHECK(etl::holds_alternative<int>(var));
        CHECK(*etl::get_if<int>(&var) == 42);
    }

    SECTION("float")
    {
        auto var = etl::variant<etl::monostate, int, float> { 143.0F };
        CHECK(etl::holds_alternative<float>(var));
        CHECK(*etl::get_if<float>(&var) == 143.0F);
    }
}

TEST_CASE("variant: index", "[variant]")
{
    SECTION("0")
    {
        auto var
            = etl::variant<etl::monostate, int, float> { etl::monostate {} };
        CHECK(var.index() == 0);
    }

    SECTION("1")
    {
        auto var = etl::variant<etl::monostate, int, float> { 42 };
        CHECK(var.index() == 1);
    }

    SECTION("2")
    {
        auto var = etl::variant<etl::monostate, int, float> { 143.0F };
        CHECK(var.index() == 2);
    }

    SECTION("3")
    {
        auto var = etl::variant<etl::monostate, int, float, double> { 143.0 };
        CHECK(var.index() == 3);
    }
}

TEST_CASE("variant: operator=(variant const&)", "[variant]")
{
    auto var = etl::variant<etl::monostate, int, float> { 42 };
    CHECK(etl::holds_alternative<int>(var));
    CHECK(*etl::get_if<int>(&var) == 42);

    auto var2 = etl::variant<etl::monostate, int, float> { 143 };
    CHECK(etl::holds_alternative<int>(var2));
    CHECK(*etl::get_if<int>(&var2) == 143);
    var2 = var;
    CHECK(etl::holds_alternative<int>(var2));
    CHECK(*etl::get_if<int>(&var2) == 42);

    // var = 42.0f;
    // CHECK(etl::holds_alternative<float>(var));
    // CHECK(etl::get_if<int>(&var) == nullptr);
    // CHECK(*etl::get_if<float>(&var) == 42.0f);
}

TEST_CASE("variant: holds_alternative", "[variant]")
{
    SECTION("mutable")
    {
        auto var = etl::variant<etl::monostate, int, float, double> { 42 };
        CHECK(etl::holds_alternative<int>(var));
        CHECK_FALSE(etl::holds_alternative<etl::monostate>(var));
        CHECK_FALSE(etl::holds_alternative<float>(var));
        CHECK_FALSE(etl::holds_alternative<double>(var));
    }

    SECTION("const")
    {
        auto const var
            = etl::variant<etl::monostate, int, float, double> { 42.0F };
        CHECK(etl::holds_alternative<float>(var));
        CHECK_FALSE(etl::holds_alternative<int>(var));
        CHECK_FALSE(etl::holds_alternative<etl::monostate>(var));
        CHECK_FALSE(etl::holds_alternative<double>(var));
    }
}

TEST_CASE("variant: get_if", "[variant]")
{
    SECTION("mutable")
    {
        auto var = etl::variant<etl::monostate, int, float, double> { 42 };
        CHECK(etl::get_if<int>(&var) != nullptr);
        CHECK(*etl::get_if<int>(&var) == 42);

        CHECK(etl::get_if<etl::monostate>(&var) == nullptr);
        CHECK(etl::get_if<float>(&var) == nullptr);
        CHECK(etl::get_if<double>(&var) == nullptr);
    }

    SECTION("const")
    {
        auto const var
            = etl::variant<etl::monostate, int, float, double> { 42 };
        CHECK(etl::get_if<int>(&var) != nullptr);
        CHECK(*etl::get_if<int>(&var) == 42);

        CHECK(etl::get_if<etl::monostate>(&var) == nullptr);
        CHECK(etl::get_if<float>(&var) == nullptr);
        CHECK(etl::get_if<double>(&var) == nullptr);
    }
}

TEST_CASE("variant: variant_size", "[variant]")
{
    using t1 = etl::variant<etl::monostate>;
    using t2 = etl::variant<etl::monostate, int>;
    using t3 = etl::variant<etl::monostate, int, float>;
    using t4 = etl::variant<etl::monostate, int, float, double>;

    STATIC_REQUIRE(etl::variant_size_v<t1> == 1);
    STATIC_REQUIRE(etl::variant_size_v<t2> == 2);
    STATIC_REQUIRE(etl::variant_size_v<t3> == 3);
    STATIC_REQUIRE(etl::variant_size_v<t4> == 4);
}