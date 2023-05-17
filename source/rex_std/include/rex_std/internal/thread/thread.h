// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: thread.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

//-----------------------------------------------------------------------------
// https://en.cppreference.com/w/cpp/thread/thread
//
// The class thread represents a single thread of execution.
//-----------------------------------------------------------------------------

#include "rex_std/bonus/types.h"
#include "rex_std/internal/functional/invoke.h"
#include "rex_std/internal/memory/unique_ptr.h"
#include "rex_std/internal/assert/assert_impl.h"
#include "rex_std/internal/format/core.h"
#include "rex_std/internal/functional/hash.h"
#include "rex_std/internal/ostream/basic_ostream.h"
#include "rex_std/internal/sstream/basic_sstream.h"
#include "rex_std/internal/utility/forward.h"

namespace rsl
{
  inline namespace v1
  {


    namespace internal
    {
      template <typename Func>
      class func_wrapper
      {
      public:
        func_wrapper(Func&& func) // NOLINT(google-explicit-constructor)
            : m_func(rsl::forward<Func>(func))
        {
        }

        Func& function()
        {
          return m_func;
        }

      private:
        Func m_func;
      };
    } // namespace internal

    class thread
    {
    private:
      using thread_start_func = unsigned long(__stdcall*)(void*);

    public:
      class id
      {
        template <typename Char, typename Traits>
        friend basic_ostream<Char, Traits>& operator<<(basic_ostream<Char, Traits>& os, id id);
        friend struct hash<id>;
        friend class thread;

      public:
        explicit id(ulong id)
            : m_id(id)
        {
        }

        bool operator==(id other) const
        {
          return m_id == other.m_id;
        }
        bool operator!=(id other) const
        {
          return !(*this == other);
        }

        bool operator<(id other) const
        {
          return m_id < other.m_id;
        }
        bool operator<=(id other) const
        {
          return m_id <= other.m_id;
        }
        bool operator>(id other) const
        {
          return m_id > other.m_id;
        }
        bool operator>=(id other) const
        {
          return m_id >= other.m_id;
        }

      private:
        ulong m_id;
      };

      using native_handle_type = void*;

      // Creates new thread object which does not represent a thread.
      thread();
      thread(const thread&) = delete;
      // Constructs the thread object to represent the thread of execution that was represented by other. After this call other no longer represents a thread of execution.
      thread(thread&& other);

      /// RSL Comment: Different from ISO C++ Standard at time of writing (28/Jan/2023)
      // In the Standard Library, this function also takes in variadic arguments.
      // to avoid the complexity and not having to work with tuples, we just taking in a function.
      // Creates new std::thread object and associates it with a thread of execution. The new thread of execution starts executing f with args as function arguments
      template <typename Func>
      explicit thread(Func&& f)
          : m_handle()
          , m_id(0)
      {
        start(rsl::forward<Func>(f));
      }

      // destroys the thread object, if the thread has an associated thread, an assert is raised after which terminate is called
      ~thread();

      thread& operator=(const thread& other) = delete;

      // destroys the current thread object is as if the dtor was called
      // assigns the state of other to this and other is left in the default constructed state
      thread& operator=(thread&& other);

      // checks if there is still an active thread associated with this thread
      bool joinable() const;
      // returns the id of the thread
      id get_id() const;
      // returns the underlying implementation-defined thread handle
      native_handle_type native_handle();
      // returns the number of concurrent threads supported by the implementation
      static card32 hardware_concurrency();

      // waits for the thread to finish its execution
      void join();
      // permits the thread to execute independentaly from the thread handle
      void detach();
      // swap two thread objects
      void swap(thread& other);

    private:
      void create(thread_start_func func, void* param);

      template <typename Func>
      void start(Func&& func)
      {
        rsl::unique_ptr<internal::func_wrapper<Func>> func_wrapper = rsl::make_unique<internal::func_wrapper<Func>>(rsl::forward<Func>(func));
        create(&invoke<Func>, func_wrapper.release());
      }

      template <typename Func>
      static ulong __stdcall invoke(void* param)
      {
        // the reason why I copy the function ptr is so that we don't have a possible heap alloc
        // that lasts for the rest of the program
        // this could lad to "memory leak" which wouldn't really be leaking
        rsl::unique_ptr<internal::func_wrapper<Func>> func(static_cast<internal::func_wrapper<Func>*>(param));
        auto& function_ptr = func->function();
        rsl::invoke(function_ptr);
        return 0;
      }

    private:
      native_handle_type m_handle;
      id m_id;
    };

    template <typename Char, typename Traits>
    basic_ostream<Char, Traits>& operator<<(basic_ostream<Char, Traits>& os, thread::id id)
    {
      os << id.m_id;
      return os;
    }

    // swap two thread objects
    void swap(thread& lhs, thread& rhs);

    template <>
    struct formatter<thread::id>
    {
      auto parse(format_parse_context& ctx) const -> decltype(ctx.begin()) // NOLINT(readability-convert-member-functions-to-static)
      {
        return ctx.begin();
      }

      template <typename FormatContext>
      auto format(const thread::id& id, FormatContext& ctx) -> decltype(ctx.out())
      {
        rsl::stringstream ss;
        ss << id;
        rsl::string str = ss.str();
        return format_to(ctx.out(), "{}", str);
      }
    };

  } // namespace v1
} // namespace rsl
