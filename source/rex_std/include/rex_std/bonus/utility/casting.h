// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: casting.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/assert.h"
#include "rex_std/type_traits.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename ToType, typename FromType>
    constexpr ToType numeric_cast(const FromType value)
    {
      static_assert(rsl::is_arithmetic_v<FromType>, "FromType must be or arithmetic type");
      return static_cast<ToType>(value);
    }

    template <typename ToType, typename FromType>
    constexpr ToType safe_numeric_cast(const FromType value)
    {
      static_assert(rsl::is_arithmetic_v<FromType>, "FromType must be arithmetic type");
#if RSL_ENABLE_SAFE_CASTING
      ToType to_val = static_cast<ToType>(value);
      if(to_val != value) // narrow check
      {
        RSL_ERROR("numeric cast loses value");
      }

      constexpr auto max_signed_val = rsl::numeric_limits<rsl::make_signed_t<FromType>>::max();

  // it's okay to disable the warning here as we'd get a compiler error anyway,
  // should this function be called at compile time
  #pragma warning(push)
  #pragma warning(disable : 4389)

      // comparing the values here would never trigger because the signed would be promoted to an unsigned
      if(to_val > max_signed_val || to_val < 0) // sign cast check
      {
        RSL_ERROR("numeric cast loses value");
      }

  #pragma pop

      return to_val;
#else
      return numeric_cast<ToType>(value);
#endif
    }

  } // namespace v1
} // namespace rsl