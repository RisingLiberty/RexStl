

#pragma once

#include "rex_std/atomic.h"

namespace rsl
{
  inline namespace v1
  {

    class atomic_flag
    {
    public: /* ctors */
      constexpr explicit atomic_flag(bool desired)
          : m_flag {desired}
      {
      }

      constexpr atomic_flag()
          : m_flag {false}
      {
      }

      ~atomic_flag() = default;

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

      void clear(rsl::internal::memory_order_relaxed_s /*unused*/)
      {
        m_flag.store(false, rsl::memory_order_relaxed);
      }

      void clear(rsl::internal::memory_order_release_s /*unused*/)
      {
        m_flag.store(false, rsl::memory_order_release);
      }

      void clear(rsl::internal::memory_order_seq_cst_s /*unused*/)
      {
        m_flag.store(false, rsl::memory_order_seq_cst);
      }

      void clear()
      {
        m_flag.store(false, rsl::memory_order_seq_cst);
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

      bool test_and_set(rsl::internal::memory_order_relaxed_s /*unused*/)
      {
        return m_flag.exchange(true, rsl::memory_order_relaxed);
      }

      bool test_and_set(rsl::internal::memory_order_acquire_s /*unused*/)
      {
        return m_flag.exchange(true, rsl::memory_order_acquire);
      }

      bool test_and_set(rsl::internal::memory_order_release_s /*unused*/)
      {
        return m_flag.exchange(true, rsl::memory_order_release);
      }

      bool test_and_set(rsl::internal::memory_order_acq_rel_s /*unused*/)
      {
        return m_flag.exchange(true, rsl::memory_order_acq_rel);
      }

      bool test_and_set(rsl::internal::memory_order_seq_cst_s /*unused*/)
      {
        return m_flag.exchange(true, rsl::memory_order_seq_cst);
      }

      bool test_and_set()
      {
        return m_flag.exchange(true, rsl::memory_order_seq_cst);
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

      bool test(rsl::internal::memory_order_relaxed_s /*unused*/) const
      {
        return m_flag.load(rsl::memory_order_relaxed);
      }

      bool test(rsl::internal::memory_order_acquire_s /*unused*/) const
      {
        return m_flag.load(rsl::memory_order_acquire);
      }

      bool test(rsl::internal::memory_order_seq_cst_s /*unused*/) const
      {
        return m_flag.load(rsl::memory_order_seq_cst);
      }

      bool test() const
      {
        return m_flag.load(rsl::memory_order_seq_cst);
      }

    private:
      rsl::atomic<bool> m_flag {};
    };
  } // namespace v1

} // namespace rsl
