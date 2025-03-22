// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: unique_array.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/utility/compressed_pair.h"
#include "rex_std/bonus/attributes.h"
#include "rex_std/bonus/types.h"
#include "rex_std/internal/memory/nullptr.h"
#include "rex_std/internal/type_traits/enable_if.h"
#include "rex_std/internal/type_traits/conjunction.h"
#include "rex_std/internal/type_traits/is_array.h"
#include "rex_std/internal/type_traits/remove_extent.h"
#include "rex_std/internal/type_traits/is_default_constructible.h"
#include "rex_std/internal/type_traits/is_pointer.h"
#include "rex_std/internal/type_traits/negation.h"
#include "rex_std/internal/utility/exchange.h"
#include "rex_std/internal/utility/swap.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      template <typename Deleter>
      using UniqueArrayEnableDefault = enable_if_t<conjunction_v<negation<is_pointer<Deleter>>, is_default_constructible<Deleter>>, int>;
    }

    template <typename T, typename Deleter = default_delete_array<T>>
    class unique_array
    {
    public:
      using pointer            = rsl::remove_extent_t<T>*;
      using const_pointer      = const rsl::remove_extent_t<T>*;
      using element_type       = rsl::remove_extent_t<T>;
      using const_element_type = const rsl::remove_extent_t<T>;
      using deleter_type       = Deleter;

      // constructs a unique_array that owns nothing
      template <typename Deleter2 = Deleter, internal::UniquePtrEnableDefault<Deleter2> = 0>
      constexpr unique_array()
        : m_cp_ptr_and_deleter(nullptr)
        , m_count(0)
      {
      }
      // constructs a unique_array that owns nothing
      template <typename Deleter2 = Deleter, internal::UniquePtrEnableDefault<Deleter2> = 0>
      constexpr unique_array(rsl::nullptr_t) // NOLINT(google-explicit-constructor): this needs to be explicit
        : m_cp_ptr_and_deleter(nullptr)
        , m_count(0)
      {
      }
      // construct a unique_array that owns ptr and copy constructs the deleter
      template <typename Deleter2 = Deleter, enable_if_t<is_constructible_v<Deleter, const Deleter2&>, bool> = true>
      unique_array(pointer ptr, card32 count, const Deleter2& deleter = Deleter2())
        : m_cp_ptr_and_deleter(ptr, deleter)
        , m_count(count)
      {
      }
      // construct a unique_array that owns ptr and copy constructs the deleter
      template <typename Deleter2, enable_if_t<conjunction_v<negation<is_reference<Deleter2>>, is_constructible<Deleter2, Deleter2>>, bool> = true>
      unique_array(pointer ptr, card32 count, Deleter2&& deleter)
        : m_cp_ptr_and_deleter(ptr, rsl::move(deleter))
        , m_count(count)
      {
      }
      template <typename Deleter2, enable_if_t<conjunction_v<is_reference<Deleter2>, is_constructible<Deleter2, remove_reference_t<Deleter2>>>, bool> = true>
      unique_array(pointer, remove_reference_t<Deleter2>&&) = delete;
      // dleters the copy constructor
      unique_array(const unique_array&) = delete;
      // construct a unique_array that takes ownership of the  ptr in the other unique_array.
      // perfectly forwards the deleter of the other unique_array.
      unique_array(unique_array&& right)
      {
        // Need to assign count first as it gets zeroed by the release func called below
        m_count = right.m_count;
        m_cp_ptr_and_deleter = compressed_pair<pointer, deleter_type>(right.release(), rsl::forward<Deleter>(right.get_deleter()));
      }
      // construct a unique_array that owns ptr and copy constructs the deleter
      template <
        typename T2, typename Deleter2,
        enable_if_t<conjunction_v<negation<is_array<T2>>, is_convertible<typename unique_array<T2, Deleter2>::pointer, pointer>, conditional_t<is_reference_v<Deleter>, is_same<Deleter, Deleter>, is_convertible<Deleter2, Deleter>>>, bool> = true>
      unique_array(unique_array<T2, Deleter2>&& right) // NOLINT(google-explicit-constructor)
        : m_cp_ptr_and_deleter(right.release(), rsl::forward<Deleter2>(right.get_deleter()))
        , m_count(right.m_count)
      {
      }
      ~unique_array()
      {
        reset();
      }

      unique_array& operator=(const unique_array&) = delete;
      unique_array& operator=(unique_array&& other) noexcept
      {
        card32 other_count = other.m_count;
        reset(other.release());
        m_count = other_count;
        return *this;
      }

      void swap(unique_array& other)
      {
        T* tmp_ptr       = m_cp_ptr_and_deleter.first();
        card32 tmp_count = m_count;

        m_cp_ptr_and_deleter.first()   = other.m_cp_ptr_and_deleter.first();
        m_count = other.m_count;

        other.m_cp_ptr_and_deleter.first()   = tmp_ptr;
        other.m_count = tmp_count;
      }

      RSL_NO_DISCARD const_pointer get() const
      {
        return m_cp_ptr_and_deleter.first();
      }
      RSL_NO_DISCARD pointer get()
      {
        return m_cp_ptr_and_deleter.first();
      }
      // returns the deleter object used to destroy the managed object
      RSL_NO_DISCARD const deleter_type& get_deleter() const
      {
        return m_cp_ptr_and_deleter.second();
      }
      // returns the deleter object used to destroy the managed object
      RSL_NO_DISCARD deleter_type& get_deleter()
      {
        return m_cp_ptr_and_deleter.second();
      }
      RSL_NO_DISCARD pointer release()
      {
        m_count = 0;
        return rsl::exchange(m_cp_ptr_and_deleter.first(), pointer());
      }

      card32 elem_size() const
      {
        return sizeof(T);
      }
      card32 byte_size() const
      {
        return count() * elem_size();
      }
      card32 count() const
      {
        return m_count;
      }

      element_type& operator[](card32 idx)
      {
        return m_cp_ptr_and_deleter.first()[idx];
      }
      const_element_type& operator[](card32 idx) const
      {
        return m_cp_ptr_and_deleter.first()[idx];
      }

      explicit operator bool() const
      {
        return m_cp_ptr_and_deleter.first() != nullptr;
      }

      void reset(pointer ptr = pointer(), card32 count = 0)
      {
        m_cp_ptr_and_deleter.second()(m_cp_ptr_and_deleter.first(), sizeof(element_type) * m_count);
        m_cp_ptr_and_deleter.first()   = ptr;
        m_count = count;
      }

      pointer begin()
      {
        return m_cp_ptr_and_deleter.first();
      }
      const_pointer begin() const
      {
        return m_cp_ptr_and_deleter.first();
      }
      const_pointer cbegin() const
      {
        return m_cp_ptr_and_deleter.first();
      }
      pointer end()
      {
        return m_cp_ptr_and_deleter.first() + m_count;
      }
      const_pointer end() const
      {
        return m_cp_ptr_and_deleter.first() + m_count;
      }
      const_pointer cend() const
      {
        return m_cp_ptr_and_deleter.first() + m_count;
      }

    private:
      compressed_pair<pointer, deleter_type> m_cp_ptr_and_deleter {};
      card32 m_count;
    };

    template <typename T, rsl::enable_if_t<rsl::is_array_v<T>, bool> = true>
    RSL_NO_DISCARD unique_array<rsl::remove_extent_t<T>> make_unique(card32 size)
    {
      using Elem = rsl::remove_extent_t<T>;
      return unique_array<Elem>(new Elem[size](), size);
    }

  } // namespace v1
} // namespace rsl
