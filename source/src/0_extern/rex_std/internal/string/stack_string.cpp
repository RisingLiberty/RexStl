// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: stack_string.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/bonus/string/stack_string.h"

rsl::Tinystack_string rsl::to_stack_string(const uint32 value)
{
  return internal::to_string<Tinystack_string>(value);
}
rsl::Tinystack_string rsl::to_stack_string(const int32 value)
{
  return internal::to_string<Tinystack_string>(value);
}
rsl::Tinystack_string rsl::to_stack_string(const uint64 value)
{
  return internal::to_string<Tinystack_string>(value);
}
rsl::Tinystack_string rsl::to_stack_string(const int64 value)
{
  return internal::to_string<Tinystack_string>(value);
}
rsl::Tinystack_string rsl::to_stack_string(const float32 value, card32 precision)
{
  return internal::to_string<Tinystack_string>(value, precision);
}
rsl::Tinystack_string rsl::to_stack_string(const float64 value, card32 precision)
{
  return internal::to_string<Tinystack_string>(value, precision);
}
rsl::Tinystack_string rsl::to_stack_string(const void* ptr)
{
    return internal::to_string<Tinystack_string>(ptr);
}

rsl::Tinystack_string operator"" _tiny(const char* str, size_t length)
{
  return rsl::Tinystack_string(str, static_cast<card32>(length + 1));
}
rsl::Smallstack_string operator"" _small(const char* str, size_t length)
{
  return rsl::Smallstack_string(str, static_cast<card32>(length + 1));
}
rsl::Mediumstack_string operator"" _med(const char* str, size_t length)
{
  return rsl::Mediumstack_string(str, static_cast<card32>(length + 1));
}
rsl::Bigstack_string operator"" _big(const char* str, size_t length)
{
  return rsl::Bigstack_string(str, static_cast<card32>(length + 1));
}