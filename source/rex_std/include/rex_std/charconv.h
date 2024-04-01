// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: charconv.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <charconv>

namespace rsl
{
  inline namespace v1
  {

    RSL_CLASS_ALIAS(chars_format);

    RSL_FUNC_ALIAS(from_chars);
    RSL_FUNC_ALIAS(to_chars);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
