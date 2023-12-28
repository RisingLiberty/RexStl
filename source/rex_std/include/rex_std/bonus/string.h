// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: string.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/string/c_string.h"
#include "rex_std/bonus/string/character_lookup.h"
#include "rex_std/bonus/string/stack_string.h"
#include "rex_std/bonus/string/string_fwd.h"
#include "rex_std/bonus/string/string_utils.h"
#include "rex_std/bonus/string/string_utils_impl.h"
#include "rex_std/string.h"
#include "rex_std/string_view.h"
#include "rex_std/vector.h"

namespace rsl
{
  inline namespace v1
  {
    // Splits the string input into different parts using the deliminators
    rsl::vector<rsl::string_view> split(rsl::string_view str, rsl::string_view deliminators);
    // Splits the string input into different parts using the deliminators
    rsl::vector<rsl::wstring_view> split(rsl::wstring_view str, rsl::wstring_view deliminators);
  } // namespace v1
} // namespace rsl