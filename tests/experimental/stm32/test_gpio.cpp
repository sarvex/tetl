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

#include <bitset>

#include "taetl/experimental/hardware/stm32/stm32.hpp"

#include "catch2/catch.hpp"

using namespace taetl::hardware;
using register_bits = std::bitset<32>;

TEST_CASE("stm32: gpio", "[stm32][hardware]")
{
    auto memory          = stm32::gpio_memory_layout {};
    memory.bit_set_reset = 0x0;
    auto& gpio           = stm32::port::place_at(&memory);

    SECTION("When pin is set to low, sets bits in BSRR lower word")
    {
        gpio.write(stm32::pin_number::pin_1, stm32::pin_state::reset);
        REQUIRE(register_bits(memory.bit_set_reset).test(1));

        gpio.write(stm32::pin_number::pin_3, stm32::pin_state::reset);
        REQUIRE(register_bits(memory.bit_set_reset).test(3));

        gpio.write(stm32::pin_number::pin_15, stm32::pin_state::reset);
        REQUIRE(register_bits(memory.bit_set_reset).test(15));
    }

    SECTION("When pin is set to high, sets bits in BSRR upper word")
    {
        gpio.write(stm32::pin_number::pin_1, stm32::pin_state::set);
        REQUIRE(register_bits(memory.bit_set_reset).test(1 + 16));

        gpio.write(stm32::pin_number::pin_3, stm32::pin_state::set);
        REQUIRE(register_bits(memory.bit_set_reset).test(3 + 16));

        gpio.write(stm32::pin_number::pin_15, stm32::pin_state::set);
        REQUIRE(register_bits(memory.bit_set_reset).test(15 + 16));
    }
}