// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: log_message.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/diagnostics/log_message.h"

#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::ConsoleColor rsl::log_level_to_color(LogLevel level)
{
  switch(level)
  {
    case rsl::LogLevel::Assert: return rsl::console_colors::Assert;
    case rsl::LogLevel::Error: return rsl::console_colors::Error;
    case rsl::LogLevel::Warning: return rsl::console_colors::Warning;
    case rsl::LogLevel::Info: return rsl::console_colors::Info;
    case rsl::LogLevel::Todo: return rsl::console_colors::Todo;
    case rsl::LogLevel::Debug: return rsl::console_colors::Debug;
    case rsl::LogLevel::Trace: return rsl::console_colors::Trace;
  }

  return rsl::console_colors::Reset;
}

rsl::LogLevel rsl::log_color_to_level(ConsoleColor color)
{
  if(color == rsl::console_colors::Info)
    return LogLevel::Info;
  else if(color == rsl::console_colors::Warning)
    return LogLevel::Warning;
  else if(color == rsl::console_colors::Error)
    return LogLevel::Error;
  else if(color == rsl::console_colors::Assert)
    return LogLevel::Assert;
  else if(color == rsl::console_colors::Todo)
    return LogLevel::Todo;
  else if(color == rsl::console_colors::Debug)
    return LogLevel::Debug;
  else if(color == rsl::console_colors::Trace)
    return LogLevel::Trace;

  return LogLevel::Undefined;
}

rsl::TimeDigits::TimeDigits(card32 value)
{
  high = static_cast<char8>(value * 0.1f);
  low  = static_cast<char8>(value - high * 10);

  high += '0';
  low += '0';
}

rsl::OStream& rsl::operator<<(rsl::OStream& os, rsl::TimeDigits digits)
{
  os << digits.high << digits.low;
  return os;
}

rsl::SmallStackString rsl::time_to_string(const Time& time)
{
  const char8 time_seperator = ':';

  TimeDigits hour(time.hours());
  TimeDigits minutes(time.minutes());
  TimeDigits seconds(time.seconds());

  return {hour.high, hour.low, time_seperator, minutes.high, minutes.low, time_seperator, seconds.high, seconds.low};
}
rsl::SmallStackString rsl::formatted_time_string(const Time& time)
{
  return "[" + time_to_string(time) + "]";
}

rsl::BigStackString rsl::LogMessage::to_string() const
{
  BigStackString res;

  res += m_color.ascii();
  res += formatted_time_string(m_time);
  res += " ";
  res += m_message;

  return res;
}

rsl::BigStackString rsl::LogMessage::message_only() const
{
  return m_message;
}
rsl::ConsoleColor rsl::LogMessage::color() const
{
  return m_color;
}
rsl::LogLevel rsl::LogMessage::log_level() const
{
  return m_log_level;
}
const rsl::Time& rsl::LogMessage::time_point() const
{
  return m_time;
}