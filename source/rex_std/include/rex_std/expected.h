// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: expected.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#ifdef RSL_ENABLE_WITH_CPP23

  #include "rex_std/disable_std_checking.h"
  #include "rex_std/std_alias_defines.h"

  #include <expected>

namespace rsl
{
  inline namespace v1
  {

    RSL_TEMPLATED_CLASS_ALIAS(expected, typename T, typename E);
    RSL_TEMPLATED_CLASS_ALIAS(unexpected, typename E);

    RSL_CLASS_ALIAS(unexpect_t);
    RSL_OBJECT_ALIAS(unexpect);

  } // namespace v1
} // namespace rsl

  #include "rex_std/enable_std_checking.h"

#endif
