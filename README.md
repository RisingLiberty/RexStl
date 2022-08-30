# Rex Standard Library

Rex Standard Library is a custom library based on the C++ Standard Library but with a focus on games.
It is mainly used in the [Rex Engine](https://github.com/Dyronix/Rex), but can be used just like you would with C++ regular's std library.

The library is written using C++17 and will support future C++ versions.


## Usage
If you're familiar with C++ and with the standard library that comes with every major compiler, the library doesn't come with many new features.

In theory you should be able to replace every "std" occurrence with "rsl" as it's the namespace used by this library. However due to some design differences, not everything is directly mappable to the C++ standard.

We keep configuration to a minimum to avoid maintaining code that's rarely used. The code is free and publicly available at on [Github](https://github.com/RisingLiberty/RexStl).
If the user would like to change some code for any reason whatsoever, he/she/they are free to do so.

A pull request can always be made if you think it's useful for other people to know about your request.


## Features
This library was written from scratch, using [C++ standard library](https://github.com/microsoft/STL) (MSVC's implementation) as a reference, as well as a few others (mainly [EASTL](https://github.com/electronicarts/EASTL)). like any software that reaches a certain age, the C++ standard has a lot of legacy code. 

Because the standard library comes with C++, it's very hard to fix mistakes made in the past and break backwards compatibility, it's even worse so as C++ is meant to be backward compatible with C. This limits the capabilities of the C++ standard library.

Rex Standard Library with the intend to break that curse, writing a lot of code from scratch, even some code that comes from the C standard (abs, div, sin, cos, ...).

Some code is implementation defined and closely tied to the operating system (C standard functions like malloc, signal, raise), these functions are not defined in this library.

Supported platforms:
- Windows

## Supported headers
### fully supported headers
- Utilities library
    - initializer_list
    - optional
    - tuple
    - type_traits
    - utility
- Numeric Limits
    - cfloat
    - climits
    - cstdint
    - limits
- Strings library
    - cctype
    - format
    - string
    - string_view
- Containers Library
    - array
    - set
    - vector
- Numerics Library
    - numbers
    - ratio

### partially supported headers
- Utilities library
    - chrono
    - csignal
    - cstddef
    - cstdlib
    - ctime
    - functional
- Dynamic Memory Management
    - memory
- Numeric Limits
    - cinttypes
- Error Handling
    - cassert
- Strings library
    - cstring
- Containers Library
    - forward_list
    - list
    - map
    - multi_map
- Iterators Library
    - iterator
- Algorithms Library
    - algorithm
- Numerics Library
    - cmath
    - numeric

### not supported headers
files marked with [x] are not supported as a design choice
- Utilities library
    - any
    - bitset
    - compare
    - csetjmp [x]
    - cstdarg
    - expected (C++23)
    - source_location(C++20)
    - typeindex
    - typeinfo
    - variant
    - version
- Dynamic Memory Management
    - memory_resource
    - new
    - scoped_allocator
- Numeric Limits
    - stdfloat (C++23)
- Error Handling
    - cerrno
    - exception [x]
    - stacktrace (C++23)
    - stdexcept [x]
    - system_error
- Strings Library
    - charconv
    - cuchar
    - cwchar
    - cwctype
- Containers Library
    - deque
    - queue
    - span (C++20)
    - stack
    - unordered_map
- Ranges Library
    - ranges (C++20)
    - generators (C++23)
- Algorithm library
    - execution
- Numerics Library
    - bit
    - cfenv
    - complex
    - random
    - valarray
- Localization Library
    - clocale
    - locale
- Input/Output Library
    - cstdio
    - fstream
    - iomanip
    - ios
    - iosfwd
    - iostream
    - istream
    - ostream
    - spanstream (C++23)
    - sstream
    - streambuf
    - syncstream (C++20)
- Filesystem library
    - filesystem
- Regular Expressions Library
    - regex
- Atomic Operations Library
    - atomic
- Thread support library
    - barrier (C++20)
    - condition_variable
    - future
    - latch (C++20)
    - mutex
    - semaphore (C++20)
    - shared_mutex
    - stop_token (C++20)
    - thread
- Concepts library
    - concepts (C++20)
- Coroutines Library
    - coroutines (C++20)


## Differences from STL
The C++ standard library targets every developer, finance, medical, game development, embedded devices and many more. Due to this the library is very generic which can hurt performance of some of its code.

Some of the standard code is also calling into C code, which can hurt performance due to lack of code being inlined for various reasons. Until C++23 a lot of C functions also don't work at compile time.

Rex standard library implements this code directly (where possible) without having to rely on C.

Some other differences between Rex standard library and C++ standard library are:
- exceptions are disabled, asserts are used instead
- allocator is not templated and allocates in bytes instead
- no usage of unsigned integers, signed integers are used instead
- 32bit integers type aliases are used, even on 64-bit platforms (size_type, difference_type, ... are always 32 bit)


## Future plans
Not all standard library classes and functions are implemented in Rex standard library yet due to time constrains, but these will come in the future.

other plans for the future (in no particular order)
bullet points marked with (?) are not yet decided.

- remove all C functions "overloads" (labs, llabs, ..)
- remove non-const data access of containers (?)
    - this can be replaced with constructors that take pointers.
    - if the underlying data is writable of a class, it defeats the purpose of the class
- support other platforms (Mac, Linux, Android, iOS)
- support other compilers
- support for clang-tidy
- support for clang-format
- write unit tests
- write documentation
    - the documentation should clearly show where the code differs from the C++ standard library and why.
- upload coding guidelines
- use inline namespaces for versioning of the library
- add natvis files for debugging