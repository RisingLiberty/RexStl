// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: algorithms.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/concepts.h"
#include "rex_std/bonus/types.h"
#include "utility/swap.h"

#include <algorithm>
#include <iterator>

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {
      template <typename It, typename CountType>
      constexpr int32 memcmp(It first1, It first2, CountType count)
      {
        CountType counter = 0;
        while(counter < count)
        {
          if(*first1 != *first2)
          {
            return *first1 - *first2;
          }
          ++first1, ++first2, ++counter;
        }

        return 0;
      }

      template <typename It1, typename It2, typename Pred>
      constexpr bool are_ranges_equal(It1 first1, It2 first2, It2 last2, [[maybe_unused]] const Pred& pred)
      {
        if constexpr(rsl::is_same_v<It1, It2>)
        {
          const auto count = last2 - first2;
          return rsl::memcmp(first1, first2, count) == 0;
        }
        else
        {
          for(; first2 != last2; ++first1, ++first2)
          {
            if(!pred(*first1, *first2))
            {
              return false;
            }
          }

          return true;
        }
      }

    } // namespace internal

    template <typename Container, typename T>
    void remove(Container& container, T&& value)
    {
      container.erase(rsl::remove(rsl::begin(container), rsl::end(container), rsl::forward<T>(value)...), rsl::end(container));
    }

    template <typename Container, typename Pred>
    void remove_if(Container& container, const Pred& predicate)
    {
      container.erase(rsl::remove_if(rsl::begin(container), rsl::end(container), predicate), rsl::end(container));
    }

    template <typename It, typename T>
    bool contains(It first, It last, T&& value)
    {
      return rsl::find(first, last, rsl::forward<T>(value)) != last;
    }

    template <typename Container, typename T>
    bool contains_fwd(const Container& container, T&& value)
    {
      if constexpr(concepts::is_sequence_container<Container>)
      {
        return contains(rsl::cbegin(container), rsl::cend(container), rsl::forward<T>(value));
      }
      else
      {
        return container.find(rsl::forward<T>(value)) != container.cend();
      }
    }

    template <typename Container, typename T>
    bool contains_bwd(const Container& container, T&& value)
    {
      if constexpr(concepts::is_sequence_container<Container>)
      {
        return contains(rsl::crbegin(container), rsl::crend(container), rsl::forward<T>(value));
      }
      else
      {
        return container.find(rsl::forward<T>(value)) != container.cend();
      }
    }

    template <typename It, typename Predicate>
    bool contains_if(It first, It last, const Predicate& pred)
    {
      return rsl::find_if(first, last, pred) != last;
    }

    template <typename Container, typename Predicate>
    bool contains_fwd_if(const Container& container, const Predicate& pred)
    {
      static_assert(concepts::is_sequence_container<Container>, "Container is not a sequence container!");
      return contains_if(rsl::cbegin(container), rsl::cend(container), pred);
    }

    template <typename Container, typename Predicate>
    bool contains_bwd_if(const Container& container, const Predicate& pred)
    {
      static_assert(concepts::is_sequence_container<Container>, "Container is not a sequence container!");
      return contains_if(rsl::crbegin(container), rsl::crend(container), pred);
    }

  } // namespace v1
} // namespace rsl
