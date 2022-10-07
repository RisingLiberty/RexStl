// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: ostream.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/ostream.h"

#include "rex_std/bonus/string/stack_string.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T>
void convert(T value, OStream& os)
{
  TinyStackString str = rsl::to_stack_string(value);
  os.stream_buff().putn(str.data(), str.length());
  os.flush();
}

REX_RSL_END_NAMESPACE

rsl::OStream::OStream(OStream&& other) noexcept = default;

rsl::OStream::~OStream() = default;

rsl::OStream& rsl::OStream::operator<<(char8 value)
{
  stream_buff().putc(value);
  flush();
  return *this;
}
rsl::OStream& rsl::OStream::operator<<(tchar value)
{
  convert(value, *this);
  return *this;
}

rsl::OStream& rsl::OStream::operator<<(uint8 value)
{
  stream_buff().putc(value);
  flush();
  return *this;
}
rsl::OStream& rsl::OStream::operator<<(uint16 value)
{
  convert(value, *this);
  return *this;
}
rsl::OStream& rsl::OStream::operator<<(uint32 value)
{
  convert(value, *this);
  return *this;
}
rsl::OStream& rsl::OStream::operator<<(uint64 value)
{
  convert(value, *this);
  return *this;
}

rsl::OStream& rsl::OStream::operator<<(int8 value)
{
  stream_buff().putc(value);
  flush();
  return *this;
}
rsl::OStream& rsl::OStream::operator<<(int16 value)
{
  convert(value, *this);
  return *this;
}
rsl::OStream& rsl::OStream::operator<<(int32 value)
{
  convert(value, *this);
  return *this;
}
rsl::OStream& rsl::OStream::operator<<(int64 value)
{
  convert(value, *this);
  return *this;
}

rsl::OStream& rsl::OStream::operator<<(float32 value)
{
  convert(value, *this);
  return *this;
}
rsl::OStream& rsl::OStream::operator<<(float64 value)
{
  convert(value, *this);
  return *this;
}

rsl::OStream& rsl::OStream::operator<<(const char8* str)
{
  card32 length = string_length(str);
  stream_buff().putn(str, length);
  flush();
  return *this;
}
rsl::OStream& rsl::OStream::operator<<(const void* address)
{
  char buf[21];
  sprintf_s(buf, "%p", address);
  StringView temp(buf);
  stream_buff().putn(temp.data(), temp.length());
  flush();
  return *this;
}
