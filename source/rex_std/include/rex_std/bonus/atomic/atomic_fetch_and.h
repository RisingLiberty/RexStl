// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_fetch_and.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/atomic/atomic_casts.h"
#include "rex_std/bonus/atomic/atomic_fixed_width_type.h"
#include "rex_std/bonus/atomic/atomic_memory_order.h"
#include "rex_std/bonus/atomic/atomic_xor_fetch.h"
#include "rex_std/bonus/types.h"

#if defined(REX_COMPILER_MSVC)
  #include <intrin.h>
#endif

namespace rsl
{
  inline namespace v1
  {
#if defined(REX_COMPILER_MSVC)
    template <typename T>
    REX_FORCE_INLINE atomic_t<T> atomic_fetch_and(T* obj, T valToAdd, rsl::memory_order order)
    {
      (void)order;
      atomic_t<T> atom_value_to_add      = valToAdd;
      volatile atomic_t<T>* volatile_obj = rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj);

      if constexpr(sizeof(T) == 1)
      {
        return _InterlockedAnd8_np(volatile_obj, atom_value_to_add);
      }
      else if constexpr(sizeof(T) == 2)
      {
        return _InterlockedAnd16_np(volatile_obj, atom_value_to_add);
      }
      else if constexpr(sizeof(T) == 4)
      {
        return _InterlockedAnd_np(volatile_obj, atom_value_to_add);
      }
      else if constexpr(sizeof(T) == 8)
      {
        return _InterlockedAnd64_np(volatile_obj, atom_value_to_add);
      }
      else
      {
        static_assert(rsl::internal::always_false<T>, "Invalid type used for atomic add fetch");
        return 0;
      }
    }
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
    template <typename T>
    REX_FORCE_INLINE atomic_t<T> atomic_fetch_and(T* obj, T valToAdd, rsl::memory_order order)
    {
      // GCC Documentation says:
      // These built-in functions perform the operation suggested by the name, and return the value that had previously been in *ptr.
      // Operations on pointer arguments are performed as if the operands were of the uintptr_t type.
      // That is, they are not scaled by the size of the type to which the pointer points.
      // { tmp = *ptr; *ptr op= val; return tmp; }
      // Therefore we save their value to a temporary of type uintptr first and perform the operation on that
      rsl::uintptr tmp = *obj;

      switch(order)
      {
        case rsl::v1::memory_order::relaxed: return __atomic_fetch_and(obj, valToAdd, __ATOMIC_RELAXED);
        case rsl::v1::memory_order::consume: return __atomic_fetch_and(obj, valToAdd, __ATOMIC_CONSUME);
        case rsl::v1::memory_order::acquire: return __atomic_fetch_and(obj, valToAdd, __ATOMIC_ACQUIRE);
        case rsl::v1::memory_order::release: return __atomic_fetch_and(obj, valToAdd, __ATOMIC_RELEASE);
        case rsl::v1::memory_order::acq_rel: return __atomic_fetch_and(obj, valToAdd, __ATOMIC_ACQ_REL);
        case rsl::v1::memory_order::seq_cst: return __atomic_fetch_and(obj, valToAdd, __ATOMIC_SEQ_CST);
        default: REX_ASSERT("Invalid memory order for operation"); break;
      }
    }
#endif
  } // namespace v1
} // namespace rsl
