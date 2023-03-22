


#ifndef REX_ATOMIC_INTERNAL_COMPILER_BARRIER_H
#define REX_ATOMIC_INTERNAL_COMPILER_BARRIER_H

#pragma once


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_COMPILER_BARRIER()
//
#if defined(REX_COMPILER_ATOMIC_COMPILER_BARRIER)
	#define REX_COMPILER_ATOMIC_COMPILER_BARRIER_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_COMPILER_BARRIER_AVAILABLE 0
#endif


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_COMPILER_BARRIER_DATA_DEPENDENCY(const T&, type)
//
#if defined(REX_COMPILER_ATOMIC_COMPILER_BARRIER_DATA_DEPENDENCY)
	#define REX_COMPILER_ATOMIC_COMPILER_BARRIER_DATA_DEPENDENCY_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_COMPILER_BARRIER_DATA_DEPENDENCY_AVAILABLE 0
#endif


#endif /* REX_ATOMIC_INTERNAL_COMPILER_BARRIER_H */
