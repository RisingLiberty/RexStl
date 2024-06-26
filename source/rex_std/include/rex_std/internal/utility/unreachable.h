// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: unreachable.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/attributes.h"
#include "rex_std/bonus/defines.h"

namespace rsl
{
  inline namespace v1
  {
    RSL_NO_RETURN inline void unreachable() // NOLINT(misc-definitions-in-headers)
    {
#if defined(__GNUC__) // GCC, Clang, ICC
      __builtin_unreachable();
#elif defined(_MSC_VER) // MSVC
      __assume(false);
#endif
    }

  } // namespace v1
} // namespace rsl
