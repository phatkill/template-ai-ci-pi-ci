#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Hàm xây dựng mảng prefix (pi function) cho chuỗi mẫu P
// pi[i] là độ dài tiền tố dài nhất của P[0...i] cũng là hậu tố của P[0...i]
vector<int> compute_prefix_function(const string& P) {
    int m = P.length();
    vector<int> pi(m);
    pi[0] = 0; // Phần tử đầu tiên luôn có pi = 0
    int k = 0; // k là độ dài tiền tố khớp hiện tại
    for (int q = 1; q < m; q++) {
        // Nếu ký tự không khớp, quay lui k dựa trên giá trị pi trước đó
        while (k > 0 && P[k] != P[q])
            k = pi[k - 1];
        // Nếu khớp, tăng độ dài tiền tố khớp lên 1
        if (P[k] == P[q])
            k++;
        pi[q] = k; // Lưu giá trị pi tại vị trí q
    }
    return pi;
}

// Hàm tìm kiếm KMP: tìm tất cả vị trí xuất hiện của P trong T
void KMP_search(const string& T, const string& P) {
    int n = T.length();
    int m = P.length();
    if (m == 0) return; // Trường hợp chuỗi mẫu rỗng

    // B1: Tính mảng pi cho chuỗi mẫu P
    vector<int> pi = compute_prefix_function(P);

    int q = 0; // q là số ký tự đã khớp
    for (int i = 0; i < n; i++) {
        // Tương tự như xây dựng pi: nếu không khớp, quay lui q
        while (q > 0 && P[q] != T[i])
            q = pi[q - 1];
        // Nếu khớp ký tự tiếp theo
        if (P[q] == T[i])
            q++;
        // Nếu đã khớp toàn bộ chuỗi P (q == m)
        if (q == m) {
            // Tìm thấy P tại vị trí kết thúc là i.
            // Vị trí bắt đầu là i - m + 1 (0-based index)
            cout << "Tim thay mau tai vi tri: " << i - m + 1 << "\n";
            
            // Chuẩn bị cho lần tìm kiếm tiếp theo: coi như vừa khớp sai để quay lui
            q = pi[q - 1];
        }
    }
}

/*
=== HƯỚNG DẪN INPUT/OUTPUT ===

Bài toán: Tìm tất cả vị trí xuất hiện của mẫu P trong văn bản T.

Input mẫu:
ababcabcabababd
ababd

Giải thích Input:
- Dòng 1: Chuỗi văn bản T = "ababcabcabababd"
- Dòng 2: Chuỗi mẫu P = "ababd"

Output mong đợi:
Tim thay mau tai vi tri: 10

Giải thích:
- Chuỗi "ababd" chỉ xuất hiện 1 lần trong T, bắt đầu từ chỉ số 10.
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
