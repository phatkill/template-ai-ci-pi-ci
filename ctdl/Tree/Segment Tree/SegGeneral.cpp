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
template<typename T>
struct SegmentTree{
    int n;
    vector<T> node;
    SegmentTree(int sz): n(sz){
        node.resize(4 * n + 5, T{});
    }

    void build(vector<T> &a, int id, int l, int r){
        if (l == r){
            node[id] = a[l];
            return;
        }
        int mid = l + r >> 1;
        build(a, id * 2, l, mid);
        build(a, id * 2 + 1, mid + 1, r);
        node[id] = merge(node[id * 2], node[id * 2 + 1]);  
    }

    void update(int id, int l, int r, int i, T val){
        if (i > r || i < l) return;
        if (l == r){
            node[id] = val;
            return;
        }
        int mid = l + r >> 1;
        update(id * 2, l, mid, i, val);
        update(id * 2 + 1, mid + 1, r, i, val);
        node[id] = merge(node[id * 2], node[id * 2 + 1]);
    }

    T get(int id, int l, int r, int u, int v){
        if (r < u || l > v) return T{};
        if (l >= u && r <= v) return node[id];
        int mid = l + r >> 1;
        return merge(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
    }

    T merge(T a, T b){
        return a + b;
    }

    void update(int i, T val){
        update(1, 1, n, i, val);
    }

    T get(int l, int r){
        return get(1, 1, n, l, r);
    }
};
int main() {
    faster
    int n, m; cin >> n >> m;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    SegmentTree<ll> tree(n);
    tree.build(a, 1, 1, n);
    for (int i = 1; i <= m; ++i){
        int type; cin >> type;
        int u; ll v; cin >> u >> v;
        u++;
        if (type == 1)  tree.update(u, v);
        else cout << tree.get(u, v) << '\n';
    }
}
//tinh tong
//input
// 5 5
// 5 4 2 3 5
// 2 0 3
// 1 1 1
// 2 0 3
// 1 3 1
// 2 0 5
//output
// 11
// 8
// 14