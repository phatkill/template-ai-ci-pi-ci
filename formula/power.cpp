#include <iostream>


long long power(long long base, int exp) {
    // Initialize result as 1 (since a^0 = 1)
    long long res = 1;

    // Process while exponent > 0
    while (exp > 0) {
        
        // Check the last bit of 'exp' (odd?)
        // If exp is odd (exp % 2 == 1 or exp & 1)
        if (exp % 2 == 1) {
            // Multiply current base (a^1, a^2, a^4, a^8...) into result
            res = res * base;
        }

        // Square base for next bit
        // (a -> a^2 -> a^4 -> a^8 ...)
        base = base * base;

        // Shift exponent right (divide by 2)
        // (13 -> 6 -> 3 -> 1 -> 0)
        exp = exp / 2; // Or: exp >>= 1;
    }

    return res;
}

// Simple test harness
int main() {
    // Test: 2^10 = 1024
    std::cout << "2^10 = " << power(2, 10) << std::endl;

    // Test: 3^5 = 243
    // exp = 5 (101_2)
    // 1. exp=5 (odd) : res = 1 * 3 = 3   , base = 3 * 3 = 9   , exp = 2
    // 2. exp=2 (even): res = 3           , base = 9 * 9 = 81  , exp = 1
    // 3. exp=1 (odd) : res = 3 * 81 = 243, base = 81 * 81 , exp = 0
    std::cout << "3^5 = " << power(3, 5) << std::endl;

    // Test: 5^0 = 1
    std::cout << "5^0 = " << power(5, 0) << std::endl;

    return 0;
}