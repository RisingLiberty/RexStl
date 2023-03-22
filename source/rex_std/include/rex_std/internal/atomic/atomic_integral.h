


#ifndef REX_ATOMIC_INTERNAL_INTEGRAL_H
#define REX_ATOMIC_INTERNAL_INTEGRAL_H

#pragma once



namespace rsl
{
	inline namespace v1
	{


namespace internal
{


#define REX_ATOMIC_INTEGRAL_STATIC_ASSERT_FUNCS_IMPL(funcName)	\
	template <typename Order>										\
	T funcName(T /*arg*/, Order /*order*/)				\
	{																\
		REX_ATOMIC_STATIC_ASSERT_INVALID_MEMORY_ORDER(T);			\
	}																\
																	\
	template <typename Order>										\
	T funcName(T /*arg*/, Order /*order*/) volatile		\
	{																\
		REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);				\
	}																\
																	\
	T funcName(T /*arg*/) volatile						\
	{																\
		REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);				\
	}


#define REX_ATOMIC_INTEGRAL_STATIC_ASSERT_INC_DEC_OPERATOR_IMPL(operatorOp) \
	T operator operatorOp() volatile						\
	{																	\
		REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);					\
	}																	\
																		\
	T operator operatorOp(int) volatile						\
	{																	\
		REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);					\
	}


#define REX_ATOMIC_INTEGRAL_STATIC_ASSERT_ASSIGNMENT_OPERATOR_IMPL(operatorOp) \
	T operator operatorOp(T /*arg*/) volatile				\
	{																	\
		REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);					\
	}


	template <typename T, unsigned width = sizeof(T)>
	struct atomic_integral_base : public atomic_base_width<T, width>
	{
	private:

		using Base = atomic_base_width<T, width>;

	public: /* ctors */

		constexpr atomic_integral_base(T desired)
			: Base{ desired }
		{
		}

		constexpr atomic_integral_base() = default;

		atomic_integral_base(const atomic_integral_base&) = delete;

	public: /* assignment operator */

		using Base::operator=;

		atomic_integral_base& operator=(const atomic_integral_base&)          = delete;
		atomic_integral_base& operator=(const atomic_integral_base&) volatile = delete;

	public: /* fetch_add */

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_FUNCS_IMPL(fetch_add)

	public: /* add_fetch */

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_FUNCS_IMPL(add_fetch)

	public: /* fetch_sub */

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_FUNCS_IMPL(fetch_sub)

	public: /* sub_fetch */

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_FUNCS_IMPL(sub_fetch)

	public: /* fetch_and */

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_FUNCS_IMPL(fetch_and)

	public: /* and_fetch */

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_FUNCS_IMPL(and_fetch)

	public: /* fetch_or */

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_FUNCS_IMPL(fetch_or)

	public: /* or_fetch */

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_FUNCS_IMPL(or_fetch)

	public: /* fetch_xor */

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_FUNCS_IMPL(fetch_xor)

	public: /* xor_fetch */

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_FUNCS_IMPL(xor_fetch)

	public: /* operator++ && operator-- */

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_INC_DEC_OPERATOR_IMPL(++)

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_INC_DEC_OPERATOR_IMPL(--)

	public: /* operator+= && operator-= */

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_ASSIGNMENT_OPERATOR_IMPL(+=)

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_ASSIGNMENT_OPERATOR_IMPL(-=)

	public: /* operator&= */

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_ASSIGNMENT_OPERATOR_IMPL(&=)

	public: /* operator|= */

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_ASSIGNMENT_OPERATOR_IMPL(|=)

	public: /* operator^= */

		REX_ATOMIC_INTEGRAL_STATIC_ASSERT_ASSIGNMENT_OPERATOR_IMPL(^=)

	};


	template <typename T, unsigned width = sizeof(T)>
	struct atomic_integral_width;

#define REX_ATOMIC_INTEGRAL_FUNC_IMPL(op, bits)						\
	T retVal;															\
	MERGE(op, bits)(T, retVal, this->GetAtomicAddress(), arg); \
	return retVal;

#define REX_ATOMIC_INTEGRAL_FETCH_IMPL(funcName, op, bits)	\
	T funcName(T arg)								\
	{															\
		REX_ATOMIC_INTEGRAL_FUNC_IMPL(op, bits);				\
	}

#define REX_ATOMIC_INTEGRAL_FETCH_ORDER_IMPL(funcName, orderType, op, bits) \
	T funcName(T arg, orderType)							\
	{																	\
		REX_ATOMIC_INTEGRAL_FUNC_IMPL(op, bits);						\
	}

#define REX_ATOMIC_INTEGRAL_FETCH_OP_JOIN(fetchOp, Order)				\
	MERGE(MERGE(REX_ATOMIC_, fetchOp), Order)

#define REX_ATOMIC_INTEGRAL_FETCH_FUNCS_IMPL(funcName, fetchOp, bits) \
	using Base::funcName;												\
																		\
	REX_ATOMIC_INTEGRAL_FETCH_IMPL(funcName, REX_ATOMIC_INTEGRAL_FETCH_OP_JOIN(fetchOp, _SEQ_CST_), bits) \
																		\
	REX_ATOMIC_INTEGRAL_FETCH_ORDER_IMPL(funcName, rsl::internal::memory_order_relaxed_s, \
										   REX_ATOMIC_INTEGRAL_FETCH_OP_JOIN(fetchOp, _RELAXED_), bits) \
																		\
	REX_ATOMIC_INTEGRAL_FETCH_ORDER_IMPL(funcName, rsl::internal::memory_order_acquire_s, \
										   REX_ATOMIC_INTEGRAL_FETCH_OP_JOIN(fetchOp, _ACQUIRE_), bits) \
																		\
	REX_ATOMIC_INTEGRAL_FETCH_ORDER_IMPL(funcName, rsl::internal::memory_order_release_s, \
										   REX_ATOMIC_INTEGRAL_FETCH_OP_JOIN(fetchOp, _RELEASE_), bits) \
																		\
	REX_ATOMIC_INTEGRAL_FETCH_ORDER_IMPL(funcName, rsl::internal::memory_order_acq_rel_s, \
										   REX_ATOMIC_INTEGRAL_FETCH_OP_JOIN(fetchOp, _ACQ_REL_), bits) \
																		\
	REX_ATOMIC_INTEGRAL_FETCH_ORDER_IMPL(funcName, rsl::internal::memory_order_seq_cst_s, \
										   REX_ATOMIC_INTEGRAL_FETCH_OP_JOIN(fetchOp, _SEQ_CST_), bits)

#define REX_ATOMIC_INTEGRAL_FETCH_INC_DEC_OPERATOR_IMPL(operatorOp, preFuncName, postFuncName) \
	using Base::operator operatorOp;									\
																		\
	T operator operatorOp()									\
	{																	\
		return preFuncName(1, rsl::memory_order_seq_cst);				\
	}																	\
																		\
	T operator operatorOp(int)								\
	{																	\
		return postFuncName(1, rsl::memory_order_seq_cst);			\
	}

#define REX_ATOMIC_INTEGRAL_FETCH_ASSIGNMENT_OPERATOR_IMPL(operatorOp, funcName) \
	using Base::operator operatorOp;									\
																		\
	T operator operatorOp(T arg)							\
	{																	\
		return funcName(arg, rsl::memory_order_seq_cst);				\
	}


#define REX_ATOMIC_INTEGRAL_WIDTH_SPECIALIZE(bytes, bits)				\
	template <typename T>												\
	struct atomic_integral_width<T, bytes> : public atomic_integral_base<T, bytes> \
	{																	\
	private:															\
																		\
		using Base = atomic_integral_base<T, bytes>;					\
																		\
	public: /* ctors */													\
																		\
		constexpr atomic_integral_width(T desired)		\
			: Base{ desired }											\
		{																\
		}																\
																		\
		constexpr atomic_integral_width() = default;		\
																		\
		atomic_integral_width(const atomic_integral_width&) = delete; \
																		\
	public: /* assignment operator */									\
																		\
		using Base::operator=;											\
																		\
		atomic_integral_width& operator=(const atomic_integral_width&)          = delete; \
		atomic_integral_width& operator=(const atomic_integral_width&) volatile = delete; \
																		\
	public: /* fetch_add */												\
																		\
		REX_ATOMIC_INTEGRAL_FETCH_FUNCS_IMPL(fetch_add, FETCH_ADD, bits) \
																		\
	public: /* add_fetch */												\
																		\
		REX_ATOMIC_INTEGRAL_FETCH_FUNCS_IMPL(add_fetch, ADD_FETCH, bits) \
																		\
	public: /* fetch_sub */												\
																		\
		REX_ATOMIC_INTEGRAL_FETCH_FUNCS_IMPL(fetch_sub, FETCH_SUB, bits) \
																		\
	public: /* sub_fetch */												\
																		\
		REX_ATOMIC_INTEGRAL_FETCH_FUNCS_IMPL(sub_fetch, SUB_FETCH, bits) \
																		\
	public: /* fetch_and */												\
																		\
		REX_ATOMIC_INTEGRAL_FETCH_FUNCS_IMPL(fetch_and, FETCH_AND, bits) \
																		\
	public: /* and_fetch */												\
																		\
		REX_ATOMIC_INTEGRAL_FETCH_FUNCS_IMPL(and_fetch, AND_FETCH, bits) \
																		\
	public: /* fetch_or */												\
																		\
		REX_ATOMIC_INTEGRAL_FETCH_FUNCS_IMPL(fetch_or, FETCH_OR, bits) \
																		\
	public: /* or_fetch */												\
																		\
		REX_ATOMIC_INTEGRAL_FETCH_FUNCS_IMPL(or_fetch, OR_FETCH, bits) \
																		\
	public: /* fetch_xor */												\
																		\
		REX_ATOMIC_INTEGRAL_FETCH_FUNCS_IMPL(fetch_xor, FETCH_XOR, bits) \
																		\
	public: /* xor_fetch */												\
																		\
		REX_ATOMIC_INTEGRAL_FETCH_FUNCS_IMPL(xor_fetch, XOR_FETCH, bits) \
																		\
	public: /* operator++ && operator-- */								\
																		\
		REX_ATOMIC_INTEGRAL_FETCH_INC_DEC_OPERATOR_IMPL(++, add_fetch, fetch_add) \
																		\
		REX_ATOMIC_INTEGRAL_FETCH_INC_DEC_OPERATOR_IMPL(--, sub_fetch, fetch_sub) \
																		\
	public: /* operator+= && operator-= */								\
																		\
		REX_ATOMIC_INTEGRAL_FETCH_ASSIGNMENT_OPERATOR_IMPL(+=, add_fetch) \
																		\
		REX_ATOMIC_INTEGRAL_FETCH_ASSIGNMENT_OPERATOR_IMPL(-=, sub_fetch) \
																		\
	public: /* operator&= */											\
																		\
		REX_ATOMIC_INTEGRAL_FETCH_ASSIGNMENT_OPERATOR_IMPL(&=, and_fetch) \
																		\
	public: /* operator|= */											\
																		\
		REX_ATOMIC_INTEGRAL_FETCH_ASSIGNMENT_OPERATOR_IMPL(|=, or_fetch) \
																		\
	public: /* operator^= */											\
																		\
		REX_ATOMIC_INTEGRAL_FETCH_ASSIGNMENT_OPERATOR_IMPL(^=, xor_fetch) \
																		\
	};


#if defined(REX_ATOMIC_HAS_8BIT)
	REX_ATOMIC_INTEGRAL_WIDTH_SPECIALIZE(1, 8)
#endif

#if defined(REX_ATOMIC_HAS_16BIT)
	REX_ATOMIC_INTEGRAL_WIDTH_SPECIALIZE(2, 16)
#endif

#if defined(REX_ATOMIC_HAS_32BIT)
	REX_ATOMIC_INTEGRAL_WIDTH_SPECIALIZE(4, 32)
#endif

#if defined(REX_ATOMIC_HAS_64BIT)
	REX_ATOMIC_INTEGRAL_WIDTH_SPECIALIZE(8, 64)
#endif

#if defined(REX_ATOMIC_HAS_128BIT)
	REX_ATOMIC_INTEGRAL_WIDTH_SPECIALIZE(16, 128)
#endif


} // namespace internal

	}

} // namespace rsl



#endif /* REX_ATOMIC_INTERNAL_INTEGRAL_H */
