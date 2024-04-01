// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: fenv.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <cfenv>

namespace rsl
{
  inline namespace v1
  {

    RSL_CLASS_ALIAS(fenv_t);
    RSL_CLASS_ALIAS(fexcept_t);

    RSL_FUNC_ALIAS(feclearexcept);
    RSL_FUNC_ALIAS(fetestexcept);
    RSL_FUNC_ALIAS(feraiseexcept);
    RSL_FUNC_ALIAS(fegetexceptflag);
    RSL_FUNC_ALIAS(fesetexceptflag);
    RSL_FUNC_ALIAS(fegetround);
    RSL_FUNC_ALIAS(fesetround);
    RSL_FUNC_ALIAS(fegetenv);
    RSL_FUNC_ALIAS(fesetenv);
    RSL_FUNC_ALIAS(feholdexcept);
    RSL_FUNC_ALIAS(feupdateenv);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
