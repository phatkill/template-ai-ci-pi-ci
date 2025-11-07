#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Sàng thường để tìm nguyên tố đến sqrt(R_max)
// Giả sử R tối đa 10^12 thì cần sàng đến 10^6
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

// Hàm sàng trên đoạn [L, R]
void segmented_sieve(long long L, long long R) {
    // B1: Sàng các nguyên tố nhỏ đến sqrt(R)
    int limit = sqrt(R);
    sieve(limit);

    // B2: Tạo mảng đánh dấu cho đoạn [L, R]
    // is_prime[i] tương ứng với số L + i
    int len = R - L + 1;
    vector<bool> is_prime(len, true);

    for (long long p : primes) {
        // Tìm số nhỏ nhất trong đoạn [L, R] chia hết cho p
        // Công thức: max(p*p, (L + p - 1) / p * p)
        long long start = max((long long)p * p, (L + p - 1) / p * p);

        // Đánh dấu các bội của p trong đoạn [L, R] bắt đầu từ 'start'
        for (long long j = start; j <= R; j += p) {
            is_prime[j - L] = false;
        }
    }

    // Xử lý riêng trường hợp số 1 nếu L = 1
    if (L == 1) is_prime[0] = false;

    // In kết quả hoặc lưu trữ
    for (int i = 0; i < len; ++i) {
        if (is_prime[i]) {
            cout << (L + i) << "\n";
        }
    }
}

/*
=== HƯỚNG DẪN SỬ DỤNG ===
Input mẫu:
1
990 1000

Output mẫu:
991
997

Lưu ý:
- R có thể lên tới 10^12 hoặc 10^14 tùy giới hạn thời gian.
- Hiệu (R - L) thường phải <= 10^6 hoặc 10^7 để mảng is_prime đủ bộ nhớ.
*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    // Nếu đề bài có nhiều test case
    if (cin >> t) {
        while (t--) {
            long long L, R;
            cin >> L >> R;
            segmented_sieve(L, R);
            if (t > 0) cout << "\n"; // In dòng trống giữa các test case nếu cần
            
            // Reset lại primes nếu cần thiết cho test case sau (thường không cần vì sqrt(R) giống nhau)
             primes.clear(); // Chỉ cần nếu R thay đổi quá lớn giữa các test case
        }
    }

    return 0;
}
