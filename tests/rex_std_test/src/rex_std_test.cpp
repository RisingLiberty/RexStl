#include "rex_std_test/rex_std_test.h"

namespace rsl
{
  namespace test
  {
    uint32 g_rand_seed;

    uint32 rand_seed()
    {
      return g_rand_seed;
    }
    void set_rand_seed(uint32 seed)
    {
      g_rand_seed = seed;
    }
  }
}