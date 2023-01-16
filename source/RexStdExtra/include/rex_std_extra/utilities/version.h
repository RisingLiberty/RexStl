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
#include "rex_std/string_view.h"

REX_RSL_BEGIN_NAMESPACE

class Version
{
public:
  Version(card8 major, card8 minor, card32 patch);
  Version(const StringView version);

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

class OStream;
OStream& operator<<(OStream& os, const Version& version);

REX_RSL_END_NAMESPACE