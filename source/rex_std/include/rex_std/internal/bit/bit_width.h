#pragma once

#include "rex_std/internal/bit/countl_zero.h"
#include "rex_std/limits.h"

namespace rsl
{
	inline namespace v1
	{
		template <typename T>
		constexpr T bit_width(T value)
		{
			return numeric_limits<T>::digits - countl_zero(value);
		}
	}
}