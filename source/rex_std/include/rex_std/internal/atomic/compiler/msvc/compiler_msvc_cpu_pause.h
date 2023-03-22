


#ifndef REX_ATOMIC_INTERNAL_COMPILER_MSVC_CPU_PAUSE_H
#define REX_ATOMIC_INTERNAL_COMPILER_MSVC_CPU_PAUSE_H

#pragma once


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_CPU_PAUSE()
//
// NOTE:
// Rather obscure macro in Windows.h that expands to pause or rep; nop on
// compatible x86 cpus or the arm yield on compatible arm processors.
// This is nicer than switching on platform specific intrinsics.
//
#define REX_COMPILER_ATOMIC_CPU_PAUSE()		\
	YieldProcessor()


#endif /* REX_ATOMIC_INTERNAL_COMPILER_MSVC_CPU_PAUSE_H */
