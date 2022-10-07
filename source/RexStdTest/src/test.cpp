#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "rex_std/vector.h"

TEST_CASE("vector size", "[vector]")
{
  rsl::vector<int> vec;
  vec.push_back(1);
  REQUIRE(vec.size() == 1);
}