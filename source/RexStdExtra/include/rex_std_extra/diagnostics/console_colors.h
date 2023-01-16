// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: console_colors.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

// look here for more info:
// https://en.wikipedia.org/wiki/ANSI_escape_code
// https://gist.github.com/vratiu/9780109
// https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html

#include "rex_std/bonus/types.h"

REX_RSL_BEGIN_NAMESPACE

class ConsoleColor
{
public:
  constexpr ConsoleColor()
      : m_ascii("\u001b[0m") // Reset color
  {
  }
  constexpr ConsoleColor(const char8* ascii)
      : m_ascii(ascii)
  {
  }

  constexpr bool operator==(const ConsoleColor& rhs) const
  {
    return m_ascii == rhs.m_ascii;
  }
  constexpr bool operator!=(const ConsoleColor& rhs) const
  {
    return !(*this == rhs);
  }

  constexpr const char8* ascii() const
  {
    return m_ascii;
  }

private:
  const char8* m_ascii;
};

namespace console_colors
{
  constexpr ConsoleColor Reset = "\u001b[0m";

  constexpr ConsoleColor Black       = "\u001b[30m";
  constexpr ConsoleColor Red         = "\u001b[31m";
  constexpr ConsoleColor Green       = "\u001b[32m";
  constexpr ConsoleColor Yellow      = "\u001b[33m";
  constexpr ConsoleColor Blue        = "\u001b[34m";
  constexpr ConsoleColor Purple      = "\u001b[35m";
  constexpr ConsoleColor Cyan        = "\u001b[36m";
  constexpr ConsoleColor White       = "\u001b[37m";
  constexpr ConsoleColor Grey        = Reset;
  constexpr ConsoleColor LightBlack  = "\u001b[90m";
  constexpr ConsoleColor LightRed    = "\u001b[91m";
  constexpr ConsoleColor LightGreen  = "\u001b[92m";
  constexpr ConsoleColor LightYellow = "\u001b[93m";
  constexpr ConsoleColor LightBlue   = "\u001b[94m";
  constexpr ConsoleColor LightPurple = "\u001b[95m";
  constexpr ConsoleColor LightCyan   = "\u001b[96m";
  constexpr ConsoleColor LightWhite  = "\u001b[97m";

  constexpr ConsoleColor Info    = Green;
  constexpr ConsoleColor Warning = Yellow;
  constexpr ConsoleColor Error   = Red;
  constexpr ConsoleColor Assert  = Purple;
  constexpr ConsoleColor Todo    = LightCyan;
  constexpr ConsoleColor Debug   = Yellow;
  constexpr ConsoleColor Trace   = LightWhite;
} // namespace console_colors

REX_RSL_END_NAMESPACE