# ZLIB
find_package(ZLIB REQUIRED)

set(AWESOMEMC_HEADER_PATH "${AwesomeMC_SOURCE_DIR}/include/AwesomeMC")

### Includes
# anvil
set(ANVIL_INCLUDES
    "${AWESOMEMC_HEADER_PATH}/anvil/anvil_read.hpp"
    "${AWESOMEMC_HEADER_PATH}/anvil/block.hpp"
    "${AWESOMEMC_HEADER_PATH}/anvil/chunk.hpp"
    "${AWESOMEMC_HEADER_PATH}/anvil/chunk_info.hpp"
    "${AWESOMEMC_HEADER_PATH}/anvil/heightmap.hpp"
    "${AWESOMEMC_HEADER_PATH}/anvil/region.hpp"
    "${AWESOMEMC_HEADER_PATH}/anvil/region_header.hpp"
)

# nbt
set(NBT_INCLUDES
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/abstract_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/abstract_vector_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/array_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/byte_array_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/byte_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/compound_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/double_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/end_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/float_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/int_array_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/int_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/list_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/long_array_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/long_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/short_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/string_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/tags.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/tags/value_tag.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/nbt_print.hpp"
    "${AWESOMEMC_HEADER_PATH}/nbt/nbt_read.hpp"
)

# util
set(UTIL_INCLUDES
    "${AWESOMEMC_HEADER_PATH}/util/bit.hpp"
    "${AWESOMEMC_HEADER_PATH}/util/byte_stream.hpp"
    "${AWESOMEMC_HEADER_PATH}/util/byte_swap.hpp"
    "${AWESOMEMC_HEADER_PATH}/util/compression.hpp"
    "${AWESOMEMC_HEADER_PATH}/util/conversion.hpp"
    "${AWESOMEMC_HEADER_PATH}/util/floating_point.hpp"
    "${AWESOMEMC_HEADER_PATH}/util/indent.hpp"
    "${AWESOMEMC_HEADER_PATH}/util/traits.hpp"
)

set(AWESOMEMC_INCLUDES
    ${ANVIL_INCLUDES}
    ${NBT_INCLUDES}
    ${UTIL_INCLUDES}
    "${AWESOMEMC_HEADER_PATH}/constants.hpp"
    "${AWESOMEMC_HEADER_PATH}/version.hpp"
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
    PRIVATE ${AwesomeMC_SOURCE_DIR}/include
)
target_link_libraries(AwesomeMC ${ZLIB_LIBRARIES})
set_target_properties(AwesomeMC PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_compile_options(AwesomeMC PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
          -std=c++20 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Woverloaded-virtual -Wpedantic -Wno-psabi>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)
