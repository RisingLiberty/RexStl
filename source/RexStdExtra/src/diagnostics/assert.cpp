// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: assert.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/diagnostics/assert.h"

#include "rex_std_extra/diagnostics/win/win_debug.h"
#include "rex_std_extra/diagnostics/win/win_message_box.h"
#include "rex_std_extra/diagnostics/win/win_stack_tracing.h"
#include "rex_std_extra/rex_stl_extra_pch.h"
#include "rex_std_extra/utilities/break.h"

#ifdef REX_ENABLE_ASSERTS
void rsl::internal::internal_assert(const char8* file, const char8* function, card32 line_nr, rsl::StringView message)
{
  rsl::console().log_line(rsl::console_colors::Assert, LOGGER_NAME_OUTPUT, message);
  rsl::console().log_line(rsl::console_colors::Assert, LOGGER_NAME_OUTPUT, "Execution Failed");
  rsl::console().log_line(rsl::console_colors::Assert, LOGGER_NAME_OUTPUT, "file: ", file);
  rsl::console().log_line(rsl::console_colors::Assert, LOGGER_NAME_OUTPUT, "function: ", function);
  rsl::console().log_line(rsl::console_colors::Assert, LOGGER_NAME_OUTPUT, "on line: ", line_nr);
  rsl::console().log_line(rsl::console_colors::Assert, LOGGER_NAME_OUTPUT, "with message: ", message);
  rsl::stack_trace(1).dump("assert_stack_dump.txt");
  rsl::message_box(message, "Assert triggered!");
  if(!rsl::is_debugger_attached())
  {
    rsl::message_box("No debugger attached, the application will now crash", "Crash report");
  }
  REX_BREAK_INF;
}

void rsl::internal::internal_assert(rsl::StringView condition_str, const char8* file, const char8* function, card32 line_nr, rsl::StringView message)
{
  rsl::console().log_line(rsl::console_colors::Assert, LOGGER_NAME_OUTPUT, "condition failed: ", condition_str);
  internal_assert(file, function, line_nr, message);
}
#endif
