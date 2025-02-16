#pragma once

#include "rex_std/bonus/defines.h"

namespace rsl
{
	inline namespace v1
	{
		template <typename T>
		RSL_NO_DISCARD constexpr bool has_single_bit(const T val)
		{
			return val != 0 && (val & (val - 1)) == 0;
		}
	}
}