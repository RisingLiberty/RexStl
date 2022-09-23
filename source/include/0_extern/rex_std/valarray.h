// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: valarray.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <valarray>

REX_RSL_BEGIN_NAMESPACE

template <typename T>
REX_STD_TEMPLATED_CLASS_ALIAS(valarray, T);

REX_STD_CLASS_ALIAS(slice);

template <typename T>
REX_STD_TEMPLATED_CLASS_ALIAS(slice_array, T);

REX_STD_CLASS_ALIAS(gslice);

template <typename T>
REX_STD_TEMPLATED_CLASS_ALIAS(gslice_array, T);

template <typename T>
REX_STD_TEMPLATED_CLASS_ALIAS(mask_array, T);

template <typename T>
REX_STD_TEMPLATED_CLASS_ALIAS(indirect_array, T);

REX_STD_FUNC_ALIAS(begin);
REX_STD_FUNC_ALIAS(end);
REX_STD_FUNC_ALIAS(operator+);
REX_STD_FUNC_ALIAS(operator-);
REX_STD_FUNC_ALIAS(operator*);
REX_STD_FUNC_ALIAS(operator/);
REX_STD_FUNC_ALIAS(operator%);
REX_STD_FUNC_ALIAS(operator&);
REX_STD_FUNC_ALIAS(operator|);
REX_STD_FUNC_ALIAS(operator^);
REX_STD_FUNC_ALIAS(operator<<);
REX_STD_FUNC_ALIAS(operator>>);
REX_STD_FUNC_ALIAS(operator&&);
REX_STD_FUNC_ALIAS(operator||);
REX_STD_FUNC_ALIAS(operator==);
REX_STD_FUNC_ALIAS(operator!=);
REX_STD_FUNC_ALIAS(operator<);
REX_STD_FUNC_ALIAS(operator<=);
REX_STD_FUNC_ALIAS(operator>);
REX_STD_FUNC_ALIAS(operator>=);

// REX_STD_FUNC_ALIAS(abs); // doesn't work because we have a rsl version
REX_STD_FUNC_ALIAS(exp);
REX_STD_FUNC_ALIAS(log);
REX_STD_FUNC_ALIAS(log10);
REX_STD_FUNC_ALIAS(pow);
REX_STD_FUNC_ALIAS(sqrt);

REX_STD_FUNC_ALIAS(sin);
REX_STD_FUNC_ALIAS(cos);
REX_STD_FUNC_ALIAS(tan);
REX_STD_FUNC_ALIAS(asin);
REX_STD_FUNC_ALIAS(acos);
REX_STD_FUNC_ALIAS(atan);
REX_STD_FUNC_ALIAS(atan2);

REX_STD_FUNC_ALIAS(sinh);
REX_STD_FUNC_ALIAS(cosh);
REX_STD_FUNC_ALIAS(tanh);

REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"
