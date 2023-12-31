#include "rex_std_fuzzy/fuzzy_hash.h"

#include "rex_std/functional.h"
#include "rex_std/iostream.h"
#include "rex_std/vector.h"
#include "rex_std/algorithm.h"
#include "rex_std/ctype.h"

namespace rsl
{
  inline namespace v1
  {
    struct HashResult
    {
      std::string input;
      size_t result;
    };

    rsl::vector<HashResult> g_hash_results;
    count_t g_num_collisions = 0;
    count_t g_num_iteration = 0;

    struct FuzzyHashLog
    {
      ~FuzzyHashLog()
      {
        rsl::cout << "hash collision counter: " << g_num_collisions << "/" << g_hash_results.size() << " - " << 100 * (static_cast<float>(g_num_collisions) / g_hash_results.size()) << "%\n";
      }
    } g_log;

    auto collides(size_t res, std::string_view str)
    {
      for (auto it = g_hash_results.cbegin(); it != g_hash_results.cend(); ++it)
      {
        if (it->result == res && it->input != str)
        {
          return it;
        }
      }

      return g_hash_results.cend();
    }

    void fuzz_hash(fuzz_span input)
    {
      ++g_num_iteration;

      // if (!rsl::all_of(input.cbegin(), input.cend(), [](char8 c) {return rsl::is_alnum(c); }))
      // {
      //   return;
      // }

      // alnum only: hash collision counter: 3300/57799 - 5.7094%
      // all chars: hash collision counter: 20616/50000 - 41.2319%
      
      std::string str(input);

      size_t res = std::hash<std::string>{}(str);

      auto it = collides(res, str);

      if (it != g_hash_results.cend())
      {
        ++g_num_collisions;
      }

      if (g_hash_results.size() % 1000 == 0)
      {
        rsl::cout << "iteration: " << g_hash_results.size() << " - " << g_num_iteration << "\n";
      }

      g_hash_results.push_back({str, res});
    }
  } // namespace v1
} // namespace rsl