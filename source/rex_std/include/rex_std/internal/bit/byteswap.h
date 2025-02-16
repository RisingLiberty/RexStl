#pragma once

#include "rex_std/bonus/defines.h"

namespace rsl
{
	inline namespace v1
	{
		template <typename T>
		RSL_NO_DISCARD constexpr T byteswap(T val)
		{
			if constexpr (sizeof(val) == 1)
			{
				return val;
			}
			else if constexpr (sizeof(val) == 2)
			{
#if RSL_COMPILER_MSVC
				return _byteswap_ushort(val);
#else
				return __builtin_bswap16(val);
#endif
			}
			else if constexpr (sizeof(val) == 4)
			{
#if RSL_COMPILER_MSVC
				return _byteswap_ulong(val);
#else
				return __builtin_bswap32(val);
#endif
			}
			else if constexpr (sizeof(val) == 8)
			{
#if RSL_COMPILER_MSVC
				return _byteswap_uint64(val);
#else
				return __builtin_bswap64(val);
#endif
			}
			else
			{
				static_assert(sizeof(val) == 0, "byteswap is unimplemented for integral types of this size");
			}
		}
	}
}