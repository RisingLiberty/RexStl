// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: print.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#ifdef RSL_ENABLE_WITH_CPP23

  #include "rex_std/disable_std_checking.h"
  #include "rex_std/std_alias_defines.h"

  #include <print>

namespace rsl
{
  inline namespace v1
  {

    RSL_FUNC_ALIAS(print);
    RSL_FUNC_ALIAS(println);
    RSL_FUNC_ALIAS(vprint_unicode);
    RSL_FUNC_ALIAS(vprint_nounicode);

  } // namespace v1
} // namespace rsl

  #include "rex_std/enable_std_checking.h"

#endif // RSL_ENABLE_WITH_CPP23