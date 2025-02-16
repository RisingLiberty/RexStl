#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/bonus/types.h"

namespace rsl
{
	inline namespace v1
	{
		namespace internal
		{
			template <typename T>
			int32 popcount32(T val)
			{
#ifdef RSL_COMPILER_MSVC
				return __popcnt(val);
#else
				return __builtin_popcount(val);
#endif
			}
			template <typename T>
			int32 popcount64(T val)
			{
#ifdef RSL_COMPILER_MSVC
				return static_cast<int32>(__popcnt64(val));
#else
				return __builtin_popcountll(val);
#endif
			}
		}

		template <typename T>
		RSL_NO_DISCARD constexpr int32 popcount(T val)
		{
			if constexpr (sizeof(val) <= sizeof(uint32))
			{
				return internal::popcount32(static_cast<uint32>(val));
			}
			else if constexpr (sizeof(val) <= sizeof(uint64))
			{
				return internal::popcount64(static_cast<uint64>(val));
			}
			else
			{
				int32 ret = 0;
				while (val != 0)
				{
					ret += internal::popcount64(static_cast<uint64>(val));
					val >>= rsl::numeric_limits<uint64>::digits;
				}
				return ret;
			}
		}
	}
}