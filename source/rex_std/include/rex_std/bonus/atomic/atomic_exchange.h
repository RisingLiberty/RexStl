// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_exchange.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/atomic/atomic_casts.h"
#include "rex_std/bonus/atomic/atomic_compiler_barrier.h"
#include "rex_std/bonus/atomic/atomic_fixed_width_type.h"
#include "rex_std/bonus/types.h"

#if defined(REX_COMPILER_MSVC)
  #include <intrin.h>
#endif

namespace rsl
{
  inline namespace v1
  {
#if defined(REX_COMPILER_MSVC)
    namespace internal
    {
      template <typename T>
      auto interlocked_exchange(volatile atomic8_t* volatileObject, atomic_t<T> newVal)
      {
        return _InterlockedExchange8(volatileObject, newVal);
      }
      template <typename T>
      auto interlocked_exchange(volatile atomic16_t* volatileObject, atomic_t<T> newVal)
      {
        return _InterlockedExchange16(volatileObject, newVal);
      }
      template <typename T>
      auto interlocked_exchange(volatile atomic32_t* volatileObject, atomic_t<T> newVal)
      {
        return _InterlockedExchange(volatileObject, newVal);
      }
      template <typename T>
      auto interlocked_exchange(volatile atomic64_t* volatileObject, atomic_t<T> newVal)
      {
        return _InterlockedExchange64(volatileObject, newVal);
      }
    } // namespace internal

    template <typename T>
    T atomic_exchange(T* obj, T value, rsl::memory_order order)
    {
      (void)order;
      const atomic_t<T> atom_value_to_set = *rsl::internal::atomic_integral_cast<const atomic_t<T>>(&value);
      volatile atomic_t<T>* volatile_obj  = rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj);

      return internal::interlocked_exchange<T>(volatile_obj, atom_value_to_set);
    }
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
    template <typename T>
    atomic_t<T> atomic_exchange(T* obj, T value, rsl::memory_order order)
    {
      // GCC Documentation says:
      // These built-in functions perform the operation suggested by the name, and return the value that had previously been in *ptr.
      // Operations on pointer arguments are performed as if the operands were of the uintptr_t type.
      // That is, they are not scaled by the size of the type to which the pointer points.
      // { tmp = *ptr; *ptr op= val; return tmp; }
      // Therefore we save their value to a temporary of type uintptr first and perform the operation on that
      rsl::uintptr& tmp = *reinterpret_cast<rsl::uintptr*>(obj);

      switch(order)
      {
        case rsl::v1::memory_order::relaxed: return __atomic_exchange_n(&tmp, value, __ATOMIC_RELAXED);
        case rsl::v1::memory_order::consume: return __atomic_exchange_n(&tmp, value, __ATOMIC_CONSUME);
        case rsl::v1::memory_order::acquire: return __atomic_exchange_n(&tmp, value, __ATOMIC_ACQUIRE);
        case rsl::v1::memory_order::release: return __atomic_exchange_n(&tmp, value, __ATOMIC_RELEASE);
        case rsl::v1::memory_order::acq_rel: return __atomic_exchange_n(&tmp, value, __ATOMIC_ACQ_REL);
        case rsl::v1::memory_order::seq_cst: return __atomic_exchange_n(&tmp, value, __ATOMIC_SEQ_CST);
        default: RSL_ASSERT("Invalid sucess memory order for operation"); break;
      }
    }
#endif
  } // namespace v1
} // namespace rsl