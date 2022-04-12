# libAwesomeMC

libAwesomeMC is a C++ library to read and write Minecraft NBT and Level data.

The current library version targets Minecraft 1.18.1 and data version 2865.

# Building the library

libAwesomeMC requires a few third party libraries for the full build.

- zlib (tested with version 1.2.11, 1.2.12)
- googletest (only for unit tests, tested with latest version > 1.11.0)

Make sure that the libraries are built and can be found with the `find_package` command of CMake.
You can also point CMake to the correct directory (see section about Windows).

This library requires a compiler with C++20 support. (GCC 10.3.0, Visual Studio 16.9)

# References

Data format references:
* [Chunk-Format](https://minecraft.fandom.com/wiki/Chunk_format)
* [Chunk Format 2](https://wiki.vg/Chunk_Format)
* [Chunk Format Changes 1.18](https://minecraft.fandom.com/wiki/Java_Edition_1.18#General_2)
* [Region-Format](https://minecraft.fandom.com/wiki/Region_file_format)
* [Anvil-Format](https://minecraft.fandom.com/wiki/Anvil_file_format)
* [NBT-Format](https://minecraft.fandom.com/wiki/NBT_format)


# About the library

I always wanted to be able to read and write Minecraft data to modify or use it in private custom projects.
Because there are only a few libraries in C++ and many of them are outdated, I began to develop my own library.
This is not only a library to support my own projects, but also for learning CMake and C++20 features in a practical way.
I hope this library is also useful for other people.

Please feel free to contact me if there are any bugs, feature requests or problems with the library.
