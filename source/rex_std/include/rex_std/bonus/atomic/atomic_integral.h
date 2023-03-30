#pragma once

namespace rsl

{

  inline namespace v1

  {

    namespace internal

    {

      template <typename T, unsigned width = sizeof(T)>
      struct atomic_integral_base : public atomic_base_width<T, width>

      {
      private:
        using Base = atomic_base_width<T, width>;

      public:
        constexpr atomic_integral_base(T desired)
          : Base(desired)
        {
        }

        constexpr atomic_integral_base() = default;

        atomic_integral_base(const atomic_integral_base&) = delete;

      public:
        using Base::operator=;

        atomic_integral_base& operator=(const atomic_integral_base&) = delete;

        atomic_integral_base& operator=(const atomic_integral_base&) volatile = delete;

      public:
        template <typename Order>
        T fetch_add(T, Order)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T fetch_add(T, Order) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T fetch_add(T) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T add_fetch(T, Order)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T add_fetch(T, Order) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T add_fetch(T) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T fetch_sub(T, Order)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T fetch_sub(T, Order) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T fetch_sub(T) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T sub_fetch(T, Order)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T sub_fetch(T, Order) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T sub_fetch(T) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T fetch_and(T, Order)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T fetch_and(T, Order) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T fetch_and(T) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T and_fetch(T, Order)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T and_fetch(T, Order) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T and_fetch(T) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T fetch_or(T, Order)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T fetch_or(T, Order) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T fetch_or(T) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T or_fetch(T, Order)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T or_fetch(T, Order) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T or_fetch(T) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T fetch_xor(T, Order)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T fetch_xor(T, Order) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T fetch_xor(T) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T xor_fetch(T, Order)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T xor_fetch(T, Order) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T xor_fetch(T) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        T operator++() volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T operator++(int) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

        T operator--() volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T operator--(int) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        T operator+=(T) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

        T operator-=(T) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        T operator&=(T) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        T operator|=(T) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        T operator^=(T) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
      };

      template <typename T, unsigned width = sizeof(T)>
      struct atomic_integral_width;

      template <typename T>
      struct atomic_integral_width<T, 1> : public atomic_integral_base<T, 1>
      {
      private:
        using Base = atomic_integral_base<T, 1>;

      public:
        constexpr atomic_integral_width(T desired)
          : Base(desired)
        {
        }
        constexpr atomic_integral_width() = default;
        atomic_integral_width(const atomic_integral_width&) = delete;

      public:
        using Base::operator=;
        atomic_integral_width& operator=(const atomic_integral_width&) = delete;
        atomic_integral_width& operator=(const atomic_integral_width&) volatile = delete;

      public:
        using Base::fetch_add;
        T fetch_add(T arg)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_and_relaxed(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_and_acquire(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_and_release(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_and_acq_rel(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::add_fetch;
        T add_fetch(T arg)
        {
          return rsl::atomic_add_fetch_seq_cst(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_add_fetch_relaxed(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_add_fetch_acquire(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_add_fetch_release(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_add_fetch_acq_rel(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_add_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_sub;
        T fetch_sub(T arg)
        {
          return rsl::atomic_fetch_sub_seq_cst(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_sub_relaxed(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_sub_acquire(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_sub_release(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_sub_acq_rel(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_sub_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::sub_fetch;
        T sub_fetch(T arg)
        {
          return rsl::atomic_sub_fetch_seq_cst(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_sub_fetch_relaxed(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_sub_fetch_acquire(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_sub_fetch_release(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_sub_fetch_acq_rel(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_sub_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_and;
        T fetch_and(T arg)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_and_relaxed(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_and_acquire(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_and_release(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_and_acq_rel(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::and_fetch;
        T and_fetch(T arg)
        {
          return rsl::atomic_and_fetch_seq_cst(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_and_fetch_relaxed(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_and_fetch_acquire(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_and_fetch_release(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_and_fetch_acq_rel(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_and_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_or;
        T fetch_or(T arg)
        {
          return rsl::atomic_fetch_or_seq_cst(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_or_relaxed(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_or_acquire(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_or_release(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_or_acq_rel(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_or_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::or_fetch;
        T or_fetch(T arg)
        {
          return rsl::atomic_or_fetch_seq_cst(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_or_fetch_relaxed(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_or_fetch_acquire(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_or_fetch_release(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_or_fetch_acq_rel(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_or_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_xor;
        T fetch_xor(T arg)
        {
          return rsl::atomic_fetch_xor_seq_cst(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_xor_relaxed(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_xor_acquire(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_xor_release(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_xor_acq_rel(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_xor_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::xor_fetch;
        T xor_fetch(T arg)
        {
          return rsl::atomic_xor_fetch_seq_cst(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_xor_fetch_relaxed(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_xor_fetch_acquire(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_xor_fetch_release(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_xor_fetch_acq_rel(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_xor_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::operator++;
        T operator++()
        {
          return add_fetch(1, rsl::memory_order_seq_cst);
        }
        T operator++(int)
        {
          return fetch_add(1, rsl::memory_order_seq_cst);
        }
        using Base::operator--;
        T operator--()
        {
          return sub_fetch(1, rsl::memory_order_seq_cst);
        }
        T operator--(int)
        {
          return fetch_sub(1, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator+=;
        T operator+=(T arg)
        {
          return add_fetch(arg, rsl::memory_order_seq_cst);
        }
        using Base::operator-=;
        T operator-=(T arg)
        {
          return sub_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator&=;
        T operator&=(T arg)
        {
          return and_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator|=;
        T operator|=(T arg)
        {
          return or_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator^=;
        T operator^=(T arg)
        {
          return xor_fetch(arg, rsl::memory_order_seq_cst);
        }
      };

      template <typename T>
      struct atomic_integral_width<T, 2> : public atomic_integral_base<T, 2>
      {
      private:
        using Base = atomic_integral_base<T, 2>;

      public:
        constexpr atomic_integral_width(T desired)
          : Base(desired)
        {
        }
        constexpr atomic_integral_width() = default;
        atomic_integral_width(const atomic_integral_width&) = delete;

      public:
        using Base::operator=;
        atomic_integral_width& operator=(const atomic_integral_width&) = delete;
        atomic_integral_width& operator=(const atomic_integral_width&) volatile = delete;

      public:
        using Base::fetch_add;
        T fetch_add(T arg)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_and_relaxed(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_and_acquire(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_and_release(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_and_acq_rel(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::add_fetch;
        T add_fetch(T arg)
        {
          return rsl::atomic_add_fetch_seq_cst(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_add_fetch_relaxed(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_add_fetch_acquire(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_add_fetch_release(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_add_fetch_acq_rel(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_add_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_sub;
        T fetch_sub(T arg)
        {
          return rsl::atomic_fetch_sub_seq_cst(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_sub_relaxed(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_sub_acquire(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_sub_release(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_sub_acq_rel(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_sub_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::sub_fetch;
        T sub_fetch(T arg)
        {
          return rsl::atomic_sub_fetch_seq_cst(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_sub_fetch_relaxed(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_sub_fetch_acquire(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_sub_fetch_release(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_sub_fetch_acq_rel(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_sub_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_and;
        T fetch_and(T arg)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_and_relaxed(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_and_acquire(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_and_release(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_and_acq_rel(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::and_fetch;
        T and_fetch(T arg)
        {
          return rsl::atomic_and_fetch_seq_cst(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_and_fetch_relaxed(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_and_fetch_acquire(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_and_fetch_release(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_and_fetch_acq_rel(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_and_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_or;
        T fetch_or(T arg)
        {
          return rsl::atomic_fetch_or_seq_cst(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_or_relaxed(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_or_acquire(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_or_release(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_or_acq_rel(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_or_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::or_fetch;
        T or_fetch(T arg)
        {
          return rsl::atomic_or_fetch_seq_cst(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_or_fetch_relaxed(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_or_fetch_acquire(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_or_fetch_release(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_or_fetch_acq_rel(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_or_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_xor;
        T fetch_xor(T arg)
        {
          return rsl::atomic_fetch_xor_seq_cst(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_xor_relaxed(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_xor_acquire(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_xor_release(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_xor_acq_rel(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_xor_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::xor_fetch;
        T xor_fetch(T arg)
        {
          return rsl::atomic_xor_fetch_seq_cst(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_xor_fetch_relaxed(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_xor_fetch_acquire(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_xor_fetch_release(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_xor_fetch_acq_rel(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_xor_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::operator++;
        T operator++()
        {
          return add_fetch(1, rsl::memory_order_seq_cst);
        }
        T operator++(int)
        {
          return fetch_add(1, rsl::memory_order_seq_cst);
        }
        using Base::operator--;
        T operator--()
        {
          return sub_fetch(1, rsl::memory_order_seq_cst);
        }
        T operator--(int)
        {
          return fetch_sub(1, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator+=;
        T operator+=(T arg)
        {
          return add_fetch(arg, rsl::memory_order_seq_cst);
        }
        using Base::operator-=;
        T operator-=(T arg)
        {
          return sub_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator&=;
        T operator&=(T arg)
        {
          return and_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator|=;
        T operator|=(T arg)
        {
          return or_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator^=;
        T operator^=(T arg)
        {
          return xor_fetch(arg, rsl::memory_order_seq_cst);
        }
      };

      template <typename T>
      struct atomic_integral_width<T, 4> : public atomic_integral_base<T, 4>
      {
      private:
        using Base = atomic_integral_base<T, 4>;

      public:
        constexpr atomic_integral_width(T desired)
          : Base(desired)
        {
        }
        constexpr atomic_integral_width() = default;
        atomic_integral_width(const atomic_integral_width&) = delete;

      public:
        using Base::operator=;
        atomic_integral_width& operator=(const atomic_integral_width&) = delete;
        atomic_integral_width& operator=(const atomic_integral_width&) volatile = delete;

      public:
        using Base::fetch_add;
        T fetch_add(T arg)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_and_relaxed(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_and_acquire(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_and_release(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_and_acq_rel(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::add_fetch;
        T add_fetch(T arg)
        {
          return rsl::atomic_add_fetch_seq_cst(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_add_fetch_relaxed(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_add_fetch_acquire(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_add_fetch_release(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_add_fetch_acq_rel(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_add_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_sub;
        T fetch_sub(T arg)
        {
          return rsl::atomic_fetch_sub_seq_cst(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_sub_relaxed(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_sub_acquire(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_sub_release(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_sub_acq_rel(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_sub_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::sub_fetch;
        T sub_fetch(T arg)
        {
          return rsl::atomic_sub_fetch_seq_cst(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_sub_fetch_relaxed(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_sub_fetch_acquire(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_sub_fetch_release(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_sub_fetch_acq_rel(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_sub_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_and;
        T fetch_and(T arg)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_and_relaxed(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_and_acquire(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_and_release(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_and_acq_rel(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::and_fetch;
        T and_fetch(T arg)
        {
          return rsl::atomic_and_fetch_seq_cst(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_and_fetch_relaxed(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_and_fetch_acquire(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_and_fetch_release(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_and_fetch_acq_rel(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_and_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_or;
        T fetch_or(T arg)
        {
          return rsl::atomic_fetch_or_seq_cst(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_or_relaxed(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_or_acquire(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_or_release(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_or_acq_rel(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_or_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::or_fetch;
        T or_fetch(T arg)
        {
          return rsl::atomic_or_fetch_seq_cst(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_or_fetch_relaxed(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_or_fetch_acquire(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_or_fetch_release(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_or_fetch_acq_rel(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_or_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_xor;
        T fetch_xor(T arg)
        {
          return rsl::atomic_fetch_xor_seq_cst(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_xor_relaxed(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_xor_acquire(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_xor_release(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_xor_acq_rel(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_xor_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::xor_fetch;
        T xor_fetch(T arg)
        {
          return rsl::atomic_xor_fetch_seq_cst(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_xor_fetch_relaxed(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_xor_fetch_acquire(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_xor_fetch_release(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_xor_fetch_acq_rel(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_xor_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::operator++;
        T operator++()
        {
          return add_fetch(1, rsl::memory_order_seq_cst);
        }
        T operator++(int)
        {
          return fetch_add(1, rsl::memory_order_seq_cst);
        }
        using Base::operator--;
        T operator--()
        {
          return sub_fetch(1, rsl::memory_order_seq_cst);
        }
        T operator--(int)
        {
          return fetch_sub(1, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator+=;
        T operator+=(T arg)
        {
          return add_fetch(arg, rsl::memory_order_seq_cst);
        }
        using Base::operator-=;
        T operator-=(T arg)
        {
          return sub_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator&=;
        T operator&=(T arg)
        {
          return and_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator|=;
        T operator|=(T arg)
        {
          return or_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator^=;
        T operator^=(T arg)
        {
          return xor_fetch(arg, rsl::memory_order_seq_cst);
        }
      };

      template <typename T>
      struct atomic_integral_width<T, 8> : public atomic_integral_base<T, 8>
      {
      private:
        using Base = atomic_integral_base<T, 8>;

      public:
        constexpr atomic_integral_width(T desired)
          : Base(desired)
        {
        }
        constexpr atomic_integral_width() = default;
        atomic_integral_width(const atomic_integral_width&) = delete;

      public:
        using Base::operator=;
        atomic_integral_width& operator=(const atomic_integral_width&) = delete;
        atomic_integral_width& operator=(const atomic_integral_width&) volatile = delete;

      public:
        using Base::fetch_add;
        T fetch_add(T arg)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_and_relaxed(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_and_acquire(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_and_release(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_and_acq_rel(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::add_fetch;
        T add_fetch(T arg)
        {
          return rsl::atomic_add_fetch_seq_cst(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_add_fetch_relaxed(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_add_fetch_acquire(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_add_fetch_release(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_add_fetch_acq_rel(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_add_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_sub;
        T fetch_sub(T arg)
        {
          return rsl::atomic_fetch_sub_seq_cst(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_sub_relaxed(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_sub_acquire(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_sub_release(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_sub_acq_rel(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_sub_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::sub_fetch;
        T sub_fetch(T arg)
        {
          return rsl::atomic_sub_fetch_seq_cst(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_sub_fetch_relaxed(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_sub_fetch_acquire(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_sub_fetch_release(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_sub_fetch_acq_rel(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_sub_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_and;
        T fetch_and(T arg)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_and_relaxed(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_and_acquire(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_and_release(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_and_acq_rel(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::and_fetch;
        T and_fetch(T arg)
        {
          return rsl::atomic_and_fetch_seq_cst(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_and_fetch_relaxed(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_and_fetch_acquire(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_and_fetch_release(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_and_fetch_acq_rel(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_and_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_or;
        T fetch_or(T arg)
        {
          return rsl::atomic_fetch_or_seq_cst(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_or_relaxed(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_or_acquire(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_or_release(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_or_acq_rel(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_or_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::or_fetch;
        T or_fetch(T arg)
        {
          return rsl::atomic_or_fetch_seq_cst(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_or_fetch_relaxed(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_or_fetch_acquire(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_or_fetch_release(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_or_fetch_acq_rel(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_or_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_xor;
        T fetch_xor(T arg)
        {
          return rsl::atomic_fetch_xor_seq_cst(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_xor_relaxed(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_xor_acquire(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_xor_release(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_xor_acq_rel(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_xor_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::xor_fetch;
        T xor_fetch(T arg)
        {
          return rsl::atomic_xor_fetch_seq_cst(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_xor_fetch_relaxed(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_xor_fetch_acquire(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_xor_fetch_release(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_xor_fetch_acq_rel(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_xor_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::operator++;
        T operator++()
        {
          return add_fetch(1, rsl::memory_order_seq_cst);
        }
        T operator++(int)
        {
          return fetch_add(1, rsl::memory_order_seq_cst);
        }
        using Base::operator--;
        T operator--()
        {
          return sub_fetch(1, rsl::memory_order_seq_cst);
        }
        T operator--(int)
        {
          return fetch_sub(1, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator+=;
        T operator+=(T arg)
        {
          return add_fetch(arg, rsl::memory_order_seq_cst);
        }
        using Base::operator-=;
        T operator-=(T arg)
        {
          return sub_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator&=;
        T operator&=(T arg)
        {
          return and_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator|=;
        T operator|=(T arg)
        {
          return or_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator^=;
        T operator^=(T arg)
        {
          return xor_fetch(arg, rsl::memory_order_seq_cst);
        }
      };

      template <typename T>
      struct atomic_integral_width<T, 16> : public atomic_integral_base<T, 16>
      {
      private:
        using Base = atomic_integral_base<T, 16>;

      public:
        constexpr atomic_integral_width(T desired)
          : Base(desired)
        {
        }
        constexpr atomic_integral_width() = default;
        atomic_integral_width(const atomic_integral_width&) = delete;

      public:
        using Base::operator=;
        atomic_integral_width& operator=(const atomic_integral_width&) = delete;
        atomic_integral_width& operator=(const atomic_integral_width&) volatile = delete;

      public:
        using Base::fetch_add;
        T fetch_add(T arg)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_and_relaxed(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_and_acquire(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_and_release(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_and_acq_rel(this->atomic_address(), arg);
        }
        T fetch_add(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::add_fetch;
        T add_fetch(T arg)
        {
          return rsl::atomic_add_fetch_seq_cst(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_add_fetch_relaxed(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_add_fetch_acquire(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_add_fetch_release(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_add_fetch_acq_rel(this->atomic_address(), arg);
        }
        T add_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_add_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_sub;
        T fetch_sub(T arg)
        {
          return rsl::atomic_fetch_sub_seq_cst(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_sub_relaxed(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_sub_acquire(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_sub_release(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_sub_acq_rel(this->atomic_address(), arg);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_sub_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::sub_fetch;
        T sub_fetch(T arg)
        {
          return rsl::atomic_sub_fetch_seq_cst(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_sub_fetch_relaxed(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_sub_fetch_acquire(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_sub_fetch_release(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_sub_fetch_acq_rel(this->atomic_address(), arg);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_sub_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_and;
        T fetch_and(T arg)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_and_relaxed(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_and_acquire(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_and_release(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_and_acq_rel(this->atomic_address(), arg);
        }
        T fetch_and(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_and_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::and_fetch;
        T and_fetch(T arg)
        {
          return rsl::atomic_and_fetch_seq_cst(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_and_fetch_relaxed(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_and_fetch_acquire(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_and_fetch_release(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_and_fetch_acq_rel(this->atomic_address(), arg);
        }
        T and_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_and_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_or;
        T fetch_or(T arg)
        {
          return rsl::atomic_fetch_or_seq_cst(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_or_relaxed(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_or_acquire(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_or_release(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_or_acq_rel(this->atomic_address(), arg);
        }
        T fetch_or(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_or_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::or_fetch;
        T or_fetch(T arg)
        {
          return rsl::atomic_or_fetch_seq_cst(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_or_fetch_relaxed(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_or_fetch_acquire(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_or_fetch_release(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_or_fetch_acq_rel(this->atomic_address(), arg);
        }
        T or_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_or_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::fetch_xor;
        T fetch_xor(T arg)
        {
          return rsl::atomic_fetch_xor_seq_cst(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_fetch_xor_relaxed(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_fetch_xor_acquire(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_fetch_xor_release(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_fetch_xor_acq_rel(this->atomic_address(), arg);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_fetch_xor_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::xor_fetch;
        T xor_fetch(T arg)
        {
          return rsl::atomic_xor_fetch_seq_cst(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_relaxed_s)
        {
          return rsl::atomic_xor_fetch_relaxed(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acquire_s)
        {
          return rsl::atomic_xor_fetch_acquire(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_release_s)
        {
          return rsl::atomic_xor_fetch_release(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acq_rel_s)
        {
          return rsl::atomic_xor_fetch_acq_rel(this->atomic_address(), arg);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_seq_cst_s)
        {
          return rsl::atomic_xor_fetch_seq_cst(this->atomic_address(), arg);
        }

      public:
        using Base::operator++;
        T operator++()
        {
          return add_fetch(1, rsl::memory_order_seq_cst);
        }
        T operator++(int)
        {
          return fetch_add(1, rsl::memory_order_seq_cst);
        }
        using Base::operator--;
        T operator--()
        {
          return sub_fetch(1, rsl::memory_order_seq_cst);
        }
        T operator--(int)
        {
          return fetch_sub(1, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator+=;
        T operator+=(T arg)
        {
          return add_fetch(arg, rsl::memory_order_seq_cst);
        }
        using Base::operator-=;
        T operator-=(T arg)
        {
          return sub_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator&=;
        T operator&=(T arg)
        {
          return and_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator|=;
        T operator|=(T arg)
        {
          return or_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator^=;
        T operator^=(T arg)
        {
          return xor_fetch(arg, rsl::memory_order_seq_cst);
        }
      };

    } // namespace internal

  } // namespace v1

} // namespace rsl
