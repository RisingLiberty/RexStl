


#ifndef REX_ATOMIC_INTERNAL_MEMORY_ORDER_H
#define REX_ATOMIC_INTERNAL_MEMORY_ORDER_H

#pragma once


namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      struct memory_order_relaxed_s {};
      struct memory_order_read_depends_s {};
      struct memory_order_acquire_s {};
      struct memory_order_release_s {};
      struct memory_order_acq_rel_s {};
      struct memory_order_seq_cst_s {};
    } // namespace internal


    inline constexpr auto memory_order_relaxed = internal::memory_order_relaxed_s{};
    inline constexpr auto memory_order_read_depends = internal::memory_order_read_depends_s{};
    inline constexpr auto memory_order_acquire = internal::memory_order_acquire_s{};
    inline constexpr auto memory_order_release = internal::memory_order_release_s{};
    inline constexpr auto memory_order_acq_rel = internal::memory_order_acq_rel_s{};
    inline constexpr auto memory_order_seq_cst = internal::memory_order_seq_cst_s{};

    enum class memory_order
    {
      relaxed,
      consume,
      acquire,
      release,
      acq_rel,
      seq_cst
    };
  }


} // namespace rsl


#endif /* REX_ATOMIC_INTERNAL_MEMORY_ORDER_H */
