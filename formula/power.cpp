#include <iostream>


long long power(long long base, int exp) {
    // Khoi tao ket qua la 1 (vi a^0 = 1)
    long long res = 1;

    // Chung ta xu ly khi so mu van con > 0
    while (exp > 0) {
        
        // Kiem tra bit cuoi cung cua 'exp' (co phai so le khong)
        // Neu exp la so le (exp % 2 == 1 hoac exp & 1)
        if (exp % 2 == 1) {
            // Nhan co so hien tai (a^1, a^4, a^8...) vao ket qua
            res = res * base;
        }

        // Binh phuong co so de chuan bi cho bit tiep theo
        // (a -> a^2 -> a^4 -> a^8 ...)
        base = base * base;

        // Dich bit so mu sang phai (tuong duong chia nguyen cho 2)
        // (13 -> 6 -> 3 -> 1 -> 0)
        exp = exp / 2; // Hoac: exp >>= 1;
    }

    return res;
}

// Ham main() de kiem tra
int main() {
    // Kiem tra: 2^10 = 1024
    std::cout << "2^10 = " << power(2, 10) << std::endl;

    // Kiem tra: 3^5 = 243
    // exp = 5 (101_2)
    // 1. exp=5 (le)  : res = 1 * 3 = 3   , base = 3 * 3 = 9   , exp = 2
    // 2. exp=2 (chan): res = 3           , base = 9 * 9 = 81  , exp = 1
    // 3. exp=1 (le)  : res = 3 * 81 = 243, base = 81 * 81 , exp = 0
    std::cout << "3^5 = " << power(3, 5) << std::endl;

    // Kiem tra: 5^0 = 1
    std::cout << "5^0 = " << power(5, 0) << std::endl;

    return 0;
}