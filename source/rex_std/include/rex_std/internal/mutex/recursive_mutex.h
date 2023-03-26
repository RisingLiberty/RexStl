// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: recursive_mutex.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/mutex/mutex_base.h"

namespace rsl
{
  inline namespace v1
  {
    class recursive_mutex : public internal::mutex_base 
    {
    public:
      recursive_mutex() 
        : rsl::internal::mutex_base()
      {}

      REX_NO_DISCARD bool try_lock()
      {
        return rsl::internal::mutex_base::try_lock();
      }

      recursive_mutex(const recursive_mutex&) = delete;
      recursive_mutex& operator=(const recursive_mutex&) = delete;
    };
  }
}
