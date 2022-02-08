cmake_minimum_required(VERSION 3.15)

project(AwesomeMC
    VERSION 0.1.0
    LANGUAGES C CXX
)

### Options
option(BUILD_TESTS "Build unit tests for AwesomeMC" TRUE)
option(BUILD_EXAMPLES "Build example programs for AwesomeMC" TRUE)

### Additional flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/version.hpp.in
    ${CMAKE_CURRENT_SOURCE_DIR}/include/AwesomeMC/version.hpp
)

### Installation directories
set(AwesomeMC_INSTALL_BINARY_DIR "bin")
set(AwesomeMC_INSTALL_INCLUDE_DIR "include")
set(AwesomeMC_INSTALL_LIBRARY_DIR "lib/${CMAKE_BUILD_TYPE}")

### AwesomeMC library
add_subdirectory(src)

### Build examples
if(BUILD_EXAMPLES)
    add_subdirectory(example)
endif()

### Build Unit Tests
if(BUILD_TESTS)
    add_subdirectory(test)
endif()