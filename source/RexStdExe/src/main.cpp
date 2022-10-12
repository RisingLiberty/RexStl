#include <rex_std/type_traits.h>

int main() 
{
  static_assert(rsl::is_arithmetic_v<int> || !rsl::is_move_constructible_v<int> || !rsl::is_move_assignable_v<int>, "calling move with a const T that can be moved");

}