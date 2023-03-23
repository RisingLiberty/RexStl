

#ifndef REX_ATOMIC_INTERNAL_COMPILER_GCC_BARRIER_H
#define REX_ATOMIC_INTERNAL_COMPILER_GCC_BARRIER_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_COMPILER_BARRIER()
//
#define REX_COMPILER_ATOMIC_COMPILER_BARRIER() __asm__ __volatile__("" ::: "memory")

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_COMPILER_BARRIER_DATA_DEPENDENCY(const T&, type)
//
#define REX_COMPILER_ATOMIC_COMPILER_BARRIER_DATA_DEPENDENCY(val, type) __asm__ __volatile__("" : /* Output Operands */ : "r"(&(val)) : "memory")

#endif /* REX_ATOMIC_INTERNAL_COMPILER_GCC_BARRIER_H */
