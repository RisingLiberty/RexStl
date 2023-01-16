// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: source_location.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

class SourceLocation
{
public:
  constexpr SourceLocation(const StringView file, card32 line)
      : m_file(file)
      , m_line(line)
  {
  }

  constexpr StringView file() const
  {
    return m_file;
  }
  card32 line() const
  {
    return m_line;
  }

  BigStackString to_string() const;

private:
  StringView m_file;
  card32 m_line;
};

REX_RSL_END_NAMESPACE