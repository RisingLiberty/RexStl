


#ifndef REX_ATOMIC_INTERNAL_MACROS_BASE_H
#define REX_ATOMIC_INTERNAL_MACROS_BASE_H

#pragma once


#define REX_ATOMIC_INTERNAL_COMPILER_AVAILABLE(op)					\
	MERGE(MERGE(REX_COMPILER_, op), _AVAILABLE)

#define REX_ATOMIC_INTERNAL_ARCH_AVAILABLE(op)						\
	MERGE(MERGE(REX_ARCH_, op), _AVAILABLE)

#define REX_ATOMIC_INTERNAL_NOT_IMPLEMENTED_ERROR(...)				\
	static_assert(false, "rsl::atomic<T> atomic macro not implemented!")


/* Compiler && Arch Not Implemented */
#define REX_ATOMIC_INTERNAL_OP_PATTERN_00(op) \
	REX_ATOMIC_INTERNAL_NOT_IMPLEMENTED_ERROR

/* Arch Implemented */
#define REX_ATOMIC_INTERNAL_OP_PATTERN_01(op) \
	MERGE(REX_ARCH_, op)

/* Compiler Implmented */
#define REX_ATOMIC_INTERNAL_OP_PATTERN_10(op) \
	MERGE(REX_COMPILER_, op)

/* Compiler && Arch Implemented */
#define REX_ATOMIC_INTERNAL_OP_PATTERN_11(op) \
	MERGE(REX_ARCH_, op)


/* This macro creates the pattern macros above for the 2x2 True-False truth table */
#define REX_ATOMIC_INTERNAL_OP_HELPER1(compiler, arch, op)			\
	MERGE(REX_ATOMIC_INTERNAL_OP_PATTERN_, MERGE(compiler, arch))(op)


/////////////////////////////////////////////////////////////////////////////////
//
// REX_ATOMIC_CHOOSE_OP_IMPL
//
// This macro chooses between the compiler or architecture implementation for a
// given atomic operation.
//
// USAGE:
//
// REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_ADD_RELAXED_8)(ret, ptr, val)
//
#define REX_ATOMIC_CHOOSE_OP_IMPL(op)					\
	REX_ATOMIC_INTERNAL_OP_HELPER1(					\
		REX_ATOMIC_INTERNAL_COMPILER_AVAILABLE(op),	\
		REX_ATOMIC_INTERNAL_ARCH_AVAILABLE(op),		\
		op												\
		)


#endif /* REX_ATOMIC_INTERNAL_MACROS_BASE_H */
