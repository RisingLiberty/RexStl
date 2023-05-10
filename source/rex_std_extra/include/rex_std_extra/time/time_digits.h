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
#include "rex_std/format.h"
#include "rex_std/iostream.h"

namespace rsl
{
  inline namespace v1
  {
    struct time_digits
    {
      explicit time_digits(card32 value)
          : high(static_cast<char>(value * 0.1f))     // NOLINT(cppcoreguidelines-narrowing-conversions)
          , low(static_cast<char>(value - high * 10)) // NOLINT(cppcoreguidelines-narrowing-conversions)
      {
        high += '0';
        low += '0';
      }

      rsl::tiny_stack_string to_string() const
      {
        rsl::tiny_stack_string str;
        str += high;
        str += low;
        return str;
      }

      char high;
      char low;
    };

    template <>
    struct formatter<time_digits>
    {
      auto parse(format_parse_context& ctx) const -> decltype(ctx.begin()) // NOLINT(readability-convert-member-functions-to-static)
      {
        return ctx.begin();
      }

      template <typename FormatContext>
      auto format(const time_digits& digits, FormatContext& ctx) -> decltype(ctx.out())
      {
        return format_to(ctx.out(), "{}{}", digits.high, digits.low);
      }
    };
  
    rsl::ostream& operator<<(rsl::ostream& os, time_digits digits);

  } // namespace v1
} // namespace rsl
