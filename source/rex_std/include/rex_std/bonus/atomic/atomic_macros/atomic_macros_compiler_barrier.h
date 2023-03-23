

#ifndef REX_ATOMIC_INTERNAL_MACROS_COMPILER_BARRIER_H
#define REX_ATOMIC_INTERNAL_MACROS_COMPILER_BARRIER_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_COMPILER_BARRIER()
//
#define REX_ATOMIC_COMPILER_BARRIER() REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_COMPILER_BARRIER)()

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_COMPILER_BARRIER_DATA_DEPENDENCY(const T&, type)
//
#define REX_ATOMIC_COMPILER_BARRIER_DATA_DEPENDENCY(val, type) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_COMPILER_BARRIER_DATA_DEPENDENCY)(val, type)

#endif /* REX_ATOMIC_INTERNAL_MACROS_COMPILER_BARRIER_H */
