// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: weak_ptr.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/memory/ref_ptr.h"
#include "rex_std/internal/memory/shared_ptr.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename T>
    class weak_ptr : public internal::ref_ptr<T>
    {
    public:
      using element_type = T;

      constexpr weak_ptr()
      {}
      weak_ptr(const weak_ptr& ptr)
        : internal::ref_ptr<T>(ptr)
      {
        internal::ref_ptr<T>::safe_inc_weak_ref();
      }
      template <typename U>
      weak_ptr(const weak_ptr<U>& ptr)
        : internal::ref_ptr<T>(ptr)
      {
        internal::ref_ptr<T>::safe_inc_weak_ref();
      }
      template <typename U>
      weak_ptr(const rsl::shared_ptr<U>& ptr)
        : internal::ref_ptr<T>(ptr)
      {
        internal::ref_ptr<T>::safe_inc_weak_ref();
      }
      weak_ptr(weak_ptr&& ptr)
        : internal::ref_ptr<T>(rsl::move(ptr))
      {
      }
      template <typename U>
      weak_ptr(weak_ptr<U>&& ptr)
        : internal::ref_ptr<T>(rsl::move(ptr))
      {
      }

      ~weak_ptr()
      {
        internal::ref_ptr<T>::safe_dec_weak_ref();
      }

      weak_ptr& operator=(const weak_ptr& ptr)
      {
        rsl::weak_ptr<T>(ptr).swap(*this);
        return *this;
      }
      template <typename U>
      weak_ptr& operator=(const weak_ptr<U>& ptr)
      {
        rsl::weak_ptr<T>(ptr).swap(*this);
        return *this;
      }
      template <typename U>
      weak_ptr& operator=(const shared_ptr<U>& ptr)
      {
        rsl::weak_ptr<T>(ptr).swap(*this);
        return *this;
      }
      weak_ptr& operator=(weak_ptr&& ptr)
      {
        rsl::weak_ptr<T>(rsl::move(ptr)).swap(*this);
        return *this;
      }
      template <typename U>
      weak_ptr& operator=(weak_ptr<U>&& ptr)
      {
        rsl::weak_ptr<T>(rsl::move(ptr)).swap(*this);
        return *this;
      }

      void reset()
      {
        weak_ptr{}.swap(*this);
      }
      void swap(weak_ptr& ptr)
      {
        internal::ref_ptr<T>::swap(ptr);
      }
      
      bool expired() const
      {
        return internal::ref_ptr<T>::use_count() == 0;
      }
      shared_ptr<T> lock() const
      {
        if (expired())
        {
          return shared_ptr<T>{};
        }
        
        return shared_ptr<T>(*this);
      }
    };

    template <typename T>
    void swap(weak_ptr<T>& lhs, weak_ptr<T>& rhs)
    {
      lhs.swap(rhs);
    }

    // atomic

    template <typename T>
    weak_ptr(shared_ptr<T>) -> weak_ptr<T>;
  }
}
