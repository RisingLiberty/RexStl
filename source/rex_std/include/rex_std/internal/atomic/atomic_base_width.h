


#ifndef REX_ATOMIC_INTERNAL_BASE_WIDTH_H
#define REX_ATOMIC_INTERNAL_BASE_WIDTH_H

#pragma once



namespace rsl
{
	inline namespace v1
	{


namespace internal
{


	template <typename T, unsigned width = sizeof(T)>
	struct atomic_base_width;

	/**
	 * NOTE:
	 *
	 * T does not have to be trivially default constructible but it still
	 * has to be a trivially copyable type for the primary atomic template.
	 * Thus we must type pun into whatever storage type of the given fixed width
	 * the platform designates. This ensures T does not have to be trivially constructible.
	 */

#define REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits)				\
	MERGE(REX_ATOMIC_FIXED_WIDTH_TYPE_, bits)


#define REX_ATOMIC_STORE_FUNC_IMPL(op, bits)							\
	REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits) fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits), desired); \
	MERGE(op, bits)(REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits), \
								   REX_ATOMIC_TYPE_CAST(REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits), this->GetAtomicAddress()), \
								   fixedWidthDesired)


#define REX_ATOMIC_LOAD_FUNC_IMPL(op, bits)							\
	REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits) retVal;					\
	MERGE(op, bits)(REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits), \
								   retVal,								\
								   REX_ATOMIC_TYPE_CAST(REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits), this->GetAtomicAddress())); \
	return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);


#define REX_ATOMIC_EXCHANGE_FUNC_IMPL(op, bits)						\
	REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits) retVal;					\
	REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits) fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits), desired); \
	MERGE(op, bits)(REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits), \
								   retVal,								\
								   REX_ATOMIC_TYPE_CAST(REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits), this->GetAtomicAddress()), \
								   fixedWidthDesired);					\
	return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);


#define REX_ATOMIC_CMPXCHG_FUNC_IMPL(op, bits)						\
	bool retVal;														\
	REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits) fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits), desired); \
	MERGE(op, bits)(REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits), \
								   retVal,								\
								   REX_ATOMIC_TYPE_CAST(REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits), this->GetAtomicAddress()), \
								   REX_ATOMIC_TYPE_CAST(REX_ATOMIC_BASE_FIXED_WIDTH_TYPE(bits), &expected), \
								   fixedWidthDesired);					\
	return retVal;


#define REX_ATOMIC_BASE_OP_JOIN(op, Order)						\
	MERGE(MERGE(REX_ATOMIC_, op), Order)


#define REX_ATOMIC_BASE_CMPXCHG_FUNCS_IMPL(funcName, cmpxchgOp, bits)	\
	using Base::funcName;												\
																		\
	bool funcName(T& expected, T desired)					\
	{																	\
		REX_ATOMIC_CMPXCHG_FUNC_IMPL(REX_ATOMIC_BASE_OP_JOIN(cmpxchgOp, _SEQ_CST_), bits); \
	}																	\
																		\
	bool funcName(T& expected, T desired,								\
				  rsl::internal::memory_order_relaxed_s)	\
	{																	\
		REX_ATOMIC_CMPXCHG_FUNC_IMPL(REX_ATOMIC_BASE_OP_JOIN(cmpxchgOp, _RELAXED_), bits); \
	}																	\
																		\
	bool funcName(T& expected, T desired,								\
				  rsl::internal::memory_order_acquire_s)	\
	{																	\
		REX_ATOMIC_CMPXCHG_FUNC_IMPL(REX_ATOMIC_BASE_OP_JOIN(cmpxchgOp, _ACQUIRE_), bits); \
	}																	\
																		\
	bool funcName(T& expected, T desired,								\
				  rsl::internal::memory_order_release_s)	\
	{																	\
		REX_ATOMIC_CMPXCHG_FUNC_IMPL(REX_ATOMIC_BASE_OP_JOIN(cmpxchgOp, _RELEASE_), bits); \
	}																	\
																		\
	bool funcName(T& expected, T desired,								\
				  rsl::internal::memory_order_acq_rel_s)	\
	{																	\
		REX_ATOMIC_CMPXCHG_FUNC_IMPL(REX_ATOMIC_BASE_OP_JOIN(cmpxchgOp, _ACQ_REL_), bits); \
	}																	\
																		\
	bool funcName(T& expected, T desired,								\
				  rsl::internal::memory_order_seq_cst_s)	\
	{																	\
		REX_ATOMIC_CMPXCHG_FUNC_IMPL(REX_ATOMIC_BASE_OP_JOIN(cmpxchgOp, _SEQ_CST_), bits); \
	}																	\
																		\
	bool funcName(T& expected, T desired,								\
				  rsl::internal::memory_order_relaxed_s,				\
				  rsl::internal::memory_order_relaxed_s)	\
	{																	\
		REX_ATOMIC_CMPXCHG_FUNC_IMPL(REX_ATOMIC_BASE_OP_JOIN(cmpxchgOp, _RELAXED_RELAXED_), bits); \
	}																	\
																		\
	bool funcName(T& expected, T desired,								\
				  rsl::internal::memory_order_acquire_s,				\
				  rsl::internal::memory_order_relaxed_s)	\
	{																	\
		REX_ATOMIC_CMPXCHG_FUNC_IMPL(REX_ATOMIC_BASE_OP_JOIN(cmpxchgOp, _ACQUIRE_RELAXED_), bits); \
	}																	\
																		\
	bool funcName(T& expected, T desired,								\
				  rsl::internal::memory_order_acquire_s,				\
				  rsl::internal::memory_order_acquire_s)	\
	{																	\
		REX_ATOMIC_CMPXCHG_FUNC_IMPL(REX_ATOMIC_BASE_OP_JOIN(cmpxchgOp, _ACQUIRE_ACQUIRE_), bits); \
	}																	\
																		\
	bool funcName(T& expected, T desired,								\
				  rsl::internal::memory_order_release_s,				\
				  rsl::internal::memory_order_relaxed_s)	\
	{																	\
		REX_ATOMIC_CMPXCHG_FUNC_IMPL(REX_ATOMIC_BASE_OP_JOIN(cmpxchgOp, _RELEASE_RELAXED_), bits); \
	}																	\
																		\
	bool funcName(T& expected, T desired,								\
				  rsl::internal::memory_order_acq_rel_s,				\
				  rsl::internal::memory_order_relaxed_s)	\
	{																	\
		REX_ATOMIC_CMPXCHG_FUNC_IMPL(REX_ATOMIC_BASE_OP_JOIN(cmpxchgOp, _ACQ_REL_RELAXED_), bits); \
	}																	\
																		\
	bool funcName(T& expected, T desired,								\
				  rsl::internal::memory_order_acq_rel_s,				\
				  rsl::internal::memory_order_acquire_s)	\
	{																	\
		REX_ATOMIC_CMPXCHG_FUNC_IMPL(REX_ATOMIC_BASE_OP_JOIN(cmpxchgOp, _ACQ_REL_ACQUIRE_), bits); \
	}																	\
																		\
	bool funcName(T& expected, T desired,								\
				  rsl::internal::memory_order_seq_cst_s,				\
				  rsl::internal::memory_order_relaxed_s)	\
	{																	\
		REX_ATOMIC_CMPXCHG_FUNC_IMPL(REX_ATOMIC_BASE_OP_JOIN(cmpxchgOp, _SEQ_CST_RELAXED_), bits); \
	}																	\
																		\
	bool funcName(T& expected, T desired,								\
				  rsl::internal::memory_order_seq_cst_s,				\
				  rsl::internal::memory_order_acquire_s)	\
	{																	\
		REX_ATOMIC_CMPXCHG_FUNC_IMPL(REX_ATOMIC_BASE_OP_JOIN(cmpxchgOp, _SEQ_CST_ACQUIRE_), bits); \
	}																	\
																		\
	bool funcName(T& expected, T desired,								\
				  rsl::internal::memory_order_seq_cst_s,				\
				  rsl::internal::memory_order_seq_cst_s)	\
	{																	\
		REX_ATOMIC_CMPXCHG_FUNC_IMPL(REX_ATOMIC_BASE_OP_JOIN(cmpxchgOp, _SEQ_CST_SEQ_CST_), bits); \
	}

#define REX_ATOMIC_BASE_CMPXCHG_WEAK_FUNCS_IMPL(bits)					\
	REX_ATOMIC_BASE_CMPXCHG_FUNCS_IMPL(compare_exchange_weak, CMPXCHG_WEAK, bits)

#define REX_ATOMIC_BASE_CMPXCHG_STRONG_FUNCS_IMPL(bits)				\
	REX_ATOMIC_BASE_CMPXCHG_FUNCS_IMPL(compare_exchange_strong, CMPXCHG_STRONG, bits)


#define REX_ATOMIC_BASE_WIDTH_SPECIALIZE(bytes, bits)					\
	template <typename T>												\
	struct atomic_base_width<T, bytes> : public atomic_size_aligned<T>	\
	{																	\
	private:															\
																		\
		static_assert(alignof(atomic_size_aligned<T>) == bytes, "rsl::atomic<T> must be sizeof(T) aligned!"); \
		static_assert(alignof(atomic_size_aligned<T>) == sizeof(T), "rsl::atomic<T> must be sizeof(T) aligned!"); \
		using Base = atomic_size_aligned<T>;							\
																		\
	public: /* ctors */													\
																		\
		constexpr atomic_base_width(T desired)			\
			: Base{ desired }											\
		{																\
		}																\
																		\
		constexpr atomic_base_width() = default; \
																		\
		atomic_base_width(const atomic_base_width&) = delete; \
																		\
	public: /* store */													\
																		\
		using Base::store;												\
																		\
		void store(T desired)								\
		{																\
			REX_ATOMIC_STORE_FUNC_IMPL(REX_ATOMIC_STORE_SEQ_CST_, bits); \
		}																\
																		\
		void store(T desired, rsl::internal::memory_order_relaxed_s)	\
		{																\
			REX_ATOMIC_STORE_FUNC_IMPL(REX_ATOMIC_STORE_RELAXED_, bits); \
		}																\
																		\
		void store(T desired, rsl::internal::memory_order_release_s)	\
		{																\
			REX_ATOMIC_STORE_FUNC_IMPL(REX_ATOMIC_STORE_RELEASE_, bits); \
		}																\
																		\
		void store(T desired, rsl::internal::memory_order_seq_cst_s)	\
		{																\
			REX_ATOMIC_STORE_FUNC_IMPL(REX_ATOMIC_STORE_SEQ_CST_, bits); \
		}																\
																		\
	public: /* load */													\
																		\
		using Base::load;												\
																		\
		T load() const										\
		{																\
			REX_ATOMIC_LOAD_FUNC_IMPL(REX_ATOMIC_LOAD_SEQ_CST_, bits); \
		}																\
																		\
		T load(rsl::internal::memory_order_relaxed_s) const \
		{																\
			REX_ATOMIC_LOAD_FUNC_IMPL(REX_ATOMIC_LOAD_RELAXED_, bits); \
		}																\
																		\
		T load(rsl::internal::memory_order_acquire_s) const \
		{																\
			REX_ATOMIC_LOAD_FUNC_IMPL(REX_ATOMIC_LOAD_ACQUIRE_, bits); \
		}																\
																		\
		T load(rsl::internal::memory_order_seq_cst_s) const \
		{																\
			REX_ATOMIC_LOAD_FUNC_IMPL(REX_ATOMIC_LOAD_SEQ_CST_, bits); \
		}																\
																		\
	public: /* exchange */												\
																		\
		using Base::exchange;											\
																		\
		T exchange(T desired)								\
		{																\
			REX_ATOMIC_EXCHANGE_FUNC_IMPL(REX_ATOMIC_EXCHANGE_SEQ_CST_, bits); \
		}																\
																		\
		T exchange(T desired, rsl::internal::memory_order_relaxed_s) \
		{																\
			REX_ATOMIC_EXCHANGE_FUNC_IMPL(REX_ATOMIC_EXCHANGE_RELAXED_, bits); \
		}																\
																		\
		T exchange(T desired, rsl::internal::memory_order_acquire_s)	\
		{																\
			REX_ATOMIC_EXCHANGE_FUNC_IMPL(REX_ATOMIC_EXCHANGE_ACQUIRE_, bits); \
		}																\
																		\
		T exchange(T desired, rsl::internal::memory_order_release_s)	\
		{																\
			REX_ATOMIC_EXCHANGE_FUNC_IMPL(REX_ATOMIC_EXCHANGE_RELEASE_, bits); \
		}																\
																		\
		T exchange(T desired, rsl::internal::memory_order_acq_rel_s)	\
		{																\
			REX_ATOMIC_EXCHANGE_FUNC_IMPL(REX_ATOMIC_EXCHANGE_ACQ_REL_, bits); \
		}																\
																		\
		T exchange(T desired, rsl::internal::memory_order_seq_cst_s)	\
		{																\
			REX_ATOMIC_EXCHANGE_FUNC_IMPL(REX_ATOMIC_EXCHANGE_SEQ_CST_, bits); \
		}																\
																		\
	public: /* compare_exchange_weak */									\
																		\
		REX_ATOMIC_BASE_CMPXCHG_WEAK_FUNCS_IMPL(bits)					\
																		\
	public: /* compare_exchange_strong */								\
																		\
		REX_ATOMIC_BASE_CMPXCHG_STRONG_FUNCS_IMPL(bits)				\
																		\
	public: /* assignment operator */									\
																		\
		using Base::operator=;											\
																		\
		T operator=(T desired)								\
		{																\
			store(desired, rsl::memory_order_seq_cst);				\
			return desired;												\
		}																\
																		\
		atomic_base_width& operator=(const atomic_base_width&)          = delete; \
		atomic_base_width& operator=(const atomic_base_width&) volatile = delete; \
																		\
	};


#if defined(REX_ATOMIC_HAS_8BIT)
	REX_ATOMIC_BASE_WIDTH_SPECIALIZE(1, 8)
#endif

#if defined(REX_ATOMIC_HAS_16BIT)
	REX_ATOMIC_BASE_WIDTH_SPECIALIZE(2, 16)
#endif

#if defined(REX_ATOMIC_HAS_32BIT)
	REX_ATOMIC_BASE_WIDTH_SPECIALIZE(4, 32)
#endif

#if defined(REX_ATOMIC_HAS_64BIT)
	REX_ATOMIC_BASE_WIDTH_SPECIALIZE(8, 64)
#endif

#if defined(REX_ATOMIC_HAS_128BIT)
	REX_ATOMIC_BASE_WIDTH_SPECIALIZE(16, 128)
#endif


} // namespace internal
	}


} // namespace rsl



#endif /* REX_ATOMIC_INTERNAL_BASE_WIDTH_H */
