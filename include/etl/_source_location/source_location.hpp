// SPDX-License-Identifier: BSL-1.0

#ifndef TETL_SOURCE_LOCATION_SOURCE_LOCATION_HPP
#define TETL_SOURCE_LOCATION_SOURCE_LOCATION_HPP

#include "etl/_config/all.hpp"

#include "etl/_cstdint/uint_least_t.hpp"
#include "etl/_version/language_standard.hpp"

namespace etl {

#if defined(__cpp_consteval)

/// \brief Source location
/// \include source_location.cpp
struct source_location {
    [[nodiscard]] static consteval auto current(uint_least32_t const line = TETL_BUILTIN_LINE(),
        uint_least32_t const column = TETL_BUILTIN_COLUMN(), char const* const file = TETL_BUILTIN_FILE(),
        char const* const function = TETL_BUILTIN_FUNCTION()) noexcept -> source_location
    {
        auto result      = source_location {};
        result.line_     = line;
        result.column_   = column;
        result.file_     = file;
        result.function_ = function;
        return result;
    }

    constexpr source_location() noexcept = default;

    [[nodiscard]] constexpr auto line() const noexcept -> etl::uint_least32_t { return line_; }

    [[nodiscard]] constexpr auto column() const noexcept -> etl::uint_least32_t { return column_; }

    [[nodiscard]] constexpr auto file_name() const noexcept -> char const* { return file_; }

    [[nodiscard]] constexpr auto function_name() const noexcept -> char const* { return function_; }

private:
    etl::uint_least32_t line_ {};
    etl::uint_least32_t column_ {};
    char const* file_     = "";
    char const* function_ = "";
};

#endif

} // namespace etl

#endif // TETL_SOURCE_LOCATION_SOURCE_LOCATION_HPP
