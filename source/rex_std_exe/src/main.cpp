#include "rex_std/iostream.h"

#include <rex_std/format.h>

struct custom_type
{
  int i = 0;
};

namespace rsl
{
  inline namespace v1
  {
    template <> struct formatter<custom_type>
    {
      auto parse(format_parse_context& ctx) const -> decltype(ctx.begin())
      {
        return ctx.begin();
      }

      template <typename FormatContext>
      auto format(const custom_type& p, FormatContext& ctx) -> decltype(ctx.out())
      {
        return format_to(ctx.out(), "cust={}", p.i);
      }
    };
  }
}

int main()
{
  rsl::cout << "this is a test" << "string to check if we provide an implicit space";
}