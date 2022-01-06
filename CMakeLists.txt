cmake_minimum_required(VERSION 3.12)

project(AwesomeMC
    VERSION 0.1.0
    LANGUAGES C CXX
)

### Options
option(BUILD_TESTS "Build unit tests for AwesomeMC" TRUE)
option(BUILD_EXAMPLES "Build example programs for AwesomeMC" TRUE)

### Additional flags
set(CMAKE_CXX_STANDARD 20)

### Version
set(AWESOMEMC_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(AWESOMEMC_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(AWESOMEMC_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(AWESOMEMC_VERSION ${AWESOMEMC_VERSION_MAJOR}.${AWESOMEMC_VERSION_MINOR}.${AWESOMEMC_VERSION_PATCH})

execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE AWESOMEMC_GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)
execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE AWESOMEMC_GIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/version.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/include/AwesomeMC/version.h
)

### LIBRARIES

# ZLIB
find_package(ZLIB REQUIRED)

### Includes
# anvil
set(ANVIL_INCLUDES
    "include/AwesomeMC/anvil/chunk_info.hpp"
    "include/AwesomeMC/anvil/chunk.hpp"
    "include/AwesomeMC/anvil/constants.hpp"
    "include/AwesomeMC/anvil/region.hpp"
    "include/AwesomeMC/anvil/region_header.hpp"
    "include/AwesomeMC/anvil/anvil_read.hpp"
    "include/AwesomeMC/anvil/block.hpp"
)

# nbt
set(NBT_INCLUDES
    "include/AwesomeMC/nbt/tags/abstract_tag.hpp"
    "include/AwesomeMC/nbt/tags/byte_array_tag.hpp"
    "include/AwesomeMC/nbt/tags/byte_tag.hpp"
    "include/AwesomeMC/nbt/tags/compound_tag.hpp"
    "include/AwesomeMC/nbt/tags/double_tag.hpp"
    "include/AwesomeMC/nbt/tags/end_tag.hpp"
    "include/AwesomeMC/nbt/tags/float_tag.hpp"
    "include/AwesomeMC/nbt/tags/int_array_tag.hpp"
    "include/AwesomeMC/nbt/tags/int_tag.hpp"
    "include/AwesomeMC/nbt/tags/list_tag.hpp"
    "include/AwesomeMC/nbt/tags/long_array_tag.hpp"
    "include/AwesomeMC/nbt/tags/long_tag.hpp"
    "include/AwesomeMC/nbt/tags/short_tag.hpp"
    "include/AwesomeMC/nbt/tags/string_tag.hpp"
    "include/AwesomeMC/nbt/tags/tags.hpp"
    "include/AwesomeMC/nbt/nbt_read.hpp"
    "include/AwesomeMC/nbt/nbt_print.hpp"
)

# util
set(UTIL_INCLUDES
    "include/AwesomeMC/util/byte_stream.hpp"
    "include/AwesomeMC/util/byte_swap.hpp"
    "include/AwesomeMC/util/compression.hpp"
    "include/AwesomeMC/util/floating_point.hpp"
    "include/AwesomeMC/util/conversion.hpp"
    "include/AwesomeMC/version.h"
)

### Sources
# anvil
set(ANVIL_SOURCES
    "src/anvil/chunk_info.cpp"
    "src/anvil/chunk.cpp"
    "src/anvil/region.cpp"
    "src/anvil/region_header.cpp"
    "src/anvil/anvil_read.cpp"
    "src/anvil/block.cpp"
)

# nbt
set(NBT_SOURCES
    "src/nbt/tags/abstract_tag.cpp"
    "src/nbt/tags/byte_array_tag.cpp"
    "src/nbt/tags/byte_tag.cpp"
    "src/nbt/tags/compound_tag.cpp"
    "src/nbt/tags/double_tag.cpp"
    "src/nbt/tags/end_tag.cpp"
    "src/nbt/tags/float_tag.cpp"
    "src/nbt/tags/int_array_tag.cpp"
    "src/nbt/tags/int_tag.cpp"
    "src/nbt/tags/list_tag.cpp"
    "src/nbt/tags/long_array_tag.cpp"
    "src/nbt/tags/long_tag.cpp"
    "src/nbt/tags/short_tag.cpp"
    "src/nbt/tags/string_tag.cpp"
    "src/nbt/nbt_read.cpp"
    "src/nbt/nbt_print.cpp"
 )

# util
set(UTIL_SOURCES
    "src/util/byte_stream.cpp"
    "src/util/compression.cpp"
    "src/util/conversion.cpp"
)

### Library
if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

### Targets
# lib
add_library(AwesomeMC SHARED 
    ${ANVIL_SOURCES} 
    ${NBT_SOURCES} 
    ${UTIL_SOURCES} 
    ${ANVIL_INCLUDES} 
    ${NBT_INCLUDES} 
    ${UTIL_INCLUDES}
)
target_compile_definitions(AwesomeMC PUBLIC TEST_EXPORT)
target_include_directories(AwesomeMC
    PRIVATE ${ZLIB_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(AwesomeMC ${ZLIB_LIBRARIES})
set_property(TARGET AwesomeMC PROPERTY CXX_STANDARD 20)

# example
if(BUILD_EXAMPLES)
# example 1
    add_executable(example1 "example/example1.cpp")
    target_include_directories(example1
        PRIVATE ${ZLIB_INCLUDE_DIRS}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    target_link_libraries(example1 AwesomeMC)
    set_property(TARGET example1 PROPERTY CXX_STANDARD 20)
# example 2
    add_executable(example_nbt "example/example_nbt.cpp")
    target_include_directories(example_nbt
        PRIVATE ${ZLIB_INCLUDE_DIRS}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    target_link_libraries(example_nbt AwesomeMC)
    set_property(TARGET example_nbt PROPERTY CXX_STANDARD 20)
# example 3
    add_executable(example_anvil "example/example_anvil.cpp")
    target_include_directories(example_anvil
        PRIVATE ${ZLIB_INCLUDE_DIRS}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    target_link_libraries(example_anvil AwesomeMC)
    set_property(TARGET example_anvil PROPERTY CXX_STANDARD 20)
# example 4
    add_executable(load_testmap "example/load_testmap.cpp")
    target_include_directories(load_testmap
        PRIVATE ${ZLIB_INCLUDE_DIRS}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    target_link_libraries(load_testmap AwesomeMC)
    set_property(TARGET load_testmap PROPERTY CXX_STANDARD 20)
endif()

# Build Unit Tests
if(BUILD_TESTS)
    add_subdirectory(test)
endif()