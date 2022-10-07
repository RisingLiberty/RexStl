// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_console.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/ostream.h"
#include "rex_std/sstream.h"
#include "rex_std_extra/diagnostics/console_colors.h"
#include "rex_std_extra/diagnostics/log_message.h"

#include <mutex>

REX_RSL_BEGIN_NAMESPACE

namespace win
{
  using FileHandle = void*;
}

class OFile;

class Console : public OStream
{
public:
  Console();

  void sync() final;

  template <typename... Args>
  void log(Args&&... args)
  {
    LogMessage msg(console_colors::White, LogLevel::Undefined, rsl::forward<Args>(args)...);
    log_msg(msg);
  }
  template <typename... Args>
  void log_line(Args&&... args)
  {
    LogMessage msg(console_colors::White, LogLevel::Undefined, rsl::forward<Args>(args)..., '\n');
    log_msg(msg);
  }
  template <typename... Args>
  void log(ConsoleColor color, Args&&... args)
  {
    LogLevel level = log_color_to_level(color);
    LogMessage msg(color, level, rsl::forward<Args>(args)...);
    log_msg(msg);
  }
  template <typename... Args>
  void log_line(ConsoleColor color, Args&&... args)
  {
    LogLevel level = log_color_to_level(color);
    LogMessage msg(color, level, rsl::forward<Args>(args)..., '\n');
    log_msg(msg);
  }

private:
  void log_msg(const LogMessage& msg);

  void save_logs_to_file(OFile& file);
  void enable_virtual_terminal_processing();

  void set_color(ConsoleColor color);

private:
  win::FileHandle m_output_handle;
};

Console& console();

REX_RSL_END_NAMESPACE