// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: iterator_traits.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/iterator/iterator_tags.h"
#include "rex_std/internal/type_traits/void.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      template <typename T, typename = void>
      struct get_itr_pointer_type
      {
        using type = typename T::pointer;
      };
      template <typename T>
      struct get_itr_pointer_type<T, void_t<typename T::const_pointer>>
      {
        using type = typename T::const_pointer;
      };

      template <typename T, typename = void>
      struct get_itr_reference_type
      {
        using type = typename T::reference;
      };
      template <typename T>
      struct get_itr_reference_type<T, void_t<typename T::const_reference>>
      {
        using type = typename T::const_reference;
      };
    }

    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Aug/2022)
    // in C++20, this structure changed making it more complex to implement.
    // this is not supported in Rex at the moment as it's not needed.
    // iterator traits
    template <typename Iterator>
    struct iterator_traits
    {
      using iterator_category = typename Iterator::iterator_category;
      using value_type = typename Iterator::value_type;
      using difference_type = typename Iterator::difference_type;
      using pointer = typename Iterator::pointer;
      using const_pointer = typename internal::get_itr_pointer_type<Iterator>::type;
      using reference = typename Iterator::reference;
      using const_reference = typename internal::get_itr_reference_type<Iterator>::type;
    };
    template <typename T>
    struct iterator_traits<T*>
    {
      using iterator_category = rsl::random_access_iterator_tag;
      using value_type = T;
      using difference_type = ptrdiff;
      using pointer = T*;
      using const_pointer = const T*;
      using reference = T&;
      using const_reference = const T&;
    };
    template <typename T>
    struct iterator_traits<const T*>
    {
      using iterator_category = rsl::random_access_iterator_tag;
      using value_type = T;
      using difference_type = ptrdiff;
      using pointer = const T*;
      using const_pointer = const T*;
      using reference = const T&;
      using const_reference = const T&;
    };

  } // namespace v1
} // namespace rsl
