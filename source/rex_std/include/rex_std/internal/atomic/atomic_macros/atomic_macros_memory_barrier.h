

#ifndef REX_ATOMIC_INTERNAL_MACROS_MEMORY_BARRIER_H
#define REX_ATOMIC_INTERNAL_MACROS_MEMORY_BARRIER_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_CPU_MB()
//
#define REX_ATOMIC_CPU_MB() REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_CPU_MB)()

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_CPU_WMB()
//
#define REX_ATOMIC_CPU_WMB() REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_CPU_WMB)()

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_CPU_RMB()
//
#define REX_ATOMIC_CPU_RMB() REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_CPU_RMB)()

#endif /* REX_ATOMIC_INTERNAL_MACROS_MEMORY_BARRIER_H */
