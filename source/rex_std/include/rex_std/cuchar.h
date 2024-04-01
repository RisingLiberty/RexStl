// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: cuchar.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <cuchar>

namespace rsl
{
  inline namespace v1
  {

    RSL_CLASS_ALIAS(mbstate_t);
    RSL_CLASS_ALIAS(size_t);

    RSL_FUNC_ALIAS(mbrtoc16);
    RSL_FUNC_ALIAS(c16rtomb);
    RSL_FUNC_ALIAS(mbrtoc32);
    RSL_FUNC_ALIAS(c32rtomb);

#ifdef RSL_ENABLE_WITH_CPP20
    RSL_FUNC_ALIAS(mbrtoc8);
    RSL_FUNC_ALIAS(c8rtomb);
#endif // RSL_ENABLE_WITH_CPP20

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
