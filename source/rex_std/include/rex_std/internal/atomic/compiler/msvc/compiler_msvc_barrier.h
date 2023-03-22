


#ifndef REX_ATOMIC_INTERNAL_COMPILER_MSVC_BARRIER_H
#define REX_ATOMIC_INTERNAL_COMPILER_MSVC_BARRIER_H

#pragma once


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_COMPILER_BARRIER()
//
#define REX_COMPILER_ATOMIC_COMPILER_BARRIER()	\
	_ReadWriteBarrier()										\


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_COMPILER_BARRIER_DATA_DEPENDENCY(const T&, type)
//
#define REX_COMPILER_ATOMIC_COMPILER_BARRIER_DATA_DEPENDENCY(val, type) \
	REX_COMPILER_ATOMIC_COMPILER_BARRIER_DATA_DEPENDENCY_FUNC(const_cast<type*>(rsl::addressof((val)))); \
	REX_ATOMIC_COMPILER_BARRIER()


#endif /* REX_ATOMIC_INTERNAL_COMPILER_MSVC_BARRIER_H */
