// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: fmt_chrono_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#ifdef REX_ENABLE_FMT_TESTING

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/chrono.h"
#include "rex_std/time.h"
#include "rex_std/vector.h"

#include "rex_std/format.h"
#include "rex_std/internal/format/chrono.h"

#define REQUIRE_STR(x, y) REQUIRE(rsl::string_view(x) == rsl::string_view(y))

using rsl::runtime;

#if defined(__MINGW32__) && !defined(_UCRT)
// Only C89 conversion specifiers when using MSVCRT instead of UCRT
#  define FMT_HAS_C99_STRFTIME 0
#else
#  define FMT_HAS_C99_STRFTIME 1
#endif

auto make_tm() -> rsl::tm {
  auto time = rsl::tm();
  time.tm_mday = 1;
  return time;
}

auto make_hour(int h) -> rsl::tm {
  auto time = make_tm();
  time.tm_hour = h;
  return time;
}

auto make_minute(int m) -> rsl::tm {
  auto time = make_tm();
  time.tm_min = m;
  return time;
}

auto make_second(int s) -> rsl::tm {
  auto time = make_tm();
  time.tm_sec = s;
  return time;
}

rsl::string system_strftime(const rsl::string& format, const rsl::tm* timeptr, rsl::locale* locptr = nullptr)
{
  auto loc = locptr ? *locptr : rsl::locale::classic();
  auto& facet = rsl::use_facet<rsl::time_put<char>>(loc);
  rsl::ostringstream os;
  os.imbue(loc);
  facet.put(os, os, ' ', timeptr, format.c_str(), format.c_str() + format.size());
#ifdef _WIN32
  // Workaround a bug in older versions of Universal CRT.
  auto str = os.str();
  if (str == "-0000") str = "+0000";
  return str;
#else
  return os.str();
#endif
}

FMT_CONSTEXPR rsl::tm make_tm(int year, int mon, int mday, int hour, int min, int sec)
{
  auto tm = rsl::tm();
  tm.tm_sec = sec;
  tm.tm_min = min;
  tm.tm_hour = hour;
  tm.tm_mday = mday;
  tm.tm_mon = mon - 1;
  tm.tm_year = year - 1900;
  return tm;
}

TEST_CASE("chrono_test, format_tm")
{
  auto tm = rsl::tm();
  tm.tm_year = 116;
  tm.tm_mon = 3;
  tm.tm_mday = 25;
  tm.tm_hour = 11;
  tm.tm_min = 22;
  tm.tm_sec = 33;

  REQUIRE(rsl::format("The date is {:%Y-%m-%d %H:%M:%S}.", tm) == rsl::string_view("The date is 2016-04-25 11:22:33."));
  REQUIRE(rsl::format("{:%Y}", tm) == rsl::string_view("2016"));
  REQUIRE(rsl::format("{:%C}", tm) == rsl::string_view("20"));
  REQUIRE(rsl::format("{:%C%y}", tm) == rsl::format("{:%Y}", tm));
  REQUIRE(rsl::format("{:%e}", tm) == rsl::string_view("25"));
  REQUIRE(rsl::format("{:%D}", tm) == rsl::string_view("04/25/16"));
  REQUIRE(rsl::format("{:%F}", tm) == rsl::string_view("2016-04-25"));
  REQUIRE(rsl::format("{:%T}", tm) == rsl::string_view("11:22:33"));

  // Short year
  tm.tm_year = 999 - 1900;
  tm.tm_mon = 0;   // for %G
  tm.tm_mday = 2;  // for %G
  tm.tm_wday = 3;  // for %G
  tm.tm_yday = 1;  // for %G
  REQUIRE(rsl::format("{:%Y}", tm) == rsl::string_view("0999"));
  REQUIRE(rsl::format("{:%C%y}", tm) == rsl::string_view("0999"));
  REQUIRE(rsl::format("{:%G}", tm) == rsl::string_view("0999"));

  tm.tm_year = 27 - 1900;
  REQUIRE(rsl::format("{:%Y}", tm) == rsl::string_view("0027"));
  REQUIRE(rsl::format("{:%C%y}", tm) == rsl::string_view("0027"));

  // Overflow year
  tm.tm_year = 2147483647;
  REQUIRE(rsl::format("{:%Y}", tm) == rsl::string_view("2147485547"));

  tm.tm_year = -2147483648;
  REQUIRE(rsl::format("{:%Y}", tm) == rsl::string_view("-2147481748"));

  // for week on the year
  // https://www.cl.cam.ac.uk/~mgk25/iso-time.html
  rsl::vector<rsl::tm> tm_list =
  {
    make_tm(1975, 12, 29, 12, 14, 16),  // W01
    make_tm(1977, 1, 2, 12, 14, 16),    // W53
    make_tm(1999, 12, 27, 12, 14, 16),  // W52
    make_tm(1999, 12, 31, 12, 14, 16),  // W52
    make_tm(2000, 1, 1, 12, 14, 16),    // W52
    make_tm(2000, 1, 2, 12, 14, 16),    // W52
    make_tm(2000, 1, 3, 12, 14, 16)     // W1
  };

#if !FMT_HAS_C99_STRFTIME
  GTEST_SKIP() << "Skip the rest of this test because it relies on strftime() "
    "conforming to C99, but on this platform, MINGW + MSVCRT, "
    "the function conforms only to C89.";
#endif

  const rsl::string iso_week_spec = "%Y-%m-%d: %G %g %V";
  for (auto ctm : tm_list)
  {
    // Calculate tm_yday, tm_wday, etc.
    rsl::time_t t = rsl::mktime(&ctm);
    tm = *rsl::localtime(&t);

    auto fmt_spec = rsl::format("{{:{}}}", iso_week_spec);
    REQUIRE(system_strftime(iso_week_spec, &tm) == rsl::format(rsl::runtime(fmt_spec), tm));
  }

  // Every day from 1970-01-01
  rsl::time_t time_now = rsl::time(nullptr);
  for (rsl::time_t t = 6 * 3600; t < time_now; t += 86400) {
    tm = *rsl::localtime(&t);

    auto fmt_spec = rsl::format("{{:{}}}", iso_week_spec);
    REQUIRE(system_strftime(iso_week_spec, &tm) == rsl::format(rsl::runtime(fmt_spec), tm));
  }
}

// MSVC:
//  minkernel\crts\ucrt\src\appcrt\time\wcsftime.cpp(971) : Assertion failed:
//  timeptr->tm_year >= -1900 && timeptr->tm_year <= 8099
#ifndef _WIN32
TEST(chrono_test, format_tm_future) {
  auto tm = rsl::tm();
  tm.tm_year = 10445;  // 10000+ years
  tm.tm_mon = 3;
  tm.tm_mday = 25;
  tm.tm_hour = 11;
  tm.tm_min = 22;
  tm.tm_sec = 33;
  REQUIRE(rsl::format("The date is {:%Y-%m-%d %H:%M:%S}.", tm),
    "The date is 12345-04-25 11:22:33.");
  REQUIRE(rsl::format("{:%Y}", tm), "12345");
  REQUIRE(rsl::format("{:%C}", tm), "123");
  REQUIRE(rsl::format("{:%C%y}", tm), rsl::format("{:%Y}", tm));
  REQUIRE(rsl::format("{:%D}", tm), "04/25/45");
  REQUIRE(rsl::format("{:%F}", tm), "12345-04-25");
  REQUIRE(rsl::format("{:%T}", tm), "11:22:33");
}

TEST(chrono_test, format_tm_past) {
  auto tm = rsl::tm();
  tm.tm_year = -2001;
  tm.tm_mon = 3;
  tm.tm_mday = 25;
  tm.tm_hour = 11;
  tm.tm_min = 22;
  tm.tm_sec = 33;
  REQUIRE(rsl::format("The date is {:%Y-%m-%d %H:%M:%S}.", tm),
    "The date is -101-04-25 11:22:33.");
  REQUIRE(rsl::format("{:%Y}", tm), "-101");

  // macOS  %C - "-1"
  // Linux  %C - "-2"
  // rsl    %C - "-1"
  REQUIRE(rsl::format("{:%C}", tm), "-1");
  REQUIRE(rsl::format("{:%C%y}", tm), rsl::format("{:%Y}", tm));

  // macOS  %D - "04/25/01" (%y)
  // Linux  %D - "04/25/99" (%y)
  // rsl    %D - "04/25/01" (%y)
  REQUIRE(rsl::format("{:%D}", tm), "04/25/01");

  REQUIRE(rsl::format("{:%F}", tm), "-101-04-25");
  REQUIRE(rsl::format("{:%T}", tm), "11:22:33");

  tm.tm_year = -1901;  // -1
  REQUIRE(rsl::format("{:%Y}", tm), "-001");
  REQUIRE(rsl::format("{:%C%y}", tm), rsl::format("{:%Y}", tm));

  tm.tm_year = -1911;  // -11
  REQUIRE(rsl::format("{:%Y}", tm), "-011");
  REQUIRE(rsl::format("{:%C%y}", tm), rsl::format("{:%Y}", tm));
}
#endif

TEST_CASE("chrono_test, grow_buffer")
{
  auto s = rsl::string("{:");
  for (int i = 0; i < 30; ++i) s += "%c";
  s += "}\n";
  auto t = rsl::time(nullptr);
  (void)rsl::format(rsl::runtime(s), *rsl::localtime(&t));
}

TEST_CASE("chrono_test, format_to_empty_container") {
  auto time = rsl::tm();
  time.tm_sec = 42;
  auto s = rsl::string();
  rsl::format_to(rsl::back_inserter(s), "{:%S}", time);
  REQUIRE(s == rsl::string_view("42"));
}

TEST_CASE("chrono_test, empty_result")
{
  REQUIRE(rsl::format("{}", rsl::tm()) == rsl::string_view(""));
}

auto equal(const rsl::tm& lhs, const rsl::tm& rhs) -> bool {
  return lhs.tm_sec == rhs.tm_sec && lhs.tm_min == rhs.tm_min &&
    lhs.tm_hour == rhs.tm_hour && lhs.tm_mday == rhs.tm_mday &&
    lhs.tm_mon == rhs.tm_mon && lhs.tm_year == rhs.tm_year &&
    lhs.tm_wday == rhs.tm_wday && lhs.tm_yday == rhs.tm_yday &&
    lhs.tm_isdst == rhs.tm_isdst;
}

TEST_CASE("chrono_test, gmtime") 
{
  auto t = rsl::time(nullptr);
  auto tm = *rsl::gmtime(&t);
  REQUIRE(equal(tm, rsl::gmtime(t)) == true);
}

template <typename TimePoint>
auto strftime_full_utc(TimePoint tp) -> rsl::string 
{
  auto t = rsl::chrono::system_clock::to_time_t(tp);
  auto tm = *rsl::gmtime(&t);
  return system_strftime("%Y-%m-%d %H:%M:%S", &tm);
}

TEST_CASE("chrono_test, system_clock_time_point") 
{
  auto t1 = rsl::chrono::time_point_cast<rsl::chrono::seconds>(rsl::chrono::system_clock::now());
  REQUIRE_STR(strftime_full_utc(t1), rsl::format("{:%Y-%m-%d %H:%M:%S}", t1));
  REQUIRE_STR(strftime_full_utc(t1), rsl::format("{}", t1));
  using time_point = rsl::chrono::time_point<rsl::chrono::system_clock, rsl::chrono::seconds>;
  auto t2 = time_point(rsl::chrono::seconds(42));
  REQUIRE_STR(strftime_full_utc(t2), rsl::format("{:%Y-%m-%d %H:%M:%S}", t2));

  rsl::vector<rsl::string_view> spec_list = {
      "%%",  "%n",  "%t",  "%Y",  "%EY", "%y",  "%Oy", "%Ey", "%C",
      "%EC", "%G",  "%g",  "%b",  "%h",  "%B",  "%m",  "%Om", "%U",
      "%OU", "%W",  "%OW", "%V",  "%OV", "%j",  "%d",  "%Od", "%e",
      "%Oe", "%a",  "%A",  "%w",  "%Ow", "%u",  "%Ou", "%H",  "%OH",
      "%I",  "%OI", "%M",  "%OM", "%S",  "%OS", "%x",  "%Ex", "%X",
      "%EX", "%D",  "%F",  "%R",  "%T",  "%p" };
#ifndef _WIN32
  // Disabled on Windows because these formats are not consistent among
  // platforms.
  spec_list.insert(spec_list.end(), { "%c", "%Ec", "%r" });
#elif !FMT_HAS_C99_STRFTIME
  // Only C89 conversion specifiers when using MSVCRT instead of UCRT
  spec_list = { "%%", "%Y", "%y", "%b", "%B", "%m", "%U", "%W", "%j", "%d",
               "%a", "%A", "%w", "%H", "%I", "%M", "%S", "%x", "%X", "%p" };
#endif
  spec_list.emplace_back("%Y-%m-%d %H:%M:%S");

  for (const auto& spec : spec_list) 
  {
    auto t = rsl::chrono::system_clock::to_time_t(t1);
    auto tm = *rsl::gmtime(&t);

    auto sys_output = system_strftime(spec, &tm);

    auto fmt_spec = rsl::format("{{:{}}}", spec);
    REQUIRE_STR(sys_output, rsl::format(rsl::runtime(fmt_spec), t1));
    REQUIRE_STR(sys_output, rsl::format(rsl::runtime(fmt_spec), tm));
  }

  // Timezone formatters tests makes sense for localtime.
#if FMT_HAS_C99_STRFTIME
  spec_list = { "%z", "%Z" };
#else
  spec_list = { "%Z" };
#endif
  for (const auto& spec : spec_list) {
    auto t = rsl::chrono::system_clock::to_time_t(t1);
    auto tm = *rsl::localtime(&t);

    auto sys_output = system_strftime(spec, &tm);

    auto fmt_spec = rsl::format("{{:{}}}", spec);
    REQUIRE(sys_output == rsl::format(rsl::runtime(fmt_spec), tm));

    if (spec == "%z") {
      sys_output.insert(sys_output.end() - 2, 1, ':');
      REQUIRE_STR(sys_output, rsl::format("{:%Ez}", tm));
      REQUIRE_STR(sys_output, rsl::format("{:%Oz}", tm));
    }
  }

  // Separate tests for UTC, since rsl::time_put can use local time and ignoring
  // the timezone in rsl::tm (if it presents on platform).
  if (rsl::detail::has_member_data_tm_zone<rsl::tm>::value) {
    auto t = rsl::chrono::system_clock::to_time_t(t1);
    auto tm = *rsl::gmtime(&t);

    rsl::vector<rsl::string> tz_names = { "GMT", "UTC" };
    EXPECT_THAT(tz_names, Contains(rsl::format("{:%Z}", t1)));
    EXPECT_THAT(tz_names, Contains(rsl::format("{:%Z}", tm)));
  }

  if (rsl::detail::has_member_data_tm_gmtoff<rsl::tm>::value) {
    auto t = rsl::chrono::system_clock::to_time_t(t1);
    auto tm = *rsl::gmtime(&t);

    REQUIRE_STR("+0000", rsl::format("{:%z}", t1));
    REQUIRE_STR("+0000", rsl::format("{:%z}", tm));

    REQUIRE_STR("+00:00", rsl::format("{:%Ez}", t1));
    REQUIRE_STR("+00:00", rsl::format("{:%Ez}", tm));

    REQUIRE_STR("+00:00", rsl::format("{:%Oz}", t1));
    REQUIRE_STR("+00:00", rsl::format("{:%Oz}", tm));
  }
}

#if FMT_USE_LOCAL_TIME

TEST(chrono_test, localtime) {
  auto t = rsl::time(nullptr);
  auto tm = *rsl::localtime(&t);
  EXPECT_TRUE(equal(tm, rsl::localtime(t)));
}

template <typename Duration>
auto strftime_full_local(rsl::chrono::local_time<Duration> tp) -> rsl::string {
  auto t = rsl::chrono::system_clock::to_time_t(
    rsl::chrono::current_zone()->to_sys(tp));
  auto tm = *rsl::localtime(&t);
  return system_strftime("%Y-%m-%d %H:%M:%S", &tm);
}

TEST(chrono_test, local_system_clock_time_point) {
#  ifdef _WIN32
  return;  // Not supported on Windows.
#  endif
  auto t1 = rsl::chrono::time_point_cast<rsl::chrono::seconds>(
    rsl::chrono::current_zone()->to_local(rsl::chrono::system_clock::now()));
  REQUIRE(strftime_full_local(t1), rsl::format("{:%Y-%m-%d %H:%M:%S}", t1));
  REQUIRE(strftime_full_local(t1), rsl::format("{}", t1));
  using time_point = rsl::chrono::local_time<rsl::chrono::seconds>;
  auto t2 = time_point(rsl::chrono::seconds(86400 + 42));
  REQUIRE(strftime_full_local(t2), rsl::format("{:%Y-%m-%d %H:%M:%S}", t2));

  rsl::vector<rsl::string> spec_list = {
      "%%",  "%n",  "%t",  "%Y",  "%EY", "%y",  "%Oy", "%Ey", "%C",
      "%EC", "%G",  "%g",  "%b",  "%h",  "%B",  "%m",  "%Om", "%U",
      "%OU", "%W",  "%OW", "%V",  "%OV", "%j",  "%d",  "%Od", "%e",
      "%Oe", "%a",  "%A",  "%w",  "%Ow", "%u",  "%Ou", "%H",  "%OH",
      "%I",  "%OI", "%M",  "%OM", "%S",  "%OS", "%x",  "%Ex", "%X",
      "%EX", "%D",  "%F",  "%R",  "%T",  "%p",  "%z",  "%Z" };
#  ifndef _WIN32
  // Disabled on Windows because these formats are not consistent among
  // platforms.
  spec_list.insert(spec_list.end(), { "%c", "%Ec", "%r" });
#  elif !FMT_HAS_C99_STRFTIME
  // Only C89 conversion specifiers when using MSVCRT instead of UCRT
  spec_list = { "%%", "%Y", "%y", "%b", "%B", "%m", "%U", "%W", "%j", "%d", "%a",
               "%A", "%w", "%H", "%I", "%M", "%S", "%x", "%X", "%p", "%Z" };
#  endif
  spec_list.push_back("%Y-%m-%d %H:%M:%S");

  for (const auto& spec : spec_list) {
    auto t = rsl::chrono::system_clock::to_time_t(
      rsl::chrono::current_zone()->to_sys(t1));
    auto tm = *rsl::localtime(&t);

    auto sys_output = system_strftime(spec, &tm);

    auto fmt_spec = rsl::format("{{:{}}}", spec);
    REQUIRE(sys_output, rsl::format(rsl::runtime(fmt_spec), t1));
    REQUIRE(sys_output, rsl::format(rsl::runtime(fmt_spec), tm));
  }

  if (rsl::find(spec_list.cbegin(), spec_list.cend(), "%z") !=
    spec_list.cend()) {
    auto t = rsl::chrono::system_clock::to_time_t(
      rsl::chrono::current_zone()->to_sys(t1));
    auto tm = *rsl::localtime(&t);

    auto sys_output = system_strftime("%z", &tm);
    sys_output.insert(sys_output.end() - 2, 1, ':');

    REQUIRE(sys_output, rsl::format("{:%Ez}", t1));
    REQUIRE(sys_output, rsl::format("{:%Ez}", tm));

    REQUIRE(sys_output, rsl::format("{:%Oz}", t1));
    REQUIRE(sys_output, rsl::format("{:%Oz}", tm));
  }
}

#endif  // FMT_USE_LOCAL_TIME

#ifndef FMT_STATIC_THOUSANDS_SEPARATOR

TEST_CASE("chrono_test, format_default")
{
  REQUIRE_STR("42s", rsl::format("{}", rsl::chrono::seconds(42)));
  REQUIRE_STR("42as",
    rsl::format("{}", rsl::chrono::duration<int, rsl::atto>(42)));
  REQUIRE_STR("42fs",
    rsl::format("{}", rsl::chrono::duration<int, rsl::femto>(42)));
  REQUIRE_STR("42ps",
    rsl::format("{}", rsl::chrono::duration<int, rsl::pico>(42)));
  REQUIRE_STR("42ns", rsl::format("{}", rsl::chrono::nanoseconds(42)));
  REQUIRE_STR("42µs", rsl::format("{}", rsl::chrono::microseconds(42)));
  REQUIRE_STR("42ms", rsl::format("{}", rsl::chrono::milliseconds(42)));
  REQUIRE_STR("42cs",
    rsl::format("{}", rsl::chrono::duration<int, rsl::centi>(42)));
  REQUIRE_STR("42ds",
    rsl::format("{}", rsl::chrono::duration<int, rsl::deci>(42)));
  REQUIRE_STR("42s", rsl::format("{}", rsl::chrono::seconds(42)));
  REQUIRE_STR("42das",
    rsl::format("{}", rsl::chrono::duration<int, rsl::deca>(42)));
  REQUIRE_STR("42hs",
    rsl::format("{}", rsl::chrono::duration<int, rsl::hecto>(42)));
  REQUIRE_STR("42ks",
    rsl::format("{}", rsl::chrono::duration<int, rsl::kilo>(42)));
  REQUIRE_STR("42Ms",
    rsl::format("{}", rsl::chrono::duration<int, rsl::mega>(42)));
  REQUIRE_STR("42Gs",
    rsl::format("{}", rsl::chrono::duration<int, rsl::giga>(42)));
  REQUIRE_STR("42Ts",
    rsl::format("{}", rsl::chrono::duration<int, rsl::tera>(42)));
  REQUIRE_STR("42Ps",
    rsl::format("{}", rsl::chrono::duration<int, rsl::peta>(42)));
  REQUIRE_STR("42Es",
    rsl::format("{}", rsl::chrono::duration<int, rsl::exa>(42)));
  REQUIRE_STR("42m", rsl::format("{}", rsl::chrono::minutes(42)));
  REQUIRE_STR("42h", rsl::format("{}", rsl::chrono::hours(42)));
  REQUIRE_STR(
    "42[15]s",
    rsl::format("{}", rsl::chrono::duration<int, rsl::ratio<15, 1>>(42)));
  REQUIRE_STR(
    "42[15/4]s",
    rsl::format("{}", rsl::chrono::duration<int, rsl::ratio<15, 4>>(42)));
}

TEST_CASE("chrono_test, align") {
  auto s = rsl::chrono::seconds(42);
  REQUIRE_STR("42s  ", rsl::format("{:5}", s));
  REQUIRE_STR("42s  ", rsl::format("{:{}}", s, 5));
  REQUIRE_STR("  42s", rsl::format("{:>5}", s));
  REQUIRE_STR("**42s**", rsl::format("{:*^7}", s));
  REQUIRE_STR("03:25:45    ",
    rsl::format("{:12%H:%M:%S}", rsl::chrono::seconds(12345)));
  REQUIRE_STR("    03:25:45",
    rsl::format("{:>12%H:%M:%S}", rsl::chrono::seconds(12345)));
  REQUIRE_STR("~~03:25:45~~",
    rsl::format("{:~^12%H:%M:%S}", rsl::chrono::seconds(12345)));
  REQUIRE_STR("03:25:45    ",
    rsl::format("{:{}%H:%M:%S}", rsl::chrono::seconds(12345), 12));
}

TEST_CASE("chrono_test, format_specs") {
  REQUIRE_STR("%", rsl::format("{:%%}", rsl::chrono::seconds(0)));
  REQUIRE_STR("\n", rsl::format("{:%n}", rsl::chrono::seconds(0)));
  REQUIRE_STR("\t", rsl::format("{:%t}", rsl::chrono::seconds(0)));
  REQUIRE_STR("00", rsl::format("{:%S}", rsl::chrono::seconds(0)));
  REQUIRE_STR("00", rsl::format("{:%S}", rsl::chrono::seconds(60)));
  REQUIRE_STR("42", rsl::format("{:%S}", rsl::chrono::seconds(42)));
  REQUIRE_STR("01.234", rsl::format("{:%S}", rsl::chrono::milliseconds(1234)));
  REQUIRE_STR("00", rsl::format("{:%M}", rsl::chrono::minutes(0)));
  REQUIRE_STR("00", rsl::format("{:%M}", rsl::chrono::minutes(60)));
  REQUIRE_STR("42", rsl::format("{:%M}", rsl::chrono::minutes(42)));
  REQUIRE_STR("01", rsl::format("{:%M}", rsl::chrono::seconds(61)));
  REQUIRE_STR("00", rsl::format("{:%H}", rsl::chrono::hours(0)));
  REQUIRE_STR("00", rsl::format("{:%H}", rsl::chrono::hours(24)));
  REQUIRE_STR("14", rsl::format("{:%H}", rsl::chrono::hours(14)));
  REQUIRE_STR("01", rsl::format("{:%H}", rsl::chrono::minutes(61)));
  REQUIRE_STR("12", rsl::format("{:%I}", rsl::chrono::hours(0)));
  REQUIRE_STR("12", rsl::format("{:%I}", rsl::chrono::hours(12)));
  REQUIRE_STR("12", rsl::format("{:%I}", rsl::chrono::hours(24)));
  REQUIRE_STR("04", rsl::format("{:%I}", rsl::chrono::hours(4)));
  REQUIRE_STR("02", rsl::format("{:%I}", rsl::chrono::hours(14)));
  REQUIRE_STR("03:25:45",
    rsl::format("{:%H:%M:%S}", rsl::chrono::seconds(12345)));
  REQUIRE_STR("03:25", rsl::format("{:%R}", rsl::chrono::seconds(12345)));
  REQUIRE_STR("03:25:45", rsl::format("{:%T}", rsl::chrono::seconds(12345)));
  REQUIRE_STR("12345", rsl::format("{:%Q}", rsl::chrono::seconds(12345)));
  REQUIRE_STR("s", rsl::format("{:%q}", rsl::chrono::seconds(12345)));
}

TEST_CASE("chrono_test, invalid_specs") {
  auto sec = rsl::chrono::seconds(0);
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%a}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%A}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%c}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%x}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%Ex}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%X}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%EX}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%D}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%F}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%Ec}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%w}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%u}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%b}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%B}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%z}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%Z}"), sec), rsl::format_error,
    "no date");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%Eq}"), sec), rsl::format_error,
    "invalid format");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:%Oq}"), sec), rsl::format_error,
    "invalid format");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:abc}"), sec), rsl::format_error,
    "invalid format");
  EXPECT_THROW_MSG((void)rsl::format(runtime("{:.2f}"), sec), rsl::format_error,
    "invalid format");
}

auto format_tm(const rsl::tm& time, rsl::string_view spec, const rsl::locale& loc) -> rsl::string 
{
  auto& facet = rsl::use_facet<rsl::time_put<char>>(loc);
  rsl::ostringstream os;
  os.imbue(loc);
  facet.put(os, os, ' ', &time, spec.begin(), spec.end());
  return os.str();
}

TEST_CASE("chrono_test, locale") 
{
  auto loc = get_locale("ja_JP.utf8");
  if (loc == rsl::locale::classic()) return;
#  define EXPECT_TIME(spec, time, duration)                     \
    {                                                           \
      auto jp_loc = rsl::locale("ja_JP.utf8");                  \
      REQUIRE(format_tm(time, spec, jp_loc),                  \
                rsl::format(jp_loc, "{:L" spec "}", duration)); \
    }
  EXPECT_TIME("%OH", make_hour(14), rsl::chrono::hours(14));
  EXPECT_TIME("%OI", make_hour(14), rsl::chrono::hours(14));
  EXPECT_TIME("%OM", make_minute(42), rsl::chrono::minutes(42));
  EXPECT_TIME("%OS", make_second(42), rsl::chrono::seconds(42));
  auto time = make_tm();
  time.tm_hour = 3;
  time.tm_min = 25;
  time.tm_sec = 45;
  auto sec = rsl::chrono::seconds(12345);
  EXPECT_TIME("%r", time, sec);
  EXPECT_TIME("%p", time, sec);
}

using dms = rsl::chrono::duration<double, rsl::milli>;

TEST_CASE("chrono_test, format_default_fp") {
  typedef rsl::chrono::duration<float> fs;
  REQUIRE_STR("1.234s", rsl::format("{}", fs(1.234)));
  typedef rsl::chrono::duration<float, rsl::milli> fms;
  REQUIRE_STR("1.234ms", rsl::format("{}", fms(1.234)));
  typedef rsl::chrono::duration<double> ds;
  REQUIRE_STR("1.234s", rsl::format("{}", ds(1.234)));
  REQUIRE_STR("1.234ms", rsl::format("{}", dms(1.234)));
}

TEST_CASE("chrono_test, format_precision") {
  EXPECT_THROW_MSG(
    (void)rsl::format(runtime("{:.2%Q}"), rsl::chrono::seconds(42)),
    rsl::format_error, "precision not allowed for this argument type");
  REQUIRE_STR("1ms", rsl::format("{:.0}", dms(1.234)));
  REQUIRE_STR("1.2ms", rsl::format("{:.1}", dms(1.234)));
  REQUIRE_STR("1.23ms", rsl::format("{:.{}}", dms(1.234), 2));

  REQUIRE_STR("13ms", rsl::format("{:.0}", dms(12.56)));
  REQUIRE_STR("12.6ms", rsl::format("{:.1}", dms(12.56)));
  REQUIRE_STR("12.56ms", rsl::format("{:.2}", dms(12.56)));
}

TEST_CASE("chrono_test, format_full_specs") {
  REQUIRE_STR("1ms   ", rsl::format("{:6.0}", dms(1.234)));
  REQUIRE_STR("1.2ms ", rsl::format("{:6.1}", dms(1.234)));
  REQUIRE_STR("  1.23ms", rsl::format("{:>8.{}}", dms(1.234), 2));
  REQUIRE_STR(" 1.2ms ", rsl::format("{:^{}.{}}", dms(1.234), 7, 1));
  REQUIRE_STR(" 1.23ms ", rsl::format("{0:^{2}.{1}}", dms(1.234), 2, 8));
  REQUIRE_STR("=1.234ms=", rsl::format("{:=^{}.{}}", dms(1.234), 9, 3));
  REQUIRE_STR("*1.2340ms*", rsl::format("{:*^10.4}", dms(1.234)));

  REQUIRE_STR("13ms  ", rsl::format("{:6.0}", dms(12.56)));
  REQUIRE_STR("    13ms", rsl::format("{:>8.{}}", dms(12.56), 0));
  REQUIRE_STR(" 13ms ", rsl::format("{:^{}.{}}", dms(12.56), 6, 0));
  REQUIRE_STR("  13ms  ", rsl::format("{0:^{2}.{1}}", dms(12.56), 0, 8));
  REQUIRE_STR("==13ms===", rsl::format("{:=^{}.{}}", dms(12.56), 9, 0));
  REQUIRE_STR("***13ms***", rsl::format("{:*^10.0}", dms(12.56)));
}

TEST_CASE("chrono_test, format_simple_q") {
  typedef rsl::chrono::duration<float> fs;
  REQUIRE_STR("1.234 s", rsl::format("{:%Q %q}", fs(1.234)));
  typedef rsl::chrono::duration<float, rsl::milli> fms;
  REQUIRE_STR("1.234 ms", rsl::format("{:%Q %q}", fms(1.234)));
  typedef rsl::chrono::duration<double> ds;
  REQUIRE_STR("1.234 s", rsl::format("{:%Q %q}", ds(1.234)));
  REQUIRE_STR("1.234 ms", rsl::format("{:%Q %q}", dms(1.234)));
}

TEST_CASE("chrono_test, format_precision_q") {
  EXPECT_THROW_MSG(
    (void)rsl::format(runtime("{:.2%Q %q}"), rsl::chrono::seconds(42)),
    rsl::format_error, "precision not allowed for this argument type");
  REQUIRE_STR("1.2 ms", rsl::format("{:.1%Q %q}", dms(1.234)));
  REQUIRE_STR("1.23 ms", rsl::format("{:.{}%Q %q}", dms(1.234), 2));
}

TEST_CASE("chrono_test, format_full_specs_q") {
  REQUIRE_STR("1 ms   ", rsl::format("{:7.0%Q %q}", dms(1.234)));
  REQUIRE_STR("1.2 ms ", rsl::format("{:7.1%Q %q}", dms(1.234)));
  REQUIRE_STR(" 1.23 ms", rsl::format("{:>8.{}%Q %q}", dms(1.234), 2));
  REQUIRE_STR(" 1.2 ms ", rsl::format("{:^{}.{}%Q %q}", dms(1.234), 8, 1));
  REQUIRE_STR(" 1.23 ms ", rsl::format("{0:^{2}.{1}%Q %q}", dms(1.234), 2, 9));
  REQUIRE_STR("=1.234 ms=", rsl::format("{:=^{}.{}%Q %q}", dms(1.234), 10, 3));
  REQUIRE_STR("*1.2340 ms*", rsl::format("{:*^11.4%Q %q}", dms(1.234)));

  REQUIRE_STR("13 ms  ", rsl::format("{:7.0%Q %q}", dms(12.56)));
  REQUIRE_STR("   13 ms", rsl::format("{:>8.{}%Q %q}", dms(12.56), 0));
  REQUIRE_STR(" 13 ms  ", rsl::format("{:^{}.{}%Q %q}", dms(12.56), 8, 0));
  REQUIRE_STR("  13 ms  ", rsl::format("{0:^{2}.{1}%Q %q}", dms(12.56), 0, 9));
  REQUIRE_STR("==13 ms==", rsl::format("{:=^{}.{}%Q %q}", dms(12.56), 9, 0));
  REQUIRE_STR("***13 ms***", rsl::format("{:*^11.0%Q %q}", dms(12.56)));
}

TEST_CASE("chrono_test, invalid_width_id") {
  EXPECT_THROW((void)rsl::format(runtime("{:{o}"), rsl::chrono::seconds(0)),
    rsl::format_error);
}

TEST_CASE("chrono_test, invalid_colons") {
  EXPECT_THROW((void)rsl::format(runtime("{0}=:{0::"), rsl::chrono::seconds(0)),
    rsl::format_error);
}

TEST_CASE("chrono_test, negative_durations") {
  REQUIRE_STR("-12345", rsl::format("{:%Q}", rsl::chrono::seconds(-12345)));
  REQUIRE_STR("-03:25:45",
    rsl::format("{:%H:%M:%S}", rsl::chrono::seconds(-12345)));
  REQUIRE_STR("-00:01",
    rsl::format("{:%M:%S}", rsl::chrono::duration<double>(-1)));
  REQUIRE_STR("s", rsl::format("{:%q}", rsl::chrono::seconds(-12345)));
  REQUIRE_STR("-00.127",
    rsl::format("{:%S}",
      rsl::chrono::duration<signed char, rsl::milli>{-127}));
  auto min = rsl::numeric_limits<int>::min();
  REQUIRE_STR(rsl::format("{}", min),
    rsl::format("{:%Q}", rsl::chrono::duration<int>(min)));
}

TEST_CASE("chrono_test, special_durations") {
  auto value = rsl::format("{:%S}", rsl::chrono::duration<double>(1e20));
  REQUIRE_STR(value, "40");
  auto nan = rsl::numeric_limits<double>::quiet_NaN();
  REQUIRE_STR(
    "nan nan nan nan nan:nan nan",
    rsl::format("{:%I %H %M %S %R %r}", rsl::chrono::duration<double>(nan)));
  REQUIRE_STR(rsl::format("{}", rsl::chrono::duration<float, rsl::exa>(1)),
    "1Es");
  REQUIRE_STR(rsl::format("{}", rsl::chrono::duration<float, rsl::atto>(1)),
    "1as");
  REQUIRE_STR(rsl::format("{:%R}", rsl::chrono::duration<char, rsl::mega>{2}),
    "03:33");
  REQUIRE_STR(rsl::format("{:%T}", rsl::chrono::duration<char, rsl::mega>{2}),
    "03:33:20");
  REQUIRE_STR("44.000000000000",
    rsl::format("{:%S}", rsl::chrono::duration<float, rsl::pico>(
      1.54213895E+26)));
}

TEST_CASE("chrono_test, unsigned_duration") {
  REQUIRE("42s", rsl::format("{}", rsl::chrono::duration<unsigned>(42)));
}

TEST_CASE("chrono_test, weekday") {
  auto loc = get_locale("ru_RU.UTF-8");
  rsl::locale::global(loc);
  auto mon = rsl::weekday(1);

  auto tm = rsl::tm();
  tm.tm_wday = static_cast<int>(mon.c_encoding());

  REQUIRE_STR(rsl::format("{}", mon), "Mon");
  REQUIRE_STR(rsl::format("{:%a}", tm), "Mon");

  if (loc != rsl::locale::classic()) {
    EXPECT_THAT((rsl::vector<rsl::string>{"Ð¿Ð½", "ÐÐ½", "Ð¿Ð½Ð´", "ÐÐ½Ð´"}),
      Contains(rsl::format(loc, "{:L}", mon)));
    EXPECT_THAT((rsl::vector<rsl::string>{"Ð¿Ð½", "ÐÐ½", "Ð¿Ð½Ð´", "ÐÐ½Ð´"}),
      Contains(rsl::format(loc, "{:%a}", tm)));
  }
}

TEST_CASE("chrono_test, cpp20_duration_subsecond_support") {
  using attoseconds = rsl::chrono::duration<long long, rsl::atto>;
  // Check that 18 digits of subsecond precision are supported.
  REQUIRE_STR(rsl::format("{:%S}", attoseconds{ 999999999999999999 }),
    "00.999999999999999999");
  REQUIRE_STR(rsl::format("{:%S}", attoseconds{ 673231113420148734 }),
    "00.673231113420148734");
  REQUIRE_STR(rsl::format("{:%S}", attoseconds{ -673231113420148734 }),
    "-00.673231113420148734");
  REQUIRE_STR(rsl::format("{:%S}", rsl::chrono::nanoseconds{ 13420148734 }),
    "13.420148734");
  REQUIRE_STR(rsl::format("{:%S}", rsl::chrono::nanoseconds{ -13420148734 }),
    "-13.420148734");
  REQUIRE_STR(rsl::format("{:%S}", rsl::chrono::milliseconds{ 1234 }), "01.234");
  // Check subsecond presision modifier.
  REQUIRE_STR(rsl::format("{:.6%S}", rsl::chrono::nanoseconds{ 1234 }),
    "00.000001");
  REQUIRE_STR(rsl::format("{:.18%S}", rsl::chrono::nanoseconds{ 1234 }),
    "00.000001234000000000");
  REQUIRE_STR(rsl::format("{:.{}%S}", rsl::chrono::nanoseconds{ 1234 }, 6),
    "00.000001");
  REQUIRE_STR(rsl::format("{:.6%S}", rsl::chrono::milliseconds{ 1234 }),
    "01.234000");
  REQUIRE_STR(rsl::format("{:.6%S}", rsl::chrono::milliseconds{ -1234 }),
    "-01.234000");
  REQUIRE_STR(rsl::format("{:.3%S}", rsl::chrono::seconds{ 1234 }), "34.000");
  REQUIRE_STR(rsl::format("{:.3%S}", rsl::chrono::hours{ 1234 }), "00.000");
  REQUIRE_STR(rsl::format("{:.5%S}", dms(1.234)), "00.00123");
  REQUIRE_STR(rsl::format("{:.8%S}", dms(1.234)), "00.00123400");
  {
    // Check that {:%H:%M:%S} is equivalent to {:%T}.
    auto dur = rsl::chrono::milliseconds{ 3601234 };
    auto formatted_dur = rsl::format("{:%T}", dur);
    REQUIRE_STR(formatted_dur, "01:00:01.234");
    REQUIRE_STR(rsl::format("{:%H:%M:%S}", dur), formatted_dur);
    REQUIRE_STR(rsl::format("{:.6%H:%M:%S}", dur), "01:00:01.234000");
  }
  using nanoseconds_dbl = rsl::chrono::duration<double, rsl::nano>;
  REQUIRE_STR(rsl::format("{:%S}", nanoseconds_dbl{ -123456789 }), "-00.123456789");
  REQUIRE_STR(rsl::format("{:%S}", nanoseconds_dbl{ 9123456789 }), "09.123456789");
  // Verify that only the seconds part is extracted and printed.
  REQUIRE_STR(rsl::format("{:%S}", nanoseconds_dbl{ 99123456789 }), "39.123456789");
  REQUIRE_STR(rsl::format("{:%S}", nanoseconds_dbl{ 99123000000 }), "39.123000000");
  {
    // Now the hour is printed, and we also test if negative doubles work.
    auto dur = nanoseconds_dbl{ -99123456789 };
    auto formatted_dur = rsl::format("{:%T}", dur);
    REQUIRE_STR(formatted_dur, "-00:01:39.123456789");
    REQUIRE_STR(rsl::format("{:%H:%M:%S}", dur), formatted_dur);
    REQUIRE_STR(rsl::format("{:.3%H:%M:%S}", dur), "-00:01:39.123");
  }
  // Check that durations with precision greater than rsl::chrono::seconds have
  // fixed precision, and print zeros even if there is no fractional part.
  REQUIRE_STR(rsl::format("{:%S}", rsl::chrono::microseconds{ 7000000 }),
    "07.000000");
  REQUIRE_STR(rsl::format("{:%S}",
    rsl::chrono::duration<long long, rsl::ratio<1, 3>>(1)),
    "00.333333");
  REQUIRE_STR(rsl::format("{:%S}",
    rsl::chrono::duration<long long, rsl::ratio<1, 7>>(1)),
    "00.142857");

  REQUIRE_STR(rsl::format("{:%S}",
    rsl::chrono::duration<char, rsl::ratio<1, 100>>(0x80)),
    "-01.28");

  REQUIRE_STR(
    rsl::format("{:%M:%S}",
      rsl::chrono::duration<short, rsl::ratio<1, 100>>(0x8000)),
    "-05:27.68");

  // Check that floating point seconds with ratio<1,1> are printed.
  REQUIRE_STR(rsl::format("{:%S}", rsl::chrono::duration<double>{1.5}),
    "01.500000");
  REQUIRE_STR(rsl::format("{:%M:%S}", rsl::chrono::duration<double>{-61.25}),
    "-01:01.250000");
}

#endif  // FMT_STATIC_THOUSANDS_SEPARATOR

// Disable the utc_clock test for windows, as the icu.dll used for tzdb
// (time zone database) is not shipped with many windows versions.
#if FMT_USE_UTC_TIME && !defined(_WIN32)
TEST(chrono_test, utc_clock) {
  auto t1 = rsl::chrono::system_clock::now();
  auto t1_utc = rsl::chrono::utc_clock::from_sys(t1);
  REQUIRE(rsl::format("{:%Y-%m-%d %H:%M:%S}", t1),
    rsl::format("{:%Y-%m-%d %H:%M:%S}", t1_utc));
}
#endif

TEST_CASE("chrono_test, timestamps_sub_seconds") {
  rsl::chrono::time_point<rsl::chrono::system_clock,
    rsl::chrono::duration<long long, rsl::ratio<1, 3>>>
    t1(rsl::chrono::duration<long long, rsl::ratio<1, 3>>(4));

  REQUIRE_STR(rsl::format("{:%S}", t1), "01.333333");

  rsl::chrono::time_point<rsl::chrono::system_clock,
    rsl::chrono::duration<double, rsl::ratio<1, 3>>>
    t2(rsl::chrono::duration<double, rsl::ratio<1, 3>>(4));

  REQUIRE_STR(rsl::format("{:%S}", t2), "01.333333");

  const rsl::chrono::time_point<rsl::chrono::system_clock, rsl::chrono::seconds>
    t3(rsl::chrono::seconds(2));

  REQUIRE_STR(rsl::format("{:%S}", t3), "02");

  const rsl::chrono::time_point<rsl::chrono::system_clock,
    rsl::chrono::duration<double>>
    t4(rsl::chrono::duration<double, rsl::ratio<1, 1>>(9.5));

  REQUIRE_STR(rsl::format("{:%S}", t4), "09.500000");

  const rsl::chrono::time_point<rsl::chrono::system_clock,
    rsl::chrono::duration<double>>
    t5(rsl::chrono::duration<double, rsl::ratio<1, 1>>(9));

  REQUIRE_STR(rsl::format("{:%S}", t5), "09");

  const rsl::chrono::time_point<rsl::chrono::system_clock,
    rsl::chrono::milliseconds>
    t6(rsl::chrono::seconds(1) + rsl::chrono::milliseconds(120));

  REQUIRE_STR(rsl::format("{:%S}", t6), "01.120");

  const rsl::chrono::time_point<rsl::chrono::system_clock,
    rsl::chrono::microseconds>
    t7(rsl::chrono::microseconds(1234567));

  REQUIRE_STR(rsl::format("{:%S}", t7), "01.234567");

  const rsl::chrono::time_point<rsl::chrono::system_clock,
    rsl::chrono::nanoseconds>
    t8(rsl::chrono::nanoseconds(123456789));

  REQUIRE_STR(rsl::format("{:%S}", t8), "00.123456789");

  const auto t9 = rsl::chrono::time_point_cast<rsl::chrono::nanoseconds>(
    rsl::chrono::system_clock::now());
  const auto t9_sec = rsl::chrono::time_point_cast<rsl::chrono::seconds>(t9);
  auto t9_sub_sec_part = rsl::format("{0:09}", (t9 - t9_sec).count());

  REQUIRE_STR(rsl::format("{}.{}", strftime_full_utc(t9_sec), t9_sub_sec_part),
    rsl::format("{:%Y-%m-%d %H:%M:%S}", t9));

  const rsl::chrono::time_point<rsl::chrono::system_clock,
    rsl::chrono::milliseconds>
    t10(rsl::chrono::milliseconds(2000));

  REQUIRE_STR(rsl::format("{:%S}", t10), "02.000");
}

#endif