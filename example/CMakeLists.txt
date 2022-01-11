# ZLIB
find_package(ZLIB REQUIRED)

### Example 1
add_executable(example1 "example1.cpp")
target_include_directories(example1
    PRIVATE ${ZLIB_INCLUDE_DIRS}
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(example1 AwesomeMC)
set_target_properties(example1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

### Example 2
add_executable(example_nbt "example_nbt.cpp")
target_include_directories(example_nbt
    PRIVATE ${ZLIB_INCLUDE_DIRS}
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(example_nbt AwesomeMC)
set_target_properties(example_nbt PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

### Example 3
add_executable(example_anvil "example_anvil.cpp")
target_include_directories(example_anvil
    PRIVATE ${ZLIB_INCLUDE_DIRS}
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(example_anvil AwesomeMC)
set_target_properties(example_anvil PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

### Example 4
add_executable(load_testmap "load_testmap.cpp")
target_include_directories(load_testmap
    PRIVATE ${ZLIB_INCLUDE_DIRS}
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(load_testmap AwesomeMC)
set_target_properties(load_testmap PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})