// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: aligned_storage.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/memory/byte.h"
#include "rex_std/internal/memory/memcpy.h"
#include "rex_std/internal/utility/forward.h"

#include <new> // needed for placement new

REX_RSL_BEGIN_NAMESPACE

/// RSL Comment: Different from ISO C++ Standard at time of writing (26/Aug/2022)
template <typename T>
class aligned_storage
{
public:
  template <typename... Args>
  void set(Args&&... args)
  {
    new(static_cast<void*>(m_buff)) T(rsl::forward<Args>(args)...);
  }
  void set(const T* newVal)
  {
    rsl::memcpy(m_buff, newVal, sizeof(T));
  }
  T* get()
  {
    return reinterpret_cast<T*>(m_buff);
  }

private:
  alignas(T) rsl::byte m_buff[sizeof(T)];
};

REX_RSL_END_NAMESPACE
