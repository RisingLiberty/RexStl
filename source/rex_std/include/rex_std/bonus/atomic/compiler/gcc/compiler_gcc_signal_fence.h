

#ifndef REX_ATOMIC_INTERNAL_COMPILER_GCC_SIGNAL_FENCE_H
#define REX_ATOMIC_INTERNAL_COMPILER_GCC_SIGNAL_FENCE_H

#pragma once

#define REX_GCC_ATOMIC_SIGNAL_FENCE(gccMemoryOrder) __atomic_signal_fence(gccMemoryOrder)

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_SIGNAL_FENCE_*()
//
#define REX_COMPILER_ATOMIC_SIGNAL_FENCE_RELAXED() REX_GCC_ATOMIC_SIGNAL_FENCE(__ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_SIGNAL_FENCE_ACQUIRE() REX_GCC_ATOMIC_SIGNAL_FENCE(__ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_SIGNAL_FENCE_RELEASE() REX_GCC_ATOMIC_SIGNAL_FENCE(__ATOMIC_RELEASE)

#define REX_COMPILER_ATOMIC_SIGNAL_FENCE_ACQ_REL() REX_GCC_ATOMIC_SIGNAL_FENCE(__ATOMIC_ACQ_REL)

#define REX_COMPILER_ATOMIC_SIGNAL_FENCE_SEQ_CST() REX_GCC_ATOMIC_SIGNAL_FENCE(__ATOMIC_SEQ_CST)

#endif /* REX_ATOMIC_INTERNAL_COMPILER_GCC_SIGNAL_FENCE_H */