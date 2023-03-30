// SPDX-License-Identifier: BSL-1.0

#ifndef TETL_ALGORITHM_GENERATE_HPP
#define TETL_ALGORITHM_GENERATE_HPP

namespace etl {

/// \brief Assigns each element in range `[first, last)` a value generated by
/// the given function object g.
///
/// \param first The range of elements to generate.
/// \param last The range of elements to generate.
/// \param g Generator function object that will be called.
///
/// https://en.cppreference.com/w/cpp/algorithm/generate
template <typename ForwardIt, typename Generator>
constexpr auto generate(ForwardIt first, ForwardIt last, Generator g) -> void
{
    for (; first != last; ++first) { *first = g(); }
}

} // namespace etl

#endif // TETL_ALGORITHM_GENERATE_HPP
