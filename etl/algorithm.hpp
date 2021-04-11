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

/// \file algorithm.hpp
/// \example algorithm.cpp

#ifndef TAETL_ALGORITHM_HPP
#define TAETL_ALGORITHM_HPP

#include "etl/cassert.hpp"
#include "etl/cstddef.hpp"
#include "etl/functional.hpp"
#include "etl/iterator.hpp"
#include "etl/type_traits.hpp"

#include "etl/detail/algo_search.hpp"
#include "etl/detail/algo_swap.hpp"

namespace etl
{
/// \brief Swaps the values of the elements the given iterators are pointing to.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/iter_swap
template <typename ForwardIt1, typename ForwardIt2>
constexpr auto iter_swap(ForwardIt1 a, ForwardIt2 b) -> void
{
  using etl::swap;
  swap(*a, *b);
}

/// \brief Exchanges elements between range [first1 ,last1) and another range
/// starting at first2.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/swap_ranges
/// \param first1 the first range of elements to swap
/// \param last1 the first range of elements to swap
/// \param first2 beginning of the second range of elements to swap
template <typename ForwardIter1, typename ForwardIter2>
constexpr auto swap_ranges(ForwardIter1 first1, ForwardIter1 last1,
                           ForwardIter2 first2) -> ForwardIter2
{
  while (first1 != last1)
  {
    iter_swap(first1, first2);
    ++first1;
    ++first2;
  }

  return first2;
}

/// \brief Moves the elements in the range [first, last), to another range
/// beginning at destination, starting from first and proceeding to last - 1.
/// After this operation the elements in the moved-from range will still contain
/// valid values of the appropriate type, but not necessarily the same values as
/// before the move.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/move
/// \param first The range of elements to move.
/// \param last The range of elements to move.
/// \param destination The beginning of the destination range.
/// \returns Output iterator to the element past the last element moved.
template <typename InputIter, typename OutputIter>
constexpr auto move(InputIter first, InputIter last, OutputIter destination)
  -> OutputIter
{
  for (; first != last; ++first, ++destination) { *destination = move(*first); }
  return destination;
}

/// \brief Moves the elements from the range [first, last), to another range
/// ending at destination. The elements are moved in reverse order (the last
/// element is moved first), but their relative order is preserved.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/move_backward
/// \param first The range of elements to move.
/// \param last The range of elements to move.
/// \param destination End of the destination range.
/// \returns Iterator in the destination range, pointing at the last element
/// moved.
template <typename BidirIter1, typename BidirIter2>
constexpr auto move_backward(BidirIter1 first, BidirIter1 last,
                             BidirIter2 destination) -> BidirIter2
{
  for (; first != last;) { *(--destination) = move(*--last); }
  return destination;
}

/// \brief Applies the given function object f to the result of dereferencing
/// every iterator in the range [first, last) in order.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/for_each
/// \param first The range to apply the function to.
/// \param last The range to apply the function to.
/// \param f Function object, to be applied to the result of dereferencing every
/// iterator in the range.
template <typename InputIter, typename UnaryFunction>
constexpr auto for_each(InputIter first, InputIter last,
                        UnaryFunction f) noexcept -> UnaryFunction
{
  for (; first != last; ++first) { f(*first); }
  return f;
}

/// \brief Applies the given function object f to the result of dereferencing
/// every iterator in the range [first, first + n] in order.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/for_each_n
/// \param first The beginning of the range to apply the function to.
/// \param n The number of elements to apply the function to.
/// \param f Function object, to be applied to the result of dereferencing every
/// iterator in the range.
template <typename InputIter, typename Size, typename UnaryFunction>
constexpr auto for_each_n(InputIter first, Size n, UnaryFunction f) noexcept
  -> InputIter
{
  for (Size i = 0; i < n; ++first, ++i) { f(*first); }
  return first;
}

/// \brief Applies the given function to a range and stores the result in
/// another range, beginning at dest. The unary operation op is applied to
/// the range defined by [first, last).
///
/// \details https://en.cppreference.com/w/cpp/algorithm/transform
/// \param first The first range of elements to transform.
/// \param last The first range of elements to transform.
/// \param dest The beginning of the destination range, may be equal to first.
/// \param op Unary operation function object that will be applied.
/// \group transform
/// \module algorithm
template <typename InputIter, typename OutputIter, typename UnaryOperation>
constexpr auto transform(InputIter first, InputIter last, OutputIter dest,
                         UnaryOperation op) -> OutputIter
{
  for (; first != last; ++first, ++dest) { *dest = op(*first); }
  return dest;
}

/// \brief Applies the given function to a range and stores the result in
/// another range, beginning at destination. The binary operation op is applied
/// to pairs of elements from two ranges: one defined by [first1, last1) and the
/// other beginning at first2.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/transform
/// \param first1 The first range of elements to transform.
/// \param last1 The first range of elements to transform.
/// \param first2 The beginning of the second range of elements to transform.
/// \param dest The beginning of the destination range, may be equal to first.
/// \param op Unary operation function object that will be applied.
/// \group transform
/// \module algorithm
template <typename InputIter1, typename InputIter2, typename OutputIter,
          typename BinaryOperation>
constexpr auto transform(InputIter1 first1, InputIter1 last1, InputIter2 first2,
                         OutputIter dest, BinaryOperation op) -> OutputIter
{
  for (; first1 != last1; ++first1, ++first2, ++dest)
  {
    *dest = op(*first1, *first2);
  }
  return dest;
}

/// \brief Assigns each element in range [first, last) a value generated by the
/// given function object g.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/generate
/// \param first The range of elements to generate.
/// \param last The range of elements to generate.
/// \param g Generator function object that will be called.
template <typename ForwardIter, typename Generator>
constexpr auto generate(ForwardIter first, ForwardIter last, Generator g)
  -> void
{
  for (; first != last; ++first) { *first = g(); }
}

/// \brief Assigns values, generated by given function object g, to the first
/// count elements in the range beginning at first, if count > 0. Does nothing
/// otherwise.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/generate_n
/// \param first The range of elements to generate.
/// \param count Number of the elements to generate.
/// \param g Generator function object that will be called.
template <typename OutputIter, typename SizeT, typename Generator>
constexpr auto generate_n(OutputIter first, SizeT count, Generator g)
  -> OutputIter
{
  for (; count > 0; ++first, --count) { *first = g(); }
  return first;
}

/// \brief Returns the number of elements in the range [first, last) satisfying
/// specific criteria. Counts the elements that are equal to value.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/count
/// \param first The range of elements to examine.
/// \param last The range of elements to examine.
/// \param value The value to search for.
/// \group count
/// \module algorithm
template <typename InputIter, typename T>
[[nodiscard]] constexpr auto count(InputIter first, InputIter last,
                                   T const& value) ->
  typename iterator_traits<InputIter>::difference_type
{
  auto result = typename iterator_traits<InputIter>::difference_type {0};
  for (; first != last; ++first)
  {
    if (*first == value) { ++result; }
  }
  return result;
}

/// \brief Returns the number of elements in the range [first, last) satisfying
/// specific criteria. Counts elements for which predicate p returns true.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/count
/// \param first The range of elements to examine.
/// \param last The range of elements to examine.
/// \param p Unary predicate which returns ​true for the required elements.
/// \group count
/// \module algorithm
template <typename InputIter, typename UnaryPredicate>
[[nodiscard]] constexpr auto count_if(InputIter first, InputIter last,
                                      UnaryPredicate p) ->
  typename iterator_traits<InputIter>::difference_type
{
  auto result = typename iterator_traits<InputIter>::difference_type {0};
  for (; first != last; ++first)
  {
    if (p(*first)) { ++result; }
  }
  return result;
}

/// \brief Returns the first mismatching pair of elements from two ranges: one
/// defined by [first1, last1) and another defined by [first2,last2). If last2
/// is not provided (overloads (1-4)), it denotes first2 + (last1 - first1).
/// Elements are compared using the given binary predicate pred.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/mismatch
/// \param first1 The first range of the elements.
/// \param last1 The first range of the elements.
/// \param first2 The second range of the elements.
/// \param pred Binary predicate which returns ​true if the elements should be
/// treated as equal.
/// \group mismatch
/// \module algorithm
template <typename InputIter1, typename InputIter2, typename BinaryPredicate>
[[nodiscard]] constexpr auto mismatch(InputIter1 first1, InputIter1 last1,
                                      InputIter2 first2, BinaryPredicate pred)
  -> pair<InputIter1, InputIter2>
{
  for (; first1 != last1; ++first1, ++first2)
  {
    if (!pred(*first1, *first2)) { break; }
  }

  return pair<InputIter1, InputIter2>(first1, first2);
}

/// \brief Returns the first mismatching pair of elements from two ranges: one
/// defined by [first1, last1) and another defined by [first2,last2). If last2
/// is not provided (overloads (1-4)), it denotes first2 + (last1 - first1).
/// Elements are compared using operator==.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/mismatch
/// \param first1 The first range of the elements.
/// \param last1 The first range of the elements.
/// \param first2 The second range of the elements.
/// \group mismatch
/// \module algorithm
template <typename InputIter1, typename InputIter2>
[[nodiscard]] constexpr auto mismatch(InputIter1 first1, InputIter1 last1,
                                      InputIter2 first2)
  -> pair<InputIter1, InputIter2>
{
  return mismatch(first1, last1, first2, equal_to<> {});
}

/// \brief Returns the first mismatching pair of elements from two ranges: one
/// defined by [first1, last1) and another defined by [first2, last2). Elements
/// are compared using the given binary predicate pred.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/mismatch
/// \param first1 The first range of the elements.
/// \param last1 The first range of the elements.
/// \param first2 The second range of the elements.
/// \param last2 The second range of the elements.
/// \param pred Binary predicate which returns ​true if the elements should be
/// treated as equal.
/// \group mismatch
/// \module algorithm
template <typename InputIter1, typename InputIter2, typename BinaryPredicate>
[[nodiscard]] constexpr auto mismatch(InputIter1 first1, InputIter1 last1,
                                      InputIter2 first2, InputIter2 last2,
                                      BinaryPredicate pred)
  -> pair<InputIter1, InputIter2>
{
  for (; first1 != last1 && first2 != last2; ++first1, ++first2)
  {
    if (!pred(*first1, *first2)) { break; }
  }

  return pair<InputIter1, InputIter2>(first1, first2);
}

/// \brief Returns the first mismatching pair of elements from two ranges: one
/// defined by [first1, last1) and another defined by [first2,last2). Elements
/// are compared using operator==.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/mismatch
/// \param first1 The first range of the elements.
/// \param last1 The first range of the elements.
/// \param first2 The second range of the elements.
/// \param last2 The second range of the elements.
/// \group mismatch
/// \module algorithm
template <typename InputIter1, typename InputIter2>
[[nodiscard]] constexpr auto mismatch(InputIter1 first1, InputIter1 last1,
                                      InputIter2 first2, InputIter2 last2)
  -> pair<InputIter1, InputIter2>
{
  return mismatch(first1, last1, first2, last2, equal_to<> {});
}

/// \brief Searches the range [first, last) for two consecutive equal elements.
/// Elements are compared using the given binary predicate p.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/adjacent_find
/// \param first The range of elements to examine.
/// \param last The range of elements to examine.
/// \param pred Binary predicate which returns ​true if the elements should be
/// treated as equal.
/// \group adjacent_find
/// \module algorithm
template <typename ForwardIter, typename BinaryPredicate>
[[nodiscard]] constexpr auto adjacent_find(ForwardIter first, ForwardIter last,
                                           BinaryPredicate pred) -> ForwardIter
{
  if (first == last) { return last; }

  auto next = first;
  ++next;

  for (; next != last; ++next, ++first)
  {
    if (pred(*first, *next)) { return first; }
  }

  return last;
}

/// \brief Searches the range [first, last) for two consecutive equal elements.
/// Elements are compared using operator==.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/adjacent_find
/// \param first The range of elements to examine.
/// \param last The range of elements to examine.
/// \group adjacent_find
/// \module algorithm
template <typename ForwardIt>
[[nodiscard]] constexpr auto adjacent_find(ForwardIt first, ForwardIt last)
  -> ForwardIt
{
  return adjacent_find(first, last, equal_to<> {});
}

/// \brief Searches for an element equal to value.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/find
/// \param first The range of elements to examine.
/// \param last The range of elements to examine.
/// \param value Value to compare the elements to.
/// \group find
/// \module algorithm
template <typename InputIter, typename T>
[[nodiscard]] constexpr auto find(InputIter first, InputIter last,
                                  T const& value) noexcept -> InputIter
{
  for (; first != last; ++first)
  {
    if (*first == value) { return first; }
  }
  return last;
}

/// \brief Searches for an element for which predicate p returns true
///
/// \details https://en.cppreference.com/w/cpp/algorithm/find
/// \param first The range of elements to examine.
/// \param last The range of elements to examine.
/// \param pred Unary predicate which returns ​true for the required element.
/// \group find
/// \module algorithm
template <typename InputIter, typename UnaryPredicate>
[[nodiscard]] constexpr auto find_if(InputIter first, InputIter last,
                                     UnaryPredicate pred) noexcept -> InputIter
{
  for (; first != last; ++first)
  {
    if (pred(*first)) { return first; }
  }
  return last;
}

/// \brief Searches for an element for which predicate q returns false
///
/// \details https://en.cppreference.com/w/cpp/algorithm/find
/// \param first The range of elements to examine.
/// \param last The range of elements to examine.
/// \param pred Unary predicate which returns ​true for the required element.
/// \group find
/// \module algorithm
template <typename InputIter, typename UnaryPredicate>
[[nodiscard]] constexpr auto find_if_not(InputIter first, InputIter last,
                                         UnaryPredicate pred) noexcept
  -> InputIter
{
  for (; first != last; ++first)
  {
    if (!pred(*first)) { return first; }
  }
  return last;
}

/// \brief Searches the range [first, last) for any of the elements in the range
/// [sFirst, sLast). Elements are compared using the given binary predicate
/// pred.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/find_first_of
/// \param first The range of elements to examine.
/// \param last The range of elements to examine.
/// \param sFirst The range of elements to search for.
/// \param sLast The range of elements to search for.
/// \param pred Binary predicate which returns ​true if the elements should be
/// treated as equal.
/// \group find_first_of
/// \module algorithm
template <typename InputIter, typename ForwardIter, typename BinaryPredicate>
[[nodiscard]] constexpr auto
find_first_of(InputIter first, InputIter last, ForwardIter sFirst,
              ForwardIter sLast, BinaryPredicate pred) -> InputIter
{
  for (; first != last; ++first)
  {
    for (auto it = sFirst; it != sLast; ++it)
    {
      if (pred(*first, *it)) { return first; }
    }
  }

  return last;
}

/// \brief Searches the range [first, last) for any of the elements in the range
/// [sFirst, sLast). Elements are compared using operator==.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/find_first_of
/// \param first The range of elements to examine.
/// \param last The range of elements to examine.
/// \param sFirst The range of elements to search for.
/// \param sLast The range of elements to search for.
/// \group find_first_of
/// \module algorithm
template <typename InputIter, typename ForwardIter>
[[nodiscard]] constexpr auto find_first_of(InputIter first, InputIter last,
                                           ForwardIter sFirst,
                                           ForwardIter sLast) -> InputIter
{
  return find_first_of(first, last, sFirst, sLast, equal_to<> {});
}

/// \brief Searches for the first occurrence of the sequence of elements
/// [sFirst, sLast) in the range [first, last). Elements are compared using the
/// given binary predicate pred.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/search
/// \param first The range of elements to examine.
/// \param last The range of elements to examine.
/// \param sFirst The range of elements to search for.
/// \param sLast The range of elements to search for.
/// \param pred Binary predicate which returns ​true if the elements should be
/// treated as equal.
/// \group search
/// \module algorithm
template <typename ForwardIter1, typename ForwardIter2,
          typename BinaryPredicate>
[[nodiscard]] constexpr auto search(ForwardIter1 first, ForwardIter1 last,
                                    ForwardIter2 sFirst, ForwardIter2 sLast,
                                    BinaryPredicate pred) -> ForwardIter1
{
  return detail::search_impl(first, last, sFirst, sLast, pred);
}

/// \brief Searches for the first occurrence of the sequence of elements
/// [sFirst, sLast) in the range [first, last). Elements are compared using
/// operator==.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/search
/// \param first The range of elements to examine.
/// \param last The range of elements to examine.
/// \param sFirst The range of elements to search for.
/// \param sLast The range of elements to search for.
/// \group search
/// \module algorithm
template <typename ForwardIter1, typename ForwardIter2>
[[nodiscard]] constexpr auto search(ForwardIter1 first, ForwardIter1 last,
                                    ForwardIter2 sFirst, ForwardIter2 sLast)
  -> ForwardIter1
{
  return search(first, last, sFirst, sLast, equal_to<> {});
}

/// \brief Searches the sequence [first, last) for the pattern specified in the
/// constructor of searcher.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/search
/// \param first The range of elements to examine.
/// \param last The range of elements to examine.
/// \param searcher The searcher encapsulating the search algorithm and the
/// pattern to look for.
/// \group search
/// \module algorithm
template <typename ForwardIter, typename Searcher>
[[nodiscard]] constexpr auto search(ForwardIter first, ForwardIter last,
                                    Searcher const& searcher) -> ForwardIter
{
  return searcher(first, last).first;
}

/// \brief Searches the range [first, last) for the first sequence of count
/// identical elements, each equal to the given value.
/// \group search_n
/// \module algorithm
template <typename ForwardIter, typename Size, typename ValueT,
          typename BinaryPredicate>
[[nodiscard]] constexpr auto search_n(ForwardIter first, ForwardIter last,
                                      Size count, ValueT const& value,
                                      BinaryPredicate pred) -> ForwardIter
{
  if (count <= Size {}) { return first; }

  auto localCounter = Size {};
  ForwardIter found = nullptr;

  for (; first != last; ++first)
  {
    if (pred(*first, value))
    {
      localCounter++;
      if (found == nullptr) { found = first; }
    }
    else
    {
      localCounter = 0;
    }

    if (localCounter == count) { return found; }
  }

  return last;
}

/// \brief Searches the range [first, last) for the first sequence of count
/// identical elements, each equal to the given value.
/// \group search_n
/// \module algorithm
template <typename ForwardIter, typename Size, typename ValueT>
[[nodiscard]] constexpr auto search_n(ForwardIter first, ForwardIter last,
                                      Size count, ValueT const& value)
  -> ForwardIter
{
  return search_n(first, last, count, value, equal_to<> {});
}

/// \brief Searches for the last occurrence of the sequence [sFirst, sLast) in
/// the range [first, last). Elements are compared using the given binary
/// predicate p.
///
/// \param first The range of elements to examine
/// \param last The range of elements to examine
/// \param sFirst The range of elements to search for
/// \param sLast The range of elements to search for
/// \param p Binary predicate
/// \return Iterator to the beginning of last occurrence of the sequence
/// [sFirst, sLast) in range [first, last). If [sFirst, sLast) is empty or if
/// no such sequence is found, last is returned.
/// \group find_end
/// \module algorithm
template <typename ForwardIter1, typename ForwardIter2,
          typename BinaryPredicate>
[[nodiscard]] constexpr auto find_end(ForwardIter1 first, ForwardIter1 last,
                                      ForwardIter2 sFirst, ForwardIter2 sLast,
                                      BinaryPredicate p) -> ForwardIter1
{
  if (sFirst == sLast) { return last; }
  auto result = last;
  while (true)
  {
    auto newResult = search(first, last, sFirst, sLast, p);
    if (newResult == last) { break; }
    result = newResult;
    first  = result;
    ++first;
  }
  return result;
}

/// \brief Searches for the last occurrence of the sequence [sFirst, sLast) in
/// the range [first, last). Elements are compared using operator==.
///
/// \param first The range of elements to examine
/// \param last The range of elements to examine
/// \param sFirst The range of elements to search for
/// \param sLast The range of elements to search for
/// \return Iterator to the beginning of last occurrence of the sequence
/// [sFirst, sLast) in range [first, last). If [sFirst, sLast) is empty or if
/// no such sequence is found, last is returned.
/// \group find_end
/// \module algorithm
template <typename ForwardIter1, typename ForwardIter2>
[[nodiscard]] constexpr auto find_end(ForwardIter1 first, ForwardIter1 last,
                                      ForwardIter2 sFirst, ForwardIter2 sLast)
  -> ForwardIter1
{
  return find_end(first, last, sFirst, sLast, equal_to<> {});
}

/// \brief Removes all elements satisfying specific criteria from the range
/// [first, last) and returns a past-the-end iterator for the new end of the
/// range.
/// \group remove
/// \module algorithm
template <typename ForwardIter, typename UnaryPredicate>
[[nodiscard]] constexpr auto remove_if(ForwardIter first, ForwardIter last,
                                       UnaryPredicate pred) -> ForwardIter
{
  first = find_if(first, last, pred);

  if (first != last)
  {
    for (auto i = first; ++i != last;)
    {
      if (!pred(*i)) { *first++ = move(*i); }
    }
  }

  return first;
}

/// \brief Removes all elements satisfying specific criteria from the range
/// [first, last) and returns a past-the-end iterator for the new end of the
/// range.
/// \group remove
/// \module algorithm
template <typename ForwardIter, typename T>
[[nodiscard]] constexpr auto remove(ForwardIter first, ForwardIter last,
                                    T const& value) -> ForwardIter
{
  return remove_if(first, last,
                   [&value](auto const& item) { return item == value; });
}

/// \brief Copies elements from the range [ first , last ), to another range
/// beginning at destination, omitting the elements which satisfy specific
/// criteria. Source and destination ranges cannot overlap. Ignores all elements
/// for which predicate p returns true.
///
/// \return Iterator to the element past the last element copied.
/// \group remove_copy
/// \module algorithm
template <typename InputIter, typename OutputIter, typename UnaryPredicate>
constexpr auto remove_copy_if(InputIter first, InputIter last,
                              OutputIter destination, UnaryPredicate p)
  -> OutputIter
{
  for (; first != last; ++first, ++destination)
  {
    if (!p(*first)) { *destination = *first; }
  }

  return destination;
}

/// \brief Copies elements from the range [ first , last ), to another range
/// beginning at destination, omitting the elements which satisfy specific
/// criteria. Source and destination ranges cannot overlap. Ignores all elements
/// that are equal to value.
///
/// \return Iterator to the element past the last element copied.
/// \group remove_copy
/// \module algorithm
template <typename InputIter, typename OutputIter, typename T>
constexpr auto remove_copy(InputIter first, InputIter last,
                           OutputIter destination, T const& value) -> OutputIter
{
  return remove_copy_if(first, last, destination,
                        [&value](auto const& item) { return item == value; });
}

/// \brief Replaces all elements satisfying specific criteria with new_value in
/// the range [ first , last ). Replaces all elements for which predicate p
/// returns true.
/// \group replace
/// \module algorithm
template <typename ForwardIt, typename UnaryPredicate, typename T>
constexpr auto replace_if(ForwardIt first, ForwardIt last, UnaryPredicate p,
                          T const& newValue) -> void
{
  for (; first != last; ++first)
  {
    if (p(*first)) { *first = newValue; }
  }
}

/// \brief Replaces all elements satisfying specific criteria with new_value in
/// the range [ first , last ). Replaces all elements that are equal to
/// old_value.
/// \group replace
/// \module algorithm
template <typename ForwardIt, typename T>
constexpr auto replace(ForwardIt first, ForwardIt last, T const& oldValue,
                       T const& newValue) -> void
{
  auto predicate = [&oldValue](auto const& item) { return item == oldValue; };
  replace_if(first, last, predicate, newValue);
}

/// \brief Returns the greater of a and b.
/// \group max
/// \module algorithm
template <typename Type>
[[nodiscard]] constexpr auto max(Type const& a, Type const& b) noexcept
  -> Type const&
{
  return (a < b) ? b : a;
}

/// \brief Returns the greater of a and b, using a compare function.
/// \group max
/// \module algorithm
template <typename Type, typename Compare>
[[nodiscard]] constexpr auto max(Type const& a, Type const& b,
                                 Compare comp) noexcept -> Type const&
{
  return (comp(a, b)) ? b : a;
}

/// \brief Finds the greatest element in the range [first, last). Elements are
/// compared using operator<.
/// \group max_element
/// \module algorithm
template <typename ForwardIterator>
[[nodiscard]] constexpr auto max_element(ForwardIterator first,
                                         ForwardIterator last) noexcept
  -> ForwardIterator
{
  if (first == last) { return last; }

  ForwardIterator largest = first;
  ++first;
  for (; first != last; ++first)
  {
    if (*largest < *first) { largest = first; }
  }
  return largest;
}

/// \brief Finds the greatest element in the range [first, last). Elements are
/// compared using the given binary comparison function comp.
/// \group max_element
/// \module algorithm
template <typename ForwardIterator, typename Compare>
[[nodiscard]] constexpr auto max_element(ForwardIterator first,
                                         ForwardIterator last, Compare comp)
  -> ForwardIterator
{
  if (first == last) { return last; }

  ForwardIterator largest = first;
  ++first;
  for (; first != last; ++first)
  {
    if (comp(*largest, *first)) { largest = first; }
  }
  return largest;
}

/// \brief Returns the smaller of a and b.
/// \group min
/// \module algorithm
template <typename Type>
[[nodiscard]] constexpr auto min(Type const& a, Type const& b) noexcept
  -> Type const&
{
  return (b < a) ? b : a;
}

/// \brief Returns the smaller of a and b, using a compare function.
/// \group min
/// \module algorithm
template <typename Type, typename Compare>
[[nodiscard]] constexpr auto min(Type const& a, Type const& b,
                                 Compare comp) noexcept -> Type const&
{
  return (comp(b, a)) ? b : a;
}

/// \brief Finds the smallest element in the range [first, last). Elements are
/// compared using operator<.
/// \group min_element
/// \module algorithm
template <typename ForwardIterator>
[[nodiscard]] constexpr auto min_element(ForwardIterator first,
                                         ForwardIterator last) noexcept
  -> ForwardIterator
{
  if (first == last) { return last; }

  ForwardIterator smallest = first;
  ++first;
  for (; first != last; ++first)
  {
    if (*first < *smallest) { smallest = first; }
  }
  return smallest;
}

/// \brief Finds the smallest element in the range [first, last). Elements are
/// compared using the given binary comparison function comp.
/// \group min_element
/// \module algorithm
template <typename ForwardIterator, typename Compare>
[[nodiscard]] constexpr auto min_element(ForwardIterator first,
                                         ForwardIterator last, Compare comp)
  -> ForwardIterator
{
  if (first == last) { return last; }

  ForwardIterator smallest = first;
  ++first;
  for (; first != last; ++first)
  {
    if (comp(*first, *smallest)) { smallest = first; }
  }
  return smallest;
}

/// \brief Returns the lowest and the greatest of the given values.
/// \group minmax
/// \module algorithm
template <typename T, typename Compare>
[[nodiscard]] constexpr auto minmax(T const& a, T const& b, Compare comp)
  -> pair<T const&, T const&>
{
  using return_type = pair<T const&, T const&>;
  return comp(b, a) ? return_type(b, a) : return_type(a, b);
}

/// \brief Returns the lowest and the greatest of the given values.
/// \group minmax
/// \module algorithm
template <typename T>
[[nodiscard]] constexpr auto minmax(T const& a, T const& b)
  -> pair<T const&, T const&>
{
  return minmax(a, b, less<> {});
}

/// \brief Finds the smallest and greatest element in the range [first, last).
/// \group minmax_element
/// \module algorithm
template <typename ForwardIter, typename Compare>
[[nodiscard]] constexpr auto minmax_element(ForwardIter first, ForwardIter last,
                                            Compare comp)
  -> pair<ForwardIter, ForwardIter>
{
  auto min = first;
  auto max = first;

  if (first == last || ++first == last) { return {min, max}; }

  if (comp(*first, *min)) { min = first; }
  else
  {
    max = first;
  }

  while (++first != last)
  {
    auto i = first;
    if (++first == last)
    {
      if (comp(*i, *min)) { min = i; }
      else if (!(comp(*i, *max)))
      {
        max = i;
      }
      break;
    }

    if (comp(*first, *i))
    {
      if (comp(*first, *min)) { min = first; }
      if (!(comp(*i, *max))) { max = i; }
    }
    else
    {
      if (comp(*i, *min)) { min = i; }
      if (!(comp(*first, *max))) { max = first; }
    }
  }

  return {min, max};
}

/// \brief Finds the smallest and greatest element in the range [first, last).
/// \group minmax_element
/// \module algorithm
template <typename ForwardIter>
[[nodiscard]] constexpr auto minmax_element(ForwardIter first, ForwardIter last)
  -> pair<ForwardIter, ForwardIter>
{
  using value_type = typename iterator_traits<ForwardIter>::value_type;
  return minmax_element(first, last, less<value_type>());
}

/// \brief If v compares less than lo, returns lo; otherwise if hi compares less
/// than v, returns hi; otherwise returns v. Uses operator< to compare the
/// values.

/// \group clamp
/// \module algorithm
template <typename Type>
[[nodiscard]] constexpr auto clamp(Type const& v, Type const& lo,
                                   Type const& hi) noexcept -> Type const&
{
  return clamp(v, lo, hi, less<Type>());
}
/// \group clamp
/// \module algorithm
template <typename Type, typename Compare>
[[nodiscard]] constexpr auto clamp(Type const& v, Type const& lo,
                                   Type const& hi, Compare comp) -> Type const&
{
  assert(!comp(hi, lo));
  return comp(v, lo) ? lo : comp(hi, v) ? hi : v;
}

/// \brief Checks if unary predicate p returns true for all elements in the
/// range [first, last).
template <typename InputIter, typename UnaryPredicate>
[[nodiscard]] constexpr auto all_of(InputIter first, InputIter last,
                                    UnaryPredicate p) -> bool
{
  return find_if_not(first, last, p) == last;
}

/// \brief Checks if unary predicate p returns true for at least one element in
/// the range [first, last).
template <typename InputIter, typename UnaryPredicate>
[[nodiscard]] constexpr auto any_of(InputIter first, InputIter last,
                                    UnaryPredicate p) -> bool
{
  return find_if(first, last, p) != last;
}

/// \brief Checks if unary predicate p returns true for no elements in the range
/// [first, last).
template <typename InputIter, typename UnaryPredicate>
[[nodiscard]] constexpr auto none_of(InputIter first, InputIter last,
                                     UnaryPredicate p) -> bool
{
  return find_if(first, last, p) == last;
}

/// \brief Reverses the order of the elements in the range [first, last).
/// Behaves as if applying iter_swap to every pair of iterators first+i,
/// (last-i) - 1 for each non-negative i < (last-first)/2.
template <typename BidirIter>
constexpr auto reverse(BidirIter first, BidirIter last) -> void
{
  while ((first != last) && (first != --last)) { iter_swap(first++, last); }
}

/// \brief Copies the elements from the range [ first, last ) to another range
/// beginning at d_first in such a way that the elements in the new range are in
/// reverse order.
///
/// \details If the source and destination ranges (that is, [first, last) and
/// [d_first, d_first+(last-first)) respectively) overlap, the behavior is
/// undefined.
template <typename BidirIter, typename OutputIter>
constexpr auto reverse_copy(BidirIter first, BidirIter last,
                            OutputIter destination) -> OutputIter
{
  for (; first != last; ++destination) { *(destination) = *(--last); }
  return destination;
}

/// \brief Performs a left rotation on a range of elements.
///
/// \details Specifically, rotate swaps the elements in the range [first,
/// last) in such a way that the element n_first becomes the first element of
/// the new range and n_first - 1 becomes the last element. A precondition of
/// this function is that [first, n_first) and [n_first, last) are valid ranges.
template <typename ForwardIter>
constexpr auto rotate(ForwardIter first, ForwardIter nFirst, ForwardIter last)
  -> ForwardIter
{
  if (first == nFirst) { return last; }
  if (nFirst == last) { return first; }

  auto read     = nFirst;
  auto write    = first;
  auto nextRead = first;

  while (read != last)
  {
    if (write == nextRead) { nextRead = read; }
    iter_swap(write++, read++);
  }

  rotate(write, nextRead, last);
  return write;
}

/// \brief Eliminates all except the first element from every consecutive group
/// of equivalent elements from the range [first, last) and returns a
/// past-the-end iterator for the new logical end of the range.
/// \group unique
/// \module algorithm
template <typename ForwardIter, typename BinaryPredicate>
constexpr auto unique(ForwardIter first, ForwardIter last, BinaryPredicate pred)
  -> ForwardIter
{
  if (first == last) { return last; }

  auto result = first;
  while (++first != last)
  {
    if (!pred(*result, *first) && ++result != first) { *result = move(*first); }
  }
  return ++result;
}

/// \brief Eliminates all except the first element from every consecutive group
/// of equivalent elements from the range [first, last) and returns a
/// past-the-end iterator for the new logical end of the range.
/// \group unique
/// \module algorithm
template <typename ForwardIter>
constexpr auto unique(ForwardIter first, ForwardIter last) -> ForwardIter
{
  return unique(first, last, equal_to<> {});
}

/// \brief Copies the elements from the range [first, last), to another range
/// beginning at d_first in such a way that there are no consecutive equal
/// elements. Only the first element of each group of equal elements is copied.
///
/// \details Elements are compared using the given binary predicate pred. The
/// behavior is undefined if it is not an equivalence relation.
/// \group unique_copy
/// \module algorithm
template <typename InputIter, typename OutputIter, typename BinaryPredicate>
constexpr auto unique_copy(InputIter first, InputIter last,
                           OutputIter destination, BinaryPredicate pred)
  -> OutputIter
{
  if (first != last)
  {
    *destination = *first;

    while (++first != last)
    {
      if (!pred(*destination, *first)) { *++destination = *first; }
    }

    ++destination;
  }

  return destination;
}

/// \brief Copies the elements from the range [first, last), to another range
/// beginning at d_first in such a way that there are no consecutive equal
/// elements. Only the first element of each group of equal elements is copied.
///
/// \details Elements are compared using operator==. The behavior is undefined
/// if it is not an equivalence relation.
/// \group unique_copy
/// \module algorithm
template <typename InputIter, typename OutputIter>
constexpr auto unique_copy(InputIter first, InputIter last,
                           OutputIter destination) -> OutputIter
{
  return unique_copy(first, last, destination, equal_to<> {});
}

/// \brief Reorders the elements in the range [first, last) in such a way that
/// all elements for which the predicate p returns true precede the elements for
/// which predicate p returns false. Relative order of the elements is not
/// preserved.
template <typename ForwardIter, typename UnaryPredicate>
constexpr auto partition(ForwardIter first, ForwardIter last, UnaryPredicate p)
  -> ForwardIter
{
  first = find_if_not(first, last, p);
  if (first == last) { return first; }

  for (ForwardIter i = next(first); i != last; ++i)
  {
    if (p(*i))
    {
      iter_swap(i, first);
      ++first;
    }
  }
  return first;
}

/// \brief Copies the elements from the range [ first , last ) to two different
/// ranges depending on the value returned by the predicate p. The elements that
/// satisfy the predicate p are copied to the range beginning at
/// destination_true. The rest of the elements are copied to the range beginning
/// at destination_false.
///
/// \details The behavior is undefined if the input range overlaps either of the
/// output ranges.
template <typename InputIter, typename OutputIter1, typename OutputIter2,
          typename UnaryPredicate>
constexpr auto partition_copy(InputIter first, InputIter last,
                              OutputIter1 destinationTrue,
                              OutputIter2 destinationFalse, UnaryPredicate p)
  -> pair<OutputIter1, OutputIter2>
{
  for (; first != last; ++first)
  {
    if (p(*first))
    {
      *destinationTrue = *first;
      ++destinationTrue;
    }
    else
    {
      *destinationFalse = *first;
      ++destinationFalse;
    }
  }

  return make_pair(destinationTrue, destinationFalse);
}

/// \brief Returns true if all elements in the range [ first , last ) that
/// satisfy the predicate p appear before all elements that don't. Also returns
/// true if the range is empty.
///
/// https://en.cppreference.com/w/cpp/algorithm/is_partitioned
template <typename InputIter, typename UnaryPredicate>
[[nodiscard]] constexpr auto is_partitioned(InputIter first, InputIter last,
                                            UnaryPredicate p) -> bool
{
  for (; first != last; ++first)
  {
    if (!p(*first)) { break; }
  }

  for (; first != last; ++first)
  {
    if (p(*first)) { return false; }
  }

  return true;
}

/// \brief Examines the partitioned (as if by partition) range [ first ,
/// last ) and locates the end of the first partition, that is, the first
/// element that does not satisfy p or last if all elements satisfy p.
template <typename ForwardIter, typename UnaryPredicate>
[[nodiscard]] constexpr auto partition_point(ForwardIter first,
                                             ForwardIter last, UnaryPredicate p)
  -> ForwardIter
{
  for (; first != last; ++first)
  {
    if (!p(*first)) { break; }
  }

  return first;
}

/// \brief  Reorders the elements in the range [first, last) in such a way
/// that all elements for which the predicate p returns true precede the
/// elements for which predicate p returns false. Relative order of the
/// elements is preserved.
template <typename BidirIter, typename UnaryPredicate>
constexpr auto stable_partition(BidirIter f, BidirIter l, UnaryPredicate p)
  -> BidirIter
{
  auto const n = l - f;
  if (n == 0) { return f; }
  if (n == 1) { return f + p(*f); }
  auto const m = f + (n / 2);
  return rotate(stable_partition(f, m, p), m, stable_partition(m, l, p));
}

/// \brief Copies the elements in the range, defined by [first, last), to
/// another range beginning at destination.
///
/// \details Copies all elements in the range [first, last) starting from first
/// and proceeding to last - 1. The behavior is undefined if destination is
/// within the range [first, last). In this case, copy_backward may be used
/// instead.
///
/// \return Output iterator to the element in the destination range, one past
/// the last element copied.
/// \group copy
/// \module algorithm
template <typename InputIter, typename OutputIter>
constexpr auto copy(InputIter first, InputIter last, OutputIter destination)
  -> OutputIter
{
  for (; first != last; ++first, ++destination) { *destination = *first; }
  return destination;
}

/// \brief Copies the elements in the range, defined by [first, last), to
/// another range beginning at destination.
///
/// \details Only copies the elements for which the predicate pred returns true.
/// The relative order of the elements that are copied is preserved. The
/// behavior is undefined if the source and the destination ranges overlap.
///
/// \return Output iterator to the element in the destination range, one past
/// the last element copied.
/// \group copy
/// \module algorithm
template <typename InputIter, typename OutputIter, typename UnaryPredicate>
constexpr auto copy_if(InputIter first, InputIter last, OutputIter dFirst,
                       UnaryPredicate pred) -> OutputIter
{
  while (first != last)
  {
    if (pred(*first)) { *dFirst++ = *first; }
    first++;
  }
  return dFirst;
}

/// \brief Copies exactly count values from the range beginning at first to the
/// range beginning at result. Formally, for each integer 0 ≤ i < count,
/// performs
/// *(result + i) =
/// *(first + i). Overlap of ranges is formally permitted, but leads to
/// unpredictable ordering of the results.
///
/// \return Iterator in the destination range, pointing past the last element
/// copied if count>0 or result otherwise.
template <typename InputIter, typename Size, typename OutputIter>
constexpr auto copy_n(InputIter first, Size count, OutputIter result)
  -> OutputIter
{
  if (count > 0)
  {
    *result++ = *first;
    for (Size i = 1; i < count; ++i) { *result++ = *++first; }
  }
  return result;
}

/// \brief Copies the elements from the range, defined by [first, last), to
/// another range ending at d_last. The elements are copied in reverse order
/// (the last element is copied first), but their relative order is preserved.
///
/// \details The behavior is undefined if d_last is within (first, last].
/// copy must be used instead of copy_backward in that case.
///
/// \return Iterator to the last element copied.
template <typename BidirIter1, typename BidirIter2>
constexpr auto copy_backward(BidirIter1 first, BidirIter1 last,
                             BidirIter2 dLast) -> BidirIter2
{
  while (first != last) { *(--dLast) = *(--last); }
  return dLast;
}

/// \brief Copies the elements from the range [ first , last ), to another range
/// beginning at destination in such a way, that the element n_first becomes the
/// first element of the new range and n_first - 1 becomes the last element.
template <typename ForwardIter, typename OutputIter>
constexpr auto rotate_copy(ForwardIter first, ForwardIter nFirst,
                           ForwardIter last, OutputIter destination)
  -> OutputIter
{
  destination = copy(nFirst, last, destination);
  return copy(first, nFirst, destination);
}

/// \brief Assigns the given value to the elements in the range [first, last).
template <typename ForwardIter, typename T>
constexpr auto fill(ForwardIter first, ForwardIter last, T const& value) -> void
{
  for (; first != last; ++first) { *first = value; }
}

/// \brief Assigns the given value to the first count elements in the range
/// beginning at first if count > 0. Does nothing otherwise.
///
/// \return Iterator one past the last element assigned if count > 0, first
/// otherwise.
template <typename OutputIter, typename Size, typename T>
constexpr auto fill_n(OutputIter first, Size count, T const& value)
  -> OutputIter
{
  for (auto i = Size {0}; i < count; ++i)
  {
    *first = value;
    ++first;
  }

  return first;
}

/// \brief Returns true if the range [first1, last1) is equal to the range
/// [first2, first2
/// + (last1 - first1)), and false otherwise.
/// \group equal
/// \module algorithm
template <typename InputIter1, typename InputIter2, typename BinaryPredicate>
[[nodiscard]] constexpr auto equal(InputIter1 first1, InputIter1 last1,
                                   InputIter2 first2, BinaryPredicate p) -> bool
{
  for (; first1 != last1; ++first1, ++first2)
  {
    if (!p(*first1, *first2)) { return false; }
  }
  return true;
}

/// \brief Returns true if the range [first1, last1) is equal to the range
/// [first2, first2
/// + (last1 - first1)), and false otherwise.
/// \group equal
/// \module algorithm
template <typename InputIter1, typename InputIter2>
[[nodiscard]] constexpr auto equal(InputIter1 first1, InputIter1 last1,
                                   InputIter2 first2) -> bool
{
  return equal(first1, last1, first2, equal_to<> {});
}

/// \brief Returns true if the range [first1, last1) is equal to the range
/// [first2, last2), and false otherwise.
/// \group equal
/// \module algorithm
template <typename InputIter1, typename InputIter2, typename BinaryPredicate>
[[nodiscard]] constexpr auto equal(InputIter1 first1, InputIter1 last1,
                                   InputIter2 first2, InputIter2 last2,
                                   BinaryPredicate p) -> bool
{
  if (distance(first1, last1) != distance(first2, last2)) { return false; }
  return equal(first1, last1, first2, p);
}

/// \brief Returns true if the range [first1, last1) is equal to the range
/// [first2, last2), and false otherwise.
/// \group equal
/// \module algorithm
template <typename InputIter1, typename InputIter2>
[[nodiscard]] constexpr auto equal(InputIter1 first1, InputIter1 last1,
                                   InputIter2 first2, InputIter2 last2) -> bool
{
  return equal(first1, last1, first2, last2, equal_to<> {});
}

/// \brief Checks if the first range [first1, last1) is lexicographically
/// less than the second range [first2, last2). Elements are compared using
/// the given binary comparison function comp.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
/// \group lexicographical_compare
/// \module algorithm
template <typename InputIter1, typename InputIter2, typename Compare>
[[nodiscard]] constexpr auto
lexicographical_compare(InputIter1 first1, InputIter1 last1, InputIter2 first2,
                        InputIter2 last2, Compare comp) -> bool
{
  for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
  {
    if (comp(*first1, *first2)) { return true; }
    if (comp(*first2, *first1)) { return false; }
  }
  return (first1 == last1) && (first2 != last2);
}

/// \brief Checks if the first range [first1, last1) is lexicographically
/// less than the second range [first2, last2). Elements are compared using
/// operator<.
///
/// \details https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
/// \group lexicographical_compare
/// \module algorithm
template <typename InputIter1, typename InputIter2>
[[nodiscard]] constexpr auto
lexicographical_compare(InputIter1 first1, InputIter1 last1, InputIter2 first2,
                        InputIter2 last2) -> bool
{
  return lexicographical_compare(first1, last1, first2, last2,
                                 less<decltype(*first1)> {});
}

/// \brief Sorts the elements in the range [first, last) in non-descending
/// order. The order of equal elements is not guaranteed to be preserved.
///
/// \details A sequence is sorted with respect to a comparator comp if for any
/// iterator it pointing to the sequence and any non-negative integer n such
/// that it + n is a valid iterator pointing to an element of the sequence,
/// comp(*(it
/// + n), *it) (or
/// *(it + n) < *it) evaluates to false. Bubble sort implementation.
///
/// https://en.cppreference.com/w/cpp/algorithm/sort
/// \group sort
/// \module algorithm
template <typename RandomIter, typename Compare>
constexpr auto sort(RandomIter first, RandomIter last, Compare comp) -> void
{
  for (auto i = first; i != last; ++i)
  {
    for (auto j = first; j < i; ++j)
    {
      if (comp(*i, *j)) { iter_swap(i, j); }
    }
  }
}

/// \brief Sorts the elements in the range [first, last) in non-descending
/// order. The order of equal elements is not guaranteed to be preserved.
/// Elements are compared using operator<.
///
/// \details A sequence is sorted with respect to a comparator comp if for any
/// iterator it pointing to the sequence and any non-negative integer n such
/// that it + n is a valid iterator pointing to an element of the sequence,
/// comp(*(it
/// + n), *it) (or
/// *(it + n) < *it) evaluates to false. Bubble sort implementation.
///
/// https://en.cppreference.com/w/cpp/algorithm/sort
/// \group sort
/// \module algorithm
template <typename RandomIter>
constexpr auto sort(RandomIter first, RandomIter last) -> void
{
  sort(first, last, less<> {});
}

/// \brief Sorts the elements in the range [first, last) in non-descending
/// order. The order of equivalent elements is guaranteed to be preserved.
/// Elements are compared using the given comparison function comp.
///
/// https://en.cppreference.com/w/cpp/algorithm/stable_sort
/// \group stable_sort
/// \module algorithm
template <typename RandomIter, typename Compare>
constexpr auto stable_sort(RandomIter first, RandomIter last, Compare cmp)
  -> void
{
  for (; first != last; ++first)
  {
    auto min = first;
    for (auto j = next(first, 1); j != last; ++j)
    {
      if (cmp(*j, *min)) { min = j; }
    }

    auto key = *min;
    while (min != first)
    {
      *min = *prev(min, 1);
      --min;
    }

    *first = key;
  }
}

/// \brief Sorts the elements in the range [first, last) in non-descending
/// order. The order of equivalent elements is guaranteed to be preserved.
/// Elements are compared using operator<.
///
/// https://en.cppreference.com/w/cpp/algorithm/stable_sort
/// \group stable_sort
/// \module algorithm
template <typename RandomIter>
constexpr auto stable_sort(RandomIter first, RandomIter last) -> void
{
  stable_sort(first, last, less<> {});
}

/// \brief Rearranges elements such that the range [first, middle) contains the
/// sorted middle - first smallest elements in the range [first, last). The
/// order of equal elements is not guaranteed to be preserved. The order of the
/// remaining elements in the range [middle, last) is unspecified. Elements are
/// compared using the given binary comparison function comp.
///
/// https://en.cppreference.com/w/cpp/algorithm/partial_sort
///
/// \todo Improve. Currently forwards to regular sort.
/// \group partial_sort
/// \module algorithm
template <typename RandomIter, typename Compare>
constexpr auto partial_sort(RandomIter first, RandomIter middle,
                            RandomIter last, Compare comp) -> void
{
  etl::ignore_unused(middle);
  etl::sort(first, last, comp);
}

/// \brief Rearranges elements such that the range [first, middle) contains the
/// sorted middle - first smallest elements in the range [first, last). The
/// order of equal elements is not guaranteed to be preserved. The order of the
/// remaining elements in the range [middle, last) is unspecified. Elements are
/// compared using operator<.
///
/// https://en.cppreference.com/w/cpp/algorithm/partial_sort
///
/// \todo Improve. Currently forwards to regular sort.
/// \group partial_sort
/// \module algorithm
template <typename RandomIter>
constexpr auto partial_sort(RandomIter first, RandomIter middle,
                            RandomIter last) -> void
{
  etl::ignore_unused(middle);
  etl::sort(first, last);
}

/// \brief nth_element is a partial sorting algorithm that rearranges elements
/// in [first, last) such that:
///
/// The element pointed at by nth is changed to whatever element would occur in
/// that position if [first, last) were sorted.
///
/// All of the elements before this new nth element are less than or equal to
/// the elements after the new nth element.
///
/// Elements are compared using the given binary comparison function comp.
///
/// https://en.cppreference.com/w/cpp/algorithm/nth_element
///
/// \todo Improve. Currently forwards to regular sort.
/// \group nth_element
/// \module algorithm
template <typename RandomIter, typename Compare>
constexpr auto nth_element(RandomIter first, RandomIter nth, RandomIter last,
                           Compare comp) -> void
{
  etl::ignore_unused(nth);
  etl::sort(first, last, comp);
}

/// \brief nth_element is a partial sorting algorithm that rearranges elements
/// in [first, last) such that:
///
/// The element pointed at by nth is changed to whatever element would occur in
/// that position if [first, last) were sorted.
///
/// All of the elements before this new nth element are less than or equal to
/// the elements after the new nth element.
///
/// Elements are compared using operator<.
///
/// https://en.cppreference.com/w/cpp/algorithm/nth_element
///
/// \todo Improve. Currently forwards to regular sort.
/// \group nth_element
/// \module algorithm
template <typename RandomIter>
constexpr auto nth_element(RandomIter first, RandomIter nth, RandomIter last)
  -> void
{
  etl::ignore_unused(nth);
  etl::sort(first, last);
}

/// \brief Examines the range [first, last) and finds the largest range
/// beginning at first in which the elements are sorted in non-descending order.
/// Elements are compared using operator<.
/// \group is_sorted_until
/// \module algorithm
template <typename ForwardIter>
[[nodiscard]] constexpr auto is_sorted_until(ForwardIter first,
                                             ForwardIter last) -> ForwardIter
{
  return is_sorted_until(first, last, less<>());
}

/// \brief Examines the range [first, last) and finds the largest range
/// beginning at first in which the elements are sorted in non-descending order.
/// Elements are compared using the given binary comparison function comp.
/// \group is_sorted_until
/// \module algorithm
template <typename ForwardIter, typename Compare>
[[nodiscard]] constexpr auto is_sorted_until(ForwardIter first,
                                             ForwardIter last, Compare comp)
  -> ForwardIter
{
  if (first != last)
  {
    ForwardIter next = first;
    while (++next != last)
    {
      if (comp(*next, *first)) { return next; }
      first = next;
    }
  }
  return last;
}

/// \brief Checks if the elements in range [first, last) are sorted in
/// non-descending order. Elements are compared using operator<.
/// \group is_sorted
/// \module algorithm
template <typename ForwardIter>
[[nodiscard]] constexpr auto is_sorted(ForwardIter first, ForwardIter last)
  -> bool
{
  return is_sorted_until(first, last) == last;
}

/// \brief Checks if the elements in range [ first , last ) are sorted in
/// non-descending order. Elements are compared using the given binary
/// comparison function comp.
/// \group is_sorted
/// \module algorithm
template <typename ForwardIter, typename Compare>
[[nodiscard]] constexpr auto is_sorted(ForwardIter first, ForwardIter last,
                                       Compare comp) -> bool
{
  return is_sorted_until(first, last, comp) == last;
}

/// \brief Returns an iterator pointing to the first element in the range
/// [first, last) that is not less than (i.e. greater or equal to) value, or
/// last if no such element is found.
///
/// https://en.cppreference.com/w/cpp/algorithm/lower_bound
/// \group lower_bound
/// \module algorithm
template <typename ForwardIter, typename T, typename Compare>
[[nodiscard]] constexpr auto lower_bound(ForwardIter first, ForwardIter last,
                                         T const& value, Compare comp) noexcept
  -> ForwardIter
{
  using diff_t = typename iterator_traits<ForwardIter>::difference_type;
  ForwardIter it;
  diff_t count;
  diff_t step;
  count = distance(first, last);

  while (count > 0)
  {
    it   = first;
    step = count / 2;
    advance(it, step);
    if (comp(*it, value))
    {
      first = ++it;
      count -= step + 1;
    }
    else
    {
      count = step;
    }
  }

  return first;
}

/// \brief Returns an iterator pointing to the first element in the range
/// [first, last) that is not less than (i.e. greater or equal to) value, or
/// last if no such element is found.
///
/// https://en.cppreference.com/w/cpp/algorithm/lower_bound
/// \group lower_bound
/// \module algorithm
template <typename ForwardIter, typename T>
[[nodiscard]] constexpr auto lower_bound(ForwardIter first, ForwardIter last,
                                         T const& value) noexcept -> ForwardIter
{
  return lower_bound(first, last, value, less<> {});
}

/// \brief Returns an iterator pointing to the first element in the range
/// [ first , last ) that is greater than value, or last if no such element is
/// found.
///
/// \details The range [ first , last ) must be partitioned with respect to the
/// expression !(value < element) or !comp(value, element), i.e., all elements
/// for which the expression is true must precede all elements for which the
/// expression is false. A fully-sorted range meets this criterion.
/// \group upper_bound
/// \module algorithm
template <typename ForwardIter, typename T, typename Compare>
[[nodiscard]] constexpr auto upper_bound(ForwardIter first, ForwardIter last,
                                         T const& value, Compare comp)
  -> ForwardIter
{
  using diff_t = typename iterator_traits<ForwardIter>::difference_type;

  ForwardIter it;
  diff_t count;
  diff_t step;
  count = distance(first, last);

  while (count > 0)
  {
    it   = first;
    step = count / 2;
    advance(it, step);
    if (!comp(value, *it))
    {
      first = ++it;
      count -= step + 1;
    }
    else
    {
      count = step;
    }
  }

  return first;
}

/// \brief Returns an iterator pointing to the first element in the range
/// [ first , last ) that is greater than value, or last if no such element is
/// found.
///
/// \details The range [ first , last ) must be partitioned with respect to the
/// expression !(value < element) or !comp(value, element), i.e., all elements
/// for which the expression is true must precede all elements for which the
/// expression is false. A fully-sorted range meets this criterion.
/// \group upper_bound
/// \module algorithm
template <typename ForwardIter, typename T>
[[nodiscard]] constexpr auto upper_bound(ForwardIter first, ForwardIter last,
                                         T const& value) -> ForwardIter
{
  return upper_bound(first, last, value, less<> {});
}

/// \brief Returns a range containing all elements equivalent to value in the
/// range [first, last).
///
/// https://en.cppreference.com/w/cpp/algorithm/equal_range
/// \group equal_range
/// \module algorithm
template <typename ForwardIt, typename T, typename Compare>
[[nodiscard]] constexpr auto equal_range(ForwardIt first, ForwardIt last,
                                         T const& value, Compare comp)
  -> pair<ForwardIt, ForwardIt>
{
  return make_pair(lower_bound(first, last, value, comp),
                   upper_bound(first, last, value, comp));
}

/// \brief Returns a range containing all elements equivalent to value in the
/// range [first, last).
///
/// https://en.cppreference.com/w/cpp/algorithm/equal_range
/// \group equal_range
/// \module algorithm
template <typename ForwardIt, typename T>
[[nodiscard]] constexpr auto equal_range(ForwardIt first, ForwardIt last,
                                         T const& value)
  -> pair<ForwardIt, ForwardIt>
{
  return equal_range(first, last, value, less<> {});
}

/// \brief Checks if an element equivalent to value appears within the range [
/// first , last ).
///
/// \details For binary_search to succeed, the range [ first , last ) must
/// be at least partially ordered with respect to value
///
/// https://en.cppreference.com/w/cpp/algorithm/binary_search
/// \group binary_search
/// \module algorithm
template <typename ForwardIter, typename T, typename Compare>
[[nodiscard]] constexpr auto binary_search(ForwardIter first, ForwardIter last,
                                           T const& value, Compare comp) -> bool
{
  first = lower_bound(first, last, value, comp);
  return (!(first == last) && !(comp(value, *first)));
}

/// \brief Checks if an element equivalent to value appears within the range [
/// first , last ).
///
/// \details For binary_search to succeed, the range [ first , last ) must
/// be at least partially ordered with respect to value
///
/// https://en.cppreference.com/w/cpp/algorithm/binary_search
/// \group binary_search
/// \module algorithm
template <typename ForwardIter, class T>
[[nodiscard]] constexpr auto binary_search(ForwardIter first, ForwardIter last,
                                           T const& value) -> bool
{
  return binary_search(first, last, value, less<> {});
}

/// \brief Merges two sorted ranges [first1, last1) and [first2, last2) into one
/// sorted range beginning at d_first. Elements are compared using the given
/// binary comparison function comp.
/// \group merge
/// \module algorithm
template <typename InputIt1, typename InputIt2, typename OutputIt,
          typename Compare>
constexpr auto merge(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                     InputIt2 last2, OutputIt destination, Compare comp)
  -> OutputIt
{
  for (; first1 != last1; ++destination)
  {
    if (first2 == last2) { return copy(first1, last1, destination); }
    if (comp(*first2, *first1))
    {
      *destination = *first2;
      ++first2;
    }
    else
    {
      *destination = *first1;
      ++first1;
    }
  }
  return copy(first2, last2, destination);
}

/// \brief Merges two sorted ranges [first1, last1) and [first2, last2) into one
/// sorted range beginning at destination. Elements are compared using
/// operator<.
/// \group merge
/// \module algorithm
template <typename InputIt1, typename InputIt2, typename OutputIt>
constexpr auto merge(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                     InputIt2 last2, OutputIt destination) -> OutputIt
{
  return merge(first1, last1, first2, last2, destination, less<> {});
}

/// \brief Returns true if the sorted range [first2, last2) is a subsequence of
/// the sorted range [first1, last1). Both ranges must be sorted with operator<.
/// \group includes
/// \module algorithm
template <typename InputIter1, typename InputIter2>
[[nodiscard]] constexpr auto includes(InputIter1 first1, InputIter1 last1,
                                      InputIter2 first2, InputIter2 last2)
  -> bool
{
  for (; first2 != last2; ++first1)
  {
    if (first1 == last1 || *first2 < *first1) { return false; }
    if (!(*first1 < *first2)) { ++first2; }
  }
  return true;
}

/// \brief Returns true if the sorted range [first2, last2) is a subsequence of
/// the sorted range [first1, last1). Both ranges must be sorted with the given
/// comparison function comp.
/// \group includes
/// \module algorithm
template <typename InputIter1, typename InputIter2, typename Compare>
[[nodiscard]] constexpr auto includes(InputIter1 first1, InputIter1 last1,
                                      InputIter2 first2, InputIter2 last2,
                                      Compare comp) -> bool
{
  for (; first2 != last2; ++first1)
  {
    if (first1 == last1 || comp(*first2, *first1)) { return false; }
    if (!comp(*first1, *first2)) { ++first2; }
  }
  return true;
}

/// \brief Copies the elements from the sorted range [first1, last1) which are
/// not found in the sorted range [first2, last2) to the range beginning at
/// destination. Elements are compared using the given binary comparison
/// function comp and the ranges must be sorted with respect to the same.
/// \group set_difference
/// \module algorithm
template <typename InputIt1, typename InputIt2, typename OutputIt,
          typename Compare>
constexpr auto set_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                              InputIt2 last2, OutputIt destination,
                              Compare comp) -> OutputIt
{
  while (first1 != last1)
  {
    if (first2 == last2) { return copy(first1, last1, destination); }

    if (comp(*first1, *first2)) { *destination++ = *first1++; }
    else
    {
      if (!comp(*first2, *first1)) { ++first1; }
      ++first2;
    }
  }
  return destination;
}

/// \brief Copies the elements from the sorted range [first1, last1) which are
/// not found in the sorted range [first2, last2) to the range beginning at
/// destination. Elements are compared using operator< and the ranges must be
/// sorted with respect to the same.
/// \group set_difference
/// \module algorithm
template <typename InputIt1, typename InputIt2, typename OutputIt>
constexpr auto set_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                              InputIt2 last2, OutputIt destination) -> OutputIt
{
  return set_difference(first1, last1, first2, last2, destination, less<> {});
}

/// \brief Constructs a sorted range beginning at d_first consisting of elements
/// that are found in both sorted ranges [first1, last1) and [first2, last2). If
/// some element is found m times in [first1, last1) and n times in [first2,
/// last2), the first min(m, n) elements will be copied from the first range to
/// the destination range. The order of equivalent elements is preserved. The
/// resulting range cannot overlap with either of the input ranges.
///
/// Elements are compared using the given binary comparison function comp and
/// the ranges must be sorted with respect to the same.
/// \group set_intersection
/// \module algorithm
template <typename InputIt1, typename InputIt2, typename OutputIt,
          typename Compare>
constexpr auto set_intersection(InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2, OutputIt dest,
                                Compare comp) -> OutputIt
{
  while (first1 != last1 && first2 != last2)
  {
    if (comp(*first1, *first2)) { ++first1; }
    else
    {
      if (!comp(*first2, *first1)) { *dest++ = *first1++; }
      ++first2;
    }
  }
  return dest;
}

/// \brief Constructs a sorted range beginning at d_first consisting of elements
/// that are found in both sorted ranges [first1, last1) and [first2, last2). If
/// some element is found m times in [first1, last1) and n times in [first2,
/// last2), the first min(m, n) elements will be copied from the first range to
/// the destination range. The order of equivalent elements is preserved. The
/// resulting range cannot overlap with either of the input ranges.
///
/// Elements are compared using operator< and the ranges must be sorted with
/// respect to the same.
/// \group set_intersection
/// \module algorithm
template <typename InputIt1, typename InputIt2, typename OutputIt>
constexpr auto set_intersection(InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2, OutputIt dest)
  -> OutputIt
{
  return set_intersection(first1, last1, first2, last2, dest, less<>());
}

/// \brief Computes symmetric difference of two sorted ranges: the elements that
/// are found in either of the ranges, but not in both of them are copied to the
/// range beginning at destination. The resulting range is also sorted. Elements
/// are compared using the given binary comparison function comp and the ranges
/// must be sorted with respect to the same.
/// \group set_symmetric_difference
/// \module algorithm
template <typename InputIter1, typename InputIter2, typename OutputIter,
          typename Compare>
constexpr auto set_symmetric_difference(InputIter1 first1, InputIter1 last1,
                                        InputIter2 first2, InputIter2 last2,
                                        OutputIter destination, Compare comp)
  -> OutputIter
{
  while (first1 != last1)
  {
    if (first2 == last2) { return copy(first1, last1, destination); }

    if (comp(*first1, *first2)) { *destination++ = *first1++; }
    else
    {
      if (comp(*first2, *first1)) { *destination++ = *first2; }
      else
      {
        ++first1;
      }
      ++first2;
    }
  }
  return copy(first2, last2, destination);
}

/// \brief Computes symmetric difference of two sorted ranges: the elements that
/// are found in either of the ranges, but not in both of them are copied to the
/// range beginning at destination. The resulting range is also sorted. Elements
/// are compared using operator< and the ranges must be sorted with respect to
/// the same.
/// \group set_symmetric_difference
/// \module algorithm
template <typename InputIter1, typename InputIter2, typename OutputIter>
constexpr auto set_symmetric_difference(InputIter1 first1, InputIter1 last1,
                                        InputIter2 first2, InputIter2 last2,
                                        OutputIter dest) -> OutputIter
{
  return set_symmetric_difference(first1, last1, first2, last2, dest, less<>());
}

/// \brief Constructs a sorted union beginning at destination consisting of the
/// set of elements present in one or both sorted ranges [first1, last1) and
/// [first2, last2). The resulting range cannot overlap with either of the input
/// ranges. Elements are compared using the given binary comparison function
/// comp and the ranges must be sorted with respect to the same.
/// \group set_union
/// \module algorithm
template <typename InputIter1, typename InputIter2, typename OutputIter,
          typename Compare>
constexpr auto set_union(InputIter1 first1, InputIter1 last1, InputIter2 first2,
                         InputIter2 last2, OutputIter destination, Compare comp)
  -> OutputIter
{
  for (; first1 != last1; ++destination)
  {
    if (first2 == last2) { return copy(first1, last1, destination); }
    if (comp(*first2, *first1))
    {
      *destination = *first2++;
      continue;
    }

    *destination = *first1;
    if (!comp(*first1, *first2)) { ++first2; }
    ++first1;
  }
  return copy(first2, last2, destination);
}

/// \brief Constructs a sorted union beginning at destination consisting of the
/// set of elements present in one or both sorted ranges [first1, last1) and
/// [first2, last2). The resulting range cannot overlap with either of the input
/// ranges. Elements are compared using operator< and the ranges must be sorted
/// with respect to the same.
/// \group set_union
/// \module algorithm
template <typename InputIter1, typename InputIter2, typename OutputIter>
constexpr auto set_union(InputIter1 first1, InputIter1 last1, InputIter2 first2,
                         InputIter2 last2, OutputIter destination) -> OutputIter
{
  return set_union(first1, last1, first2, last2, destination, etl::less<> {});
}

/// \brief Returns true if there exists a permutation of the elements in the
/// range [first1, last1) that makes that range equal to the range
/// [first2,last2), where last2 denotes first2 + (last1 - first1) if it was not
/// given.
///
/// \details Elements are compared using operator==. The behavior is undefined
/// if it is not an equivalence relation.
/// \group is_permuatation
/// \module algorithm
template <typename ForwardIter1, typename ForwardIter2>
[[nodiscard]] constexpr auto is_permutation(ForwardIter1 first,
                                            ForwardIter1 last,
                                            ForwardIter2 first2) -> bool
{
  // skip common prefix
  auto const [fDiff1, fDiff2] = mismatch(first, last, first2);

  // iterate over the rest, counting how many times each element
  // from [first, last) appears in [first2, last2)
  if (fDiff1 != last)
  {
    auto last2 = next(fDiff2, distance(fDiff1, last));
    for (auto i = fDiff1; i != last; ++i)
    {
      // this *i has been checked
      if (i != find(fDiff1, i, *i)) { continue; }

      auto m = count(fDiff2, last2, *i);
      if (m == 0 || count(i, last, *i) != m) { return false; }
    }
  }

  return true;
}

/// \brief Returns true if there exists a permutation of the elements in the
/// range [first1, last1) that makes that range equal to the range
/// [first2,last2), where last2 denotes first2 + (last1 - first1) if it was not
/// given.
///
/// \details Elements are compared using operator==. The behavior is undefined
/// if it is not an equivalence relation.
/// \group is_permuatation
/// \module algorithm
template <typename ForwardIter1, typename ForwardIter2>
[[nodiscard]] constexpr auto
is_permutation(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2,
               ForwardIter2 last2) -> bool
{
  if (distance(first1, last1) != distance(first2, last2)) { return false; }
  return is_permutation(first1, last1, first2);
}

}  // namespace etl

#endif  // TAETL_ALGORITHM_HPP