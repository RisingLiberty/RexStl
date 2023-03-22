


#ifndef REX_ATOMIC_INTERNAL_ARCH_ARM_STORE_H
#define REX_ATOMIC_INTERNAL_ARCH_ARM_STORE_H

#pragma once


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_STORE_*_N(type, type * ptr, type val)
//
#if defined(REX_COMPILER_MSVC)


	#define REX_ARCH_ATOMIC_ARM_STORE_N(integralType, bits, type, ptr, val) \
		MERGE(__iso_volatile_store, bits)(REX_ATOMIC_VOLATILE_INTEGRAL_CAST(integralType, (ptr)), REX_ATOMIC_TYPE_PUN_CAST(integralType, (val)))


	#define REX_ARCH_ATOMIC_ARM_STORE_8(type, ptr, val)			\
		REX_ARCH_ATOMIC_ARM_STORE_N(__int8, 8, type, ptr, val)

	#define REX_ARCH_ATOMIC_ARM_STORE_16(type, ptr, val)			\
		REX_ARCH_ATOMIC_ARM_STORE_N(__int16, 16, type, ptr, val)

	#define REX_ARCH_ATOMIC_ARM_STORE_32(type, ptr, val)			\
		REX_ARCH_ATOMIC_ARM_STORE_N(__int32, 32, type, ptr, val)


	#if defined(REX_PLATFORM_ARM64)

		#define REX_ARCH_ATOMIC_ARM_STORE_64(type, ptr, val)			\
			REX_ARCH_ATOMIC_ARM_STORE_N(__int64, 64, type, ptr, val)

	#endif


	#define REX_ARCH_ATOMIC_ARM_STORE_128(type, ptr, val, MemoryOrder)	\
		{																	\
			type exchange128; (void)(exchange128);						\
			MERGE(MERGE(REX_ATOMIC_EXCHANGE_, MemoryOrder), _128)(type, exchange128, ptr, val); \
		}


	#define REX_ARCH_ATOMIC_STORE_RELAXED_8(type, ptr, val)	\
		REX_ARCH_ATOMIC_ARM_STORE_8(type, ptr, val)

	#define REX_ARCH_ATOMIC_STORE_RELAXED_16(type, ptr, val)	\
		REX_ARCH_ATOMIC_ARM_STORE_16(type, ptr, val)

	#define REX_ARCH_ATOMIC_STORE_RELAXED_32(type, ptr, val)	\
		REX_ARCH_ATOMIC_ARM_STORE_32(type, ptr, val)

	#define REX_ARCH_ATOMIC_STORE_RELAXED_128(type, ptr, val)		\
		REX_ARCH_ATOMIC_ARM_STORE_128(type, ptr, val, RELAXED)


	#define REX_ARCH_ATOMIC_STORE_RELEASE_8(type, ptr, val)	\
		REX_ATOMIC_CPU_MB();									\
		REX_ARCH_ATOMIC_ARM_STORE_8(type, ptr, val)

	#define REX_ARCH_ATOMIC_STORE_RELEASE_16(type, ptr, val)	\
		REX_ATOMIC_CPU_MB();									\
		REX_ARCH_ATOMIC_ARM_STORE_16(type, ptr, val)

	#define REX_ARCH_ATOMIC_STORE_RELEASE_32(type, ptr, val)	\
		REX_ATOMIC_CPU_MB();									\
		REX_ARCH_ATOMIC_ARM_STORE_32(type, ptr, val)

	#define REX_ARCH_ATOMIC_STORE_RELEASE_128(type, ptr, val)		\
		REX_ARCH_ATOMIC_ARM_STORE_128(type, ptr, val, RELEASE)


	#define REX_ARCH_ATOMIC_STORE_SEQ_CST_8(type, ptr, val)	\
		REX_ATOMIC_CPU_MB();									\
		REX_ARCH_ATOMIC_ARM_STORE_8(type, ptr, val) ;			\
		REX_ATOMIC_CPU_MB()

	#define REX_ARCH_ATOMIC_STORE_SEQ_CST_16(type, ptr, val)	\
		REX_ATOMIC_CPU_MB();									\
		REX_ARCH_ATOMIC_ARM_STORE_16(type, ptr, val);			\
		REX_ATOMIC_CPU_MB()

	#define REX_ARCH_ATOMIC_STORE_SEQ_CST_32(type, ptr, val)	\
		REX_ATOMIC_CPU_MB();									\
		REX_ARCH_ATOMIC_ARM_STORE_32(type, ptr, val);			\
		REX_ATOMIC_CPU_MB()

	#define REX_ARCH_ATOMIC_STORE_SEQ_CST_128(type, ptr, val)		\
		REX_ARCH_ATOMIC_ARM_STORE_128(type, ptr, val, SEQ_CST)


	#if defined(REX_PLATFORM_ARM32)


		#define REX_ARCH_ATOMIC_STORE_RELAXED_64(type, ptr, val)			\
			{																\
				type retExchange64; (void)(retExchange64);				\
				REX_ATOMIC_EXCHANGE_RELAXED_64(type, retExchange64, ptr, val); \
			}

		#define REX_ARCH_ATOMIC_STORE_RELEASE_64(type, ptr, val)			\
			{																\
				type retExchange64; (void)(retExchange64);				\
				REX_ATOMIC_EXCHANGE_RELEASE_64(type, retExchange64, ptr, val); \
			}

		#define REX_ARCH_ATOMIC_STORE_SEQ_CST_64(type, ptr, val)			\
			{																\
				type retExchange64; (void)(retExchange64);				\
				REX_ATOMIC_EXCHANGE_SEQ_CST_64(type, retExchange64, ptr, val); \
			}


	#elif defined(REX_PLATFORM_ARM64)


		#define REX_ARCH_ATOMIC_STORE_RELAXED_64(type, ptr, val)	\
			REX_ARCH_ATOMIC_ARM_STORE_64(type, ptr, val)

		#define REX_ARCH_ATOMIC_STORE_RELEASE_64(type, ptr, val)	\
			REX_ATOMIC_CPU_MB();									\
			REX_ARCH_ATOMIC_ARM_STORE_64(type, ptr, val)

		#define REX_ARCH_ATOMIC_STORE_SEQ_CST_64(type, ptr, val)	\
			REX_ATOMIC_CPU_MB();									\
			REX_ARCH_ATOMIC_ARM_STORE_64(type, ptr, val);			\
			REX_ATOMIC_CPU_MB()


	#endif


#endif


#endif /* REX_ATOMIC_INTERNAL_ARCH_ARM_STORE_H */
