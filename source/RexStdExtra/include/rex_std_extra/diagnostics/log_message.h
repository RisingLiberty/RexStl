// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: log_message.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/string/stack_string.h"
#include "rex_std/bonus/types.h"
#include "rex_std/ostream.h"
#include "rex_std/sstream.h"
#include "rex_std_extra/diagnostics/console_colors.h"
#include "rex_std_extra/time/time.h"

REX_RSL_BEGIN_NAMESPACE

enum class LogLevel
{
  Assert,
  Error,
  Warning,
  Info,
  Todo,
  Debug,
  Trace,
  Undefined
};

ConsoleColor log_level_to_color(LogLevel level);
LogLevel log_color_to_level(ConsoleColor color);

struct TimeDigits
{
public:
  TimeDigits(card32 value);

  char8 high;
  char8 low;
};

OStream& operator<<(OStream& os, TimeDigits digits);

SmallStackString time_to_string(const Time& time);
SmallStackString formatted_time_string(const Time& time_point);

class LogMessage
{
public:
  template <typename... Args>
  LogMessage(ConsoleColor color, LogLevel log_level, Args&&... args)
      : m_color(color)
      , m_log_level(log_level)
      , m_time(rsl::current_time())
  {
    m_message = full_message(rsl::forward<Args>(args)...);
  }

  BigStackString to_string() const;

  BigStackString message_only() const;
  ConsoleColor color() const;
  LogLevel log_level() const;
  const Time& time_point() const;

private:
  template <typename... Args>
  BigStackString full_message(Args&&... args)
  {
    return rsl::stack_string_from_message<BigStackString>(rsl::forward<Args>(args)...);
  }

  BigStackString m_message;
  ConsoleColor m_color;
  LogLevel m_log_level;
  Time m_time;
};

REX_RSL_END_NAMESPACE