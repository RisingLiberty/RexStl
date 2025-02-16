#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/bonus/types.h"

#include "rex_std/limits.h"

#if RSL_COMPILER_MSVC
#include <intrin.h>
#endif

namespace rsl
{
	inline namespace v1
	{
		namespace internal
		{
			template <typename T>
			int32 crz32(T val)
			{
#ifdef RSL_COMPILER_MSVC
				return _tzcnt_u32(val);
#else
				return __builtin_ctz(val);
#endif
			}
			template <typename T>
			int32 crz64(T val)
			{
#ifdef RSL_COMPILER_MSVC
				return static_cast<int32>(_tzcnt_u64(val));
#else
				return __builtin_ctzll(val);
#endif
			}
		}

		template <typename T>
		RSL_NO_DISCARD constexpr int32 countr_zero(const T val)
		{
			if (val == 0)
			{
				return numeric_limits<T>::digits;
			}

			if constexpr (sizeof(T) <= sizeof(uint32))
			{
				return internal::crz32(static_cast<uint32>(val));
			}
			else if constexpr (sizeof(T) <= sizeof(uint64))
			{
				return internal::crz64(static_cast<uint64>(val));
			}
			else
			{
				int32 ret = 0;
				const uint32 ui64digits = rsl::numeric_limits<uint64>::digits;
				while (static_cast<uint64>(val) == 0)
				{
					ret += ui64digits;
					val >>= ui64digits;
				}
				return ret + internal::crz64<uint64>(val);
			}
		}
	}
}