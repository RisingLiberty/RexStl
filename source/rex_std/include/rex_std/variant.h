// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: variant.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/compare.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <variant>

namespace rsl
{
  inline namespace v1
  {

    RSL_TEMPLATED_CLASS_ALIAS(template <typename... Types>, variant, Types...);

    RSL_CLASS_ALIAS(monostate);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename T>, variant_size, T);

    RSL_TEMPLATED_OBJECT_ALIAS(template <typename T>, variant_size_v, T);

    RSL_TEMPLATED_CLASS_ALIAS(template <size_t I, typename T>, variant_alternative, I, T);

    RSL_TEMPLATED_OBJECT_ALIAS(template <size_t I, typename T>, variant_alternative_t, I, T);

    template <typename T>
    struct hash;

    RSL_OBJECT_ALIAS(variant_npos);

    RSL_FUNC_ALIAS(visit);
    RSL_FUNC_ALIAS(holds_alternative);
    RSL_FUNC_ALIAS(get);
    RSL_FUNC_ALIAS(get_if);
    RSL_FUNC_ALIAS(operator==);
    RSL_FUNC_ALIAS(operator!=);
    RSL_FUNC_ALIAS(operator<);
    RSL_FUNC_ALIAS(operator<=);
    RSL_FUNC_ALIAS(operator>);
    RSL_FUNC_ALIAS(operator>=);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
