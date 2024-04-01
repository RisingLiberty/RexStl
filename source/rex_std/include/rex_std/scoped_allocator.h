// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: scoped_allocator.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <scoped_allocator>

namespace rsl
{
  inline namespace v1
  {

    RSL_TEMPLATED_CLASS_ALIAS(template <typename OuterAlloc, typename... InnerAlloc>, scoped_allocator_adaptor, OuterAlloc, InnerAlloc...);

    RSL_FUNC_ALIAS(operator==);
    RSL_FUNC_ALIAS(operator!=);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
