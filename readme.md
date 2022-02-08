# libAwesomeMC

libAwesomeMC is a library to read and write Minecraft NBT and Level data.
The current library version targets Minecraft 1.18.1.

# References

Data format references:
* [Chunk-Format](https://minecraft.fandom.com/wiki/Chunk_format)
* [Chunk Format 2](https://wiki.vg/Chunk_Format)
* [Chunk Format Changes 1.18](https://minecraft.fandom.com/wiki/Java_Edition_1.18#General_2)
* [Region-Format](https://minecraft.fandom.com/wiki/Region_file_format)
* [Anvil-Format](https://minecraft.fandom.com/wiki/Anvil_file_format)
* [NBT-Format](https://minecraft.fandom.com/wiki/NBT_format)

# Style Guide

1. Include Order: Local to global -> to prevent hidden dependencies
    * (Prototype/Interface Header for implementation if in *.cpp file)
    * Other headers from same project
    * 3rd party library headers, eg. Qt
    * 3rd party library headers that are almost STD, eg. boost
    * C++ STL
    * C STL 
2. All header includes are based on library 'root/include' dir.
3. Include paths must not be relative => '..'
4. Include Guards 
5. Header files path should be used with library name eg. `include/libname/headers`
6. Use signed types where unsigned is not explicitly necessary.
    * "In particular, do not use unsigned types to say a number will never be negative. Instead, use assertions for this." - Google C++ Style Guide
7. Naming
    1. Classes -> PascalCase 
    2. Members camelCase
    3. private members m_ prefix + camelCase
    4. Concepts -> PascalCase
    5. Traits -> camelCase
    6. Template Parameters -> PascalCase
    7. Enum -> PascalCase
    8. Abstract classes are prefixed with "Abstract"
    9. Abbreviations with max 2 upper case letters in a row, i.e. ID but not TAG
    10. Exceptions where necessary

# TODO

- Project Management
  - Extend support for other compiler and processors
    - Win64
    - Win32
    - Linux64 (WSL) GCC 10.3
    - ARM (RaspberryPi) GCC 10.3
  - Github Workflow?
  - Improve Readme
    - Requirements + Version
    - Tested Versions
    - Use cool batches.
    - Image?
    - Usage example
  - Compileroptions
    - Set Warnings are Errors
    - Add more Warnings for cleaner code
  - Add clang_format
    - Extend Guidelines
  - CMake bring CMakeSettings.json information to CMakeLists-txt in root directory -> build, install, bin dir.
- Library Version
  - Add Minecraft Target Version (1.18.1) + DataVersion (Current 2865)
- Source Code
  - Improve Examples.
    - Naming, functional test code.
  - Unify the use of `char` / `unsigned char` for byte data
  - Round vs. curly braces
  - Use size_t when dealing with sizes of containers
  - Evaluate Header initialization instead of Initialization in constructors
  - Evaluate getter/setter in hpp/cpp, inline?
  - Evaluate getter name without "get" and just the Type name, see. Qt
  - Check if StringTag is Unicode or ASCII (general implementation)
  - set passed pointers to `nullptr` after transfering ownership? Does this increase safety?
- Format & Documentation
  - Check all Comments for style, typos, case, etc.
  - Add Doxygen comments
- Unit tests
  - Implement tests for all missing functions
  - Implement tests for all skipped tests
  - Refactor unit tests
    - Unify tests
      - naming of variables, types
    - Simplyfy tests
    - Use more fixtures
    - Use gmock or custom test functions for checking arrays etc.
    - Use sample data
  - Write unit test and/or example with mcr region test file.
