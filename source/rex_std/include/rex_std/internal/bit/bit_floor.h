#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/limits.h"

#include "rex_std/internal/bit/countl_zero.h"

namespace rsl
{
	inline namespace v1
	{
		template <typename T>
		RSL_NO_DISCARD constexpr T bit_floor(const T val)
		{
			if (val == 0)
			{
				return 0;
			}

			return static_cast<T>(T(1) << (rsl::numeric_limits<T>::digits - 1 - rsl::countl_zero(val)));
		}
	}
}