// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: valarray.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <valarray>

namespace rsl
{
  inline namespace v1
  {

    RSL_TEMPLATED_CLASS_ALIAS(template <typename T>, valarray, T);

    RSL_CLASS_ALIAS(slice);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename T>, slice_array, T);

    RSL_CLASS_ALIAS(gslice);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename T>, gslice_array, T);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename T>, mask_array, T);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename T>, indirect_array, T);

    RSL_FUNC_ALIAS(begin);
    RSL_FUNC_ALIAS(operator+);
    RSL_FUNC_ALIAS(operator-);
    RSL_FUNC_ALIAS(operator*);
    RSL_FUNC_ALIAS(operator/);
    RSL_FUNC_ALIAS(operator%);
    RSL_FUNC_ALIAS(operator&);
    RSL_FUNC_ALIAS(operator|);
    RSL_FUNC_ALIAS(operator^);
    RSL_FUNC_ALIAS(operator<<);
    RSL_FUNC_ALIAS(operator>>);
    RSL_FUNC_ALIAS(operator&&);
    RSL_FUNC_ALIAS(operator||);
    RSL_FUNC_ALIAS(operator==);
    RSL_FUNC_ALIAS(operator!=);
    RSL_FUNC_ALIAS(operator<);
    RSL_FUNC_ALIAS(operator<=);
    RSL_FUNC_ALIAS(operator>);
    RSL_FUNC_ALIAS(operator>=);

    // RSL_FUNC_ALIAS(abs); // doesn't work because we have a rsl version
    RSL_FUNC_ALIAS(exp);
    RSL_FUNC_ALIAS(log);
    RSL_FUNC_ALIAS(log10);
    RSL_FUNC_ALIAS(pow);
    RSL_FUNC_ALIAS(sqrt);

    RSL_FUNC_ALIAS(sin);
    RSL_FUNC_ALIAS(cos);
    RSL_FUNC_ALIAS(tan);
    RSL_FUNC_ALIAS(asin);
    RSL_FUNC_ALIAS(acos);
    RSL_FUNC_ALIAS(atan);
    RSL_FUNC_ALIAS(atan2);

    RSL_FUNC_ALIAS(sinh);
    RSL_FUNC_ALIAS(cosh);
    RSL_FUNC_ALIAS(tanh);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
