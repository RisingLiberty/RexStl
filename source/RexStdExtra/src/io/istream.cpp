// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: istream.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/io/istream.h"

#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::IStream::IStream(IStream&& other) noexcept = default;

rsl::IStream::~IStream() = default;

rsl::IStream& rsl::IStream::operator>>(char8& value)
{
  value = stream_buff().getc();
  return *this;
}
rsl::IStream& rsl::IStream::operator>>(tchar& value)
{
  value = IOSBase::read_next_int<tchar>();
  return *this;
}

rsl::IStream& rsl::IStream::operator>>(int8& value)
{
  value = stream_buff().getc();
  return *this;
}
rsl::IStream& rsl::IStream::operator>>(int16& value)
{
  value = IOSBase::read_next_int<int16>();
  return *this;
}
rsl::IStream& rsl::IStream::operator>>(int32& value)
{
  value = IOSBase::read_next_int<int32>();
  return *this;
}
rsl::IStream& rsl::IStream::operator>>(int64& value)
{
  value = IOSBase::read_next_int<int64>();
  return *this;
}

rsl::IStream& rsl::IStream::operator>>(uint8& value)
{
  value = stream_buff().getc();
  return *this;
}
rsl::IStream& rsl::IStream::operator>>(uint16& value)
{
  value = IOSBase::read_next_int<uint16>();
  return *this;
}
rsl::IStream& rsl::IStream::operator>>(uint32& value)
{
  value = IOSBase::read_next_int<uint32>();
  return *this;
}
rsl::IStream& rsl::IStream::operator>>(uint64& value)
{
  value = IOSBase::read_next_int<uint64>();
  return *this;
}

rsl::IStream& rsl::IStream::operator>>(float32& value)
{
  value = IOSBase::read_next_float<float32>();
  return *this;
}
rsl::IStream& rsl::IStream::operator>>(float64& value)
{
  value = IOSBase::read_next_float<float64>();
  return *this;
}
