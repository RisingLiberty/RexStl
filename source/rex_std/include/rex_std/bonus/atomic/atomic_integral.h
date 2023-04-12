#pragma once

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      template <typename T, unsigned Width = sizeof(T)>
      struct atomic_integral_base : public atomic_base_width<T, Width>
      {
      private:
        using Base = atomic_base_width<T, Width>;

      public:
        constexpr explicit atomic_integral_base(T desired)
            : Base(desired)
        {
        }

        constexpr atomic_integral_base()                  = default;
        ~atomic_integral_base()                           = default;
        atomic_integral_base(const atomic_integral_base&) = delete;

      public:
        using Base::operator=;

        atomic_integral_base& operator=(const atomic_integral_base&) = delete;

        atomic_integral_base& operator=(const atomic_integral_base&) volatile = delete;

      public:
        template <typename Order>
        T fetch_add(T /*unused*/, Order /*unused*/)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T fetch_add(T /*unused*/, Order /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T fetch_add(T /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T add_fetch(T /*unused*/, Order /*unused*/)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T add_fetch(T /*unused*/, Order /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T add_fetch(T /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T fetch_sub(T /*unused*/, Order /*unused*/)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T fetch_sub(T /*unused*/, Order /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T fetch_sub(T /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T sub_fetch(T /*unused*/, Order /*unused*/)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T sub_fetch(T /*unused*/, Order /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T sub_fetch(T /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T fetch_and(T /*unused*/, Order /*unused*/)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T fetch_and(T /*unused*/, Order /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T fetch_and(T /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T and_fetch(T /*unused*/, Order /*unused*/)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T and_fetch(T /*unused*/, Order /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T and_fetch(T /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T fetch_or(T /*unused*/, Order /*unused*/)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T fetch_or(T /*unused*/, Order /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T fetch_or(T /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T or_fetch(T /*unused*/, Order /*unused*/)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T or_fetch(T /*unused*/, Order /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T or_fetch(T /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T fetch_xor(T /*unused*/, Order /*unused*/)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T fetch_xor(T /*unused*/, Order /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T fetch_xor(T /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        template <typename Order>
        T xor_fetch(T /*unused*/, Order /*unused*/)
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : invalid memory order for the given operation!");
        }
        template <typename Order>
        T xor_fetch(T /*unused*/, Order /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
        T xor_fetch(T /*unused*/) volatile
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
        T operator+=(T /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

        T operator-=(T /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        T operator&=(T /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        T operator|=(T /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }

      public:
        T operator^=(T /*unused*/) volatile
        {
          static_assert(!rsl::is_same<T, T>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");
        }
      };

      template <typename T, unsigned Width = sizeof(T)>
      struct atomic_integral_width;

      template <typename T>
      struct atomic_integral_width<T, 1> : public atomic_integral_base<T, 1>
      {
      private:
        using Base = atomic_integral_base<T, 1>;

      public:
        constexpr explicit atomic_integral_width(T desired)
            : Base(desired)
        {
        }
        constexpr atomic_integral_width()                   = default;
        ~atomic_integral_width()                            = default;
        atomic_integral_width(const atomic_integral_width&) = delete;

      public:
        using Base::operator=;
        atomic_integral_width& operator=(const atomic_integral_width&)          = delete;
        atomic_integral_width& operator=(const atomic_integral_width&) volatile = delete;

      public:
        using Base::fetch_add;
        T fetch_add(T arg)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_add(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_add(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_add(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::add_fetch;
        T add_fetch(T arg)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T add_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T add_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T add_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_sub;
        T fetch_sub(T arg)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::sub_fetch;
        T sub_fetch(T arg)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_and;
        T fetch_and(T arg)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_and(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_and(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_and(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::and_fetch;
        T and_fetch(T arg)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T and_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T and_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T and_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_or;
        T fetch_or(T arg)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_or(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_or(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_or(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::or_fetch;
        T or_fetch(T arg)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T or_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T or_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T or_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_xor;
        T fetch_xor(T arg)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::xor_fetch;
        T xor_fetch(T arg)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
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
        constexpr explicit atomic_integral_width(T desired)
            : Base(desired)
        {
        }
        constexpr atomic_integral_width()                   = default;
        ~atomic_integral_width()                            = default;
        atomic_integral_width(const atomic_integral_width&) = delete;

      public:
        using Base::operator=;
        atomic_integral_width& operator=(const atomic_integral_width&)          = delete;
        atomic_integral_width& operator=(const atomic_integral_width&) volatile = delete;

      public:
        using Base::fetch_add;
        T fetch_add(T arg)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_add(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_add(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_add(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::add_fetch;
        T add_fetch(T arg)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T add_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T add_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T add_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_sub;
        T fetch_sub(T arg)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::sub_fetch;
        T sub_fetch(T arg)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_and;
        T fetch_and(T arg)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_and(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_and(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_and(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::and_fetch;
        T and_fetch(T arg)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T and_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T and_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T and_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_or;
        T fetch_or(T arg)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_or(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_or(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_or(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::or_fetch;
        T or_fetch(T arg)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T or_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T or_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T or_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_xor;
        T fetch_xor(T arg)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::xor_fetch;
        T xor_fetch(T arg)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
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
        constexpr explicit atomic_integral_width(T desired)
            : Base(desired)
        {
        }
        constexpr atomic_integral_width()                   = default;
        ~atomic_integral_width()                            = default;
        atomic_integral_width(const atomic_integral_width&) = delete;

      public:
        using Base::operator=;
        atomic_integral_width& operator=(const atomic_integral_width&)          = delete;
        atomic_integral_width& operator=(const atomic_integral_width&) volatile = delete;

      public:
        using Base::fetch_add;
        T fetch_add(T arg)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_add(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_add(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_add(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::add_fetch;
        T add_fetch(T arg)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T add_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T add_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T add_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_sub;
        T fetch_sub(T arg)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::sub_fetch;
        T sub_fetch(T arg)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_and;
        T fetch_and(T arg)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_and(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_and(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_and(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::and_fetch;
        T and_fetch(T arg)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T and_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T and_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T and_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_or;
        T fetch_or(T arg)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_or(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_or(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_or(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::or_fetch;
        T or_fetch(T arg)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T or_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T or_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T or_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_xor;
        T fetch_xor(T arg)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::xor_fetch;
        T xor_fetch(T arg)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
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
        constexpr explicit atomic_integral_width(T desired)
            : Base(desired)
        {
        }
        constexpr atomic_integral_width()                   = default;
        ~atomic_integral_width()                            = default;
        atomic_integral_width(const atomic_integral_width&) = delete;

      public:
        using Base::operator=;
        atomic_integral_width& operator=(const atomic_integral_width&)          = delete;
        atomic_integral_width& operator=(const atomic_integral_width&) volatile = delete;

      public:
        using Base::fetch_add;
        T fetch_add(T arg)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_add(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_add(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_add(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::add_fetch;
        T add_fetch(T arg)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T add_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T add_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T add_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_sub;
        T fetch_sub(T arg)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::sub_fetch;
        T sub_fetch(T arg)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_and;
        T fetch_and(T arg)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_and(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_and(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_and(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::and_fetch;
        T and_fetch(T arg)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T and_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T and_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T and_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_or;
        T fetch_or(T arg)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_or(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_or(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_or(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::or_fetch;
        T or_fetch(T arg)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T or_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T or_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T or_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_xor;
        T fetch_xor(T arg)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::xor_fetch;
        T xor_fetch(T arg)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
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
        constexpr explicit atomic_integral_width(T desired)
            : Base(desired)
        {
        }
        constexpr atomic_integral_width()                   = default;
        ~atomic_integral_width()                            = default;
        atomic_integral_width(const atomic_integral_width&) = delete;

      public:
        using Base::operator=;
        atomic_integral_width& operator=(const atomic_integral_width&)          = delete;
        atomic_integral_width& operator=(const atomic_integral_width&) volatile = delete;

      public:
        using Base::fetch_add;
        T fetch_add(T arg)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_add(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_add(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_add(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_add(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::add_fetch;
        T add_fetch(T arg)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T add_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T add_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T add_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T add_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_add_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_sub;
        T fetch_sub(T arg)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_sub(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_sub(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::sub_fetch;
        T sub_fetch(T arg)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T sub_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_sub_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_and;
        T fetch_and(T arg)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_and(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_and(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_and(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_and(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_and(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::and_fetch;
        T and_fetch(T arg)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T and_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T and_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T and_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T and_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_and_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_or;
        T fetch_or(T arg)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_or(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_or(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_or(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_or(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_or(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::or_fetch;
        T or_fetch(T arg)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T or_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T or_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T or_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T or_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_or_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::fetch_xor;
        T fetch_xor(T arg)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T fetch_xor(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_fetch_xor(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }

      public:
        using Base::xor_fetch;
        T xor_fetch(T arg)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::relaxed);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::acquire);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_release_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::release);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::acq_rel);
        }
        T xor_fetch(T arg, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          return rsl::atomic_xor_fetch(this->atomic_address(), arg, rsl::memory_order::seq_cst);
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
