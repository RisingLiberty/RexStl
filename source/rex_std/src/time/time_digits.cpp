// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: time_digits.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/bonus/time/time_digits.h"

namespace rsl
{
  inline namespace v1
  {
    rsl::ostream& operator<<(rsl::ostream& os, time_digits digits)
    {
      os << digits.to_string();
      return os;
    }
  } // namespace v1
} // namespace rsl