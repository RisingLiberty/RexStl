// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: time_digits.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/iostream.h"
#include "rex_std/format.h"

namespace rsl
{
  inline namespace v1
  {
    struct time_digits
    {
      time_digits(card32 value)
      {
        high = static_cast<char>(value * 0.1f);
        low = static_cast<char>(value - high * 10);

        high += '0';
        low += '0';
      }

      char high;
      char low;
    };

    template <>
    struct formatter<time_digits>
    {
      auto parse(format_parse_context& ctx) const -> decltype(ctx.begin())
      {
        return ctx.begin();
      }

      template <typename FormatContext>
      auto format(const time_digits& digits, FormatContext& ctx) -> decltype(ctx.out())
      {
        format_to(ctx.out(), "{}{}", digits.high, digits.low);
      }
    };
  }

  rsl::ostream& operator<<(rsl::ostream& os, time_digits digits);
}
