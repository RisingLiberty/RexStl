

#ifndef REX_ATOMIC_INTERNAL_MACROS_COMPILER_BARRIER_H
#define REX_ATOMIC_INTERNAL_MACROS_COMPILER_BARRIER_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_COMPILER_BARRIER()
//
#define REX_ATOMIC_COMPILER_BARRIER() rsl::compiler_barrier()

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_COMPILER_BARRIER_DATA_DEPENDENCY(const T&, type)
//
#define REX_ATOMIC_COMPILER_BARRIER_DATA_DEPENDENCY(val, type) rsl::compiler_barrier(&type)

#endif /* REX_ATOMIC_INTERNAL_MACROS_COMPILER_BARRIER_H */
