// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: destroy_n.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/memory/addressof.h"

REX_RSL_BEGIN_NAMESPACE

template <typename ForwardIt, typename Size>
constexpr ForwardIt destroy_n(ForwardIt first, Size n)
{
  for(; n > 0; ++first, --n)
  {
    destroy_at(addressof(*first));
  }
}

REX_RSL_END_NAMESPACE
