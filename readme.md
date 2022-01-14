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

1. Include Order: Local to global -> to prvent hidden dependencies
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

# TODO

- Project Management
  - Extend support for other compiler and processors
    - Win64
    - Win32
    - Linux64 (WSL) GCC 10.3
    - ARM (RaspberryPi) GCC 10.x
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
  - Choose and add licence information
  - Test for memory leaks
  - Add clang_format
    - Extend Guidelines
  - CMake bring CMakeSettings.json information to CMakeLists-txt in root directory -> build, install, bin dir.
- Library Version
  - Add Minecraft Target Version (1.18.1) + DataVersion (Current 2865)
- Source Code
  - Improve Examples.
    - Naming, functional test code.
  - Add HeightMap get/set
  - Evaluate iterator for ListTag / CompoundTag? Useful?
  - value_type for tags? -> see STL.
  - Unify the use of `char` / `unsigned char` for byte data
  - Check namespaces, eventually put everything in a common library namespace, i.e. `AwesomeMC`, `amc`, ..., 
    - Remove anvil namespace
  - Round vs. curly braces
  - Use size_t when dealing with sizes of containers
  - Use templates for tags
    - Abstract Intermediate class `NumberTag` for number tags : char, short, int, long, float, double
    - Abstract Intermediate class `ArrayTag` for array tags : byte array, int array, long array
    - Use instanciated unit tests to test the template types.
  - Use correct floating point comparison
  - Evaluate Header initialization instead of Initialization in constructors
  - (Evaluate Custom data types, eg. `NbtShort` for `char` etc.)
  - Check if StringTag is Unicode or ASCII (general implementation)
  - Check all pointers in NBT tags
    - set passed pointers to `nullptr` after transfering ownership? Does this increase safety?
  - ByteStream should use templated stream operators instead of multiple overrides.
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
