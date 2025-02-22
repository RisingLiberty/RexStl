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

#include "rex_std/bonus/utility/version.h"

#include "rex_std/bonus/utility/casting.h"

rsl::version::version(card8 major, card8 minor, card32 patch)
    : m_major(major)
    , m_minor(minor)
    , m_patch(patch)
{
}
rsl::version::version(const string_view version)
    : m_major(0)
    , m_minor(0)
    , m_patch(0)
{
  const card32 first_dot_pos  = version.find_first_of('.');
  const card32 second_dot_pos = version.find_first_of('.', first_dot_pos + 1);

  const card32 minor_length = second_dot_pos - first_dot_pos - 1;

  m_major = numeric_cast<card8>(rsl::stoi(version.substr(0, first_dot_pos)).value());
  m_minor = numeric_cast<card8>(rsl::stoi(version.substr(first_dot_pos + 1, minor_length)).value());
  m_patch = second_dot_pos != string_view::npos() ? numeric_cast<card32>(rsl::stoi(version.substr(second_dot_pos + 1)).value()) : 0;
}

card8 rsl::version::major() const
{
  return m_major;
}
card8 rsl::version::minor() const
{
  return m_minor;
}
card32 rsl::version::patch() const
{
  return m_patch;
}

bool rsl::version::operator==(const version& rhs) const
{
  return m_major == rhs.major() && m_minor == rhs.minor() && m_patch == rhs.patch();
}
bool rsl::version::operator!=(const version& rhs) const
{
  return !(*this == rhs);
}

rsl::string rsl::to_string(const rsl::version& version)
{
  rsl::string version_str;

  version_str += rsl::to_string(version.major());
  version_str += ".";
  version_str += rsl::to_string(version.minor());
  version_str += ".";
  version_str += rsl::to_string(version.patch());

  return version_str;
}

rsl::ostream& rsl::operator<<(ostream& os, const version& version)
{
  // need to convert major and minor to card32, otherwise they'll be formatted as a char
  os << static_cast<card32>(version.major()) << '.' << static_cast<card32>(version.minor()) << '.' << version.patch();
  return os;
}