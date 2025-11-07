/**
problem:
A rebellious thought defies heaven — countless schemes perish
Date: 2025/11/04, Time: 06:06:52
create by: Phat Of Bug
**/

#include <bits/stdc++.h>
using namespace std;
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define ll long long 

// Set MOD (modulo)
const ll MOD = 1e9 + 7;

/**
 * @brief 2x2 matrix structure for computing Fibonacci numbers
 *
 * Supports matrix multiplication and matrix exponentiation.
 */
struct Matrix {
    ll mat[2][2];

    // Constructor (defaults to the zero matrix)
    Matrix() {
        mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;
    }

    // Create identity matrix
    static Matrix identity() {
        Matrix res;
        res.mat[0][0] = res.mat[1][1] = 1;
        return res;
    }

    // Overload operator * (matrix multiplication)
    Matrix operator*(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    // Multiplication and addition are performed with modulo
                    result.mat[i][j] = (result.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
                }
            }
        }
        return result;
    }
};

/**
 * @brief Compute (base ^ exp) % MOD using Binary Exponentiation
 *
 * Applies to Matrix objects.
 */
Matrix power(Matrix base, ll exp) {
    Matrix res = Matrix::identity();

    while (exp > 0) {
        if (exp % 2 == 1) { // Equivalent to (exp & 1)
            res = res * base;
        }
        base = base * base;
        exp /= 2; // Equivalent to (exp >>= 1)
    }
    return res;
}

int main() {
    faster
    
    int m; // Number of queries
    cin >> m;

    for (int i = 0; i < m; ++i) {
        ll n;
        cin >> n;

        // Edge case: F(0) = 0
        if (n == 0) {
            cout << 0 << '\n';
            continue;
        }

        // Define base matrix T (base matrix)
        // T = [[1, 1],
        //      [1, 0]]
        Matrix T;
        T.mat[0][0] = 1; T.mat[0][1] = 1;
        T.mat[1][0] = 1; T.mat[1][1] = 0;

        // Formula:
        // [F(n+1), F(n)]^T = (T^n) * [F(1), F(0)]^T
        // [F(n+1), F(n)]^T = (T^n) * [1, 0]^T
        //
        // Let T^n = [[a, b],
        //            [c, d]]
        //
        // F(n+1) = a*1 + b*0 = a
        // F(n)   = c*1 + d*0 = c
        //
        // Thus F(n) is the element [1][0] of matrix T^n
        
        Matrix result = power(T, n);
        cout << result.mat[1][0] << '\n';
    }
    return 0;
}

// compute F(n) % (1e9 + 7)
// input
// 8
// 0
// 1
// 2
// 3
// 4
// 5
// 10
// 90
// output
// 0
// 1
// 1
// 2
// 3
// 5
// 55
// 288006732