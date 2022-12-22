# Rex Standard Library

Rex Standard Library is a custom library based on the C++ Standard Library but with a focus on games.
It is mainly used in the [Rex Engine](https://github.com/Dyronix/Rex), but can be used just like you would with C++ regular's std library.

The library is written using C++17 and will support future C++ versions.

The entire library is written by Nick De Breuck, if you have any questions, please reach out on one of the below channels:
- twitter: [@nick_debreuck](https://twitter.com/nick_debreuck)
- discord: Rising Liberty#2195

## Usage
If you're familiar with C++ and with the standard library that comes with every major compiler, the library doesn't come with many new features.

In theory you should be able to replace every "std" occurrence with "rsl" as it's the namespace used by this library. However due to some design differences, not everything is directly mappable to the C++ standard.

We keep configuration to a minimum to avoid maintaining code that's rarely used. The code is free and publicly available on [Github](https://github.com/RisingLiberty/RexStl).
If the user would like to change some code for any reason whatsoever, he/she/they are free to do so.

A pull request can always be made if you think it's useful for other people to know about your request.

## Features
This library was written from scratch, using [C++ standard library](https://github.com/microsoft/STL) (MSVC's implementation) as a reference, as well as a few others (mainly [EASTL](https://github.com/electronicarts/EASTL)). like any software that reaches a certain age, the C++ standard has a lot of legacy code. 

Because the standard library comes with C++, it's very hard to fix mistakes made in the past and break backwards compatibility, it's even worse so as C++ is meant to be backward compatible with C. This limits the capabilities of the C++ standard library.

Rex Standard Library with the intend to break that curse, writing a lot of code from scratch, even some code that comes from the C standard (abs, div, sin, cos, ...).

Some code is implementation defined and closely tied to the operating system (C standard functions like malloc, signal, raise), these functions are not defined in this library.

Supported platforms:
- Windows

## Clang tooling
In C++, there's a lot of things you CAN do, but that doesn't mean you SHOULD do them. to add constrains to the codebase and have them automatically applied,
clang-tidy and clang-format is fully integrated into the build system and added as post build events when building the library.
These checks are enabled in .clang-tidy and .clang-format files which sit in the root directory of the library.

## Unit tests
Unit tests are a great way to make sure your code does exactly what it needs to do. They can catch bugs early on and are a great way to make sure every templated function
is instantiated to make sure all templated code compiles on every compiler and platform.
Currently, the library has unit tests for the following:
    - array
    - chrono
    - ctype
    - functional
    - initializer_list
    - list
    - optional
    - source_location
    - string
    - string_view
    - type_traits
    - unordered_map
    - utility
    - vector

Other than unit tests, other tests are also performed on the code to better tests and catch edge cases, memory issues and undefined behavior.

these additional tests are: 
### include-what-you-use
https://include-what-you-use.org


Include-what-you-use is a tool that parses your code to verify you're only including headers where needed. If you can get away with a forward declare, it'll do that instead, making the header smaller in size and easier to compile.

### Code Coverage
https://clang.llvm.org/docs/SourceBasedCodeCoverage.html

We're applying code coverage on our unit tests to make sure that all the code is properly executed and tested. This is to make sure that when you're writing unit tests, all the code that should be tested (which is all the code) is properly tested.
File summaries, line summaries and lcov reports get auto generated which you can inspect in your browser to verify which files need more tests.

### Address Sanitizer
https://clang.llvm.org/docs/AddressSanitizer.html

This is used for fast memory error detection. Address sanitizer can detect the following errors:
- out-of-bounds access to heap, stack and globals
- use-after-free
- use-after-return
- use-after-scope
- double free
- memory leaks (experimental)

Code does suffer a performance hit when address sanitizer is enabled so this should not be enabled on shipping builds it's great to run unit tests with, especially if those unit tests have 100% code coverage, then you know you're not doing anything bad within your code.

### Undefined Behavior Sanitizer
https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html

Like the address sanitizer detects memory errors, the undefined behavior sanitizer detects undefined behavior in your code.
it can detect the following errors:
- array subscript out of bounds (where the array bounds are statically determined)
- bitwise shifts that are out of bounds for their data type
- dereferencing misaligned or null pointers
- signed integer overflow
- conversion to, from or between floating-point types which would overflow the destination
- float division by zero

more checks are available but these are the ones we enable at the moment.

### Fuzzy testing
https://llvm.org/docs/LibFuzzer.html

Fuzzy testing is a special way of testing your code. You don't necessarily know the output of your code but the goal is to call your code with a lot of different kind of input and make sure it doesn't crash. This works exceptionally well when address sanitizer and undefined behavior sanitizer is enabled

This is enabled for Rex Standard Library but hasn't been properly set up yet, this will get added later.

## Supported headers
### fully supported headers
- Utilities library
    - chrono
    - functional
    - initializer_list
    - optional
    - tuple
    - type_traits
    - utility
- Error Handling
    - cassert
- Numeric Limits
    - cfloat (as float.h)
    - cinttypes ( as inttypes.h)
    - climits (as limits.h)
    - cstdint (as stdint.h)
    - limits
- Strings library
    - cctype (as ctype.h)
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
- Input/Output Library
    - iosfwd
    - iostream
    - istream
    - ostream

### partially supported headers
- Utilities library
    - csignal
    - cstddef
    - cstdlib
    - ctime
- Dynamic Memory Management
    - memory
- Strings library
    - cstring (as string.h)
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
- Input/Output Library
    - ios

### not supported headers
files marked with [x] are not supported as a design choice
- Utilities library
    - any
    - bitset
    - compare
    - csetjmp [x]
    - cstdarg [x]
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


## Removed C Headers
Some C headers were created a long time ago and still exist to avoid breaking old code. Some of its contents are no longer useful in modern code however. platforms are now mostly 64-bit, with a few exceptions still being 32-bit. 

Integer sizes are mostly consistent between platforms, and the "least", "fast" and "max" versions no longer have their purposes in modern day code, that's why these have been removed.

C++ also provides function overloading making a lot of C functions redundant, so these have also been removed to simplify the library.

Some C headers are still useful in modern day code, but these headers got renamed, dropping the 'c' prefix, making them C++ headers.

The removed C headers, or the mapped version to C++ headers are:
- cassert -> assert.h
- cctype -> ctype.h
- cerrno -> errno.h
- cfenv -> fenv.h
- cinttypes -> inttypes.h
- clocale -> removed
- cmath -> math.h
- csetjmp -> removed
- csignal -> removed
- cstdarg -> removed
- cstddef -> stddef.h
- cstdio -> stdio.h
- cstdlib -> stdlib.h
- cstring -> string.h
- ctime -> time.h
- cwchar -> wchar.h
- cwctype -> wctype.h



## Future plans
Not all standard library classes and functions are implemented in Rex standard library yet due to time constrains, but these will come in the future.

other plans for the future (in no particular order)
bullet points marked with (?) are not yet decided.

- remove all C functions "overloads" (labs, llabs, ..)
- remove non-const data access of containers (?)
    - this can be replaced with constructors that take pointers.
    - if the underlying data is writable of a class, it defeats the purpose of the class
- support other platforms (Mac, Linux, Android, iOS)
- write documentation
    - the documentation should clearly show where the code differs from the C++ standard library and why.
- upload coding guidelines
- add natvis files for debugging
