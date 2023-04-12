// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

// NOLINTBEGIN(llvm-include-order)
// clang-format off

// the following includes need to be in this order or the code doesn't compiler
#include "rex_std/type_traits.h"
#include "rex_std/bonus/compiler.h"
#include "rex_std/bonus/utility/always_false.h"

#include "rex_std/bonus/atomic/atomic_add_fetch.h"
#include "rex_std/bonus/atomic/atomic_and_fetch.h"
#include "rex_std/bonus/atomic/atomic_cmpxchg_strong.h"
#include "rex_std/bonus/atomic/atomic_cmpxchg_weak.h"
#include "rex_std/bonus/atomic/atomic_compiler_barrier.h"
#include "rex_std/bonus/atomic/atomic_cpu_pause.h"
#include "rex_std/bonus/atomic/atomic_decrement.h"
#include "rex_std/bonus/atomic/atomic_exchange.h"
#include "rex_std/bonus/atomic/atomic_fetch_add.h"
#include "rex_std/bonus/atomic/atomic_fetch_and.h"
#include "rex_std/bonus/atomic/atomic_fetch_or.h"
#include "rex_std/bonus/atomic/atomic_fetch_sub.h"
#include "rex_std/bonus/atomic/atomic_fetch_xor.h"
#include "rex_std/bonus/atomic/atomic_increment.h"
#include "rex_std/bonus/atomic/atomic_load.h"
#include "rex_std/bonus/atomic/atomic_memory_barrier.h"
#include "rex_std/bonus/atomic/atomic_or_fetch.h"
#include "rex_std/bonus/atomic/atomic_read.h"
#include "rex_std/bonus/atomic/atomic_signal_fence.h"
#include "rex_std/bonus/atomic/atomic_store.h"
#include "rex_std/bonus/atomic/atomic_thread_fence.h"
#include "rex_std/bonus/atomic/atomic_xor_fetch.h"

#include "rex_std/bonus/atomic/atomic_casts.h"
#include "rex_std/bonus/atomic/atomic_memory_order.h"
#include "rex_std/bonus/atomic/atomic_asserts.h"
#include "rex_std/bonus/atomic/atomic_size_aligned.h"
#include "rex_std/bonus/atomic/atomic_base_width.h"
#include "rex_std/bonus/atomic/atomic_integral.h"
#include "rex_std/bonus/atomic/atomic_pointer.h"

// clang-format on
// NOLINTEND(llvm-include-order)

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      template <typename T>
      struct is_atomic_lockfree_size
      {
        static inline constexpr bool value = sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8 || sizeof(T) == 16;
      };

      template <typename T>
      inline constexpr bool is_atomic_lockfree_size_v = is_atomic_lockfree_size<T>::value;

      template <typename T>
      struct is_user_type_suitable_for_primary_template
      {
        static inline constexpr bool value = rsl::internal::is_atomic_lockfree_size_v<T>;
      };

      template <typename T>
      inline constexpr bool is_user_type_suitable_for_primary_template_v = is_user_type_suitable_for_primary_template<T>::value;

      template <typename T>
      using select_atomic_inherit_0 = typename rsl::conditional_t<rsl::is_same_v<bool, T> || rsl::internal::is_user_type_suitable_for_primary_template_v<T>, rsl::internal::atomic_base_width<T>, /* True */
                                                                  rsl::internal::atomic_invalid_type<T>>;                                                                                         /* False */

      template <typename T>
      using select_atomic_inherit = select_atomic_inherit_0<T>;

    } // namespace internal

    template <typename T, typename = void>
    class atomic : protected rsl::internal::select_atomic_inherit<T>
    {
      static_assert(!rsl::is_const_v<T>, "rsl::atomic<T> : template typename T cannot be const!");
      static_assert(!rsl::is_volatile_v<T>, "rsl::atomic<T> : template typename T cannot be volatile! Use the memory orders to access the underlying type for the guarantees you need.");
      static_assert(rsl::is_standard_layout_v<T>, "rsl::atomic<T> : Must have standard layout!");
      static_assert(rsl::is_trivially_copyable_v<T>, "rsl::atomic<T> : template typename T must be trivially copyable!");
      static_assert(rsl::is_copy_constructible_v<T>, "rsl::atomic<T> : template typename T must be copy constructible!");
      static_assert(rsl::is_move_constructible_v<T>, "rsl::atomic<T> : template typename T must be move constructible!");
      static_assert(rsl::is_copy_assignable_v<T>, "rsl::atomic<T> : template typename T must be copy assignable!");
      static_assert(rsl::is_move_assignable_v<T>, "rsl::atomic<T> : template typename T must be move assignable!");
      static_assert(rsl::is_trivially_destructible_v<T>, "rsl::atomic<T> : Must be trivially destructible!");
      static_assert(rsl::internal::is_atomic_lockfree_size_v<T>, "rsl::atomic<T> : template typename T must be a lockfree size!");

      using Base = rsl::internal::select_atomic_inherit<T>;

    public:
      using value_type      = T;
      using difference_type = T;

      static constexpr bool is_always_lock_free = rsl::internal::is_atomic_lockfree_size_v<T>;

      atomic(const atomic&)                     = delete;
      ~atomic()                                 = default;
      atomic& operator=(const atomic&)          = delete;
      atomic& operator=(const atomic&) volatile = delete;

      constexpr atomic() = default;
      constexpr atomic(T desired) // NOLINT(google-explicit-constructor)
          : Base(desired)
      {
      }

      bool is_lock_free() const
      {
        return rsl::internal::is_atomic_lockfree_size_v<T>;
      }
      bool is_lock_free() const volatile
      {
        static_assert(rsl::internal::always_false<T>, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in EASTL/atomic.h! Use the memory orders to access the atomic object!");
        return false;
      }

      using Base::operator=;
      using Base::compare_exchange_strong;
      using Base::compare_exchange_weak;
      using Base::exchange;
      using Base::load;
      using Base::store;

      explicit operator T() const volatile
      {
        static_assert(rsl::internal::always_false<T>, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in EASTL/atomic.h! Use the memory orders to access the atomic object!");
      }
      explicit operator T() const
      {
        return load(rsl::memory_order_seq_cst);
      }
    };

    template <typename T>
    class atomic<T, rsl::enable_if_t<rsl::is_integral_v<T> && !rsl::is_same_v<bool, T>>> : protected rsl::internal::atomic_integral_width<T>
    {
      static_assert(!rsl::is_const_v<T>, "rsl::atomic<T> : template typename T cannot be const!");
      static_assert(!rsl::is_volatile_v<T>, "rsl::atomic<T> : template typename T cannot be volatile! Use the memory orders to access the underlying type for the guarantees you need.");
      static_assert(rsl::is_standard_layout_v<T>, "rsl::atomic<T> : Must have standard layout!");
      static_assert(rsl::is_trivially_copyable_v<T>, "rsl::atomic<T> : template typename T must be trivially copyable!");
      static_assert(rsl::is_copy_constructible_v<T>, "rsl::atomic<T> : template typename T must be copy constructible!");
      static_assert(rsl::is_move_constructible_v<T>, "rsl::atomic<T> : template typename T must be move constructible!");
      static_assert(rsl::is_copy_assignable_v<T>, "rsl::atomic<T> : template typename T must be copy assignable!");
      static_assert(rsl::is_move_assignable_v<T>, "rsl::atomic<T> : template typename T must be move assignable!");
      static_assert(rsl::is_trivially_destructible_v<T>, "rsl::atomic<T> : Must be trivially destructible!");
      static_assert(rsl::internal::is_atomic_lockfree_size_v<T>, "rsl::atomic<T> : template typename T must be a lockfree size!");

    public:
      using Base = rsl::internal::atomic_integral_width<T>;

      using value_type      = T;
      using difference_type = T;

      static constexpr bool is_always_lock_free = rsl::internal::is_atomic_lockfree_size_v<T>;

      constexpr atomic() = default;
      constexpr atomic(T desired) // NOLINT(google-explicit-constructor)
          : Base(desired)
      {
      }

      atomic(const atomic&)                     = delete;
      ~atomic()                                 = default;
      atomic& operator=(const atomic&)          = delete;
      atomic& operator=(const atomic&) volatile = delete;

      bool is_lock_free() const
      {
        return rsl::internal::is_atomic_lockfree_size_v<T>;
      }
      bool is_lock_free() const volatile
      {
        static_assert(rsl::internal::always_false<T>, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in EASTL/atomic.h! Use the memory orders to access the atomic object!");
        return false;
      }

      using Base::operator=;
      using Base::compare_exchange_strong;
      using Base::compare_exchange_weak;
      using Base::exchange;
      using Base::load;
      using Base::store;

      operator T() const volatile // NOLINT(google-explicit-constructor)
      {
        static_assert(rsl::internal::always_false<T>, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in EASTL/atomic.h! Use the memory orders to access the atomic object!");
      }
      operator T() const // NOLINT(google-explicit-constructor)
      {
        return load(rsl::memory_order_seq_cst);
      }

      using Base::add_fetch;
      using Base::and_fetch;
      using Base::fetch_add;
      using Base::fetch_and;
      using Base::fetch_or;
      using Base::fetch_sub;
      using Base::fetch_xor;
      using Base::or_fetch;
      using Base::sub_fetch;
      using Base::xor_fetch;
      using Base::operator++;
      using Base::operator--;
      using Base::operator+=;
      using Base::operator-=;
      using Base::operator&=;
      using Base::operator|=;
      using Base::operator^=;
    };

    template <typename T>
    class atomic<T*> : protected rsl::internal::atomic_pointer_width<T*>
    {
      static_assert(!rsl::is_const_v<T*>, "rsl::atomic<T> : template typename T cannot be const!");
      static_assert(!rsl::is_volatile_v<T*>, "rsl::atomic<T> : template typename T cannot be volatile! Use the memory orders to access the underlying type for the guarantees you need.");
      static_assert(rsl::is_standard_layout_v<T*>, "rsl::atomic<T> : Must have standard layout!");
      static_assert(rsl::is_trivially_copyable_v<T*>, "rsl::atomic<T> : template typename T must be trivially copyable!");
      static_assert(rsl::is_copy_constructible_v<T*>, "rsl::atomic<T> : template typename T must be copy constructible!");
      static_assert(rsl::is_move_constructible_v<T*>, "rsl::atomic<T> : template typename T must be move constructible!");
      static_assert(rsl::is_copy_assignable_v<T*>, "rsl::atomic<T> : template typename T must be copy assignable!");
      static_assert(rsl::is_move_assignable_v<T*>, "rsl::atomic<T> : template typename T must be move assignable!");
      static_assert(rsl::is_trivially_destructible_v<T*>, "rsl::atomic<T> : Must be trivially destructible!");
      static_assert(rsl::internal::is_atomic_lockfree_size_v<T*>, "rsl::atomic<T> : template typename T must be a lockfree size!");

      using Base = rsl::internal::atomic_pointer_width<T*>;

    public:
      using value_type      = T*;
      using difference_type = ptrdiff_t;

      static constexpr bool is_always_lock_free = rsl::internal::is_atomic_lockfree_size_v<T*>;

      constexpr atomic() = default;
      constexpr atomic(T* desired) // NOLINT(google-explicit-constructor)
          : Base(desired)
      {
      }

      atomic(const atomic&)                     = delete;
      ~atomic()                                 = default;
      atomic& operator=(const atomic&)          = delete;
      atomic& operator=(const atomic&) volatile = delete;

      bool is_lock_free() const
      {
        return rsl::internal::is_atomic_lockfree_size_v<T*>;
      }
      bool is_lock_free() const volatile
      {
        static_assert(rsl::internal::always_false<T>, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in EASTL/atomic.h! Use the memory orders to access the atomic object!");
        ;
        return false;
      }

      using Base::operator=;
      using Base::compare_exchange_strong;
      using Base::compare_exchange_weak;
      using Base::exchange;
      using Base::load;
      using Base::store;

      operator T*() const volatile // NOLINT(google-explicit-constructor)
      {
        static_assert(rsl::internal::always_false<T>, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in EASTL/atomic.h! Use the memory orders to access the atomic object!");
      }
      operator T*() const // NOLINT(google-explicit-constructor)
      {
        return load(rsl::memory_order_seq_cst);
      }

      using Base::add_fetch;
      using Base::fetch_add;
      using Base::fetch_sub;
      using Base::sub_fetch;
      using Base::operator++;
      using Base::operator--;
      using Base::operator+=;
      using Base::operator-=;
    };

  } // namespace v1
} // namespace rsl
