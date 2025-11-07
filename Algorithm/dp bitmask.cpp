#include <bits/stdc++.h>
using namespace std;
const int MAXN = (1 << 15) + 1;

int n, k;
long long dp[MAXN][16];

//Lấy bit thứ k của số x
int getBit(int x, int k)
{
    return (x >> k) & 1;
}

int solve(int n, int k)
{
    for (int mask = 0; mask < (1 << n); mask++)
        for (int k = 0; k <= n; k++)
            dp[mask][k] = 0;

    //base case
    dp[0][0] = 1;

    for (int mask = 0; mask < (1 << n); mask++)
        for (int q = 1; q <= n; q++)
        {
            //check q nằm trong tập hợp (biểu diễn bằng mask)
            if (getBit(mask, q - 1)) continue;
            for (int p = 0; p <= n; p++)
            {
                //check chênh lệch của q và p
                if (p != 0 && abs(q - p) > k) continue;

                //thêm q vào tập hợp
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