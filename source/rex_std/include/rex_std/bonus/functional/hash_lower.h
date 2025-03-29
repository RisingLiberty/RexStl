// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: hash_result.h
// Copyright (c) Nick De Breuck 2025
//
// ============================================

#pragma once

#include "rex_std/bonus/functional/hash_result.h"
#include "rex_std/bonus/functional/crc/crc32c.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename StringType>
    struct hash_lower
    {
      constexpr rsl::hash_result operator()(const StringType& str) const
      {
        return rsl::crc32::compute_as_lower(str.data(), str.length());
      }
    };
  } // namespace v1
} // namespace rsl
