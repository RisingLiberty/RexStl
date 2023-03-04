#pragma once

#include "rex_std/internal/string/basic_string.h"
#include "rex_std/internal/format/fmt_defines.h"
#include "rex_std/string_view.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename Char>
    struct basic_runtime
    {
      basic_string_view<Char> str;
    };

    /** A compile-time format string. */
    template <typename Char, typename... Args>
    class basic_format_string
    {
    private:
      basic_string_view<Char> m_str;

    public:
      template <typename S, FMT_ENABLE_IF(rsl::is_convertible<const S&, basic_string_view<Char>>::value)>
      FMT_CONSTEVAL FMT_INLINE basic_format_string(const S& s) // NOLINT(google-explicit-constructor)
        : m_str(s)
      {
        static_assert(detail::count<(rsl::is_base_of<detail::view, remove_reference_t<Args>>::value&& rsl::is_reference<Args>::value)...>() == 0, "passing views as lvalues is disallowed");
#ifdef FMT_HAS_CONSTEVAL
        if constexpr (detail::count_named_args<Args...>() == detail::count_statically_named_args<Args...>())
        {
          using checker = detail::format_string_checker<Char, detail::error_handler, remove_cvref_t<Args>...>;
          detail::parse_format_string<true>(m_str, checker(s, {}));
        }
#else
        detail::check_format_string<Args...>(s);
#endif
      }
      basic_format_string(basic_runtime<Char> r) // NOLINT(google-explicit-constructor)
        : m_str(r.str)
      {
      }

      FMT_INLINE operator basic_string_view<Char>() const // NOLINT(google-explicit-constructor)
      {
        return m_str;
      }
    };

#if FMT_GCC_VERSION && FMT_GCC_VERSION < 409
    // Workaround broken conversion on older gcc.
    template <typename...>
    using format_string = string_view;
    inline auto runtime(string_view s) -> string_view
    {
      return s;
    }
#else
    template <typename... Args>
    using format_string = basic_format_string<char, type_identity_t<Args>...>;
    /**
      \rst
      Creates a runtime format string.

      **Example**::

        // Check format string at runtime instead of compile-time.
        rsl::print(rsl::runtime("{:d}"), "I am not a number");
      \endrst
     */
    inline auto runtime(string_view s) -> basic_runtime<char>
    {
      return { {s} };
    }
#endif

  }
}