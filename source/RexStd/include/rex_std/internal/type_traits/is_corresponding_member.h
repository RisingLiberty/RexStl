// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_corresponding_member.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename S1, typename S2, typename M1, typename M2>
    inline constexpr bool is_corresponding_member(M !S1::*mp, M2 S2::*mq)
    {
      return __is_corresponding_member(S1, S2, M1, M2);
    }

  } // namespace v1
} // namespace rsl