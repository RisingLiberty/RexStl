


#ifndef REX_ATOMIC_INTERNAL_ARCH_CPU_PAUSE_H
#define REX_ATOMIC_INTERNAL_ARCH_CPU_PAUSE_H

#pragma once


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_CPU_PAUSE()
//
#if defined(REX_ARCH_ATOMIC_CPU_PAUSE)
	#define REX_ARCH_ATOMIC_CPU_PAUSE_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_CPU_PAUSE_AVAILABLE 0
#endif


#endif /* REX_ATOMIC_INTERNAL_ARCH_CPU_PAUSE_H */
