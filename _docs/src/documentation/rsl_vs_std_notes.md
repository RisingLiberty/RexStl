## Container copying and moving
Container copying and moving with different allocators is not allowed in rsl as this would cause huge performance issues which are easily hidden.

## EnableIf overload resolution
rsl ignores all "this overload does not participate in overload resolution unless ..." that the standard defines for some of it functions. (eg. swap).

the reason for this is that the compiler would likely emit an error anyway and we want to keep the code readable.

## Calling rsl::move
rsl implements a rsl::move function, just like the C++ Standard does. However, calling this function with a const lvalue will result in a compiler error. The reason for this is that rsl::move should only be called with rvalues or non-const lvalues, otherwise there is no point in doing the move as it'll result in an error. 
This shouldn't cause any problems, even in templated code as rsl::forward should be called with universal references.