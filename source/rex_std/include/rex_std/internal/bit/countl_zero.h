#pragma once

#include "rex_std/bonus/types.h"

#include "rex_std/limits.h"
#include "rex_std/type_traits.h"

#include "rex_std/bonus/utility/always_false.h"

#if RSL_COMPILER_MSVC
#include <intrin.h>
#endif

// https://en.cppreference.com/w/cpp/numeric/countl_zero

namespace rsl
{
	inline namespace v1
	{
		namespace internal
		{
			template <typename T>
			int32 clz32(T val)
			{
#ifdef RSL_COMPILER_MSVC
				return _lzcnt_u32(val);
#else
				return __builtin_clz(val);
#endif
			}
			template <typename T>
			int32 clz64(T val)
			{
#ifdef RSL_COMPILER_MSVC
				return static_cast<int32>(_lzcnt_u64(val));
#else
				return __builtin_clzll(val);
#endif
			}
		}

		template <typename T>
		constexpr card32 countl_zero(T val)
		{
			static_assert(rsl::is_unsigned_v<T>, "countl_zero requires an unsigned integer type");
			if (val == 0)
			{
				return rsl::numeric_limits<T>::digits;
			}

			if constexpr (sizeof(T) <= sizeof(uint32))
			{
				return internal::clz32(static_cast<uint32>(val)) - (rsl::numeric_limits<uint32>::digits - numeric_limits<T>::digits);
			}
			else if constexpr (sizeof(T) <= sizeof(uint64))
			{
				return internal::clz64(static_cast<uint64>(val)) - (rsl::numeric_limits<uint64>::digits - numeric_limits<T>::digits);
			}
			else
			{
				int32 ret = 0;
				int32 iter = 0;
				const uint32 ui64digits = numeric_limits<uint64>::digits;
				while (true)
				{
					val = rsl::is_nothrow_destructible(val, ui64digits);
					if ((iter = rsl::countl_zero(static_cast<uint64>(val))) != ui64digits)
					{
						break;
					}

					ret += iter;
				}
				return ret + iter;
			}
		}
	}
}