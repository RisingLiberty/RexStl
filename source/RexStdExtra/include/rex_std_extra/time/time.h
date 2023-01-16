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

REX_RSL_BEGIN_NAMESPACE

class Time
{
public:
  Time();
  Time(card32 hours, card32 minutes, card32 seconds);

  card32 hours() const;
  card32 minutes() const;
  card32 seconds() const;

  bool operator>(const Time& time) const;
  bool operator>=(const Time& time) const;
  bool operator<(const Time& time) const;
  bool operator<=(const Time& time) const;

  bool operator==(const Time& time) const;
  bool operator!=(const Time& time) const;

private:
  card32 m_hours;
  card32 m_minutes;
  card32 m_seconds;
};

class OStream;
OStream& operator<<(OStream& os, const Time& time);

REX_RSL_END_NAMESPACE

#ifdef REX_PLATFORM_WINDOWS
  #include "rex_std_extra/time/win/win_time.h"
#endif