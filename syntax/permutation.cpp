#include <iostream>
#include <string>
#include <algorithm> // Bắt buộc cho next_permutation và sort
// Sử dụng namespace std để code ngắn gọn hơn
using namespace std;
int main() {
    string s = "BAC"; // Bắt đầu với chuỗi chưa sắp xếp
    // 1. Sắp xếp chuỗi (quan trọng!)
    // Điều này đảm bảo bạn bắt đầu từ hoán vị nhỏ nhất ("ABC")
    sort(s.begin(), s.end());
    cout << "Cac hoan vi cua \"" << s << "\":\n";
    // 2. Lặp qua tất cả các hoán vị
    do {
        cout << s << "\n";
    } while (next_permutation(s.begin(), s.end()));
    /*
    Output:
    ABC
    ACB
    BAC
    BCA
    CAB
    CBA
    */
}