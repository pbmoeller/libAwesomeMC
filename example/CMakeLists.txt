# ZLIB
find_package(ZLIB REQUIRED)

### Example 2
add_executable(example_nbt "example_nbt.cpp")
target_include_directories(example_nbt
    PRIVATE ${ZLIB_INCLUDE_DIRS}
    PRIVATE ${AwesomeMC_SOURCE_DIR}/include
)
target_link_libraries(example_nbt AwesomeMC)
set_target_properties(example_nbt PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_compile_options(example_nbt PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
          -std=c++20 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Woverloaded-virtual -Wpedantic>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)

### Example 3
add_executable(example_anvil "example_anvil.cpp")
target_include_directories(example_anvil
    PRIVATE ${ZLIB_INCLUDE_DIRS}
    PRIVATE ${AwesomeMC_SOURCE_DIR}/include
)
target_link_libraries(example_anvil AwesomeMC)
set_target_properties(example_anvil PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_compile_options(example_anvil PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
          -std=c++20 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Woverloaded-virtual -Wpedantic>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)

### Example 4
add_executable(load_testmap "load_testmap.cpp")
target_include_directories(load_testmap
    PRIVATE ${ZLIB_INCLUDE_DIRS}
    PRIVATE ${AwesomeMC_SOURCE_DIR}/include
)
target_link_libraries(load_testmap AwesomeMC)
set_target_properties(load_testmap PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_compile_options(load_testmap PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
          -std=c++20 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Woverloaded-virtual -Wpedantic -Wno-psabi>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)