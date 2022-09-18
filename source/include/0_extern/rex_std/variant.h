// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: variant.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <variant>

#include "rex_std/compare.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename ... Types>
    REX_STD_TEMPLATED_CLASS_ALIAS(variant, Types...);

    REX_STD_CLASS_ALIAS(monostate);

    template <typename T>
    REX_STD_TEMPLATED_CLASS_ALIAS(variant_size, T);

    template <typename T>
    REX_STD_TEMPLATED_OBJECT_ALIAS(variant_size_v, T);

    template <size_t I, typename T>
    REX_STD_TEMPLATED_CLASS_ALIAS(variant_alternative, I, T);

    template <size_t I, typename T>
    REX_STD_TEMPLATED_OBJECT_ALIAS(variant_alternative_t, I, T);

    template <typename T>
    struct hash;

    REX_STD_OBJECT_ALIAS(variant_npos);

    REX_STD_FUNC_ALIAS(visit);
    REX_STD_FUNC_ALIAS(holds_alternative);
    REX_STD_FUNC_ALIAS(get);
    REX_STD_FUNC_ALIAS(get_if);
    REX_STD_FUNC_ALIAS(operator==);
    REX_STD_FUNC_ALIAS(operator!=);
    REX_STD_FUNC_ALIAS(operator<);
    REX_STD_FUNC_ALIAS(operator<=);
    REX_STD_FUNC_ALIAS(operator>);
    REX_STD_FUNC_ALIAS(operator>=);
    
REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"
