#pragma once

#include "rex_std/string.h"
#include "rex_std/string_view.h"
#include "rex_std/vector.h"

namespace rsl
{
  inline namespace v1
  {
    // Splits the string input into different parts using the deliminators
    rsl::vector<rsl::string_view> split(rsl::string_view str, rsl::string_view deliminators);
  }
}