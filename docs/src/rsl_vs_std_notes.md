## Container copying and moving
Container copying and moving with different allocators is not allowed in rtl as this would cause huge performance issues which are easily hidden.

## EnableIf overload resolution
rsl ignores all "this overload does not participate in overload resolution unless ..." that the standard defines for some of it functions. (eg. swap).

the reason for this is that the compiler would likely emit an error anyway and we want to keep the code readable.