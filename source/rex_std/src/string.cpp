#include "rex_std/bonus/string.h"

#include "rex_std/algorithm.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      // Splits the string input into different parts using the deliminators
      template <typename CharType, typename Traits>
      rsl::vector<rsl::basic_string_view<CharType, Traits>> split(rsl::basic_string_view<CharType, Traits> str, rsl::basic_string_view<CharType, Traits> deliminators)
      {
        using string_view_type = rsl::basic_string_view<CharType, Traits>;

        rsl::vector<string_view_type> result;

        // Quick memory optimization to avoid reallocation later on
        // Always starts with 1 as in worst case we need to copy the entire string
        card32 delim_in_str = 1;
        for (CharType c : deliminators)
        {
          delim_in_str += rsl::count(str.cbegin(), str.end(), c);
        }
        result.reserve(delim_in_str);

        card32 start = 0;
        for (card32 i = 0; i < str.size(); ++i)
        {
          const CharType c = str[i];
          for (const CharType d : deliminators)
          {
            if (c == d)
            {
              const string_view_type sub_str = str.substr(start, i - start);
              if (!sub_str.empty())
              {
                result.push_back(str.substr(start, i - start));
              }
              start = i + 1;
            }
          }
        }

        if (start != str.size())
        {
          result.push_back(str.substr(start));
        }

        return result;
      }
    }

    rsl::vector<rsl::string_view> split(rsl::string_view str, rsl::string_view deliminators)
    {
      return internal::split(str, deliminators);
    }
    rsl::vector<rsl::wstring_view> split(rsl::wstring_view str, rsl::wstring_view deliminators)
    {
      return internal::split(str, deliminators);
    }

  } // namespace v1
} // namespace rsl