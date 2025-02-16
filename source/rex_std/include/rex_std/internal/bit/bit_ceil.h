#pragma once

#include "rex_std/bonus/defines.h"

#include "rex_std/type_traits.h"
#include "rex_std/limits.h"

#include "rex_std/internal/bit/countl_zero.h"

namespace rsl
{
	inline namespace v1
	{
    template <typename T>
    RSL_NO_DISCARD constexpr T bit_ceil(const T val)
    {
      static_assert(rsl::is_unsigned_v<T>, "bit_ceil can only be called with a unsigned type");

      if(val == 0)
      {
        return 1;
      }

      return static_cast<T>(T(1) << (rsl::numeric_limits<T>::digits - rsl::countl_zero(static_cast<T>(val - 1))));
    }
	}
}