#include "rex_std/bonus/string.h"

namespace rsl
{
  inline namespace v1
  {
    rsl::vector<rsl::string_view> split(rsl::string_view str, rsl::string_view deliminators)
    {
      rsl::vector<rsl::string_view> result;
      card32 start = 0;
      for(card32 i = 0; i < str.size(); ++i)
      {
        const char8 c = str[i];
        for(const char8 d : deliminators)
        {
          if(c == d)
          {
            const rsl::string_view sub_str = str.substr(start, i - start);
            if(!sub_str.empty())
            {
              result.push_back(str.substr(start, i - start));
            }
            start = i + 1;
          }
        }
      }

      if(start != str.size())
      {
        result.push_back(str.substr(start));
      }

      return result;
    }
  } // namespace v1
} // namespace rsl