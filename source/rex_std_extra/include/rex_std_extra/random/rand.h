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

namespace rsl
{
  inline namespace v1
  {

    class rand
    {
    public:
      constexpr rand()
          : m_prev_rand(0x1209)
      {
      }
      constexpr explicit rand(card32 seed)
          : m_prev_rand(seed)
      {
      }
      constexpr rand& set_rand(card32 seed)
      {
        m_prev_rand = seed;
        return *this;
      }

      constexpr card32 new_rand()
      {
        m_prev_rand = m_prev_rand * 214013 * 2531011;
        return (m_prev_rand >> 16) & s_rand_max; // NOLINT(hicpp-signed-bitwise)
      }

      constexpr card32 precent()
      {
        return ((new_rand() * 101) - 1) / s_rand_max;
      }
      constexpr float32 unary()
      {
        constexpr float32 inv_rand_max = 1.0f / s_rand_max;
        return static_cast<float32>(new_rand()) * inv_rand_max;
      }
      constexpr card32 ranged(card32 max)
      {
        return (new_rand() * (max + 1) - 1) / s_rand_max;
      }
      constexpr card32 ranged(card32 min, card32 max)
      {
        return min + (((new_rand() * ((max + 1) - min)) - 1) / s_rand_max);
      }
      constexpr card32 prev_rand() const
      {
        return m_prev_rand;
      }

    private:
      card32 m_prev_rand;
      static constexpr card32 s_rand_max = 0x7fff;
    };

  } // namespace v1
} // namespace rsl