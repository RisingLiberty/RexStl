// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: atomic_cmpxchg_weak.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/bonus/atomic/atomic_xor_fetch.h"
#include "rex_std/bonus/atomic/atomic_fixed_width_type.h"
#include "rex_std/bonus/atomic/atomic_memory_order.h"
#include "rex_std/bonus/atomic/atomic_casts.h"
#include <intrin.h>

namespace rsl
{
  inline namespace v1
  {
#if defined(REX_COMPILER_MSVC)
    template <typename T>
    atomic_t<T> atomic_cmpxchg_weak_msvc(T* obj, T expected, T desired)
    {
      atomic_t<T> atom_expected_value = expected;
      atomic_t<T> atom_desired_value = desired;
      volatile atomic_t<T>* volatile_obj = rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj);

      if constexpr (sizeof(T) == 1)
      {
        return _InterlockedCompareExchange8(volatile_obj, atom_expected_value, atom_desired_value);
      }
      else if constexpr (sizeof(T) == 2)
      {
        return _InterlockedCompareExchange16_np(volatile_obj, atom_expected_value, atom_desired_value);
      }
      else if constexpr (sizeof(T) == 4)
      {
        return _InterlockedCompareExchange_np(volatile_obj, atom_expected_value, atom_desired_value);
      }
      else if constexpr (sizeof(T) == 8)
      {
        return _InterlockedCompareExchange64_np(volatile_obj, atom_expected_value, atom_desired_value);
      }
      else
      {
        static_assert(rsl::internal::always_false<T>, "Invalid type used for atomic add fetch");
        return 0;
      }
    }
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
    template <typename T>
    atomic_t<T> atomic_cmpxchg_weak_clang(T* obj, T expected, T desired, rsl::memory_order successOrder, rsl::memory_order failureOrder)
    {
      // GCC Documentation says:
      // These built-in functions perform the operation suggested by the name, and return the value that had previously been in *ptr. 
      // Operations on pointer arguments are performed as if the operands were of the uintptr_t type. 
      // That is, they are not scaled by the size of the type to which the pointer points.
      // { tmp = *ptr; *ptr op= val; return tmp; }
      // Therefore we save their value to a temporary of type uintptr first and perform the operation on that
      rsl::uintptr tmp = *obj;

      int failure_order = -1;
      switch (failureOrder)
      {
      case rsl::v1::memory_order::relaxed: failure_order = __ATOMIC_RELAXED;
      case rsl::v1::memory_order::consume: failure_order = __ATOMIC_CONSUME;
      case rsl::v1::memory_order::acquire: failure_order = __ATOMIC_ACQUIRE;
      case rsl::v1::memory_order::release: failure_order = __ATOMIC_RELEASE;
      case rsl::v1::memory_order::acq_rel: failure_order = __ATOMIC_ACQ_REL;
      case rsl::v1::memory_order::seq_cst: failure_order = __ATOMIC_SEQ_CST;
      default:
        REX_ASSERT("Invalid failure memory order for operation");
        break;
      }

      switch (successOrder)
      {
      case rsl::v1::memory_order::relaxed: return __atomic_compare_exchange(obj, expected, desired, true, __ATOMIC_RELAXED, failureOrder);
      case rsl::v1::memory_order::consume: return __atomic_compare_exchange(obj, expected, desired, true, __ATOMIC_CONSUME, failureOrder);
      case rsl::v1::memory_order::acquire: return __atomic_compare_exchange(obj, expected, desired, true, __ATOMIC_ACQUIRE, failureOrder);
      case rsl::v1::memory_order::release: return __atomic_compare_exchange(obj, expected, desired, true, __ATOMIC_RELEASE, failureOrder);
      case rsl::v1::memory_order::acq_rel: return __atomic_compare_exchange(obj, expected, desired, true, __ATOMIC_ACQ_REL, failureOrder);
      case rsl::v1::memory_order::seq_cst: return __atomic_compare_exchange(obj, expected, desired, true, __ATOMIC_SEQ_CST, failureOrder);
      default:
        REX_ASSERT("Invalid sucess memory order for operation");
        break;
      }
    }
#endif

    // uint8
    uint8 atomic_cmpxchg_weak_relaxed(uint8* obj, uint8 expected, uint8 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::relaxed, failureOrder);
#endif
    }
    uint8 atomic_cmpxchg_weak_acquire(uint8* obj, uint8 expected, uint8 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acquire, failureOrder);
#endif
    }
    uint8 atomic_cmpxchg_weak_release(uint8* obj, uint8 expected, uint8 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::release, failureOrder);
#endif
    }
    uint8 atomic_cmpxchg_weak_acq_rel(uint8* obj, uint8 expected, uint8 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acq_rel, failureOrder);
#endif
  }
    uint8 atomic_cmpxchg_weak_seq_cst(uint8* obj, uint8 expected, uint8 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::seq_cst, failureOrder);
#endif
}

    // int8
    int8 atomic_cmpxchg_weak_relaxed(int8* obj, int8 expected, int8 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::relaxed, failureOrder);
#endif
    }
    int8 atomic_cmpxchg_weak_acquire(int8* obj, int8 expected, int8 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acquire, failureOrder);
#endif
    }
    int8 atomic_cmpxchg_weak_release(int8* obj, int8 expected, int8 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::release, failureOrder);
#endif
    }
    int8 atomic_cmpxchg_weak_acq_rel(int8* obj, int8 expected, int8 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acq_rel, failureOrder);
#endif
    }
    int8 atomic_cmpxchg_weak_seq_cst(int8* obj, int8 expected, int8 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::seq_cst, failureOrder);
#endif
    }

    // uint16
    uint16 atomic_cmpxchg_weak_relaxed(uint16* obj, uint16 expected, uint16 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::relaxed, failureOrder);
#endif
    }
    uint16 atomic_cmpxchg_weak_acquire(uint16* obj, uint16 expected, uint16 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acquire, failureOrder);
#endif
    }
    uint16 atomic_cmpxchg_weak_release(uint16* obj, uint16 expected, uint16 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::release, failureOrder);
#endif
    }
    uint16 atomic_cmpxchg_weak_acq_rel(uint16* obj, uint16 expected, uint16 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acq_rel, failureOrder);
#endif
    }
    uint16 atomic_cmpxchg_weak_seq_cst(uint16* obj, uint16 expected, uint16 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::seq_cst, failureOrder);
#endif
    }

    // int16
    int16 atomic_cmpxchg_weak_relaxed(int16* obj, int16 expected, int16 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::relaxed, failureOrder);
#endif
    }
    int16 atomic_cmpxchg_weak_acquire(int16* obj, int16 expected, int16 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acquire, failureOrder);
#endif
    }
    int16 atomic_cmpxchg_weak_release(int16* obj, int16 expected, int16 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::release, failureOrder);
#endif
    }
    int16 atomic_cmpxchg_weak_acq_rel(int16* obj, int16 expected, int16 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acq_rel, failureOrder);
#endif
    }
    int16 atomic_cmpxchg_weak_seq_cst(int16* obj, int16 expected, int16 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::seq_cst, failureOrder);
#endif
    }

    // uint32
    uint32 atomic_cmpxchg_weak_relaxed(uint32* obj, uint32 expected, uint32 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::relaxed, failureOrder);
#endif
    }
    uint32 atomic_cmpxchg_weak_acquire(uint32* obj, uint32 expected, uint32 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acquire, failureOrder);
#endif
    }
    uint32 atomic_cmpxchg_weak_release(uint32* obj, uint32 expected, uint32 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::release, failureOrder);
#endif
    }
    uint32 atomic_cmpxchg_weak_acq_rel(uint32* obj, uint32 expected, uint32 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acq_rel, failureOrder);
#endif
    }
    uint32 atomic_cmpxchg_weak_seq_cst(uint32* obj, uint32 expected, uint32 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::seq_cst, failureOrder);
#endif
    }

    // int32
    int32 atomic_cmpxchg_weak_relaxed(int32* obj, int32 expected, int32 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::relaxed, failureOrder);
#endif
    }
    int32 atomic_cmpxchg_weak_acquire(int32* obj, int32 expected, int32 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acquire, failureOrder);
#endif
    }
    int32 atomic_cmpxchg_weak_release(int32* obj, int32 expected, int32 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::release, failureOrder);
#endif
    }
    int32 atomic_cmpxchg_weak_acq_rel(int32* obj, int32 expected, int32 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acq_rel, failureOrder);
#endif
    }
    int32 atomic_cmpxchg_weak_seq_cst(int32* obj, int32 expected, int32 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::seq_cst, failureOrder);
#endif
    }

    // uint64
    uint64 atomic_cmpxchg_weak_relaxed(uint64* obj, uint64 expected, uint64 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::relaxed, failureOrder);
#endif
    }
    uint64 atomic_cmpxchg_weak_acquire(uint64* obj, uint64 expected, uint64 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acquire, failureOrder);
#endif
    }
    uint64 atomic_cmpxchg_weak_release(uint64* obj, uint64 expected, uint64 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::release, failureOrder);
#endif
    }
    uint64 atomic_cmpxchg_weak_acq_rel(uint64* obj, uint64 expected, uint64 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acq_rel, failureOrder);
#endif
    }
    uint64 atomic_cmpxchg_weak_seq_cst(uint64* obj, uint64 expected, uint64 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::seq_cst, failureOrder);
#endif
    }

    // int64
    int64 atomic_cmpxchg_weak_relaxed(int64* obj, int64 expected, int64 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::relaxed, failureOrder);
#endif
    }
    int64 atomic_cmpxchg_weak_acquire(int64* obj, int64 expected, int64 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acquire, failureOrder);
#endif
    }
    int64 atomic_cmpxchg_weak_release(int64* obj, int64 expected, int64 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::release, failureOrder);
#endif
    }
    int64 atomic_cmpxchg_weak_acq_rel(int64* obj, int64 expected, int64 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::acq_rel, failureOrder);
#endif
    }
    int64 atomic_cmpxchg_weak_seq_cst(int64* obj, int64 expected, int64 desired, rsl::memory_order failureOrder)
    {
#if defined(REX_COMPILER_MSVC)
      (void)failureOrder;
      return atomic_cmpxchg_weak_msvc(obj, expected, desired);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_cmpxchg_weak_clang(obj, expected, desired, rsl::memory_order::seq_cst, failureOrder);
#endif
    }
    }
    }