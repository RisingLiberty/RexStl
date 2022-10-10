// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: assert_impl.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

//-----------------------------------------------------------------------------
// Implementation of the assert function. This is implemented in a different file
// to avoid circular inclusion issues.
//-----------------------------------------------------------------------------

#pragma once

namespace rsl
{
  inline namespace v1
  {

    template <typename... Args>
    bool rex_assert(bool cond, Args&&... args)
    {
      return false;
    }

  } // namespace v1
} // namespace rsl