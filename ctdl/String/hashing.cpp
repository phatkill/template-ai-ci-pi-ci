#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll; // Dùng long long để tránh tràn số khi nhân

const int MAXN = 100005; // Kích thước tối đa của chuỗi
const int BASE = 311;    // Cơ số (thường chọn số nguyên tố > 256)
const long long MOD = 1e9 + 7; // Số MOD đủ lớn (nguyên tố)

ll POW[MAXN];  // Mảng lưu lũy thừa của BASE
ll HASH[MAXN]; // HASH[i] lưu giá trị hash của prefix độ dài i (s[0...i-1])

// 1. Tiền xử lý lũy thừa (chỉ cần chạy 1 lần duy nhất đầu chương trình)
void precompute_powers() {
    POW[0] = 1;
    for (int i = 1; i < MAXN; i++)
        POW[i] = (POW[i - 1] * BASE) % MOD;
}

// 2. Xây dựng mảng hash cho chuỗi s
void build_hash(const string& s) {
    int n = s.length();
    HASH[0] = 0;
    for (int i = 0; i < n; i++) {
        // Công thức rolling hash: H[i+1] = (H[i] * BASE + s[i]) % MOD
        HASH[i+1] = (HASH[i] * BASE + s[i]) % MOD;
    }
}

// 3. Lấy hash của substring s[L...R] (inclusive, chỉ số bắt đầu từ 0)
// VD: s = "banana", get_hash(1, 3) trả về hash của "ana"
ll get_hash(int L, int R) {
    // Công thức: (HASH[R+1] - HASH[L] * BASE^(len)) % MOD
    ll res = (HASH[R+1] - HASH[L] * POW[R - L + 1]) % MOD;
    if (res < 0) res += MOD; // Đảm bảo kết quả luôn dương do phép trừ
    return res;
}

/*
=== HƯỚNG DẪN INPUT/OUTPUT ===

Bài toán ví dụ:
Cho một chuỗi S. Có Q truy vấn, mỗi truy vấn gồm 4 số L1, R1, L2, R2.
Kiểm tra xem chuỗi con s[L1...R1] có giống chuỗi con s[L2...R2] không.

Input mẫu:
banana
3
0 2 2 4
1 3 3 5
0 0 5 5

Giải thích Input:
- Chuỗi S: "banana" (các chỉ số: b=0, a=1, n=2, a=3, n=4, a=5)
- 3 truy vấn:
  + Truy vấn 1: So sánh s[0...2] ("ban") và s[2...4] ("nan") -> Khác nhau
  + Truy vấn 2: So sánh s[1...3] ("ana") và s[3...5] ("ana") -> Giống nhau
  + Truy vấn 3: So sánh s[0...0] ("b") và s[5...5] ("a") -> Khác nhau

Output mong đợi:
NO
YES
NO
*/

int main() {
    // Tối ưu I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute_powers(); // Bắt buộc phải gọi hàm này trước tiên

    string s;
    if (!(cin >> s)) return 0;
    
    build_hash(s); // Xây dựng hash cho chuỗi vừa nhập

    int q;
    cin >> q;
    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;

        // Lấy hash của 2 đoạn và so sánh
        // Chỉ mất O(1) cho mỗi lần gọi get_hash
        if (get_hash(l1, r1) == get_hash(l2, r2)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
