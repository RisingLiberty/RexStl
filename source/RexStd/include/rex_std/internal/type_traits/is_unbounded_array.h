// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_unbounded_array.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename T>
    struct IsUnboundedArrayStruct : public false_type
    {
    };

    template <typename T>
    struct IsUnboundedArrayStruct<T[]> : public true_type
    {
    };

    template <typename T>
    inline constexpr bool IsUnboundedArray = IsUnboundedArrayStruct<T>::value;

  } // namespace v1
} // namespace rsl