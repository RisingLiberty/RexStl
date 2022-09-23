// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: system_error.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/compare.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <system_error>

REX_RSL_BEGIN_NAMESPACE

REX_STD_CLASS_ALIAS(error_category);
REX_STD_CLASS_ALIAS(error_condition);
REX_STD_CLASS_ALIAS(errc);
REX_STD_CLASS_ALIAS(error_code);
REX_STD_CLASS_ALIAS(system_error);

template <typename T>
REX_STD_TEMPLATED_CLASS_ALIAS(is_error_code_enum, T);
template <typename T>
REX_STD_TEMPLATED_CLASS_ALIAS(is_error_condition_enum, T);

template <typename T>
REX_STD_TEMPLATED_OBJECT_ALIAS(is_error_code_enum_v, T);
template <typename T>
REX_STD_TEMPLATED_OBJECT_ALIAS(is_error_condition_enum_v, T);

REX_STD_FUNC_ALIAS(generic_category);
REX_STD_FUNC_ALIAS(system_category);
REX_STD_FUNC_ALIAS(operator==);
REX_STD_FUNC_ALIAS(operator!=);
REX_STD_FUNC_ALIAS(operator<);
REX_STD_FUNC_ALIAS(operator<<);
REX_STD_FUNC_ALIAS(make_error_code);
REX_STD_FUNC_ALIAS(make_error_condition);

REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"
