cmake_minimum_required(VERSION 3.14)
project(FactorialProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Source files
set(SOURCE_FILES
    src/Factorial.cpp
)

# Test files
set(TEST_FILES
    tests/main.cpp
    tests/FactorialTest.cpp
)

# Create the library for Factorial
add_library(FactorialLib ${SOURCE_FILES})

# FetchContent module is available in CMake 3.11+
include(FetchContent)

# Download and configure Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# Prevent Google Test from overriding the compiler/linker options in the parent project
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make GTest available
FetchContent_MakeAvailable(googletest)

# Create the test executable
add_executable(FactorialTest ${TEST_FILES})

# Link the test executable with the Factorial library and Google Test libraries
target_link_libraries(FactorialTest FactorialLib gtest gtest_main pthread)

# Enable testing
enable_testing()

include(GoogleTest)
gtest_discover_tests(FactorialTest)

# Code coverage options
option(COVERAGE "Enable coverage reporting" ON)
if(COVERAGE)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(FATAL_ERROR "Coverage requires GCC or Clang")
    endif()

    message(STATUS "Building with code coverage enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
endif()

# Add a target to generate coverage information using gcovr!
if(COVERAGE)
    find_program(GCOVR_EXECUTABLE gcovr)

    if(GCOVR_EXECUTABLE)
        add_custom_target(coveragecmake
            COMMAND ${GCOVR_EXECUTABLE} -r .. -exclude 'build.*' --html --html-details -o coverage_report.html
            COMMAND ${CMAKE_COMMAND} -E echo "Coverage report generated in coverage_report.html"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS FactorialTest
        )
    else()
        message(WARNING "gcovr not found! Coverage target not available.")
    endif()
endif()

