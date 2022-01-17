enable_testing()
find_package(GTest REQUIRED)

add_executable(tests 
    "test_main.cpp" 
    "types_test.cpp"
    "nbt/tags/abstract_tag_test.cpp"
    "nbt/tags/byte_tag_test.cpp"
    "nbt/tags/end_tag_test.cpp"
    "nbt/tags/short_tag_test.cpp"
    "nbt/tags/long_tag_test.cpp"
    "nbt/tags/int_tag_test.cpp"
    "nbt/tags/float_tag_test.cpp" 
    "nbt/tags/double_tag_test.cpp"
    "nbt/tags/byte_array_tag_test.cpp"
    "nbt/tags/string_tag_test.cpp"
    "nbt/tags/list_tag_test.cpp"
    "nbt/tags/int_array_tag_test.cpp"
    "nbt/tags/long_array_tag_test.cpp"
    "nbt/tags/compound_tag_test.cpp"
    "nbt/nbt_read_test.cpp"
    "anvil/region_test.cpp"
    "anvil/region_header_test.cpp"
    "anvil/chunk_info_test.cpp"
    "anvil/chunk_test.cpp"
    "anvil/heightmap_test.cpp"
    "util/byte_swap_test.cpp"
    "util/byte_stream_test.cpp"
    "anvil/block_test.cpp"
    "util/conversion_test.cpp"
    "util/bit_test.cpp"
)
target_link_libraries(tests AwesomeMC ${GTEST_LIBRARIES})

if(UNIX)
    target_link_libraries(tests pthread)
endif()

target_include_directories(tests
    PRIVATE ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/test
    PRIVATE ${GTEST_INCLUDE_DIRS}
    PRIVATE ${GMOCK_INCLUDE_DIRS}
)

set_target_properties(tests 
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)
target_compile_options(tests PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
          -std=c++20 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Woverloaded-virtual -Wpedantic -Wno-psabi>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)