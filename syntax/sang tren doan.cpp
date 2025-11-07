#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Simple sieve to find primes up to sqrt(R_max)
// If R up to 1e12, sieve up to 1e6
const int MAX_SQRT = 1000005;
vector<int> primes;
bool is_prime_small[MAX_SQRT];

void sieve(int limit) {
    fill(is_prime_small + 2, is_prime_small + limit + 1, true);
    for (int i = 2; i * i <= limit; ++i) {
        if (is_prime_small[i]) {
            for (int j = i * i; j <= limit; j += i)
                is_prime_small[j] = false;
        }
    }
    for (int i = 2; i <= limit; ++i) {
        if (is_prime_small[i]) {
            primes.push_back(i);
        }
    }
}

// Segmented sieve on interval [L, R]
void segmented_sieve(long long L, long long R) {
    // Step 1: Sieve small primes up to sqrt(R)
    int limit = sqrt(R);
    sieve(limit);

    // Step 2: Create marking array for [L, R]
    // is_prime[i] corresponds to number L + i
    int len = R - L + 1;
    vector<bool> is_prime(len, true);

    for (long long p : primes) {
    // Find the smallest multiple of p in [L, R]
    // start = max(p*p, ceil(L/p) * p)
        long long start = max((long long)p * p, (L + p - 1) / p * p);

    // Mark multiples of p in [L, R] starting from 'start'
        for (long long j = start; j <= R; j += p) {
            is_prime[j - L] = false;
        }
    }

    // Handle special case when L = 1
    if (L == 1) is_prime[0] = false;

    // Print or store results
    for (int i = 0; i < len; ++i) {
        if (is_prime[i]) {
            cout << (L + i) << "\n";
        }
    }
}

/*
=== USAGE GUIDE ===
Sample input:
1
990 1000

Sample output:
991
997

Notes:
- R can be up to 1e12 or 1e14 depending on constraints.
- Range size (R - L) should be <= 1e6 or 1e7 for memory limits.
*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    // If multiple test cases
    if (cin >> t) {
        while (t--) {
            long long L, R;
            cin >> L >> R;
            segmented_sieve(L, R);
            if (t > 0) cout << "\n"; // Blank line between test cases if needed
            
            // Reset primes if necessary for next test (usually not needed)
             primes.clear(); // Only if R changes drastically
        }
    }

    return 0;
}
