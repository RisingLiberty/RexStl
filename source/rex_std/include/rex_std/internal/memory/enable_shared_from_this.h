#pragma once

// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: enable_shared_from_this.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/bonus/attributes.h"
#include "rex_std/internal/memory/weak_ptr.h"
#include "rex_std/internal/type_traits/is_convertible.h"
#include "rex_std/internal/type_traits/remove_cv.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename T>
    class shared_ptr;

    // provide member functions that create shared_ptr to this
    template <typename T>
    class enable_shared_from_this
    {
    public:
      using enable_shared_from_this_type = enable_shared_from_this;

      REX_NO_DISCARD shared_ptr<T> shared_from_this()
      {
        return shared_ptr<T>(m_weak_ptr);
      }

      REX_NO_DISCARD shared_ptr<const T> shared_from_this() const
      {
        return shared_ptr<const T>(m_weak_ptr);
      }

      REX_NO_DISCARD weak_ptr<T> weak_from_this()
      {
        return m_weak_ptr;
      }

      REX_NO_DISCARD weak_ptr<const T> weak_from_this() const
      {
        return m_weak_ptr;
      }

    protected:
      constexpr enable_shared_from_this()
          : m_weak_ptr()
      {
      }

      // construct (must value-initialize m_weak_ptr)
      enable_shared_from_this(const enable_shared_from_this& /*other*/)
          : m_weak_ptr()
      {
      }

      enable_shared_from_this& operator=(const enable_shared_from_this& /*other*/)
      {
        // assign (must not change m_weak_ptr)
        return *this;
      }

      ~enable_shared_from_this() = default;

    private:
      template <class U>
      friend class shared_ptr;

      mutable weak_ptr<T> m_weak_ptr;
    };

    namespace internal
    {
      template <typename T, typename = void>
      struct has_shared_from_this : false_type
      {
      };

      template <typename T>
      struct has_shared_from_this<T, void_t<typename T::enable_shared_from_this_type>> : is_convertible<remove_cv_t<T>*, typename T::enable_shared_from_this_type*>::type
      {
      };

      template <typename T>
      inline constexpr bool has_shared_from_this_v = has_shared_from_this<T>::value;
    } // namespace internal
  }   // namespace v1
} // namespace rsl