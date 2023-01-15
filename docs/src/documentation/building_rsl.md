# Building Rex Standard Library

## Build System
Rex Standard Library uses Sharpmake as a build system. Sharpmake uses C# for its build system instead of a custom made scripting language like CMAKE and PreMake.

This makes it easier to develop for and also easier to debug as there are debuggers out there for C# and it allows us to use the entire .NET framework as well as any other libraries written in C#.

## How to build
To build Rex Standard Library you first need to launch the setup script, to make sure all the proper tools are installed. run **setup.py**, this will install the proper tools, including sharpmake.

After the setup script has finished, run build.py. This will build Rex Standard Library.

## How to run the tests
Rex Standard Library consists of a lot of test code as well, making sure the entire library is running correctly.
To run these tests after manually modifying the code, run test.py.

This will run include-what-you-use, clang-tidy, unit tests, address sanitizer, undefined behavior sanitizer and fuzzy testing.