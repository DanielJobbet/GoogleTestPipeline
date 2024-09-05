#include "Factorial.h"
#include <stdexcept>

// Computes the factorial of a number n
int Factorial::compute(int n) {
    if (n < 0) {
        throw std::invalid_argument("Negative numbers do not have a factorial");
    }

    int result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}
