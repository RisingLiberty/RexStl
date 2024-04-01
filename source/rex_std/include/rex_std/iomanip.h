// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: iomanip.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <iomanip>

namespace rsl
{
  inline namespace v1
  {

    RSL_FUNC_ALIAS(resetiosflags);
    RSL_FUNC_ALIAS(setiosflags);
    RSL_FUNC_ALIAS(setbase);
    RSL_FUNC_ALIAS(setfill);
    RSL_FUNC_ALIAS(setprecision);
    RSL_FUNC_ALIAS(setw);
    RSL_FUNC_ALIAS(get_money);
    RSL_FUNC_ALIAS(put_money);
    RSL_FUNC_ALIAS(get_time);
    RSL_FUNC_ALIAS(put_time);
    RSL_FUNC_ALIAS(quoted);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
