// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: stream_buffer.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/io/stream_buffer.h"

#include "rex_std_extra/rex_stl_extra_pch.h"
#include "rex_std_extra/string/string.h"

rsl::StreamBuff::StreamBuff()
    : m_stream_buff()
    , m_read_cursor_pos(0)
    , m_write_cursor_pos(0)
{
}

void rsl::StreamBuff::init(const rsl::UniqueArray<char8>& data)
{
  m_read_cursor_pos  = 0;
  m_write_cursor_pos = data.count();

  m_stream_buff = rsl::make_unique<char8[]>(data.count());
  rsl::memcpy(m_stream_buff.get(), data.get(), data.count());
}

void rsl::StreamBuff::init(rsl::UniqueArray<char8>&& data)
{
  m_stream_buff      = std::move(data);
  m_read_cursor_pos  = 0;
  m_write_cursor_pos = m_stream_buff.count();
}

void rsl::StreamBuff::putc(char8 c)
{
  if(!can_put())
  {
    alloc_bigger_buf(1);
  }

  putc_impl(c);
  ++m_write_cursor_pos;
}

void rsl::StreamBuff::putn(const char8* c, card32 length)
{
  if(!can_put(length))
  {
    alloc_bigger_buf(length);
  }

  putn_impl(c, length);
  m_write_cursor_pos += length;
}

char8 rsl::StreamBuff::peek() const
{
  return can_peek() ? m_stream_buff[read_cursor_pos()] : eof();
}

char8 rsl::StreamBuff::getc()
{
  if(!can_get())
  {
    return eof();
  }
  return getc_impl();
}

card32 rsl::StreamBuff::getn(char8* out_buf, card32 length)
{
  card32 chars_read = length > 0 && can_get(length) ? getn_impl(out_buf, length) : 0;

  m_read_cursor_pos += chars_read;
  return chars_read;
}

void rsl::StreamBuff::flush()
{
  m_read_cursor_pos  = 0;
  m_write_cursor_pos = 0;
}

card32 rsl::StreamBuff::read_cursor_pos() const
{
  return m_read_cursor_pos;
}

const char8* rsl::StreamBuff::read_cursor_pos_pointer() const
{
  return m_stream_buff.get() ? &m_stream_buff[read_cursor_pos()] : nullptr;
}

card32 rsl::StreamBuff::write_cursor_pos() const
{
  return m_write_cursor_pos;
}

char8* rsl::StreamBuff::write_cursor_pos_pointer()
{
  return m_stream_buff.get() ? &m_stream_buff[write_cursor_pos()] : nullptr;
}

void rsl::StreamBuff::set_read_cursor_pos(card32 count)
{
  m_read_cursor_pos = count;
}
void rsl::StreamBuff::set_write_cursor_pos(card32 count)
{
  m_write_cursor_pos = count;
}

const char8* rsl::StreamBuff::stream_data() const
{
  return m_stream_buff.get();
}
card32 rsl::StreamBuff::stream_size() const
{
  return m_stream_buff.count();
}

rsl::String rsl::StreamBuff::str() const
{
  String tmp(stream_data(), write_cursor_pos());
  return tmp;
}

rsl::UniqueArray<char8> rsl::StreamBuff::release_data()
{
  rsl::UniqueArray<char8> data = std::move(m_stream_buff);
  m_read_cursor_pos            = 0;
  m_write_cursor_pos           = 0;
  return data;
}

bool rsl::StreamBuff::can_put(card32 length) const
{
  return write_cursor_pos() + (length - 1) < m_stream_buff.count();
}
bool rsl::StreamBuff::can_get(card32 length) const
{
  return read_cursor_pos() + (length - 1) < write_cursor_pos();
}

bool rsl::StreamBuff::can_peek() const
{
  return read_cursor_pos() < write_cursor_pos();
}

void rsl::StreamBuff::alloc_bigger_buf(card32 min_size)
{
  card32 new_size             = (m_stream_buff.count() + min_size) * 2;
  rsl::UniqueArray<char8> tmp = rsl::make_unique<char8[]>(new_size);
  rsl::memcpy(tmp.get(), m_stream_buff.get(), m_stream_buff.count());
  m_stream_buff = std::move(tmp);
}

void rsl::StreamBuff::putc_impl(char8 c)
{
  rsl::memcpy(m_stream_buff.get() + write_cursor_pos(), &c, sizeof(c));
}
void rsl::StreamBuff::putn_impl(const char8* c, card32 length)
{
  rsl::memcpy(m_stream_buff.get() + write_cursor_pos(), c, length);
}

char8 rsl::StreamBuff::getc_impl()
{
  return m_stream_buff[read_cursor_pos()];
}

card32 rsl::StreamBuff::getn_impl(char8* out_buf, card32 length)
{
  rsl::memcpy(out_buf, &m_stream_buff[read_cursor_pos()], length);
  return length;
}