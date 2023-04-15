// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: shared_ptr.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/functional/hash_result.h"
#include "rex_std/bonus/memory/ref_ptr.h"
#include "rex_std/bonus/utility/compressed_pair.h"
#include "rex_std/internal/assert/assert_fwd.h"
#include "rex_std/internal/memory/allocator.h"
#include "rex_std/internal/memory/default_delete.h"
#include "rex_std/internal/memory/enable_shared_from_this.h"
#include "rex_std/internal/type_traits/aligned_storage.h"
#include "rex_std/internal/type_traits/alignment_of.h"
#include "rex_std/internal/type_traits/is_empty.h"
#include "rex_std/internal/type_traits/remove_extent.h"
#include "rex_std/internal/utility/move.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename T, typename Deleter>
    class unique_ptr;

    template <typename T>
    class shared_ptr : public internal::ref_ptr<T>
    {
    public:
      using element_type   = remove_extent_t<T>;
      using default_delete = default_delete<T>;
      using reference_type = T&;

      // constructs new shared ptr with no managed object
      shared_ptr() {}
      // constructs new shared ptr with no managed object
      shared_ptr(nullptr_t) // NOLINT(google-explicit-constructor)
      {
      }
      // constructs a shared ptr with a ptr as the managed objects
      // uses the delete expression as the deleter
      template <typename U>
      explicit shared_ptr(U* ptr)
          : internal::ref_ptr<T>(ptr)
      {
      }
      /// RSL Comment: Different from ISO C++ Standard at time of writing (04/Aug/2022)
      // the pointer provided cannot be nullptr, in the standard, it can be
      // constructs a shared ptr with a ptr as the managed objects
      // uses the provided deleter as the deleter
      template <typename U, typename Deleter>
      explicit shared_ptr(U* ptr, Deleter d)
          : internal::ref_ptr<T>(ptr, d)
      {
      }
      /// RSL Comment: Different from ISO C++ Standard at time of writing (04/Aug/2022)
      // in the standard, the use count after this construct call == 1
      // in rex, the use count after this is 0
      // construct a shared ptr with no managed object
      // uses the provided deleter as the deleter
      template <typename Deleter>
      explicit shared_ptr(nullptr_t, Deleter d)
          : internal::ref_ptr<T>(nullptr, d)
      {
      }
      /// RSL Comment: Different from ISO C++ Standard at time of writing (04/Aug/2022)
      // in the standard, the use count after this construct call == 1
      // in rex, the use count after this is 0
      // also the allocator is capture by value, not by reference
      // construct a shared ptr with no managed object
      // uses the provided deleter as the deleter
      // uses a copy of alloc for heap allocation
      template <typename U, typename Deleter, typename Alloc>
      explicit shared_ptr(U* ptr, Deleter d, Alloc& alloc)
          : internal::ref_ptr<T>(ptr, d, alloc)
      {
      }
      /// RSL Comment: Different from ISO C++ Standard at time of writing (04/Aug/2022)
      // in the standard, the use count after this construct call == 1
      // in rex, the use count after this is 0
      // also the allocator is capture by value, not by reference
      // construct a shared ptr with no managed object
      // uses the provided deleter as the deleter
      // uses a copy of alloc for heap allocation
      template <typename Deleter, typename Alloc>
      explicit shared_ptr(nullptr_t, Deleter d, Alloc& alloc)
          : internal::ref_ptr<T>(nullptr, d, alloc)
      {
      }
      // constructs a shared ptr instance that stores p and shares ownership with r.
      // post condition: get() == ptr && use_count() == sharedPtr.use_count()
      // the user is responsible to make sure "ptr" doesn't leak
      // all what this function does is store an UNMANAGED ptr
      // this is useful for when the pointer is a downcast of an existing pointer
      // it is not recommended to use this constructor if "ptr" is a pointer that needs to be deleted
      template <typename U>
      explicit shared_ptr(const shared_ptr<U>& sharedPtr, element_type* ptr)
          : internal::ref_ptr<T>(sharedPtr, ptr)
      {
        internal::ref_ptr<T>::safe_inc_ref();
      }
      // constructs a shared ptr that stores p and shares ownership with r
      // post condition: get() == ptr && use_count() == sharedPtr.use_count()
      // the provided sharedPtr is empty after the constructor call
      // the user is responsible to make sure "ptr" doesn't leak
      // all what this function does is store an UNMANAGED ptr
      // this is useful for when the pointer is a downcast of an existing pointer
      // it is not recommended to use this constructor if "ptr" is a pointer that needs to be deleted
      template <typename U>
      explicit shared_ptr(shared_ptr<U>&& sharedPtr, element_type* ptr)
          : internal::ref_ptr<T>(rsl::move(sharedPtr), ptr)
      {
      }
      // constructs a shared pointer which shares ownership with the sharedPtr provided.
      shared_ptr(const shared_ptr<T>& sharedPtr)
          : internal::ref_ptr<T>(sharedPtr)
      {
        internal::ref_ptr<T>::safe_inc_ref();
      }
      // constructs a shared pointer which shares ownership with the sharedPtr provided
      template <typename U>
      shared_ptr(const shared_ptr<U>& sharedPtr) // NOLINT(google-explicit-constructor)
          : internal::ref_ptr<T>(sharedPtr)
      {
        internal::ref_ptr<T>::safe_inc_ref();
      }
      // moves ownership from the sharedPtr provided
      // after the call the sharedPtr provided is empty
      shared_ptr(shared_ptr&& sharedPtr)
          : internal::ref_ptr<T>(rsl::move(sharedPtr))
      {
      }
      // moves ownership from the sharedPtr provided
      // after the call the sharedPtr provided is empty
      template <typename U>
      explicit shared_ptr(shared_ptr<U>&& sharedPtr)
          : internal::ref_ptr<T>(rsl::move(sharedPtr))
      {
      }
      // constructs a shared ptr that shares ownership with the provided weakPtr
      template <typename U>
      explicit shared_ptr(const weak_ptr<U>& weakPtr)
          : internal::ref_ptr<T>(weakPtr)
      {
        RSL_ASSERT_X(weakPtr.use_count() > 0, "cannot create shared ptr from emtpy weak ptr");
        internal::ref_ptr<T>::inc_ref();
      }

      // constructs a shared ptr from a uniquePtr
      // post condition: ref count == 1
      // uniquePtr.get() == nullptr
      template <typename U, typename Deleter>
      explicit shared_ptr(unique_ptr<U, Deleter>&& uniquePtr)
          : internal::ref_ptr<T>(uniquePtr.get())
      {
      }

      // decrements the reference count if this has a managed object.
      // if this is the last managed object, it destroys it through the provided deleter
      ~shared_ptr()
      {
        internal::ref_ptr<T>::safe_dec_ref();
      }

      // replaces the managed object with the one managed by r
      shared_ptr& operator=(const shared_ptr& other) // NOLINT(bugprone-unhandled-self-assignment)
      {
        RSL_ASSERT_X(&other != this, "copying shared ptr to itself");

        shared_ptr<T>(other).swap(*this);

        return *this;
      }

      // replaces the managed object with the one managed by r
      template <typename U>
      shared_ptr& operator=(const shared_ptr<U>& other)
      {
        if(!equivalent_ownership(other))
        {
          shared_ptr(other).swap(*this);
        }

        return *this;
      }

      // moves assigns a shared ptr from other.
      // after the assignment other is empty and this holds what r used to hold
      shared_ptr& operator=(shared_ptr&& other)
      {
        RSL_ASSERT_X(&other != this, "copying shared ptr to itself");

        shared_ptr(rsl::move(other)).swap(*this);

        return *this;
      }

      // moves assigns a shared ptr from other.
      // after the assignment other is empty and this holds what r used to hold
      template <typename U>
      shared_ptr& operator=(shared_ptr<U>&& other)
      {
        if(!equivalent_onwership(other))
        {
          shared_ptr(rsl::move(other)).swap(*this);
        }

        return *this;
      }

      // transfers ownership of an unique ptr to this
      template <typename U, typename Deleter>
      shared_ptr& operator=(unique_ptr<U, Deleter>&& other)
      {
        shared_ptr(rsl::move(other)).swap(*this);

        return *this;
      }

      // makes this shared ptr not manage the object anymore
      // "releases" the managed object, not to be confused with unique ptr's release.
      void reset()
      {
        shared_ptr().swap(*this);
      }
      // "releases" ownership and takes ownership of the passed in pointer
      // the word "release" is not to be confused with unique_ptr's release function
      template <typename U>
      void reset(U* ptr)
      {
        shared_ptr(ptr).swap(*this);
      }
      // "releases" ownership and takes ownership of the passed in pointer
      // the word "release" is not to be confused with unique_ptr's release function
      template <typename U, typename Deleter>
      void reset(U* ptr, Deleter deleter)
      {
        shared_ptr(ptr, deleter).swap(*this);
      }
      // "releases" ownership and takes ownership of the passed in pointer
      // the word "release" is not to be confused with unique_ptr's release function
      template <typename U, typename Deleter, typename Allocator>
      void reset(U* ptr, Deleter deleter, allocator& alloc)
      {
        shared_ptr(ptr, deleter, alloc).swap(*this);
      }

      // exchanges the owned pointer between two shared ptr objects
      void swap(shared_ptr& sharedPtr)
      {
        internal::ref_ptr<T>::swap(sharedPtr);
      }

      /// RSL Comment: Different from ISO C++ Standard at time of writing (05/Aug/2022)
      // the standard doesn't propagate const, rex does
      // returns a reference to the managed object
      reference_type operator*() const
      {
        return *internal::ref_ptr<T>::get();
      }
      // returns a reference to the managed object
      reference_type operator*()
      {
        return *internal::ref_ptr<T>::get();
      }
      /// RSL Comment: Different from ISO C++ Standard at time of writing (05/Aug/2022)
      // the standard doesn't propagate const, rex does
      // returns a pointer to the managed object
      const element_type* operator->() const
      {
        return internal::ref_ptr<T>::get();
      }
      element_type* operator->()
      {
        return internal::ref_ptr<T>::get();
      }

      // checks if the stored pointer is not null
      explicit operator bool() const
      {
        return internal::ref_ptr<T>::get() != nullptr;
      }

    private:
      void init_shared_from_this()
      {
        if constexpr(internal::has_shared_from_this_v<T>)
        {
          if(internal::ref_ptr<T>::get() && internal::ref_ptr<T>::get()->m_weak_ptr.expired())
          {
            internal::ref_ptr<T>::get()->m_weak_ptr = shared_ptr<remove_cv_t<T>>(*this, const_cast<remove_cv_t<T>*>(internal::ref_ptr<T>::get()));
          }
        }
      }

    private:
      template <class Deleter, typename U>
      friend Deleter* get_deleter(const shared_ptr<U>& ptr);

      template <typename U>
      friend void internal::allocate_shared_helper(shared_ptr<U>& sharedPtr, internal::ref_count_base* refCount, U* value);
    };

    namespace internal
    {
      template <typename T>
      void allocate_shared_helper(shared_ptr<T>& sharedPtr, ref_count_base* refCount, T* value)
      {
        sharedPtr.m_ref_count = refCount;
        sharedPtr.m_ptr       = value;
        sharedPtr.init_shared_from_this();
      }
    } // namespace internal

    template <typename T, typename Allocator, typename... Args>
    shared_ptr<T> allocate_shared(Allocator& allocator, Args&&... args)
    {
      using ref_count_type = internal::ref_count_inst<T, Allocator>;
      shared_ptr<T> ret;
      void* const mem           = allocator.allocate(sizeof(ref_count_type));
      ref_count_type* ref_count = new(mem) ref_count_type(allocator, rsl::forward<Args>(args)...);
      internal::allocate_shared_helper(ret, ref_count, ref_count->value());
      return ret;
    }

    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args&&... args)
    {
      allocator alloc {};
      return allocate_shared<T>(alloc, rsl::forward<Args>(args)...);
    }

    template <typename T>
    struct hash;

    template <typename T>
    struct hash<shared_ptr<T>>
    {
      hash_result operator()(const shared_ptr<T>& ptr) const
      {
        hash<T*> new_hash;
        return new_hash(ptr.get());
      }
    };

    template <typename T, typename U>
    shared_ptr<T> static_pointer_cast(const shared_ptr<U>& other)
    {
      const auto ptr = static_cast<typename shared_ptr<T>::element_type*>(other.get());
      return shared_ptr<T>(other, ptr);
    }
    template <typename T, typename U>
    shared_ptr<T> static_pointer_cast(shared_ptr<U>&& other)
    {
      const auto ptr = static_cast<typename shared_ptr<T>::element_type*>(other.get());
      return shared_ptr<T>(rsl::move(other), ptr);
    }

    template <typename T, typename U>
    shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U>& other)
    {
      const auto ptr = dynamic_cast<typename shared_ptr<T>::element_type*>(other.get());
      return shared_ptr<T>(other, ptr);
    }
    template <typename T, typename U>
    shared_ptr<T> dynamic_pointer_cast(shared_ptr<U>&& other)
    {
      const auto ptr = dynamic_cast<typename shared_ptr<T>::element_type*>(other.get());
      return shared_ptr<T>(rsl::move(other), ptr);
    }

    template <typename T, typename U>
    shared_ptr<T> const_pointer_cast(const shared_ptr<U>& other)
    {
      const auto ptr = const_cast<typename shared_ptr<T>::element_type*>(other.get());
      return shared_ptr<T>(other, ptr);
    }
    template <typename T, typename U>
    shared_ptr<T> const_pointer_cast(shared_ptr<U>&& other)
    {
      const auto ptr = const_cast<typename shared_ptr<T>::element_type*>(other.get());
      return shared_ptr<T>(rsl::move(other), ptr);
    }

    template <typename T, typename U>
    shared_ptr<T> reinterpret_pointer_cast(const shared_ptr<U>& other)
    {
      const auto ptr = reinterpret_cast<typename shared_ptr<T>::element_type*>(other.get());
      return shared_ptr<T>(other, ptr);
    }
    template <typename T, typename U>
    shared_ptr<T> reinterpret_pointer_cast(shared_ptr<U>&& other)
    {
      const auto ptr = reinterpret_cast<typename shared_ptr<T>::element_type*>(other.get());
      return shared_ptr<T>(rsl::move(other), ptr);
    }

    template <typename Deleter, typename T>
    Deleter* get_deleter(const shared_ptr<T>& p)
    {
      if(p.m_ref_count)
      {
        return static_cast<Deleter*>(p.m_ref_count->get_deleter());
      }
    }

    template <typename T, typename U>
    bool operator==(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
      return lhs.get() == rhs.get();
    }

    template <typename T, typename U>
    bool operator!=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
      return !(lhs == rhs);
    }

    template <typename T, typename U>
    bool operator<(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
      return less<>()(lhs.get(), rhs.get());
    }

    template <typename T, typename U>
    bool operator>(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
      return rhs < lhs;
    }

    template <typename T, typename U>
    bool operator<=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
      return !(rhs < lhs);
    }

    template <typename T, typename U>
    bool operator>=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
      return !(lhs < rhs);
    }

    template <typename T>
    bool operator==(const shared_ptr<T>& lhs, nullptr_t)
    {
      return !lhs;
    }

    template <typename T>
    bool operator==(nullptr_t, const shared_ptr<T>& lhs)
    {
      return !lhs;
    }

    template <typename T>
    bool operator!=(const shared_ptr<T>& lhs, nullptr_t)
    {
      return static_cast<bool>(lhs);
    }

    template <typename T>
    bool operator!=(nullptr_t, const shared_ptr<T>& lhs)
    {
      return static_cast<bool>(lhs);
    }

    template <typename T>
    bool operator<(const shared_ptr<T>& lhs, nullptr_t)
    {
      return less<T*>()(lhs.get(), nullptr);
    }

    template <typename T>
    bool operator<(nullptr_t, const shared_ptr<T>& lhs)
    {
      return less<T*>()(nullptr, lhs.get());
    }

    template <typename T>
    bool operator>(const shared_ptr<T>& lhs, nullptr_t)
    {
      return nullptr < lhs;
    }

    template <typename T>
    bool operator>(nullptr_t, const shared_ptr<T>& lhs)
    {
      return lhs < nullptr;
    }

    template <typename T>
    bool operator<=(const shared_ptr<T>& lhs, nullptr_t)
    {
      return !(nullptr < lhs);
    }

    template <typename T>
    bool operator<=(nullptr_t, const shared_ptr<T>& lhs)
    {
      return !(lhs < nullptr);
    }

    template <typename T>
    bool operator>=(const shared_ptr<T>& lhs, nullptr_t)
    {
      return !(lhs < nullptr);
    }

    template <typename T>
    bool operator>=(nullptr_t, const shared_ptr<T>& lhs)
    {
      return !(nullptr < lhs);
    }

    template <typename CharType, typename Traits>
    class basic_ostream;

    template <typename CharType, typename Traits, typename Y>
    basic_ostream<CharType, Traits>& operator<<(basic_ostream<CharType, Traits>& os, const shared_ptr<Y>& p)
    {
      os << p.get();
      return os;
    }
  } // namespace v1
} // namespace rsl
