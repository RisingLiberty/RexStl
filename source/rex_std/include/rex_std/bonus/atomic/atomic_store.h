// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: atomic_store.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/atomic/atomic_fixed_width_type.h"

namespace rsl
{
  inline namespace v1
  {
    void atomic_store(atomic_fixed_width_type_t<8> val);
    void atomic_store(atomic_fixed_width_type_t<16> val);
    void atomic_store(atomic_fixed_width_type_t<32> val);
    void atomic_store(atomic_fixed_width_type_t<64> val);
  }
}
