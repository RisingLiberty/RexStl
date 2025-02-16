#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/bonus/types.h"

#include "rex_std/limits.h"

namespace rsl
{
	inline namespace v1
	{
		template <typename T>
		RSL_NO_DISCARD constexpr T rotr(const T val, int32 rotation);

		template <typename T>
		RSL_NO_DISCARD constexpr T rotl(const T val, int32 rotation)
		{
			constexpr auto digits = rsl::numeric_limits<T>::digits;
			const auto remainder = rotation % digits;
			if (remainder > 0)
			{
				return static_cast<T>(static_cast<T>(val << remainder) | static_cast<T>(val >> (digits - remainder)));
			}
			else if (remainder == 0)
			{
				return val;
			}
			else
			{
				return rsl::rotr(val, -remainder);
			}
		}
	}
}