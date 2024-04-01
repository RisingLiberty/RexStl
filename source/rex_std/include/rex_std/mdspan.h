// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: mdspan.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#ifdef RSL_ENABLE_WITH_CPP23

  #include "rex_std/compare.h"
  #include "rex_std/disable_std_checking.h"
  #include "rex_std/initializer_list.h"
  #include "rex_std/std_alias_defines.h"

  #include <mdspan>

namespace rsl
{
  inline namespace v1
  {

    // No pages about this exist yet on cppreference

  }
} // namespace rsl

  #include <rex_std/enable_std_checking.h>

#endif // RSL_ENABLE_WITH_CPP23
