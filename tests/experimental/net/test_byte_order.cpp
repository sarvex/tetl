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

#include "etl/definitions.hpp"                  // for int8_t, uint16_t, uin...
#include "etl/experimental/net/byte_order.hpp"  // for hton, ntoh, net

TEST_CASE("experimental/net: ntoh/hton char", "[experimental][net]")
{
    using namespace etl::net;
    REQUIRE(ntoh(hton(char {0})) == 0);
    REQUIRE(ntoh(hton(char {1})) == 1);
    REQUIRE(ntoh(hton(char {42})) == 42);
}

TEST_CASE("experimental/net: ntoh/hton etl::int8_t", "[experimental][net]")
{
    using namespace etl::net;
    REQUIRE(ntoh(hton(etl::int8_t {0})) == 0);
    REQUIRE(ntoh(hton(etl::int8_t {1})) == 1);
    REQUIRE(ntoh(hton(etl::int8_t {42})) == 42);
}

TEST_CASE("experimental/net: ntoh/hton etl::uint8_t", "[experimental][net]")
{
    using namespace etl::net;
    REQUIRE(ntoh(hton(etl::uint8_t {0})) == 0);
    REQUIRE(ntoh(hton(etl::uint8_t {1})) == 1);
    REQUIRE(ntoh(hton(etl::uint8_t {42})) == 42);
}

TEST_CASE("experimental/net: ntoh/hton etl::uint16_t", "[experimental][net]")
{
    using namespace etl::net;
    REQUIRE(ntoh(hton(etl::uint16_t {0})) == 0);
    REQUIRE(ntoh(hton(etl::uint16_t {1})) == 1);
    REQUIRE(ntoh(hton(etl::uint16_t {42})) == 42);
}

TEST_CASE("experimental/net: ntoh/hton etl::uint32_t", "[experimental][net]")
{
    using namespace etl::net;
    REQUIRE(ntoh(hton(etl::uint32_t {0})) == 0);
    REQUIRE(ntoh(hton(etl::uint32_t {1})) == 1);
    REQUIRE(ntoh(hton(etl::uint32_t {42})) == 42);
}