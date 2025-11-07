#include <bits/stdc++.h>
using namespace std;
const int MAXN = (1 << 15) + 1;

int n, k;
long long dp[MAXN][16];

// Get the k-th bit of number x
int getBit(int x, int k)
{
    return (x >> k) & 1;
}

int solve(int n, int k)
{
    for (int mask = 0; mask < (1 << n); mask++)
        for (int k = 0; k <= n; k++)
            dp[mask][k] = 0;

    // Base case
    dp[0][0] = 1;

    for (int mask = 0; mask < (1 << n); mask++)
        for (int q = 1; q <= n; q++)
        {
            // Check if q is already in the set (represented by mask)
            if (getBit(mask, q - 1)) continue;
            for (int p = 0; p <= n; p++)
            {
                // Check difference constraint between q and p
                if (p != 0 && abs(q - p) > k) continue;

                // Add q into the set
                int newMask = mask | (1 << (q - 1));

                dp[newMask][q] += dp[mask][p];
            }
        }

    long long res = 0;
    int fullMask = (1 << n) - 1;
    for (int k = 1; k <= n; k++)
        res += dp[fullMask][k];
    return res;
}