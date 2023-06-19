// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: mutex.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/mutex/mutex_base.h"

namespace rsl
{
  inline namespace v1
  {
    class mutex : public rsl::internal::mutex_base
    {
    public:
      mutex() = default;

      mutex(const mutex&) = delete;
      mutex(mutex&&)      = delete;
      ~mutex()            = default;

      mutex& operator=(const mutex&) = delete;
      mutex& operator=(mutex&&)      = delete;
    };
  } // namespace v1
} // namespace rsl
