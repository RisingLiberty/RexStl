// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_call.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/diagnostics/win/win_call.h"

#include "rex_std_extra/rex_stl_extra_pch.h"

#define NOMINMAX
#include <comdef.h>
#include <windows.h>

REX_RSL_BEGIN_NAMESPACE::win
{
  rsl::MediumStackString report_hr_error(HRESULT hr, [[maybe_unused]] const rsl::StringView file, [[maybe_unused]] const rsl::StringView function, [[maybe_unused]] card32 line_nr)
  {
    _com_error err(hr);
    rsl::MediumStackString error_message(err.ErrorMessage());
    REX_ERROR("Windows Error");
    REX_ERROR("File: ", file);
    REX_ERROR("Function: ", function);
    REX_ERROR("On line: ", line_nr);
    REX_ERROR("Windows error: ", error_message);

    return error_message;
  }
}

rsl::win::WinCall::WinCall(const rsl::StringView file, const rsl::StringView function, card32 line_nr)
    : WinCall(ERROR_SUCCESS, file, function, line_nr)
{
}

rsl::win::WinCall::WinCall(DWord error_success, const rsl::StringView file, const rsl::StringView function, card32 line_nr)
    : m_error(GetLastError())
{
  if(m_error != error_success && m_error != ERROR_SUCCESS)
  {
    HRESULT hr      = HRESULT_FROM_WIN32(m_error);
    m_error_message = report_hr_error(hr, file, function, line_nr);
  }

  // GetLastError() is not always cleared when a function succeeds
  // So we just clear it ourselves
  clear_win_errors();
}

bool rsl::win::WinCall::has_failed() const
{
  return m_error != ERROR_SUCCESS;
}
bool rsl::win::WinCall::has_succeeded() const
{
  return !has_failed();
}

rsl::StringView rsl::win::WinCall::error_message() const
{
  return m_error_message.to_view();
}

void rsl::win::check_for_win_errors(const rsl::StringView file, const rsl::StringView function, card32 line_nr)
{
#ifdef REX_SUPRESS_PRE_CHECK_WINDOWS_ERRORS
  clear_win_errors();
#else
  DWord err = GetLastError();
  clear_win_errors();

  if(err != ERROR_SUCCESS)
  {
    REX_WARN("Still Windows errors in pool!");

    HRESULT hr = HRESULT_FROM_WIN32(err);
    report_hr_error(hr, file, function, line_nr);
  }
#endif
}

void rsl::win::clear_win_errors()
{
  SetLastError(ERROR_SUCCESS);
}
