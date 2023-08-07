// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_cmpxchg_weak.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/atomic/atomic_casts.h"
#include "rex_std/bonus/atomic/atomic_compiler_barrier.h"
#include "rex_std/bonus/atomic/atomic_fixed_width_type.h"
#include "rex_std/bonus/atomic/atomic_memory_order.h"
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
    bool atomic_cmpxchg_weak(T* obj, T& expected, T desired, rsl::memory_order successOrder, rsl::memory_order failureOrder)
    {
      (void)successOrder;
      (void)failureOrder;

      atomic_t<T> atom_expected_value    = expected;
      atomic_t<T> atom_desired_value     = desired;
      volatile atomic_t<T>* volatile_obj = rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj);
      atomic_t<T> prev_value             = T {};

      if constexpr(sizeof(T) == 1)
      {
        prev_value = _InterlockedCompareExchange8(volatile_obj, atom_desired_value, atom_expected_value);
      }
      else if constexpr(sizeof(T) == 2)
      {
        prev_value = _InterlockedCompareExchange16_np(volatile_obj, atom_desired_value, atom_expected_value);
      }
      else if constexpr(sizeof(T) == 4)
      {
        prev_value = _InterlockedCompareExchange_np(volatile_obj, atom_desired_value, atom_expected_value);
      }
      else if constexpr(sizeof(T) == 8)
      {
        prev_value = _InterlockedCompareExchange64_np(volatile_obj, atom_desired_value, atom_expected_value);
      }
      else
      {
        static_assert(rsl::internal::always_false<T>, "Invalid type used for atomic add fetch");
        return false;
      }

      if(prev_value == expected)
      {
        return true;
      }

      expected = prev_value;
      return false;
    }
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
    template <typename T>
    bool atomic_cmpxchg_weak(T* obj, T expected, T desired, rsl::memory_order successOrder, rsl::memory_order failureOrder)
    {
      // GCC Documentation says:
      // These built-in functions perform the operation suggested by the name, and return the value that had previously been in *ptr.
      // Operations on pointer arguments are performed as if the operands were of the uintptr_t type.
      // That is, they are not scaled by the size of the type to which the pointer points.
      // { tmp = *ptr; *ptr op= val; return tmp; }
      // Therefore we save their value to a temporary of type uintptr first and perform the operation on that
      rsl::uintptr& tmp = *reinterpret_cast<rsl::uintptr*>(obj);

      int failure_order = -1;
      switch(failureOrder)
      {
        case rsl::v1::memory_order::relaxed: failure_order = __ATOMIC_RELAXED;
        case rsl::v1::memory_order::consume: failure_order = __ATOMIC_CONSUME;
        case rsl::v1::memory_order::acquire: failure_order = __ATOMIC_ACQUIRE;
        case rsl::v1::memory_order::release: failure_order = __ATOMIC_RELEASE;
        case rsl::v1::memory_order::acq_rel: failure_order = __ATOMIC_ACQ_REL;
        case rsl::v1::memory_order::seq_cst: failure_order = __ATOMIC_SEQ_CST;
        default: RSL_ASSERT("Invalid failure memory order for operation"); break;
      }

      switch(successOrder)
      {
        case rsl::v1::memory_order::relaxed: return __atomic_compare_exchange_n(obj, &expected, desired, true, __ATOMIC_RELAXED, failure_order);
        case rsl::v1::memory_order::consume: return __atomic_compare_exchange_n(obj, &expected, desired, true, __ATOMIC_CONSUME, failure_order);
        case rsl::v1::memory_order::acquire: return __atomic_compare_exchange_n(obj, &expected, desired, true, __ATOMIC_ACQUIRE, failure_order);
        case rsl::v1::memory_order::release: return __atomic_compare_exchange_n(obj, &expected, desired, true, __ATOMIC_RELEASE, failure_order);
        case rsl::v1::memory_order::acq_rel: return __atomic_compare_exchange_n(obj, &expected, desired, true, __ATOMIC_ACQ_REL, failure_order);
        case rsl::v1::memory_order::seq_cst: return __atomic_compare_exchange_n(obj, &expected, desired, true, __ATOMIC_SEQ_CST, failure_order);
        default: RSL_ASSERT("Invalid sucess memory order for operation"); break;
      }
    }
#endif
  } // namespace v1
} // namespace rsl
