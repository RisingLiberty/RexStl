

#ifndef REX_ATOMIC_INTERNAL_COMPILER_MSVC_SIGNAL_FENCE_H
#define REX_ATOMIC_INTERNAL_COMPILER_MSVC_SIGNAL_FENCE_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_SIGNAL_FENCE_*()
//
#define REX_COMPILER_ATOMIC_SIGNAL_FENCE_RELAXED() REX_ATOMIC_COMPILER_BARRIER()

#define REX_COMPILER_ATOMIC_SIGNAL_FENCE_ACQUIRE() REX_ATOMIC_COMPILER_BARRIER()

#define REX_COMPILER_ATOMIC_SIGNAL_FENCE_RELEASE() REX_ATOMIC_COMPILER_BARRIER()

#define REX_COMPILER_ATOMIC_SIGNAL_FENCE_ACQ_REL() REX_ATOMIC_COMPILER_BARRIER()

#define REX_COMPILER_ATOMIC_SIGNAL_FENCE_SEQ_CST() REX_ATOMIC_COMPILER_BARRIER()

#endif /* REX_ATOMIC_INTERNAL_COMPILER_MSVC_SIGNAL_FENCE_H */
