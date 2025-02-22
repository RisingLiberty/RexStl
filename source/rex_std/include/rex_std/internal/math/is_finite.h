#pragma once

#include "rex_std/bonus/types.h"

#include "rex_std/internal/math/is_nan.h"

namespace rsl
{
	inline namespace v1
	{
		constexpr bool is_finite(float num)
		{
			return !is_nan(num) && num - num == 0;
		}
		constexpr bool is_finite(double num)
		{
			return !is_nan(num) && num - num == 0;
		}
	}
}