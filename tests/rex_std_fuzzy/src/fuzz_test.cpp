#include "rex_std_fuzzy/fuzzy_hash.h"

extern "C" int LLVMFuzzerTestOneInput(const char* data, size_t size)
{
  rsl::fuzz_span input(data, size);
  rsl::fuzz_hash(input);

  return 0; // Values other than 0 and -1 are reserved for future use.
}
