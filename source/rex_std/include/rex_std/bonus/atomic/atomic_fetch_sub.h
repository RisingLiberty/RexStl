// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Authsub: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_fetch_sub.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/atomic/atomic_casts.h"
#include "rex_std/bonus/atomic/atomic_compiler_barrier.h"
#include "rex_std/bonus/atomic/atomic_fixed_width_type.h"
#include "rex_std/bonus/types.h"

#if defined(RSL_COMPILER_MSVC)
  #include <intrin.h>
#endif

namespace rsl
{
  inline namespace v1
  {
#if defined(RSL_COMPILER_MSVC)
    template <typename T>
    atomic_t<T> atomic_fetch_sub(T* obj, T valToSub, rsl::memory_order order)
    {
      (void)order;
      T value_to_sub                     = internal::atomic_negate_operand(valToSub);
      atomic_t<T> atom_value_to_sub      = value_to_sub;
      volatile atomic_t<T>* volatile_obj = rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj);

      if constexpr(sizeof(T) == 1)
      {
        return _InterlockedExchangeAdd8(volatile_obj, atom_value_to_sub);
      }
      else if constexpr(sizeof(T) == 2)
      {
        return _InterlockedExchangeAdd16(volatile_obj, atom_value_to_sub);
      }
      else if constexpr(sizeof(T) == 4)
      {
        return _InterlockedExchangeAdd(volatile_obj, atom_value_to_sub);
      }
      else if constexpr(sizeof(T) == 8)
      {
        return _InterlockedExchangeAdd64(volatile_obj, atom_value_to_sub);
      }
      else
      {
        static_assert(rsl::internal::always_false<T>, "Invalid type used for atomic fetch or");
        return 0;
      }
    }
#elif defined(RSL_COMPILER_GCC) || defined(RSL_COMPILER_CLANG)
    template <typename T>
    atomic_t<T> atomic_fetch_sub(T* obj, T valToSub, rsl::memory_order order)
    {
      switch(order)
      {
        case rsl::v1::memory_order::relaxed: return __atomic_fetch_sub(obj, valToSub, __ATOMIC_RELAXED);
        case rsl::v1::memory_order::consume: return __atomic_fetch_sub(obj, valToSub, __ATOMIC_CONSUME);
        case rsl::v1::memory_order::acquire: return __atomic_fetch_sub(obj, valToSub, __ATOMIC_ACQUIRE);
        case rsl::v1::memory_order::release: return __atomic_fetch_sub(obj, valToSub, __ATOMIC_RELEASE);
        case rsl::v1::memory_order::acq_rel: return __atomic_fetch_sub(obj, valToSub, __ATOMIC_ACQ_REL);
        case rsl::v1::memory_order::seq_cst: return __atomic_fetch_sub(obj, valToSub, __ATOMIC_SEQ_CST);
        default: RSL_ASSERT("Invalid memory order for atomic fetch_sub"); break;
      }
    }
#endif
  } // namespace v1
} // namespace rsl
