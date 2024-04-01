// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: compare.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#ifdef RSL_ENABLE_WITH_CPP20

  #include "rex_std/disable_std_checking.h"
  #include "rex_std/std_alias_defines.h"

  #include <compare>

namespace rsl
{
  inline namespace v1
  {

    RSL_CLASS_ALIAS(partial_ordering);

    template <typename T, typename Cat = rsl::partial_ordering>
    using three_way_comparable = rsl::three_way_comparable<T, Cat>;
    template <typename T, typename U, typename Cat = rsl::partial_ordering>
    using three_way_comparable_with = rsl::three_way_comparable_with<T, U, Cat>;

    RSL_CLASS_ALIAS(weak_ordering);
    RSL_CLASS_ALIAS(strong_ordering);

    RSL_CLASS_ALIAS(common_comparison_category);
    RSL_CLASS_ALIAS(compare_three_way_result);
    RSL_CLASS_ALIAS(compare_three_way);

    RSL_OBJECT_ALIAS(strong_order);
    RSL_OBJECT_ALIAS(weak_order);
    RSL_OBJECT_ALIAS(partial_order);
    RSL_OBJECT_ALIAS(compare_strong_order_fallback);
    RSL_OBJECT_ALIAS(compare_weak_order_fallback);
    RSL_OBJECT_ALIAS(compare_partial_order_fallback);

    RSL_FUNC_ALIAS(is_eq);
    RSL_FUNC_ALIAS(is_neq);
    RSL_FUNC_ALIAS(is_lt);
    RSL_FUNC_ALIAS(is_lteq);
    RSL_FUNC_ALIAS(is_gt);
    RSL_FUNC_ALIAS(is_gteq);

  } // namespace v1
} // namespace rsl

  #include "rex_std/enable_std_checking.h"

#endif // RSL_ENABLE_WITH_CPP20
