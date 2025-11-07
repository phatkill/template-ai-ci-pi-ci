#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll; // Use long long to avoid overflow when multiplying

const int MAXN = 100005; // Maximum string length
const int BASE = 311;    // Base (choose a prime > 256 typically)
const long long MOD = 1e9 + 7; // Large prime MOD

ll POW[MAXN];  // POW[i] stores BASE^i % MOD
ll HASH[MAXN]; // HASH[i] stores hash of prefix length i (s[0...i-1])

// 1. Precompute powers (call once at start)
void precompute_powers() {
    POW[0] = 1;
    for (int i = 1; i < MAXN; i++)
        POW[i] = (POW[i - 1] * BASE) % MOD;
}

// 2. Build hash array for string s
void build_hash(const string& s) {
    int n = s.length();
    HASH[0] = 0;
    for (int i = 0; i < n; i++) {
        // Rolling hash formula: H[i+1] = (H[i] * BASE + s[i]) % MOD
        HASH[i+1] = (HASH[i] * BASE + s[i]) % MOD;
    }
}

// 3. Get hash of substring s[L...R] (inclusive, 0-based)
// Example: s = "banana", get_hash(1, 3) returns hash of "ana"
ll get_hash(int L, int R) {
    // Formula: (HASH[R+1] - HASH[L] * BASE^(len)) % MOD
    ll res = (HASH[R+1] - HASH[L] * POW[R - L + 1]) % MOD;
    if (res < 0) res += MOD; // Ensure positive due to subtraction
    return res;
}

/*
=== INPUT/OUTPUT GUIDE ===

Example problem:
Given a string S. There are Q queries, each query consists of L1, R1, L2, R2.
Check if substring s[L1...R1] equals s[L2...R2].

Sample input:
banana
3
0 2 2 4
1 3 3 5
0 0 5 5

Explanation:
- S = "banana" (indices: b=0, a=1, n=2, a=3, n=4, a=5)
- 3 queries:
    + Query 1: compare s[0...2] ("ban") vs s[2...4] ("nan") -> Different
    + Query 2: compare s[1...3] ("ana") vs s[3...5] ("ana") -> Same
    + Query 3: compare s[0...0] ("b") vs s[5...5] ("a") -> Different

Expected output:
NO
YES
NO
*/

int main() {
    // Tối ưu I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute_powers(); // Must be called first

    string s;
    if (!(cin >> s)) return 0;
    
    build_hash(s); // Build hash for input string

    int q;
    cin >> q;
    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;

    // Get hash of two substrings and compare
    // O(1) per get_hash call
        if (get_hash(l1, r1) == get_hash(l2, r2)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
