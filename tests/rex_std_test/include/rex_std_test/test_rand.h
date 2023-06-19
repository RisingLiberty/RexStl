#pragma once

#include "rex_std/bonus/types.h"

namespace rsl::test
{
  // based on EASTL test random number generator

  class rand
  {
  public:
    rand(uint32 nSeed)
      : m_seed(nSeed)
    {}

    uint32 seed() const
    {
      return m_seed;
    }

    void set_seed(uint32 nSeed)
    {
      m_seed = nSeed;
    }

    uint32 rand_value()
    {
      if (m_seed == 0)
      {
        m_seed = 0xfafa;
      }
      const uint64 nResult64 = ((m_seed * (uint64)1103515245) + 12345);
      return (m_seed = (uint32)((nResult64 >> 16) & 0xffffffff));
    }

    uint32 rand_limit(uint32 nLimit)
    {
      return (uint32)((rand_value() * (uint64)nLimit) >> 32);
    }

    int32 rand_range(int32 nBegin, int32 nEnd)
    {
      return nBegin + (int32)rand_limit((uint32)(nEnd - nBegin));
    }

    uint32 operator()()
    {
      return rand_value();
    }

    uint32 operator()(card32 n)
    {
      return rand_limit((uint32)n);
    }

  private:
    uint32 m_seed;
  };
}