# libAwesomeMC

libAwesomeMC is a cross-platform C++ library to read and write Minecraft NBT and Level data.

The current library version targets Minecraft 1.18.1 and data version 2865.

## Building the library

libAwesomeMC requires a compiler compliant with the C++20 standard and has been tested on:

* Windows (MSVC 2019 - 16.9 or higher) (64bit)
* Linux (GCC 10.3.0 or higher) (ARM64 and 64bit)

This project uses CMake (3.15 or higher) as build system.
To build this library, additional dependencies are required and have to be installed.

* zlib (tested with version >= 1.2.11)
* googletest (only if you plan to build the tests, tested with version >= 1.11.0)

Make sure that the libraries can be found with the `find_package` command of CMake.
You can also point CMake to the correct directory (see section about Windows).

### Building on Windows

The easiest way to build the library is to clone the Github repository and run CMake directly from the console.

```
$ git clone https://github.com/AwesomeCodingGuy/libAwesomeMC.git

$ cd libAwesomeMC/
$ cmake -Bout/build .
$ cmake --build out/build/
```

This should build the project including the samples and the unit tests.
You can run the tests directly after the build:

```
$ cd out/build/Debug
$ ./tests.exe
```

### Building on Linux

Building the library on Linux is quite similar to windows. *Note:* In this example the build directory is one level deeper compared to the Windows build. This is due to the relative directory structure of the unit test data. 

```
$ git clone https://github.com/AwesomeCodingGuy/libAwesomeMC.git

$ cd libAwesomeMC/
$ cmake -Bout/build/Debug .
$ cmake --build out/build/Debug
```

Running the tests.

```
$ cd out/build/Debug
$ ./tests.exe
```


# References

This library is mainly based on the information of various references and further researches.

* [Chunk-Format](https://minecraft.fandom.com/wiki/Chunk_format)
* [Chunk Format 2](https://wiki.vg/Chunk_Format)
* [Chunk Format Changes 1.18](https://minecraft.fandom.com/wiki/Java_Edition_1.18#General_2)
* [Region-Format](https://minecraft.fandom.com/wiki/Region_file_format)
* [Anvil-Format](https://minecraft.fandom.com/wiki/Anvil_file_format)
* [NBT-Format](https://minecraft.fandom.com/wiki/NBT_format)


# About the library

I always wanted to be able to read and write Minecraft data to modify or use it in private projects.
Because there are only a few libraries in C++ and many of them are outdated, I began to develop my own library.
This is not only a library to support my own projects, but also for learning CMake and C++20 features in a practical way.
I hope this library is also useful for other people.

Please feel free to contact me if there are any bugs, feature requests or problems with the library.
