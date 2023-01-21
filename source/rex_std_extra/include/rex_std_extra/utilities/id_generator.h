// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: id_generator.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

namespace rsl { inline namespace v1 {

using ID = card32;

namespace id_generator
{
  // unique ID based on type
  template <typename T>
  ID new_id()
  {
    static ID id = 0;
    return id++;
  }

  // Global unique id
  ID new_id();
} // namespace id_generator

}}