#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7; // Hoặc MOD = 1000000007

// Hàm tính lũy thừa modulo: a^b % MOD
long long power(long long a, long long b, long long mod) {
    long long result = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) result = (result * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return result;
}

// Hàm tính nghịch đảo modulo: a^(-1) % MOD = a^(MOD-2) % MOD (theo định lý Fermat)
long long modInverse(long long a, long long mod) {
    return power(a, mod - 2, mod);
}

// Hàm tính tổ hợp C(n, k) % MOD
long long combination(int n, int k) {
    // Trường hợp đặc biệt
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    
    // Tối ưu: C(n, k) = C(n, n-k)
    if (k > n - k) k = n - k;
    
    // Tính tử số: n * (n-1) * ... * (n-k+1) % MOD
    long long numerator = 1;
    for (int i = 0; i < k; i++) {
        numerator = (numerator * ((n - i) % MOD)) % MOD;
    }
    
    // Tính mẫu số: k! % MOD
    long long denominator = 1;
    for (int i = 1; i <= k; i++) {
        denominator = (denominator * i) % MOD;
    }
    
    // Kết quả: (tử số) * (nghịch đảo mẫu số) % MOD
    return (numerator * modInverse(denominator, MOD)) % MOD;
}

int main() {
    int n, k;
    cout << "Nhap n: ";
    cin >> n;
    cout << "Nhap k: ";
    cin >> k;
    
    // Tính và in kết quả C(n, k) % MOD
    cout << "C(" << n << ", " << k << ") % " << MOD << " = " << combination(n, k) << endl;
    
    return 0;
}
