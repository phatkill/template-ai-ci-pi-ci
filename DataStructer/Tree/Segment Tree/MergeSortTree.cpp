/**
problem:
Một niệm nghịch thiên — muôn kế diệt vong
Date: 2025/11/07, Time: 09:34:10
create by: Phat Of Bug
**/

#include <bits/stdc++.h>
using namespace std;
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define all(x) x.begin(), x.end()
template<typename T>
struct MergeSortTree{
    vector<vector<T>> node;
    int n;
    MergeSortTree(int sz): n(sz){
        node.resize(4 * n + 5);
    }

    void build(vector<T> &a, int id, int l, int r){
        if (l == r){
            node[id].pb(a[l]);
            return;
        }
        int mid = l + r >> 1;
        build(a, id * 2, l, mid);
        build(a, id * 2 + 1, mid + 1, r);
        std::merge(all(node[id * 2]), all(node[id * 2 + 1]), back_inserter(node[id]));
    }

    void build(vector<T> &a){ build(a, 1, 1, n);}

    T get(int id, int l, int r, int u, int v, T k){
        if (l > v || r < u) return T{};
        if ( u <= l && r <= v) return node[id].end() - upper_bound(all(node[id]), k); // greater || (less or equal: upper_bound(all(node[id])) - node[id].begin())
        int mid = l + r >> 1;
        return get(id * 2, l, mid, u, v, k) + get(id * 2 + 1, mid + 1, r, u, v, k);
    }

    T get(int l, int r, T k){
        if (l > r) return T{};
        return get(1, 1, n, l, r, k);
    }

    T merge(T a, T b){
        return a + b;
    }

};

#define ll long long
int main() {
    faster
    int n; cin >> n;
    vector<int> a(n + 1);
    ll cnt = 0;
    MergeSortTree<int> tree(n);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    tree.build(a);
    int q; cin >> q;
    for (int i = 1; i <= q; ++i){
        int l, r; int x; cin >> l >> r >> x;
        cout << tree.get(l, r, x) << '\n';
    }
}
// input
// 5
// 5 1 2 3 4
// 3
// 2 4 1
// 4 4 4
// 1 5 2 
// output
// 2
// 0
// 3
