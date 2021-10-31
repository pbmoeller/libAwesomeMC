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
    "include/nbt/abstract_tag.hpp"
    "include/nbt/byte_array_tag.hpp"
    "include/nbt/byte_tag.hpp"
    "include/nbt/compound_tag.hpp"
    "include/nbt/double_tag.hpp"
    "include/nbt/end_tag.hpp"
    "include/nbt/float_tag.hpp"
    "include/nbt/int_array_tag.hpp"
    "include/nbt/int_tag.hpp"
    "include/nbt/list_tag.hpp"
    "include/nbt/long_array_tag.hpp"
    "include/nbt/long_tag.hpp"
    "include/nbt/short_tag.hpp"
    "include/nbt/string_tag.hpp"
)

# util
set(UTIL_INCLUDES
    "include/util/byte_stream.hpp"
    "include/util/byte_swap.hpp"
    "include/util/compression.hpp"
)

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
    "src/nbt/abstract_tag.cpp"
    "src/nbt/byte_array_tag.cpp"
    "src/nbt/byte_tag.cpp"
    "src/nbt/compound_tag.cpp"
    "src/nbt/double_tag.cpp"
    "src/nbt/end_tag.cpp"
    "src/nbt/float_tag.cpp"
    "src/nbt/int_array_tag.cpp"
    "src/nbt/int_tag.cpp"
    "src/nbt/list_tag.cpp"
    "src/nbt/long_array_tag.cpp"
    "src/nbt/long_tag.cpp"
    "src/nbt/short_tag.cpp"
    "src/nbt/string_tag.cpp"
)

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
    add_executable(example1 example/example1.cpp)
    target_include_directories(example1
        PRIVATE ${ZLIB_INCLUDE_DIRS}
    )
    target_link_libraries(example1 AwesomeAnvil)
    set_property(TARGET example1 PROPERTY CXX_STANDARD 20)
endif()

# tests
if(build_tests)
    

    add_executable(tests 
        "test/test_main.cpp" 
        "test/types_test.cpp"
        "test/anvil/region_test.cpp" 
        "test/anvil/chunk_info_test.cpp" 
        "test/nbt/abstract_tag_test.cpp"
        "test/nbt/byte_tag_test.cpp"
        "test/nbt/end_tag_test.cpp"
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
    )
    set_property(TARGET tests PROPERTY CXX_STANDARD 20)
endif()