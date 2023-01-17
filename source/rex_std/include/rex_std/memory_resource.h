// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: memory_resource.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/enable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <memory_resource>

namespace rsl
{
  inline namespace v1
  {

    namespace pmr
    {
      using namespace std::pmr;
    }

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
