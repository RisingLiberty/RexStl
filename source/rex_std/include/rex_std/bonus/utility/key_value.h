// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: key_value.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/utility/forward.h"
#include "rex_std/internal/utility/move.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename Key, typename Value>
    struct key_value
    {
    public:
      using key_type   = Key;
      using value_type = Value;

      // useful type alias for pair utility
      using first_type  = key_type;
      using second_type = value_type;

      key_value() = default;
      template <typename... Args>
      explicit key_value(const Key& k, Args&&... args)
          : key(k)
          , value(rsl::forward<Args>(args)...)
      {
      }
      template <typename... Args>
      explicit key_value(Key&& k, Args&&... args)
          : key(rsl::move(k))
          , value(rsl::forward<Args>(args)...)
      {
      }

      const Key& first() const
      {
        return key;
      }
      Key& first()
      {
        return key;
      }

      const Value& second() const
      {
        return value;
      }
      Value& second()
      {
        return value;
      }

    public:
      Key key; // NOLINT(readability-identifier-naming, cppcoreguidelines-avoid-const-or-ref-data-members)
      Value value;
    };

  } // namespace v1
} // namespace rsl
