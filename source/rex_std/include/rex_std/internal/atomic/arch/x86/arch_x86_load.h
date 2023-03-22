


#ifndef REX_ATOMIC_INTERNAL_ARCH_X86_LOAD_H
#define REX_ATOMIC_INTERNAL_ARCH_X86_LOAD_H

#pragma once


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_LOAD_*_N(type, type ret, type * ptr)
//

#if ((defined(REX_COMPILER_CLANG) || defined(REX_COMPILER_GCC)) && defined(REX_PLATFORM_X64))


	/**
	 * NOTE:
	 *
	 * Since the cmpxchg 128-bit inline assembly does a sete in the asm to set the return boolean,
	 * it doesn't get dead-store removed even though we don't care about the success of the
	 * cmpxchg since the compiler cannot reason about what is inside asm blocks.
	 * Thus this variant just does the minimum required to do an atomic load.
	 */
#define REX_ARCH_ATOMIC_X86_LOAD_128(type, ret, ptr, MemoryOrder)		\
		{																	\
			REX_ATOMIC_FIXED_WIDTH_TYPE_128 expected = 0;					\
			ret = REX_ATOMIC_TYPE_PUN_CAST(type, expected);				\
																			\
			/* Compare RDX:RAX with m128. If equal, set ZF and load RCX:RBX into m128. Else, clear ZF and load m128 into RDX:RAX. */ \
			__asm__ __volatile__ ("lock; cmpxchg16b %2" /* cmpxchg16b sets/clears ZF */ \
								  /* Output  Operands */					\
								  : "=a"((REX_ATOMIC_TYPE_CAST(uint64_t, &(ret)))[0]), "=d"((REX_ATOMIC_TYPE_CAST(uint64_t, &(ret)))[1]), \
									"+m"(*(REX_ATOMIC_VOLATILE_INTEGRAL_CAST(__uint128_t, (ptr)))) \
								  /* Input Operands */						\
								  : "b"((REX_ATOMIC_TYPE_CAST(uint64_t, &(ret)))[0]), "c"((REX_ATOMIC_TYPE_CAST(uint64_t, &(ret)))[1]), \
									"a"((REX_ATOMIC_TYPE_CAST(uint64_t, &(ret)))[0]), "d"((REX_ATOMIC_TYPE_CAST(uint64_t, &(ret)))[1]) \
								  /* Clobbers */							\
								  : "memory", "cc");						\
		}


#define REX_ARCH_ATOMIC_LOAD_RELAXED_128(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_128(type, ret, ptr, RELAXED)

#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_128(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_128(type, ret, ptr, ACQUIRE)

#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_128(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_128(type, ret, ptr, SEQ_CST)

#elif defined(REX_COMPILER_MSVC)


	#if defined(REX_COMPILER_MSVC) && (REX_COMPILER_VERSION >= 1920) // >= VS2019

		#define REX_ARCH_ATOMIC_X86_LOAD_N(integralType, bits, type, ret, ptr) \
			{																	\
				integralType retIntegral;										\
				retIntegral = MERGE(__iso_volatile_load, bits)(REX_ATOMIC_VOLATILE_INTEGRAL_CAST(integralType, (ptr))); \
																				\
				ret = REX_ATOMIC_TYPE_PUN_CAST(type, retIntegral);			\
			}

	#else

		#define REX_ARCH_ATOMIC_X86_LOAD_N(integralType, bits, type, ret, ptr) \
			{																	\
				integralType retIntegral;										\
				retIntegral = (*(REX_ATOMIC_VOLATILE_INTEGRAL_CAST(integralType, (ptr)))); \
																				\
				ret = REX_ATOMIC_TYPE_PUN_CAST(type, retIntegral);			\
			}

	#endif


	#define REX_ARCH_ATOMIC_X86_LOAD_128(type, ret, ptr, MemoryOrder)		\
		{																	\
			REX_ATOMIC_FIXED_WIDTH_TYPE_128 expected{0, 0};				\
			ret = REX_ATOMIC_TYPE_PUN_CAST(type, expected);				\
																			\
			bool cmpxchgRetBool; (void)(cmpxchgRetBool);					\
			MERGE(MERGE(REX_ATOMIC_CMPXCHG_STRONG_, MemoryOrder), _128)(type, cmpxchgRetBool, ptr, &(ret), ret); \
		}


	#define REX_ARCH_ATOMIC_X86_LOAD_8(type, ret, ptr)		\
		REX_ARCH_ATOMIC_X86_LOAD_N(__int8, 8, type, ret, ptr)

	#define REX_ARCH_ATOMIC_X86_LOAD_16(type, ret, ptr)		\
		REX_ARCH_ATOMIC_X86_LOAD_N(__int16, 16, type, ret, ptr)

	#define REX_ARCH_ATOMIC_X86_LOAD_32(type, ret, ptr)		\
		REX_ARCH_ATOMIC_X86_LOAD_N(__int32, 32, type, ret, ptr)

	#define REX_ARCH_ATOMIC_X86_LOAD_64(type, ret, ptr)		\
		REX_ARCH_ATOMIC_X86_LOAD_N(__int64, 64, type, ret, ptr)


	#define REX_ARCH_ATOMIC_LOAD_RELAXED_8(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_8(type, ret, ptr)

	#define REX_ARCH_ATOMIC_LOAD_RELAXED_16(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_16(type, ret, ptr)

	#define REX_ARCH_ATOMIC_LOAD_RELAXED_32(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_32(type, ret, ptr)

	#define REX_ARCH_ATOMIC_LOAD_RELAXED_64(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_64(type, ret, ptr)

	#define REX_ARCH_ATOMIC_LOAD_RELAXED_128(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_128(type, ret, ptr, RELAXED)


	#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_8(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_8(type, ret, ptr);			\
		REX_ATOMIC_COMPILER_BARRIER()

	#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_16(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_16(type, ret, ptr);			\
		REX_ATOMIC_COMPILER_BARRIER()

	#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_32(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_32(type, ret, ptr);			\
		REX_ATOMIC_COMPILER_BARRIER()

	#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_64(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_64(type, ret, ptr);			\
		REX_ATOMIC_COMPILER_BARRIER()

	#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_128(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_128(type, ret, ptr, ACQUIRE)


	#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_8(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_8(type, ret, ptr);			\
		REX_ATOMIC_COMPILER_BARRIER()

	#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_16(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_16(type, ret, ptr);			\
		REX_ATOMIC_COMPILER_BARRIER()

	#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_32(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_32(type, ret, ptr);			\
		REX_ATOMIC_COMPILER_BARRIER()

	#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_64(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_64(type, ret, ptr);			\
		REX_ATOMIC_COMPILER_BARRIER()

	#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_128(type, ret, ptr)	\
		REX_ARCH_ATOMIC_X86_LOAD_128(type, ret, ptr, SEQ_CST)

#endif


#endif /* REX_ATOMIC_INTERNAL_ARCH_X86_LOAD_H */
