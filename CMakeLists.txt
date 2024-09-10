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
)

# Prevent Google Test from overriding the compiler/linker options in the parent project
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make GTest available
FetchContent_MakeAvailable(googletest)

# Create the test executable
add_executable(FactorialTest ${TEST_FILES})

# Link the test executable with the Factorial library and Google Test libraries
target_link_libraries(FactorialTest FactorialLib gtest gtest_main pthread)
