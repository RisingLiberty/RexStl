// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: source_location.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/utilities/source_location.h"

#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::BigStackString rsl::SourceLocation::to_string() const
{
  // Result in format of
  // File: Line

  BigStackString result;
  result += file();
  result += ": ";
  result += to_stack_string(line());
  return result;
}