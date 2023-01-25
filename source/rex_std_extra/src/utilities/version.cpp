// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: version.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/utilities/version.h"

#include "rex_std_extra/utilities/casting.h"

rsl::Version::Version(card8 major, card8 minor, card32 patch)
    : m_major(major)
    , m_minor(minor)
    , m_patch(patch)
{
}
rsl::Version::Version(const string_view version)
    : m_major(0)
    , m_minor(0)
    , m_patch(0)
{
  card32 first_dot_pos  = version.find_first_of('.');
  card32 second_dot_pos = version.find_first_of('.', first_dot_pos + 1);

  m_major = numeric_cast<card8>(rsl::stoi(version.substr(0, first_dot_pos)).value());
  m_minor = numeric_cast<card8>(rsl::stoi(version.substr(first_dot_pos + 1, second_dot_pos - first_dot_pos)).value());
  m_patch = second_dot_pos != string_view::npos() ? numeric_cast<card32>(rsl::stoi(version.substr(second_dot_pos + 1)).value()) : 0;
}

card8 rsl::Version::major() const
{
  return m_major;
}
card8 rsl::Version::minor() const
{
  return m_minor;
}
card32 rsl::Version::patch() const
{
  return m_patch;
}

bool rsl::Version::operator==(const Version& rhs) const
{
  return m_major == rhs.major() && m_minor == rhs.minor() && m_patch == rhs.patch();
}
bool rsl::Version::operator!=(const Version& rhs) const
{
  return !(*this == rhs);
}

rsl::ostream& rsl::operator<<(ostream& os, const Version& version)
{
  // need to convert major and minor to card32, otherwise they'll be formatted as a char
  os << (card32)version.major() << '.' << (card32)version.minor() << '.' << version.patch();
  return os;
}