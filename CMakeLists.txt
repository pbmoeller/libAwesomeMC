cmake_minimum_required(VERSION 3.15)

project(AwesomeMC
    VERSION 0.2.2
    LANGUAGES C CXX
)

include(CMakePackageConfigHelpers)

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
    ${PROJECT_BINARY_DIR}/AwesomeMC/version.hpp
)

write_basic_package_version_file("${PROJECT_BINARY_DIR}/AwesomeMC-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

### Installation directories
set(AwesomeMC_INSTALL_BINARY_DIR "bin")
set(AwesomeMC_INSTALL_INCLUDE_DIR "include")
set(AwesomeMC_INSTALL_LIBRARY_DIR "lib/${CMAKE_BUILD_TYPE}")
set(AwesomeMC_INSTALL_CMAKE_CONFIG_DIR "share/AwesomeMC/cmake")
set(AwesomeMC_INSTALL_ADDITIONAL_FILES_DIR "share/AwesomeMC")

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

### Install
install(FILES "AwesomeMC-config.cmake" "${PROJECT_BINARY_DIR}/AwesomeMC-config-version.cmake" DESTINATION ${AwesomeMC_INSTALL_CMAKE_CONFIG_DIR})
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" "${CMAKE_CURRENT_SOURCE_DIR}/readme.md" DESTINATION ${AwesomeMC_INSTALL_ADDITIONAL_FILES_DIR})
install(EXPORT AwesomeMC DESTINATION ${AwesomeMC_INSTALL_CMAKE_CONFIG_DIR})