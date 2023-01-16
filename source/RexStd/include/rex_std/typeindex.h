// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: typeindex.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/compare.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <typeindex>

namespace rsl
{
  inline namespace v1
  {

    REX_STD_CLASS_ALIAS(type_index);
    template <typename T>
    struct hash;

  } // namespace v1
} // namespace rsl
#include "rex_std/enable_std_checking.h"
