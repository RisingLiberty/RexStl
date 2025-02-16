#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/bonus/types.h"

#include "rex_std/internal/bit/countr_zero.h"
#include "rex_std/limits.h"

namespace rsl
{
	inline namespace v1
	{
		template <typename T>
		RSL_NO_DISCARD constexpr int32 countr_one(T val)
		{
			return val != rsl::numeric_limits<T>::max() ? rsl::countr_zero(static_cast<T>(~val)) : rsl::numeric_limits<T>::digits;
		}
	}
}