// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_message_box.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/diagnostics/win/win_message_box.h"

#include "rex_std_extra/filesystem.h"
#include "rex_std_extra/rex_stl_extra_pch.h"

#define NOMINMAX
#include <windows.h>

int32 rsl::message_box(const rsl::StringView msg)
{
  rsl::MediumStackString title;
  GetModuleFileName(NULL, title.data(), static_cast<DWORD>(title.max_size()));
  title.reset_null_termination_offset();
  Path module_filepath(title);
  return message_box(msg, module_filepath.filename().data());
}
int32 rsl::message_box(const rsl::StringView msg, const rsl::StringView title)
{
  // We provide NULL as owner so it won't get in the way when we want to view the game window
  // return value not handled, it should break infinitely or crash when running without debugger
  return MessageBox(NULL, msg.data(), title.data(), MB_OK | MB_ICONERROR);
}

bool rsl::yes_no_message_box(const rsl::StringView msg)
{
  rsl::MediumStackString title;
  GetModuleFileName(NULL, title.data(), static_cast<DWORD>(title.max_size()));
  title.reset_null_termination_offset();
  Path module_filepath(title);
  return yes_no_message_box(msg, module_filepath.filename().data());
}
bool rsl::yes_no_message_box(const rsl::StringView msg, const rsl::StringView title)
{
  // We provide NULL as owner so it won't get in the way when we want to view the game window
  // return value not handled, it should break infinitely or crash when running without debugger
  return MessageBox(NULL, msg.data(), title.data(), MB_YESNO) == IDYES;
}
