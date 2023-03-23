// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: fmt_compile_test.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#ifdef REX_ENABLE_FMT_TESTING

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/format.h"
#include "rex_std/internal/format/compile.h"

TEST_CASE("iterator_test, counting_iterator") {
  auto it = rsl::detail::counting_iterator();
  auto prev = it++;
  REQUIRE(prev.count() == 0);
  REQUIRE(it.count() == 1);
  REQUIRE((it + 41).count() == 42);
}

TEST_CASE("iterator_test, truncating_iterator") {
  char* p = nullptr;
  auto it = rsl::detail::truncating_iterator<char*>(p, 3);
  auto prev = it++;
  REQUIRE(prev.base() == p);
  REQUIRE(it.base() == p + 1);
}

TEST_CASE("iterator_test, truncating_iterator_default_construct") {
  auto it = rsl::detail::truncating_iterator<char*>();
  REQUIRE(nullptr == it.base());
  REQUIRE(std::size_t{ 0 } == it.count());
}

#ifdef __cpp_lib_ranges
TEST_CASE(iterator_test, truncating_iterator_is_output_iterator) {
  static_assert(
    std::output_iterator<rsl::detail::truncating_iterator<char*>, char>);
}
#endif

TEST_CASE("iterator_test, truncating_back_inserter") {
  auto buffer = std::string();
  auto bi = std::back_inserter(buffer);
  auto it = rsl::detail::truncating_iterator<decltype(bi)>(bi, 2);
  *it++ = '4';
  *it++ = '2';
  *it++ = '1';
  REQUIRE(buffer.size() == 2);
  REQUIRE(buffer == "42");
}

TEST_CASE("compile_test, compile_fallback") {
  // FMT_COMPILE should fallback on runtime formatting when `if constexpr` is
  // not available.
  REQUIRE("42" == rsl::format(FMT_COMPILE("{}"), 42));
}

struct type_with_get {
  template <int> friend void get(type_with_get);
};

FMT_BEGIN_NAMESPACE
template <> struct formatter<type_with_get> : formatter<int> {
  template <typename FormatContext>
  auto format(type_with_get, FormatContext& ctx) -> decltype(ctx.out()) {
    return formatter<int>::format(42, ctx);
  }
};
FMT_END_NAMESPACE

TEST_CASE("compile_test, compile_type_with_get") {
  REQUIRE("42" == rsl::format(FMT_COMPILE("{}"), type_with_get()));
}

#if defined(__cpp_if_constexpr) && defined(__cpp_return_type_deduction)
struct test_formattable {};

FMT_BEGIN_NAMESPACE
template <> struct formatter<test_formattable> : formatter<const char*> {
  char word_spec = 'f';
  constexpr auto parse(format_parse_context& ctx) {
    auto it = ctx.begin(), end = ctx.end();
    if (it == end || *it == '}') return it;
    if (it != end && (*it == 'f' || *it == 'b')) word_spec = *it++;
    if (it != end && *it != '}') throw format_error("invalid format");
    return it;
  }
  template <typename FormatContext>
  constexpr auto format(test_formattable, FormatContext& ctx) const
    -> decltype(ctx.out()) {
    return formatter<const char*>::format(word_spec == 'f' ? "foo" : "bar",
      ctx);
  }
};
FMT_END_NAMESPACE

TEST_CASE("compile_test, format_default") {
  REQUIRE("42" == rsl::format(FMT_COMPILE("{}"), 42));
  REQUIRE("42" == rsl::format(FMT_COMPILE("{}"), 42u));
  REQUIRE("42" == rsl::format(FMT_COMPILE("{}"), 42ll));
  REQUIRE("42" == rsl::format(FMT_COMPILE("{}"), 42ull));
  REQUIRE("true" == rsl::format(FMT_COMPILE("{}"), true));
  REQUIRE("x" == rsl::format(FMT_COMPILE("{}"), 'x'));
  REQUIRE("4.2" == rsl::format(FMT_COMPILE("{}"), 4.2));
  REQUIRE("foo" == rsl::format(FMT_COMPILE("{}"), "foo"));
  REQUIRE("foo" == rsl::format(FMT_COMPILE("{}"), std::string("foo")));
  REQUIRE("foo" == rsl::format(FMT_COMPILE("{}"), test_formattable()));
  auto t = std::chrono::system_clock::now();
  REQUIRE(rsl::format("{}", t) == rsl::format(FMT_COMPILE("{}"), t));
#  ifdef __cpp_lib_byte
  REQUIRE("42" == rsl::format(FMT_COMPILE("{}"), std::byte{ 42 }));
#  endif
}

TEST_CASE("compile_test, format_wide_string") {
  REQUIRE(L"42" == rsl::format(FMT_COMPILE(L"{}"), 42));
}

TEST_CASE("compile_test, format_specs") {
  REQUIRE("42" == rsl::format(FMT_COMPILE("{:x}"), 0x42));
  REQUIRE("1.2 ms " == rsl::format(FMT_COMPILE("{:7.1%Q %q}"), std::chrono::duration<double, std::milli>(1.234)));
}

TEST_CASE("compile_test, dynamic_format_specs") {
  REQUIRE("foo  " == rsl::format(FMT_COMPILE("{:{}}"), "foo", 5));
  REQUIRE("  3.14" == rsl::format(FMT_COMPILE("{:{}.{}f}"), 3.141592, 6, 2));
  REQUIRE("=1.234ms=" == rsl::format(FMT_COMPILE("{:=^{}.{}}"), std::chrono::duration<double, std::milli>(1.234), 9, 3));
}

TEST_CASE("compile_test, manual_ordering") {
  REQUIRE("42" == rsl::format(FMT_COMPILE("{0}"), 42));
  REQUIRE(" -42" == rsl::format(FMT_COMPILE("{0:4}"), -42));
  REQUIRE("41 43" == rsl::format(FMT_COMPILE("{0} {1}"), 41, 43));
  REQUIRE("41 43" == rsl::format(FMT_COMPILE("{1} {0}"), 43, 41));
  REQUIRE("41 43" == rsl::format(FMT_COMPILE("{0} {2}"), 41, 42, 43));
  REQUIRE("  41   43" == rsl::format(FMT_COMPILE("{1:{2}} {0:4}"), 43, 41, 4));
  REQUIRE("42 1.2 ms " == rsl::format(FMT_COMPILE("{0} {1:7.1%Q %q}"), 42, std::chrono::duration<double, std::milli>(1.234)));
  REQUIRE("true 42 42 foo 0x1234 foo" == rsl::format(FMT_COMPILE("{0} {1} {2} {3} {4} {5}"), true, 42, 42.0f, "foo", reinterpret_cast<void*>(0x1234), test_formattable()));
  REQUIRE(L"42", rsl::format(FMT_COMPILE(L"{0}"), 42));
}

TEST_CASE("compile_test, manual_ordering") {
  auto runtime_named_field_compiled =
    rsl::detail::compile<decltype(rsl::arg("arg", 42))>(FMT_COMPILE("{arg}"));
  static_assert(std::is_same_v<decltype(runtime_named_field_compiled),
    rsl::detail::runtime_named_field<char>>);

  REQUIRE("42", rsl::format(FMT_COMPILE("{}"), rsl::arg("arg", 42)));
  REQUIRE("41 43", rsl::format(FMT_COMPILE("{} {}"), rsl::arg("arg", 41),
    rsl::arg("arg", 43)));

  REQUIRE("foobar",
    rsl::format(FMT_COMPILE("{a0}{a1}"), rsl::arg("a0", "foo"),
      rsl::arg("a1", "bar")));
  REQUIRE("foobar", rsl::format(FMT_COMPILE("{}{a1}"), rsl::arg("a0", "foo"),
    rsl::arg("a1", "bar")));
  REQUIRE("foofoo", rsl::format(FMT_COMPILE("{a0}{}"), rsl::arg("a0", "foo"),
    rsl::arg("a1", "bar")));
  REQUIRE("foobar", rsl::format(FMT_COMPILE("{0}{a1}"), rsl::arg("a0", "foo"),
    rsl::arg("a1", "bar")));
  REQUIRE("foobar", rsl::format(FMT_COMPILE("{a0}{1}"), rsl::arg("a0", "foo"),
    rsl::arg("a1", "bar")));

  REQUIRE("foobar",
    rsl::format(FMT_COMPILE("{}{a1}"), "foo", rsl::arg("a1", "bar")));
  REQUIRE("foobar",
    rsl::format(FMT_COMPILE("{a0}{a1}"), rsl::arg("a1", "bar"),
      rsl::arg("a2", "baz"), rsl::arg("a0", "foo")));
  REQUIRE(" bar foo ",
    rsl::format(FMT_COMPILE(" {foo} {bar} "), rsl::arg("foo", "bar"),
      rsl::arg("bar", "foo")));

  EXPECT_THROW(rsl::format(FMT_COMPILE("{invalid}"), rsl::arg("valid", 42)),
    rsl::format_error);

#  if FMT_USE_NONTYPE_TEMPLATE_ARGS
  using namespace rsl::literals;
  auto statically_named_field_compiled =
    rsl::detail::compile<decltype("arg"_a = 42)>(FMT_COMPILE("{arg}"));
  static_assert(std::is_same_v<decltype(statically_named_field_compiled),
    rsl::detail::field<char, int, 0>>);

  REQUIRE("41 43",
    rsl::format(FMT_COMPILE("{a0} {a1}"), "a0"_a = 41, "a1"_a = 43));
  REQUIRE("41 43",
    rsl::format(FMT_COMPILE("{a1} {a0}"), "a0"_a = 43, "a1"_a = 41));
#  endif
}

TEST_CASE("compile_test, join") {
  unsigned char data[] = { 0x1, 0x2, 0xaf };
  REQUIRE("0102af", rsl::format(FMT_COMPILE("{:02x}"), rsl::join(data, "")));
}

TEST_CASE("compile_test, format_to") {
  char buf[8];
  auto end = rsl::format_to(buf, FMT_COMPILE("{}"), 42);
  *end = '\0';
  EXPECT_STREQ("42", buf);
  end = rsl::format_to(buf, FMT_COMPILE("{:x}"), 42);
  *end = '\0';
  EXPECT_STREQ("2a", buf);
}

TEST_CASE("compile_test, format_to_n") {
  constexpr auto buffer_size = 8;
  char buffer[buffer_size];
  auto res = rsl::format_to_n(buffer, buffer_size, FMT_COMPILE("{}"), 42);
  *res.out = '\0';
  EXPECT_STREQ("42", buffer);
  res = rsl::format_to_n(buffer, buffer_size, FMT_COMPILE("{:x}"), 42);
  *res.out = '\0';
  EXPECT_STREQ("2a", buffer);
}

#ifdef __cpp_lib_bit_cast
TEST_CASE(compile_test, constexpr_formatted_size) {
  FMT_CONSTEXPR20 size_t s1 = rsl::formatted_size(FMT_COMPILE("{0}"), 42);
  REQUIRE(2, s1);
  FMT_CONSTEXPR20 size_t s2 = rsl::formatted_size(FMT_COMPILE("{0:<4.2f}"), 42.0);
  REQUIRE(5, s2);
}
#endif

TEST_CASE("compile_test, text_and_arg") {
  REQUIRE(">>>42<<<", rsl::format(FMT_COMPILE(">>>{}<<<"), 42));
  REQUIRE("42!", rsl::format(FMT_COMPILE("{}!"), 42));
}

TEST_CASE("compile_test, unknown_format_fallback") {
  REQUIRE(" 42 ",
    rsl::format(FMT_COMPILE("{name:^4}"), rsl::arg("name", 42)));

  std::vector<char> v;
  rsl::format_to(std::back_inserter(v), FMT_COMPILE("{name:^4}"),
    rsl::arg("name", 42));
  REQUIRE(" 42 ", rsl::string_view(v.data(), v.size()));

  char buffer[4];
  auto result = rsl::format_to_n(buffer, 4, FMT_COMPILE("{name:^5}"),
    rsl::arg("name", 42));
  REQUIRE(5u, result.size);
  REQUIRE(buffer + 4, result.out);
  REQUIRE(" 42 ", rsl::string_view(buffer, 4));
}

TEST_CASE("compile_test, empty")
{ 
  REQUIRE("", rsl::format(FMT_COMPILE(""))); 
}

struct to_stringable {
  friend rsl::string_view to_string_view(to_stringable) { return {}; }
};

FMT_BEGIN_NAMESPACE
template <> struct formatter<to_stringable> {
  auto parse(format_parse_context& ctx) const -> decltype(ctx.begin()) {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const to_stringable&, FormatContext& ctx) -> decltype(ctx.out()) {
    return ctx.out();
  }
};
FMT_END_NAMESPACE

TEST_CASE("compile_test, to_string_and_formatter") {
  rsl::format(FMT_COMPILE("{}"), to_stringable());
}

TEST_CASE("compile_test, print") {
  EXPECT_WRITE(stdout, rsl::print(FMT_COMPILE("Don't {}!"), "panic"),
    "Don't panic!");
  EXPECT_WRITE(stderr, rsl::print(stderr, FMT_COMPILE("Don't {}!"), "panic"),
    "Don't panic!");
}
#endif

#if FMT_USE_NONTYPE_TEMPLATE_ARGS
TEST_CASE(compile_test, compile_format_string_literal) {
  using namespace rsl::literals;
  REQUIRE("", rsl::format(""_cf));
  REQUIRE("42", rsl::format("{}"_cf, 42));
  REQUIRE(L"42", rsl::format(L"{}"_cf, 42));
}
#endif

// MSVS 2019 19.29.30145.0 - Support C++20 and OK.
// MSVS 2022 19.32.31332.0 - compile-test.cc(362,3): fatal error C1001: Internal
// compiler error.
//  (compiler file
//  'D:\a\_work\1\s\src\vctools\Compiler\CxxFE\sl\p1\c\constexpr\constexpr.cpp',
//  line 8635)
#if ((FMT_CPLUSPLUS >= 202002L) &&                           \
     (!defined(_GLIBCXX_RELEASE) || _GLIBCXX_RELEASE > 9) && \
     (!FMT_MSC_VERSION || FMT_MSC_VERSION < 1930)) ||        \
    (FMT_CPLUSPLUS >= 201709L && FMT_GCC_VERSION >= 1002)
template <size_t max_string_length, typename Char = char> struct test_string {
  template <typename T> constexpr bool operator==(const T& rhs) const noexcept {
    return rsl::basic_string_view<Char>(rhs).compare(buffer) == 0;
  }
  Char buffer[max_string_length]{};
};

template <size_t max_string_length, typename Char = char, typename... Args>
consteval auto test_format(auto format, const Args&... args) {
  test_string<max_string_length, Char> string{};
  rsl::format_to(string.buffer, format, args...);
  return string;
}

TEST_CASE(compile_time_formatting_test, bool) {
  REQUIRE("true", test_format<5>(FMT_COMPILE("{}"), true));
  REQUIRE("false", test_format<6>(FMT_COMPILE("{}"), false));
  REQUIRE("true ", test_format<6>(FMT_COMPILE("{:5}"), true));
  REQUIRE("1", test_format<2>(FMT_COMPILE("{:d}"), true));
}

TEST_CASE(compile_time_formatting_test, integer) {
  REQUIRE("42", test_format<3>(FMT_COMPILE("{}"), 42));
  REQUIRE("420", test_format<4>(FMT_COMPILE("{}"), 420));
  REQUIRE("42 42", test_format<6>(FMT_COMPILE("{} {}"), 42, 42));
  REQUIRE("42 42",
    test_format<6>(FMT_COMPILE("{} {}"), uint32{ 42 }, uint64{ 42 }));

  REQUIRE("+42", test_format<4>(FMT_COMPILE("{:+}"), 42));
  REQUIRE("42", test_format<3>(FMT_COMPILE("{:-}"), 42));
  REQUIRE(" 42", test_format<4>(FMT_COMPILE("{: }"), 42));

  REQUIRE("-0042", test_format<6>(FMT_COMPILE("{:05}"), -42));

  REQUIRE("101010", test_format<7>(FMT_COMPILE("{:b}"), 42));
  REQUIRE("0b101010", test_format<9>(FMT_COMPILE("{:#b}"), 42));
  REQUIRE("0B101010", test_format<9>(FMT_COMPILE("{:#B}"), 42));
  REQUIRE("042", test_format<4>(FMT_COMPILE("{:#o}"), 042));
  REQUIRE("0x4a", test_format<5>(FMT_COMPILE("{:#x}"), 0x4a));
  REQUIRE("0X4A", test_format<5>(FMT_COMPILE("{:#X}"), 0x4a));

  REQUIRE("   42", test_format<6>(FMT_COMPILE("{:5}"), 42));
  REQUIRE("   42", test_format<6>(FMT_COMPILE("{:5}"), 42ll));
  REQUIRE("   42", test_format<6>(FMT_COMPILE("{:5}"), 42ull));

  REQUIRE("42  ", test_format<5>(FMT_COMPILE("{:<4}"), 42));
  REQUIRE("  42", test_format<5>(FMT_COMPILE("{:>4}"), 42));
  REQUIRE(" 42 ", test_format<5>(FMT_COMPILE("{:^4}"), 42));
  REQUIRE("**-42", test_format<6>(FMT_COMPILE("{:*>5}"), -42));
}

TEST_CASE(compile_time_formatting_test, char) {
  REQUIRE("c", test_format<2>(FMT_COMPILE("{}"), 'c'));

  REQUIRE("c  ", test_format<4>(FMT_COMPILE("{:3}"), 'c'));
  REQUIRE("99", test_format<3>(FMT_COMPILE("{:d}"), 'c'));
}

TEST_CASE(compile_time_formatting_test, string) {
  REQUIRE("42", test_format<3>(FMT_COMPILE("{}"), "42"));
  REQUIRE("The answer is 42",
    test_format<17>(FMT_COMPILE("{} is {}"), "The answer", "42"));

  REQUIRE("abc**", test_format<6>(FMT_COMPILE("{:*<5}"), "abc"));
  REQUIRE("**🤡**", test_format<9>(FMT_COMPILE("{:*^6}"), "🤡"));
}

TEST_CASE(compile_time_formatting_test, combination) {
  REQUIRE("420, true, answer",
    test_format<18>(FMT_COMPILE("{}, {}, {}"), 420, true, "answer"));

  REQUIRE(" -42", test_format<5>(FMT_COMPILE("{:{}}"), -42, 4));
}

TEST_CASE(compile_time_formatting_test, custom_type) {
  REQUIRE("foo", test_format<4>(FMT_COMPILE("{}"), test_formattable()));
  REQUIRE("bar", test_format<4>(FMT_COMPILE("{:b}"), test_formattable()));
}

TEST_CASE(compile_time_formatting_test, multibyte_fill) {
  REQUIRE("жж42", test_format<8>(FMT_COMPILE("{:ж>4}"), 42));
}
#endif

#endif