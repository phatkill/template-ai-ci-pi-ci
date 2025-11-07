#include <bits/stdc++.h>
using namespace std;

template<typename T> using pqmax = priority_queue<T>;
template<typename T> using pqmin = priority_queue<T, vector<T>, greater<T>>;

int main() {
    pqmax<int> mx;          // max-heap (default)
    pqmin<int> mn;          // min-heap

    // Push elements
    mx.push(10); mx.push(7);
    mn.push(10); mn.push(7);
    // Access top element
    cout << mx.top() << "\n"; // 10
    cout << mn.top() << "\n"; // 7

    // Pop
    mx.pop();
    mn.pop();


    return 0;
}
