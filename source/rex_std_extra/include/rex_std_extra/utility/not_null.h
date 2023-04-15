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

#include <type_traits>

namespace rsl
{
  inline namespace v1
  {

    template <typename T>
    class NotNull
    {
    public:
      constexpr NotNull(T* ptr)
          : m_ptr(ptr)
      {
        RSL_ASSERT_X(m_ptr != nullptr, "Can't assign a nullptr to a NotNull class");
      }

      constexpr NotNull(rsl::nullptr_t) = delete;

      template <typename U, rsl::EnableIf<rsl::is_convertible_v<U, T>, bool> = true>
      constexpr NotNull(const NotNull<U>& other)
          : NotNull(other.get())
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