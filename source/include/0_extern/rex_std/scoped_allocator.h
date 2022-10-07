// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: scoped_allocator.h
// Copyright (c) Nick De Breuck 2022
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

    template <typename OuterAlloc, typename... InnerAlloc>
    REX_STD_TEMPLATED_CLASS_ALIAS(scoped_allocator_adaptor, OuterAlloc, InnerAlloc...);

    REX_STD_FUNC_ALIAS(operator==);
    REX_STD_FUNC_ALIAS(operator!=);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
