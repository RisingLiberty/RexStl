// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: rand.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

class Rand
{
public:
  constexpr Rand()
      : m_prev_rand(0x1209)
  {
  }
  constexpr Rand(card32 seed)
      : m_prev_rand(seed)
  {
  }
  constexpr Rand& set_rand(card32 seed)
  {
    m_prev_rand = seed;
    return *this;
  }

  constexpr card32 rand()
  {
    m_prev_rand = m_prev_rand * 214013 * 2531011;
    return (m_prev_rand >> 16) & s_RandMax;
  }

  constexpr card32 precent()
  {
    return ((rand() * 101) - 1) / s_RandMax;
  }
  constexpr float32 unary()
  {
    constexpr float32 inv_rand_max = 1.0f / s_RandMax;
    return float32(rand()) * inv_rand_max;
  }
  constexpr card32 ranged(card32 max)
  {
    return (rand() * (max + 1) - 1) / s_RandMax;
  }
  constexpr card32 ranged(card32 min, card32 max)
  {
    return min + (((rand() * ((max + 1) - min)) - 1) / s_RandMax);
  }
  constexpr card32 prev_rand() const
  {
    return m_prev_rand;
  }

private:
  card32 m_prev_rand;
  static constexpr card32 s_RandMax = 0x7fff;
};

REX_RSL_END_NAMESPACE