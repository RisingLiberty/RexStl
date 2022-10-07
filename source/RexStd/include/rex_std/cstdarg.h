// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: cstdarg.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <cstdarg>

namespace rsl
{
  inline namespace v1
  {

    REX_STD_CLASS_ALIAS(va_list);

  }
} // namespace rsl

#include "rex_std/enable_std_checking.h"