cmake_minimum_required(VERSION 3.10)
project(FactorialProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

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

# Find Google Test package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Create the test executable
add_executable(FactorialTest ${TEST_FILES})

# Link the test executable with the Factorial library and Google Test libraries
target_link_libraries(FactorialTest FactorialLib ${GTEST_LIBRARIES} pthread)
