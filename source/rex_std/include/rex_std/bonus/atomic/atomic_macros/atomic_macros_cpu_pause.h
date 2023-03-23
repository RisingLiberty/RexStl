

#ifndef REX_ATOMIC_INTERNAL_MACROS_CPU_PAUSE_H
#define REX_ATOMIC_INTERNAL_MACROS_CPU_PAUSE_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_CPU_PAUSE()
//
#define REX_ATOMIC_CPU_PAUSE() REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_CPU_PAUSE)()

#endif /* REX_ATOMIC_INTERNAL_MACROS_CPU_PAUSE_H */
