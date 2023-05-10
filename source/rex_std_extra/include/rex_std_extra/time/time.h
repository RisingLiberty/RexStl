// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: time.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/ostream.h"

namespace rsl
{
  inline namespace v1
  {

    class time
    {
    public:
      time();
      time(card32 hours, card32 minutes, card32 seconds);

      card32 hours() const;
      card32 minutes() const;
      card32 seconds() const;

      rsl::small_stack_string to_string() const;

      bool operator>(const time& time) const;
      bool operator>=(const time& time) const;
      bool operator<(const time& time) const;
      bool operator<=(const time& time) const;

      bool operator==(const time& time) const;
      bool operator!=(const time& time) const;

    private:
      card32 m_hours;
      card32 m_minutes;
      card32 m_seconds;
    };

    ostream& operator<<(ostream& os, const time& time);

  } // namespace v1
} // namespace rsl

#ifdef REX_PLATFORM_WINDOWS
  #include "rex_std_extra/time/win/win_time.h"
#endif