

#ifndef REX_ATOMIC_INTERNA_ATOMIC_FLAG_H
#define REX_ATOMIC_INTERNA_ATOMIC_FLAG_H

#pragma once

#include "rex_std/atomic.h"

namespace rsl
{

  class atomic_flag
  {
  public: /* ctors */
    constexpr atomic_flag(bool desired)
        : mFlag {desired}
    {
    }

    constexpr atomic_flag()
        : mFlag {false}
    {
    }

  public: /* deleted ctors && assignment operators */
    atomic_flag(const atomic_flag&) = delete;

    atomic_flag& operator=(const atomic_flag&)          = delete;
    atomic_flag& operator=(const atomic_flag&) volatile = delete;

  public: /* clear */
    template <typename Order>
    void clear(Order /*order*/) volatile
    {
      REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(Order);
    }

    template <typename Order>
    void clear(Order /*order*/)
    {
      REX_ATOMIC_STATIC_ASSERT_INVALID_MEMORY_ORDER(Order);
    }

    void clear(rsl::internal::memory_order_relaxed_s)
    {
      mFlag.store(false, rsl::memory_order_relaxed);
    }

    void clear(rsl::internal::memory_order_release_s)
    {
      mFlag.store(false, rsl::memory_order_release);
    }

    void clear(rsl::internal::memory_order_seq_cst_s)
    {
      mFlag.store(false, rsl::memory_order_seq_cst);
    }

    void clear()
    {
      mFlag.store(false, rsl::memory_order_seq_cst);
    }

  public: /* test_and_set */
    template <typename Order>
    bool test_and_set(Order /*order*/) volatile
    {
      REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(Order);
      return false;
    }

    template <typename Order>
    bool test_and_set(Order /*order*/)
    {
      REX_ATOMIC_STATIC_ASSERT_INVALID_MEMORY_ORDER(Order);
      return false;
    }

    bool test_and_set(rsl::internal::memory_order_relaxed_s)
    {
      return mFlag.exchange(true, rsl::memory_order_relaxed);
    }

    bool test_and_set(rsl::internal::memory_order_acquire_s)
    {
      return mFlag.exchange(true, rsl::memory_order_acquire);
    }

    bool test_and_set(rsl::internal::memory_order_release_s)
    {
      return mFlag.exchange(true, rsl::memory_order_release);
    }

    bool test_and_set(rsl::internal::memory_order_acq_rel_s)
    {
      return mFlag.exchange(true, rsl::memory_order_acq_rel);
    }

    bool test_and_set(rsl::internal::memory_order_seq_cst_s)
    {
      return mFlag.exchange(true, rsl::memory_order_seq_cst);
    }

    bool test_and_set()
    {
      return mFlag.exchange(true, rsl::memory_order_seq_cst);
    }

  public: /* test */
    template <typename Order>
    bool test(Order /*order*/) const volatile
    {
      REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(Order);
      return false;
    }

    template <typename Order>
    bool test(Order /*order*/) const
    {
      REX_ATOMIC_STATIC_ASSERT_INVALID_MEMORY_ORDER(Order);
      return false;
    }

    bool test(rsl::internal::memory_order_relaxed_s) const
    {
      return mFlag.load(rsl::memory_order_relaxed);
    }

    bool test(rsl::internal::memory_order_acquire_s) const
    {
      return mFlag.load(rsl::memory_order_acquire);
    }

    bool test(rsl::internal::memory_order_seq_cst_s) const
    {
      return mFlag.load(rsl::memory_order_seq_cst);
    }

    bool test() const
    {
      return mFlag.load(rsl::memory_order_seq_cst);
    }

  private:
    rsl::atomic<bool> mFlag;
  };

} // namespace rsl

#endif /* REX_ATOMIC_INTERNA_ATOMIC_FLAG_H */
