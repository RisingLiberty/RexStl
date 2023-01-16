// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: hr_call.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

namespace win
{
  using HResult = long;

  class HrCall
  {
  public:
    HrCall(HResult hr, const rsl::StringView file, const rsl::StringView function, card32 line_nr);

    bool has_failed() const;
    bool has_succeeded() const;

    rsl::StringView error_message() const;

  private:
    bool m_has_failed;
    rsl::MediumStackString m_error_message;
  };
} // namespace win

REX_RSL_END_NAMESPACE

#ifdef REX_ENABLE_HR_CALL
  #define HR_CALL(function)    rsl::win::HrCall(function, __FILE__, __FUNCTION__, __LINE__)
  #define HR_SUCCESS(function) rsl::win::HrCall(function, __FILE__, __FUNCTION__, __LINE__).has_succeeded()
  #define HR_FAILED(function)  rsl::win::HrCall(function, __FILE__, __FUNCTION__, __LINE__).has_failed()
#else
  #define HR_CALL(function)    function
  #define HR_SUCCESS(function) function
  #define HR_FAILED(function)  function
#endif