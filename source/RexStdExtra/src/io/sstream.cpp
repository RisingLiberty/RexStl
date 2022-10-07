// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: sstream.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/io/sstream.h"

#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::String rsl::StringStream::str() const
{
  return stream_buff().str();
}

void rsl::StringStream::str(const StringView str)
{
  clear();
  *this << str;
}

void rsl::StringStream::clear()
{
  stream_buff().set_read_cursor_pos(0);
  stream_buff().set_write_cursor_pos(0);
}

void rsl::StringStream::flush()
{
  // Nothing to implement
}

rsl::StringStream& rsl::stream_for_messages()
{
  static thread_local StringStream ss;
  ss.clear();
  return ss;
}