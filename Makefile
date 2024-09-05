# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -I./include -isystem /usr/src/gtest/include -pthread

# Directories
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Source files
SRC_FILES = $(SRC_DIR)/Factorial.cpp
TEST_FILES = $(TEST_DIR)/main.cpp $(TEST_DIR)/FactorialTest.cpp

# Output binary
TARGET = $(BUILD_DIR)/FactorialTest

# Libraries
LIBS = -L/usr/src/gtest/lib -lgtest -lgtest_main

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build the test executable
$(TARGET): $(BUILD_DIR) $(SRC_FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) $(TEST_FILES) -o $(TARGET) $(LIBS)

# Run the tests
test: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -rf $(BUILD_DIR)/*
