// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: basic_string.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/string/basic_string.h"

REX_RSL_BEGIN_NAMESPACE

rsl::optional<int32> stoi(const string& str, char8* str_end, int32 base)
{
  return rsl::strtol(str.data(), &str_end, base);
}
rsl::optional<long> stol(const string& str, char8* str_end, int32 base)
{
  return rsl::strtol(str.data(), &str_end, base);
}
rsl::optional<int64> stoll(const string& str, char8* str_end, int32 base)
{
  return rsl::strtoll(str.data(), &str_end, base);
}
rsl::optional<uint32> stoui(const string& str, char8* str_end, int32 base)
{
  return rsl::strtoul(str.data(), &str_end, base);
}
rsl::optional<ulong> stoul(const string& str, char8* str_end, int32 base)
{
  return rsl::strtoul(str.data(), &str_end, base);
}
rsl::optional<uint64> stoull(const string& str, char8* str_end, int32 base)
{
  return rsl::strtoull(str.data(), &str_end, base);
}
rsl::optional<float32> stof(const string& str, char8* str_end)
{
  return rsl::strtof(str.data(), &str_end);
}
rsl::optional<float64> stod(const string& str, char8* str_end)
{
  return rsl::strtod(str.data(), &str_end);
}
rsl::optional<lfloat64> stold(const string& str, char8* str_end)
{
  return rsl::strtold(str.data(), &str_end);
}


string to_string(int32 value)
{
  return internal::to_string<string>(value);
}
string to_string(long value)
{
  return internal::to_string<string>(value);
}
string to_string(int64 value)
{
  return internal::to_string<string>(value);
}
string to_string(uint32 value)
{
  return internal::to_string<string>(value);
}
string to_string(ulong value)
{
  return internal::to_string<string>(value);
}
string to_string(uint64 value)
{
  return internal::to_string<string>(value);
}
string to_string(float32 value)
{
  return internal::to_string<string>(value);
}
string to_string(float64 value)
{
  return internal::to_string<string>(value);
}
string to_string(lfloat64 value)
{
  return internal::to_string<string>(value);
}

namespace string_literals
{
  // returns a string of the desired type
  string operator""s(const char8 * s, size_t len)
  {
    count_t len_as_count = static_cast<count_t>(len);
    return string(s, len_as_count);
  }
  // returns a string of the desired type
  u16string operator""s(const char16_t* s, size_t len)
  {
    count_t len_as_count = static_cast<count_t>(len);
    return u16string(s, len_as_count);
  }
  // returns a string of the desired type
  u32string operator""s(const char32_t* s, size_t len)
  {
    count_t len_as_count = static_cast<count_t>(len);
    return u32string(s, len_as_count);
  }
  // returns a string of the desired type
  wstring operator""s(const tchar * s, size_t len)
  {
    count_t len_as_count = static_cast<count_t>(len);
    return wstring(s, len_as_count);
  }
}

REX_RSL_END_NAMESPACE