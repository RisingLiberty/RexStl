// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: timepoint.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/time/date.h"
#include "rex_std/bonus/time/time.h"
#include "rex_std/bonus/types.h"
#include "rex_std/ostream.h"

namespace rsl
{
  inline namespace v1
  {
    class time_point
    {
    public:
      time_point();
      time_point(const rsl::date& date, const rsl::time& time);

      const rsl::date& date() const;
      const rsl::time& time() const;

      bool operator>(const time_point& timepoint) const;
      bool operator>=(const time_point& timepoint) const;
      bool operator<(const time_point& timepoint) const;
      bool operator<=(const time_point& timepoint) const;

      bool operator==(const time_point& timepoint) const;
      bool operator!=(const time_point& timepoint) const;

      float32 operator-(const time_point& other) const;

    private:
      rsl::time m_time;
      rsl::date m_date;
    };

    rsl::string to_string(const time_point& timepoint);

    ostream& operator<<(ostream& os, const time_point& timepoint);

    template <>
    struct formatter<time_point>
    {
      auto parse(format_parse_context& ctx) const -> decltype(ctx.begin()) // NOLINT(readability-convert-member-functions-to-static)
      {
        return ctx.begin();
      }

      template <typename FormatContext>
      auto format(const time_point& timepoint, FormatContext& ctx) -> decltype(ctx.out())
      {
        return format_to(ctx.out(), "{}", to_string(timepoint));
      }
    };

  } // namespace v1
} // namespace rsl

#ifdef RSL_PLATFORM_WINDOWS
  #include "rex_std/bonus/time/win/win_timepoint.h" // IWYU pragma: keep
#endif