# ZLIB
find_package(ZLIB REQUIRED)

### Includes
# anvil
set(ANVIL_INCLUDES
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/anvil/chunk_info.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/anvil/chunk.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/anvil/constants.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/anvil/region.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/anvil/region_header.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/anvil/anvil_read.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/anvil/block.hpp"
)

# nbt
set(NBT_INCLUDES
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/tags/abstract_tag.hpp"
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
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/nbt_read.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/nbt/nbt_print.hpp"
)

# util
set(UTIL_INCLUDES
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/util/byte_stream.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/util/byte_swap.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/util/compression.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/util/floating_point.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/util/conversion.hpp"
    "${CMAKE_SOURCE_DIR}/include/AwesomeMC/version.h"
)

### Sources
# anvil
set(ANVIL_SOURCES
    "anvil/chunk_info.cpp"
    "anvil/chunk.cpp"
    "anvil/region.cpp"
    "anvil/region_header.cpp"
    "anvil/anvil_read.cpp"
    "anvil/block.cpp"
)

# nbt
set(NBT_SOURCES
    "nbt/tags/abstract_tag.cpp"
    "nbt/tags/byte_array_tag.cpp"
    "nbt/tags/byte_tag.cpp"
    "nbt/tags/compound_tag.cpp"
    "nbt/tags/double_tag.cpp"
    "nbt/tags/end_tag.cpp"
    "nbt/tags/float_tag.cpp"
    "nbt/tags/int_array_tag.cpp"
    "nbt/tags/int_tag.cpp"
    "nbt/tags/list_tag.cpp"
    "nbt/tags/long_array_tag.cpp"
    "nbt/tags/long_tag.cpp"
    "nbt/tags/short_tag.cpp"
    "nbt/tags/string_tag.cpp"
    "nbt/nbt_read.cpp"
    "nbt/nbt_print.cpp"
 )

# util
set(UTIL_SOURCES
    "util/byte_stream.cpp"
    "util/compression.cpp"
    "util/conversion.cpp"
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
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(AwesomeMC ${ZLIB_LIBRARIES})
set_property(TARGET AwesomeMC PROPERTY CXX_STANDARD 20)
set_target_properties(AwesomeMC PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})