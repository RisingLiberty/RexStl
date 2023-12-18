// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: not_null.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/enable_if.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename T>
    class not_null
    {
    public:
      constexpr not_null(T* ptr)
          : m_ptr(ptr)
      {
        RSL_ASSERT_X(m_ptr != nullptr, "Can't assign a nullptr to a not_null class");
      }

      constexpr not_null(rsl::nullptr_t) = delete;

      template <typename U, rsl::enable_if_t<rsl::is_convertible_v<U, T>, bool> = true>
      constexpr not_null(const not_null<U>& other)
          : not_null(other.get())
      {
      }

      const T* get() const
      {
        return m_ptr;
      }
      T* get()
      {
        return m_ptr;
      }

      const T& operator*() const
      {
        return *m_ptr;
      }
      T& operator*()
      {
        return *m_ptr;
      }

    private:
      T* m_ptr;
    };

  } // namespace v1
} // namespace rsl