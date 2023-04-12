// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: enum_reflection.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

//  __  __             _        ______                          _____
// |  \/  |           (_)      |  ____|                        / ____|_     _
// | \  / | __ _  __ _ _  ___  | |__   _ __  _   _ _ __ ___   | |   _| |_ _| |_
// | |\/| |/ _` |/ _` | |/ __| |  __| | '_ \| | | | '_ ` _ \  | |  |_   _|_   _|
// | |  | | (_| | (_| | | (__  | |____| | | | |_| | | | | | | | |____|_|   |_|
// |_|  |_|\__,_|\__, |_|\___| |______|_| |_|\__,_|_| |_| |_|  \_____|
//                __/ | https://github.com/Neargye/magic_enum
//               |___/  version 0.7.3
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// SPDX-License-Identifier: MIT
// Copyright (c) 2019 - 2021 Daniil Goncharov <neargye@gmail.com>.
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef NEARGYE_MAGIC_ENUM_HPP
  #define NEARGYE_MAGIC_ENUM_HPP

  #define MAGIC_ENUM_VERSION_MAJOR 0
  #define MAGIC_ENUM_VERSION_MINOR 7
  #define MAGIC_ENUM_VERSION_PATCH 3

  #include "rex_std/array.h"
  #include "rex_std/assert.h"
  #include "rex_std/bonus/types.h"
  #include "rex_std/iostream.h"
  #include "rex_std/limits.h"
  #include "rex_std/string.h"
  #include "rex_std/string_view.h"
  #include "rex_std/type_traits.h"
  #include "rex_std/utility.h"

  #if defined(MAGIC_ENUM_CONFIG_FILE)
    #include MAGIC_ENUM_CONFIG_FILE
  #endif

  #if !defined(MAGIC_ENUM_USING_ALIAS_OPTIONAL)
    #include "rex_std/optional.h"
  #endif

  #if defined(__clang__)
    #pragma clang diagnostic push
  #elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wmaybe-uninitialized" // May be used uninitialized 'return {};'.
  #elif defined(_MSC_VER)
    #pragma warning(push)
    #pragma warning(disable : 26495) // Variable 'static_string<N>::chars_' is uninitialized.
    #pragma warning(disable : 28020) // Arithmetic overflow: Using operator '-' on a 4 byte value and then casting the result to a 8 byte value.
    #pragma warning(disable : 26451) // The expression '0<=_Param_(1)&&_Param_(1)<=1-1' is not true at this call.
  #endif

  // Checks enum_refl compiler compatibility.
  #if defined(__clang__) && __clang_major__ >= 5 || defined(__GNUC__) && __GNUC__ >= 9 || defined(_MSC_VER) && _MSC_VER >= 1910
    #undef MAGIC_ENUM_SUPPORTED
    #define MAGIC_ENUM_SUPPORTED 1
  #endif

  // Checks enum_refl compiler aliases compatibility.
  #if defined(__clang__) && __clang_major__ >= 5 || defined(__GNUC__) && __GNUC__ >= 9 || defined(_MSC_VER) && _MSC_VER >= 1920
    #undef MAGIC_ENUM_SUPPORTED_ALIASES
    #define MAGIC_ENUM_SUPPORTED_ALIASES 1
  #endif

  // Enum value must be greater or equals than MAGIC_ENUM_RANGE_MIN. By default MAGIC_ENUM_RANGE_MIN = -128.
  // If need another min range for all enum types by default, redefine the macro MAGIC_ENUM_RANGE_MIN.
  #if !defined(MAGIC_ENUM_RANGE_MIN)
    #define MAGIC_ENUM_RANGE_MIN -128
  #endif

  // Enum value must be less or equals than MAGIC_ENUM_RANGE_MAX. By default MAGIC_ENUM_RANGE_MAX = 128.
  // If need another max range for all enum types by default, redefine the macro MAGIC_ENUM_RANGE_MAX.
  #if !defined(MAGIC_ENUM_RANGE_MAX)
    #define MAGIC_ENUM_RANGE_MAX 256
  #endif

namespace rsl
{
  inline namespace v1
  {
    namespace enum_refl
    {

      // If need another optional type, define the macro MAGIC_ENUM_USING_ALIAS_OPTIONAL.
  #if defined(MAGIC_ENUM_USING_ALIAS_OPTIONAL)
      MAGIC_ENUM_USING_ALIAS_OPTIONAL
  #else
      using rsl::optional;
  #endif

      // If need another rsl::string_view type, define the macro MAGIC_ENUM_USING_ALIAS_STRING_VIEW.
  #if defined(MAGIC_ENUM_USING_ALIAS_STRING_VIEW)
      MAGIC_ENUM_USING_ALIAS_STRING_VIEW
  #else
      using rsl::string_view;
  #endif

      // If need another string type, define the macro MAGIC_ENUM_USING_ALIAS_STRING.
  #if defined(MAGIC_ENUM_USING_ALIAS_STRING)
      MAGIC_ENUM_USING_ALIAS_STRING
  #else
      using rsl::string;
  #endif

      namespace customize
      {

        // Enum value must be in range [MAGIC_ENUM_RANGE_MIN, MAGIC_ENUM_RANGE_MAX]. By default MAGIC_ENUM_RANGE_MIN = -128, MAGIC_ENUM_RANGE_MAX = 128.
        // If need another range for all enum types by default, redefine the macro MAGIC_ENUM_RANGE_MIN and MAGIC_ENUM_RANGE_MAX.
        // If need another range for specific enum type, add specialization enum_range for necessary enum type.
        template <typename E>
        struct enum_range
        {
          static_assert(rsl::is_enum_v<E>, "enum_refl::customize::enum_range requires enum type.");
          inline static constexpr int min = MAGIC_ENUM_RANGE_MIN;
          inline static constexpr int max = MAGIC_ENUM_RANGE_MAX;
          static_assert(max > min, "enum_refl::customize::enum_range requires max > min.");
        };

        static_assert(MAGIC_ENUM_RANGE_MIN <= 0, "MAGIC_ENUM_RANGE_MIN must be less or equals than 0.");
        static_assert(MAGIC_ENUM_RANGE_MIN > (rsl::numeric_limits<rsl::int16>::min)(), "MAGIC_ENUM_RANGE_MIN must be greater than INT16_MIN.");

        static_assert(MAGIC_ENUM_RANGE_MAX > 0, "MAGIC_ENUM_RANGE_MAX must be greater than 0.");
        static_assert(MAGIC_ENUM_RANGE_MAX < (rsl::numeric_limits<rsl::int16>::max)(), "MAGIC_ENUM_RANGE_MAX must be less than INT16_MAX.");

        static_assert(MAGIC_ENUM_RANGE_MAX > MAGIC_ENUM_RANGE_MIN, "MAGIC_ENUM_RANGE_MAX must be greater than MAGIC_ENUM_RANGE_MIN.");

        // If need custom names for enum, add specialization enum_name for necessary enum type.
        template <typename E>
        constexpr rsl::string_view enum_name(E) noexcept
        {
          static_assert(rsl::is_enum_v<E>, "enum_refl::customize::enum_name requires enum type.");

          return {};
        }

      } // namespace customize

      namespace detail
      {

        template <typename T>
        struct supported
  #if defined(MAGIC_ENUM_SUPPORTED) && MAGIC_ENUM_SUPPORTED || defined(MAGIC_ENUM_NO_CHECK_SUPPORT)
            : rsl::true_type
        {
        };
  #else
            : rsl::false_type
        {
        };
  #endif

        struct char_equal_to
        {
          constexpr bool operator()(char lhs, char rhs) const noexcept
          {
            return lhs == rhs;
          }
        };

        template <card32 N>
        class static_string
        {
        public:
          constexpr explicit static_string(rsl::string_view str) noexcept
              : static_string {str, rsl::make_index_sequence<N> {}}
          {
            // REX_ASSERT_X(str.size() == N, "invalid static_string length");
          }

          constexpr const char* data() const noexcept
          {
            return chars_;
          }

          constexpr card32 size() const noexcept
          {
            return N;
          }

          constexpr operator rsl::string_view() const noexcept
          {
            return {data(), size()};
          }

        private:
          template <card32... I>
          constexpr static_string(rsl::string_view str, rsl::index_sequence<I...>) noexcept
              : chars_ {str[I]..., '\0'}
          {
          }

          char chars_[N + 1];
        };

        template <>
        class static_string<0>
        {
        public:
          constexpr explicit static_string(rsl::string_view) noexcept {}

          constexpr const char* data() const noexcept
          {
            return nullptr;
          }

          constexpr card32 size() const noexcept
          {
            return 0;
          }

          constexpr operator rsl::string_view() const noexcept
          {
            return {};
          }
        };

        constexpr rsl::string_view pretty_name(rsl::string_view name) noexcept
        {
          for(card32 i = name.size(); i > 0; --i)
          {
            if(!((name[i - 1] >= '0' && name[i - 1] <= '9') || (name[i - 1] >= 'a' && name[i - 1] <= 'z') || (name[i - 1] >= 'A' && name[i - 1] <= 'Z') ||
  #if defined(MAGIC_ENUM_ENABLE_NONASCII)
                 (name[i - 1] & 0x80) ||
  #endif
                 (name[i - 1] == '_')))
            {
              name.remove_prefix(i);
              break;
            }
          }

          if(name.size() > 0 && ((name.front() >= 'a' && name.front() <= 'z') || (name.front() >= 'A' && name.front() <= 'Z') ||
  #if defined(MAGIC_ENUM_ENABLE_NONASCII)
                                 (name.front() & 0x80) ||
  #endif
                                 (name.front() == '_')))
          {
            return name;
          }

          return {}; // Invalid name.
        }

        constexpr card32 find(rsl::string_view str, char c) noexcept
        {
  #if defined(__clang__) && __clang_major__ < 9 && defined(__GLIBCXX__) || defined(_MSC_VER) && _MSC_VER < 1920 && !defined(__clang__)
          // https://stackoverflow.com/questions/56484834/constexpr-stdString-viewfind-last-of-doesnt-work-on-clang-8-with-libstdc
          // https://developercommunity.visualstudio.com/content/problem/360432/vs20178-regression-c-failed-in-test.html
          constexpr bool workaround = true;
  #else
          constexpr bool workaround = false;
  #endif

          if constexpr(workaround)
          {
            for(card32 i = 0; i < str.size(); ++i)
            {
              if(str[i] == c)
              {
                return i;
              }
            }

            return rsl::string_view::npos();
          }
          else
          {
            return str.find_first_of(c);
          }
        }

        template <typename T, card32 N, card32... I>
        constexpr rsl::array<rsl::remove_cv_t<T>, N> to_array(T (&a)[N], rsl::index_sequence<I...>)
        {
          return {{a[I]...}};
        }

        template <typename BinaryPredicate>
        constexpr bool cmp_equal(rsl::string_view lhs, rsl::string_view rhs, BinaryPredicate&& p) noexcept(rsl::is_nothrow_invocable_r_v<bool, BinaryPredicate, char, char>)
        {
  #if defined(_MSC_VER) && _MSC_VER < 1920 && !defined(__clang__)
          // https://developercommunity.visualstudio.com/content/problem/360432/vs20178-regression-c-failed-in-test.html
          // https://developercommunity.visualstudio.com/content/problem/232218/c-constexpr-string-view.html
          constexpr bool workaround = true;
  #else
          constexpr bool workaround = false;
  #endif
          constexpr bool custom_predicate = rsl::negation_v<rsl::is_same<rsl::decay_t<BinaryPredicate>, char_equal_to>>;

          if constexpr(custom_predicate || workaround)
          {
            if(lhs.size() != rhs.size())
            {
              return false;
            }

            const auto size = lhs.size();
            for(card32 i = 0; i < size; ++i)
            {
              if(!p(lhs[i], rhs[i]))
              {
                return false;
              }
            }

            return true;
          }
          else
          {
            static_cast<void>(p);

            return lhs == rhs;
          }
        }

        template <typename L, typename R>
        constexpr bool cmp_less(L lhs, R rhs) noexcept
        {
          static_assert(rsl::is_integral_v<L> && rsl::is_integral_v<R>, "enum_refl::detail::cmp_less requires integral type.");

          if constexpr(rsl::is_signed_v<L> == rsl::is_signed_v<R>)
          {
            // If same signedness (both signed or both unsigned).
            return lhs < rhs;
          }
          else if constexpr(rsl::is_same_v<L, bool>)
          { // bool special case due to msvc's C4804, C4018
            return static_cast<R>(lhs) < rhs;
          }
          else if constexpr(rsl::is_same_v<R, bool>)
          { // bool special case due to msvc's C4804, C4018
            return lhs < static_cast<L>(rhs);
          }
          else if constexpr(rsl::is_signed_v<R>)
          {
            // If 'right' is negative, then result is 'false', otherwise cast & compare.
            return rhs > 0 && lhs < static_cast<rsl::make_unsigned_t<R>>(rhs);
          }
          else
          {
            // If 'left' is negative, then result is 'true', otherwise cast & compare.
            return lhs < 0 || static_cast<rsl::make_unsigned_t<L>>(lhs) < rhs;
          }
        }

        template <typename I>
        constexpr I log2(I value) noexcept
        {
          static_assert(rsl::is_integral_v<I>, "enum_refl::detail::log2 requires integral type.");

          auto ret = I {0};
          for(; value > I {1}; value >>= I {1}, ++ret)
          {
          }

          return ret;
        }

        template <typename I>
        constexpr bool is_pow2(I x) noexcept
        {
          static_assert(rsl::is_integral_v<I>, "enum_refl::detail::is_pow2 requires integral type.");

          return x != 0 && (x & (x - 1)) == 0;
        }

        template <typename T>
        inline constexpr bool is_enum_v = rsl::is_enum_v<T> && rsl::is_same_v<T, rsl::decay_t<T>>;

        template <typename E>
        constexpr auto n() noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::n requires enum type.");
  #if defined(MAGIC_ENUM_SUPPORTED) && MAGIC_ENUM_SUPPORTED
    #if defined(__clang__)
          constexpr rsl::string_view name {__PRETTY_FUNCTION__ + 34, sizeof(__PRETTY_FUNCTION__) - 36};
    #elif defined(__GNUC__)
          constexpr rsl::string_view name {__PRETTY_FUNCTION__ + 49, sizeof(__PRETTY_FUNCTION__) - 51};
    #elif defined(_MSC_VER)
          constexpr rsl::string_view name {__FUNCSIG__ + 40, sizeof(__FUNCSIG__) - 57};
    #endif
          return static_string<name.size()> {name};
  #else
          return rsl::string_view {};   // Unsupported compiler.
  #endif
        }

        template <typename E>
        inline constexpr auto type_name_v = n<E>();

        template <typename E, E V>
        constexpr auto n() noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::n requires enum type.");
          constexpr auto custom_name = customize::enum_name<E>(V);

          if constexpr(custom_name.empty())
          {
            static_cast<void>(custom_name);
  #if defined(MAGIC_ENUM_SUPPORTED) && MAGIC_ENUM_SUPPORTED
    #if defined(__clang__) || defined(__GNUC__)
            constexpr auto name = pretty_name({__PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__) - 2});
    #elif defined(_MSC_VER)
            constexpr auto name = pretty_name({__FUNCSIG__, sizeof(__FUNCSIG__) - 17});
    #endif
            return static_string<name.size()> {name};
  #else
            return rsl::string_view {}; // Unsupported compiler.
  #endif
          }
          else
          {
            return static_string<custom_name.size()> {custom_name};
          }
        }

        template <typename E, E V>
        inline constexpr auto enum_name_v = n<E, V>();

        template <typename E, auto V>
        constexpr bool is_valid() noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::is_valid requires enum type.");

          return n<E, static_cast<E>(V)>().size() != 0;
        }

        template <typename E, int O, bool IsFlags = false, typename U = rsl::underlying_type_t<E>>
        constexpr E value(card32 i) noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::value requires enum type.");

          if constexpr(IsFlags)
          {
            return static_cast<E>(U {1} << static_cast<U>(static_cast<int>(i) + O));
          }
          else
          {
            return static_cast<E>(static_cast<int>(i) + O);
          }
        }

        template <typename E, bool IsFlags, typename U = rsl::underlying_type_t<E>>
        constexpr int reflected_min() noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::reflected_min requires enum type.");

          if constexpr(IsFlags)
          {
            return 0;
          }
          else
          {
            constexpr auto lhs = customize::enum_range<E>::min;
            static_assert(lhs > (rsl::numeric_limits<rsl::int16>::min)(), "enum_refl::enum_range requires min must be greater than INT16_MIN.");
            constexpr auto rhs = (rsl::numeric_limits<U>::min)();

            if constexpr(cmp_less(rhs, lhs))
            {
              static_assert(!is_valid<E, value<E, lhs - 1, IsFlags>(0)>(), "enum_refl::enum_range detects enum value smaller than min range size.");
              return lhs;
            }
            else
            {
              return rhs;
            }
          }
        }

        template <typename E, bool IsFlags, typename U = rsl::underlying_type_t<E>>
        constexpr int reflected_max() noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::reflected_max requires enum type.");

          if constexpr(IsFlags)
          {
            return rsl::numeric_limits<U>::digits - 1;
          }
          else
          {
            constexpr auto lhs = customize::enum_range<E>::max;
            static_assert(lhs < (rsl::numeric_limits<rsl::int16>::max)(), "enum_refl::enum_range requires max must be less than INT16_MAX.");
            constexpr auto rhs = (rsl::numeric_limits<U>::max)();

            if constexpr(cmp_less(lhs, rhs))
            {
              static_assert(!is_valid<E, value<E, lhs + 1, IsFlags>(0)>(), "enum_refl::enum_range detects enum value larger than max range size.");
              return lhs;
            }
            else
            {
              return rhs;
            }
          }
        }

        template <typename E, bool IsFlags = false>
        inline constexpr auto reflected_min_v = reflected_min<E, IsFlags>();

        template <typename E, bool IsFlags = false>
        inline constexpr auto reflected_max_v = reflected_max<E, IsFlags>();

        template <card32 N>
        constexpr card32 values_count(const bool (&valid)[N]) noexcept
        {
          auto count = card32 {0};
          for(card32 i = 0; i < N; ++i)
          {
            if(valid[i])
            {
              ++count;
            }
          }

          return count;
        }

        template <typename E, bool IsFlags, int Min, card32... I>
        constexpr auto values(rsl::index_sequence<I...>) noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::values requires enum type.");
          constexpr bool valid[sizeof...(I)] = {is_valid<E, value<E, Min, IsFlags>(I)>()...};
          constexpr card32 count             = values_count(valid);

          if constexpr(count > 0)
          {
            E values[count] = {};
            for(card32 i = 0, v = 0; v < count; ++i)
            {
              if(valid[i])
              {
                values[v++] = value<E, Min, IsFlags>(i);
              }
            }

            return to_array(values, rsl::make_index_sequence<count> {});
          }
          else
          {
            return rsl::array<E, 0> {};
          }
        }

        template <typename E, bool IsFlags, typename U = rsl::underlying_type_t<E>>
        constexpr auto values() noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::values requires enum type.");
          constexpr auto min        = reflected_min_v<E, IsFlags>;
          constexpr auto max        = reflected_max_v<E, IsFlags>;
          constexpr auto range_size = max - min + 1;
          static_assert(range_size > 0, "enum_refl::enum_range requires valid size.");
          static_assert(range_size < (rsl::numeric_limits<rsl::uint16>::max)(), "enum_refl::enum_range requires valid size.");

          return values<E, IsFlags, reflected_min_v<E, IsFlags>>(rsl::make_index_sequence<range_size> {});
        }

        template <typename E, bool IsFlags = false>
        inline constexpr auto values_v = values<E, IsFlags>();

        template <typename E, bool IsFlags = false, typename D = rsl::decay_t<E>>
        using values_t = decltype((values_v<D, IsFlags>));

        template <typename E, bool IsFlags = false>
        inline constexpr auto count_v = values_v<E, IsFlags>.size();

        template <typename E, bool IsFlags = false, typename U = rsl::underlying_type_t<E>>
        inline constexpr auto min_v = (count_v<E, IsFlags> > 0) ? static_cast<U>(values_v<E, IsFlags>.front()) : U {0};

        template <typename E, bool IsFlags = false, typename U = rsl::underlying_type_t<E>>
        inline constexpr auto max_v = (count_v<E, IsFlags> > 0) ? static_cast<U>(values_v<E, IsFlags>.back()) : U {0};

        template <typename E, bool IsFlags, typename U = rsl::underlying_type_t<E>>
        constexpr card32 range_size() noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::range_size requires enum type.");
          constexpr auto max        = IsFlags ? log2(max_v<E, IsFlags>) : max_v<E, IsFlags>;
          constexpr auto min        = IsFlags ? log2(min_v<E, IsFlags>) : min_v<E, IsFlags>;
          constexpr auto range_size = max - min + U {1};
          static_assert(range_size > 0, "enum_refl::enum_range requires valid size.");
          static_assert(range_size < (rsl::numeric_limits<rsl::uint16>::max)(), "enum_refl::enum_range requires valid size.");

          return static_cast<card32>(range_size);
        }

        template <typename E, bool IsFlags = false>
        inline constexpr auto range_size_v = range_size<E, IsFlags>();

        template <typename E, bool IsFlags = false>
        using index_t = rsl::conditional_t < range_size_v<E, IsFlags><(rsl::numeric_limits<rsl::uint8>::max)(), rsl::uint8, rsl::uint16>;

        template <typename E, bool IsFlags = false>
        inline constexpr auto invalid_index_v = (rsl::numeric_limits<index_t<E, IsFlags>>::max)();

        template <typename E, bool IsFlags, card32... I>
        constexpr auto indexes(rsl::index_sequence<I...>) noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::indexes requires enum type.");
          constexpr auto min      = IsFlags ? log2(min_v<E, IsFlags>) : min_v<E, IsFlags>;
          [[maybe_unused]] auto i = index_t<E, IsFlags> {0};

          return rsl::array<decltype(i), sizeof...(I)> {{(is_valid<E, value<E, min, IsFlags>(I)>() ? i++ : invalid_index_v<E, IsFlags>)...}};
        }

        template <typename E, bool IsFlags = false>
        inline constexpr auto indexes_v = indexes<E, IsFlags>(rsl::make_index_sequence<range_size_v<E, IsFlags>> {});

        template <typename E, bool IsFlags, card32... I>
        constexpr auto names(rsl::index_sequence<I...>) noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::names requires enum type.");

          return rsl::array<rsl::string_view, sizeof...(I)> {{enum_name_v<E, values_v<E, IsFlags>[I]>...}};
        }

        template <typename E, bool IsFlags = false>
        inline constexpr auto names_v = names<E, IsFlags>(rsl::make_index_sequence<count_v<E, IsFlags>> {});

        template <typename E, bool IsFlags = false, typename D = rsl::decay_t<E>>
        using names_t = decltype((names_v<D, IsFlags>));

        template <typename E>
        class enum_entry
        {
        public:
          constexpr enum_entry(E value, rsl::string_view name)
              : m_value(value)
              , m_name(name)
          {
          }

          constexpr E val() const
          {
            return m_value;
          }
          constexpr rsl::string_view name() const
          {
            return m_name;
          }

        private:
          E m_value;
          rsl::string_view m_name;
        };

        template <typename E, bool IsFlags, card32... I>
        constexpr auto entries(rsl::index_sequence<I...>) noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::entries requires enum type.");

          return rsl::array<enum_entry<E>, sizeof...(I)> {{{values_v<E, IsFlags>[I], enum_name_v<E, values_v<E, IsFlags>[I]>}...}};
        }

        template <typename E, bool IsFlags = false>
        inline constexpr auto entries_v = entries<E, IsFlags>(rsl::make_index_sequence<count_v<E, IsFlags>> {});

        template <typename E, bool IsFlags = false, typename D = rsl::decay_t<E>>
        using entries_t = decltype((entries_v<D, IsFlags>));

        template <typename E, bool IsFlags, typename U = rsl::underlying_type_t<E>>
        constexpr bool is_sparse() noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::is_sparse requires enum type.");

          return range_size_v<E, IsFlags> != count_v<E, IsFlags>;
        }

        template <typename E, bool IsFlags = false>
        inline constexpr bool is_sparse_v = is_sparse<E, IsFlags>();

        template <typename E, typename U = rsl::underlying_type_t<E>>
        constexpr card32 undex(U value) noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::undex requires enum type.");

          if(const auto i = static_cast<card32>(value - min_v<E>); value >= min_v<E> && value <= max_v<E>)
          {
            if constexpr(is_sparse_v<E>)
            {
              if(const auto idx = indexes_v<E>[i]; idx != invalid_index_v<E>)
              {
                return idx;
              }
            }
            else
            {
              return i;
            }
          }

          return invalid_index_v<E>; // Value out of range.
        }

        template <typename E, typename U = rsl::underlying_type_t<E>>
        constexpr card32 endex(E value) noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::endex requires enum type.");

          return undex<E>(static_cast<U>(value));
        }

        template <typename E, typename U = rsl::underlying_type_t<E>>
        constexpr U value_ors() noexcept
        {
          static_assert(is_enum_v<E>, "enum_refl::detail::endex requires enum type.");

          auto value = U {0};
          for(card32 i = 0; i < count_v<E, true>; ++i)
          {
            value |= static_cast<U>(values_v<E, true>[i]);
          }

          return value;
        }

        template <bool, typename T, typename R>
        struct enable_if_enum
        {
        };

        template <typename T, typename R>
        struct enable_if_enum<true, T, R>
        {
          using type = R;
          using D    = rsl::decay_t<T>;
          static_assert(supported<D>::value, "enum_refl unsupported compiler (https://github.com/Neargye/enum_refl#compiler-compatibility).");
        };

        template <typename T, typename R = void>
        using enable_if_enum_t = rsl::enable_if_t<rsl::is_enum_v<rsl::decay_t<T>>, R>;

        template <typename T, typename Enable = rsl::enable_if_t<rsl::is_enum_v<rsl::decay_t<T>>>>
        using enum_concept = T;

        template <typename T, bool = rsl::is_enum_v<T>>
        struct is_scoped_enum : rsl::false_type
        {
        };

        template <typename T>
        struct is_scoped_enum<T, true> : rsl::bool_constant<!rsl::is_convertible_v<T, rsl::underlying_type_t<T>>>
        {
        };

        template <typename T, bool = rsl::is_enum_v<T>>
        struct is_unscoped_enum : rsl::false_type
        {
        };

        template <typename T>
        struct is_unscoped_enum<T, true> : rsl::bool_constant<rsl::is_convertible_v<T, rsl::underlying_type_t<T>>>
        {
        };

        template <typename T, bool = rsl::is_enum_v<rsl::decay_t<T>>>
        struct underlying_type
        {
        };

        template <typename T>
        struct underlying_type<T, true> : rsl::underlying_type<rsl::decay_t<T>>
        {
        };

      } // namespace detail

      // Checks is enum_refl supported compiler.
      inline constexpr bool is_magic_enum_supported = detail::supported<void>::value;

      template <typename T>
      using Enum = detail::enum_concept<T>;

      // Checks whether T is an Unscoped enumeration type.
      // Provides the member constant value which is equal to true, if T is an [Unscoped enumeration](https://en.cppreference.com/w/cpp/language/enum#Unscoped_enumeration) type. Otherwise, value is equal to false.
      template <typename T>
      struct is_unscoped_enum : detail::is_unscoped_enum<T>
      {
      };

      template <typename T>
      inline constexpr bool is_unscoped_enum_v = is_unscoped_enum<T>::value;

      // Checks whether T is an Scoped enumeration type.
      // Provides the member constant value which is equal to true, if T is an [Scoped enumeration](https://en.cppreference.com/w/cpp/language/enum#Scoped_enumerations) type. Otherwise, value is equal to false.
      template <typename T>
      struct is_scoped_enum : detail::is_scoped_enum<T>
      {
      };

      template <typename T>
      inline constexpr bool is_scoped_enum_v = is_scoped_enum<T>::value;

      // If T is a complete enumeration type, provides a member typedef type that names the underlying type of T.
      // Otherwise, if T is not an enumeration type, there is no member type. Otherwise (T is an incomplete enumeration type), the program is ill-formed.
      template <typename T>
      struct underlying_type : detail::underlying_type<T>
      {
      };

      template <typename T>
      using underlying_type_t = typename underlying_type<T>::type;

      // Returns type name of enum.
      template <typename E>
      [[nodiscard]] constexpr auto enum_type_name() noexcept -> detail::enable_if_enum_t<E, rsl::string_view>
      {
        using D                         = rsl::decay_t<E>;
        constexpr rsl::string_view name = detail::type_name_v<D>;
        static_assert(name.size() > 0, "Enum type does not have a name.");

        return name;
      }

      // Returns number of enum values.
      template <typename E>
      [[nodiscard]] constexpr auto enum_count() noexcept -> detail::enable_if_enum_t<E, card32>
      {
        using D = rsl::decay_t<E>;

        return detail::count_v<D>;
      }

      // Returns enum value at specified index.
      // No bounds checking is performed: the behavior is undefined if index >= number of enum values.
      template <typename E>
      [[nodiscard]] constexpr auto enum_value(card32 index) noexcept -> detail::enable_if_enum_t<E, rsl::decay_t<E>>
      {
        using D = rsl::decay_t<E>;
        static_assert(detail::count_v<D> > 0, "enum_refl requires enum implementation and valid max and min.");

        if constexpr(detail::is_sparse_v<D>)
        {
          return assert((index < detail::count_v<D>)), detail::values_v<D>[index];
        }
        else
        {
          return assert((index < detail::count_v<D>)), detail::value<D, detail::min_v<D>>(index);
        }
      }

      // Returns rsl::array with enum values, sorted by enum value.
      template <typename E>
      [[nodiscard]] constexpr auto enum_values() noexcept -> detail::enable_if_enum_t<E, detail::values_t<E>>
      {
        using D = rsl::decay_t<E>;
        static_assert(detail::count_v<D> > 0, "enum_refl requires enum implementation and valid max and min.");

        return detail::values_v<D>;
      }

      // Returns name from static storage enum variable.
      // This version is much lighter on the compile times and is not restricted to the enum_range limitation.
      template <auto V>
      [[nodiscard]] constexpr auto enum_name() noexcept -> detail::enable_if_enum_t<decltype(V), rsl::string_view>
      {
        using D                         = rsl::decay_t<decltype(V)>;
        constexpr rsl::string_view name = detail::enum_name_v<D, V>;
        static_assert(name.size() > 0, "Enum value does not have a name.");

        return name;
      }

      // Returns name from enum value.
      // If enum value does not have name or value out of range, returns empty string.
      template <typename E>
      [[nodiscard]] constexpr auto enum_name(E value) noexcept -> detail::enable_if_enum_t<E, rsl::string_view>
      {
        using D = rsl::decay_t<E>;

        if(const auto i = detail::endex<D>(value); i != detail::invalid_index_v<D>)
        {
          return detail::names_v<D>[i];
        }

        return {}; // Invalid value or out of range.
      }

      // Returns rsl::array with names, sorted by enum value.
      template <typename E>
      [[nodiscard]] constexpr auto enum_names() noexcept -> detail::enable_if_enum_t<E, detail::names_t<E>>
      {
        using D = rsl::decay_t<E>;
        static_assert(detail::count_v<D> > 0, "enum_refl requires enum implementation and valid max and min.");

        return detail::names_v<D>;
      }

      // Returns rsl::array with pairs (value, name), sorted by enum value.
      template <typename E>
      [[nodiscard]] constexpr auto enum_entries() noexcept -> detail::enable_if_enum_t<E, detail::entries_t<E>>
      {
        using D = rsl::decay_t<E>;
        static_assert(detail::count_v<D> > 0, "enum_refl requires enum implementation and valid max and min.");

        return detail::entries_v<D>;
      }

      // Obtains enum value from integer value.
      // Returns optional with enum value.
      template <typename E>
      [[nodiscard]] constexpr auto enum_cast(underlying_type_t<E> value) noexcept -> detail::enable_if_enum_t<E, optional<rsl::decay_t<E>>>
      {
        using D = rsl::decay_t<E>;

        if(detail::undex<D>(value) != detail::invalid_index_v<D>)
        {
          return static_cast<D>(value);
        }

        return {}; // Invalid value or out of range.
      }

      // Obtains enum value from name.
      // Returns optional with enum value.
      template <typename E, typename BinaryPredicate>
      [[nodiscard]] constexpr auto enum_cast(rsl::string_view value, BinaryPredicate p) noexcept(rsl::is_nothrow_invocable_r_v<bool, BinaryPredicate, char, char>) -> detail::enable_if_enum_t<E, optional<rsl::decay_t<E>>>
      {
        static_assert(rsl::is_invocable_r_v<bool, BinaryPredicate, char, char>, "enum_refl::enum_cast requires bool(char, char) invocable predicate.");
        using D = rsl::decay_t<E>;

        for(card32 i = 0; i < detail::count_v<D>; ++i)
        {
          if(detail::cmp_equal(value, detail::names_v<D>[i], p))
          {
            return enum_value<D>(i);
          }
        }

        return {}; // Invalid value or out of range.
      }

      // Obtains enum value from name.
      // Returns optional with enum value.
      template <typename E>
      [[nodiscard]] constexpr auto enum_cast(rsl::string_view value) noexcept -> detail::enable_if_enum_t<E, optional<rsl::decay_t<E>>>
      {
        using D = rsl::decay_t<E>;

        return enum_cast<D>(value, detail::char_equal_to {});
      }

      // Returns integer value from enum value.
      template <typename E>
      [[nodiscard]] constexpr auto enum_integer(E value) noexcept -> detail::enable_if_enum_t<E, underlying_type_t<E>>
      {
        return static_cast<underlying_type_t<E>>(value);
      }

      // Obtains index in enum values from enum value.
      // Returns optional with index.
      template <typename E>
      [[nodiscard]] constexpr auto enum_index(E value) noexcept -> detail::enable_if_enum_t<E, optional<card32>>
      {
        using D = rsl::decay_t<E>;

        if(const auto i = detail::endex<D>(value); i != detail::invalid_index_v<D>)
        {
          return i;
        }

        return {}; // Invalid value or out of range.
      }

      // Checks whether enum contains enumerator with such enum value.
      template <typename E>
      [[nodiscard]] constexpr auto enum_contains(E value) noexcept -> detail::enable_if_enum_t<E, bool>
      {
        using D = rsl::decay_t<E>;

        return detail::endex<D>(value) != detail::invalid_index_v<D>;
      }

      // Checks whether enum contains enumerator with such integer value.
      template <typename E>
      [[nodiscard]] constexpr auto enum_contains(underlying_type_t<E> value) noexcept -> detail::enable_if_enum_t<E, bool>
      {
        using D = rsl::decay_t<E>;

        return detail::undex<D>(value) != detail::invalid_index_v<D>;
      }

      // Checks whether enum contains enumerator with such name.
      template <typename E, typename BinaryPredicate>
      [[nodiscard]] constexpr auto enum_contains(rsl::string_view value, BinaryPredicate p) noexcept(rsl::is_nothrow_invocable_r_v<bool, BinaryPredicate, char, char>) -> detail::enable_if_enum_t<E, bool>
      {
        static_assert(rsl::is_invocable_r_v<bool, BinaryPredicate, char, char>, "enum_refl::enum_contains requires bool(char, char) invocable predicate.");
        using D = rsl::decay_t<E>;

        return enum_cast<D>(value, rsl::move_if_noexcept(p)).has_value();
      }

      // Checks whether enum contains enumerator with such name.
      template <typename E>
      [[nodiscard]] constexpr auto enum_contains(rsl::string_view value) noexcept -> detail::enable_if_enum_t<E, bool>
      {
        using D = rsl::decay_t<E>;

        return enum_cast<D>(value).has_value();
      }

      namespace ostream_operators
      {

        template <typename Char, typename Traits, typename E, rsl::enable_if_t<rsl::is_enum_v<E>, int> = 0>
        rsl::basic_ostream<Char, Traits>& operator<<(rsl::basic_ostream<Char, Traits>& os, E value)
        {
          using D = rsl::decay_t<E>;
          using U = underlying_type_t<D>;
  #if defined(MAGIC_ENUM_SUPPORTED) && MAGIC_ENUM_SUPPORTED
          if(const auto name = enum_refl::enum_name<D>(value); !name.empty())
          {
            for(const auto c: name)
            {
              os.put(c);
            }
            return os;
          }
  #endif
          return (os << static_cast<U>(value));
        }

        template <typename Char, typename Traits, typename E, rsl::enable_if_t<rsl::is_enum_v<E>, int> = 0>
        rsl::basic_ostream<Char, Traits>& operator<<(rsl::basic_ostream<Char, Traits>& os, optional<E> value)
        {
          return value.has_value() ? (os << value.value()) : os;
        }

      } // namespace ostream_operators

      namespace bitwise_operators
      {

        template <typename E, rsl::enable_if_t<rsl::is_enum_v<E>, int> = 0>
        constexpr E operator~(E rhs) noexcept
        {
          return static_cast<E>(~static_cast<underlying_type_t<E>>(rhs));
        }

        template <typename E, rsl::enable_if_t<rsl::is_enum_v<E>, int> = 0>
        constexpr E operator|(E lhs, E rhs) noexcept
        {
          return static_cast<E>(static_cast<underlying_type_t<E>>(lhs) | static_cast<underlying_type_t<E>>(rhs));
        }

        template <typename E, rsl::enable_if_t<rsl::is_enum_v<E>, int> = 0>
        constexpr E operator&(E lhs, E rhs) noexcept
        {
          return static_cast<E>(static_cast<underlying_type_t<E>>(lhs) & static_cast<underlying_type_t<E>>(rhs));
        }

        template <typename E, rsl::enable_if_t<rsl::is_enum_v<E>, int> = 0>
        constexpr E operator^(E lhs, E rhs) noexcept
        {
          return static_cast<E>(static_cast<underlying_type_t<E>>(lhs) ^ static_cast<underlying_type_t<E>>(rhs));
        }

        template <typename E, rsl::enable_if_t<rsl::is_enum_v<E>, int> = 0>
        constexpr E& operator|=(E& lhs, E rhs) noexcept
        {
          return lhs = (lhs | rhs);
        }

        template <typename E, rsl::enable_if_t<rsl::is_enum_v<E>, int> = 0>
        constexpr E& operator&=(E& lhs, E rhs) noexcept
        {
          return lhs = (lhs & rhs);
        }

        template <typename E, rsl::enable_if_t<rsl::is_enum_v<E>, int> = 0>
        constexpr E& operator^=(E& lhs, E rhs) noexcept
        {
          return lhs = (lhs ^ rhs);
        }

      } // namespace bitwise_operators

      namespace flags
      {

        // Returns type name of enum.
        using enum_refl::enum_type_name;

        // Returns number of enum-flags values.
        template <typename E>
        [[nodiscard]] constexpr auto enum_count() noexcept -> detail::enable_if_enum_t<E, card32>
        {
          using D = rsl::decay_t<E>;

          return detail::count_v<D, true>;
        }

        // Returns enum-flags value at specified index.
        // No bounds checking is performed: the behavior is undefined if index >= number of enum-flags values.
        template <typename E>
        [[nodiscard]] constexpr auto enum_value(card32 index) noexcept -> detail::enable_if_enum_t<E, rsl::decay_t<E>>
        {
          using D = rsl::decay_t<E>;
          static_assert(detail::count_v<D, true> > 0, "enum_refl::flags requires enum-flags implementation.");

          if constexpr(detail::is_sparse_v<D, true>)
          {
            return assert((index < detail::count_v<D, true>)), detail::values_v<D, true>[index];
          }
          else
          {
            constexpr auto min = detail::log2(detail::min_v<D, true>);

            return assert((index < detail::count_v<D, true>)), detail::value<D, min, true>(index);
          }
        }

        // Returns rsl::array with enum-flags values, sorted by enum-flags value.
        template <typename E>
        [[nodiscard]] constexpr auto enum_values() noexcept -> detail::enable_if_enum_t<E, detail::values_t<E, true>>
        {
          using D = rsl::decay_t<E>;
          static_assert(detail::count_v<D, true> > 0, "enum_refl::flags requires enum-flags implementation.");

          return detail::values_v<D, true>;
        }

        // Returns name from enum-flags value.
        // If enum-flags value does not have name or value out of range, returns empty string.
        template <typename E>
        [[nodiscard]] auto enum_name(E value) -> detail::enable_if_enum_t<E, string>
        {
          using D = rsl::decay_t<E>;
          using U = underlying_type_t<D>;

          string name;
          auto check_value = U {0};
          for(card32 i = 0; i < detail::count_v<D, true>; ++i)
          {
            if(const auto v = static_cast<U>(enum_value<D>(i)); (static_cast<U>(value) & v) != 0)
            {
              check_value |= v;
              const auto n = detail::names_v<D, true>[i];
              if(!name.empty())
              {
                name.append(1, '|');
              }
              name.append(n.data(), n.size());
            }
          }

          if(check_value != 0 && check_value == static_cast<U>(value))
          {
            return name;
          }

          return {}; // Invalid value or out of range.
        }

        // Returns rsl::array with string names, sorted by enum-flags value.
        template <typename E>
        [[nodiscard]] constexpr auto enum_names() noexcept -> detail::enable_if_enum_t<E, detail::names_t<E, true>>
        {
          using D = rsl::decay_t<E>;
          static_assert(detail::count_v<D, true> > 0, "enum_refl::flags requires enum-flags implementation.");

          return detail::names_v<D, true>;
        }

        // Returns rsl::array with pairs (value, name), sorted by enum-flags value.
        template <typename E>
        [[nodiscard]] constexpr auto enum_entries() noexcept -> detail::enable_if_enum_t<E, detail::entries_t<E, true>>
        {
          using D = rsl::decay_t<E>;
          static_assert(detail::count_v<D, true> > 0, "enum_refl::flags requires enum-flags implementation.");

          return detail::entries_v<D, true>;
        }

        // Obtains enum-flags value from integer value.
        // Returns optional with enum-flags value.
        template <typename E>
        [[nodiscard]] constexpr auto enum_cast(underlying_type_t<E> value) noexcept -> detail::enable_if_enum_t<E, optional<rsl::decay_t<E>>>
        {
          using D = rsl::decay_t<E>;
          using U = underlying_type_t<D>;

          if constexpr(detail::is_sparse_v<D, true>)
          {
            auto check_value = U {0};
            for(card32 i = 0; i < detail::count_v<D, true>; ++i)
            {
              if(const auto v = static_cast<U>(enum_value<D>(i)); (value & v) != 0)
              {
                check_value |= v;
              }
            }

            if(check_value != 0 && check_value == value)
            {
              return static_cast<D>(value);
            }
          }
          else
          {
            constexpr auto min = detail::min_v<D, true>;
            constexpr auto max = detail::value_ors<D>();

            if(value >= min && value <= max)
            {
              return static_cast<D>(value);
            }
          }

          return {}; // Invalid value or out of range.
        }

        // Obtains enum-flags value from name.
        // Returns optional with enum-flags value.
        template <typename E, typename BinaryPredicate>
        [[nodiscard]] constexpr auto enum_cast(rsl::string_view value, BinaryPredicate p) noexcept(rsl::is_nothrow_invocable_r_v<bool, BinaryPredicate, char, char>) -> detail::enable_if_enum_t<E, optional<rsl::decay_t<E>>>
        {
          static_assert(rsl::is_invocable_r_v<bool, BinaryPredicate, char, char>, "enum_refl::flags::enum_cast requires bool(char, char) invocable predicate.");
          using D = rsl::decay_t<E>;
          using U = underlying_type_t<D>;

          auto result = U {0};
          while(!value.empty())
          {
            const auto d = detail::find(value, '|');
            const auto s = (d == rsl::string_view::npos()) ? value : value.substr(0, d);
            auto f       = U {0};
            for(card32 i = 0; i < detail::count_v<D, true>; ++i)
            {
              if(detail::cmp_equal(s, detail::names_v<D, true>[i], p))
              {
                f = static_cast<U>(enum_value<D>(i));
                result |= f;
                break;
              }
            }
            if(f == U {0})
            {
              return {}; // Invalid value or out of range.
            }
            value.remove_prefix((d == rsl::string_view::npos()) ? value.size() : d + 1);
          }

          if(result == U {0})
          {
            return {}; // Invalid value or out of range.
          }
          else
          {
            return static_cast<D>(result);
          }
        }

        // Obtains enum-flags value from name.
        // Returns optional with enum-flags value.
        template <typename E>
        [[nodiscard]] constexpr auto enum_cast(rsl::string_view value) noexcept -> detail::enable_if_enum_t<E, optional<rsl::decay_t<E>>>
        {
          using D = rsl::decay_t<E>;

          return enum_cast<D>(value, detail::char_equal_to {});
        }

        // Returns integer value from enum value.
        using enum_refl::enum_integer;

        // Obtains index in enum-flags values from enum-flags value.
        // Returns optional with index.
        template <typename E>
        [[nodiscard]] constexpr auto enum_index(E value) noexcept -> detail::enable_if_enum_t<E, optional<card32>>
        {
          using D = rsl::decay_t<E>;
          using U = underlying_type_t<D>;

          if(detail::is_pow2(static_cast<U>(value)))
          {
            for(card32 i = 0; i < detail::count_v<D, true>; ++i)
            {
              if(enum_value<D>(i) == value)
              {
                return i;
              }
            }
          }

          return {}; // Invalid value or out of range.
        }

        // Checks whether enum-flags contains enumerator with such enum-flags value.
        template <typename E>
        [[nodiscard]] constexpr auto enum_contains(E value) noexcept -> detail::enable_if_enum_t<E, bool>
        {
          using D = rsl::decay_t<E>;
          using U = underlying_type_t<D>;

          return enum_cast<D>(static_cast<U>(value)).has_value();
        }

        // Checks whether enum-flags contains enumerator with such integer value.
        template <typename E>
        [[nodiscard]] constexpr auto enum_contains(underlying_type_t<E> value) noexcept -> detail::enable_if_enum_t<E, bool>
        {
          using D = rsl::decay_t<E>;

          return enum_cast<D>(value).has_value();
        }

        // Checks whether enum-flags contains enumerator with such name.
        template <typename E, typename BinaryPredicate>
        [[nodiscard]] constexpr auto enum_contains(rsl::string_view value, BinaryPredicate p) noexcept(rsl::is_nothrow_invocable_r_v<bool, BinaryPredicate, char, char>) -> detail::enable_if_enum_t<E, bool>
        {
          static_assert(rsl::is_invocable_r_v<bool, BinaryPredicate, char, char>, "enum_refl::flags::enum_contains requires bool(char, char) invocable predicate.");
          using D = rsl::decay_t<E>;

          return enum_cast<D>(value, rsl::move_if_noexcept(p)).has_value();
        }

        // Checks whether enum-flags contains enumerator with such name.
        template <typename E>
        [[nodiscard]] constexpr auto enum_contains(rsl::string_view value) noexcept -> detail::enable_if_enum_t<E, bool>
        {
          using D = rsl::decay_t<E>;

          return enum_cast<D>(value).has_value();
        }

      } // namespace flags

      namespace flags::ostream_operators
      {

        template <typename Char, typename Traits, typename E, rsl::enable_if_t<rsl::is_enum_v<E>, int> = 0>
        rsl::basic_ostream<Char, Traits>& operator<<(rsl::basic_ostream<Char, Traits>& os, E value)
        {
          using D = rsl::decay_t<E>;
          using U = underlying_type_t<D>;
  #if defined(MAGIC_ENUM_SUPPORTED) && MAGIC_ENUM_SUPPORTED
          if(const auto name = enum_refl::flags::enum_name<D>(value); !name.empty())
          {
            for(const auto c: name)
            {
              os.put(c);
            }
            return os;
          }
  #endif
          return (os << static_cast<U>(value));
        }

        template <typename Char, typename Traits, typename E, rsl::enable_if_t<rsl::is_enum_v<E>, int> = 0>
        rsl::basic_ostream<Char, Traits>& operator<<(rsl::basic_ostream<Char, Traits>& os, optional<E> value)
        {
          return value.has_value() ? (os << value.value()) : os;
        }

      } // namespace flags::ostream_operators

      namespace flags::bitwise_operators
      {

        using namespace enum_refl::bitwise_operators;

      } // namespace flags::bitwise_operators

    } // namespace enum_refl
  }   // namespace v1
} // namespace rsl
  #if defined(__clang__)
    #pragma clang diagnostic pop
  #elif defined(__GNUC__)
    #pragma GCC diagnostic pop
  #elif defined(_MSC_VER)
    #pragma warning(pop)
  #endif

#endif // NEARGYE_MAGIC_ENUM_HPP
