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

#include "rex_std/bonus/attributes.h"
#include "rex_std/bonus/types.h"
#include "rex_std/internal/memory/nullptr.h"
#include "rex_std/internal/type_traits/enable_if.h"
#include "rex_std/internal/type_traits/is_array.h"
#include "rex_std/internal/type_traits/remove_extent.h"
#include "rex_std/internal/utility/exchange.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename T>
    class unique_array
    {
    public:
      using pointer            = rsl::remove_extent_t<T>*;
      using const_pointer      = const rsl::remove_extent_t<T>*;
      using element_type       = rsl::remove_extent_t<T>;
      using const_element_type = const rsl::remove_extent_t<T>;

      unique_array()
          : m_ptr(nullptr)
          , m_count(0)
      {
      }
      unique_array(rsl::nullptr_t) // NOLINT(google-explicit-constructor)
          : m_ptr(nullptr)
          , m_count(0)
      {
      }

      unique_array(pointer pointer, card32 count)
          : m_ptr(pointer)
          , m_count(count)
      {
      }

      unique_array(const unique_array&) = delete;
      unique_array(unique_array&& other) noexcept
          : m_ptr()
          , m_count(other.count())
      {
        m_ptr = other.release();
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
        T* tmp_ptr       = m_ptr;
        card32 tmp_count = m_count;

        m_ptr   = other.m_ptr;
        m_count = other.m_count;

        other.m_ptr   = tmp_ptr;
        other.m_count = tmp_count;
      }

      RSL_NO_DISCARD const_pointer get() const
      {
        return m_ptr;
      }
      RSL_NO_DISCARD pointer get()
      {
        return m_ptr;
      }
      RSL_NO_DISCARD pointer release()
      {
        m_count = 0;
        return rsl::exchange(m_ptr, pointer());
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
        return m_ptr[idx];
      }
      const_element_type& operator[](card32 idx) const
      {
        return m_ptr[idx];
      }

      explicit operator bool() const
      {
        return m_ptr != nullptr;
      }

      void reset(pointer ptr = pointer(), card32 count = 0)
      {
        operator delete[](m_ptr, sizeof(element_type) * m_count);
        m_ptr   = ptr;
        m_count = count;
      }

      pointer begin()
      {
        return m_ptr;
      }
      const_pointer begin() const
      {
        return m_ptr;
      }
      const_pointer cbegin() const
      {
        return m_ptr;
      }
      pointer end()
      {
        return m_ptr + m_count;
      }
      const_pointer end() const
      {
        return m_ptr + m_count;
      }
      const_pointer cend() const
      {
        return m_ptr + m_count;
      }

    private:
      rsl::remove_extent_t<T>* m_ptr;
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
