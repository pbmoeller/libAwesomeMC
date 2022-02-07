# ZLIB
find_package(ZLIB REQUIRED)

### Includes
# anvil
set(ANVIL_INCLUDES
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/anvil/anvil_read.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/anvil/block.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/anvil/chunk.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/anvil/chunk_info.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/anvil/heightmap.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/anvil/region.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/anvil/region_header.hpp"
)

# nbt
set(NBT_INCLUDES
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/abstract_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/abstract_vector_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/array_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/byte_array_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/byte_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/compound_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/double_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/end_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/float_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/int_array_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/int_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/list_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/long_array_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/long_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/short_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/string_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/tags.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/value_tag.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/nbt_print.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/nbt_read.hpp"
)

# util
set(UTIL_INCLUDES
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/util/bit.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/util/byte_stream.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/util/byte_swap.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/util/compression.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/util/conversion.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/util/floating_point.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/util/indent.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/util/traits.hpp"
)

set(AWESOMEMC_INCLUDES
    ${ANVIL_INCLUDES}
    ${NBT_INCLUDES}
    ${UTIL_INCLUDES}
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/constants.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/version.hpp"
)

### Sources
# anvil
set(ANVIL_SOURCES
    "anvil/anvil_read.cpp"
    "anvil/block.cpp"
    "anvil/chunk.cpp"
    "anvil/chunk_info.cpp"
    "anvil/heightmap.cpp"
    "anvil/region.cpp"
    "anvil/region_header.cpp"
)

# nbt
set(NBT_SOURCES
    "nbt/tags/abstract_tag.cpp"
    "nbt/tags/abstract_vector_tag.cpp"
    "nbt/tags/compound_tag.cpp"
    "nbt/tags/end_tag.cpp"
    "nbt/tags/list_tag.cpp"
    "nbt/nbt_print.cpp"
    "nbt/nbt_read.cpp"
)

# util
set(UTIL_SOURCES
    "util/byte_stream.cpp"
    "util/compression.cpp"
    "util/conversion.cpp"
    "util/indent.cpp"
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
    ${AWESOMEMC_INCLUDES}
)
target_compile_definitions(AwesomeMC PUBLIC TEST_EXPORT)
target_include_directories(AwesomeMC
    PRIVATE ${ZLIB_INCLUDE_DIRS}
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(AwesomeMC ${ZLIB_LIBRARIES})
set_target_properties(AwesomeMC PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_compile_options(AwesomeMC PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
          -std=c++20 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Woverloaded-virtual -Wpedantic -Wno-psabi>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)
