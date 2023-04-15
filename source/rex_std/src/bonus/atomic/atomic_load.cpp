//// ============================================
////
//// REX - STANDARD LIBRARY IMPLEMENTATION
////
//// Author: Nick De Breuck
//// Twitter: @nick_debreuck
////
//// File: atomic_load.cpp
//// Copyright (c) Nick De Breuck 2022
////
//// ============================================
//
// #include "rex_std/bonus/atomic/atomic_casts.h"
// #include "rex_std/bonus/atomic/atomic_compiler_barrier.h"
// #include "rex_std/bonus/atomic/atomic_fixed_width_type.h"
// #include "rex_std/bonus/atomic/atomic_memory_order.h"
// #include "rex_std/bonus/atomic/atomic_xor_fetch.h"
//
// #include <intrin.h>
//
// namespace rsl
//{
//  inline namespace v1
//  {
// #if defined(REX_COMPILER_MSVC)
//    template <typename T>
//    atomic_t<T> atomic_load(T* obj)
//    {
//      volatile atomic_t<T>* volatile_obj = rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj);
//
//      if constexpr(sizeof(T) == 1)
//      {
//  #if(REX_COMPILER_VERSION >= 1920)
//        return __iso_volatile_load8(volatile_obj);
//  #else
//        return (*(rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj)));
//  #endif
//      }
//      else if constexpr(sizeof(T) == 2)
//      {
//  #if(REX_COMPILER_VERSION >= 1920)
//        return __iso_volatile_load16(volatile_obj);
//  #else
//        return (*(rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj)));
//  #endif
//      }
//      else if constexpr(sizeof(T) == 4)
//      {
//  #if(REX_COMPILER_VERSION >= 1920)
//        return __iso_volatile_load32(rsl::internal::atomic_volatile_integral_cast<int>(volatile_obj));
//  #else
//        return (*(rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj)));
//  #endif
//      }
//      else if constexpr(sizeof(T) == 8)
//      {
//  #if(REX_COMPILER_VERSION >= 1920)
//        return __iso_volatile_load64(volatile_obj);
//  #else
//        return (*(rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj)));
//  #endif
//      }
//      else
//      {
//        static_assert(rsl::internal::always_false<T>, "Invalid type used for atomic add fetch");
//        return 0;
//      }
//    }
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//    template <typename T>
//    atomic_t<T> atomic_load(T* obj, rsl::memory_order order)
//    {
//      // GCC Documentation says:
//      // These built-in functions perform the operation suggested by the name, and return the value that had previously been in *ptr.
//      // Operations on pointer arguments are performed as if the operands were of the uintptr_t type.
//      // That is, they are not scaled by the size of the type to which the pointer points.
//      // { tmp = *ptr; *ptr op= val; return tmp; }
//      // Therefore we save their value to a temporary of type uintptr first and perform the operation on that
//      rsl::uintptr const tmp = *obj; // NOLINT(bugprone-signed-char-misuse)
//
//      switch(order)
//      {
//        case rsl::v1::memory_order::consume: return __atomic_load_n(obj, __ATOMIC_CONSUME);
//        case rsl::v1::memory_order::acquire: return __atomic_load_n(obj, __ATOMIC_ACQUIRE);
//        case rsl::v1::memory_order::seq_cst: return __atomic_load_n(obj, __ATOMIC_SEQ_CST);
//        default: RSL_ASSERT("Invalid memory order for operation"); break;
//      }
//
//      return 0;
//    }
// #endif
//
//    // uint8
//    uint8 atomic_load_relaxed(uint8* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::relaxed);
// #endif
//    }
//    uint8 atomic_load_acquire(uint8* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::acquire);
// #endif
//    }
//    uint8 atomic_load_release(uint8* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::release);
// #endif
//    }
//    uint8 atomic_load_acq_rel(uint8* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::acq_rel);
// #endif
//    }
//    uint8 atomic_load_seq_cst(uint8* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::seq_cst);
// #endif
//    }
//
//    // int8
//    int8 atomic_load_relaxed(int8* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int8>(atomic_load(obj, rsl::memory_order::relaxed));
// #endif
//    }
//    int8 atomic_load_acquire(int8* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int8>(atomic_load(obj, rsl::memory_order::acquire));
// #endif
//    }
//    int8 atomic_load_release(int8* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int8>(atomic_load(obj, rsl::memory_order::release));
// #endif
//    }
//    int8 atomic_load_acq_rel(int8* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int8>(atomic_load(obj, rsl::memory_order::acq_rel));
// #endif
//    }
//    int8 atomic_load_seq_cst(int8* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int8>(atomic_load(obj, rsl::memory_order::seq_cst));
// #endif
//    }
//
//    // uint16
//    uint16 atomic_load_relaxed(uint16* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::relaxed);
// #endif
//    }
//    uint16 atomic_load_acquire(uint16* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::acquire);
// #endif
//    }
//    uint16 atomic_load_release(uint16* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::release);
// #endif
//    }
//    uint16 atomic_load_acq_rel(uint16* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::acq_rel);
// #endif
//    }
//    uint16 atomic_load_seq_cst(uint16* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::seq_cst);
// #endif
//    }
//
//    // int16
//    int16 atomic_load_relaxed(int16* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int16>(atomic_load(obj, rsl::memory_order::relaxed));
// #endif
//    }
//    int16 atomic_load_acquire(int16* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int16>(atomic_load(obj, rsl::memory_order::acquire));
// #endif
//    }
//    int16 atomic_load_release(int16* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int16>(atomic_load(obj, rsl::memory_order::release));
// #endif
//    }
//    int16 atomic_load_acq_rel(int16* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int16>(atomic_load(obj, rsl::memory_order::acq_rel));
// #endif
//    }
//    int16 atomic_load_seq_cst(int16* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int16>(atomic_load(obj, rsl::memory_order::seq_cst));
// #endif
//    }
//
//    // uint32
//    uint32 atomic_load_relaxed(uint32* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::relaxed);
// #endif
//    }
//    uint32 atomic_load_acquire(uint32* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::acquire);
// #endif
//    }
//    uint32 atomic_load_release(uint32* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::release);
// #endif
//    }
//    uint32 atomic_load_acq_rel(uint32* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GsCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::acq_rel);
// #endif
//    }
//    uint32 atomic_load_seq_cst(uint32* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::seq_cst);
// #endif
//    }
//
//    // int32
//    int32 atomic_load_relaxed(int32* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int32>(atomic_load(obj, rsl::memory_order::relaxed));
// #endif
//    }
//    int32 atomic_load_acquire(int32* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int32>(atomic_load(obj, rsl::memory_order::acquire));
// #endif
//    }
//    int32 atomic_load_release(int32* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int32>(atomic_load(obj, rsl::memory_order::release));
// #endif
//    }
//    int32 atomic_load_acq_rel(int32* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int32>(atomic_load(obj, rsl::memory_order::acq_rel));
// #endif
//    }
//    int32 atomic_load_seq_cst(int32* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int32>(atomic_load(obj, rsl::memory_order::seq_cst));
// #endif
//    }
//
//    // uint64
//    uint64 atomic_load_relaxed(uint64* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::relaxed);
// #endif
//    }
//    uint64 atomic_load_acquire(uint64* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::acquire);
// #endif
//    }
//    uint64 atomic_load_release(uint64* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::release);
// #endif
//    }
//    uint64 atomic_load_acq_rel(uint64* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::acq_rel);
// #endif
//    }
//    uint64 atomic_load_seq_cst(uint64* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return atomic_load(obj, rsl::memory_order::seq_cst);
// #endif
//    }
//
//    // int64
//    int64 atomic_load_relaxed(int64* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int64>(atomic_load(obj, rsl::memory_order::relaxed));
// #endif
//    }
//    int64 atomic_load_acquire(int64* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int64>(atomic_load(obj, rsl::memory_order::acquire));
// #endif
//    }
//    int64 atomic_load_release(int64* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int64>(atomic_load(obj, rsl::memory_order::release));
// #endif
//    }
//    int64 atomic_load_acq_rel(int64* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      return atomic_load(obj);
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int64>(atomic_load(obj, rsl::memory_order::acq_rel));
// #endif
//    }
//    int64 atomic_load_seq_cst(int64* obj)
//    {
// #if defined(REX_COMPILER_MSVC)
//      auto res = atomic_load(obj);
//      rsl::compiler_barrier();
//      return res;
// #elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
//      return static_cast<int64>(atomic_load(obj, rsl::memory_order::seq_cst));
// #endif
//    }
//  } // namespace v1
//} // namespace rsl