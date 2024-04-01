// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: stdfloat.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#ifdef RSL_ENABLE_WITH_CPP23

  #include "rex_std/disable_std_checking.h"
  #include "rex_std/std_alias_defines.h"

  #include <stdfloat>

namespace rsl
{
  inline namespace v1
  {

    RSL_CLASS_ALIAS(float16_t);
    RSL_CLASS_ALIAS(float32_t);
    RSL_CLASS_ALIAS(float64_t);
    RSL_CLASS_ALIAS(float128_t);
    RSL_CLASS_ALIAS(bfloat16_t);

  } // namespace v1
} // namespace rsl

  #include "rex_std/enable_std_checking.h"

#endif