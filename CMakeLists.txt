cmake_minimum_required(VERSION 3.12)

project(AwesomeAnvil C CXX)

### LIBRARIES

# GTEST
if(build_tests)
    enable_testing()
    find_package(GTest REQUIRED)
endif()

# ZLIB
find_package(ZLIB REQUIRED)

### Includes
# anvil
set(ANVIL_INCLUDES
    "include/anvil/chunk_info.hpp"
    "include/anvil/chunk_tag.hpp"
    "include/anvil/constants.hpp"
    "include/anvil/region.hpp"
    "include/anvil/region_header.hpp"
)

# nbt
set(NBT_INCLUDES
    "include/nbt/tags/abstract_tag.hpp"
    "include/nbt/tags/byte_array_tag.hpp"
    "include/nbt/tags/byte_tag.hpp"
    "include/nbt/tags/compound_tag.hpp"
    "include/nbt/tags/double_tag.hpp"
    "include/nbt/tags/end_tag.hpp"
    "include/nbt/tags/float_tag.hpp"
    "include/nbt/tags/int_array_tag.hpp"
    "include/nbt/tags/int_tag.hpp"
    "include/nbt/tags/list_tag.hpp"
    "include/nbt/tags/long_array_tag.hpp"
    "include/nbt/tags/long_tag.hpp"
    "include/nbt/tags/short_tag.hpp"
    "include/nbt/tags/string_tag.hpp"
    "include/nbt/tags.hpp"
 "include/nbt/nbt_reader.hpp")

# util
set(UTIL_INCLUDES
    "include/util/byte_stream.hpp"
    "include/util/byte_swap.hpp"
    "include/util/compression.hpp"
    "include/util/floating_point.hpp")

### Sources
# anvil
set(ANVIL_SOURCES
    "src/anvil/chunk_info.cpp"
    "src/anvil/chunk_tag.cpp"
    "src/anvil/region.cpp"
    "src/anvil/region_header.cpp"
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
 "src/nbt/nbt_reader.cpp")

# util
set(UTIL_SOURCES
    "src/util/byte_stream.cpp"
    "src/util/compression.cpp"
)

### Library
if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

### Targets
# lib
add_library(AwesomeAnvil SHARED 
    ${ANVIL_SOURCES} 
    ${NBT_SOURCES} 
    ${UTIL_SOURCES} 
    ${ANVIL_INCLUDES} 
    ${NBT_INCLUDES} 
    ${UTIL_INCLUDES}
)
target_compile_definitions(AwesomeAnvil PUBLIC TEST_EXPORT)
target_include_directories(AwesomeAnvil
    PRIVATE ${ZLIB_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(AwesomeAnvil ${ZLIB_LIBRARIES})
set_property(TARGET AwesomeAnvil PROPERTY CXX_STANDARD 20)

# example
if(build_examples)
# example 1
    add_executable(example1 "example/example1.cpp")
    target_include_directories(example1
        PRIVATE ${ZLIB_INCLUDE_DIRS}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    target_link_libraries(example1 AwesomeAnvil)
    set_property(TARGET example1 PROPERTY CXX_STANDARD 20)
# example 2
    add_executable(example_nbt "example/example_nbt.cpp")
    target_include_directories(example_nbt
        PRIVATE ${ZLIB_INCLUDE_DIRS}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    target_link_libraries(example_nbt AwesomeAnvil)
    set_property(TARGET example_nbt PROPERTY CXX_STANDARD 20)
endif()

# tests
if(build_tests)
    add_executable(tests 
        "test/test_main.cpp" 
        "test/types_test.cpp"
        "test/nbt/tags/abstract_tag_test.cpp"
        "test/nbt/tags/byte_tag_test.cpp"
        "test/nbt/tags/end_tag_test.cpp"
        "test/nbt/tags/short_tag_test.cpp"
        "test/nbt/tags/long_tag_test.cpp"
        "test/nbt/tags/int_tag_test.cpp"
        "test/nbt/tags/float_tag_test.cpp" 
        "test/nbt/tags/double_tag_test.cpp"
        "test/nbt/tags/byte_array_tag_test.cpp"
        "test/nbt/tags/string_tag_test.cpp"
        "test/nbt/tags/list_tag_test.cpp"
        "test/nbt/tags/int_array_tag_test.cpp"
        "test/nbt/tags/long_array_tag_test.cpp"
        "test/nbt/tags/compound_tag_test.cpp"
        "test/anvil/region_test.cpp"
        "test/anvil/chunk_info_test.cpp"
        "test/util/byte_swap_test.cpp"
        "test/util/byte_stream_test.cpp"
    )
    target_link_libraries(tests AwesomeAnvil ${GTEST_LIBRARIES})
    if(UNIX)
        target_link_libraries(tests pthread)
    endif()

    target_include_directories(tests
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test
        PRIVATE ${GTEST_INCLUDE_DIRS}
        PRIVATE ${GMOCK_INCLUDE_DIRS}
    )
    set_property(TARGET tests PROPERTY CXX_STANDARD 20)
endif()