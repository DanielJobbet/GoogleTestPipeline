#include <gtest/gtest.h>
#include "Factorial.h"

// Define a test fixture class
class FactorialTest : public ::testing::Test {
protected:
    Factorial factorial;

    // SetUp and TearDown are not needed in this simple case, but could be used
};

// Test case for factorial of 0 (0! = 1)
TEST_F(FactorialTest, FactorialOfZero) {
    EXPECT_EQ(factorial.compute(0), 1);
}

// Test case for factorial of a small positive number
TEST_F(FactorialTest, FactorialOfSmallNumber) {
    EXPECT_EQ(factorial.compute(5), 120);  // 5! = 120
}

// Test case for factorial of 1 (1! = 1)
TEST_F(FactorialTest, FactorialOfOne) {
    EXPECT_EQ(factorial.compute(1), 1);
}

// Test case for factorial of a larger positive number
TEST_F(FactorialTest, FactorialOfLargerNumber) {
    EXPECT_EQ(factorial.compute(10), 3628800);  // 10! = 3628800
}

// Test case for handling negative input (should throw an exception)
TEST_F(FactorialTest, FactorialOfNegativeNumber) {
    EXPECT_THROW(factorial.compute(-5), std::invalid_argument);
}
