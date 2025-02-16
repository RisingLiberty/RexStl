#pragma once

#if RSL_COMPILER_MSVC
#include <intrin.h>
#endif

#include "rex_std/type_traits.h"

namespace rsl
{
	inline namespace v1
	{
		enum class endian
		{
#if defined(RSL_COMPILER_MSVC) // Windows machines are always little endian
			little = 0,
			big = 1,
			native = little
#else // Other platforms can be big endian, as they're not supported on MSVC, this is a safe check to do
			little = __ORDER_LITTLE_ENDIAN__,
			big = __ORDER_BIG_ENDIAN__,
			native = __BYTE_ORDER__
#endif
		};

		template <typename To, typename From>
		constexpr To bit_cast(const From& from)
		{
			static_assert(sizeof(To) == sizeof(From), "bit cast cannot be performed on objects with mismatching size");
			static_assert(rsl::is_trivially_copyable_v<From>, "bit cast cannot be performned on an object that's not trivially copyable");
			static_assert(rsl::is_trivially_copyable_v<To>, "bit cast cannot target an object that's not trivially copyable");

			return __builtin_bit_cast(To, from);
		}
	}
}
