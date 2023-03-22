// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/atomic/atomic.h"
#include "rex_std/internal/atomic/atomic_standalone.h"
#include "rex_std/internal/atomic/atomic_flag.h"
#include "rex_std/internal/atomic/atomic_flag_standalone.h"

//#define REX_ENABLE_STD_ALIAS
//#include "rex_std/disable_std_checking.h"
//#include "rex_std/std_alias_defines.h"
//
//#include "rex_std/internal/type_traits/is_trivially_copyable.h"
//#include "rex_std/internal/type_traits/is_copy_constructible.h"
//#include "rex_std/internal/type_traits/is_move_constructible.h"
//#include "rex_std/internal/type_traits/is_copy_assignable.h"
//#include "rex_std/internal/type_traits/is_move_assignable.h"
//#include "rex_std/internal/type_traits/is_floating_point.h"
//#include "rex_std/internal/type_traits/is_integral.h"
//#include "rex_std/internal/type_traits/is_same.h"
//
//#include "rex_std/bonus/type_traits/type_select.h"
//
//#include "rex_std/internal/assert/assert_fwd.h"
//
//namespace rsl
//{
//  inline namespace v1
//  {
//    namespace internal
//    {
//      enum class memory_order
//      {
//        relaxed,
//        consume,
//        acquire,
//        release,
//        acq_rel,
//        seq_cst
//      };
//
//      // checks if the order provided fits the operation about to be performed
//      // returns true if valid, returs false if not
//      bool check_load_memory_order(memory_order order);
//      bool check_store_memory_order(memory_order order);
//      bool check_exchange_memory_order(memory_order order);
//
//      using atomic_spinlock_t = void**;
//
//      // lock and unlock functions for a mutex
//      void atomic_lock_acquire(atomic_spinlock_t mutex);
//      void atomic_lock_release(atomic_spinlock_t mutex);
//
//      class atomic_lock_guard
//      {
//      public:
//        explicit atomic_lock_guard(atomic_spinlock_t& spinlock)
//          : m_mtx(spinlock)
//        {
//          atomic_lock_acquire(spinlock);
//        }
//
//        atomic_lock_guard(const atomic_lock_guard&) = delete;
//        atomic_lock_guard(atomic_lock_guard&&) = delete;
//
//        ~atomic_lock_guard()
//        {
//          atomic_lock_release(m_mtx);
//        }
//
//        atomic_lock_guard& operator=(const atomic_lock_guard&) = delete;
//        atomic_lock_guard& operator=(atomic_lock_guard&&) = delete;
//
//      private:
//        atomic_spinlock_t& m_mtx;
//      };
//
//      template <typename T, size_t /* = sizeof(T) */>
//      class atomic_storage
//      {
//      public:
//        atomic_storage() = default;
//        atomic_storage(T val)
//          : m_value(val)
//        {}
//
//        void store(T val, memory_order order = memory_order::seq_cst)
//        {
//          REX_ASSERT_X(check_store_memory_order(order), "invalid store memory order");
//          atomic_lock_guard lock(m_mtx);
//          m_value = val;
//        }
//
//        T load(const memory_order order = memory_order::seq_cst)
//        {
//          REX_ASSERT_X(check_load_memory_order(order), "invalid load memory order");
//          atomic_lock_guard lock(m_mtx);
//          return m_value;
//        }
//
//        T exchange(const T val, const memory_order order = memory_order::seq_cst)
//        {
//          REX_ASSERT_X(check_exchange_memory_order(order), "invalid exchange memory order");
//          atomic_lock_guard lock(m_mtx);
//          T val = m_value;
//          m_value = val;
//          return val;
//        }
//
//        bool compare_exchange_strong(T& expected, T desired, memory_order order = memory_order::seq_cst)
//        {
//          REX_ASSERT_X(check_exchange_memory_order(order), "invalid exchange memory order");
//          const auto value_ptr = rsl::addressof(m_value);
//          const auto expected_ptr = rsl::addressof(expected);
//
//          atomic_lock_guard lock(m_mtx);
//          bool result = rsl::memcmp(value_ptr, expected_ptr, sizeof(T)) == 0;
//          if (result)
//          {
//            rsl::memcpy(value_ptr, rsl::addressof(desired), sizeof(T));
//          }
//          else
//          {
//            rsl::memcpy(expected_ptr, value_ptr, sizeof(T));
//          }
//
//          return result;
//        }
//
//        void wait(T expected, memory_order = memory_order::seq_cst) const
//        {
//          const auto value_ptr = rsl::addressof(value);
//          const auto expected_ptr = rsl::addressof(expected);
//          for (;;)
//          {
//            {
//              atomic_lock_guard lock(m_mtx);
//              if (rsl::memcmp(value_ptr, expected_ptr, sizeof(T)) != 0)
//              {
//                return;
//              }
//
//
//            }
//          }
//
//
//        }
//
//      private:
//        /// [22/Mar/2023] RSL TODO: check if a semaphore is faster, they bypass the scheduler on Windows, this could result in better performance
//        mutable atomic_spinlock_t m_mtx{};
//        T m_value{};
//      };
//
//      template <typename T>
//      class atomic_floating
//      {};
//
//      template <typename T>
//      class atomic_integral
//      {};
//
//      template <typename T>
//      class atomic_pointer
//      {};
//    }
//
//    template <typename T>
//    class atomic : public
//      type_select_t<is_floating_point_v<T>, internal::atomic_floating<T>, // T == floating point
//      type_select_t<is_integral_v<T> && !is_same_v<T, bool>, internal::atomic_integral<T>, // T == integral, but no bool
//      type_select_t<is_pointer_v<T>&& is_object_v<remove_pointer_t<T>>, internal::atomic_pointer, // T == pointer to object
//      internal::atomic_storage<T>>>>
//    {
//      static_assert(is_trivially_copyable_v<T>&& is_copy_constructible_v<T>&& is_move_constructible_v<T>&& is_copy_assignable_v<T>&& is_move_assignable_v<T>,
//        "an atomic should be trivially copyable, copy constructible, move constructible, copy assignable and move assignable");
//
//    public:
//      atomic() = default;
//      atomic(const atomic&) = delete;
//      atomic(atomic&&) = delete;
//      ~atomic() = default;
//
//      atomic& operator=(const atomic&) = delete;
//      atomic& operator=(atomic&&) = delete;
//
//      T operator=(T value)
//      {
//        store(value);
//      }
//
//      bool is_lock_free() const
//      {
//        return sizeof(T) <= 8 && sizeof(T) & sizeof(T) - 1) == 0;
//      }
//
//      void store(T value)
//      {
//
//      }
//      void store(T value, memory_order order)
//      {
//
//      }
//
//      T load() const
//      {
//
//      }
//      T load(const memory_order order)
//      {
//
//      }
//
//      T exchange(T value)
//      {
//
//      }
//      T exchange(T value, memory_order order)
//      {
//
//      }
//
//      bool compare_exchange_strong(T& expected, T desired)
//      {
//
//      }
//      bool compare_exchange_strong(T& expected, T desired, memory_order order)
//      {
//
//      }
//      bool compare_exchange_strong(T& expected, T desired, memory_order success, memory_order failure)
//      {
//
//      }
//      bool compare_exchange_strong(T& expected, T desired, memory_order success, memory_order failure)
//      {
//
//      }
//
//      bool compare_exchange_weak(T& expected, T desired)
//      {
//
//      }
//      bool compare_exchange_weak(T& expected, T desired, memory_order order)
//      {
//
//      }
//      bool compare_exchange_weak(T& expected, T desired, memory_order success, memory_order failure)
//      {
//
//      }
//      bool compare_exchange_weak(T& expected, T desired, memory_order success, memory_order failure)
//      {
//
//      }
//
//      void wait(T expected, const memory_order order = memory_order::seq_cst)
//      {
//
//      }
//      void notify_one()
//      {
//
//      }
//      void notify_all()
//      {
//
//      }
//
//      operator T() const
//      {
//
//      }
//
//    private:
//
//    };
//
//    template <typename T>
//    atomic(T)->atomic<T>;
//
//  }
//}
//
//namespace rsl
//{
//  inline namespace v1
//  {
//
//
//    //    REX_STD_TEMPLATED_CLASS_ALIAS(template <typename T>, atomic, T);
//    //
//    //    REX_STD_TEMPLATED_CLASS_ALIAS(template <typename T>, atomic, T);
//    //
//    //    REX_STD_CLASS_ALIAS(atomic_flag);
//    //    REX_STD_CLASS_ALIAS(memory_order);
//    //
//    //    REX_STD_CLASS_ALIAS(atomic_bool);
//    //    REX_STD_CLASS_ALIAS(atomic_char);
//    //    REX_STD_CLASS_ALIAS(atomic_schar);
//    //    REX_STD_CLASS_ALIAS(atomic_uchar);
//    //    REX_STD_CLASS_ALIAS(atomic_short);
//    //    REX_STD_CLASS_ALIAS(atomic_ushort);
//    //    REX_STD_CLASS_ALIAS(atomic_int);
//    //    REX_STD_CLASS_ALIAS(atomic_uint);
//    //    REX_STD_CLASS_ALIAS(atomic_long);
//    //    REX_STD_CLASS_ALIAS(atomic_ulong);
//    //    REX_STD_CLASS_ALIAS(atomic_llong);
//    //    REX_STD_CLASS_ALIAS(atomic_ullong);
//    //    REX_STD_CLASS_ALIAS(atomic_char8_t);
//    //    REX_STD_CLASS_ALIAS(atomic_char16_t);
//    //    REX_STD_CLASS_ALIAS(atomic_char32_t);
//    //    REX_STD_CLASS_ALIAS(atomic_wchar_t);
//    //    REX_STD_CLASS_ALIAS(atomic_int8_t);
//    //    REX_STD_CLASS_ALIAS(atomic_uint8_t);
//    //    REX_STD_CLASS_ALIAS(atomic_int16_t);
//    //    REX_STD_CLASS_ALIAS(atomic_uint16_t);
//    //    REX_STD_CLASS_ALIAS(atomic_int32_t);
//    //    REX_STD_CLASS_ALIAS(atomic_uint32_t);
//    //    REX_STD_CLASS_ALIAS(atomic_int64_t);
//    //    REX_STD_CLASS_ALIAS(atomic_uint64_t);
//    //    REX_STD_CLASS_ALIAS(atomic_int_least8_t);
//    //    REX_STD_CLASS_ALIAS(atomic_uint_least8_t);
//    //    REX_STD_CLASS_ALIAS(atomic_int_least16_t);
//    //    REX_STD_CLASS_ALIAS(atomic_uint_least16_t);
//    //    REX_STD_CLASS_ALIAS(atomic_int_least32_t);
//    //    REX_STD_CLASS_ALIAS(atomic_uint_least32_t);
//    //    REX_STD_CLASS_ALIAS(atomic_int_least64_t);
//    //    REX_STD_CLASS_ALIAS(atomic_uint_least64_t);
//    //    REX_STD_CLASS_ALIAS(atomic_int_fast8_t);
//    //    REX_STD_CLASS_ALIAS(atomic_uint_fast8_t);
//    //    REX_STD_CLASS_ALIAS(atomic_int_fast16_t);
//    //    REX_STD_CLASS_ALIAS(atomic_uint_fast16_t);
//    //    REX_STD_CLASS_ALIAS(atomic_int_fast32_t);
//    //    REX_STD_CLASS_ALIAS(atomic_uint_fast32_t);
//    //    REX_STD_CLASS_ALIAS(atomic_int_fast64_t);
//    //    REX_STD_CLASS_ALIAS(atomic_uint_fast64_t);
//    //    REX_STD_CLASS_ALIAS(atomic_intptr_t);
//    //    REX_STD_CLASS_ALIAS(atomic_uintptr_t);
//    //    REX_STD_CLASS_ALIAS(atomic_size_t);
//    //    REX_STD_CLASS_ALIAS(atomic_ptrdiff_t);
//    //    REX_STD_CLASS_ALIAS(atomic_intmax_t);
//    //    REX_STD_CLASS_ALIAS(atomic_uintmax_t);
//    //
//    //#ifdef REX_ENABLE_WITH_CPP20
//    //    REX_STD_CLASS_ALIAS(atomic_signed_lock_free);
//    //    REX_STD_CLASS_ALIAS(atomic_unsigned_lock_free);
//    //#endif // REX_ENABLE_WITH_CPP20
//    //
//    //    REX_STD_FUNC_ALIAS(atomic_is_lock_free);
//    //    REX_STD_FUNC_ALIAS(atomic_store);
//    //    REX_STD_FUNC_ALIAS(atomic_store_explicit);
//    //    REX_STD_FUNC_ALIAS(atomic_exchange);
//    //    REX_STD_FUNC_ALIAS(atomic_exchange_explicit);
//    //    REX_STD_FUNC_ALIAS(atomic_compare_exchange_weak);
//    //    REX_STD_FUNC_ALIAS(atomic_compare_exchange_weak_explicit);
//    //    REX_STD_FUNC_ALIAS(atomic_compare_exchange_strong);
//    //    REX_STD_FUNC_ALIAS(atomic_compare_exchange_strong_explicit);
//    //    REX_STD_FUNC_ALIAS(atomic_fetch_add);
//    //    REX_STD_FUNC_ALIAS(atomic_fetch_add_explicit);
//    //    REX_STD_FUNC_ALIAS(atomic_fetch_sub);
//    //    REX_STD_FUNC_ALIAS(atomic_fetch_sub_explicit);
//    //    REX_STD_FUNC_ALIAS(atomic_fetch_and);
//    //    REX_STD_FUNC_ALIAS(atomic_fetch_and_explicit);
//    //    REX_STD_FUNC_ALIAS(atomic_fetch_or);
//    //    REX_STD_FUNC_ALIAS(atomic_fetch_or_explicit);
//    //    REX_STD_FUNC_ALIAS(atomic_fetch_xor);
//    //    REX_STD_FUNC_ALIAS(atomic_fetch_xor_explicit);
//    //    REX_STD_FUNC_ALIAS(atomic_wait);
//    //    REX_STD_FUNC_ALIAS(atomic_wait_explicit);
//    //    REX_STD_FUNC_ALIAS(atomic_notify_one);
//    //    REX_STD_FUNC_ALIAS(atomic_notify_all);
//    //    REX_STD_FUNC_ALIAS(atomic_flag_test);
//    //    REX_STD_FUNC_ALIAS(atomic_flag_test_explicit);
//    //    REX_STD_FUNC_ALIAS(atomic_flag_test_and_set);
//    //    REX_STD_FUNC_ALIAS(atomic_flag_test_and_set_explicit);
//    //    REX_STD_FUNC_ALIAS(atomic_flag_clear);
//    //    REX_STD_FUNC_ALIAS(atomic_flag_clear_explicit);
//    //    REX_STD_FUNC_ALIAS(atomic_flag_wait);
//    //    REX_STD_FUNC_ALIAS(atomic_flag_wait_explicit);
//    //    REX_STD_FUNC_ALIAS(atomic_flag_notify_one);
//    //    REX_STD_FUNC_ALIAS(atomic_flag_notify_all);
//    //    REX_STD_FUNC_ALIAS(atomic_init);
//    //    REX_STD_FUNC_ALIAS(kill_dependency);
//    //    REX_STD_FUNC_ALIAS(atomic_thread_fence);
//    //    REX_STD_FUNC_ALIAS(atomic_signal_fence);
//
//  } // namespace v1
//} // namespace rsl
//
//#include "rex_std/enable_std_checking.h"
//
//#include "rex_std/internal/assert/assert_impl.h"
