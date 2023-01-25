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

#include "rex_std/bonus/types.h"
#include "rex_std/iostream.h"
#include "rex_std/string_view.h"

namespace rsl
{
  inline namespace v1
  {

    class Version
    {
    public:
      Version(card8 major, card8 minor, card32 patch);
      Version(const string_view version);

      card8 major() const;
      card8 minor() const;
      card32 patch() const;

      bool operator==(const Version& rhs) const;
      bool operator!=(const Version& rhs) const;

    private:
      card8 m_major;
      card8 m_minor;
      card32 m_patch;
    };

    ostream& operator<<(ostream& os, const Version& version);

  } // namespace v1
} // namespace rsl