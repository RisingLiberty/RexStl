// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: stacktrace.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/array.h"
#include "rex_std/bonus/string.h"
#include "rex_std/format.h"
#include "rex_std/internal/functional/hash.h"
#include "rex_std/internal/iterator/random_access_iterator.h"
#include "rex_std/internal/iterator/reverse_iterator.h"
#include "rex_std/internal/memory/allocator.h"
#include "rex_std/iostream.h"
#include "rex_std/string.h"
#include "rex_std/vector.h"

namespace rsl
{
  inline namespace v1
  {
    class stacktrace_entry
    {
    public:
      using native_handle_type = void*;

      stacktrace_entry();
      stacktrace_entry(native_handle_type handle, const big_stack_string& file, const big_stack_string& func, card32 lineNr);
      stacktrace_entry(const stacktrace_entry& other) = default;
      ~stacktrace_entry()                             = default;

      stacktrace_entry& operator=(const stacktrace_entry& other) = default;

      native_handle_type native_handle() const;

      /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Mar/2023)
      // This is implicit in the standard
      explicit operator bool() const;

      rsl::string description() const;

      /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Mar/2023)
      // This returns a std::string in the standard
      const rsl::big_stack_string& source_file() const;
      card32 source_line() const;

    private:
      rsl::big_stack_string m_file;
      rsl::big_stack_string m_function;
      native_handle_type m_handle;
      card32 m_line_nr;
    };

    bool operator==(const stacktrace_entry& lhs, const stacktrace_entry& rhs);
    bool operator!=(const stacktrace_entry& lhs, const stacktrace_entry& rhs);
    rsl::string to_string(const stacktrace_entry& entry);

    template <typename Char, typename Traits>
    class basic_ostream;

    rsl::ostream& operator<<(rsl::ostream& os, const stacktrace_entry& entry);
    rsl::wostream& operator<<(rsl::wostream& os, const stacktrace_entry& entry);

    template <>
    struct formatter<stacktrace_entry>
    {
      auto parse(format_parse_context& ctx) const -> decltype(ctx.begin()) // NOLINT(readability-convert-member-functions-to-static)
      {
        return ctx.begin();
      }

      template <typename FormatContext>
      auto format(const stacktrace_entry& stacktrace, FormatContext& ctx) -> decltype(ctx.out())
      {
        return format_to(ctx.out(), "{}", stacktrace.description());
      }
    };

    template <>
    struct hash<rsl::stacktrace_entry>
    {
      constexpr hash_result operator()(const stacktrace_entry& entry)
      {
        return hash<stacktrace_entry::native_handle_type> {}(entry.native_handle());
      }
    };

    template <typename Allocator>
    class basic_stacktrace;

    namespace internal
    {
      inline constexpr card32 g_stacktrace_stack_size = 10;
      __declspec(noinline) rsl::array<stacktrace_entry, g_stacktrace_stack_size> stack_trace(card32 skip, card32 maxDepth);
    } // namespace internal

    template <typename Allocator>
    class basic_stacktrace
    {
    private:
      constexpr static card32 s_max_entries = internal::g_stacktrace_stack_size;

    public:
      using value_type             = stacktrace_entry;
      using reference              = value_type&;
      using const_reference        = const value_type&;
      using const_iterator         = random_access_iterator<stacktrace_entry>;
      using iterator               = const_iterator;
      using reverse_iterator       = rsl::reverse_iterator<iterator>;
      using reverse_const_iterator = rsl::reverse_iterator<const_iterator>;
      using difference_type        = ptrdiff;
      using size_type              = card32;
      using allocator_type         = Allocator;

      basic_stacktrace()
          : m_entries()
          , m_size(0)
      {
      }
      explicit basic_stacktrace(const allocator_type& /*unused*/)
          : m_entries()
          , m_size(0)
      {
      }
      basic_stacktrace(const basic_stacktrace& other) = default;
      basic_stacktrace(basic_stacktrace&& other)      = default;
      basic_stacktrace(const basic_stacktrace& other, const allocator_type& /*unused*/)
          : basic_stacktrace(other)
      {
      }
      basic_stacktrace(basic_stacktrace&& other, const allocator_type& /*unused*/)
          : basic_stacktrace(rsl::move(other))
      {
      }

      ~basic_stacktrace() = default;

      basic_stacktrace& operator=(const basic_stacktrace& other)
      {
        m_entries = other.m_entries;
        m_size    = other.m_size;
        return *this;
      }
      basic_stacktrace& operator=(basic_stacktrace&& other)
      {
        m_entries = other.m_entries;
        m_size    = other.m_size;
        return *this;
      }

      static basic_stacktrace<allocator_type> current(const allocator_type& /*unused*/ = allocator_type())
      {
        return basic_stacktrace<allocator_type>(internal::stack_trace(0, s_max_entries));
      }
      static basic_stacktrace<allocator_type> current(size_type skip, const allocator_type& /*unused*/ = allocator_type())
      {
        return basic_stacktrace<allocator_type>(internal::stack_trace(skip, s_max_entries));
      }
      static basic_stacktrace<allocator_type> current(size_type skip, size_type maxDepth, const allocator_type& /*unused*/ = allocator_type())
      {
        return basic_stacktrace<allocator_type>(internal::stack_trace(skip, maxDepth));
      }

      // const allocator_type& get_allocator();

      iterator begin()
      {
        return m_entries.begin();
      }
      const_iterator begin() const
      {
        return m_entries.begin();
      }
      const_iterator cbegin() const
      {
        return m_entries.cbegin();
      }

      iterator end()
      {
        return m_entries.end();
      }
      const_iterator end() const
      {
        return m_entries.end();
      }
      const_iterator cend() const
      {
        return m_entries.cend();
      }

      reverse_iterator rbegin()
      {
        return m_entries.rbegin();
      }
      reverse_const_iterator rbegin() const
      {
        return m_entries.rbegin();
      }
      reverse_const_iterator crbegin() const
      {
        return m_entries.crbegin();
      }

      reverse_iterator rend()
      {
        return m_entries.rend();
      }
      reverse_const_iterator rend() const
      {
        return m_entries.rend();
      }
      reverse_const_iterator crend() const
      {
        return m_entries.crend();
      }

      bool empty() const
      {
        return m_entries.front().operator bool();
      }
      size_type size() const
      {
        return m_size;
      }
      size_type max_size() const
      {
        return m_entries.max_size();
      }

      const_reference operator[](size_type pos) const
      {
        return m_entries[pos];
      }
      const_reference at(size_type pos) const
      {
        RSL_ASSERT_X(pos < m_size, "pos out of bounds!");
        return m_entries[pos];
      }

      void swap(basic_stacktrace& other)
      {
        basic_stacktrace tmp = *this;
        *this                = other;
        other                = tmp;
      }

      constexpr static card32 max_entries()
      {
        return s_max_entries;
      }

    private:
      explicit basic_stacktrace(const rsl::array<stacktrace_entry, max_entries()>& entries)
          : m_entries(entries)
          , m_size(0)
      {
        for(const stacktrace_entry& entry: m_entries)
        {
          if(entry)
          {
            ++m_size;
          }
          else
          {
            break;
          }
        }
      }

    private:
      rsl::array<stacktrace_entry, s_max_entries> m_entries;
      card32 m_size;
    };

    template <typename Allocator>
    rsl::string to_string(const basic_stacktrace<Allocator>& trace) // NOLINT(misc-no-recursion)
    {
      rsl::string result;

      for(card32 i = 0; i < trace.size(); ++i)
      {
        result += trace[i].description();
        result += "\n";
      }

      return result;
    }

    template <typename Allocator>
    void swap(const basic_stacktrace<Allocator>& lhs, const basic_stacktrace<Allocator>& rhs)
    {
      return lhs.swap(rhs);
    }

    using stacktrace = basic_stacktrace<allocator>;

    template <typename Char, typename Traits, typename Allocator>
    rsl::basic_ostream<Char, Traits>& operator<<(rsl::basic_ostream<Char, Traits>& os, const basic_stacktrace<Allocator>& trace) // NOLINT(misc-no-recursion)
    {
      os << to_string(trace);
      return os;
    }

    template <typename Allocator>
    struct formatter<basic_stacktrace<Allocator>>
    {
      auto parse(format_parse_context& ctx) const -> decltype(ctx.begin()) // NOLINT(readability-convert-member-functions-to-static)
      {
        return ctx.begin();
      }

      template <typename FormatContext>
      auto format(const basic_stacktrace<Allocator>& stacktrace, FormatContext& ctx) -> decltype(ctx.out())
      {
        return format_to(ctx.out(), "{}", to_string(stacktrace));
      }
    };
  } // namespace v1
} // namespace rsl
