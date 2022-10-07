// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: ios_base.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/ios.h"
#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::IOSBase::IOSBase(IOSBase&& other) noexcept = default;

rsl::IOSBase::~IOSBase() = default;

const rsl::StreamBuff& rsl::IOSBase::stream_buff() const
{
  return m_stream_buf;
}
rsl::StreamBuff& rsl::IOSBase::stream_buff()
{
  return m_stream_buf;
}

rsl::UniqueArray<char8> rsl::IOSBase::release_stream_buff_data()
{
  return m_stream_buf.release_data();
}

void rsl::IOSBase::flush()
{
  sync();
  m_stream_buf.flush();
}
void rsl::IOSBase::sync()
{
  // Nothing to implement
}

card32 rsl::IOSBase::read_cursor_pos() const
{
  return m_stream_buf.read_cursor_pos();
}
card32 rsl::IOSBase::write_cursor_pos() const
{
  return m_stream_buf.write_cursor_pos();
}

const char8* rsl::IOSBase::read_cursor_pos_pointer() const
{
  return m_stream_buf.read_cursor_pos_pointer();
}
char8* rsl::IOSBase::write_cursor_pos_pointer()
{
  return m_stream_buf.write_cursor_pos_pointer();
}

const char8* rsl::IOSBase::stream_data() const
{
  return m_stream_buf.stream_data();
}

card32 rsl::IOSBase::stream_size() const
{
  return m_stream_buf.stream_size();
}

void rsl::IOSBase::set_read_cursor_pos(card32 count)
{
  m_stream_buf.set_read_cursor_pos(count);
}
void rsl::IOSBase::set_write_cursor_pos(card32 count)
{
  m_stream_buf.set_write_cursor_pos(count);
}

void rsl::IOSBase::init(const UniqueArray<char8>& data)
{
  m_stream_buf.init(data);
}
void rsl::IOSBase::init(UniqueArray<char8>&& data)
{
  m_stream_buf.init(std::move(data));
}

card32 rsl::IOSBase::fill_buff_with_chars(char8* dst, card32 offset, const char8* memchr_array, card32 memchr_array_size)
{
  card32 i = offset;
  for(; i < s_MaxIntegerDigits; ++i)
  {
    char8 c = stream_buff().peek();

    if(c == '\0' || c == stream_buff().eof())
    {
      break;
    }

    if(memchr(memchr_array, c, memchr_array_size))
    {
      dst[i++] = stream_buff().getc();
    }
  }

  return i;
}