// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: iostream.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

//-----------------------------------------------------------------------------
// https://en.cppreference.com/w/cpp/header/iostream
//
//
//-----------------------------------------------------------------------------

#include "rex_std/iostream.h"

#include "rex_std/bonus/iostream/console_buf.h"
#include "rex_std/internal/type_traits/is_same.h"

#include <Windows.h>

REX_RSL_BEGIN_NAMESPACE

rsl::streambuf* cin_streambuf()
{
  HANDLE input_handle = GetStdHandle(STD_INPUT_HANDLE);

  static console_buf<char8> buff(input_handle);
  return &buff;
}
rsl::streambuf* cout_streambuf()
{
  HANDLE output_handle = GetStdHandle(STD_OUTPUT_HANDLE);

  static console_buf<char8> buff(output_handle);
  return &buff;
}
rsl::streambuf* cerr_streambuf()
{
  HANDLE error_handle = GetStdHandle(STD_ERROR_HANDLE);

  static console_buf<char8> buff(error_handle);
  return &buff;
}

rsl::istream cin(cin_streambuf());
rsl::ostream cout(cout_streambuf());
rsl::ostream cerr(cerr_streambuf());
rsl::ostream clog(cerr_streambuf());

namespace internal
{
  class InitCout
  {
  public:
    InitCout()
    {
      cin.tie(&cout);
      cerr.tie(&cout);
    }
    ~InitCout()
    {
      clog.flush();
      cout.flush();
      cerr.flush();
    }
  };

  InitCout init_cout;
} // namespace internal

REX_RSL_END_NAMESPACE