


#ifndef REX_ATOMIC_INTERNAL_COMPILER_CPU_PAUSE_H
#define REX_ATOMIC_INTERNAL_COMPILER_CPU_PAUSE_H

#pragma once


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_CPU_PAUSE()
//
#if defined(REX_COMPILER_ATOMIC_CPU_PAUSE)

	#define REX_COMPILER_ATOMIC_CPU_PAUSE_AVAILABLE 1

#else

	#define REX_COMPILER_ATOMIC_CPU_PAUSE()		\
		((void)0)

	#define REX_COMPILER_ATOMIC_CPU_PAUSE_AVAILABLE 1

#endif


#endif /* REX_ATOMIC_INTERNAL_COMPILER_CPU_PAUSE_H */
