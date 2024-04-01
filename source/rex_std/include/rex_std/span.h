// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: span.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <span>

namespace rsl
{
  inline namespace v1
  {

    RSL_OBJECT_ALIAS(dynamic_extent);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename T, size_t Extent = rsl::dynamic_extent>, span, T, Extent);

    RSL_FUNC_ALIAS(as_bytes);
    RSL_FUNC_ALIAS(as_writable_bytes);

    RSL_FUNC_ALIAS(begin);
    RSL_FUNC_ALIAS(cbegin);
    RSL_FUNC_ALIAS(cend);
    RSL_FUNC_ALIAS(rbegin);
    RSL_FUNC_ALIAS(crbegin);
    RSL_FUNC_ALIAS(rend);
    RSL_FUNC_ALIAS(crend);
    RSL_FUNC_ALIAS(size);
    RSL_FUNC_ALIAS(ssize);
    RSL_FUNC_ALIAS(empty);
    RSL_FUNC_ALIAS(data);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
