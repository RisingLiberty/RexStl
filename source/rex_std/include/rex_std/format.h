/*
  Formatting library for C++

  Copyright (c) 2012 - present, Victor Zverovich

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

  --- Optional exception to the license ---

  As an exception, if, as a result of your compiling your source code, portions
  of this Software are embedded into a machine-executable object form of such
  source code, you may redistribute such embedded portions in such object form
  without including the above copyright and permission notices.
 */

// NOLINTBEGIN(fuchsia-trailing-return, hicpp-signed-bitwise, misc-no-recursion)

#pragma once

#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wheader-guard"
#endif

#ifndef FMT_FORMAT_H_
  #define FMT_FORMAT_H

  #include "rex_std/bonus/iterator/iter_val.h"
  #include "rex_std/bonus/memory/typed_allocator.h"
  #include "rex_std/bonus/string.h"
  #include "rex_std/internal/algorithm/copy.h"
  #include "rex_std/internal/iterator/begin.h"
  #include "rex_std/internal/iterator/end.h"
  #include "rex_std/internal/math/ceil.h"
  #include "rex_std/internal/math/is_nan.h"
  #include "rex_std/internal/memory/memcpy.h"
  #include "rex_std/internal/memory/memset.h"
  #include "rex_std/internal/memory/shared_ptr.h"
  #include "rex_std/internal/memory/unique_ptr.h"
  #include "rex_std/internal/string/basic_string.h"
  #include "rex_std/internal/type_traits/is_floating_point.h"
  #include "rex_std/internal/type_traits/is_integral.h"
  #include "rex_std/internal/type_traits/is_same.h"
  #include "rex_std/internal/utility/declval.h"
  #include "rex_std/limits.h"

  #include <cmath>        // std::signbit
  #include <cstdint>      // uint32
  #include <memory>       // std::uninitialized_copy
  #include <stdexcept>    // std::runtime_error
  #include <system_error> // std::system_error

  #ifdef __cpp_lib_bit_cast
    #include <bit> // rsl::bitcast
  #endif

  #include "rex_std/internal/format/core.h"

  #if FMT_GCC_VERSION
    #define FMT_GCC_VISIBILITY_HIDDEN __attribute__((visibility("hidden")))
  #else
    #define FMT_GCC_VISIBILITY_HIDDEN
  #endif

  #ifdef __NVCC__
    #define FMT_CUDA_VERSION (__CUDACC_VER_MAJOR__ * 100 + __CUDACC_VER_MINOR__)
  #else
    #define FMT_CUDA_VERSION 0
  #endif

  #ifdef __has_builtin
    #define FMT_HAS_BUILTIN(x) __has_builtin(x)
  #else
    #define FMT_HAS_BUILTIN(x) 0
  #endif

  #if FMT_GCC_VERSION || FMT_CLANG_VERSION
    #define FMT_NOINLINE __attribute__((noinline))
  #else
    #define FMT_NOINLINE
  #endif

  #if FMT_MSC_VERSION
    #define FMT_MSC_DEFAULT = default
  #else
    #define FMT_MSC_DEFAULT
  #endif

  #ifndef FMT_THROW
    #if FMT_EXCEPTIONS
      #if FMT_MSC_VERSION || defined(__NVCC__)
namespace rsl
{
  inline namespace v1
  {
    namespace detail
    {
      template <typename Exception>
      inline void do_throw(const Exception& x)
      {
        // Silence unreachable code warnings in MSVC and NVCC because these
        // are nearly impossible to fix in a generic code.
        volatile bool b = true;
        if(b)
          throw x;
      }
    } // namespace detail
  }   // namespace v1
} // namespace rsl
        #define FMT_THROW(x) detail::do_throw(x)
      #else
        #define FMT_THROW(x) throw x
      #endif
    #else
      #define FMT_THROW(x)                                                                                                                                                                                                                               \
        do                                                                                                                                                                                                                                               \
        {                                                                                                                                                                                                                                                \
          FMT_ASSERT(false, (x).what());                                                                                                                                                                                                                 \
        } while(false)
    #endif
  #endif

  #if FMT_EXCEPTIONS
    #define FMT_TRY      try
    #define FMT_CATCH(x) catch(x)
  #else
    #define FMT_TRY      if(true)
    #define FMT_CATCH(x) if(false)
  #endif

  #ifndef FMT_MAYBE_UNUSED
    #if FMT_HAS_CPP17_ATTRIBUTE(maybe_unused)
      #define FMT_MAYBE_UNUSED [[maybe_unused]]
    #else
      #define FMT_MAYBE_UNUSED
    #endif
  #endif

  #ifndef FMT_USE_USER_DEFINED_LITERALS
// EDG based compilers (Intel, NVIDIA, Elbrus, etc), GCC and MSVC support UDLs.
    #if(FMT_HAS_FEATURE(cxx_user_literals) || FMT_GCC_VERSION >= 407 || FMT_MSC_VERSION >= 1900) && (!defined(__EDG_VERSION__) || __EDG_VERSION__ >= /* UDL feature */ 480)
      #define FMT_USE_USER_DEFINED_LITERALS 1
    #else
      #define FMT_USE_USER_DEFINED_LITERALS 0
    #endif
  #endif

  // Defining FMT_REDUCE_INT_INSTANTIATIONS to 1, will reduce the number of
  // integer formatter template instantiations to just one by only using the
  // largest integer type. This results in a reduction in binary size but will
  // cause a decrease in integer formatting performance.
  #if !defined(FMT_REDUCE_INT_INSTANTIATIONS)
    #define FMT_REDUCE_INT_INSTANTIATIONS 0
  #endif

  // __builtin_clz is broken in clang with Microsoft CodeGen:
  // https://github.com/fmtlib/fmt/issues/519.
  #if !FMT_MSC_VERSION
    #if FMT_HAS_BUILTIN(__builtin_clz) || FMT_GCC_VERSION || FMT_ICC_VERSION
      #define FMT_BUILTIN_CLZ(n) __builtin_clz(n)
    #endif
    #if FMT_HAS_BUILTIN(__builtin_clzll) || FMT_GCC_VERSION || FMT_ICC_VERSION
      #define FMT_BUILTIN_CLZLL(n) __builtin_clzll(n)
    #endif
  #endif

  // __builtin_ctz is broken in Intel Compiler Classic on Windows:
  // https://github.com/fmtlib/fmt/issues/2510.
  #ifndef __ICL
    #if FMT_HAS_BUILTIN(__builtin_ctz) || FMT_GCC_VERSION || FMT_ICC_VERSION || defined(__NVCOMPILER)
      #define FMT_BUILTIN_CTZ(n) __builtin_ctz(n)
    #endif
    #if FMT_HAS_BUILTIN(__builtin_ctzll) || FMT_GCC_VERSION || FMT_ICC_VERSION || defined(__NVCOMPILER)
      #define FMT_BUILTIN_CTZLL(n) __builtin_ctzll(n)
    #endif
  #endif

  #if FMT_MSC_VERSION
    #include <intrin.h> // _BitScanReverse[64], _BitScanForward[64], _umul128
  #endif

  // Some compilers masquerade as both MSVC and GCC-likes or otherwise support
  // __builtin_clz and __builtin_clzll, so only define FMT_BUILTIN_CLZ using the
  // MSVC intrinsics if the clz and clzll builtins are not available.
  #if FMT_MSC_VERSION && !defined(FMT_BUILTIN_CLZLL) && !defined(FMT_BUILTIN_CTZLL)
namespace rsl
{
  inline namespace v1
  {
    namespace detail
    {
    // Avoid Clang with Microsoft CodeGen's -Wunknown-pragmas warning.
    #if !defined(__clang__)
      #pragma intrinsic(_BitScanForward)
      #pragma intrinsic(_BitScanReverse)
      #if defined(_WIN64)
        #pragma intrinsic(_BitScanForward64)
        #pragma intrinsic(_BitScanReverse64)
      #endif
    #endif

      inline auto clz(uint32 x) -> int
      {
        unsigned long r = 0;
        _BitScanReverse(&r, x);
        FMT_ASSERT(x != 0, "");
        // Static analysis complains about using uninitialized data
        // "r", but the only way that can happen is if "x" is 0,
        // which the callers guarantee to not happen.
        FMT_MSC_WARNING(suppress : 6102)
        return 31 ^ static_cast<int>(r);
      }
    #define FMT_BUILTIN_CLZ(n) detail::clz(n)

      inline auto clzll(uint64 x) -> int
      {
        unsigned long r = 0;
    #ifdef _WIN64
        _BitScanReverse64(&r, x);
    #else
        // Scan the high 32 bits.
        if(_BitScanReverse(&r, static_cast<uint32>(x >> 32)))
          return 63 ^ (r + 32);
        // Scan the low 32 bits.
        _BitScanReverse(&r, static_cast<uint32>(x));
    #endif
        FMT_ASSERT(x != 0, "");
        FMT_MSC_WARNING(suppress : 6102) // Suppress a bogus static analysis warning.
        return 63 ^ static_cast<int>(r);
      }
    #define FMT_BUILTIN_CLZLL(n) detail::clzll(n)

      inline auto ctz(uint32 x) -> int
      {
        unsigned long r = 0;
        _BitScanForward(&r, x);
        FMT_ASSERT(x != 0, "");
        FMT_MSC_WARNING(suppress : 6102) // Suppress a bogus static analysis warning.
        return static_cast<int>(r);
      }
    #define FMT_BUILTIN_CTZ(n) detail::ctz(n)

      inline auto ctzll(uint64 x) -> int
      {
        unsigned long r = 0;
        FMT_ASSERT(x != 0, "");
        FMT_MSC_WARNING(suppress : 6102) // Suppress a bogus static analysis warning.
    #ifdef _WIN64
        _BitScanForward64(&r, x);
    #else
        // Scan the low 32 bits.
        if(_BitScanForward(&r, static_cast<uint32>(x)))
          return static_cast<int>(r);
        // Scan the high 32 bits.
        _BitScanForward(&r, static_cast<uint32>(x >> 32));
        r += 32;
    #endif
        return static_cast<int>(r);
      }
    #define FMT_BUILTIN_CTZLL(n) detail::ctzll(n)
    } // namespace detail
  }   // namespace v1
} // namespace rsl
  #endif

namespace rsl
{
  inline namespace v1
  {
    namespace detail
    {

      FMT_CONSTEXPR inline void abort_fuzzing_if(bool condition)
      {
        ignore_unused(condition);
  #ifdef FMT_FUZZ
        if(condition)
          throw std::runtime_error("fuzzing limit reached");
  #endif
      }

      template <typename CharT, CharT... C>
      struct basic_string_literal
      {
        static constexpr CharT value[sizeof...(C)] = {C...}; // NOLINT(modernize-avoid-c-arrays)
        constexpr operator basic_string_view<CharT>() const  // NOLINT(google-explicit-constructor)
        {
          return {value, sizeof...(C)};
        }
      };

  #if FMT_CPLUSPLUS < 201703L
      template <typename CharT, CharT... C>
      constexpr CharT string_literal<CharT, C...>::value[sizeof...(C)];
  #endif

      template <typename Streambuf>
      class formatbuf : public Streambuf
      {
      private:
        using char_type   = typename Streambuf::char_type;
        using streamsize  = decltype(rsl::declval<Streambuf>().sputn(nullptr, 0));
        using int_type    = typename Streambuf::int_type;
        using traits_type = typename Streambuf::traits_type;

        buffer<char_type>& m_buffer; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)

      public:
        explicit formatbuf(buffer<char_type>& buf)
            : m_buffer(buf)
        {
        }

      protected:
        // The put area is always empty. This makes the implementation simpler and has
        // the advantage that the streambuf and the buffer are always in sync and
        // sputc never writes into uninitialized memory. A disadvantage is that each
        // call to sputc always results in a (virtual) call to overflow. There is no
        // disadvantage here for sputn since this always results in a call to xsputn.

        auto overflow(int_type ch) -> int_type override
        {
          if(!traits_type::eq_int_type(ch, traits_type::eof()))
            m_buffer.push_back(static_cast<char_type>(ch));
          return ch;
        }

        auto xsputn(const char_type* s, streamsize count) -> streamsize override
        {
          m_buffer.append(s, s + count);
          return count;
        }
      };

      // Implementation of rsl::bit_cast for pre-C++20.
      template <typename To, typename From, FMT_ENABLE_IF(sizeof(To) == sizeof(From))>
      FMT_CONSTEXPR20 auto bit_cast(const From& from) -> To
      {
  #ifdef __cpp_lib_bit_cast
        if(is_constant_evaluated())
          return std::bit_cast<To>(from);
  #endif
        auto to = To();
        // The cast suppresses a bogus -Wclass-memaccess on GCC.
        rsl::memcpy(static_cast<void*>(&to), &from, sizeof(to));
        return to;
      }

      inline auto is_big_endian() -> bool
      {
  #ifdef _WIN32
        return false;
  #elif defined(__BIG_ENDIAN__)
        return true;
  #elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__)
        return __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__;
  #else
        struct bytes
        {
          char data[sizeof(int)];
        };
        return bit_cast<bytes>(1).data[0] == 0;
  #endif
      }

      class uint128_fallback
      {
      private:
        uint64 m_lo, m_hi;

        friend uint128_fallback umul128(uint64 x, uint64 y) noexcept;

      public:
        constexpr uint128_fallback(uint64 hi, uint64 lo)
            : m_lo(lo)
            , m_hi(hi)
        {
        }
        constexpr uint128_fallback(uint64 value = 0) // NOLINT(google-explicit-constructor)
            : m_lo(value)
            , m_hi(0)
        {
        }

        constexpr uint64 high() const noexcept
        {
          return m_hi;
        }
        constexpr uint64 low() const noexcept
        {
          return m_lo;
        }

        template <typename T, FMT_ENABLE_IF(rsl::is_integral<T>::value)>
        constexpr explicit operator T() const
        {
          return static_cast<T>(m_lo);
        }

        friend constexpr auto operator==(const uint128_fallback& lhs, const uint128_fallback& rhs) -> bool
        {
          return lhs.m_hi == rhs.m_hi && lhs.m_lo == rhs.m_lo;
        }
        friend constexpr auto operator!=(const uint128_fallback& lhs, const uint128_fallback& rhs) -> bool
        {
          return !(lhs == rhs);
        }
        friend constexpr auto operator>(const uint128_fallback& lhs, const uint128_fallback& rhs) -> bool
        {
          return lhs.m_hi != rhs.m_hi ? lhs.m_hi > rhs.m_hi : lhs.m_lo > rhs.m_lo;
        }
        friend constexpr auto operator|(const uint128_fallback& lhs, const uint128_fallback& rhs) -> uint128_fallback
        {
          return {lhs.m_hi | rhs.m_hi, lhs.m_lo | rhs.m_lo};
        }
        friend constexpr auto operator&(const uint128_fallback& lhs, const uint128_fallback& rhs) -> uint128_fallback
        {
          return {lhs.m_hi & rhs.m_hi, lhs.m_lo & rhs.m_lo};
        }
        friend auto operator+(const uint128_fallback& lhs, const uint128_fallback& rhs) -> uint128_fallback
        {
          auto result = uint128_fallback(lhs);
          result += rhs;
          return result;
        }
        friend auto operator*(const uint128_fallback& lhs, uint32 rhs) -> uint128_fallback
        {
          FMT_ASSERT(lhs.m_hi == 0, "");
          const uint64 hi     = (lhs.m_lo >> 32) * rhs;
          const uint64 lo     = (lhs.m_lo & ~uint32()) * rhs;
          const uint64 new_lo = (hi << 32) + lo;
          return {(hi >> 32) + (new_lo < lo ? 1 : 0), new_lo};
        }
        friend auto operator-(const uint128_fallback& lhs, uint64 rhs) -> uint128_fallback
        {
          return {lhs.m_hi - (lhs.m_lo < rhs ? 1 : 0), lhs.m_lo - rhs};
        }
        FMT_CONSTEXPR auto operator>>(int shift) const -> uint128_fallback // NOLINT(misc-no-recursion)
        {
          if(shift == 64)
            return {0, m_hi};
          if(shift > 64)
            return uint128_fallback(0, m_hi) >> (shift - 64);
          return {m_hi >> shift, (m_hi << (64 - shift)) | (m_lo >> shift)};
        }
        FMT_CONSTEXPR auto operator<<(int shift) const -> uint128_fallback // NOLINT(misc-no-recursion)
        {
          if(shift == 64)
            return {m_lo, 0};
          if(shift > 64)
            return uint128_fallback(m_lo, 0) << (shift - 64);
          return {m_hi << shift | (m_lo >> (64 - shift)), (m_lo << shift)};
        }
        FMT_CONSTEXPR auto operator>>=(int shift) -> uint128_fallback&
        {
          return *this = *this >> shift;
        }
        FMT_CONSTEXPR void operator+=(uint128_fallback n)
        {
          const uint64 new_lo = m_lo + n.m_lo;
          const uint64 new_hi = m_hi + n.m_hi + (new_lo < m_lo ? 1 : 0);
          FMT_ASSERT(new_hi >= m_hi, "");
          m_lo = new_lo;
          m_hi = new_hi;
        }

        FMT_CONSTEXPR20 uint128_fallback& operator+=(uint64 n) noexcept
        {
          if(is_constant_evaluated())
          {
            m_lo += n;
            m_hi += (m_lo < n ? 1 : 0);
            return *this;
          }
  #if FMT_HAS_BUILTIN(__builtin_addcll) && !defined(__ibmxl__)
          unsigned long long carry = 0;
          m_lo                     = __builtin_addcll(m_lo, n, 0, &carry);
          m_hi += carry;
  #elif FMT_HAS_BUILTIN(__builtin_ia32_addcarryx_u64) && !defined(__ibmxl__)
          unsigned long long result;
          auto carry = __builtin_ia32_addcarryx_u64(0, lo_, n, &result);
          lo_        = result;
          hi_ += carry;
  #elif defined(_MSC_VER) && defined(_M_X64)
          auto carry = _addcarry_u64(0, m_lo, n, &m_lo);
          _addcarry_u64(carry, m_hi, 0, &m_hi);
  #else
          lo_ += n;
          hi_ += (lo_ < n ? 1 : 0);
  #endif
          return *this;
        }
      };

      using uint128_t = conditional_t<FMT_USE_INT128, uint128_opt, uint128_fallback>;

  #ifdef UINTPTR_MAX
      using uintptr_t = ::uintptr_t;
  #else
      using uintptr_t = uint128_t;
  #endif

      // Returns the largest possible value for type T. Same as
      // rsl::numeric_limits<T>::max() but shorter and not affected by the max macro.
      template <typename T>
      constexpr auto max_value() -> T
      {
        return (rsl::numeric_limits<T>::max)();
      }
      template <typename T>
      constexpr auto num_bits() -> int
      {
        return rsl::numeric_limits<T>::digits;
      }
      // rsl::numeric_limits<T>::digits may return 0 for 128-bit ints.
      template <>
      constexpr auto num_bits<int128_opt>() -> int
      {
        return 128;
      }
      template <>
      constexpr auto num_bits<uint128_t>() -> int
      {
        return 128;
      }

      // A heterogeneous bit_cast used for converting 96-bit long double to uint128_t
      // and 128-bit pointers to uint128_fallback.
      template <typename To, typename From, FMT_ENABLE_IF(sizeof(To) > sizeof(From))>
      inline auto bit_cast(const From& from) -> To
      {
        constexpr auto size = static_cast<int>(sizeof(From) / sizeof(unsigned));
        struct data_t
        {
          unsigned value[static_cast<unsigned>(size)];
        } data      = bit_cast<data_t>(from);
        auto result = To();
        if(const_check(is_big_endian()))
        {
          for(int i = 0; i < size; ++i)
            result = (result << num_bits<unsigned>()) | data.value[i];
        }
        else
        {
          for(int i = size - 1; i >= 0; --i)
            result = (result << num_bits<unsigned>()) | data.value[i];
        }
        return result;
      }

      FMT_INLINE void assume(bool condition)
      {
        (void)condition;
  #if FMT_HAS_BUILTIN(__builtin_assume) && !FMT_ICC_VERSION
        __builtin_assume(condition);
  #endif
      }

      // An approximation of iterator_t for pre-C++20 systems.
      template <typename T>
      using iterator_t = decltype(rsl::begin(rsl::declval<T&>()));
      template <typename T>
      using sentinel_t = decltype(rsl::end(rsl::declval<T&>()));

      // A workaround for rsl::string not having mutable data() until C++17.
      template <typename Char>
      inline auto get_data(rsl::basic_string<Char, rsl::char_traits<Char>, rsl::allocator>& s) -> Char*
      {
        return &s[0];
      }
      template <typename Container>
      inline auto get_data(Container& c) -> typename Container::value_type*
      {
        return c.data();
      }

  #if defined(_SECURE_SCL) && _SECURE_SCL
      // Make a checked iterator to avoid MSVC warnings.
      template <typename T>
      using checked_ptr = stdext::checked_array_iterator<T*>;
      template <typename T>
      constexpr auto make_checked(T* p, count_t size) -> checked_ptr<T>
      {
        return {p, static_cast<size_t>(size)};
      }
  #else
      template <typename T>
      using checked_ptr = T*;
      template <typename T>
      constexpr auto make_checked(T* p, count_t /*unused*/) -> T*
      {
        return p;
      }
  #endif

      // Attempts to reserve space for n extra characters in the output range.
      // Returns a pointer to the reserved range or a reference to it.
      template <typename Container, FMT_ENABLE_IF(is_contiguous<Container>::value)>
  #if FMT_CLANG_VERSION >= 307 && !FMT_ICC_VERSION
      __attribute__((no_sanitize("undefined")))
  #endif
      inline auto
          reserve(rsl::back_insert_iterator<Container> it, count_t n) -> checked_ptr<typename Container::value_type>
      {
        Container& c = get_container(it);
        count_t size = c.size();
        c.resize(size + n);
        return make_checked(get_data(c) + size, n);
      }

      template <typename T>
      inline auto reserve(buffer_appender<T> it, count_t n) -> buffer_appender<T>
      {
        buffer<T>& buf = get_container(it);
        buf.try_reserve(buf.size() + n);
        return it;
      }

      template <typename Iterator>
      constexpr auto reserve(Iterator& it, count_t /*unused*/) -> Iterator&
      {
        return it;
      }

      template <typename OutputIt>
      using reserve_iterator = remove_reference_t<decltype(reserve(rsl::declval<OutputIt&>(), 0))>;

      template <typename T, typename OutputIt>
      constexpr auto to_pointer(OutputIt /*unused*/, count_t /*unused*/) -> T*
      {
        return nullptr;
      }
      template <typename T>
      auto to_pointer(buffer_appender<T> it, count_t n) -> T*
      {
        buffer<T>& buf = get_container(it);
        auto size      = buf.size();
        if(buf.capacity() < size + n)
          return nullptr;
        buf.try_resize(size + n);
        return buf.data() + size;
      }

      template <typename Container, FMT_ENABLE_IF(is_contiguous<Container>::value)>
      inline auto base_iterator(rsl::back_insert_iterator<Container>& it, checked_ptr<typename Container::value_type> /*unused*/) -> rsl::back_insert_iterator<Container>
      {
        return it;
      }

      template <typename Iterator>
      constexpr auto base_iterator(Iterator /*unused*/, Iterator it) -> Iterator
      {
        return it;
      }

      // <algorithm> is spectacularly slow to compile in C++20 so use a simple fill_n
      // instead (#1998).
      template <typename OutputIt, typename Size, typename T>
      FMT_CONSTEXPR auto fill_n(OutputIt out, Size count, const T& value) -> OutputIt
      {
        for(Size i = 0; i < count; ++i)
          *out++ = value;
        return out;
      }
      template <typename T, typename Size>
      FMT_CONSTEXPR20 auto fill_n(T* out, Size count, char value) -> T*
      {
        if(is_constant_evaluated())
        {
          return fill_n<T*, Size, T>(out, count, value);
        }
        rsl::memset(out, value, to_unsigned(count));
        return out + count;
      }

  #ifdef __cpp_char8_t
      using char8_type = char8_t;
  #else
      enum char8_type : unsigned char
      {
      };
  #endif

      template <typename OutChar, typename InputIt, typename OutputIt>
      FMT_CONSTEXPR FMT_NOINLINE auto copy_str_noinline(InputIt begin, InputIt end, OutputIt out) -> OutputIt
      {
        return copy_str<OutChar>(begin, end, out);
      }

      // A public domain branchless UTF-8 decoder by Christopher Wellons:
      // https://github.com/skeeto/branchless-utf8
      /* Decode the next character, c, from s, reporting errors in e.
       *
       * Since this is a branchless decoder, four bytes will be read from the
       * buffer regardless of the actual length of the next character. This
       * means the buffer _must_ have at least three bytes of zero padding
       * following the end of the data stream.
       *
       * Errors are reported in e, which will be non-zero if the parsed
       * character was somehow invalid: invalid byte sequence, non-canonical
       * encoding, or a surrogate half.
       *
       * The function returns a pointer to the next character. When an error
       * occurs, this pointer will be a guess that depends on the particular
       * error, but it will always advance at least one byte.
       */
      FMT_CONSTEXPR inline auto utf8_decode(const char* s, uint32* c, int* err) -> const char*
      {
        constexpr const int prefix_masks[] = {0x00, 0x80, 0xe0, 0xf0, 0xf8}; // NOLINT(modernize-avoid-c-arrays)
        constexpr const int masks[]        = {0x00, 0x7f, 0x1f, 0x0f, 0x07}; // NOLINT(modernize-avoid-c-arrays)
        constexpr const uint32 mins[]      = {4194304, 0, 128, 2048, 65536}; // NOLINT(modernize-avoid-c-arrays)
        constexpr const int shiftc[]       = {0, 18, 12, 6, 0};              // NOLINT(modernize-avoid-c-arrays)
        constexpr const int shifte[]       = {0, 6, 4, 2, 0};                // NOLINT(modernize-avoid-c-arrays)

        const int len    = code_point_length(s);
        const char* next = s + len;

        // Assume a four-byte character and load four bytes. Unused bits are
        // shifted out.
        *c = uint32(s[0] & masks[len]) << 18; // NOLINT(google-readability-casting)
        *c |= uint32(s[1] & 0x3f) << 12;      // NOLINT(google-readability-casting)
        *c |= uint32(s[2] & 0x3f) << 6;       // NOLINT(google-readability-casting)
        *c |= uint32(s[3] & 0x3f) << 0;       // NOLINT(google-readability-casting)
        *c >>= shiftc[len];

        // Accumulate the various error conditions.
        using uchar = unsigned char;
        *err        = (*c < mins[len]) << 6; // NOLINT(readability-implicit-bool-conversion,-warnings-as-errors) // non-canonical encoding
        *err |= ((*c >> 11) == 0x1b) << 7;   // NOLINT(readability-implicit-bool-conversion,-warnings-as-errors) // surrogate half?
        *err |= (*c > 0x10FFFF) << 8;        // NOLINT(readability-implicit-bool-conversion,-warnings-as-errors) // out of range?
        *err |= (uchar(s[1]) & 0xc0) >> 2;   // NOLINT(google-readability-casting)
        *err |= (uchar(s[2]) & 0xc0) >> 4;   // NOLINT(google-readability-casting)
        *err |= uchar(s[3]) >> 6;            // NOLINT(google-readability-casting)
        *err ^= 0x2a;                        // top two bits of each tail byte correct?
        *err >>= shifte[len];
        *err |= ((uchar(s[0]) & prefix_masks[len]) != uchar((prefix_masks[len] << 1) & 0xFF)); // NOLINT(google-readability-casting, readability-implicit-bool-conversion) // first byte correct?

        return next;
      }

      constexpr uint32 invalid_code_point = ~uint32();

      // Invokes f(cp, sv) for every code point cp in s with sv being the string view
      // corresponding to the code point. cp is invalid_code_point on error.
      template <typename F>
      FMT_CONSTEXPR void for_each_codepoint(string_view s, F f)
      {
        auto decode = [f](const char* bufPtr, const char* ptr)
        {
          auto cp           = uint32();
          auto error        = 0;
          const auto* end   = utf8_decode(bufPtr, &cp, &error);
          bool const result = f(error ? invalid_code_point : cp, string_view(ptr, error ? 1 : to_unsigned(static_cast<count_t>(end - bufPtr)))); // NOLINT(cppcoreguidelines-narrowing-conversions)
          return result ? (error ? bufPtr + 1 : end) : nullptr;
        };
        const auto* p            = s.data();
        const count_t block_size = 4; // utf8_decode always reads blocks of 4 chars.
        if(s.size() >= block_size)
        {
          for(const auto* end = p + s.size() - block_size + 1; p < end;)
          {
            p = decode(p, p);
            if(!p)
              return;
          }
        }
        if(auto num_chars_left = s.data() + s.size() - p)
        {
          char buf[2 * block_size - 1] = {}; // NOLINT(modernize-avoid-c-arrays)
          copy_str<char>(p, p + num_chars_left, buf);
          const char* buf_ptr = buf;
          do
          {
            auto end = decode(buf_ptr, p);
            if(!end)
              return;
            p += end - buf_ptr;
            buf_ptr = end;
          } while(buf_ptr - buf < num_chars_left);
        }
      }

      template <typename Char>
      inline auto compute_width(basic_string_view<Char> s) -> count_t
      {
        return s.size();
      }

      // Computes approximate display width of a UTF-8 string.
      FMT_CONSTEXPR inline count_t compute_width(string_view s)
      {
        count_t num_code_points = 0;
        // It is not a lambda for compatibility with C++14.
        struct count_code_points
        {
          count_t* count;
          FMT_CONSTEXPR auto operator()(uint32 cp, string_view /*unused*/) const -> bool
          {
            *count += detail::to_unsigned(1 + (cp >= 0x1100 && (cp <= 0x115f || // NOLINT(cppcoreguidelines-narrowing-conversions, readability-implicit-bool-conversion) Hangul Jamo init. consonants
                                                                cp == 0x2329 || // LEFT-POINTING ANGLE BRACKET
                                                                cp == 0x232a || // RIGHT-POINTING ANGLE BRACKET
                                                                // CJK ... Yi except IDEOGRAPHIC HALF FILL SPACE:
                                                                (cp >= 0x2e80 && cp <= 0xa4cf && cp != 0x303f) || (cp >= 0xac00 && cp <= 0xd7a3) || // Hangul Syllables
                                                                (cp >= 0xf900 && cp <= 0xfaff) ||                                                   // CJK Compatibility Ideographs
                                                                (cp >= 0xfe10 && cp <= 0xfe19) ||                                                   // Vertical Forms
                                                                (cp >= 0xfe30 && cp <= 0xfe6f) ||                                                   // CJK Compatibility Forms
                                                                (cp >= 0xff00 && cp <= 0xff60) ||                                                   // Fullwidth Forms
                                                                (cp >= 0xffe0 && cp <= 0xffe6) ||                                                   // Fullwidth Forms
                                                                (cp >= 0x20000 && cp <= 0x2fffd) ||                                                 // CJK
                                                                (cp >= 0x30000 && cp <= 0x3fffd) ||
                                                                // Miscellaneous Symbols and Pictographs + Emoticons:
                                                                (cp >= 0x1f300 && cp <= 0x1f64f) ||
                                                                // Supplemental Symbols and Pictographs:
                                                                (cp >= 0x1f900 && cp <= 0x1f9ff))));
            return true;
          }
        };
        for_each_codepoint(s, count_code_points {&num_code_points});
        return num_code_points;
      }

      inline auto compute_width(basic_string_view<char8_type> s) -> count_t
      {
        return compute_width(string_view(reinterpret_cast<const char*>(s.data()), s.size())); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
      }

      template <typename Char>
      inline auto code_point_index(basic_string_view<Char> s, count_t n) -> count_t
      {
        count_t size = s.size();
        return n < size ? n : size;
      }

      // Calculates the index of the nth code point in a UTF-8 string.
      inline auto code_point_index(string_view s, count_t n) -> count_t
      {
        const char* data        = s.data();
        count_t num_code_points = 0;
        for(count_t i = 0, size = s.size(); i != size; ++i)
        {
          if((data[i] & 0xc0) != 0x80 && ++num_code_points > n)
            return i;
        }
        return s.size();
      }

      inline auto code_point_index(basic_string_view<char8_type> s, count_t n) -> count_t
      {
        return code_point_index(string_view(reinterpret_cast<const char*>(s.data()), s.size()), n); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
      }

  #ifndef FMT_USE_FLOAT128
    #ifdef __SIZEOF_FLOAT128__
      #define FMT_USE_FLOAT128 1
    #else
      #define FMT_USE_FLOAT128 0
    #endif
  #endif
  #if FMT_USE_FLOAT128
      using float128 = __float128;
  #else
      using float128 = void;
  #endif
      template <typename T>
      using is_float128 = rsl::is_same<T, float128>;

      template <typename T>
      using is_floating_point = bool_constant<rsl::is_floating_point<T>::value || is_float128<T>::value>;

      template <typename T, bool = rsl::is_floating_point<T>::value>
      struct is_fast_float : bool_constant<rsl::numeric_limits<T>::is_iec559 && sizeof(T) <= sizeof(double)>
      {
      };
      template <typename T>
      struct is_fast_float<T, false> : rsl::false_type
      {
      };

      template <typename T>
      using is_double_double = bool_constant<rsl::numeric_limits<T>::digits == 106>;

  #ifndef FMT_USE_FULL_CACHE_DRAGONBOX
    #define FMT_USE_FULL_CACHE_DRAGONBOX 0
  #endif

      template <typename T>
      template <typename U>
      void buffer<T>::append(const U* begin, const U* end)
      {
        while(begin != end)
        {
          auto count = to_unsigned(static_cast<count_t>(end - begin));
          try_reserve(m_size + count);
          auto free_cap = m_capacity - m_size;
          if(free_cap < static_cast<int>(count))
            count = free_cap;
          std::uninitialized_copy_n(begin, count, make_checked(m_ptr + m_size, count));
          m_size += count;
          begin += count;
        }
      }

      template <typename T, typename Enable = void>
      struct is_locale : rsl::false_type
      {
      };
      template <typename T>
      struct is_locale<T, void_t<decltype(T::classic())>> : rsl::true_type
      {
      };
    } // namespace detail

    FMT_MODULE_EXPORT_BEGIN

    // The number of characters to store in the basic_memory_buffer object itself
    // to avoid dynamic memory allocation.
    enum
    {
      inline_buffer_size = 500
    };

    /**
      \rst
      A dynamically growing memory buffer for trivially copyable/constructible types
      with the first ``SIZE`` elements stored in the object itself.

      You can use the ``memory_buffer`` type alias for ``char`` instead.

      **Example**::

         auto out = rsl::memory_buffer();
         format_to(rsl::back_inserter(out), "The answer is {}.", 42);

      This will append the following output to the ``out`` object:

      .. code-block:: none

         The answer is 42.

      The output can be converted to an ``rsl::string`` with ``to_string(out)``.
      \endrst
     */
    template <typename T, count_t SIZE = inline_buffer_size, typename Alloc = rsl::typed_allocator<T>>
    class basic_memory_buffer final : public detail::buffer<T>
    {
    private:
      T m_store[SIZE]; // NOLINT(modernize-avoid-c-arrays)

      // Don't inherit from Alloc avoid generating type_info for it.
      Alloc m_alloc;

      // Deallocate memory allocated by the buffer.
      FMT_CONSTEXPR20 void deallocate()
      {
        T* data = this->data();
        if(data != m_store)
          m_alloc.deallocate(data, this->capacity());
      }

    protected:
      FMT_CONSTEXPR20 void grow(count_t size) override;

    public:
      using value_type      = T;
      using const_reference = const T&;

      FMT_CONSTEXPR20 explicit basic_memory_buffer(const Alloc& alloc = Alloc())
          : m_alloc(alloc)
      {
        this->set(m_store, SIZE);
        if(detail::is_constant_evaluated())
          detail::fill_n(m_store, SIZE, T());
      }
      FMT_CONSTEXPR basic_memory_buffer(const basic_memory_buffer&) = delete;
      FMT_CONSTEXPR20 ~basic_memory_buffer()
      {
        deallocate();
      }

      basic_memory_buffer& operator=(const basic_memory_buffer&) = delete;

    private:
      // Move data from other to this buffer.
      FMT_CONSTEXPR20 void move(basic_memory_buffer& other)
      {
        m_alloc            = rsl::move(other.m_alloc);
        T* data            = other.data();
        const count_t size = other.size(), capacity = other.capacity(); // NOLINT(readability-isolate-declaration)
        if(data == other.m_store)
        {
          this->set(m_store, capacity);
          detail::copy_str<T>(other.m_store, other.m_store + size, detail::make_checked(m_store, capacity));
        }
        else
        {
          this->set(data, capacity);
          // Set pointer to the inline array so that delete is not called
          // when deallocating.
          other.set(other.m_store, 0);
          other.clear();
        }
        this->resize(size);
      }

    public:
      /**
        \rst
        Constructs a :class:`rsl::basic_memory_buffer` object moving the content
        of the other object to it.
        \endrst
       */
      FMT_CONSTEXPR20 basic_memory_buffer(basic_memory_buffer&& other) noexcept
      {
        move(other);
      }

      /**
        \rst
        Moves the content of the other ``basic_memory_buffer`` object to this one.
        \endrst
       */
      auto operator=(basic_memory_buffer&& other) noexcept -> basic_memory_buffer&
      {
        FMT_ASSERT(this != &other, "");
        deallocate();
        move(other);
        return *this;
      }

      // Returns a copy of the allocator associated with this buffer.
      auto get_allocator() const -> Alloc
      {
        return m_alloc;
      }

      /**
        Resizes the buffer to contain *count* elements. If T is a POD type new
        elements may not be initialized.
       */
      FMT_CONSTEXPR20 void resize(count_t count)
      {
        this->try_resize(count);
      }

      /** Increases the buffer capacity to *new_capacity*. */
      void reserve(count_t newCapacity)
      {
        this->try_reserve(newCapacity);
      }

      // Directly append data into the buffer
      using detail::buffer<T>::append;
      template <typename ContiguousRange>
      void append(const ContiguousRange& range)
      {
        append(range.data(), range.data() + range.size());
      }
    };

    template <typename T, count_t SIZE, typename Alloc>
    FMT_CONSTEXPR20 void basic_memory_buffer<T, SIZE, Alloc>::grow(count_t size)
    {
      detail::abort_fuzzing_if(size > 5000);
      const count_t max_size     = m_alloc.max_size();
      const count_t old_capacity = this->capacity();
      count_t new_capacity       = old_capacity + old_capacity / 2;
      if(size > new_capacity)
      {
        new_capacity = size;
      }
      else if(new_capacity > max_size)
      {
        new_capacity = size > max_size ? size : max_size;
      }
      T* old_data = this->data();
      T* new_data = m_alloc.allocate(new_capacity);
      // The following code doesn't throw, so the raw pointer above doesn't leak.
      std::uninitialized_copy(old_data, old_data + this->size(), detail::make_checked(new_data, new_capacity));
      this->set(new_data, new_capacity);
      // deallocate must not throw according to the standard, but even if it does,
      // the buffer already uses the new storage and will deallocate it in
      // destructor.
      if(old_data != m_store)
        m_alloc.deallocate(old_data, old_capacity);
    }

    using memory_buffer = basic_memory_buffer<char>;

    template <typename T, count_t SIZE, typename Alloc>
    struct is_contiguous<basic_memory_buffer<T, SIZE, Alloc>> : rsl::true_type
    {
    };

    namespace detail
    {
  #ifdef _WIN32
      FMT_API bool write_console(std::FILE* f, string_view text);
  #endif
      FMT_API void print(std::FILE* /*f*/, string_view /*text*/);
    } // namespace detail

    /** A formatting error such as invalid format string. */
    FMT_CLASS_API
    class FMT_API format_error : public std::runtime_error
    {
    public:
      explicit format_error(const char* message)
          : std::runtime_error(message)
      {
      }
      format_error(const format_error&)            = default;
      format_error& operator=(const format_error&) = default;
      format_error(format_error&&)                 = default;
      format_error& operator=(format_error&&)      = default;
      ~format_error() noexcept override FMT_MSC_DEFAULT;
    };

    namespace detail_exported
    {
  #if FMT_USE_NONTYPE_TEMPLATE_ARGS
      template <typename Char, count_t N>
      struct fixed_string
      {
        constexpr fixed_string(const Char (&str)[N])
        {
          detail::copy_str<Char, const Char*, Char*>(static_cast<const Char*>(str), str + N, data);
        }
        Char data[N] = {};
      };
  #endif

      // Converts a compile-time string to basic_string_view.
      template <typename Char, count_t N>
      constexpr auto compile_string_to_view(const Char (&s)[N]) -> basic_string_view<Char> // NOLINT(modernize-avoid-c-arrays)
      {
        // Remove trailing NUL character if needed. Won't be present if this is used
        // with a raw character array (i.e. not defined as a string).
        return {s, N - (rsl::char_traits<Char>::to_int_type(s[N - 1]) == 0 ? 1 : 0)};
      }
      template <typename Char>
      constexpr auto compile_string_to_view(detail::std_string_view<Char> s) -> basic_string_view<Char>
      {
        return {s.data(), s.size()};
      }
    } // namespace detail_exported

    namespace detail
    {

      template <typename T>
      struct is_integral : rsl::is_integral<T>
      {
      };
      template <>
      struct is_integral<int128_opt> : rsl::true_type
      {
      };
      template <>
      struct is_integral<uint128_t> : rsl::true_type
      {
      };

      template <typename T>
      using is_signed = rsl::integral_constant<bool, rsl::numeric_limits<T>::is_signed || rsl::is_same<T, int128_opt>::value>;

      // Returns true if value is negative, false otherwise.
      // Same as `value < 0` but doesn't produce warnings if T is an unsigned type.
      template <typename T, FMT_ENABLE_IF(is_signed<T>::value)>
      constexpr auto is_negative(T value) -> bool
      {
        return value < 0;
      }
      template <typename T, FMT_ENABLE_IF(!is_signed<T>::value)>
      constexpr auto is_negative(T /*unused*/) -> bool
      {
        return false;
      }

      template <typename T>
      FMT_CONSTEXPR auto is_supported_floating_point(T /*unused*/) -> bool
      {
        if(rsl::is_same<T, float>())
          return FMT_USE_FLOAT;
        if(rsl::is_same<T, double>())
          return FMT_USE_DOUBLE;
        if(rsl::is_same<T, long double>())
          return FMT_USE_LONG_DOUBLE;
        return true;
      }

      // Smallest of uint32, uint64, uint128_t that is large enough to
      // represent all values of an integral type T.
      template <typename T>
      using uint32_or_64_or_128_t = conditional_t<num_bits<T>() <= 32 && !FMT_REDUCE_INT_INSTANTIATIONS, uint32, conditional_t<num_bits<T>() <= 64, uint64, uint128_t>>;
      template <typename T>
      using uint64_or_128_t = conditional_t<num_bits<T>() <= 64, uint64, uint128_t>;

  #define FMT_POWERS_OF_10(factor) factor * 10, (factor)*100, (factor)*1000, (factor)*10000, (factor)*100000, (factor)*1000000, (factor)*10000000, (factor)*100000000, (factor)*1000000000

      // Converts value in the range [0, 100) to a string.
      constexpr const char* digits2(count_t value)
      {
        // GCC generates slightly better code when value is pointer-size.
        return &"0001020304050607080910111213141516171819"
                "2021222324252627282930313233343536373839"
                "4041424344454647484950515253545556575859"
                "6061626364656667686970717273747576777879"
                "8081828384858687888990919293949596979899"[static_cast<ptrdiff>(value * 2)];
      }

      // Sign is a template parameter to workaround a bug in gcc 4.8.
      template <typename Char, typename Sign>
      constexpr Char sign(Sign s)
      {
  #if !FMT_GCC_VERSION || FMT_GCC_VERSION >= 604
        static_assert(rsl::is_same<Sign, sign_t>::value, "sign type is not the same");
  #endif
        return static_cast<Char>("\0-+ "[s]);
      }

      template <typename T>
      FMT_CONSTEXPR auto count_digits_fallback(T n) -> int
      {
        int count = 1;
        for(;;)
        {
          // Integer division is slow so do it for a group of four digits instead
          // of for every digit. The idea comes from the talk by Alexandrescu
          // "Three Optimization Tips for C++". See speed-test for a comparison.
          if(n < 10)
            return count;
          if(n < 100)
            return count + 1;
          if(n < 1000)
            return count + 2;
          if(n < 10000)
            return count + 3;
          n /= 10000u;
          count += 4;
        }
      }
  #if FMT_USE_INT128
      FMT_CONSTEXPR inline auto count_digits(uint128_opt n) -> int
      {
        return count_digits_fallback(n);
      }
  #endif

  #ifdef FMT_BUILTIN_CLZLL
      // It is a separate function rather than a part of count_digits to workaround
      // the lack of static constexpr in constexpr functions.
      inline auto do_count_digits(uint64 n) -> int
      {
        // This has comparable performance to the version by Kendall Willets
        // (https://github.com/fmtlib/format-benchmark/blob/master/digits10)
        // but uses smaller tables.
        // Maps bsr(n) to ceil(log10(pow(2, bsr(n) + 1) - 1)).
        static constexpr uint8 bsr2log10[]                   = {1,  1,  1,  2,  2,  2,  3,  3,  3,  4,  4,  4,  4,  5,  5,  5,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9,  10, 10, 10,
                                                                10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 19, 20};
        auto t                                               = bsr2log10[FMT_BUILTIN_CLZLL(n | 1) ^ 63];
        static constexpr const uint64 zero_or_powers_of_10[] = {0, 0, FMT_POWERS_OF_10(1U), FMT_POWERS_OF_10(1000000000ULL), 10000000000000000000ULL};
        return t - (n < zero_or_powers_of_10[t]);
      }
  #endif

      // Returns the number of decimal digits in n. Leading zeros are not counted
      // except for n == 0 in which case count_digits returns 1.
      FMT_CONSTEXPR20 inline auto count_digits(uint64 n) -> int
      {
  #ifdef FMT_BUILTIN_CLZLL
        if(!is_constant_evaluated())
        {
          return do_count_digits(n);
        }
  #endif
        return count_digits_fallback(n);
      }

      // Counts the number of digits in n. BITS = log2(radix).
      template <int BITS, typename UInt>
      FMT_CONSTEXPR auto count_digits(UInt n) -> int
      {
  #ifdef FMT_BUILTIN_CLZ
        if(!is_constant_evaluated() && num_bits<UInt>() == 32)
          return (FMT_BUILTIN_CLZ(static_cast<uint32>(n) | 1) ^ 31) / BITS + 1;
  #endif
        // Lambda avoids unreachable code warnings from NVHPC.
        return [](UInt m)
        {
          int num_digits = 0;
          do
          {
            ++num_digits;
          } while((m >>= BITS) != 0);
          return num_digits;
        }(n);
      }

  #ifdef FMT_BUILTIN_CLZ
      // It is a separate function rather than a part of count_digits to workaround
      // the lack of static constexpr in constexpr functions.
      FMT_INLINE auto do_count_digits(uint32 n) -> int
      {
    // An optimization by Kendall Willets from https://bit.ly/3uOIQrB.
    // This increments the upper 32 bits (log10(T) - 1) when >= T is added.
    #define FMT_INC(T) (((sizeof(#T) - 1ull) << 32) - T)
        static constexpr uint64 table[] = {
            FMT_INC(0),          FMT_INC(0),          FMT_INC(0),          // 8
            FMT_INC(10),         FMT_INC(10),         FMT_INC(10),         // 64
            FMT_INC(100),        FMT_INC(100),        FMT_INC(100),        // 512
            FMT_INC(1000),       FMT_INC(1000),       FMT_INC(1000),       // 4096
            FMT_INC(10000),      FMT_INC(10000),      FMT_INC(10000),      // 32k
            FMT_INC(100000),     FMT_INC(100000),     FMT_INC(100000),     // 256k
            FMT_INC(1000000),    FMT_INC(1000000),    FMT_INC(1000000),    // 2048k
            FMT_INC(10000000),   FMT_INC(10000000),   FMT_INC(10000000),   // 16M
            FMT_INC(100000000),  FMT_INC(100000000),  FMT_INC(100000000),  // 128M
            FMT_INC(1000000000), FMT_INC(1000000000), FMT_INC(1000000000), // 1024M
            FMT_INC(1000000000), FMT_INC(1000000000)                       // 4B
        };
        auto inc = table[FMT_BUILTIN_CLZ(n | 1) ^ 31];
        return static_cast<int>((n + inc) >> 32);
      }
  #endif

      // Optional version of count_digits for better performance on 32-bit platforms.
      FMT_CONSTEXPR20 inline auto count_digits(uint32 n) -> int
      {
  #ifdef FMT_BUILTIN_CLZ
        if(!is_constant_evaluated())
        {
          return do_count_digits(n);
        }
  #endif
        return count_digits_fallback(n);
      }

      template <typename Int>
      constexpr auto digits10() noexcept -> int
      {
        return rsl::numeric_limits<Int>::digits10;
      }
      template <>
      constexpr auto digits10<int128_opt>() noexcept -> int
      {
        return 38;
      }
      template <>
      constexpr auto digits10<uint128_t>() noexcept -> int
      {
        return 38;
      }

      template <typename Char>
      struct thousands_sep_result
      {
        thousands_sep_result()
            : grouping()
            , thousands_sep()
        {
        }
        thousands_sep_result(rsl::string&& group, Char sep)
            : grouping(rsl::move(group))
            , thousands_sep(sep)
        {
        }

        rsl::string grouping;
        Char thousands_sep;
      };

      template <typename Char>
      FMT_API auto thousands_sep_impl(locale_ref loc) -> thousands_sep_result<Char>;
      template <typename Char>
      inline auto thousands_sep(locale_ref loc) -> thousands_sep_result<Char>
      {
        return thousands_sep_impl<char>(loc);
      }
      template <>
      inline auto thousands_sep(locale_ref loc) -> thousands_sep_result<wchar_t>
      {
        return thousands_sep_impl<wchar_t>(loc);
      }

      template <typename Char>
      FMT_API auto decimal_point_impl(locale_ref loc) -> Char;
      template <typename Char>
      inline auto decimal_point(locale_ref loc) -> Char
      {
        return Char(decimal_point_impl<char>(loc));
      }
      template <>
      inline auto decimal_point(locale_ref loc) -> wchar_t
      {
        return decimal_point_impl<wchar_t>(loc);
      }

      // Compares two characters for equality.
      template <typename Char>
      auto equal2(const Char* lhs, const char* rhs) -> bool
      {
        return lhs[0] == Char(rhs[0]) && lhs[1] == Char(rhs[1]);
      }
      inline auto equal2(const char* lhs, const char* rhs) -> bool
      {
        return memcmp(lhs, rhs, 2) == 0;
      }

      // Copies two characters from src to dst.
      template <typename Char>
      FMT_CONSTEXPR20 FMT_INLINE void copy2(Char* dst, const char* src)
      {
        if(!is_constant_evaluated() && sizeof(Char) == sizeof(char))
        {
          memcpy(dst, src, 2);
          return;
        }
        *dst++ = static_cast<Char>(*src++);
        *dst   = static_cast<Char>(*src);
      }

      template <typename Iterator>
      struct format_decimal_result
      {
        Iterator begin;
        Iterator end;
      };

      // Formats a decimal unsigned integer value writing into out pointing to a
      // buffer of specified size. The caller must ensure that the buffer is large
      // enough.
      template <typename Char, typename UInt>
      FMT_CONSTEXPR20 auto format_decimal(Char* out, UInt value, int size) -> format_decimal_result<Char*>
      {
        FMT_ASSERT(size >= count_digits(value), "invalid digit count");
        out += size;
        Char* end = out;
        while(value >= 100)
        {
          // Integer division is slow so do it for a group of two digits instead
          // of for every digit. The idea comes from the talk by Alexandrescu
          // "Three Optimization Tips for C++". See speed-test for a comparison.
          out -= 2;
          copy2(out, digits2(static_cast<count_t>(value % 100)));
          value /= 100;
        }
        if(value < 10)
        {
          *--out = static_cast<Char>('0' + value);
          return {out, end};
        }
        out -= 2;
        copy2(out, digits2(static_cast<count_t>(value)));
        return {out, end};
      }

      template <typename Char, typename UInt, typename Iterator, FMT_ENABLE_IF(!rsl::is_pointer<remove_cvref_t<Iterator>>::value)>
      FMT_CONSTEXPR inline auto format_decimal(Iterator out, UInt value, int size) -> format_decimal_result<Iterator>
      {
        // Buffer is large enough to hold all digits (digits10 + 1).
        Char buffer[digits10<UInt>() + 1]; // NOLINT(modernize-avoid-c-arrays)
        auto* end = format_decimal(buffer, value, size).end;
        return {out, detail::copy_str_noinline<Char>(buffer, end, out)};
      }

      template <unsigned BaseBits, typename Char, typename UInt>
      FMT_CONSTEXPR auto format_uint(Char* buffer, UInt value, int numDigits, bool upper = false) -> Char*
      {
        buffer += numDigits;
        Char* end = buffer;
        do
        {
          const char* digits   = upper ? "0123456789ABCDEF" : "0123456789abcdef";
          const unsigned digit = static_cast<unsigned>(value & ((1 << BaseBits) - 1));
          *--buffer            = static_cast<Char>(BaseBits < 4 ? static_cast<char>('0' + digit) : digits[digit]);
        } while((value >>= BaseBits) != 0);
        return end;
      }

      template <unsigned BaseBits, typename Char, typename It, typename UInt>
      inline auto format_uint(It out, UInt value, int numDigits, bool upper = false) -> It
      {
        if(auto ptr = to_pointer<Char>(out, to_unsigned(numDigits)))
        {
          format_uint<BaseBits>(ptr, value, numDigits, upper);
          return out;
        }
        // Buffer should be large enough to hold all digits (digits / BASE_BITS + 1).
        char buffer[num_bits<UInt>() / BaseBits + 1]; // NOLINT(modernize-avoid-c-arrays)
        format_uint<BaseBits>(buffer, value, numDigits, upper);
        return detail::copy_str_noinline<Char>(buffer, buffer + numDigits, out);
      }

      // A converter from UTF-8 to UTF-16.
      class utf8_to_utf16
      {
      private:
        basic_memory_buffer<wchar_t> m_buffer;

      public:
        FMT_API explicit utf8_to_utf16(string_view s);
        operator basic_string_view<wchar_t>() const // NOLINT(google-explicit-constructor)
        {
          return {m_buffer.data(), size()};
        }
        auto size() const -> count_t
        {
          return m_buffer.size() - 1;
        }
        auto c_str() const -> const wchar_t*
        {
          return m_buffer.data();
        }
        auto str() const -> rsl::wstring
        {
          return {m_buffer.data(), size()};
        }
      };

      namespace dragonbox
      {

        // Type-specific information that Dragonbox uses.
        template <typename T, typename Enable = void>
        struct float_info;

        template <>
        struct float_info<float>
        {
          using carrier_uint                                        = uint32;
          static constexpr int exponent_bits                        = 8;
          static constexpr int kappa                                = 1;
          static constexpr int big_divisor                          = 100;
          static constexpr int small_divisor                        = 10;
          static constexpr int min_k                                = -31;
          static constexpr int max_k                                = 46;
          static constexpr int shorter_interval_tie_lower_threshold = -35;
          static constexpr int shorter_interval_tie_upper_threshold = -35;
        };

        template <>
        struct float_info<double>
        {
          using carrier_uint                                        = uint64;
          static constexpr int exponent_bits                        = 11;
          static constexpr int kappa                                = 2;
          static constexpr int big_divisor                          = 1000;
          static constexpr int small_divisor                        = 100;
          static constexpr int min_k                                = -292;
          static constexpr int max_k                                = 326;
          static constexpr int shorter_interval_tie_lower_threshold = -77;
          static constexpr int shorter_interval_tie_upper_threshold = -77;
        };

        // An 80- or 128-bit floating point number.
        template <typename T>
        struct float_info<T, enable_if_t<rsl::numeric_limits<T>::digits == 64 || rsl::numeric_limits<T>::digits == 113 || is_float128<T>::value>>
        {
          using carrier_uint                 = detail::uint128_t;
          static constexpr int exponent_bits = 15;
        };

        // A double-double floating point number.
        template <typename T>
        struct float_info<T, enable_if_t<is_double_double<T>::value>>
        {
          using carrier_uint = detail::uint128_t;
        };

        template <typename T>
        struct decimal_fp
        {
          using significand_type = typename float_info<T>::carrier_uint;
          significand_type significand;
          int exponent;
        };

        template <typename T>
        FMT_API auto to_decimal(T x) noexcept -> decimal_fp<T>;
      } // namespace dragonbox

      // Returns true iff Float has the implicit bit which is not stored.
      template <typename Float>
      constexpr bool has_implicit_bit()
      {
        // An 80-bit FP number has a 64-bit significand an no implicit bit.
        return rsl::numeric_limits<Float>::digits != 64;
      }

      // Returns the number of significand bits stored in Float. The implicit bit is
      // not counted since it is not stored.
      template <typename Float>
      constexpr int num_significand_bits()
      {
        // rsl::numeric_limits may not support __float128.
        return is_float128<Float>() ? 112 : (rsl::numeric_limits<Float>::digits - (has_implicit_bit<Float>() ? 1 : 0));
      }

      template <typename Float>
      constexpr auto exponent_mask() -> typename dragonbox::float_info<Float>::carrier_uint
      {
        using uint = typename dragonbox::float_info<Float>::carrier_uint;
        return ((uint(1) << dragonbox::float_info<Float>::exponent_bits) - 1) << num_significand_bits<Float>(); // NOLINT(google-readability-casting)
      }
      template <typename Float>
      constexpr auto exponent_bias() -> int
      {
        // rsl::numeric_limits may not support __float128.
        return is_float128<Float>() ? 16383 : rsl::numeric_limits<Float>::max_exponent - 1;
      }

      // Writes the exponent exp in the form "[+-]d{2,3}" to buffer.
      template <typename Char, typename It>
      FMT_CONSTEXPR auto write_exponent(int exp, It it) -> It
      {
        FMT_ASSERT(-10000 < exp && exp < 10000, "exponent out of range");
        if(exp < 0)
        {
          *it++ = static_cast<Char>('-');
          exp   = -exp;
        }
        else
        {
          *it++ = static_cast<Char>('+');
        }
        if(exp >= 100)
        {
          const char* top = digits2(to_unsigned(exp / 100)); // NOLINT(cppcoreguidelines-narrowing-conversions)
          if(exp >= 1000)
            *it++ = static_cast<Char>(top[0]);
          *it++ = static_cast<Char>(top[1]);
          exp %= 100;
        }
        const char* d = digits2(to_unsigned(exp)); // NOLINT(cppcoreguidelines-narrowing-conversions)
        *it++         = static_cast<Char>(d[0]);
        *it++         = static_cast<Char>(d[1]);
        return it;
      }

      // A floating-point number f * pow(2, e) where F is an unsigned type.
      template <typename F>
      struct basic_fp
      {
        F f;
        int e;

        static constexpr const int num_significand_bits = static_cast<int>(sizeof(F) * num_bits<unsigned char>());

        constexpr basic_fp()
            : f(0)
            , e(0)
        {
        }
        constexpr basic_fp(uint64 fVal, int eVal)
            : f(fVal)
            , e(eVal)
        {
        }

        // Constructs fp from an IEEE754 floating-point number.
        template <typename Float>
        FMT_CONSTEXPR basic_fp(Float n) // NOLINT(cppcoreguidelines-pro-type-member-init, google-explicit-constructor)
        {
          assign(n);
        }

        // Assigns n to this and return true iff predecessor is closer than successor.
        template <typename Float, FMT_ENABLE_IF(!is_double_double<Float>::value)>
        FMT_CONSTEXPR auto assign(Float n) -> bool
        {
          static_assert(rsl::numeric_limits<Float>::digits <= 113, "unsupported FP");
          // Assume Float is in the format [sign][exponent][significand].
          using carrier_uint                    = typename dragonbox::float_info<Float>::carrier_uint;
          const auto num_float_significand_bits = detail::num_significand_bits<Float>();
          const auto implicit_bit               = carrier_uint(1) << num_float_significand_bits; // NOLINT(google-readability-casting)
          const auto significand_mask           = implicit_bit - 1;
          auto u                                = bit_cast<carrier_uint>(n);
          f                                     = static_cast<F>(u & significand_mask);
          auto biased_e                         = static_cast<int>((u & exponent_mask<Float>()) >> num_float_significand_bits);
          // The predecessor is closer if n is a normalized power of 2 (f == 0)
          // other than the smallest normalized number (biased_e > 1).
          auto is_predecessor_closer = f == 0 && biased_e > 1;
          if(biased_e == 0)
          {
            biased_e = 1; // Subnormals use biased exponent 1 (min exponent).
          }
          else if(has_implicit_bit<Float>())
          {
            f += static_cast<F>(implicit_bit);
          }
          e = biased_e - exponent_bias<Float>() - num_float_significand_bits;
          if(!has_implicit_bit<Float>())
            ++e;
          return is_predecessor_closer;
        }

        template <typename Float, FMT_ENABLE_IF(is_double_double<Float>::value)>
        FMT_CONSTEXPR auto assign(Float n) -> bool
        {
          static_assert(rsl::numeric_limits<double>::is_iec559, "unsupported FP");
          return assign(static_cast<double>(n));
        }
      };

      using fp = basic_fp<unsigned long long>;

      // Normalizes the value converted from double and multiplied by (1 << SHIFT).
      template <int SHIFT = 0, typename F>
      FMT_CONSTEXPR basic_fp<F> normalize(basic_fp<F> value)
      {
        // Handle subnormals.
        const auto implicit_bit         = F(1) << num_significand_bits<double>(); // NOLINT(google-readability-casting)
        const auto shifted_implicit_bit = implicit_bit << SHIFT;
        while((value.f & shifted_implicit_bit) == 0)
        {
          value.f <<= 1;
          --value.e;
        }
        // Subtract 1 to account for hidden bit.
        const auto offset = basic_fp<F>::num_significand_bits - num_significand_bits<double>() - SHIFT - 1;
        value.f <<= offset;
        value.e -= offset;
        return value;
      }

      // Computes lhs * rhs / pow(2, 64) rounded to nearest with half-up tie breaking.
      FMT_CONSTEXPR inline uint64 multiply(uint64 lhs, uint64 rhs)
      {
  #if FMT_USE_INT128
        auto product = static_cast<__uint128_t>(lhs) * rhs;
        auto f       = static_cast<uint64>(product >> 64);
        return (static_cast<uint64>(product) & (1ULL << 63)) != 0 ? f + 1 : f;
  #else
        // Multiply 32-bit parts of significands.
        const uint64 mask = (1ULL << 32) - 1;
        const uint64 a = lhs >> 32, b = lhs & mask;                  // NOLINT(readability-isolate-declaration)
        const uint64 c = rhs >> 32, d = rhs & mask;                  // NOLINT(readability-isolate-declaration)
        const uint64 ac = a * c, bc = b * c, ad = a * d, bd = b * d; // NOLINT(readability-isolate-declaration)
        // Compute mid 64-bit of result and round.
        const uint64 mid = (bd >> 32) + (ad & mask) + (bc & mask) + (1U << 31);
        return ac + (ad >> 32) + (bc >> 32) + (mid >> 32);
  #endif
      }

      FMT_CONSTEXPR inline fp operator*(fp x, fp y)
      {
        return {multiply(x.f, y.f), x.e + y.e + 64};
      }

      template <typename T = void>
      struct basic_data
      {
        // Normalized 64-bit significands of pow(10, k), for k = -348, -340, ..., 340.
        // These are generated by support/compute-powers.py.
        // NOLINTNEXTLINE(modernize-avoid-c-arrays)
        static constexpr uint64 pow10_significands[87] = {
            0xfa8fd5a0081c0288, 0xbaaee17fa23ebf76, 0x8b16fb203055ac76, 0xcf42894a5dce35ea, 0x9a6bb0aa55653b2d, 0xe61acf033d1a45df, 0xab70fe17c79ac6ca, 0xff77b1fcbebcdc4f, 0xbe5691ef416bd60c, 0x8dd01fad907ffc3c, 0xd3515c2831559a83,
            0x9d71ac8fada6c9b5, 0xea9c227723ee8bcb, 0xaecc49914078536d, 0x823c12795db6ce57, 0xc21094364dfb5637, 0x9096ea6f3848984f, 0xd77485cb25823ac7, 0xa086cfcd97bf97f4, 0xef340a98172aace5, 0xb23867fb2a35b28e, 0x84c8d4dfd2c63f3b,
            0xc5dd44271ad3cdba, 0x936b9fcebb25c996, 0xdbac6c247d62a584, 0xa3ab66580d5fdaf6, 0xf3e2f893dec3f126, 0xb5b5ada8aaff80b8, 0x87625f056c7c4a8b, 0xc9bcff6034c13053, 0x964e858c91ba2655, 0xdff9772470297ebd, 0xa6dfbd9fb8e5b88f,
            0xf8a95fcf88747d94, 0xb94470938fa89bcf, 0x8a08f0f8bf0f156b, 0xcdb02555653131b6, 0x993fe2c6d07b7fac, 0xe45c10c42a2b3b06, 0xaa242499697392d3, 0xfd87b5f28300ca0e, 0xbce5086492111aeb, 0x8cbccc096f5088cc, 0xd1b71758e219652c,
            0x9c40000000000000, 0xe8d4a51000000000, 0xad78ebc5ac620000, 0x813f3978f8940984, 0xc097ce7bc90715b3, 0x8f7e32ce7bea5c70, 0xd5d238a4abe98068, 0x9f4f2726179a2245, 0xed63a231d4c4fb27, 0xb0de65388cc8ada8, 0x83c7088e1aab65db,
            0xc45d1df942711d9a, 0x924d692ca61be758, 0xda01ee641a708dea, 0xa26da3999aef774a, 0xf209787bb47d6b85, 0xb454e4a179dd1877, 0x865b86925b9bc5c2, 0xc83553c5c8965d3d, 0x952ab45cfa97a0b3, 0xde469fbd99a05fe3, 0xa59bc234db398c25,
            0xf6c69a72a3989f5c, 0xb7dcbf5354e9bece, 0x88fcf317f22241e2, 0xcc20ce9bd35c78a5, 0x98165af37b2153df, 0xe2a0b5dc971f303a, 0xa8d9d1535ce3b396, 0xfb9b7cd9a4a7443c, 0xbb764c4ca7a44410, 0x8bab8eefb6409c1a, 0xd01fef10a657842c,
            0x9b10a4e5e9913129, 0xe7109bfba19c0c9d, 0xac2820d9623bf429, 0x80444b5e7aa7cf85, 0xbf21e44003acdd2d, 0x8e679c2f5e44ff8f, 0xd433179d9c8cb841, 0x9e19db92b4e31ba9, 0xeb96bf6ebadf77d9, 0xaf87023b9bf0ee6b,
        };

  #if FMT_GCC_VERSION && FMT_GCC_VERSION < 409
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wnarrowing"
  #endif
        // Binary exponents of pow(10, k), for k = -348, -340, ..., 340, corresponding
        // to significands above.
        static constexpr int16_t pow10_exponents[87] = {                                                                                                                                           // NOLINT(modernize-avoid-c-arrays)
            -1220, -1193, -1166, -1140, -1113, -1087, -1060, -1034, -1007, -980, -954, -927, -901, -874, -847, -821, -794, -768, -741, -715, -688, -661, -635, -608, -582, -555, -529, -502, -475, // NOLINT(modernize-avoid-c-arrays)
            -449,  -422,  -396,  -369,  -343,  -316,  -289,  -263,  -236,  -210, -183, -157, -130, -103, -77,  -50,  -24,  3,    30,   56,   83,   109,  136,  162,  189,  216,  242,  269,  295,
            322,   348,   375,   402,   428,   455,   481,   508,   534,   561,  588,  614,  641,  667,  694,  720,  747,  774,  800,  827,  853,  880,  907,  933,  960,  986,  1013, 1039, 1066};
  #if FMT_GCC_VERSION && FMT_GCC_VERSION < 409
    #pragma GCC diagnostic pop
  #endif

        static constexpr uint64 power_of_10_64[20] = {1, FMT_POWERS_OF_10(1ULL), FMT_POWERS_OF_10(1000000000ULL), 10000000000000000000ULL}; // NOLINT(modernize-avoid-c-arrays)
      };

  #if FMT_CPLUSPLUS < 201703L
      template <typename T>
      constexpr uint64 basic_data<T>::pow10_significands[];
      template <typename T>
      constexpr int16_t basic_data<T>::pow10_exponents[];
      template <typename T>
      constexpr uint64 basic_data<T>::power_of_10_64[];
  #endif

      // This is a struct rather than an alias to avoid shadowing warnings in gcc.
      struct data : basic_data<>
      {
      };

      // Returns a cached power of 10 `c_k = c_k.f * pow(2, c_k.e)` such that its
      // (binary) exponent satisfies `min_exponent <= c_k.e <= min_exponent + 28`.
      FMT_CONSTEXPR inline fp get_cached_power(int minExponent, int& pow10Exponent)
      {
        const int shift = 32;
        // log10(2) = 0x0.4d104d427de7fbcc...
        const int64_t significand = 0x4d104d427de7fbcc;
        int index                 = static_cast<int>(((minExponent + fp::num_significand_bits - 1) * (significand >> shift) + ((int64_t(1) << shift) - 1)) // NOLINT(google-readability-casting) // ceil
                                     >> 32                                                                                                 // arithmetic shift
        );
        // Decimal exponent of the first (smallest) cached power of 10.
        const int first_dec_exp = -348;
        // Difference between 2 consecutive decimal exponents in cached powers of 10.
        const int dec_exp_step = 8;
        index                  = (index - first_dec_exp - 1) / dec_exp_step + 1;
        pow10Exponent          = first_dec_exp + index * dec_exp_step;
        // Using *(x + index) instead of x[index] avoids an issue with some compilers
        // using the EDG frontend (e.g. nvhpc/22.3 in C++17 mode).
        return {*(data::pow10_significands + index), *(data::pow10_exponents + index)};
      }

  #ifndef _MSC_VER
    #define FMT_SNPRINTF snprintf
  #else
      FMT_API auto fmt_snprintf(char* buf, count_t size, const char* fmt, ...) -> int;
    #define FMT_SNPRINTF fmt_snprintf
  #endif // _MSC_VER

      // Formats a floating-point number with snprintf using the hexfloat format.
      template <typename T>
      auto snprintf_float(T value, int precision, float_specs specs, buffer<char>& buf) -> int
      {
        // Buffer capacity must be non-zero, otherwise MSVC's vsnprintf_s will fail.
        FMT_ASSERT(buf.capacity() > buf.size(), "empty buffer");
        FMT_ASSERT(specs.format == float_format::hex, "");
        static_assert(!rsl::is_same<T, float>::value, "type must not be float");

        // Build the format string.
        char format[7]; // NOLINT(modernize-avoid-c-arrays) // The longest format is "%#.*Le".
        char* format_ptr = format;
        *format_ptr++    = '%';
        if(specs.showpoint)
          *format_ptr++ = '#';
        if(precision >= 0)
        {
          *format_ptr++ = '.';
          *format_ptr++ = '*';
        }
        if(rsl::is_same<T, long double>())
          *format_ptr++ = 'L';
        *format_ptr++ = specs.upper ? 'A' : 'a';
        *format_ptr   = '\0';

        // Format using snprintf.
        auto offset = buf.size();
        for(;;)
        {
          auto* begin   = buf.data() + offset;
          auto capacity = buf.capacity() - offset;
          abort_fuzzing_if(precision > 100000);
          // Suppress the warning about a nonliteral format string.
          // Cannot use auto because of a bug in MinGW (#1532).
          int (*snprintf_ptr)(char*, count_t, const char*, ...) = FMT_SNPRINTF;
          const int result                                      = precision >= 0 ? snprintf_ptr(begin, capacity, format, precision, value) : snprintf_ptr(begin, capacity, format, value);
          if(result < 0)
          {
            // The buffer will grow exponentially.
            buf.try_reserve(buf.capacity() + 1);
            continue;
          }
          // Size equal to capacity means that the last character was truncated.
          if(result < capacity)
          {
            buf.try_resize(result + offset);
            return 0;
          }
          buf.try_reserve(result + offset + 1); // Add 1 for the terminating '\0'.
        }
      }

      template <typename T>
      using convert_float_result = conditional_t<rsl::is_same<T, float>::value || sizeof(T) == sizeof(double), double, T>;

      template <typename T>
      constexpr auto convert_float(T value) -> convert_float_result<T>
      {
        return static_cast<convert_float_result<T>>(value);
      }

      template <typename OutputIt, typename Char>
      FMT_NOINLINE FMT_CONSTEXPR auto fill(OutputIt it, count_t n, const fill_t<Char>& fill) -> OutputIt
      {
        auto fill_size = fill.size();
        if(fill_size == 1)
          return detail::fill_n(it, n, fill[0]);
        auto data = fill.data();
        for(count_t i = 0; i < n; ++i)
          it = copy_str<Char>(data, data + fill_size, it);
        return it;
      }

      // Writes the output of f, padded according to format specifications in specs.
      // size: output size in code units.
      // width: output display width in (terminal) column positions.
      template <align::type Align = align::left, typename OutputIt, typename Char, typename F>
      FMT_CONSTEXPR auto write_padded(OutputIt out, const basic_format_specs<Char>& specs, count_t size, count_t width, F&& f) -> OutputIt
      {
        static_assert(Align == align::left || Align == align::right, "alignment must either be left or right");
        const count_t padding = specs.width > width ? specs.width - width : 0;
        // Shifts are encoded as string literals because static constexpr is not
        // supported in constexpr functions.
        const auto* shifts          = Align == align::left ? "\x1f\x1f\x00\x01" : "\x00\x1f\x00\x01";
        const count_t left_padding  = padding >> shifts[specs.align];
        const count_t right_padding = padding - left_padding;
        auto it                     = reserve(out, size + padding * specs.fill.size());
        if(left_padding != 0)
          it = fill(it, left_padding, specs.fill);
        it = f(it);
        if(right_padding != 0)
          it = fill(it, right_padding, specs.fill);
        return base_iterator(out, it);
      }

      template <align::type Align = align::left, typename OutputIt, typename Char, typename F>
      constexpr auto write_padded(OutputIt out, const basic_format_specs<Char>& specs, count_t size, F&& f) -> OutputIt
      {
        return write_padded<Align>(out, specs, size, size, f);
      }

      template <align::type Align = align::left, typename Char, typename OutputIt>
      FMT_CONSTEXPR auto write_bytes(OutputIt out, string_view bytes, const basic_format_specs<Char>& specs) -> OutputIt
      {
        return write_padded<Align>(out, specs, bytes.size(),
                                   [bytes](reserve_iterator<OutputIt> it)
                                   {
                                     const char* data = bytes.data();
                                     return copy_str<Char>(data, data + bytes.size(), it);
                                   });
      }

      template <typename Char, typename OutputIt, typename UIntPtr>
      auto write_ptr(OutputIt out, UIntPtr value, const basic_format_specs<Char>* specs) -> OutputIt
      {
        const int num_digits = count_digits<4>(value);
        auto size            = to_unsigned(num_digits) + count_t(2); // NOLINT(google-readability-casting)
        auto write           = [=](reserve_iterator<OutputIt> it)
        {
          *it++ = static_cast<Char>('0');
          *it++ = static_cast<Char>('x');
          return format_uint<4, Char>(it, value, num_digits);
        };
        return specs ? write_padded<align::right>(out, *specs, size, write) : base_iterator(out, write(reserve(out, size)));
      }

      // Returns true iff the code point cp is printable.
      FMT_API auto is_printable(uint32 cp) -> bool;

      inline auto needs_escape(uint32 cp) -> bool
      {
        return cp < 0x20 || cp == 0x7f || cp == '"' || cp == '\\' || !is_printable(cp);
      }

      template <typename Char>
      struct find_escape_result
      {
        const Char* begin;
        const Char* end;
        uint32 cp;
      };

      template <typename Char>
      using make_unsigned_char = typename conditional_t<rsl::is_integral<Char>::value, rsl::make_unsigned<Char>, type_identity<uint32>>::type;

      template <typename Char>
      auto find_escape(const Char* begin, const Char* end) -> find_escape_result<Char>
      {
        for(; begin != end; ++begin)
        {
          const uint32 cp = static_cast<make_unsigned_char<Char>>(*begin);
          if(const_check(sizeof(Char) == 1) && cp >= 0x80)
            continue;
          if(needs_escape(cp))
            return {begin, begin + 1, cp};
        }
        return {begin, nullptr, 0};
      }

      inline auto find_escape(const char* begin, const char* end) -> find_escape_result<char>
      {
        if(!is_utf8())
          return find_escape<char>(begin, end);
        auto result = find_escape_result<char> {end, nullptr, 0};
        for_each_codepoint(string_view(begin, to_unsigned(static_cast<count_t>(end - begin))), // NOLINT(cppcoreguidelines-narrowing-conversions)
                           [&](uint32 cp, string_view sv)
                           {
                             if(needs_escape(cp))
                             {
                               result = {rsl::iterator_to_pointer(sv.begin()), rsl::iterator_to_pointer(sv.end()), cp};
                               return false;
                             }
                             return true;
                           });
        return result;
      }

  #define FMT_STRING_IMPL(s, base, explicit)                                                                                                                                                                                                             \
    []                                                                                                                                                                                                                                                   \
    {                                                                                                                                                                                                                                                    \
      /* Use the hidden visibility as a workaround for a GCC bug (#1973). */                                                                                                                                                                             \
      /* Use a macro-like name to avoid shadowing warnings. */                                                                                                                                                                                           \
      struct FMT_GCC_VISIBILITY_HIDDEN FMT_COMPILE_STRING : base                                                                                                                                                                                         \
      {                                                                                                                                                                                                                                                  \
        using char_type FMT_MAYBE_UNUSED = rsl::remove_cvref_t<decltype(s[0])>;                                                                                                                                                                          \
        FMT_MAYBE_UNUSED FMT_CONSTEXPR explicit operator rsl::basic_string_view<char_type>() const                                                                                                                                                       \
        {                                                                                                                                                                                                                                                \
          return rsl::detail_exported::compile_string_to_view<char_type>(s);                                                                                                                                                                             \
        }                                                                                                                                                                                                                                                \
      };                                                                                                                                                                                                                                                 \
      return FMT_COMPILE_STRING();                                                                                                                                                                                                                       \
    }()

  /**
    \rst
    Constructs a compile-time format string from a string literal *s*.

    **Example**::

      // A compile-time error because 'd' is an invalid specifier for strings.
      rsl::string s = rsl::format(FMT_STRING("{:d}"), "foo");
    \endrst
   */
  #define FMT_STRING(s) FMT_STRING_IMPL(s, rsl::detail::compile_string, )

      template <count_t Width, typename Char, typename OutputIt>
      auto write_codepoint(OutputIt out, char prefix, uint32 cp) -> OutputIt
      {
        *out++ = static_cast<Char>('\\');
        *out++ = static_cast<Char>(prefix);
        Char buf[Width]; // NOLINT(modernize-avoid-c-arrays)
        fill_n(buf, Width, static_cast<Char>('0'));
        format_uint<4>(buf, cp, Width);
        return copy_str<Char>(buf, buf + Width, out);
      }

      template <typename OutputIt, typename Char>
      auto write_escaped_cp(OutputIt out, const find_escape_result<Char>& escape) -> OutputIt
      {
        auto c = static_cast<Char>(escape.cp);
        switch(escape.cp)
        {
          case '\n':
            *out++ = static_cast<Char>('\\');
            c      = static_cast<Char>('n');
            break;
          case '\r':
            *out++ = static_cast<Char>('\\');
            c      = static_cast<Char>('r');
            break;
          case '\t':
            *out++ = static_cast<Char>('\\');
            c      = static_cast<Char>('t');
            break;
          case '"': FMT_FALLTHROUGH;  // NOLINT(bugprone-branch-clone)
          case '\'': FMT_FALLTHROUGH; // NOLINT(bugprone-branch-clone)
          case '\\': *out++ = static_cast<Char>('\\'); break;
          default:
            if(is_utf8())
            {
              if(escape.cp < 0x100)
              {
                return write_codepoint<2, Char>(out, 'x', escape.cp);
              }
              if(escape.cp < 0x10000)
              {
                return write_codepoint<4, Char>(out, 'u', escape.cp);
              }
              if(escape.cp < 0x110000)
              {
                return write_codepoint<8, Char>(out, 'U', escape.cp);
              }
            }
            for(Char escape_char: basic_string_view<Char>(escape.begin, to_unsigned(static_cast<count_t>(escape.end - escape.begin))))
            {
              out = write_codepoint<2, Char>(out, 'x', static_cast<uint32>(escape_char) & 0xFF);
            }
            return out;
        }
        *out++ = c;
        return out;
      }

      template <typename Char, typename OutputIt>
      auto write_escaped_string(OutputIt out, basic_string_view<Char> str) -> OutputIt
      {
        *out++     = static_cast<Char>('"');
        auto begin = str.begin(), end = str.end(); // NOLINT(readability-isolate-declaration)
        do
        {
          auto escape = find_escape(rsl::iterator_to_pointer(begin), rsl::iterator_to_pointer(end));
          out         = copy_str<Char>(rsl::iterator_to_pointer(begin), escape.begin, out);
          begin       = decltype(begin)(escape.end);
          if(!rsl::iterator_to_pointer(begin))
            break;
          out = write_escaped_cp<OutputIt, Char>(out, escape);
        } while(begin != end);
        *out++ = static_cast<Char>('"');
        return out;
      }

      template <typename Char, typename OutputIt>
      auto write_escaped_char(OutputIt out, Char v) -> OutputIt
      {
        *out++ = static_cast<Char>('\'');
        if((needs_escape(static_cast<uint32>(v)) && v != static_cast<Char>('"')) || v == static_cast<Char>('\''))
        {
          out = write_escaped_cp(out, find_escape_result<Char> {&v, &v + 1, static_cast<uint32>(v)});
        }
        else
        {
          *out++ = v;
        }
        *out++ = static_cast<Char>('\'');
        return out;
      }

      template <typename Char, typename OutputIt>
      FMT_CONSTEXPR auto write_char(OutputIt out, Char value, const basic_format_specs<Char>& specs) -> OutputIt
      {
        const bool is_debug = specs.type == presentation_type::debug;
        return write_padded(out, specs, 1,
                            [=](reserve_iterator<OutputIt> it)
                            {
                              if(is_debug)
                                return write_escaped_char(it, value);
                              *it++ = value;
                              return it;
                            });
      }
      template <typename Char, typename OutputIt>
      FMT_CONSTEXPR auto write(OutputIt out, Char value, const basic_format_specs<Char>& specs, locale_ref loc = {}) -> OutputIt
      {
        return check_char_specs(specs) ? write_char(out, value, specs) : write(out, static_cast<int>(value), specs, loc);
      }

      // Data for write_int that doesn't depend on output iterator type. It is used to
      // avoid template code bloat.
      template <typename Char>
      struct write_int_data
      {
        count_t size;
        count_t padding;

        FMT_CONSTEXPR write_int_data(int numDigits, unsigned prefix, const basic_format_specs<Char>& specs)
            : size((prefix >> 24) + to_unsigned(numDigits)) // NOLINT(cppcoreguidelines-narrowing-conversions)
            , padding(0)
        {
          if(specs.align == align::numeric)
          {
            if(specs.width > size)
            {
              padding = specs.width - size;
              size    = specs.width;
            }
          }
          else if(specs.precision > numDigits)
          {
            size    = (prefix >> 24) + to_unsigned(specs.precision);
            padding = to_unsigned(specs.precision - numDigits);
          }
        }
      };

      // Writes an integer in the format
      //   <left-padding><prefix><numeric-padding><digits><right-padding>
      // where <digits> are written by write_digits(it).
      // prefix contains chars in three lower bytes and the size in the fourth byte.
      template <typename OutputIt, typename Char, typename W>
      FMT_CONSTEXPR FMT_INLINE auto write_int(OutputIt out, int numDigits, unsigned prefix, const basic_format_specs<Char>& specs, W writeDigits) -> OutputIt
      {
        // Slightly faster check for specs.width == 0 && specs.precision == -1.
        if((specs.width | (specs.precision + 1)) == 0)
        {
          auto it = reserve(out, to_unsigned(numDigits) + (prefix >> 24));
          if(prefix != 0)
          {
            for(unsigned p = prefix & 0xffffff; p != 0; p >>= 8)
              *it++ = static_cast<Char>(p & 0xff);
          }
          return base_iterator(out, writeDigits(it));
        }
        auto data = write_int_data<Char>(numDigits, prefix, specs);
        return write_padded<align::right>(out, specs, data.size,
                                          [=](reserve_iterator<OutputIt> it)
                                          {
                                            for(unsigned p = prefix & 0xffffff; p != 0; p >>= 8)
                                              *it++ = static_cast<Char>(p & 0xff);
                                            it = detail::fill_n(it, data.padding, static_cast<Char>('0'));
                                            return writeDigits(it);
                                          });
      }

      template <typename Char>
      class digit_grouping
      {
      private:
        thousands_sep_result<Char> m_sep;

        struct next_state
        {
          next_state()
              : group()
              , pos(-1)
          {
          }
          next_state(rsl::string::const_iterator grp, int position)
              : group(grp)
              , pos(position)
          {
          }

          rsl::string::const_iterator group;
          int pos;
        };
        next_state initial_state() const
        {
          return next_state(m_sep.grouping.begin(), 0);
        }

        // Returns the next digit group separator position.
        int next(next_state& state) const
        {
          if(!m_sep.thousands_sep)
            return max_value<int>();
          if(state.group == m_sep.grouping.end())
            return state.pos += m_sep.grouping.back();
          if(*state.group <= 0 || *state.group == max_value<char>())
            return max_value<int>();
          state.pos += *state.group++;
          return state.pos;
        }

      public:
        explicit digit_grouping(locale_ref loc, bool localized = true)
        {
          if(localized)
          {
            m_sep = thousands_sep<Char>(loc);
          }
          else
          {
            m_sep.thousands_sep = Char();
          }
        }
        explicit digit_grouping(thousands_sep_result<Char> sep)
            : m_sep(sep)
        {
        }

        Char separator() const
        {
          return m_sep.thousands_sep;
        }

        int count_separators(int numDigits) const
        {
          int count  = 0;
          auto state = initial_state();
          while(numDigits > next(state))
            ++count;
          return count;
        }

        // Applies grouping to digits and write the output to out.
        template <typename Out, typename C>
        Out apply(Out out, basic_string_view<C> digits) const
        {
          auto num_digits = static_cast<int>(digits.size());
          auto separators = basic_memory_buffer<int>();
          separators.push_back(0);
          auto state = initial_state();
          while(const int i = next(state))
          {
            if(i >= num_digits)
              break;
            separators.push_back(i);
          }
          for(int i = 0, sep_index = static_cast<int>(separators.size() - 1); i < num_digits; ++i)
          {
            if(num_digits - i == separators[sep_index])
            {
              *out++ = separator();
              --sep_index;
            }
            *out++ = static_cast<Char>(digits[to_unsigned(i)]);
          }
          return out;
        }
      };

      template <typename OutputIt, typename UInt, typename Char>
      auto write_int_localized(OutputIt out, UInt value, unsigned prefix, const basic_format_specs<Char>& specs, const digit_grouping<Char>& grouping) -> OutputIt
      {
        static_assert(rsl::is_same<uint64_or_128_t<UInt>, UInt>::value, "type must be 64 or 128 bit");
        int num_digits = count_digits(value);
        char digits[40]; // NOLINT(modernize-avoid-c-arrays)
        format_decimal(digits, value, num_digits);
        const unsigned size = to_unsigned((prefix != 0 ? 1 : 0) + num_digits + grouping.count_separators(num_digits));
        return write_padded<align::right>(out, specs, size, size,
                                          [&](reserve_iterator<OutputIt> it)
                                          {
                                            if(prefix != 0)
                                            {
                                              char const sign = static_cast<char>(prefix);
                                              *it++           = static_cast<Char>(sign);
                                            }
                                            return grouping.apply(it, string_view(digits, to_unsigned(num_digits))); // NOLINT(cppcoreguidelines-narrowing-conversions, modernize-avoid-c-arrays)
                                          });
      }

      template <typename OutputIt, typename UInt, typename Char>
      auto write_int_localized(OutputIt& out, UInt value, unsigned prefix, const basic_format_specs<Char>& specs, locale_ref loc) -> bool
      {
        auto grouping = digit_grouping<Char>(loc);
        out           = write_int_localized(out, value, prefix, specs, grouping);
        return true;
      }

      FMT_CONSTEXPR inline void prefix_append(unsigned& prefix, unsigned value)
      {
        prefix |= prefix != 0 ? value << 8 : value;
        prefix += (1u + (value > 0xff ? 1 : 0)) << 24;
      }

      template <typename UInt>
      struct write_int_arg
      {
        UInt abs_value;
        unsigned prefix;
      };

      template <typename T>
      FMT_CONSTEXPR auto make_write_int_arg(T value, sign_t sign) -> write_int_arg<uint32_or_64_or_128_t<T>>
      {
        auto prefix    = 0u;
        auto abs_value = static_cast<uint32_or_64_or_128_t<T>>(value);
        if(is_negative(value))
        {
          prefix    = 0x01000000 | '-';
          abs_value = 0 - abs_value;
        }
        else
        {
          constexpr const unsigned prefixes[4] = {0, 0, 0x1000000u | '+', 0x1000000u | ' '}; // NOLINT(modernize-avoid-c-arrays)
          prefix                               = prefixes[sign];
        }
        return {abs_value, prefix};
      }

      template <typename Char, typename OutputIt, typename T>
      FMT_CONSTEXPR FMT_INLINE auto write_int(OutputIt out, write_int_arg<T> arg, const basic_format_specs<Char>& specs, locale_ref loc) -> OutputIt
      {
        static_assert(rsl::is_same<T, uint32_or_64_or_128_t<T>>::value, "T must be 32, 64 or 128 bit");
        auto abs_value = arg.abs_value;
        auto prefix    = arg.prefix;
        switch(specs.type)
        {
          case presentation_type::none:
          case presentation_type::dec:
          {
            if(specs.localized && write_int_localized(out, static_cast<uint64_or_128_t<T>>(abs_value), prefix, specs, loc))
            {
              return out;
            }
            auto num_digits = count_digits(abs_value);
            return write_int(out, num_digits, prefix, specs, [=](reserve_iterator<OutputIt> it) { return format_decimal<Char>(it, abs_value, num_digits).end; });
          }
          case presentation_type::hex_lower:
          case presentation_type::hex_upper:
          {
            const bool upper = specs.type == presentation_type::hex_upper;
            if(specs.alt)
              prefix_append(prefix, unsigned(upper ? 'X' : 'x') << 8 | '0'); // NOLINT(google-readability-casting)
            const int num_digits = count_digits<4>(abs_value);
            return write_int(out, num_digits, prefix, specs, [=](reserve_iterator<OutputIt> it) { return format_uint<4, Char>(it, abs_value, num_digits, upper); });
          }
          case presentation_type::bin_lower:
          case presentation_type::bin_upper:
          {
            const bool upper = specs.type == presentation_type::bin_upper;
            if(specs.alt)
              prefix_append(prefix, unsigned(upper ? 'B' : 'b') << 8 | '0'); // NOLINT(google-readability-casting)
            const int num_digits = count_digits<1>(abs_value);
            return write_int(out, num_digits, prefix, specs, [=](reserve_iterator<OutputIt> it) { return format_uint<1, Char>(it, abs_value, num_digits); });
          }
          case presentation_type::oct:
          {
            const int num_digits = count_digits<3>(abs_value);
            // Octal prefix '0' is counted as a digit, so only add it if precision
            // is not greater than the number of digits.
            if(specs.alt && specs.precision <= num_digits && abs_value != 0)
              prefix_append(prefix, '0');
            return write_int(out, num_digits, prefix, specs, [=](reserve_iterator<OutputIt> it) { return format_uint<3, Char>(it, abs_value, num_digits); });
          }
          case presentation_type::chr: return write_char(out, static_cast<Char>(abs_value), specs);
          default: throw_format_error("invalid type specifier");
        }
        return out;
      }
      template <typename Char, typename OutputIt, typename T>
      FMT_CONSTEXPR FMT_NOINLINE auto write_int_noinline(OutputIt out, write_int_arg<T> arg, const basic_format_specs<Char>& specs, locale_ref loc) -> OutputIt
      {
        return write_int(out, arg, specs, loc);
      }
      template <typename Char, typename OutputIt, typename T, FMT_ENABLE_IF(is_integral<T>::value && !rsl::is_same<T, bool>::value && rsl::is_same<OutputIt, buffer_appender<Char>>::value)>
      FMT_CONSTEXPR FMT_INLINE auto write(OutputIt out, T value, const basic_format_specs<Char>& specs, locale_ref loc) -> OutputIt
      {
        return write_int_noinline(out, make_write_int_arg(value, specs.sign), specs, loc);
      }
      // An inlined version of write used in format string compilation.
      template <typename Char, typename OutputIt, typename T, FMT_ENABLE_IF(is_integral<T>::value && !rsl::is_same<T, bool>::value && !rsl::is_same<OutputIt, buffer_appender<Char>>::value)>
      FMT_CONSTEXPR FMT_INLINE auto write(OutputIt out, T value, const basic_format_specs<Char>& specs, locale_ref loc) -> OutputIt
      {
        return write_int(out, make_write_int_arg(value, specs.sign), specs, loc);
      }

      // An output iterator that counts the number of objects written to it and
      // discards them.
      class counting_iterator
      {
      private:
        count_t m_count;

      public:
        using iterator_category = rsl::output_iterator_tag;
        using difference_type   = rsl::ptrdiff;
        using pointer           = void;
        using reference         = void;
        FMT_UNCHECKED_ITERATOR(counting_iterator);

        struct value_type
        {
          template <typename T>
          FMT_CONSTEXPR value_type& operator=(const T& /*unused*/)
          {
            return *this;
          }
        };

        FMT_CONSTEXPR counting_iterator()
            : m_count(0)
        {
        }

        FMT_CONSTEXPR count_t count() const
        {
          return m_count;
        }

        FMT_CONSTEXPR counting_iterator& operator++()
        {
          ++m_count;
          return *this;
        }
        FMT_CONSTEXPR counting_iterator operator++(int)
        {
          auto it = *this;
          ++*this;
          return it;
        }

        FMT_CONSTEXPR friend counting_iterator operator+(counting_iterator it, difference_type n)
        {
          it.m_count += static_cast<count_t>(n);
          return it;
        }

        FMT_CONSTEXPR value_type operator*() const
        {
          return {};
        }
      };

      template <typename Char, typename OutputIt>
      FMT_CONSTEXPR auto write(OutputIt out, basic_string_view<Char> s, const basic_format_specs<Char>& specs) -> OutputIt
      {
        auto data = s.data();
        auto size = s.size();
        if(specs.precision >= 0 && specs.precision < size)
          size = code_point_index(s, to_unsigned(specs.precision));
        const bool is_debug = specs.type == presentation_type::debug;
        count_t width       = 0;
        if(specs.width != 0)
        {
          if(is_debug)
          {
            width = write_escaped_string(counting_iterator {}, s).count();
          }
          else
          {
            width = compute_width(basic_string_view<Char>(data, size));
          }
        }
        return write_padded(out, specs, size, width,
                            [=](reserve_iterator<OutputIt> it)
                            {
                              if(is_debug)
                                return write_escaped_string(it, s);
                              return copy_str<Char>(data, data + size, it);
                            });
      }
      template <typename Char, typename OutputIt>
      FMT_CONSTEXPR auto write(OutputIt out, basic_string_view<type_identity_t<Char>> s, const basic_format_specs<Char>& specs, locale_ref /*unused*/) -> OutputIt
      {
        check_string_type_spec(specs.type);
        return write(out, s, specs);
      }
      template <typename Char, typename OutputIt>
      FMT_CONSTEXPR auto write(OutputIt out, const Char* s, const basic_format_specs<Char>& specs, locale_ref /*unused*/) -> OutputIt
      {
        return check_cstring_type_spec(specs.type) ? write(out, basic_string_view<Char>(s), specs, {}) : write_ptr<Char>(out, bit_cast<uintptr_t>(s), &specs);
      }

      template <typename Char, typename OutputIt, typename T, FMT_ENABLE_IF(is_integral<T>::value && !rsl::is_same<T, bool>::value && !rsl::is_same<T, Char>::value)>
      FMT_CONSTEXPR auto write(OutputIt out, T value) -> OutputIt
      {
        auto abs_value      = static_cast<uint32_or_64_or_128_t<T>>(value);
        const bool negative = is_negative(value);
        // Don't do -abs_value since it trips unsigned-integer-overflow sanitizer.
        if(negative)
          abs_value = ~abs_value + 1;
        const int num_digits = count_digits(abs_value);
        auto size            = (negative ? 1 : 0) + static_cast<count_t>(num_digits);
        auto it              = reserve(out, size);
        if(auto ptr = to_pointer<Char>(it, size))
        {
          if(negative)
            *ptr++ = static_cast<Char>('-');
          format_decimal<Char>(ptr, abs_value, num_digits);
          return out;
        }
        if(negative)
          *it++ = static_cast<Char>('-');
        it = format_decimal<Char>(it, abs_value, num_digits).end;
        return base_iterator(out, it);
      }

      template <typename Char, typename OutputIt>
      FMT_CONSTEXPR20 auto write_nonfinite(OutputIt out, bool isnan, basic_format_specs<Char> specs, const float_specs& fspecs) -> OutputIt
      {
        const auto* str            = isnan ? (fspecs.upper ? "NAN" : "nan") : (fspecs.upper ? "INF" : "inf");
        constexpr count_t str_size = 3;
        auto sign                  = fspecs.sign;
        auto size                  = str_size + (sign ? 1 : 0);
        // Replace '0'-padding with space for non-finite values.
        const bool is_zero_fill = specs.fill.size() == 1 && *specs.fill.data() == static_cast<Char>('0');
        if(is_zero_fill)
          specs.fill[0] = static_cast<Char>(' ');
        return write_padded(out, specs, size,
                            [=](reserve_iterator<OutputIt> it)
                            {
                              if(sign)
                                *it++ = detail::sign<Char>(sign);
                              return copy_str<Char>(str, str + str_size, it);
                            });
      }

      // A decimal floating-point number significand * pow(10, exp).
      struct big_decimal_fp
      {
        const char* significand;
        int significand_size;
        int exponent;
      };

      constexpr auto get_significand_size(const big_decimal_fp& f) -> int
      {
        return f.significand_size;
      }
      template <typename T>
      inline auto get_significand_size(const dragonbox::decimal_fp<T>& f) -> int
      {
        return count_digits(f.significand);
      }

      template <typename Char, typename OutputIt>
      constexpr auto write_significand(OutputIt out, const char* significand, int significandSize) -> OutputIt
      {
        return copy_str<Char>(significand, significand + significandSize, out);
      }
      template <typename Char, typename OutputIt, typename UInt>
      inline auto write_significand(OutputIt out, UInt significand, int significandSize) -> OutputIt
      {
        return format_decimal<Char>(out, significand, significandSize).end;
      }
      template <typename Char, typename OutputIt, typename T, typename Grouping>
      FMT_CONSTEXPR20 auto write_significand(OutputIt out, T significand, int significandSize, int exponent, const Grouping& grouping) -> OutputIt
      {
        if(!grouping.separator())
        {
          out = write_significand<Char>(out, significand, significandSize);
          return detail::fill_n(out, exponent, static_cast<Char>('0'));
        }
        auto buffer = memory_buffer();
        write_significand<char>(appender(buffer), significand, significandSize);
        detail::fill_n(appender(buffer), exponent, '0');
        return grouping.apply(out, string_view(buffer.data(), buffer.size()));
      }

      template <typename Char, typename UInt, FMT_ENABLE_IF(rsl::is_integral<UInt>::value)>
      inline auto write_significand(Char* out, UInt significand, int significandSize, int integralSize, Char decimalPoint) -> Char*
      {
        if(!decimalPoint)
          return format_decimal(out, significand, significandSize).end;
        out += significandSize + 1;
        Char* end               = out;
        const int floating_size = significandSize - integralSize;
        for(int i = floating_size / 2; i > 0; --i)
        {
          out -= 2;
          copy2(out, digits2(static_cast<count_t>(significand % 100)));
          significand /= 100;
        }
        if(floating_size % 2 != 0)
        {
          *--out = static_cast<Char>('0' + significand % 10);
          significand /= 10;
        }
        *--out = decimalPoint;
        format_decimal(out - integralSize, significand, integralSize);
        return end;
      }

      template <typename OutputIt, typename UInt, typename Char, FMT_ENABLE_IF(!rsl::is_pointer<remove_cvref_t<OutputIt>>::value)>
      inline auto write_significand(OutputIt out, UInt significand, int significandSize, int integralSize, Char decimalPoint) -> OutputIt
      {
        // Buffer is large enough to hold digits (digits10 + 1) and a decimal point.
        Char buffer[digits10<UInt>() + 2]; // NOLINT(modernize-avoid-c-arrays)
        auto end = write_significand(buffer, significand, significandSize, integralSize, decimalPoint);
        return detail::copy_str_noinline<Char>(buffer, end, out);
      }

      template <typename OutputIt, typename Char>
      FMT_CONSTEXPR auto write_significand(OutputIt out, const char* significand, int significandSize, int integralSize, Char decimalPoint) -> OutputIt
      {
        out = detail::copy_str_noinline<Char>(significand, significand + integralSize, out);
        if(!decimalPoint)
          return out;
        *out++ = decimalPoint;
        return detail::copy_str_noinline<Char>(significand + integralSize, significand + significandSize, out);
      }

      template <typename OutputIt, typename Char, typename T, typename Grouping>
      FMT_CONSTEXPR20 auto write_significand(OutputIt out, T significand, int significandSize, int integralSize, Char decimalPoint, const Grouping& grouping) -> OutputIt
      {
        if(!grouping.separator())
        {
          return write_significand(out, significand, significandSize, integralSize, decimalPoint);
        }
        auto buffer = basic_memory_buffer<Char>();
        write_significand(buffer_appender<Char>(buffer), significand, significandSize, integralSize, decimalPoint);
        grouping.apply(out, basic_string_view<Char>(buffer.data(), to_unsigned(integralSize)));
        return detail::copy_str_noinline<Char>(buffer.data() + integralSize, buffer.end(), out);
      }

      template <typename OutputIt, typename DecimalFP, typename Char, typename Grouping = digit_grouping<Char>>
      FMT_CONSTEXPR20 auto do_write_float(OutputIt out, const DecimalFP& f, const basic_format_specs<Char>& specs, float_specs fspecs, locale_ref loc) -> OutputIt // NOLINT(readability-function-cognitive-complexity)
      {
        const auto significand = f.significand; // NOLINT(readability-qualified-auto)
        int significand_size   = get_significand_size(f);
        const Char zero        = static_cast<Char>('0');
        auto sign              = fspecs.sign;
        count_t size           = to_unsigned(significand_size) + (sign ? 1 : 0); // NOLINT(cppcoreguidelines-narrowing-conversions)
        using iterator         = reserve_iterator<OutputIt>;

        Char decimal_point = fspecs.locale ? detail::decimal_point<Char>(loc) : static_cast<Char>('.');

        const int output_exp = f.exponent + significand_size - 1;
        auto use_exp_format  = [=]()
        {
          if(fspecs.format == float_format::exp)
            return true;
          if(fspecs.format != float_format::general)
            return false;
          // Use the fixed notation if the exponent is in [exp_lower, exp_upper),
          // e.g. 0.0001 instead of 1e-04. Otherwise use the exponent notation.
          const int exp_lower = -4, exp_upper = 16; // NOLINT(readability-isolate-declaration)
          return output_exp < exp_lower || output_exp >= (fspecs.precision > 0 ? fspecs.precision : exp_upper);
        };
        if(use_exp_format())
        {
          int num_zeros = 0;
          if(fspecs.showpoint)
          {
            num_zeros = fspecs.precision - significand_size;
            if(num_zeros < 0)
              num_zeros = 0;
            size += to_unsigned(num_zeros); // NOLINT(cppcoreguidelines-narrowing-conversions)
          }
          else if(significand_size == 1)
          {
            decimal_point = Char();
          }
          auto abs_output_exp = output_exp >= 0 ? output_exp : -output_exp;
          int exp_digits      = 2;
          if(abs_output_exp >= 100)
            exp_digits = abs_output_exp >= 1000 ? 4 : 3;

          size += to_unsigned((decimal_point ? 1 : 0) + 2 + exp_digits);
          const char exp_char = fspecs.upper ? 'E' : 'e';
          auto write          = [=](iterator it)
          {
            if(sign)
              *it++ = detail::sign<Char>(sign);
            // Insert a decimal point after the first digit and add an exponent.
            it = write_significand(it, significand, significand_size, 1, decimal_point);
            if(num_zeros > 0)
              it = detail::fill_n(it, num_zeros, zero);
            *it++ = static_cast<Char>(exp_char);
            return write_exponent<Char>(output_exp, it);
          };
          return specs.width > 0 ? write_padded<align::right>(out, specs, size, write) : base_iterator(out, write(reserve(out, size)));
        }

        int exp = f.exponent + significand_size;
        if(f.exponent >= 0)
        {
          // 1234e5 -> 123400000[.0+]
          size += to_unsigned(f.exponent);
          int num_zeros = fspecs.precision - exp;
          abort_fuzzing_if(num_zeros > 5000);
          if(fspecs.showpoint)
          {
            ++size;
            if(num_zeros <= 0 && fspecs.format != float_format::fixed)
              num_zeros = 1;
            if(num_zeros > 0)
              size += to_unsigned(num_zeros); // NOLINT(cppcoreguidelines-narrowing-conversions)
          }
          auto grouping = Grouping(loc, fspecs.locale);
          size += to_unsigned(grouping.count_separators(exp));
          return write_padded<align::right>(out, specs, size,
                                            [&](iterator it)
                                            {
                                              if(sign)
                                                *it++ = detail::sign<Char>(sign);
                                              it = write_significand<Char>(it, significand, significand_size, f.exponent, grouping);
                                              if(!fspecs.showpoint)
                                                return it;
                                              *it++ = decimal_point;
                                              return num_zeros > 0 ? detail::fill_n(it, num_zeros, zero) : it;
                                            });
        }
        else if(exp > 0)
        {
          // 1234e-2 -> 12.34[0+]
          int num_zeros = fspecs.showpoint ? fspecs.precision - significand_size : 0;
          size += 1 + to_unsigned(num_zeros > 0 ? num_zeros : 0); // NOLINT(cppcoreguidelines-narrowing-conversions)
          auto grouping = Grouping(loc, fspecs.locale);
          size += to_unsigned(grouping.count_separators(significand_size));
          return write_padded<align::right>(out, specs, size,
                                            [&](iterator it)
                                            {
                                              if(sign)
                                                *it++ = detail::sign<Char>(sign);
                                              it = write_significand(it, significand, significand_size, exp, decimal_point, grouping);
                                              return num_zeros > 0 ? detail::fill_n(it, num_zeros, zero) : it;
                                            });
        }
        // 1234e-6 -> 0.001234
        int num_zeros = -exp;
        if(significand_size == 0 && fspecs.precision >= 0 && fspecs.precision < num_zeros)
        {
          num_zeros = fspecs.precision;
        }
        const bool pointy = num_zeros != 0 || significand_size != 0 || fspecs.showpoint;
        size += 1 + (pointy ? 1 : 0) + to_unsigned(num_zeros); // NOLINT(cppcoreguidelines-narrowing-conversions)
        return write_padded<align::right>(out, specs, size,
                                          [&](iterator it)
                                          {
                                            if(sign)
                                              *it++ = detail::sign<Char>(sign);
                                            *it++ = zero;
                                            if(!pointy)
                                              return it;
                                            *it++ = decimal_point;
                                            it    = detail::fill_n(it, num_zeros, zero);
                                            return write_significand<Char>(it, significand, significand_size);
                                          });
      }

      template <typename Char>
      class fallback_digit_grouping
      {
      public:
        constexpr fallback_digit_grouping(locale_ref /*unused*/, bool /*unused*/) {}

        constexpr Char separator() const
        {
          return Char();
        }

        constexpr int count_separators(int /*unused*/) const
        {
          return 0;
        }

        template <typename Out, typename C>
        constexpr Out apply(Out out, basic_string_view<C> /*unused*/) const
        {
          return out;
        }
      };

      template <typename OutputIt, typename DecimalFP, typename Char>
      FMT_CONSTEXPR20 auto write_float(OutputIt out, const DecimalFP& f, const basic_format_specs<Char>& specs, float_specs fspecs, locale_ref loc) -> OutputIt
      {
        if(is_constant_evaluated())
        {
          return do_write_float<OutputIt, DecimalFP, Char, fallback_digit_grouping<Char>>(out, f, specs, fspecs, loc);
        }
        else
        {
          return do_write_float(out, f, specs, fspecs, loc);
        }
      }

      template <typename T>
      constexpr bool isnan(T value)
      {
        return !(value >= value); // rsl::isnan doesn't support __float128.
      }

      template <typename T, typename Enable = void>
      struct has_isfinite : rsl::false_type
      {
      };

      template <typename T>
      struct has_isfinite<T, enable_if_t<sizeof(std::isfinite(T())) != 0>> : rsl::true_type
      {
      };

      template <typename T, FMT_ENABLE_IF(rsl::is_floating_point<T>::value&& has_isfinite<T>::value)>
      FMT_CONSTEXPR20 bool isfinite(T value)
      {
        constexpr T inf = T(rsl::numeric_limits<double>::infinity()); // NOLINT(google-readability-casting)
        if(is_constant_evaluated())
          return !detail::isnan(value) && value != inf && value != -inf;
        return std::isfinite(value);
      }
      template <typename T, FMT_ENABLE_IF(!has_isfinite<T>::value)>
      FMT_CONSTEXPR bool isfinite(T value)
      {
        T inf = T(rsl::numeric_limits<double>::infinity());
        // std::isfinite doesn't support __float128.
        return !detail::isnan(value) && value != inf && value != -inf;
      }

      template <typename T, FMT_ENABLE_IF(is_floating_point<T>::value)>
      FMT_INLINE FMT_CONSTEXPR bool signbit(T value)
      {
        if(is_constant_evaluated())
        {
  #ifdef __cpp_if_constexpr
          if constexpr(rsl::numeric_limits<double>::is_iec559)
          {
            auto bits = detail::bit_cast<uint64>(static_cast<double>(value));
            return (bits >> (num_bits<uint64>() - 1)) != 0;
          }
  #endif
        }
        return std::signbit(static_cast<double>(value));
      }

      enum class round_direction
      {
        unknown,
        up,
        down
      };

      // Given the divisor (normally a power of 10), the remainder = v % divisor for
      // some number v and the error, returns whether v should be rounded up, down, or
      // whether the rounding direction can't be determined due to error.
      // error should be less than divisor / 2.
      FMT_CONSTEXPR inline round_direction get_round_direction(uint64 divisor, uint64 remainder, uint64 error)
      {
        FMT_ASSERT(remainder < divisor, "");     // divisor - remainder won't overflow.
        FMT_ASSERT(error < divisor, "");         // divisor - error won't overflow.
        FMT_ASSERT(error < divisor - error, ""); // error * 2 won't overflow.
        // Round down if (remainder + error) * 2 <= divisor.
        if(remainder <= divisor - remainder && error * 2 <= divisor - remainder * 2)
          return round_direction::down;
        // Round up if (remainder - error) * 2 >= divisor.
        if(remainder >= error && remainder - error >= divisor - (remainder - error))
        {
          return round_direction::up;
        }
        return round_direction::unknown;
      }

      namespace digits
      {
        enum result
        {
          more, // Generate more digits.
          done, // Done generating digits.
          error // Digit generation cancelled due to an error.
        };
      } // namespace digits

      struct gen_digits_handler
      {
        char* buf;
        int size;
        int precision;
        int exp10;
        bool fixed;

        FMT_CONSTEXPR digits::result on_digit(char digit, uint64 divisor, uint64 remainder, uint64 error, bool integral)
        {
          FMT_ASSERT(remainder < divisor, "");
          buf[size++] = digit;
          if(!integral && error >= remainder)
            return digits::error;
          if(size < precision)
            return digits::more;
          if(!integral)
          {
            // Check if error * 2 < divisor with overflow prevention.
            // The check is not needed for the integral part because error = 1
            // and divisor > (1 << 32) there.
            if(error >= divisor || error >= divisor - error)
              return digits::error;
          }
          else
          {
            FMT_ASSERT(error == 1 && divisor > 2, "");
          }
          auto dir = get_round_direction(divisor, remainder, error);
          if(dir != round_direction::up)
            return dir == round_direction::down ? digits::done : digits::error;
          ++buf[size - 1];
          for(int i = size - 1; i > 0 && buf[i] > '9'; --i)
          {
            buf[i] = '0';
            ++buf[i - 1];
          }
          if(buf[0] > '9')
          {
            buf[0] = '1';
            if(fixed)
            {
              buf[size++] = '0';
            }
            else
            {
              ++exp10;
            }
          }
          return digits::done;
        }
      };

      inline FMT_CONSTEXPR20 void adjust_precision(int& precision, int exp10)
      {
        // Adjust fixed precision by exponent because it is relative to decimal
        // point.
        if(exp10 > 0 && precision > max_value<int>() - exp10)
          FMT_THROW(format_error("number is too big"));
        precision += exp10;
      }

      // Generates output using the Grisu digit-gen algorithm.
      // error: the size of the region (lower, upper) outside of which numbers
      // definitely do not round to value (Delta in Grisu3).
      FMT_INLINE FMT_CONSTEXPR20 auto grisu_gen_digits(fp value, uint64 error, int& exp, gen_digits_handler& handler) -> digits::result
      {
        const fp one(1ULL << -value.e, value.e);
        // The integral part of scaled value (p1 in Grisu) = value / one. It cannot be
        // zero because it contains a product of two 64-bit numbers with MSB set (due
        // to normalization) - 1, shifted right by at most 60 bits.
        auto integral = static_cast<uint32>(value.f >> -one.e);
        FMT_ASSERT(integral != 0, "");
        FMT_ASSERT(integral == value.f >> -one.e, "");
        // The fractional part of scaled value (p2 in Grisu) c = value % one.
        uint64 fractional = value.f & (one.f - 1);
        exp               = count_digits(integral); // kappa in Grisu.
        // Non-fixed formats require at least one digit and no precision adjustment.
        if(handler.fixed)
        {
          adjust_precision(handler.precision, exp + handler.exp10);
          // Check if precision is satisfied just by leading zeros, e.g.
          // format("{:.2f}", 0.001) gives "0.00" without generating any digits.
          if(handler.precision <= 0)
          {
            if(handler.precision < 0)
              return digits::done;
            // Divide by 10 to prevent overflow.
            const uint64 divisor = data::power_of_10_64[exp - 1] << -one.e;
            auto dir             = get_round_direction(divisor, value.f / 10, error * 10);
            if(dir == round_direction::unknown)
              return digits::error;
            handler.buf[handler.size++] = dir == round_direction::up ? '1' : '0';
            return digits::done;
          }
        }
        // Generate digits for the integral part. This can produce up to 10 digits.
        do
        {
          uint32 digit         = 0;
          auto divmod_integral = [&](uint32 divisor)
          {
            digit = integral / divisor;
            integral %= divisor;
          };
          // This optimization by Milo Yip reduces the number of integer divisions by
          // one per iteration.
          switch(exp)
          {
            case 10: divmod_integral(1000000000); break;
            case 9: divmod_integral(100000000); break;
            case 8: divmod_integral(10000000); break;
            case 7: divmod_integral(1000000); break;
            case 6: divmod_integral(100000); break;
            case 5: divmod_integral(10000); break;
            case 4: divmod_integral(1000); break;
            case 3: divmod_integral(100); break;
            case 2: divmod_integral(10); break;
            case 1:
              digit    = integral;
              integral = 0;
              break;
            default: FMT_ASSERT(false, "invalid number of digits");
          }
          --exp;
          auto remainder = (static_cast<uint64>(integral) << -one.e) + fractional;
          auto result    = handler.on_digit(static_cast<char>('0' + digit), data::power_of_10_64[exp] << -one.e, remainder, error, true);
          if(result != digits::more)
            return result;
        } while(exp > 0);
        // Generate digits for the fractional part.
        for(;;)
        {
          fractional *= 10;
          error *= 10;
          const char digit = static_cast<char>('0' + (fractional >> -one.e));
          fractional &= one.f - 1;
          --exp;
          auto result = handler.on_digit(digit, one.f, fractional, error, false);
          if(result != digits::more)
            return result;
        }
      }

      class bigint
      {
      private:
        // A bigint is stored as an array of bigits (big digits), with bigit at index
        // 0 being the least significant one.
        using bigit        = uint32;
        using double_bigit = uint64;
        enum
        {
          bigits_capacity = 32
        };
        basic_memory_buffer<bigit, bigits_capacity> m_bigits;
        int m_exp;

        FMT_CONSTEXPR20 bigit operator[](int index) const
        {
          return m_bigits[to_unsigned(index)];
        }
        FMT_CONSTEXPR20 bigit& operator[](int index)
        {
          return m_bigits[to_unsigned(index)];
        }

        static constexpr const int bigit_bits = num_bits<bigit>();

        friend struct formatter<bigint>;

        FMT_CONSTEXPR20 void subtract_bigits(int index, bigit other, bigit& borrow)
        {
          auto result    = static_cast<double_bigit>((*this)[index]) - other - borrow;
          (*this)[index] = static_cast<bigit>(result);
          borrow         = static_cast<bigit>(result >> (bigit_bits * 2 - 1));
        }

        FMT_CONSTEXPR20 void remove_leading_zeros()
        {
          int num_bigits = static_cast<int>(m_bigits.size()) - 1;
          while(num_bigits > 0 && (*this)[num_bigits] == 0)
            --num_bigits;
          m_bigits.resize(to_unsigned(num_bigits + 1)); // NOLINT(cppcoreguidelines-narrowing-conversions)
        }

        // Computes *this -= other assuming aligned bigints and *this >= other.
        FMT_CONSTEXPR20 void subtract_aligned(const bigint& other)
        {
          FMT_ASSERT(other.m_exp >= m_exp, "unaligned bigints");
          FMT_ASSERT(compare(*this, other) >= 0, "");
          bigit borrow = 0;
          int i        = other.m_exp - m_exp;
          for(count_t j = 0, n = other.m_bigits.size(); j != n; ++i, ++j)
            subtract_bigits(i, other.m_bigits[j], borrow);
          while(borrow > 0)
            subtract_bigits(i, 0, borrow);
          remove_leading_zeros();
        }

        FMT_CONSTEXPR20 void multiply(uint32 value)
        {
          const double_bigit wide_value = value;
          bigit carry                   = 0;
          for(count_t i = 0, n = m_bigits.size(); i < n; ++i)
          {
            const double_bigit result = m_bigits[i] * wide_value + carry;
            m_bigits[i]               = static_cast<bigit>(result);
            carry                     = static_cast<bigit>(result >> bigit_bits);
          }
          if(carry != 0)
            m_bigits.push_back(carry);
        }

        template <typename UInt, FMT_ENABLE_IF(rsl::is_same<UInt, uint64>::value || rsl::is_same<UInt, uint128_t>::value)>
        FMT_CONSTEXPR20 void multiply(UInt value)
        {
          using half_uint  = conditional_t<rsl::is_same<UInt, uint128_t>::value, uint64, uint32>;
          const int shift  = num_bits<half_uint>() - bigit_bits;
          const UInt lower = static_cast<half_uint>(value);
          const UInt upper = value >> num_bits<half_uint>();
          UInt carry       = 0;
          for(count_t i = 0, n = m_bigits.size(); i < n; ++i)
          {
            UInt result = lower * m_bigits[i] + static_cast<bigit>(carry);
            carry       = (upper * m_bigits[i] << shift) + (result >> bigit_bits) + (carry >> bigit_bits);
            m_bigits[i] = static_cast<bigit>(result);
          }
          while(carry != 0)
          {
            m_bigits.push_back(static_cast<bigit>(carry));
            carry >>= bigit_bits;
          }
        }

        template <typename UInt, FMT_ENABLE_IF(rsl::is_same<UInt, uint64>::value || rsl::is_same<UInt, uint128_t>::value)>
        FMT_CONSTEXPR20 void assign(UInt n)
        {
          count_t num_bigits = 0;
          do
          {
            m_bigits[num_bigits++] = static_cast<bigit>(n);
            n >>= bigit_bits;
          } while(n != 0);
          m_bigits.resize(num_bigits);
          m_exp = 0;
        }

      public:
        FMT_CONSTEXPR20 bigint()
            : m_exp(0)
        {
        }
        explicit bigint(uint64 n) // NOLINT(cppcoreguidelines-pro-type-member-init)
        {
          assign(n);
        }

        ~bigint() = default;

        bigint(const bigint&)         = delete;
        void operator=(const bigint&) = delete;

        FMT_CONSTEXPR20 void assign(const bigint& other)
        {
          auto size = other.m_bigits.size();
          m_bigits.resize(size);
          const auto* data = other.m_bigits.data();
          rsl::copy(data, data + size, make_checked(m_bigits.data(), size));
          m_exp = other.m_exp;
        }

        template <typename Int>
        FMT_CONSTEXPR20 bigint& operator=(Int n)
        {
          FMT_ASSERT(n > 0, "");
          assign(uint64_or_128_t<Int>(n)); // NOLINT(google-readability-casting)
          return *this;
        }

        FMT_CONSTEXPR20 int num_bigits() const
        {
          return static_cast<int>(m_bigits.size()) + m_exp;
        }

        FMT_NOINLINE FMT_CONSTEXPR20 bigint& operator<<=(int shift)
        {
          FMT_ASSERT(shift >= 0, "");
          m_exp += shift / bigit_bits;
          shift %= bigit_bits;
          if(shift == 0)
            return *this;
          bigit carry = 0;
          for(count_t i = 0, n = m_bigits.size(); i < n; ++i)
          {
            const bigit c = m_bigits[i] >> (bigit_bits - shift);
            m_bigits[i]   = (m_bigits[i] << shift) + carry;
            carry         = c;
          }
          if(carry != 0)
            m_bigits.push_back(carry);
          return *this;
        }

        template <typename Int>
        FMT_CONSTEXPR20 bigint& operator*=(Int value)
        {
          FMT_ASSERT(value > 0, "");
          multiply(uint32_or_64_or_128_t<Int>(value)); // NOLINT(google-readability-casting)
          return *this;
        }

        friend FMT_CONSTEXPR20 int compare(const bigint& lhs, const bigint& rhs)
        {
          const int num_lhs_bigits = lhs.num_bigits(), num_rhs_bigits = rhs.num_bigits(); // NOLINT(readability-isolate-declaration)
          if(num_lhs_bigits != num_rhs_bigits)
            return num_lhs_bigits > num_rhs_bigits ? 1 : -1;
          int i   = static_cast<int>(lhs.m_bigits.size()) - 1;
          int j   = static_cast<int>(rhs.m_bigits.size()) - 1;
          int end = i - j;
          if(end < 0)
            end = 0;
          for(; i >= end; --i, --j)
          {
            const bigit lhs_bigit = lhs[i], rhs_bigit = rhs[j]; // NOLINT(readability-isolate-declaration)
            if(lhs_bigit != rhs_bigit)
              return lhs_bigit > rhs_bigit ? 1 : -1;
          }
          if(i != j)
            return i > j ? 1 : -1;
          return 0;
        }

        // Returns compare(lhs1 + lhs2, rhs).
        friend FMT_CONSTEXPR20 int add_compare(const bigint& lhs1, const bigint& lhs2, const bigint& rhs)
        {
          auto minimum             = [](int a, int b) { return a < b ? a : b; };
          auto maximum             = [](int a, int b) { return a > b ? a : b; };
          const int max_lhs_bigits = maximum(lhs1.num_bigits(), lhs2.num_bigits());
          const int num_rhs_bigits = rhs.num_bigits();
          if(max_lhs_bigits + 1 < num_rhs_bigits)
            return -1;
          if(max_lhs_bigits > num_rhs_bigits)
            return 1;
          auto get_bigit      = [](const bigint& n, int i) -> bigit { return i >= n.m_exp && i < n.num_bigits() ? n[i - n.m_exp] : 0; };
          double_bigit borrow = 0;
          const int min_exp   = minimum(minimum(lhs1.m_exp, lhs2.m_exp), rhs.m_exp);
          for(int i = num_rhs_bigits - 1; i >= min_exp; --i)
          {
            const double_bigit sum = static_cast<double_bigit>(get_bigit(lhs1, i)) + get_bigit(lhs2, i);
            const bigit rhs_bigit  = get_bigit(rhs, i);
            if(sum > rhs_bigit + borrow)
              return 1;
            borrow = rhs_bigit + borrow - sum;
            if(borrow > 1)
              return -1;
            borrow <<= bigit_bits;
          }
          return borrow != 0 ? -1 : 0;
        }

        // Assigns pow(10, exp) to this bigint.
        FMT_CONSTEXPR20 void assign_pow10(int exp)
        {
          FMT_ASSERT(exp >= 0, "");
          if(exp == 0)
          {
            *this = 1;
            return;
          }
          // Find the top bit.
          int bitmask = 1;
          while(exp >= bitmask)
            bitmask <<= 1;
          bitmask >>= 1;
          // pow(10, exp) = pow(5, exp) * pow(2, exp). First compute pow(5, exp) by
          // repeated squaring and multiplication.
          *this = 5;
          bitmask >>= 1;
          while(bitmask != 0)
          {
            square();
            if((exp & bitmask) != 0)
              *this *= 5;
            bitmask >>= 1;
          }
          *this <<= exp; // Multiply by pow(2, exp) by shifting.
        }

        FMT_CONSTEXPR20 void square()
        {
          const int num_bigits        = static_cast<int>(m_bigits.size());
          const int num_result_bigits = 2 * num_bigits;
          basic_memory_buffer<bigit, bigits_capacity> n(rsl::move(m_bigits));
          m_bigits.resize(to_unsigned(num_result_bigits)); // NOLINT(cppcoreguidelines-narrowing-conversions)
          auto sum = uint128_t();
          for(int bigit_index = 0; bigit_index < num_bigits; ++bigit_index)
          {
            // Compute bigit at position bigit_index of the result by adding
            // cross-product terms n[i] * n[j] such that i + j == bigit_index.
            for(int i = 0, j = bigit_index; j >= 0; ++i, --j)
            {
              // Most terms are multiplied twice which can be optimized in the future.
              sum += static_cast<double_bigit>(n[i]) * n[j];
            }
            (*this)[bigit_index] = static_cast<bigit>(sum);
            sum >>= num_bits<bigit>(); // Compute the carry.
          }
          // Do the same for the top half.
          for(int bigit_index = num_bigits; bigit_index < num_result_bigits; ++bigit_index)
          {
            for(int j = num_bigits - 1, i = bigit_index - j; i < num_bigits;)
              sum += static_cast<double_bigit>(n[i++]) * n[j--];
            (*this)[bigit_index] = static_cast<bigit>(sum);
            sum >>= num_bits<bigit>();
          }
          remove_leading_zeros();
          m_exp *= 2;
        }

        // If this bigint has a bigger exponent than other, adds trailing zero to make
        // exponents equal. This simplifies some operations such as subtraction.
        FMT_CONSTEXPR20 void align(const bigint& other)
        {
          const int exp_difference = m_exp - other.m_exp;
          if(exp_difference <= 0)
            return;
          const int num_bigits = static_cast<int>(m_bigits.size());
          m_bigits.resize(to_unsigned(num_bigits + exp_difference)); // NOLINT(cppcoreguidelines-narrowing-conversions)
          for(int i = num_bigits - 1, j = i + exp_difference; i >= 0; --i, --j)
            m_bigits[j] = m_bigits[i];
          std::uninitialized_fill_n(m_bigits.data(), exp_difference, 0);
          m_exp -= exp_difference;
        }

        // Divides this bignum by divisor, assigning the remainder to this and
        // returning the quotient.
        FMT_CONSTEXPR20 int divmod_assign(const bigint& divisor)
        {
          FMT_ASSERT(this != &divisor, "");
          if(compare(*this, divisor) < 0)
            return 0;
          FMT_ASSERT(divisor.m_bigits[divisor.m_bigits.size() - 1u] != 0, "");
          align(divisor);
          int quotient = 0;
          do
          {
            subtract_aligned(divisor);
            ++quotient;
          } while(compare(*this, divisor) >= 0);
          return quotient;
        }
      };

      // format_dragon flags.
      enum dragon
      {
        predecessor_closer = 1,
        fixup              = 2, // Run fixup to correct exp10 which can be off by one.
        fixed              = 4,
      };

      // Formats a floating-point number using a variation of the Fixed-Precision
      // Positive Floating-Point Printout ((FPP)^2) algorithm by Steele & White:
      // https://fmt.dev/papers/p372-steele.pdf.
      FMT_CONSTEXPR20 inline void format_dragon(basic_fp<uint128_t> value, unsigned flags, int numDigits, buffer<char>& buf, int& exp10) // NOLINT(readability-function-cognitive-complexity)
      {
        bigint numerator;   // 2 * R in (FPP)^2.
        bigint denominator; // 2 * S in (FPP)^2.
        // lower and upper are differences between value and corresponding boundaries.
        bigint lower;            // (M^- in (FPP)^2).
        bigint upper_store;      // upper's value if different from lower.
        bigint* upper = nullptr; // (M^+ in (FPP)^2).
        // Shift numerator and denominator by an extra bit or two (if lower boundary
        // is closer) to make lower and upper integers. This eliminates multiplication
        // by 2 during later computations.
        const bool is_predecessor_closer = (flags & dragon::predecessor_closer) != 0;
        const int shift                  = is_predecessor_closer ? 2 : 1;
        if(value.e >= 0)
        {
          numerator = value.f;
          numerator <<= value.e + shift;
          lower = 1;
          lower <<= value.e;
          if(is_predecessor_closer)
          {
            upper_store = 1;
            upper_store <<= value.e + 1;
            upper = &upper_store;
          }
          denominator.assign_pow10(exp10);
          denominator <<= shift;
        }
        else if(exp10 < 0)
        {
          numerator.assign_pow10(-exp10);
          lower.assign(numerator);
          if(is_predecessor_closer)
          {
            upper_store.assign(numerator);
            upper_store <<= 1;
            upper = &upper_store;
          }
          numerator *= value.f;
          numerator <<= shift;
          denominator = 1;
          denominator <<= shift - value.e;
        }
        else
        {
          numerator = value.f;
          numerator <<= shift;
          denominator.assign_pow10(exp10);
          denominator <<= shift - value.e;
          lower = 1;
          if(is_predecessor_closer)
          {
            upper_store = 1ULL << 1;
            upper       = &upper_store;
          }
        }
        const int even = static_cast<int>((value.f & 1) == 0);
        if(!upper) // NOLINT(readability-implicit-bool-conversion)
          upper = &lower;
        if((flags & dragon::fixup) != 0)
        {
          if(add_compare(numerator, *upper, denominator) + even <= 0)
          {
            --exp10;
            numerator *= 10;
            if(numDigits < 0)
            {
              lower *= 10;
              if(upper != &lower)
                *upper *= 10;
            }
          }
          if((flags & dragon::fixed) != 0)
            adjust_precision(numDigits, exp10 + 1);
        }
        // Invariant: value == (numerator / denominator) * pow(10, exp10).
        if(numDigits < 0)
        {
          // Generate the shortest representation.
          numDigits  = 0;
          char* data = buf.data();
          for(;;)
          {
            const int digit = numerator.divmod_assign(denominator);
            const bool low  = compare(numerator, lower) - even < 0; // numerator <[=] lower.
            // numerator + upper >[=] pow10:
            const bool high   = add_compare(numerator, *upper, denominator) + even > 0;
            data[numDigits++] = static_cast<char>('0' + digit);
            if(low || high)
            {
              if(!low)
              {
                ++data[numDigits - 1];
              }
              else if(high)
              {
                const int result = add_compare(numerator, numerator, denominator);
                // Round half to even.
                if(result > 0 || (result == 0 && (digit % 2) != 0))
                  ++data[numDigits - 1];
              }
              buf.try_resize(to_unsigned(numDigits)); // NOLINT(cppcoreguidelines-narrowing-conversions)
              exp10 -= numDigits - 1;
              return;
            }
            numerator *= 10;
            lower *= 10;
            if(upper != &lower)
              *upper *= 10;
          }
        }
        // Generate the given number of digits.
        exp10 -= numDigits - 1;
        if(numDigits == 0)
        {
          denominator *= 10;
          auto digit = add_compare(numerator, numerator, denominator) > 0 ? '1' : '0';
          buf.push_back(digit);
          return;
        }
        buf.try_resize(to_unsigned(numDigits)); // NOLINT(cppcoreguidelines-narrowing-conversions)
        for(int i = 0; i < numDigits - 1; ++i)
        {
          const int digit = numerator.divmod_assign(denominator);
          buf[i]          = static_cast<char>('0' + digit);
          numerator *= 10;
        }
        int digit   = numerator.divmod_assign(denominator);
        auto result = add_compare(numerator, numerator, denominator);
        if(result > 0 || (result == 0 && (digit % 2) != 0))
        {
          if(digit == 9)
          {
            const auto overflow = '0' + 10;
            buf[numDigits - 1]  = overflow;
            // Propagate the carry.
            for(int i = numDigits - 1; i > 0 && buf[i] == overflow; --i)
            {
              buf[i] = '0';
              ++buf[i - 1];
            }
            if(buf[0] == overflow)
            {
              buf[0] = '1';
              ++exp10;
            }
            return;
          }
          ++digit;
        }
        buf[numDigits - 1] = static_cast<char>('0' + digit);
      }

      template <typename Float>
      FMT_CONSTEXPR20 auto format_float(Float value, int precision, float_specs specs, buffer<char>& buf) -> int // NOLINT(readability-function-cognitive-complexity)
      {
        // float is passed as double to reduce the number of instantiations.
        static_assert(!rsl::is_same<Float, float>::value, "type must be float");
        FMT_ASSERT(value >= 0, "value is negative");
        auto converted_value = convert_float(value);

        const bool fixed = specs.format == float_format::fixed;
        if(value <= 0)
        { // <= instead of == to silence a warning.
          if(precision <= 0 || !fixed)
          {
            buf.push_back('0');
            return 0;
          }
          buf.try_resize(to_unsigned(precision)); // NOLINT(cppcoreguidelines-narrowing-conversions)
          fill_n(buf.data(), precision, '0');
          return -precision;
        }

        int exp               = 0;
        bool use_dragon       = true;
        unsigned dragon_flags = 0;
        if(!is_fast_float<Float>())
        {
          const auto inv_log2_10 = 0.3010299956639812; // 1 / log2(10)
          using info             = dragonbox::float_info<decltype(converted_value)>;
          const auto f           = basic_fp<typename info::carrier_uint>(converted_value);
          // Compute exp, an approximate power of 10, such that
          //   10^(exp - 1) <= value < 10^exp or 10^exp <= value < 10^(exp + 1).
          // This is based on log10(value) == log2(value) / log2(10) and approximation
          // of log2(value) by e + num_fraction_bits idea from double-conversion.
          exp          = static_cast<int>(rsl::ceil((f.e + count_digits<1>(f.f) - 1) * inv_log2_10 - 1e-10));
          dragon_flags = dragon::fixup;
        }
        else if(!is_constant_evaluated() && precision < 0)
        {
          // Use Dragonbox for the shortest format.
          if(specs.binary32)
          {
            auto dec = dragonbox::to_decimal(static_cast<float>(value));
            write<char>(buffer_appender<char>(buf), dec.significand);
            return dec.exponent;
          }
          auto dec = dragonbox::to_decimal(static_cast<double>(value));
          write<char>(buffer_appender<char>(buf), dec.significand);
          return dec.exponent;
        }
        else
        {
          // Use Grisu + Dragon4 for the given precision:
          // https://www.cs.tufts.edu/~nr/cs257/archive/florian-loitsch/printf.pdf.
          const int min_exp     = -60; // alpha in Grisu.
          int cached_exp10      = 0;   // K in Grisu.
          fp normalized         = normalize(fp(converted_value));
          const auto cached_pow = get_cached_power(min_exp - (normalized.e + fp::num_significand_bits), cached_exp10);
          normalized            = normalized * cached_pow;
          gen_digits_handler handler {buf.data(), 0, precision, -cached_exp10, fixed};
          if(grisu_gen_digits(normalized, 1, exp, handler) != digits::error && !is_constant_evaluated())
          {
            exp += handler.exp10;
            buf.try_resize(to_unsigned(handler.size)); // NOLINT(cppcoreguidelines-narrowing-conversions)
            use_dragon = false;
          }
          else
          {
            exp += handler.size - cached_exp10 - 1;
            precision = handler.precision;
          }
        }
        if(use_dragon)
        {
          auto f                           = basic_fp<uint128_t>();
          const bool is_predecessor_closer = specs.binary32 ? f.assign(static_cast<float>(value)) : f.assign(converted_value);
          if(is_predecessor_closer)
            dragon_flags |= dragon::predecessor_closer;
          if(fixed)
            dragon_flags |= dragon::fixed;
          // Limit precision to the maximum possible number of significant digits in
          // an IEEE754 double because we don't need to generate zeros.
          const int max_double_digits = 767;
          if(precision > max_double_digits)
            precision = max_double_digits;
          format_dragon(f, dragon_flags, precision, buf, exp);
        }
        if(!fixed && !specs.showpoint)
        {
          // Remove trailing zeros.
          auto num_digits = buf.size();
          while(num_digits > 0 && buf[num_digits - 1] == '0')
          {
            --num_digits;
            ++exp;
          }
          buf.try_resize(num_digits);
        }
        return exp;
      }

      template <typename Char, typename OutputIt, typename T, FMT_ENABLE_IF(is_floating_point<T>::value)>
      FMT_CONSTEXPR20 auto write(OutputIt out, T value, basic_format_specs<Char> specs, locale_ref loc = {}) -> OutputIt
      {
        if(const_check(!is_supported_floating_point(value)))
          return out;
        float_specs fspecs = parse_float_type_spec(specs);
        fspecs.sign        = specs.sign;
        if(detail::signbit(value))
        { // value < 0 is false for NaN so use signbit.
          fspecs.sign = sign::minus;
          value       = -value;
        }
        else if(fspecs.sign == sign::minus)
        {
          fspecs.sign = sign::none;
        }

        if(!detail::isfinite(value))
          return write_nonfinite(out, detail::isnan(value), specs, fspecs);

        if(specs.align == align::numeric && fspecs.sign)
        {
          auto it     = reserve(out, 1);
          *it++       = detail::sign<Char>(fspecs.sign);
          out         = base_iterator(out, it);
          fspecs.sign = sign::none;
          if(specs.width != 0)
            --specs.width;
        }

        memory_buffer buffer;
        if(fspecs.format == float_format::hex)
        {
          if(fspecs.sign)
            buffer.push_back(detail::sign<char>(fspecs.sign));
          snprintf_float(convert_float(value), specs.precision, fspecs, buffer);
          return write_bytes<align::right>(out, {buffer.data(), buffer.size()}, specs);
        }
        int precision = specs.precision >= 0 || specs.type == presentation_type::none ? specs.precision : 6;
        if(fspecs.format == float_format::exp)
        {
          if(precision == max_value<int>())
          {
            throw_format_error("number is too big");
          }
          else
          {
            ++precision;
          }
        }
        else if(fspecs.format != float_format::fixed && precision == 0)
        {
          precision = 1;
        }
        if(const_check(rsl::is_same<T, float>()))
          fspecs.binary32 = true;
        const int exp    = format_float(convert_float(value), precision, fspecs, buffer);
        fspecs.precision = precision;
        auto f           = big_decimal_fp {buffer.data(), static_cast<int>(buffer.size()), exp};
        return write_float(out, f, specs, fspecs, loc);
      }

      template <typename Char, typename OutputIt, typename T, FMT_ENABLE_IF(is_fast_float<T>::value)>
      FMT_CONSTEXPR20 auto write(OutputIt out, T value) -> OutputIt
      {
        if(is_constant_evaluated())
          return write(out, value, basic_format_specs<Char>());
        if(const_check(!is_supported_floating_point(value)))
          return out;

        auto fspecs = float_specs();
        if(detail::signbit(value))
        {
          fspecs.sign = sign::minus;
          value       = -value;
        }

        constexpr auto specs = basic_format_specs<Char>();
        using floaty         = conditional_t<rsl::is_same<T, long double>::value, double, T>;
        using uint           = typename dragonbox::float_info<floaty>::carrier_uint;
        const uint mask      = exponent_mask<floaty>();
        if((bit_cast<uint>(value) & mask) == mask)
          return write_nonfinite(out, std::isnan(value), specs, fspecs);

        auto dec = dragonbox::to_decimal(static_cast<floaty>(value));
        return write_float(out, dec, specs, fspecs, {});
      }

      template <typename Char, typename OutputIt, typename T, FMT_ENABLE_IF(is_floating_point<T>::value && !is_fast_float<T>::value)>
      inline auto write(OutputIt out, T value) -> OutputIt
      {
        return write(out, value, basic_format_specs<Char>());
      }

      template <typename Char, typename OutputIt>
      auto write(OutputIt out, monostate /*unused*/, basic_format_specs<Char> /*unused*/ = {}, locale_ref /*unused*/ = {}) -> OutputIt
      {
        FMT_ASSERT(false, "");
        return out;
      }

      template <typename Char, typename OutputIt>
      FMT_CONSTEXPR auto write(OutputIt out, basic_string_view<Char> value) -> OutputIt
      {
        auto it = reserve(out, value.size());
        it      = copy_str_noinline<Char>(value.begin(), value.end(), it);
        return base_iterator(out, it);
      }

      template <typename Char, typename OutputIt, typename T, FMT_ENABLE_IF(is_string<T>::value)>
      constexpr auto write(OutputIt out, const T& value) -> OutputIt
      {
        return write<Char>(out, to_string_view(value));
      }

      // FMT_ENABLE_IF() condition separated to workaround an MSVC bug.
      template <typename Char, typename OutputIt, typename T, bool Check = rsl::is_enum<T>::value && !rsl::is_same<T, Char>::value && mapped_type_constant<T, basic_format_context<OutputIt, Char>>::value != type::custom_type, FMT_ENABLE_IF(Check)>
      FMT_CONSTEXPR auto write(OutputIt out, T value) -> OutputIt
      {
        return write<Char>(out, static_cast<underlying_type_t<T>>(value));
      }

      template <typename Char, typename OutputIt, typename T, FMT_ENABLE_IF(rsl::is_same<T, bool>::value)>
      FMT_CONSTEXPR auto write(OutputIt out, T value, const basic_format_specs<Char>& specs = {}, locale_ref /*unused*/ = {}) -> OutputIt
      {
        return specs.type != presentation_type::none && specs.type != presentation_type::string ? write(out, value ? 1 : 0, specs, {}) : write_bytes(out, value ? string_view("true") : string_view("false"), specs);
      }

      template <typename Char, typename OutputIt>
      FMT_CONSTEXPR auto write(OutputIt out, Char value) -> OutputIt
      {
        auto it = reserve(out, 1);
        *it++   = value;
        return base_iterator(out, it);
      }

      template <typename Char, typename OutputIt>
      FMT_CONSTEXPR_CHAR_TRAITS auto write(OutputIt out, const Char* value) -> OutputIt
      {
        if(!value)
        {
          throw_format_error("string pointer is null");
        }
        else
        {
          out = write(out, basic_string_view<Char>(value));
        }
        return out;
      }

      template <typename Char, typename OutputIt, typename T, FMT_ENABLE_IF(rsl::is_same<T, void>::value)>
      auto write(OutputIt out, const T* value, const basic_format_specs<Char>& specs = {}, locale_ref /*unused*/ = {}) -> OutputIt
      {
        check_pointer_type_spec(specs.type, error_handler());
        return write_ptr<Char>(out, bit_cast<uintptr_t>(value), &specs);
      }

      // A write overload that handles implicit conversions.
      template <typename Char, typename OutputIt, typename T, typename Context = basic_format_context<OutputIt, Char>>
      FMT_CONSTEXPR auto write(OutputIt out, const T& value)
          -> enable_if_t<rsl::is_class<T>::value && !is_string<T>::value && !is_floating_point<T>::value && !rsl::is_same<T, Char>::value && !rsl::is_same<const T&, decltype(arg_mapper<Context>().map(value))>::value, OutputIt>
      {
        return write<Char>(out, arg_mapper<Context>().map(value));
      }

      template <typename Char, typename OutputIt, typename T, typename Context = basic_format_context<OutputIt, Char>>
      FMT_CONSTEXPR auto write(OutputIt out, const T& value) -> enable_if_t<mapped_type_constant<T, Context>::value == type::custom_type, OutputIt>
      {
        using formatter_type = conditional_t<has_formatter<T, Context>::value, typename Context::template formatter_type<T>, fallback_formatter<T, Char>>;
        auto ctx             = Context(out, {}, {});
        return formatter_type().format(value, ctx);
      }

      // An argument visitor that formats the argument and writes it via the output
      // iterator. It's a class and not a generic lambda for compatibility with C++11.
      template <typename Char>
      struct default_arg_formatter
      {
        using iterator = buffer_appender<Char>;
        using context  = buffer_context<Char>;

        iterator out;
        basic_format_args<context> args;
        locale_ref loc;

        template <typename T>
        auto operator()(T value) -> iterator
        {
          return write<Char>(out, value);
        }
        auto operator()(typename basic_format_arg<context>::handle h) -> iterator
        {
          basic_format_parse_context<Char> parse_ctx({});
          context format_ctx(out, args, loc);
          h.format(parse_ctx, format_ctx);
          return format_ctx.out();
        }
      };

      template <typename Char>
      struct arg_formatter
      {
        using iterator = buffer_appender<Char>;
        using context  = buffer_context<Char>;

        iterator out;
        const basic_format_specs<Char>& specs; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
        locale_ref locale;

        template <typename T>
        FMT_CONSTEXPR FMT_INLINE auto operator()(T value) -> iterator
        {
          return detail::write(out, value, specs, locale);
        }
        auto operator()(typename basic_format_arg<context>::handle /*unused*/) -> iterator
        {
          // User-defined types are handled separately because they require access
          // to the parse context.
          return out;
        }
      };

      template <typename Char>
      struct custom_formatter
      {
        basic_format_parse_context<Char>& parse_ctx; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
        buffer_context<Char>& ctx;                   // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)

        void operator()(typename basic_format_arg<buffer_context<Char>>::handle h) const
        {
          h.format(parse_ctx, ctx);
        }
        template <typename T>
        void operator()(T /*unused*/) const
        {
        }
      };

      template <typename T>
      using is_integer = bool_constant<is_integral<T>::value && !rsl::is_same<T, bool>::value && !rsl::is_same<T, char>::value && !rsl::is_same<T, wchar_t>::value>;

      template <typename ErrorHandler>
      class width_checker
      {
      public:
        explicit FMT_CONSTEXPR width_checker(ErrorHandler& eh)
            : m_handler(eh)
        {
        }

        template <typename T, FMT_ENABLE_IF(is_integer<T>::value)>
        FMT_CONSTEXPR auto operator()(T value) -> unsigned long long
        {
          if(is_negative(value))
            m_handler.on_error("negative width");
          return static_cast<unsigned long long>(value);
        }

        template <typename T, FMT_ENABLE_IF(!is_integer<T>::value)>
        FMT_CONSTEXPR auto operator()(T /*unused*/) -> unsigned long long
        {
          m_handler.on_error("width is not integer");
          return 0;
        }

      private:
        ErrorHandler& m_handler; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
      };

      template <typename ErrorHandler>
      class precision_checker
      {
      public:
        explicit FMT_CONSTEXPR precision_checker(ErrorHandler& eh)
            : m_handler(eh)
        {
        }

        template <typename T, FMT_ENABLE_IF(is_integer<T>::value)>
        FMT_CONSTEXPR auto operator()(T value) -> unsigned long long
        {
          if(is_negative(value))
            m_handler.on_error("negative precision");
          return static_cast<unsigned long long>(value);
        }

        template <typename T, FMT_ENABLE_IF(!is_integer<T>::value)>
        FMT_CONSTEXPR auto operator()(T /*unused*/) -> unsigned long long
        {
          m_handler.on_error("precision is not integer");
          return 0;
        }

      private:
        ErrorHandler& m_handler; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
      };

      template <template <typename> class Handler, typename FormatArg, typename ErrorHandler>
      FMT_CONSTEXPR auto get_dynamic_spec(FormatArg arg, ErrorHandler eh) -> int
      {
        const unsigned long long value = visit_format_arg(Handler<ErrorHandler>(eh), arg);
        if(value > to_unsigned(max_value<int>()))
          eh.on_error("number is too big");
        return static_cast<int>(value);
      }

      template <typename Context, typename ID>
      FMT_CONSTEXPR auto get_arg(Context& ctx, ID id) -> typename Context::format_arg
      {
        auto arg = ctx.arg(id);
        if(!arg)
          ctx.on_error("argument not found");
        return arg;
      }

      // The standard format specifier handler with checking.
      template <typename Char>
      class specs_handler : public specs_setter<Char>
      {
      private:
        basic_format_parse_context<Char>& m_parse_context; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
        buffer_context<Char>& m_context;                   // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)

        // This is only needed for compatibility with gcc 4.4.
        using format_arg = basic_format_arg<buffer_context<Char>>;

        FMT_CONSTEXPR auto get_arg(auto_id /*unused*/) -> format_arg
        {
          return detail::get_arg(m_context, m_parse_context.next_arg_id());
        }

        FMT_CONSTEXPR auto get_arg(int argId) -> format_arg
        {
          m_parse_context.check_arg_id(argId);
          return detail::get_arg(m_context, argId);
        }

        FMT_CONSTEXPR auto get_arg(basic_string_view<Char> argId) -> format_arg
        {
          m_parse_context.check_arg_id(argId);
          return detail::get_arg(m_context, argId);
        }

      public:
        FMT_CONSTEXPR specs_handler(basic_format_specs<Char>& specs, basic_format_parse_context<Char>& parseCtx, buffer_context<Char>& ctx)
            : specs_setter<Char>(specs)
            , m_parse_context(parseCtx)
            , m_context(ctx)
        {
        }

        template <typename Id>
        FMT_CONSTEXPR void on_dynamic_width(Id argId)
        {
          this->m_specs.width = get_dynamic_spec<width_checker>(get_arg(argId), m_context.error_handler());
        }

        template <typename Id>
        FMT_CONSTEXPR void on_dynamic_precision(Id argId)
        {
          this->m_specs.precision = get_dynamic_spec<precision_checker>(get_arg(argId), m_context.error_handler());
        }

        void on_error(const char* message)
        {
          m_context.on_error(message);
        }
      };

      template <template <typename> class Handler, typename Context>
      FMT_CONSTEXPR void handle_dynamic_spec(int& value, arg_ref<typename Context::char_type> ref, Context& ctx)
      {
        switch(ref.kind)
        {
          case arg_id_kind::none: break;
          case arg_id_kind::index: value = detail::get_dynamic_spec<Handler>(ctx.arg(ref.val.index), ctx.error_handler()); break;
          case arg_id_kind::name: value = detail::get_dynamic_spec<Handler>(ctx.arg(ref.val.name), ctx.error_handler()); break;
        }
      }

  #if FMT_USE_USER_DEFINED_LITERALS
      template <typename Char>
      struct udl_formatter
      {
        basic_string_view<Char> str;

        template <typename... T>
        auto operator()(T&&... args) const -> rsl::stack_string<Char, 512>
        {
          return vformat(str, rsl::make_format_args<buffer_context<Char>>(args...));
        }
      };

    #if FMT_USE_NONTYPE_TEMPLATE_ARGS
      template <typename T, typename Char, count_t N, rsl::detail_exported::fixed_string<Char, N> Str>
      struct statically_named_arg : view
      {
        static constexpr auto name = Str.data;

        const T& value;
        statically_named_arg(const T& v)
            : value(v)
        {
        }
      };

      template <typename T, typename Char, count_t N, rsl::detail_exported::fixed_string<Char, N> Str>
      struct is_named_arg<statically_named_arg<T, Char, N, Str>> : rsl::true_type
      {
      };

      template <typename T, typename Char, count_t N, rsl::detail_exported::fixed_string<Char, N> Str>
      struct is_statically_named_arg<statically_named_arg<T, Char, N, Str>> : rsl::true_type
      {
      };

      template <typename Char, count_t N, rsl::detail_exported::fixed_string<Char, N> Str>
      struct udl_arg
      {
        template <typename T>
        auto operator=(T&& value) const
        {
          return statically_named_arg<T, Char, N, Str>(rsl::forward<T>(value));
        }
      };
    #else
      template <typename Char>
      struct udl_arg
      {
        const Char* str;

        template <typename T>
        auto operator=(T&& value) const -> named_arg<Char, T> // NOLINT(misc-unconventional-assign-operator, cppcoreguidelines-c-copy-assignment-signature)
        {
          return {str, rsl::forward<T>(value)};
        }
      };
    #endif
  #endif // FMT_USE_USER_DEFINED_LITERALS

      template <typename Locale, typename Char>
      auto vformat(const Locale& loc, basic_string_view<Char> formatStr, basic_format_args<buffer_context<type_identity_t<Char>>> args) -> rsl::stack_string<Char, 512>
      {
        basic_memory_buffer<Char> buffer;
        detail::vformat_to(buffer, formatStr, args, detail::locale_ref(loc));
        return {buffer.data(), buffer.size()};
      }

      using format_func = void (*)(detail::buffer<char>&, int, const char*);

      FMT_API void format_error_code(buffer<char>& out, int errorCode, string_view message) noexcept;

      FMT_API void report_error(format_func func, int errorCode, const char* message) noexcept;
    } // namespace detail

    FMT_API auto vsystem_error(int errorCode, string_view formatStr, format_args args) -> std::system_error;

    /**
     \rst
     Constructs :class:`std::system_error` with a message formatted with
     ``rsl::format(fmt, args...)``.
      *error_code* is a system error code as given by ``errno``.

     **Example**::

       // This throws std::system_error with the description
       //   cannot open file 'madeup': No such file or directory
       // or similar (system message may vary).
       const char* filename = "madeup";
       std::FILE* file = rsl::fopen(filename, "r");
       if (!file)
         throw rsl::system_error(errno, "cannot open file '{}'", filename);
     \endrst
    */
    template <typename... T>
    auto system_error(int errorCode, format_string<T...> fmt, T&&... args) -> std::system_error
    {
      return vsystem_error(errorCode, fmt, rsl::make_format_args(args...));
    }

    /**
      \rst
      Formats an error message for an error returned by an operating system or a
      language runtime, for example a file opening error, and writes it to *out*.
      The format is the same as the one used by ``std::system_error(ec, message)``
      where ``ec`` is ``rsl::error_code(error_code, rsl::generic_category()})``.
      It is implementation-defined but normally looks like:

      .. parsed-literal::
         *<message>*: *<system-message>*

      where *<message>* is the passed message and *<system-message>* is the system
      message corresponding to the error code.
      *error_code* is a system error code as given by ``errno``.
      \endrst
     */
    FMT_API void format_system_error(detail::buffer<char>& out, int errorCode, const char* message) noexcept;

    // Reports a system error without throwing an exception.
    // Can be used to report errors from destructors.
    FMT_API void report_system_error(int errorCode, const char* message) noexcept;

    /** Fast integer formatter. */
    class format_int
    {
    private:
      // Buffer should be large enough to hold all digits (digits10 + 1),
      // a sign and a null character.
      enum
      {
        buffer_size = rsl::numeric_limits<unsigned long long>::digits10 + 3
      };
      mutable char m_buffer[buffer_size]; // NOLINT(modernize-avoid-c-arrays)
      char* m_str;

      template <typename UInt>
      auto format_unsigned(UInt value) -> char*
      {
        auto n = static_cast<detail::uint32_or_64_or_128_t<UInt>>(value);
        return detail::format_decimal(m_buffer, n, buffer_size - 1).begin;
      }

      template <typename Int>
      auto format_signed(Int value) -> char* // NOLINT(cppcoreguidelines-pro-type-member-init)
      {
        auto abs_value      = static_cast<detail::uint32_or_64_or_128_t<Int>>(value);
        const bool negative = value < 0;
        if(negative)
          abs_value = 0 - abs_value;
        auto begin = format_unsigned(abs_value);
        if(negative)
          *--begin = '-';
        return begin;
      }

    public:
      explicit format_int(int value) // NOLINT(cppcoreguidelines-pro-type-member-init)
          : m_str(format_signed(value))
      {
      }
      explicit format_int(long value) // NOLINT(cppcoreguidelines-pro-type-member-init)
          : m_str(format_signed(value))
      {
      }
      explicit format_int(long long value) // NOLINT(cppcoreguidelines-pro-type-member-init)
          : m_str(format_signed(value))
      {
      }
      explicit format_int(unsigned value) // NOLINT(cppcoreguidelines-pro-type-member-init)
          : m_str(format_unsigned(value))
      {
      }
      explicit format_int(unsigned long value) // NOLINT(cppcoreguidelines-pro-type-member-init)
          : m_str(format_unsigned(value))
      {
      }
      explicit format_int(unsigned long long value) // NOLINT(cppcoreguidelines-pro-type-member-init)
          : m_str(format_unsigned(value))
      {
      }

      /** Returns the number of characters written to the output buffer. */
      auto size() const -> count_t
      {
        return detail::to_unsigned(static_cast<count_t>(m_buffer - m_str + buffer_size - 1)); // NOLINT(cppcoreguidelines-narrowing-conversions)
      }

      /**
        Returns a pointer to the output buffer content. No terminating null
        character is appended.
       */
      auto data() const -> const char*
      {
        return m_str;
      }

      /**
        Returns a pointer to the output buffer content with terminating null
        character appended.
       */
      auto c_str() const -> const char*
      {
        m_buffer[buffer_size - 1] = '\0';
        return m_str;
      }

      /**
        \rst
        Returns the content of the output buffer as an ``rsl::string``.
        \endrst
       */
      auto str() const -> rsl::string
      {
        return rsl::string(m_str, size());
      }
    };

    template <typename T, typename Char>
    template <typename FormatContext>
    FMT_CONSTEXPR FMT_INLINE auto formatter<T, Char, enable_if_t<detail::type_constant<T, Char>::value != detail::type::custom_type>>::format(const T& val, FormatContext& ctx) const -> decltype(ctx.out())
    {
      if(m_specs.width_ref.kind != detail::arg_id_kind::none || m_specs.precision_ref.kind != detail::arg_id_kind::none)
      {
        auto specs = m_specs;
        detail::handle_dynamic_spec<detail::width_checker>(specs.width, specs.width_ref, ctx);
        detail::handle_dynamic_spec<detail::precision_checker>(specs.precision, specs.precision_ref, ctx);
        return detail::write<Char>(ctx.out(), val, specs, ctx.locale());
      }
      return detail::write<Char>(ctx.out(), val, m_specs, ctx.locale());
    }

    template <typename Char>
    struct formatter<void*, Char> : formatter<const void*, Char>
    {
      template <typename FormatContext>
      auto format(void* val, FormatContext& ctx) const -> decltype(ctx.out())
      {
        return formatter<const void*, Char>::format(val, ctx);
      }
    };

    template <typename Char, count_t N>
    struct formatter<Char[N], Char> : formatter<basic_string_view<Char>, Char> // NOLINT(modernize-avoid-c-arrays)
    {
      template <typename FormatContext>
      FMT_CONSTEXPR auto format(const Char* val, FormatContext& ctx) const -> decltype(ctx.out())
      {
        return formatter<basic_string_view<Char>, Char>::format(rsl::string_view(val), ctx);
      }
    };

    // A formatter for types known only at run time such as variant alternatives.
    //
    // Usage:
    //   using variant = rsl::variant<int, rsl::string>;
    //   template <>
    //   struct formatter<variant>: dynamic_formatter<> {
    //     auto format(const variant& v, format_context& ctx) {
    //       return visit([&](const auto& val) {
    //           return dynamic_formatter<>::format(val, ctx);
    //       }, v);
    //     }
    //   };
    template <typename Char = char>
    class dynamic_formatter
    {
    private:
      detail::dynamic_format_specs<Char> m_specs;
      const Char* m_format_str;

      struct null_handler : detail::error_handler
      {
        void on_align(align_t /*unused*/) {}
        void on_sign(sign_t /*unused*/) {}
        void on_hash() {}
      };

      template <typename Context>
      void handle_specs(Context& ctx)
      {
        detail::handle_dynamic_spec<detail::width_checker>(m_specs.width, m_specs.width_ref, ctx);
        detail::handle_dynamic_spec<detail::precision_checker>(m_specs.precision, m_specs.precision_ref, ctx);
      }

    public:
      template <typename ParseContext>
      FMT_CONSTEXPR auto parse(ParseContext& ctx) -> decltype(ctx.begin())
      {
        m_format_str = ctx.begin();
        // Checks are deferred to formatting time when the argument type is known.
        detail::dynamic_specs_handler<ParseContext> handler(m_specs, ctx);
        return detail::parse_format_specs(ctx.begin(), ctx.end(), handler);
      }

      template <typename T, typename FormatContext>
      auto format(const T& val, FormatContext& ctx) -> decltype(ctx.out())
      {
        handle_specs(ctx);
        detail::specs_checker<null_handler> checker(null_handler(), detail::mapped_type_constant<T, FormatContext>::value);
        checker.on_align(m_specs.align);
        if(m_specs.sign != sign::none)
          checker.on_sign(m_specs.sign);
        if(m_specs.alt)
          checker.on_hash();
        if(m_specs.precision >= 0)
          checker.end_precision();
        return detail::write<Char>(ctx.out(), val, m_specs, ctx.locale());
      }
    };

    /**
      \rst
      Converts ``p`` to ``const void*`` for pointer formatting.

      **Example**::

        auto s = rsl::format("{}", rsl::ptr(p));
      \endrst
     */
    template <typename T>
    auto ptr(T p) -> const void*
    {
      static_assert(rsl::is_pointer<T>::value, "");
      return detail::bit_cast<const void*>(p);
    }
    template <typename T>
    auto ptr(const rsl::unique_ptr<T, rsl::default_delete<T>>& p) -> const void*
    {
      return p.get();
    }
    template <typename T>
    auto ptr(const rsl::shared_ptr<T>& p) -> const void*
    {
      return p.get();
    }

    /**
      \rst
      Converts ``e`` to the underlying type.

      **Example**::

        enum class color { red, green, blue };
        auto s = rsl::format("{}", rsl::underlying(color::red));
      \endrst
     */
    template <typename Enum>
    constexpr auto underlying(Enum e) noexcept -> underlying_type_t<Enum>
    {
      return static_cast<underlying_type_t<Enum>>(e);
    }

    namespace enums
    {
      template <typename Enum, FMT_ENABLE_IF(rsl::is_enum<Enum>::value)>
      constexpr auto format_as(Enum e) noexcept -> underlying_type_t<Enum>
      {
        return static_cast<underlying_type_t<Enum>>(e);
      }
    } // namespace enums

    class bytes
    {
    private:
      string_view m_data;
      friend struct formatter<bytes>;

    public:
      explicit bytes(string_view data)
          : m_data(data)
      {
      }
    };

    template <>
    struct formatter<bytes>
    {
    private:
      detail::dynamic_format_specs<char> m_specs;

    public:
      template <typename ParseContext>
      FMT_CONSTEXPR auto parse(ParseContext& ctx) -> decltype(ctx.begin())
      {
        using handler_type = detail::dynamic_specs_handler<ParseContext>;
        detail::specs_checker<handler_type> handler(handler_type(m_specs, ctx), detail::type::string_type);
        auto it = parse_format_specs(ctx.begin(), ctx.end(), handler);
        detail::check_string_type_spec(m_specs.type, ctx.error_handler());
        return it;
      }

      template <typename FormatContext>
      auto format(bytes b, FormatContext& ctx) -> decltype(ctx.out())
      {
        detail::handle_dynamic_spec<detail::width_checker>(m_specs.width, m_specs.width_ref, ctx);
        detail::handle_dynamic_spec<detail::precision_checker>(m_specs.precision, m_specs.precision_ref, ctx);
        return detail::write_bytes(ctx.out(), b.m_data, m_specs);
      }
    };

    // group_digits_view is not derived from view because it copies the argument.
    template <typename T>
    struct group_digits_view
    {
      T value;
    };

    /**
      \rst
      Returns a view that formats an integer value using ',' as a locale-independent
      thousands separator.

      **Example**::

        rsl::print("{}", rsl::group_digits(12345));
        // Output: "12,345"
      \endrst
     */
    template <typename T>
    auto group_digits(T value) -> group_digits_view<T>
    {
      return {value};
    }

    template <typename T>
    struct formatter<group_digits_view<T>> : formatter<T>
    {
    private:
      detail::dynamic_format_specs<char> m_specs;

    public:
      template <typename ParseContext>
      FMT_CONSTEXPR auto parse(ParseContext& ctx) -> decltype(ctx.begin())
      {
        using handler_type = detail::dynamic_specs_handler<ParseContext>;
        detail::specs_checker<handler_type> handler(handler_type(m_specs, ctx), detail::type::int_type);
        auto it = parse_format_specs(ctx.begin(), ctx.end(), handler);
        detail::check_string_type_spec(m_specs.type, ctx.error_handler());
        return it;
      }

      template <typename FormatContext>
      auto format(group_digits_view<T> t, FormatContext& ctx) -> decltype(ctx.out())
      {
        detail::handle_dynamic_spec<detail::width_checker>(m_specs.width, m_specs.width_ref, ctx);
        detail::handle_dynamic_spec<detail::precision_checker>(m_specs.precision, m_specs.precision_ref, ctx);
        return detail::write_int_localized(ctx.out(), static_cast<detail::uint64_or_128_t<T>>(t.value), 0, m_specs, detail::digit_grouping<char>({"\3", ','}));
      }
    };

    template <typename Iter, typename Sentinel, typename Char = char>
    struct join_view : detail::view
    {
      Iter begin;
      Sentinel end;
      basic_string_view<Char> sep;

      join_view(Iter b, Sentinel sentinel, basic_string_view<Char> s)
          : begin(b)
          , end(sentinel)
          , sep(s)
      {
      }

      template <typename StringType = rsl::basic_string<Char>>
      auto as_string()
      {
        StringType res;
        for(auto it = begin; it != end; ++it)
        {
          res += *it;
          res += sep;
        }

        if(!res.empty())
        {
          res.resize(res.size() - sep.length());
        }

        return res;
      }
    };

    template <typename Iter, typename Sentinel, typename Char>
    struct formatter<join_view<Iter, Sentinel, Char>, Char>
    {
    private:
      using value_type =
  #ifdef __cpp_lib_ranges
          rsl::iter_val_t<Iter>;
  #else
          typename rsl::iterator_traits<Iter>::value_type;
  #endif
      using context = buffer_context<Char>;
      using mapper  = detail::arg_mapper<context>;

      template <typename T, FMT_ENABLE_IF(has_formatter<T, context>::value)>
      static auto map(const T& value) -> const T&
      {
        return value;
      }
      template <typename T, FMT_ENABLE_IF(!has_formatter<T, context>::value)>
      static auto map(const T& value) -> decltype(mapper().map(value))
      {
        return mapper().map(value);
      }

      using formatter_type = conditional_t<is_formattable<value_type, Char>::value, formatter<remove_cvref_t<decltype(map(rsl::declval<const value_type&>()))>, Char>, detail::fallback_formatter<value_type, Char>>;

      formatter_type m_value_formatter;

    public:
      template <typename ParseContext>
      FMT_CONSTEXPR auto parse(ParseContext& ctx) -> decltype(ctx.begin())
      {
        return m_value_formatter.parse(ctx);
      }

      template <typename FormatContext>
      auto format(const join_view<Iter, Sentinel, Char>& value, FormatContext& ctx) const -> decltype(ctx.out())
      {
        auto it  = value.begin;
        auto out = ctx.out();
        if(it != value.end)
        {
          out = m_value_formatter.format(map(*it), ctx);
          ++it;
          while(it != value.end)
          {
            out = detail::copy_str<Char>(value.sep.begin(), value.sep.end(), out);
            ctx.advance_to(out);
            out = m_value_formatter.format(map(*it), ctx);
            ++it;
          }
        }
        return out;
      }
    };

    /**
      Returns a view that formats the iterator range `[begin, end)` with elements
      separated by `sep`.
     */
    template <typename It, typename Sentinel>
    auto join(It begin, Sentinel end, string_view sep) -> join_view<It, Sentinel, char8>
    {
      return {begin, end, sep};
    }

    /**
      \rst
      Returns a view that formats `range` with elements separated by `sep`.

      **Example**::

        rsl::vector<int> v = {1, 2, 3};
        rsl::print("{}", rsl::join(v, ", "));
        // Output: "1, 2, 3"

      ``rsl::join`` applies passed format specifiers to the range elements::

        rsl::print("{:02}", rsl::join(v, ", "));
        // Output: "01, 02, 03"
      \endrst
     */
    template <typename Range>
    auto join(Range&& range, string_view sep) -> join_view<detail::iterator_t<Range>, detail::sentinel_t<Range>, char>
    {
      return join(rsl::begin(range), rsl::end(range), sep);
    }

    /**
      \rst
      Converts *value* to ``rsl::string`` using the default format for type *T*.

      **Example**::

        #include <fmt/format.h>

        rsl::string answer = rsl::to_string(42);
      \endrst
     */
    namespace fmt
    {
      template <typename T, FMT_ENABLE_IF(!rsl::is_integral<T>::value && !rsl::is_same_v<T, rsl::wstring> && !rsl::is_same_v<T, rsl::wstring_view>)>
      inline auto to_string(const T& value) -> rsl::big_stack_string
      {
        auto result = rsl::big_stack_string();
        detail::write<char>(rsl::back_inserter(result), value);
        return result;
      }

      template <typename T, FMT_ENABLE_IF(rsl::is_integral<T>::value)>
      FMT_NODISCARD inline auto to_string(T value) -> rsl::tiny_stack_string
      {
        // The buffer should be large enough to store the number including the sign
        // or "false" for bool.
        constexpr int max_size = detail::digits10<T>() + 2;
        char buffer[max_size > 5 ? static_cast<unsigned>(max_size) : 5];
        char* begin = buffer;
        return rsl::tiny_stack_string(begin, detail::write<char>(begin, value));
      }

      template <typename Char, count_t SIZE>
      FMT_NODISCARD auto to_string(const basic_memory_buffer<Char, SIZE>& buf) -> rsl::stack_string<Char, SIZE>
      {
        auto size = buf.size();
        detail::assume(size < rsl::stack_string<Char, SIZE>().max_size());
        return rsl::stack_string<Char, SIZE>(buf.data(), size);
      }
    } // namespace fmt

    namespace detail
    {

      template <typename Char>
      void vformat_to(buffer<Char>& buf, basic_string_view<Char> fmt, basic_format_args<FMT_BUFFER_CONTEXT(type_identity_t<Char>)> args, locale_ref loc)
      {
        // workaround for msvc bug regarding name-lookup in module
        // link names into function scope
        using detail::arg_formatter;
        using detail::buffer_appender;
        using detail::custom_formatter;
        using detail::default_arg_formatter;
        using detail::get_arg;
        using detail::locale_ref;
        using detail::parse_format_specs;
        using detail::specs_checker;
        using detail::specs_handler;
        using detail::to_unsigned;
        using detail::type;
        using detail::write;
        auto out = buffer_appender<Char>(buf);
        if(fmt.size() == 2 && equal2(fmt.data(), "{}"))
        {
          auto arg = args.get(0);
          if(!arg)
            error_handler().on_error("argument not found");
          visit_format_arg(default_arg_formatter<Char> {out, args, loc}, arg);
          return;
        }

        struct format_handler : error_handler
        {
          basic_format_parse_context<Char> parse_context;
          buffer_context<Char> context;

          format_handler(buffer_appender<Char> pOut, basic_string_view<Char> str, basic_format_args<buffer_context<Char>> pArgs, locale_ref pLoc)
              : parse_context(str)
              , context(pOut, pArgs, pLoc)
          {
          }

          void on_text(const Char* begin, const Char* end)
          {
            auto text = basic_string_view<Char>(begin, to_unsigned(static_cast<count_t>(end - begin)));

            context.advance_to(write<Char>(context.out(), text));
          }

          FMT_CONSTEXPR auto on_arg_id() -> int
          {
            return parse_context.next_arg_id();
          }
          FMT_CONSTEXPR auto on_arg_id(int id) -> int
          {
            return parse_context.check_arg_id(id), id;
          }
          FMT_CONSTEXPR auto on_arg_id(basic_string_view<Char> id) -> int
          {
            const int arg_id = context.arg_id(id);
            if(arg_id < 0)
              on_error("argument not found");
            return arg_id;
          }

          FMT_INLINE void on_replacement_field(int id, const Char* /*unused*/)
          {
            auto arg = get_arg(context, id);
            context.advance_to(visit_format_arg(default_arg_formatter<Char> {context.out(), context.args(), context.locale()}, arg));
          }

          auto on_format_specs(int id, const Char* begin, const Char* end) -> const Char*
          {
            auto arg = get_arg(context, id);
            if(arg.type() == type::custom_type)
            {
              parse_context.advance_to(parse_context.begin() + (static_cast<count_t>(begin - &*parse_context.begin())));
              visit_format_arg(custom_formatter<Char> {parse_context, context}, arg);
              return rsl::iterator_to_pointer(parse_context.begin());
            }
            auto specs = basic_format_specs<Char>();
            specs_checker<specs_handler<Char>> handler(specs_handler<Char>(specs, parse_context, context), arg.type());
            begin = parse_format_specs(begin, end, handler);
            if(begin == end || *begin != '}')
              on_error("missing '}' in format string");
            auto f = arg_formatter<Char> {context.out(), specs, context.locale()};
            context.advance_to(visit_format_arg(f, arg));
            return begin;
          }
        };
        detail::parse_format_string<false>(fmt, format_handler(out, fmt, args, loc));
      }

  #ifndef FMT_HEADER_ONLY
      extern template FMT_API auto thousands_sep_impl<char>(locale_ref) -> thousands_sep_result<char>;
      extern template FMT_API auto thousands_sep_impl<wchar_t>(locale_ref) -> thousands_sep_result<wchar_t>;
      extern template FMT_API auto decimal_point_impl(locale_ref) -> char;
      extern template FMT_API auto decimal_point_impl(locale_ref) -> wchar_t;
  #endif // FMT_HEADER_ONLY

    } // namespace detail

  #if FMT_USE_USER_DEFINED_LITERALS
    inline namespace literals
    {
    /**
      \rst
      User-defined literal equivalent of :func:`rsl::arg`.

      **Example**::

        using namespace rsl { inline namespace v1 {::literals;
        rsl::print("Elapsed time: {s:.2f} seconds", "s"_a=1.23);
      \endrst
     */
    #if FMT_USE_NONTYPE_TEMPLATE_ARGS
      template <detail_exported::fixed_string Str>
      constexpr auto operator""_a()
      {
        using char_t = remove_cvref_t<decltype(Str.data[0])>;
        return detail::udl_arg<char_t, sizeof(Str.data) / sizeof(char_t), Str>();
      }
    #else
      constexpr auto operator"" _a(const char* s, size_t /*unused*/) -> detail::udl_arg<char>
      {
        return {s};
      }
    #endif
    }    // namespace literals
  #endif // FMT_USE_USER_DEFINED_LITERALS

    template <typename Locale, FMT_ENABLE_IF(detail::is_locale<Locale>::value)>
    inline auto vformat(const Locale& loc, string_view fmt, format_args args) -> rsl::string
    {
      return detail::vformat(loc, fmt, args);
    }

    template <typename Locale, typename... T, FMT_ENABLE_IF(detail::is_locale<Locale>::value)>
    inline auto format(const Locale& loc, format_string<T...> fmt, T&&... args) -> rsl::string
    {
      return vformat(loc, string_view(fmt), rsl::make_format_args(args...));
    }

    template <typename OutputIt, typename Locale, FMT_ENABLE_IF(detail::is_output_iterator<OutputIt, char>::value&& detail::is_locale<Locale>::value)>
    auto vformat_to(OutputIt out, const Locale& loc, string_view fmt, format_args args) -> OutputIt
    {
      using detail::get_buffer;
      auto&& buf = get_buffer<char>(out);
      detail::vformat_to(buf, fmt, args, detail::locale_ref(loc));
      return detail::get_iterator(buf);
    }

    template <typename OutputIt, typename Locale, FMT_ENABLE_IF(detail::is_output_iterator<OutputIt, tchar>::value&& detail::is_locale<Locale>::value)>
    auto vformat_to(OutputIt out, const Locale& loc, wstring_view fmt, format_args args) -> OutputIt
    {
      using detail::get_buffer;
      auto&& buf = get_buffer<tchar>(out);
      detail::vformat_to(buf, fmt, args, detail::locale_ref(loc));
      return detail::get_iterator(buf);
    }

    template <typename OutputIt, typename Locale, typename... T, FMT_ENABLE_IF(detail::is_output_iterator<OutputIt, char>::value&& detail::is_locale<Locale>::value)>
    FMT_INLINE auto format_to(OutputIt out, const Locale& loc, format_string<T...> fmt, T&&... args) -> OutputIt
    {
      return vformat_to(out, loc, fmt, rsl::make_format_args(args...));
    }

    FMT_MODULE_EXPORT_END
  } // namespace v1
} // namespace rsl

  #ifdef FMT_HEADER_ONLY
    #define FMT_FUNC inline
    #include "format-inl.h"
  #else
    #define FMT_FUNC
  #endif

  #include "rex_std/bonus/string/stack_string.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename CharType, size_t MaxSize>
    struct formatter<stack_string<CharType, MaxSize>>
    {
      auto parse(format_parse_context& ctx) const -> decltype(ctx.begin())
      {
        return ctx.begin();
      }

      template <typename FormatContext>
      auto format(const stack_string<CharType, MaxSize>& str, FormatContext& ctx) -> decltype(ctx.out())
      {
        return format_to(ctx.out(), "{}", str.to_view());
      }
    };
  } // namespace v1
} // namespace rsl

#endif // FMT_FORMAT_H_

// NOLINTEND(fuchsia-trailing-return, hicpp-signed-bitwise, misc-no-recursion)

#include "rex_std/internal/format/xchar.h"
#include "rex_std/internal/assert/assert_impl.h"

#ifdef __clang__
  #pragma clang diagnostic pop
#endif