// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: clocale.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <clocale>

namespace rsl
{
  inline namespace v1
  {

    REX_STD_CLASS_ALIAS(lconv);

    REX_STD_FUNC_ALIAS(setlocale);
    REX_STD_FUNC_ALIAS(localeconv);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
