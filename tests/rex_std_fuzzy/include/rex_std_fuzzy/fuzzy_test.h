#pragma once

#include "rex_std/string_view.h"

#include <string_view>

namespace rsl
{
  inline namespace v1
  {
    using fuzz_span = rsl::basic_string_view<char>;

    // Creates an object by copying N bytes into a trivial object
    // The input is reduced by the number of bytes copied
    template <typename T>
    T make_fuzzy_object(fuzz_span& input)
    {
      static_assert(rsl::is_trivial_v<T>, "Fuzzy object type needs to be trivial");

      T result {};

      card32 bytes_used = rsl::min(input.size(), static_cast<card32>(sizeof(result)));

      rsl::memcpy(&result, input.data(), bytes_used);

      input.remove_prefix(bytes_used);

      return result;
    }
  } // namespace v1
} // namespace rsl