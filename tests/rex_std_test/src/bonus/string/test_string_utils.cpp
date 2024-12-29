#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/bonus/string/string_utils.h"
#include "rex_std/memory.h"
#include "rex_std/math.h"

TEST_CASE("TEST - strtof")
{
  SECTION("Valid integer strings") 
  {
    CHECK(rsl::strtof("0").value() == 0.0f);
    CHECK(rsl::strtof("123").value() == 123.0f);
    CHECK(rsl::strtof("-456").value() == -456.0f);
  }

  SECTION("Valid floating-point strings") 
  {
    CHECK(rsl::strtof("0.0").value() == Approx(0.0f));
    CHECK(rsl::strtof("3.14159").value() == Approx(3.14159f));
    CHECK(rsl::strtof("-2.71828").value() == Approx(-2.71828f));
    CHECK(rsl::strtof("1e3").value() == Approx(1000.0f));
    CHECK(rsl::strtof("-1.23e-4").value() == Approx(-0.000123f));
  }

  SECTION("Edge cases")
  {
    CHECK(rsl::strtof("0xp2").value() == 0);    // This is actually a string with decimal 0 and "xp2" as suffix, unreletated to the float
    CHECK(rsl::strtof("123abc").value() == 123.0f); 
    CHECK(rsl::strtof("3..14").value() == 3);
  }

  SECTION("Edge cases with large/small numbers") 
  {
    CHECK(rsl::strtof("3.402823466e+38").value() == Approx(std::numeric_limits<float>::max())); // Float max
    CHECK(rsl::strtof("1.175494351e-38F").value() == Approx(std::numeric_limits<float>::min())); // Float min
    CHECK(rsl::strtof("-3.402823466e+38").value() == Approx(std::numeric_limits<float>::lowest()));
  }
}

TEST_CASE("Hexadecimal floating-point conversions", "[rsl::strtof]") 
{
  SECTION("Valid hexadecimal floating-point strings")
  {
    CHECK(rsl::strtof("0x1.0p0").value());       // 1 * 2^0
    CHECK(rsl::strtof("0x1.8p3").value());      // 1.5 * 2^3
    CHECK(rsl::strtof("0x1.0p-1").value());      // 1 * 2^-1
    CHECK(rsl::strtof("0x0.1p4").value());    // 0.0625 * 2^4
    CHECK(rsl::strtof("-0x1.2p2").value());     // -1.25 * 2^2
  }

  SECTION("Edge cases for hexadecimal values") 
  {
    CHECK(rsl::strtof("0x1.fffffep127").value() == Approx(std::numeric_limits<float>::max())); // Max float
    CHECK(rsl::strtof("0x1p-149").value() == Approx(std::numeric_limits<float>::denorm_min())); // Smallest denorm float
    CHECK(rsl::strtof("0x0p0").value() == Approx(0.0f)); // Zero
    CHECK(rsl::strtof("-0x0p0").value() == Approx(-0.0f)); // Negative zero
  }

  SECTION("Invalid hexadecimal floating-point strings") 
  {
    CHECK(rsl::strtof("0x1.2p").has_value() == false);  // Missing exponent
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
    CHECK(std::isnan(rsl::strtof("nan").value()));
    CHECK(std::isnan(rsl::strtof("NaN").value()));
    CHECK(std::isnan(rsl::strtof("NAN").value()));
  }

  SECTION("Empty and invalid strings") 
  {
    CHECK(rsl::strtof("").has_value() == false);
    CHECK(rsl::strtof("abc").has_value() == false);
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