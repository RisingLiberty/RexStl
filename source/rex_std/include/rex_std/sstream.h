// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: sstream.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/memory/typed_allocator.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/internal/string/char_traits.h"
#include "rex_std/std_alias_defines.h"

#include <sstream>

namespace rsl
{
  inline namespace v1
  {
    REX_STD_CLASS_ALIAS(stringstream);
  }
} // namespace rsl

#include "rex_std/enable_std_checking.h"