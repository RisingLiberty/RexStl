// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: no_literal.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename T>
class NoLiteral
{
public:
  NoLiteral(T value)
      : m_value(value)
  {
  }

  NoLiteral(const T&& literal) = delete;

  operator T&()
  {
    return m_value;
  }
  operator const T&() const
  {
    return m_value;
  }

private:
  T m_value;
};

REX_RSL_END_NAMESPACE