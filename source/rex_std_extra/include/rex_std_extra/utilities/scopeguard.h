// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: scopeguard.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/functional.h"

namespace rsl
{
  inline namespace v1
  {

    class scope_guard
    {
    public:
      scope_guard(rsl::function<void()> func);
      ~scope_guard();

      void release();

    private:
      rsl::function<void()> m_function;
      bool m_is_released;
    };

  } // namespace v1
} // namespace rsl