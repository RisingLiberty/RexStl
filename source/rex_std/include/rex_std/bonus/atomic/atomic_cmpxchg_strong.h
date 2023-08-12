// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_cmpxchg_strong.h
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
    namespace internal
    {
      template <typename T>
      auto interlocked_exchange(volatile atomic8_t* volatileObject, atomic_t<T> desiredValue, atomic_t<T> expectedValue)
      {
        return _InterlockedCompareExchange8(volatileObject, desiredValue, expectedValue);
      }
      template <typename T>
      auto interlocked_exchange(volatile atomic16_t* volatileObject, atomic_t<T> desiredValue, atomic_t<T> expectedValue)
      {
        return _InterlockedCompareExchange16_np(volatileObject, desiredValue, expectedValue);
      }
      template <typename T>
      auto interlocked_exchange(volatile atomic32_t* volatileObject, atomic_t<T> desiredValue, atomic_t<T> expectedValue)
      {
        return _InterlockedCompareExchange_np(volatileObject, desiredValue, expectedValue);
      }
      template <typename T>
      auto interlocked_exchange(volatile atomic64_t* volatileObject, atomic_t<T> desiredValue, atomic_t<T> expectedValue)
      {
        return _InterlockedCompareExchange64_np(volatileObject, desiredValue, expectedValue);
      }
    } // namespace internal

#if defined(REX_COMPILER_MSVC)
    template <typename T>
    bool atomic_cmpxchg_strong(T* obj, T& expected, T desired, rsl::memory_order successOrder, rsl::memory_order failureOrder)
    {
      (void)successOrder;
      (void)failureOrder;

      const atomic_t<T> atom_expected_value = *rsl::internal::atomic_integral_cast<const atomic_t<T>>(&expected);
      const atomic_t<T> atom_desired_value  = *rsl::internal::atomic_integral_cast<const atomic_t<T>>(&desired);
      volatile atomic_t<T>* volatile_obj    = rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj);

      atomic_t<T> prev_value = internal::interlocked_exchange<T>(volatile_obj, atom_desired_value, atom_expected_value);

      if(prev_value == expected)
      {
        return true;
      }

      expected = prev_value;
      return false;
    }
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
    template <typename T>
    bool atomic_cmpxchg_strong(T* obj, T& expected, T desired, rsl::memory_order successOrder, rsl::memory_order failureOrder)
    {
      int failure_order = -1;
      switch(failureOrder)
      {
        case rsl::v1::memory_order::relaxed: failure_order = __ATOMIC_RELAXED; break;
        case rsl::v1::memory_order::consume: failure_order = __ATOMIC_CONSUME; break;
        case rsl::v1::memory_order::acquire: failure_order = __ATOMIC_ACQUIRE; break;
        case rsl::v1::memory_order::release: failure_order = __ATOMIC_RELEASE; break;
        case rsl::v1::memory_order::acq_rel: failure_order = __ATOMIC_ACQ_REL; break;
        case rsl::v1::memory_order::seq_cst: failure_order = __ATOMIC_SEQ_CST; break;
        default: RSL_ASSERT("Invalid failure memory order for operation"); break;
      }

      switch(successOrder)
      {
        case rsl::v1::memory_order::relaxed: return __atomic_compare_exchange_n(obj, &expected, desired, false, __ATOMIC_RELAXED, failure_order);
        case rsl::v1::memory_order::consume: return __atomic_compare_exchange_n(obj, &expected, desired, false, __ATOMIC_CONSUME, failure_order);
        case rsl::v1::memory_order::acquire: return __atomic_compare_exchange_n(obj, &expected, desired, false, __ATOMIC_ACQUIRE, failure_order);
        case rsl::v1::memory_order::release: return __atomic_compare_exchange_n(obj, &expected, desired, false, __ATOMIC_RELEASE, failure_order);
        case rsl::v1::memory_order::acq_rel: return __atomic_compare_exchange_n(obj, &expected, desired, false, __ATOMIC_ACQ_REL, failure_order);
        case rsl::v1::memory_order::seq_cst: return __atomic_compare_exchange_n(obj, &expected, desired, false, __ATOMIC_SEQ_CST, failure_order);
        default: RSL_ASSERT("Invalid sucess memory order for operation"); break;
      }
    }
#endif
  } // namespace v1
} // namespace rsl
