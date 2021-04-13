# TETL - Embedded Template Library

Tobante's embedded template library. A STL-like C++ template library designed for embedded devices with limited resources. Supports freestanding and hosted environments.

- [Quick Start](#quick-start)
- [Status](#status)
  - [Hosted](#hosted)
  - [Freestanding](#freestanding)
  - [Analysis](#analysis)
- [Design Goals](#design-goals)
- [Project Integration](#project-integration)
  - [Command Line / Makefile](#command-line---makefile)
  - [CMake](#cmake)
  - [PlatformIO](#platformio)
- [Header Overview](#header-overview)
- [Header Detail](#header-detail)

## Quick Start

```cpp
// main.cpp
#include "etl/algorithm.hpp"  // for count_if
#include "etl/array.hpp"      // for array

auto main() -> int
{
  auto const numbers = etl::array{1, 2, 3, 4, 5};
  auto const greater_two = [] (auto const v) { return v > 2; };
  return etl::count_if(begin(numbers), end(numbers), greater_two);
}
```

```sh
g++ -Wall -Wextra -Wpedantic -std=c++17 -I path/to/tetl main.cpp
```

For examples look at the [examples](./examples) subdirectory or the test files in [tests](./tests).

## Status

| **License**                                                                                                                 | **Lines of Code**                                 | **Progress**                                                                                                        |
| --------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------- |
| [![License](https://img.shields.io/badge/License-BSD%202--Clause-orange.svg)](https://opensource.org/licenses/BSD-2-Clause) | ![](https://sloc.xyz/github/tobanteEmbedded/tetl) | [Spreadsheet](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit?usp=sharing) |

### Hosted

| **Compiler** |                                                                                         **C++17**                                                                                         |                                                                                         **C++20**                                                                                         |
| :----------: | :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
|   **GCC**    |       [![GCC C++17](https://github.com/tobanteEmbedded/tetl/workflows/GCC%20C++17/badge.svg)](https://github.com/tobanteEmbedded/tetl/actions?query=workflow%3A%22GCC+C%2B%2B17%22)       |       [![GCC C++20](https://github.com/tobanteEmbedded/tetl/workflows/GCC%20C++20/badge.svg)](https://github.com/tobanteEmbedded/tetl/actions?query=workflow%3A%22GCC+C%2B%2B20%22)       |
|  **Clang**   |    [![Clang C++17](https://github.com/tobanteEmbedded/tetl/workflows/Clang%20C++17/badge.svg)](https://github.com/tobanteEmbedded/tetl/actions?query=workflow%3A%22Clang+C%2B%2B17%22)    |    [![Clang C++20](https://github.com/tobanteEmbedded/tetl/workflows/Clang%20C++20/badge.svg)](https://github.com/tobanteEmbedded/tetl/actions?query=workflow%3A%22Clang+C%2B%2B20%22)    |
|  **macOS**   |    [![macOS C++17](https://github.com/tobanteEmbedded/tetl/workflows/macOS%20C++17/badge.svg)](https://github.com/tobanteEmbedded/tetl/actions?query=workflow%3A%22macOS+C%2B%2B17%22)    |    [![macOS C++20](https://github.com/tobanteEmbedded/tetl/workflows/macOS%20C++20/badge.svg)](https://github.com/tobanteEmbedded/tetl/actions?query=workflow%3A%22macOS+C%2B%2B20%22)    |
| **Windows**  | [![Windows C++17](https://github.com/tobanteEmbedded/tetl/workflows/Windows%20C++17/badge.svg)](https://github.com/tobanteEmbedded/tetl/actions?query=workflow%3A%22Windows+C%2B%2B17%22) | [![Windows C++20](https://github.com/tobanteEmbedded/tetl/workflows/Windows%20C++20/badge.svg)](https://github.com/tobanteEmbedded/tetl/actions?query=workflow%3A%22Windows+C%2B%2B20%22) |

### Freestanding

| **Compiler** |                                                                                   **C++17**                                                                                   |                                                                                   **C++20**                                                                                   |
| :----------: | :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| **AVR GCC**  | [![AVR C++17](https://github.com/tobanteEmbedded/tetl/workflows/AVR%20C++17/badge.svg)](https://github.com/tobanteEmbedded/tetl/actions?query=workflow%3A%22AVR+C%2B%2B17%22) | [![AVR C++20](https://github.com/tobanteEmbedded/tetl/workflows/AVR%20C++20/badge.svg)](https://github.com/tobanteEmbedded/tetl/actions?query=workflow%3A%22AVR+C%2B%2B20%22) |
| **ARM GCC**  | [![ARM C++17](https://github.com/tobanteEmbedded/tetl/workflows/ARM%20C++17/badge.svg)](https://github.com/tobanteEmbedded/tetl/actions?query=workflow%3A%22ARM+C%2B%2B17%22) | [![ARM C++20](https://github.com/tobanteEmbedded/tetl/workflows/ARM%20C++20/badge.svg)](https://github.com/tobanteEmbedded/tetl/actions?query=workflow%3A%22ARM+C%2B%2B20%22) |

### Analysis

| **Clang-Tidy**                                                                                                                                                                | **ASAN**                                                                                                                                                    | **UBSAN**                                                                                                                                                      | **Coverage**                                                                                                                     |
| ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------- |
| [![Clang-Tidy](https://github.com/tobanteEmbedded/tetl/actions/workflows/clang-tidy.yml/badge.svg)](https://github.com/tobanteEmbedded/tetl/actions/workflows/clang-tidy.yml) | [![ASAN](https://github.com/tobanteEmbedded/tetl/actions/workflows/asan.yml/badge.svg)](https://github.com/tobanteEmbedded/tetl/actions/workflows/asan.yml) | [![UBSAN](https://github.com/tobanteEmbedded/tetl/actions/workflows/ubsan.yml/badge.svg)](https://github.com/tobanteEmbedded/tetl/actions/workflows/ubsan.yml) | [![codecov](https://codecov.io/gh/tobanteEmbedded/tetl/branch/main/graph/badge.svg)](https://codecov.io/gh/tobanteEmbedded/tetl) |

## Design Goals

- 100% portable (no STL headers required, minimum of C headers)
- Header only
- C++17 and beyond (freestanding or hosted)
- Similar API to the STL
- No dynamic memory
- `constexpr` all the things
- Easy desktop development (cmake)

It all started when I wanted to have a vector without dynamic memory. At that time I didn't know that proposals like [github.com/gnzlbg/static_vector](https://github.com/gnzlbg/static_vector) where in the making. My actual goal has turned into a mammoth project. A standard library for microcontrollers and other embedded environments. The API is, as far as it is technically feasible, identical to the STL. All algorithms work identically, pair and friend are available and containers like set, map and vector are also implemented, but with different names.

All containers work only with memory on the stack. This means that their size must be known at compile time. Furthermore I assume an environment in which exceptions and
RTTI migth be disabled. This results in the problem that not all members of a container can be implemented. Any function that returns a reference to a sequence element has the ability to throw exceptions in a normal hosted environment. If exceptions are disabled, this is not possible. For now, my solution to this problem is to delegate to the user. Unsafe methods like `etl::static_vector::operator[]` are still available (with asserts in debug builds), while throwing methods like `etl::static_vector::at` are not implemented.

Unlike LLVMs `SmallVector`, `etl::static_vector` & friends do not have a base class which they can slice to. My plan is to add mutable view-like non-owning types for each container. A `etl::static_vector` we would have a `vector_ref` which would work mostly like a `span`, but would also provide the vector interface. I don't want to name the types `*_view`, since the word `view` implies non-mutable in standard containers like `string_view`. None of the container_ref types have been implemented yet.

The headers [etl/algorithm.hpp](./etl/algorithm.hpp) and [etl/numeric.hpp](./etl/numeric.hpp) provide all algorithms from the standard. Unlike implementations found in libstdc++ or libc++, mine are primarily optimized for code size and not runtime performance. Overloads with an `ExecutionPolicy` are not implemented.

Headers like [etl/chrono.hpp](./etl/chrono.hpp) and [etl/mutex.hpp](./etl/mutex.hpp) only provide classes & functions that can be implemented in a portable way. Platform specific functionality like `steady_clock` or `mutex` can be provided by the user. The user provided types should meet the requirements listed in [Named Requirements](https://en.cppreference.com/w/cpp/named_req) to work seamlessly with the types provided in the `etl` namespace.

The [etl/experimental](./etl/experimental) subdirectory includes libraries that use `etl` as their foundation. It can be thought of as a mini boost-like library collection. Everything is work in progress.

- Networking (buffers, ntoh, ...)
- Strong types
- STM32 HAL
- DSP DSL
- FreeRTOS Abstraction
  - Stubs for unittests run on desktop machines

## Project Integration

The following steps explain how to add `etl` to your project. Embedded or desktop.

```sh
cd path/to/your/project
mkdir 3rd_party
git submodule add https://github.com/tobanteEmbedded/tetl.git 3rd_party/taetl
```

### Command Line / Makefile

```make
CXXFLAGS += -std=c++17 -I3rd_party/taetl
```

### CMake

Add `taetl` as a git submodule, then add these lines to your `CMakeLists.txt`:

```cmake
add_subdirectory(3rd_party/taetl EXCLUDE_FROM_ALL)
target_link_libraries(${YOUR_TARGET} tobanteEmbedded::etl)
```

### PlatformIO

Add `taetl` as a git submodule, then add these lines to your `platformio.ini`:

```ini
[env:yourenv]
build_unflags = -std=gnu++11
build_flags = -std=gnu++17 -Wno-register -I 3rd_party/taetl
```

## Header Overview

|          **Header**           |       **Library**        |     **Status**     |                                               **Progress (Spreadsheet)**                                               |
| :---------------------------: | :----------------------: | :----------------: | :--------------------------------------------------------------------------------------------------------------------: |
|    [algorithm](#algorithm)    |        Algorithms        | :heavy_check_mark: |  [algorithm](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1451123716)  |
|              any              |         Utility          |        :x:         |                                                                                                                        |
|        [array](#array)        |        Containers        | :heavy_check_mark: |    [array](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1320059600)    |
|            atomic             |          Atomic          |        :x:         |                                                                                                                        |
|            barrier            |          Thread          |        :x:         |                                                                                                                        |
|          [bit](#bit)          |         Numeric          | :heavy_check_mark: |     [bit](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1927645890)     |
|       [bitset](#bitset)       |         Utility          | :heavy_check_mark: |    [bitset](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=692946382)    |
|      [cassert](#cassert)      | Utility / Error Handling | :heavy_check_mark: |   [cassert](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=460740183)    |
|       [cctype](#cctype)       |         Strings          | :heavy_check_mark: |    [cctype](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=522168028)    |
|            cerrno             | Utility / Error Handling |        :x:         |                                                                                                                        |
|             cfenv             |         Numeric          |        :x:         |                                                          TODO                                                          |
|       [cfloat](#cfloat)       | Utility / Numeric Limits | :heavy_check_mark: |   [cfloat](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1012838019)    |
|     [charconv](#charconv)     |         Strings          | :heavy_check_mark: |   [charconv](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=345887816)   |
|       [chrono](#chrono)       |         Utility          | :heavy_check_mark: |   [chrono](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1279150724)    |
|           cinttypes           | Utility / Numeric Limits |        :x:         |                                                          TODO                                                          |
|      [climits](#climits)      | Utility / Numeric Limits | :heavy_check_mark: |   [climits](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1904156895)   |
|            clocale            |       Localization       |        :x:         |                                                                                                                        |
|        [cmath](#cmath)        |         Numeric          | :heavy_check_mark: |    [cmath](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=868070087)     |
|            compare            |         Utility          |        :x:         |                                                          TODO                                                          |
|            complex            |         Numeric          |        :x:         |                                                          TODO                                                          |
|     [concepts](#concepts)     |         Concepts         | :heavy_check_mark: |   [concepts](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=73781271)    |
|      condition_variable       |          Thread          |        :x:         |                                                                                                                        |
|           coroutine           |        Coroutines        |        :x:         |                                                                                                                        |
|            csetjmp            |         Utility          |        :x:         |                                                                                                                        |
|            csignal            |         Utility          |        :x:         |                                                                                                                        |
|      [cstdarg](#cstdarg)      |         Utility          | :heavy_check_mark: |   [cstdarg](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1280782172)   |
|      [cstddef](#cstddef)      |         Utility          | :heavy_check_mark: |   [cstddef](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1660546405)   |
|      [cstdint](#cstdint)      | Utility / Numeric Limits | :heavy_check_mark: |   [cstdint](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=2005735528)   |
|       [cstdio](#cstdio)       |       Input/Output       | :heavy_check_mark: |   [cstdio](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1576270107)    |
|      [cstdlib](#cstdlib)      |         Utility          | :heavy_check_mark: |   [cstdlib](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1705155517)   |
|      [cstring](#cstring)      |         Strings          | :heavy_check_mark: |   [cstring](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1824871501)   |
|        [ctime](#ctime)        |         Utility          | :heavy_check_mark: |    [ctime](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1082109762)    |
|            cuchar             |         Strings          |        :x:         |                                                                                                                        |
|            cwchar             |         Strings          |        :x:         |                                                                                                                        |
|            cwctype            |         Strings          |        :x:         |                                                                                                                        |
|             deque             |        Containers        |        :x:         |                                                          TODO                                                          |
|           exception           | Utility / Error Handling |        :x:         |                                                                                                                        |
|           execution           |        Algorithms        |        :x:         |                                                                                                                        |
|     [expected](#expected)     | Utility / Error Handling | :heavy_check_mark: |  [expected](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1624993362)   |
|          filesystem           |        Filesystem        |        :x:         |                                                                                                                        |
|       [format](#format)       |         Strings          | :heavy_check_mark: |    [format](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=159875067)    |
|         forward_list          |        Containers        |        :x:         |                                                                                                                        |
|   [functional](#functional)   |         Utility          | :heavy_check_mark: |  [functional](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=291953395)  |
|            future             |          Thread          |        :x:         |                                                                                                                        |
|            fstream            |       Input/Output       |        :x:         |                                                                                                                        |
|           ifstream            |       Input/Output       |        :x:         |                                                                                                                        |
|       initializer_list        |         Utility          |        :x:         |                                                                                                                        |
|            iomanip            |       Input/Output       |        :x:         |                                                                                                                        |
|          [ios](#ios)          |       Input/Output       | :heavy_check_mark: |     [ios](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=2084657878)     |
|            iosfwd             |       Input/Output       |        :x:         |                                                                                                                        |
|           iostream            |       Input/Output       |        :x:         |                                                                                                                        |
|     [iterator](#iterator)     |         Iterator         | :heavy_check_mark: |  [iterator](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=2084657878)   |
|            istream            |       Input/Output       |        :x:         |                                                                                                                        |
|             latch             |          Thread          |        :x:         |                                                                                                                        |
|       [limits](#limits)       | Utility / Numeric Limits | :heavy_check_mark: |   [limits](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=2084657878)    |
|             list              |        Containers        |        :x:         |                                                                                                                        |
|            locale             |       Localization       |        :x:         |                                                                                                                        |
|          [map](#map)          |        Containers        | :heavy_check_mark: |     [map](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=2084657878)     |
|       [memory](#memory)       | Utility / Dynamic Memory | :heavy_check_mark: |   [memory](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=2084657878)    |
|        memory_resource        | Utility / Dynamic Memory |        :x:         |                                                                                                                        |
|        [mutex](#mutex)        |          Thread          | :heavy_check_mark: |    [mutex](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=2084657878)    |
|          [new](#new)          | Utility / Dynamic Memory | :heavy_check_mark: |     [new](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=2084657878)     |
|      [numbers](#numbers)      |         Numeric          | :heavy_check_mark: |   [numbers](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=641824361)    |
|      [numeric](#numeric)      |         Numeric          | :heavy_check_mark: |   [numeric](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1599843301)   |
|     [optional](#optional)     |         Utility          | :heavy_check_mark: |  [optional](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1965816070)   |
|            ostream            |       Input/Output       |        :x:         |                                                                                                                        |
|             queue             |        Containers        |        :x:         |                                                          TODO                                                          |
|            random             |         Numeric          |        :x:         |                                                                                                                        |
|            ranges             |          Ranges          |        :x:         |                                                          TODO                                                          |
|             regex             |   Regular Expressions    |        :x:         |                                                                                                                        |
|        [ratio](#ratio)        |         Numeric          | :heavy_check_mark: |    [ratio](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1383686309)    |
|       scoped_allocator        | Utility / Dynamic Memory |        :x:         |                                                                                                                        |
|        [scope](#scope)        |         Utility          | :heavy_check_mark: |                                                                                                                        |
|           semaphore           |          Thread          |        :x:         |                                                                                                                        |
|        source_location        |         Utility          |        :x:         |                                                                                                                        |
|          [set](#set)          |        Containers        | :heavy_check_mark: |     [set](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=930086747)      |
|         shared_mutex          |          Thread          |        :x:         |                                                                                                                        |
|         [span](#span)         |        Containers        | :heavy_check_mark: |    [span](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1750377555)     |
|        [stack](#stack)        |        Containers        | :heavy_check_mark: |    [stack](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=385809287)     |
|          stack_trace          |         Utility          |        :x:         |                                                                                                                        |
|           stdexcept           | Utility / Error Handling |        :x:         |                                                                                                                        |
|           streambuf           |       Input/Output       |        :x:         |                                                                                                                        |
|       [string](#string)       |         Strings          | :heavy_check_mark: |    [string](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=43463000)     |
|  [string_view](#string_view)  |         Strings          | :heavy_check_mark: | [string_view](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1803550736) |
|          stop_token           |          Thread          |        :x:         |                                                                                                                        |
|            sstream            |       Input/Output       |        :x:         |                                                                                                                        |
| [system_error](#system_error) | Utility / Error Handling | :heavy_check_mark: | [system_error](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=635426347) |
|          sync_stream          |       Input/Output       |        :x:         |                                                                                                                        |
|            thread             |          Thread          |        :x:         |                                                                                                                        |
|        [tuple](#tuple)        |         Utility          | :heavy_check_mark: |    [tuple](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=857929646)     |
|          type_index           |         Utility          |        :x:         |                                                                                                                        |
|           type_info           |         Utility          |        :x:         |                                                                                                                        |
|  [type_traits](#type_traits)  |         Utility          | :heavy_check_mark: | [type_traits](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1691010448) |
|         unordered_map         |        Containers        |        :x:         |                                                          TODO                                                          |
|         unordered_set         |        Containers        |        :x:         |                                                          TODO                                                          |
|      [utility](#utility)      |         Utility          | :heavy_check_mark: |   [utility](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1484976254)   |
|           valarray            |         Numeric          |        :x:         |                                                                                                                        |
|      [variant](#variant)      |         Utility          | :heavy_check_mark: |   [variant](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=503059518)    |
|       [vector](#vector)       |        Containers        | :heavy_check_mark: |   [vector](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1613833122)    |
|      [version](#version)      |         Utility          | :heavy_check_mark: |                                                                                                                        |
|      [warning](#warning)      |         Utility          | :heavy_check_mark: |                                                     Not standard.                                                      |

## Header Detail

### algorithm

- **Library:** Algorithms
- **Include:** [`etl/algorithm.hpp`](./etl/algorithm.hpp)
- **Tests:** [test_algorithm.cpp](./tests/test_algorithm.cpp)
- **Example:** [algorithm.cpp](./examples/algorithm.cpp)
- **Progress:** [algorithm](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1451123716)
- **Changes:**
  - Implementations are optimize for code size. See [etl::search vs. libstdc++ (godbolt.org)](https://godbolt.org/z/dY9zPf8cs) as an example.
  - All overloads using an execution policy are not implemented.

### array

- **Library:** Containers
- **Include:** [`etl/array.hpp`](./etl/array.hpp)
- **Tests:** [test_array.cpp](./tests/test_array.cpp)
- **Example:** [array.cpp](./examples/array.cpp)
- **Progress:** [array](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1320059600)
- **Changes:**
  - None

### bit

- **Library:** Numeric
- **Include:** [`etl/bit.hpp`](./etl/bit.hpp)
- **Tests:** [test_bit.cpp](./tests/test_bit.cpp)
- **Example:** [bit.cpp](./examples/bit.cpp)
- **Progress:** [bit](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1927645890)
- **Changes:**
  - None

### bitset

- **Library:** Utility
- **Include:** [`etl/bitset.hpp`](./etl/bitset.hpp)
- **Tests:** [test_bitset.cpp](./tests/test_bitset.cpp)
- **Example:** [bitset.cpp](./examples/bitset.cpp)
- **Progress:** [bitset](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=692946382)
- **Changes:**
  - TODO

### cassert

- **Library:** Utility / Error Handling
- **Include:** [`etl/cassert.hpp`](./etl/cassert.hpp)
- **Tests:** [test_cassert.cpp](./tests/test_cassert.cpp)
- **Example:** [cassert.cpp](./examples/cassert.cpp)
- **Progress:** [cassert](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=460740183)
- **Changes:**
  - None

### cctype

- **Library:** Strings
- **Include:** [`etl/cctype.hpp`](./etl/cctype.hpp)
- **Tests:** [test_cctype.cpp](./tests/test_cctype.cpp)
- **Example:** TODO
- **Progress:** [cctype](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=522168028)
- **Changes:**
  - Locale independent

### cfloat

- **Library:** Utility / Numeric Limits
- **Include:** [`etl/cfloat.hpp`](./etl/cfloat.hpp)
- **Tests:** [test_cfloat.cpp](./tests/test_cfloat.cpp)
- **Example:** TODO
- **Progress:** [cfloat](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1012838019)
- **Changes:**
  - None

### charconv

- **Library:** Strings
- **Include:** [`etl/charconv.hpp`](./etl/charconv.hpp)
- **Tests:** [test_charconv.cpp](./tests/test_charconv.cpp)
- **Example:** TODO
- **Progress:** [charconv](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=345887816)
- **Changes:**
  - None

### chrono

- **Library:** Utility
- **Include:** [`etl/chrono.hpp`](./etl/chrono.hpp)
- **Tests:** [test_chrono.cpp](./tests/test_chrono.cpp)
- **Example:** [chrono.cpp](./examples/chrono.cpp)
- **Progress:** [chrono](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1279150724)
- **Changes:**
  - No clocks are implemented. You have to provide your own, which must at least meet the requirements of [Clock](https://en.cppreference.com/w/cpp/named_req/Clock).

### climits

- **Library:** Utility / Numeric Limits
- **Include:** [`etl/climits.hpp`](./etl/climits.hpp)
- **Tests:** [test_climits.cpp](./tests/test_climits.cpp)
- **Example:** TODO
- **Progress:** [climits](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1904156895)
- **Changes:**
  - None

### cmath

- **Library:** Numeric
- **Include:** [`etl/cmath.hpp`](./etl/cmath.hpp)
- **Tests:** [test_cmath.cpp](./tests/test_cmath.cpp)
- **Example:** TODO
- **Progress:** [cmath](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=868070087)
- **Changes:**
  - None

### concepts

- **Library:** Concepts
- **Include:** [`etl/concepts.hpp`](./etl/concepts.hpp)
- **Tests:** [test_concepts.cpp](./tests/test_concepts.cpp)
- **Example:** TODO
- **Progress:** [concepts](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=73781271)
- **Changes:**
  - None

### cstdarg

- **Library:** Utility
- **Include:** [`etl/cstdarg.hpp`](./etl/cstdarg.hpp)
- **Tests:** [test_cstdarg.cpp](./tests/test_cstdarg.cpp)
- **Example:** TODO
- **Progress:** [cstdarg](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1280782172)
- **Changes:**
  - None

### cstddef

- **Library:** Utility
- **Include:** [`etl/cstddef.hpp`](./etl/cstddef.hpp)
- **Tests:** [test_cstddef.cpp](./tests/test_cstddef.cpp)
- **Example:** TODO
- **Progress:** [cstddef](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1660546405)
- **Changes:**
  - None

### cstdint

- **Library:** Utility / Numeric Limits
- **Include:** [`etl/cstdint.hpp`](./etl/cstdint.hpp)
- **Tests:** [test_cstdint.cpp](./tests/test_cstdint.cpp)
- **Example:** TODO
- **Progress:** [cstdint](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=2005735528)
- **Changes:**
  - None

### cstdio

- **Library:** Input/Output
- **Include:** [`etl/cstdio.hpp`](./etl/cstdio.hpp)
- **Tests:** [test_cstdio.cpp](./tests/test_cstdio.cpp)
- **Example:** TODO
- **Progress:** [cstdio](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1576270107)
- **Changes:**
  - TODO

### cstdlib

- **Library:** Utility
- **Include:** [`etl/cstdlib.hpp`](./etl/cstdlib.hpp)
- **Tests:** [test_cstdlib.cpp](./tests/test_cstdlib.cpp)
- **Example:** TODO
- **Progress:** [cstdlib](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1705155517)
- **Changes:**
  - None

### cstring

- **Library:** Strings
- **Include:** [`etl/cstring.hpp`](./etl/cstring.hpp)
- **Tests:** [test_cstring.cpp](./tests/test_cstring.cpp)
- **Example:** TODO
- **Progress:** [cstring](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1824871501)
- **Changes:**
  - TODO

### ctime

- **Library:** Utility
- **Include:** [`etl/ctime.hpp`](./etl/ctime.hpp)
- **Tests:** [test_ctime.cpp](./tests/test_ctime.cpp)
- **Example:** TODO
- **Progress:** [ctime](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1082109762)
- **Changes:**
  - TODO

### expected

- **Library:** Utility / Error Handling
- **Include:** [`etl/expected.hpp`](./etl/expected.hpp)
- **Tests:** [test_expected.cpp](./tests/test_expected.cpp)
- **Example:** TODO
- **Progress:** [expected](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1624993362)
- **Changes:**
  - TODO

### format

- **Library:** Strings
- **Include:** [`etl/format.hpp`](./etl/format.hpp)
- **Tests:** [test_format.cpp](./tests/test_format.cpp)
- **Example:** TODO
- **Progress:** [format](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=159875067)
- **Changes:**
  - WIP. Don't use.

### functional

- **Library:** Utility
- **Include:** [`etl/functional.hpp`](./etl/functional.hpp)
- **Tests:** [test_functional.cpp](./tests/test_functional.cpp)
- **Example:** TODO
- **Progress:** [functional](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=291953395)
- **Changes:**
  - TODO

### ios

- **Library:** Input/Output
- **Include:** [`etl/ios.hpp`](./etl/ios.hpp)
- **Tests:** [test_ios.cpp](./tests/test_ios.cpp)
- **Example:** TODO
- **Progress:** [ios](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=2084657878)
- **Changes:**
  - TODO

### iterator

- **Library:** Iterator
- **Include:** [`etl/iterator.hpp`](./etl/iterator.hpp)
- **Tests:** [test_iterator.cpp](./tests/test_iterator.cpp)
- **Example:** TODO
- **Progress:** [iterator](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1722716093)
- **Changes:**
  - TODO

### limits

- **Library:** Utility / Numeric Limits
- **Include:** [`etl/limits.hpp`](./etl/limits.hpp)
- **Tests:** [test_limits.cpp](./tests/test_limits.cpp)
- **Example:** TODO
- **Progress:** [limits](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1966217100)
- **Changes:**
  - None

### map

- **Library:** Containers
- **Include:** [`etl/map.hpp`](./etl/map.hpp)
- **Tests:** [test_map.cpp](./tests/test_map.cpp)
- **Example:** [map.cpp](./examples/map.cpp)
- **Progress:** [map](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1845210258)
- **Changes:**
  - Renamed `map` to `static_map`. Fixed compile-time capacity.

### memory

- **Library:** Utility / Dynamic Memory
- **Include:** [`etl/memory.hpp`](./etl/memory.hpp)
- **Tests:** [test_memory.cpp](./tests/test_memory.cpp)
- **Example:** [memory.cpp](./examples/memory.cpp)
- **Progress:** [memory](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1321444012)
- **Changes:**
  - Non-standard class templates `small_ptr` (compressed pointer) & `pointer_int_pair` (pointer + integer) are provided.

### mutex

- **Library:** Thread
- **Include:** [`etl/mutex.hpp`](./etl/mutex.hpp)
- **Tests:** [test_mutex.cpp](./tests/test_mutex.cpp)
- **Example:** [mutex.cpp](./examples/mutex.cpp)
- **Progress:** [mutex](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=965791558)
- **Changes:**
  - Only RAII lock types are implemented. You have to provide a mutex type that at least meets the [BasicLockable](https://en.cppreference.com/w/cpp/named_req/BasicLockable) requirements.

### new

- **Library:** Utility / Dynamic Memory
- **Include:** [`etl/new.hpp`](./etl/new.hpp)
- **Tests:** [test_new.cpp](./tests/test_new.cpp)
- **Example:** TODO
- **Progress:** [new](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1146466573)
- **Changes:**
  - None
  - If the standard `<new>` is availble it is used to define the global placement new functions to avoid ODR violations when mixing `std` & `etl` headers.

### numbers

- **Library:** Numeric
- **Include:** [`etl/numbers.hpp`](./etl/numbers.hpp)
- **Tests:** [test_numbers.cpp](./tests/test_numbers.cpp)
- **Example:** TODO
- **Progress:** [numbers](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=641824361)
- **Changes:**
  - None

### numeric

- **Library:** Numeric
- **Include:** [`etl/numeric.hpp`](./etl/numeric.hpp)
- **Tests:** [test_numeric.cpp](./tests/test_numeric.cpp)
- **Example:** [numeric.cpp](./examples/numeric.cpp)
- **Progress:** [numeric](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1599843301)
- **Changes:**
  - Implementations are optimize for code size. See [etl::search vs. libstdc++ (godbolt.org)](https://godbolt.org/z/dY9zPf8cs) as an example.
  - All overloads using an execution policy are not implemented.

### optional

- **Library:** Utility
- **Include:** [`etl/optional.hpp`](./etl/optional.hpp)
- **Tests:** [test_optional.cpp](./tests/test_optional.cpp)
- **Example:** [optional.cpp](./examples/optional.cpp)
- **Progress:** [optional](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1965816070)
- **Changes:**
  - TODO

### ratio

- **Library:** Numeric
- **Include:** [`etl/ratio.hpp`](./etl/ratio.hpp)
- **Tests:** [test_ratio.cpp](./tests/test_ratio.cpp)
- **Example:** [ratio.cpp](./examples/ratio.cpp)
- **Progress:** [ratio](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1383686309)
- **Changes:**
  - None

### scope

- **Library:** Utility
- **Include:** [`etl/scope.hpp`](./etl/scope.hpp)
- **Tests:** [test_scope.cpp](./tests/test_scope.cpp)
- **Example:** TODO
- **Progress:** TODO
- **Reference:** [en.cppreference.com/w/cpp/experimental/scope_exit](https://en.cppreference.com/w/cpp/experimental/scope_exit)
- **Changes:**
  - Based on [p0052r8](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0052r8.pdf)
  - Only provides `scope_exit`

### set

- **Library:** Containers
- **Include:** [`etl/set.hpp`](./etl/set.hpp)
- **Tests:** [test_set.cpp](./tests/test_set.cpp)
- **Example:** [set.cpp](./examples/set.cpp)
- **Progress:** [set](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=930086747)
- **Changes:**
  - Renamed `set` to `static_set`. Fixed compile-time capacity.
  - If `is_trivial_v<T>`, then `is_trivially_copyable_v<static_set<T, Capacity>>`
  - If `is_trivial_v<T>`, then `is_trivially_destructible_v<static_set<T, Capacity>>`

### span

- **Library:** Containers
- **Include:** [`etl/span.hpp`](./etl/span.hpp)
- **Tests:** [test_span.cpp](./tests/test_span.cpp)
- **Example:** TODO
- **Progress:** [span](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1750377555)
- **Changes:**
  - None. Available in C++17.

### stack

- **Library:** Containers
- **Include:** [`etl/stack.hpp`](./etl/stack.hpp)
- **Tests:** [test_stack.cpp](./tests/test_stack.cpp)
- **Example:** TODO
- **Progress:** [stack](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=385809287)
- **Changes:**
  - None. Works with `static_vector`.

### string

- **Library:** Strings
- **Include:** [`etl/string.hpp`](./etl/string.hpp)
- **Tests:** [test_string.cpp](./tests/test_string.cpp)
- **Example:** [string.cpp](./examples/string.cpp)
- **Progress:** [string](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=43463000)
- **Changes:**
  - Only implemeted for type `char` at the moment.
  - Renamed `basic_string` to `basic_static_string`. Fixed compile-time capacity.

### string_view

- **Library:** Strings
- **Include:** [`etl/string_view.hpp`](./etl/string_view.hpp)
- **Tests:** [test_string_view.cpp](./tests/test_string_view.cpp)
- **Example:** [string_view.cpp](./examples/string_view.cpp)
- **Progress:** [string_view](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1803550736)
- **Changes:**
  - None
  - Only implemeted for type `char` at the moment.

### system_error

- **Library:** Utility / Error Handling
- **Include:** [`etl/system_error.hpp`](./etl/system_error.hpp)
- **Tests:** [test_system_error.cpp](./tests/test_system_error.cpp)
- **Example:** TODO
- **Progress:** [system_error](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=635426347)
- **Changes:**
  - Only provides `errc` enum and helper traits.

### tuple

- **Library:** Utility
- **Include:** [`etl/tuple.hpp`](./etl/tuple.hpp)
- **Tests:** [test_tuple.cpp](./tests/test_tuple.cpp)
- **Example:** [tuple.cpp](./examples/tuple.cpp)
- **Progress:** [tuple](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=857929646)
- **Changes:**
  - Broken at the moment.

### type_traits

- **Library:** Utility
- **Include:** [`etl/type_traits.hpp`](./etl/type_traits.hpp)
- **Tests:** [test_type_traits.cpp](./tests/test_type_traits.cpp)
- **Example:** [type_traits.cpp](./examples/type_traits.cpp)
- **Progress:** [type_traits](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1691010448)
- **Changes:**
  - None

### utility

- **Library:** Utility
- **Include:** [`etl/utility.hpp`](./etl/utility.hpp)
- **Tests:** [test_utility.cpp](./tests/test_utility.cpp)
- **Example:** [utility.cpp](./examples/utility.cpp)
- **Progress:** [utility](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1484976254)
- **Changes:**
  - None

### variant

- **Library:** Utility
- **Include:** [`etl/variant.hpp`](./etl/variant.hpp)
- **Tests:** [test_variant.cpp](./tests/test_variant.cpp)
- **Example:** TODO
- **Progress:** [variant](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=503059518)
- **Changes:**
  - Broken at the moment.

### vector

- **Library:** Containers
- **Include:** [`etl/vector.hpp`](./etl/vector.hpp)
- **Tests:** [test_vector.cpp](./tests/test_vector.cpp)
- **Example:** [vector.cpp](./examples/vector.cpp)
- **Progress:** [vector](https://docs.google.com/spreadsheets/d/1-qwa7tFnjFdgY9XKBy2fAsDozAfG8lXsJXHwA_ITQqM/edit#gid=1613833122)
- **Changes:**
  - Renamed `vector` to `static_vector`. Fixed compile-time capacity.
  - Based on `P0843r3` and the reference implementation from [github.com/gnzlbg/static_vector](https://github.com/gnzlbg/static_vector).
  - If `is_trivial_v<T>`, then `is_trivially_copyable_v<static_vector<T, Capacity>>`
  - If `is_trivial_v<T>`, then `is_trivially_destructible_v<static_vector<T, Capacity>>`

### version

- **Library:** Utility
- **Include:** [`etl/version.hpp`](./etl/version.hpp)
- **Tests:** [test_version.cpp](./tests/test_version.cpp)

Get access to all intrinsic macros & library version macro and constants.

```cpp
#include "etl/version.hpp"

#include <stdio.h>

auto main() -> int
{
#if defined(TETL_MSVC)
  puts("msvc");
#else
  puts("other compiler");
#endif
  return 0;
}
```

### warning

- **Library:** Utility
- **Include:** [`etl/warning.hpp`](./etl/warning.hpp)
- **Tests:** [test_warning.cpp](./tests/test_warning.cpp)

```cpp
#include "etl/warning.hpp"

auto main(int argc, char** argv) -> int
{
  // Explicitly ignore unused arguments or variables.
  etl::ignore_unused(argc, argv);
  return 0;
}
```
