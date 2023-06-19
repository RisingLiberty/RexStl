// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: ref_ptr.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/atomic//atomic_decrement.h"
#include "rex_std/bonus/atomic//atomic_increment.h"
#include "rex_std/bonus/atomic//atomic_read.h"
#include "rex_std/internal/assert/assert_fwd.h"
#include "rex_std/internal/memory/allocator.h"
#include "rex_std/internal/memory/default_delete.h"
#include "rex_std/internal/utility/swap.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename T>
    class weak_ptr;

    template <typename T>
    class shared_ptr;

    namespace internal
    {
      class ref_count_base
      {
      public:
        explicit ref_count_base(count_t refCount)
            : m_ref_count(refCount)
            , m_weak_ref_count(0)
        {
        }

        virtual ~ref_count_base() = default;

        count_t use_count() const
        {
          /// [06/Aug/2022] RSL Comment: If this causes any issues
          // it's because the value is read at the same time it is written to.
          return m_ref_count;
        }

        void inc_ref()
        {
          rsl::atomic_increment(m_ref_count);
        }
        void inc_weak_ref()
        {
          rsl::atomic_increment(m_weak_ref_count);
        }

        bool release()
        {
          RSL_ASSERT_X(use_count() > 0, "Invalid ref count for shared ptr");
          if(rsl::atomic_decrement(m_ref_count) == 0)
          {
            // you can never delete the last shared_ptr with still having a weak ptr referencing the ptr
            // that's why if the last shared ptr decrement results in 0 ref count, you can safely delete the ptr
            // however, it is possible that there are still weak pointers out there that reference the control block
            // that's why we can only delete the control block if the weak references are also 0
            delete_ptr();

            if(rsl::atomic_read(m_weak_ref_count) == 0)
            {
              delete_this();
            }
            return true;
          }

          return false;
        }
        void dec_weak_ref()
        {
          // it's possible all shared references destroyed but the control block isn't yet
          // because the weak ref is initialized with 1,
          if(rsl::atomic_decrement(m_weak_ref_count) == 0)
          {
            delete_this();
          }
        }

      private:
        virtual void delete_ptr()         = 0;
        virtual void delete_this()        = 0;
        virtual void* get_deleter() const = 0;

      private:
        count_t m_ref_count;
        count_t m_weak_ref_count;
      };

      template <typename T, typename Allocator, typename Deleter>
      class ref_count : ref_count_base
      {
      public:
        using value_type     = T;
        using pointer        = T*;
        using allocator_type = allocator;
        using deleter_type   = Deleter;

        ref_count(T* ptr, allocator allocator, Deleter deleter)
            : ref_count_base(1)
            , m_ptr(ptr)
            , m_deleter(rsl::move(deleter))
            , m_allocator(rsl::move(allocator))
        {
        }

        void delete_ptr() override
        {
          m_deleter(m_ptr);
          m_ptr = nullptr;
        }

        void delete_this() override
        {
          this->~ref_count();
          m_allocator.deallocate(this, sizeof(*this));
        }

        void* get_deleter() const final
        {
          return (void*)m_deleter;
        }

      private:
        T* m_ptr;
        Deleter m_deleter;
        Allocator m_allocator;
      };

      template <typename T>
      void allocate_shared_helper(shared_ptr<T>& sharedPtr, ref_count_base* refCount, T* value);

      template <typename T, typename Allocator>
      class ref_count_inst : public ref_count_base
      {
      public:
        using value_type     = T;
        using pointer        = T*;
        using allocator_type = Allocator;
        using storage_type   = rsl::aligned_storage_t<T>;

        pointer value()
        {
          return static_cast<value_type*>(static_cast<void*>(&m_memory));
        }

        template <typename... Args>
        explicit ref_count_inst(allocator_type allocator, Args&&... args)
            : ref_count_base(1)
            , m_allocator(allocator)
        {
          new(&m_memory) value_type(rsl::forward<Args>(args)...);
        }

        void delete_ptr() override
        {
          value()->~value_type();
        }
        void delete_this() override
        {
          this->~ref_count_inst();
          m_allocator.deallocate(this, sizeof(*this));
        }
        void* get_deleter() const final
        {
          return nullptr;
        }

      private:
        template <typename U>
        friend class shared_ptr;

      private:
        storage_type m_memory;
        allocator_type m_allocator;
      };

      template <typename T>
      class ref_ptr
      {
        template <typename U>
        friend class ref_ptr;

      public:
        ref_ptr()
            : m_ptr(nullptr)
            , m_ref_count(nullptr)
        {
        }

        /// RSL Comment: Different from ISO C++ Standard at time of writing (04/Aug/2022)
        // the pointer provided cannot be nullptr, in the standard, it can be
        template <typename U, typename Deleter>
        explicit ref_ptr(U* ptr, Deleter d = default_delete<T>())
            : m_ptr(ptr)
            , m_ref_count(nullptr)
        {
          RSL_ASSERT_X(m_ptr != nullptr, "nullptr cannot be provided for this constructor");
          alloc(ptr, d, allocator());
        }
        /// RSL Comment: Different from ISO C++ Standard at time of writing (04/Aug/2022)
        // in the standard, the use count after this construct call == 1
        template <typename U, typename Deleter>
        explicit ref_ptr(nullptr_t, Deleter d = default_delete<T>())
            : m_ptr(nullptr)
            , m_ref_count(nullptr)
        {
          alloc_without_ptr(nullptr, d, allocator());
        }

        template <typename U, typename Deleter, typename Allocator>
        ref_ptr(U* ptr, Deleter d, Allocator& alloc)
            : m_ptr(nullptr)
            , m_ref_count(nullptr)
        {
          RSL_ASSERT_X(m_ptr != nullptr, "nullptr cannot be provided for this constructor");
          alloc(ptr, d, alloc);
        }

        template <typename U, typename Deleter, typename Allocator>
        ref_ptr(nullptr_t, Deleter d, Allocator& alloc)
            : m_ptr(nullptr)
            , m_ref_count(nullptr)
        {
          alloc_without_ptr(d, alloc);
        }

        template <typename U>
        ref_ptr(const ref_ptr<U>& other, T* ptr)
            : m_ptr(ptr)
            , m_ref_count(other.m_ref_count)
        {
        }
        template <typename U>
        ref_ptr(ref_ptr<U>&& other, T* ptr)
            : m_ptr(ptr)
            , m_ref_count(other.m_ref_count)
        {
          other.m_ptr       = nullptr;
          other.m_ref_count = nullptr;
        }
        ref_ptr(const ref_ptr& other)
            : m_ptr(other.m_ptr)
            , m_ref_count(other.m_ref_count)
        {
        }
        template <typename U>
        ref_ptr(const ref_ptr<U>& other) // NOLINT(google-explicit-constructor)
            : m_ptr(other.m_ptr)
            , m_ref_count(other.m_ref_count)
        {
        }
        ref_ptr(ref_ptr&& other)
            : m_ptr(other.m_ptr)
            , m_ref_count(other.m_ref_count)
        {
          other.m_ptr       = nullptr;
          other.m_ref_count = nullptr;
        }
        template <typename U>
        ref_ptr(ref_ptr<U>&& other) // NOLINT(google-explicit-constructor)
            : m_ptr(other.m_ptr)
            , m_ref_count(other.m_ref_count)
        {
          other.m_ptr       = nullptr;
          other.m_ref_count = nullptr;
        }

        ~ref_ptr() = default;

        ref_ptr& operator=(const ref_ptr&) = default;
        ref_ptr& operator=(ref_ptr&& other)
        {
          rsl::exchange(m_ptr, other.m_ptr, nullptr);
          rsl::exchange(m_ref_count, other.m_ref_count, nullptr);
        }

        /// RSL Comment: Different from ISO C++ Standard at time of writing (05/Aug/2022)
        // the standard doesn't propagate const, rex does
        // returns a pointer to the managed object
        const T* get() const
        {
          return m_ptr;
        }
        // returns a pointer to the managed object
        T* get()
        {
          return m_ptr;
        }

        /// RSL Comment: Different from ISO C++ Standard at time of writing (19/Mar/2023)
        // this returns a long in the standard
        card32 use_count() const
        {
          return m_ref_count ? m_ref_count->use_count() : 0;
        }

        template <typename U>
        bool owner_before(const ref_ptr<U>& sharedPtr) const
        {
          return m_ref_count < sharedPtr.m_ref_count;
        }

      protected:
        void inc_ref()
        {
          m_ref_count->inc_ref();
        }
        void safe_inc_ref()
        {
          if(m_ref_count)
          {
            inc_ref();
          }
        }
        void inc_weak_ref()
        {
          m_ref_count->inc_weak_ref();
        }
        void safe_inc_weak_ref()
        {
          if(m_ref_count)
          {
            inc_weak_ref();
          }
        }

        void dec_ref()
        {
          m_ref_count->release();
        }
        void safe_dec_ref()
        {
          if(m_ref_count)
          {
            dec_ref();
          }
        }

        void dec_weak_ref()
        {
          m_ref_count->dec_weak_ref();
        }
        void safe_dec_weak_ref()
        {
          if(m_ref_count)
          {
            dec_weak_ref();
          }
        }

        template <typename U>
        void swap(ref_ptr<U>& other)
        {
          rsl::swap(m_ptr, other.m_ptr);
          rsl::swap(m_ref_count, other.m_ref_count);
        }

      private:
        template <typename U, typename Deleter, typename Allocator, enable_if_t<rsl::is_empty_v<Allocator>, bool> = true>
        void alloc(U* ptr, Deleter deleter, const Allocator& alloc)
        {
          void* mem = alloc.allocate(1_elem);

          m_ref_count = new(mem)(internal::ref_count<T, Allocator, Deleter>)(ptr, rsl::move(deleter), rsl::move(alloc));
          m_ptr       = ptr;
        }
        template <typename U, typename Deleter, typename Allocator, enable_if_t<!rsl::is_empty_v<Allocator>, bool> = true>
        void alloc(U* ptr, Deleter deleter, Allocator& alloc)
        {
          void* mem = alloc.allocate(1_elem);

          m_ref_count = new(mem)(internal::ref_count<T, Allocator, Deleter>)(ptr, rsl::move(deleter), rsl::move(alloc));
          m_ptr       = ptr;
        }
        template <typename Deleter, typename Allocator, enable_if_t<rsl::is_empty_v<Allocator>, bool> = true>
        void alloc_without_ptr(Deleter deleter, const Allocator& alloc)
        {
          void* mem = alloc.allocate(1_elem);

          m_ref_count = new(mem)(internal::ref_count<T, Allocator, Deleter>)(nullptr, rsl::move(deleter), rsl::move(alloc));
        }
        template <typename Deleter, typename Allocator, enable_if_t<!rsl::is_empty_v<Allocator>, bool> = true>
        void alloc_without_ptr(Deleter deleter, Allocator& alloc)
        {
          void* mem = alloc.allocate(1_elem);

          m_ref_count = new(mem)(internal::ref_count<T, Allocator, Deleter>)(nullptr, rsl::move(deleter), rsl::move(alloc));
        }

        template <typename U>
        friend void allocate_shared_helper(shared_ptr<U>&, ref_count_base*, U*);

      private:
        T* m_ptr;
        ref_count_base* m_ref_count;
      };
    } // namespace internal
  }   // namespace v1
} // namespace rsl
