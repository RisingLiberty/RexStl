// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: key.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/string_view.h"
#include "rex_std_extra/io/key_codes.h"

#include <utility>

REX_RSL_BEGIN_NAMESPACE

class Key
{
public:
  constexpr Key(KeyCode code, StringView name)
      : m_code(code)
      , m_name(name)
  {
  }

  KeyCode code() const
  {
    return m_code;
  }
  StringView name() const
  {
    return m_name;
  }

private:
  KeyCode m_code;
  StringView m_name;
};

class CharKey
{
public:
  constexpr CharKey(KeyCode code, StringView name, int8 ascii)
      : m_code(code)
      , m_name(name)
      , m_ascii(ascii)
  {
  }

  constexpr KeyCode code() const
  {
    return m_code;
  }
  constexpr StringView name() const
  {
    return m_name;
  }
  constexpr int8 ascii() const
  {
    return m_ascii;
  }

private:
  KeyCode m_code;
  StringView m_name;
  int8 m_ascii;
};
}

namespace std
{
  template <>
  struct hash<rsl::Key>
  {
    size_t operator()(const rsl::Key& key) const
    {
      return static_cast<card32>(key.code());
    }
  };

  REX_RSL_END_NAMESPACE