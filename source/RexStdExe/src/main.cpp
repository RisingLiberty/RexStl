#include "rex_std/chrono.h"

int main() 
{
  return static_cast<int>(rsl::chrono::internal::get_ticks());
}