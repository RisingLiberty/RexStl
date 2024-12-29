#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/bonus/string/string_utils.h"
#include "rex_std/memory.h"

TEST_CASE("TEST - strof")
{
  SECTION("Valid integer strings") 
  {
    CHECK(rsl::strtof("0") == 0.0f);
    CHECK(rsl::strtof("123") == 123.0f);
    CHECK(rsl::strtof("-456") == -456.0f);
  }

  SECTION("Valid floating-point strings") 
  {
    CHECK(rsl::strtof("0.0") == Approx(0.0f));
    CHECK(rsl::strtof("3.14159") == Approx(3.14159f));
    CHECK(rsl::strtof("-2.71828") == Approx(-2.71828f));
    CHECK(rsl::strtof("1e3") == Approx(1000.0f));
    CHECK(rsl::strtof("-1.23e-4") == Approx(-0.000123f));
  }

  SECTION("Edge cases with large/small numbers") 
  {
    CHECK(rsl::strtof("1.7976931348623157e+308") == Approx(std::numeric_limits<float>::max())); // Float max
    CHECK(rsl::strtof("2.2250738585072014e-308") == Approx(0.0f)); // Float underflow (too small)
    CHECK(rsl::strtof("-1.7976931348623157e+308") == Approx(-std::numeric_limits<float>::max()));
  }
}

TEST_CASE("Hexadecimal floating-point conversions", "[rsl::strtof]") 
{
  SECTION("Valid hexadecimal floating-point strings")
  {
    REQUIRE(rsl::strtof("0x1.0p0") == Approx(1.0f));       // 1 * 2^0
    REQUIRE(rsl::strtof("0x1.8p3") == Approx(12.0f));      // 1.5 * 2^3
    REQUIRE(rsl::strtof("0x1.0p-1") == Approx(0.5f));      // 1 * 2^-1
    REQUIRE(rsl::strtof("0x0.1p4") == Approx(0.0625f));    // 0.0625 * 2^4
    REQUIRE(rsl::strtof("-0x1.2p2") == Approx(-4.5f));     // -1.25 * 2^2
  }

  SECTION("Edge cases for hexadecimal values") 
  {
    REQUIRE(rsl::strtof("0x1.fffffep127") == Approx(std::numeric_limits<float>::max())); // Max float
    REQUIRE(rsl::strtof("0x1p-149") == Approx(std::numeric_limits<float>::denorm_min())); // Smallest denorm float
    REQUIRE(rsl::strtof("0x0p0") == Approx(0.0f)); // Zero
    REQUIRE(rsl::strtof("-0x0p0") == Approx(-0.0f)); // Negative zero
  }

  SECTION("Invalid hexadecimal floating-point strings") 
  {
    REQUIRE_THROWS_AS(rsl::strtof("0x1.2p"), std::invalid_argument);  // Missing exponent
    REQUIRE_THROWS_AS(rsl::strtof("0xp2"), std::invalid_argument);    // Missing mantissa
    REQUIRE_THROWS_AS(rsl::strtof("0x.2p2"), std::invalid_argument);  // Invalid format
  }
}

TEST_CASE("Special cases", "[rsl::strtof]") 
{
  SECTION("Infinity") 
  {
    CHECK(rsl::strtof("inf") == std::numeric_limits<float>::infinity());
    CHECK(rsl::strtof("-inf") == -std::numeric_limits<float>::infinity());
    CHECK(rsl::strtof("INFINITY") == std::numeric_limits<float>::infinity());
  }

  SECTION("NaN") 
  {
    CHECK(std::isnan(rsl::strtof("nan")));
    CHECK(std::isnan(rsl::strtof("NaN")));
    CHECK(std::isnan(rsl::strtof("NAN")));
  }

  SECTION("Empty and invalid strings") 
  {
    REQUIRE_THROWS_AS(rsl::strtof(""), std::invalid_argument);
    REQUIRE_THROWS_AS(rsl::strtof("abc"), std::invalid_argument);
    REQUIRE_THROWS_AS(rsl::strtof("123abc"), std::invalid_argument);
    REQUIRE_THROWS_AS(rsl::strtof("3..14"), std::invalid_argument);
  }
}

TEST_CASE("Whitespace handling", "[rsl::strtof]") 
{
  SECTION("Leading and trailing whitespace") 
  {
    CHECK(rsl::strtof(" 42 ") == Approx(42.0f));
    CHECK(rsl::strtof("\t-3.14\n") == Approx(-3.14f));
  }
}

TEST_CASE("Boundary values", "[rsl::strtof]") 
{
  SECTION("Smallest normalized and denormalized floats") 
  {
    CHECK(rsl::strtof("1.17549435e-38") == Approx(std::numeric_limits<float>::min())); // Smallest normalized float
    CHECK(rsl::strtof("1.4e-45") == Approx(std::numeric_limits<float>::denorm_min())); // Smallest denormalized float
  }

  SECTION("Largest float") 
  {
    CHECK(rsl::strtof("3.4028235e+38") == Approx(std::numeric_limits<float>::max())); // Largest representable float
  }
}