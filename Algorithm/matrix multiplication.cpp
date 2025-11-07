/**
problem:
Một niệm nghịch thiên — muôn kế diệt vong
Date: 2025/11/04, Time: 06:06:52
create by: Phat Of Bug
**/

#include <bits/stdc++.h>
using namespace std;
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define ll long long 

// Đặt MOD (modulo)
const ll MOD = 1e9 + 7;

/**
 * @brief Cấu trúc ma trận 2x2 để tính Fibo
 *
 * Hỗ trợ phép nhân ma trận và tính lũy thừa ma trận.
 */
struct Matrix {
    ll mat[2][2];

    // Hàm khởi tạo (mặc định là ma trận 0)
    Matrix() {
        mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;
    }

    // Hàm tạo ma trận đơn vị (identity matrix)
    static Matrix identity() {
        Matrix res;
        res.mat[0][0] = res.mat[1][1] = 1;
        return res;
    }

    // Nạp chồng toán tử * (nhân ma trận)
    Matrix operator*(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    // Phép nhân và cộng được thực hiện với modulo
                    result.mat[i][j] = (result.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
                }
            }
        }
        return result;
    }
};

/**
 * @brief Tính (base ^ exp) % MOD bằng Lũy thừa nhị phân (Binary Exponentiation)
 *
 * Áp dụng cho đối tượng Matrix.
 */
Matrix power(Matrix base, ll exp) {
    Matrix res = Matrix::identity();

    while (exp > 0) {
        if (exp % 2 == 1) { // Tương đương (exp & 1)
            res = res * base;
        }
        base = base * base;
        exp /= 2; // Tương đương (exp >>= 1)
    }
    return res;
}

int main() {
    faster
    
    int m; // Số lượng truy vấn
    cin >> m;

    for (int i = 0; i < m; ++i) {
        ll n;
        cin >> n;

        // Trường hợp đặc biệt: F(0) = 0
        if (n == 0) {
            cout << 0 << '\n';
            continue;
        }

        // Định nghĩa ma trận cơ sở T (base matrix)
        // T = [[1, 1],
        //      [1, 0]]
        Matrix T;
        T.mat[0][0] = 1; T.mat[0][1] = 1;
        T.mat[1][0] = 1; T.mat[1][1] = 0;

        // Công thức:
        // [F(n+1), F(n)]^T = (T^n) * [F(1), F(0)]^T
        // [F(n+1), F(n)]^T = (T^n) * [1, 0]^T
        //
        // Gọi T^n = [[a, b],
        //            [c, d]]
        //
        // F(n+1) = a*1 + b*0 = a
        // F(n)   = c*1 + d*0 = c
        //
        // Vậy F(n) là phần tử [1][0] của ma trận T^n
        
        Matrix result = power(T, n);
        cout << result.mat[1][0] << '\n';
    }
    return 0;
}

//tinh F(n) % (1e9 + 7)
//input
// 8
// 0
// 1
// 2
// 3
// 4
// 5
// 10
// 90
//output
// 0
// 1
// 1
// 2
// 3
// 5
// 55
// 288006732