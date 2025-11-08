#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Build prefix array (pi function) for pattern P
// pi[i] is the length of the longest prefix of P[0...i] that is also a suffix of P[0...i]
vector<int> compute_prefix_function(const string& P) {
    int m = P.length();
    vector<int> pi(m);
    pi[0] = 0; // First element always 0
    int k = 0; // current matched prefix length
    for (int q = 1; q < m; q++) {
        // If mismatch, fallback using previous pi value
        while (k > 0 && P[k] != P[q])
            k = pi[k - 1];
        // If match, extend matched prefix
        if (P[k] == P[q])
            k++;
        pi[q] = k; // Store pi at position q
    }
    return pi;
}

// KMP search: find all occurrences of P in T
void KMP_search(const string& T, const string& P) {
    int n = T.length();
    int m = P.length();
    if (m == 0) return; // Empty pattern

    // Step 1: compute pi array for P
    vector<int> pi = compute_prefix_function(P);

    int q = 0; // number of matched characters
    for (int i = 0; i < n; i++) {
        // Like building pi: on mismatch, fallback q
        while (q > 0 && P[q] != T[i])
            q = pi[q - 1];
        // If next character matches
        if (P[q] == T[i])
            q++;
        // If whole pattern matched (q == m)
        if (q == m) {
            // Found P ending at i.
            // Start index = i - m + 1 (0-based)
            cout << "Tim thay mau tai vi tri: " << i - m + 1 << "\n";
            
            // Prepare for next search: fallback
            q = pi[q - 1];
        }
    }
}

/*
=== INPUT/OUTPUT GUIDE ===

Task: Find all occurrences of pattern P in text T.

Sample input:
ababcabcabababd
ababd

Explanation:
- Line 1: Text T = "ababcabcabababd"
- Line 2: Pattern P = "ababd"

Expected output:
Tim thay mau tai vi tri: 10

Explanation:
- The pattern "ababd" appears once in T, starting at index 10.
    T: a b a b c a b c a b [a b a b d]
         0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
*/

int main() {
    // Tối ưu I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string T, P;
    // Đọc chuỗi T và P (có thể dùng getline nếu chuỗi có khoảng trắng)
    if (!(cin >> T >> P)) return 0;

    KMP_search(T, P);

    return 0;
}
