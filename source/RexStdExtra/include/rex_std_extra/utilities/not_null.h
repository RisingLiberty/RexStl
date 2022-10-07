// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: not_null.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include <type_traits>

REX_RSL_BEGIN_NAMESPACE

template <typename T>
class NotNull
{
public:
  constexpr NotNull(T* ptr)
      : m_ptr(ptr)
  {
    REX_ASSERT_X(m_ptr != nullptr, "Can't assign a nullptr to a NotNull class");
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

REX_RSL_END_NAMESPACE