// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: version.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/string/stack_string.h"
#include "rex_std/bonus/types.h"
#include "rex_std/ostream.h"

namespace rsl
{
  inline namespace v1
  {
    class version
    {
    public:
      version(card8 major, card8 minor, card32 patch);
      explicit version(string_view version);

      card8 major() const;
      card8 minor() const;
      card32 patch() const;

      bool operator==(const version& rhs) const;
      bool operator!=(const version& rhs) const;

    private:
      card8 m_major;
      card8 m_minor;
      card32 m_patch;
    };

    rsl::string to_string(const version& version);

    ostream& operator<<(ostream& os, const version& version);

    template <>
    struct formatter<version>
    {
      auto parse(format_parse_context& ctx) const -> decltype(ctx.begin()) // NOLINT(readability-convert-member-functions-to-static)
      {
        return ctx.begin();
      }

      template <typename FormatContext>
      auto format(const version& version, FormatContext& ctx) -> decltype(ctx.out())
      {
        return format_to(ctx.out(), "{}.{}.{}", version.major(), version.minor(), version.patch());
      }
    };

  } // namespace v1
} // namespace rsl