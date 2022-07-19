[![libAwesomeMC Version v0.4.0](https://img.shields.io/badge/libAwesomeMC-v0.4.0-green)](https://github.com/AwesomeCodingGuy/libAwesomeMC)
[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://github.com/AwesomeCodingGuy/libAwesomeMC/blob/main/LICENSE)

# libAwesomeMC - v0.4.0

libAwesomeMC is a cross-platform C++ library to read and write Minecraft NBT and Level data.

The current library version targets Minecraft 1.18.1 and data version 2865.

## Building the library

libAwesomeMC requires a compiler compliant with the C++20 standard and has been tested on:

* Windows (MSVC 2019 - 16.9 or higher) (64bit)
* Linux (GCC - 10.3.0 or higher) (ARM64 and 64bit)

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
$ ./tests
```

## Examples of use

The library has a few very simple example projects to illustrate the use of the library.

### NBT - reading, printing and writing

The following code snippets will show the basic usage of reading a NBT file and printing it to the console.
For this task the function `readNbtFile` can be used, which can be found in the `amc` namespace like all other functions and classes of libAwesomeMC.
This function automatically checks if the file is gzip or zlib compressed and loads its contents to a root CompoundTag.
Also uncompressed files can be read with this function. This function might throw if there are any errors reading the file.

``` cpp

#include <AwesomeMC/nbt/nbt_read.hpp>

/* ... */

std::string filename = "level.dat";
std::unique_ptr<amc::CompoundTag> rootTag = amc::readNbtFile(filename);
```

NBT data can be printed with the function `printNbtData`. The function will construct a std::string.

``` cpp

#include <AwesomeMC/nbt/nbt_print.hpp>

/* ... */

std::cout << amc::printNbtData(rootTag.get())
          << std::endl;
```

There is also a function to write NBT data to a file. All that is needed is a filename, a properly filles CompoundTag and optionally a compression format for the saved data. The default compression for this function is GZip.

``` cpp

#include <AwesomeMC/nbt/nbt_write.hpp>

/* ... */

std::string filename = "nbtfile.dat";
CompoundTag *tag = /* ... */;

bool ret = amc::writeNbtFile(filename, tag, amc::CompressionType::GZip);

```

### NBT - Editing

NBT data is stored in a hierarchical structure, where the root element is always a CompoundTag. The following example shows a minimal example how to setup new NBT data.

``` cpp

#include <AwesomeMC/nbt/tags/tags.hpp>

/* ... */

amc::ByteTag *byteTag = new amc::ByteTag("ByteTag Name", 123);
amc::CompoundTag *compoundTag = new amc::CompoundTag("CompoundTag Name", {
    byteTag,
    new amc::StringTag("StringTag Name", "StringTag Value")
});

```

All tag classes support several functions to access and modify their data. Notice that the parent tag always keeps the ownership of its children. You must not delete them yourself and you should be carefull to keep pointers to tags if the parent gets deleted. 

Classes that hold NBT root objects always store the root as a unique_ptr, so that when they go out of scope or get deleted the tags will be too.

If you want to have a copy of a tag (and its children) you should use the `clone` function.
When adding tags, via the `Constructors`, `insert` or `pushBack` to a `CompoundTag` or a `ListTag` the ownership is transfered.
If you want to remove a tag from `CompoundTag` or `ListTag` and keep the object the functions `take` or `takeAt` should be used and the ownership is transfered to the new object.
Accessing with `at` or index operator will not transfer ownership.
 

### Region - reading and writing

The library also supports reading and writing of Minecraft level data, namely region files (*.mca). A complete region file can be read with the `loadFromFile` member function. The current implementation checks the pattern of the filename, which should match the Minecraft region file pattern.

``` cpp

#include <AwesomeMC/anvil/region.hpp>

/* ... */

std::string filename = "r.-1.-1.mca";

amc::Region region;
region.loadFromFile(filename);

```

In some cases it is usefull to not load the complete region file into memory, i.e. there is only one chunk needed. This can be done by loading only the region file header data and reload the desired chunks manually.

``` cpp

#include <AwesomeMC/anvil/region.hpp>

/* ... */

std::string filename = "r.-1.-1.mca";       // Check the file pattern
int index = 560;                            // Index in range 0 to 1023

amc::Region region;
region.loadPartiallyFromFile(filename);

region.loadChunkAt(index);

```

After one or more chunks have been loaded, they can be accessed and manipulated by their NBT data structure. The following example shows how to access block data of that chunk. The block coordinates have to be in world coordinates.

``` cpp

#include <AwesomeMC/anvil/region.hpp>
#include <AwesomeMC/anvil/chunk.hpp>

/* ... */

region.loadChunkAt(index);

amc::Chunk chunk = region.getChunkAt(index);
if(!chunk.isEmpty()) {
    amc::Block b = chunk.getBlockAt(3, 3, 3);
}

// The same without a Chunk
amc::Block b2 = region.getBlockAt(3, 3, 3);
```

Saving a region is as easy as loading the region.

``` cpp

#include <AwesomeMC/anvil/region.hpp>

/* ... */
region.saveToFile(filename);

```


## Outlook

So far the reading and writing of NBT files, as well as modifying the tags has been tested a lot.

However this library is currently a work in progress. There are still some major tasks to do:

* The documentation must be improved. Maybe I will add Doxygen at a later point.
* There are still some essential unit tests missing for important functions.
* Finding more bugs and errors.

## References

This library is mainly based on the information of various references and further researches.

* [Chunk-Format](https://minecraft.fandom.com/wiki/Chunk_format)
* [Chunk Format 2](https://wiki.vg/Chunk_Format)
* [Chunk Format Changes 1.18](https://minecraft.fandom.com/wiki/Java_Edition_1.18#General_2)
* [Region-Format](https://minecraft.fandom.com/wiki/Region_file_format)
* [Anvil-Format](https://minecraft.fandom.com/wiki/Anvil_file_format)
* [NBT-Format](https://minecraft.fandom.com/wiki/NBT_format)


## About the library

libAwesomeMC has been written to support reading and writing of Minecraft data in private projects.

However, this is not only a library to support my own projects. I hope this library is also useful for other people. 

Please feel free to contact me if there are any bugs, feature requests or problems with the library.

