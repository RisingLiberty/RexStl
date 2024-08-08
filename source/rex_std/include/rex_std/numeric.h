// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: numeric.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/internal/numeric/accumulate.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <numeric>

namespace rsl
{
  inline namespace v1
  {

    RSL_FUNC_ALIAS(iota);
    RSL_FUNC_ALIAS(reduce);
    RSL_FUNC_ALIAS(transform_reduce);
    RSL_FUNC_ALIAS(inner_product);
    RSL_FUNC_ALIAS(adjacent_difference);
    RSL_FUNC_ALIAS(partial_sum);
    RSL_FUNC_ALIAS(inclusive_scan);
    RSL_FUNC_ALIAS(exclusive_scan);
    RSL_FUNC_ALIAS(transform_inclusive_scan);
    RSL_FUNC_ALIAS(transform_exclusive_scan);
    RSL_FUNC_ALIAS(gcd);
    RSL_FUNC_ALIAS(lcm);
    RSL_FUNC_ALIAS(midpoint);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"