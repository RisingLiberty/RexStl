#include "rex_std_extra/string.h"

namespace rsl
{
  inline namespace v1
  {
    rsl::vector<rsl::string_view> split(rsl::string_view str, rsl::string_view deliminators)
    {
      rsl::vector<rsl::string_view> result;
      card32 start = 0;
      for (card32 i = 0; i < str.size(); ++i)
      {
        char8 c = str[i];
        for (char8 d : deliminators)
        {
          if (c == d)
          {
            result.push_back(str.substr(start, i - start));
            start = i + 1;
          }
        }
      }

      return result;
    }
  }
}