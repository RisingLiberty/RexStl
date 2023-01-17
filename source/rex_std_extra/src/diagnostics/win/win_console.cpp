// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_console.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/diagnostics/win/win_console.h"

#include "rex_std_extra/diagnostics/win/win_call.h"
#include "rex_std_extra/rex_stl_extra_pch.h"
#include "rex_std_extra/utilities/enum_reflection.h"

#define NOMINMAX
#include <Windows.h>

rsl::Console& rsl::console()
{
  static Console console;
  return console;
}

rsl::Console::Console()
    : m_output_handle(GetStdHandle(STD_OUTPUT_HANDLE))
{
  // This enables color changes of the console
  enable_virtual_terminal_processing();

  set_color(console_colors::Reset);
}

void rsl::Console::sync()
{
  log(stream_buff().str());
}

void rsl::Console::log_msg(const LogMessage& msg)
{
  DWORD bytes_written    = 0;
  BigStackString log_msg = msg.to_string();
  WIN_CALL(WriteFile(m_output_handle, log_msg.data(), (DWORD)log_msg.length(), &bytes_written, NULL));
}

void rsl::Console::enable_virtual_terminal_processing()
{
  DWORD mode = 0;
  WIN_CALL(GetConsoleMode(m_output_handle, &mode));
  mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  WIN_CALL(SetConsoleMode(m_output_handle, mode));
}

void rsl::Console::set_color(ConsoleColor color)
{
  StringView color_str(color.ascii());
  DWORD bytes_written = 0;
  WIN_CALL(WriteFile(m_output_handle, color_str.data(), color_str.length(), &bytes_written, NULL));
}