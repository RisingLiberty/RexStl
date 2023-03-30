

#ifndef REX_ATOMIC_INTERNAL_MACROS_MEMORY_BARRIER_H
#define REX_ATOMIC_INTERNAL_MACROS_MEMORY_BARRIER_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_CPU_MB()
//
#define REX_ATOMIC_CPU_MB() rsl::memory_barrier()

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_CPU_WMB()
//
#define REX_ATOMIC_CPU_WMB() rsl::write_memory_barrier()

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_CPU_RMB()
//
#define REX_ATOMIC_CPU_RMB() rsl::read_memory_barrier()

#endif /* REX_ATOMIC_INTERNAL_MACROS_MEMORY_BARRIER_H */
