#include <iostream>
#include <string>
#include <algorithm> // Required for next_permutation and sort
// Sử dụng namespace std để code ngắn gọn hơn
using namespace std;
int main() {
    string s = "BAC"; // Start with an unsorted string
    // 1. Sort the string (important!)
    // Ensures you start from the smallest permutation ("ABC")
    sort(s.begin(), s.end());
    cout << "Cac hoan vi cua \"" << s << "\":\n";
    // 2. Iterate through all permutations
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