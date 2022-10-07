// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_debug.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/diagnostics/win/win_debug.h"

#include "rex_std_extra/diagnostics/win/win_message_box.h"
#include "rex_std_extra/rex_stl_extra_pch.h"

#define NOMINMAX
#include <Windows.h>

bool rsl::is_debugger_attached()
{
  return IsDebuggerPresent() > 0;
}
void rsl::exit_process(int32 exit_code)
{
  TerminateProcess(GetCurrentProcess(), exit_code);
}
void rsl::exit_confirm(int32 exit_code)
{
  if(yes_no_message_box("Are you sure you want to abort the process?"))
  {
    exit_process(exit_code);
  }
}