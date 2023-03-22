


#ifndef REX_ATOMIC_INTERNAL_MACROS_SIGNAL_FENCE_H
#define REX_ATOMIC_INTERNAL_MACROS_SIGNAL_FENCE_H

#pragma once


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_SIGNAL_FENCE_*()
//
#define REX_ATOMIC_SIGNAL_FENCE_RELAXED()						\
	REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_SIGNAL_FENCE_RELAXED)()

#define REX_ATOMIC_SIGNAL_FENCE_ACQUIRE()						\
	REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_SIGNAL_FENCE_ACQUIRE)()

#define REX_ATOMIC_SIGNAL_FENCE_RELEASE()						\
	REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_SIGNAL_FENCE_RELEASE)()

#define REX_ATOMIC_SIGNAL_FENCE_ACQ_REL()						\
	REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_SIGNAL_FENCE_ACQ_REL)()

#define REX_ATOMIC_SIGNAL_FENCE_SEQ_CST()						\
	REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_SIGNAL_FENCE_SEQ_CST)()


#endif /* REX_ATOMIC_INTERNAL_MACROS_SIGNAL_FENCE_H */
