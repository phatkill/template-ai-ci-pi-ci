/**
problem:
A rebellious thought defies heaven — countless schemes perish
Date: 2025/11/07, Time: 15:20:06
create by: Phat Of Bug
**/

#include <bits/stdc++.h>
using namespace std;
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define ll long long
template <typename T>
struct Seg{
    int n;
    vector<T> node, lazy;
    Seg(int sz): n(sz){
        node.resize(4 * n + 5, T{});
        lazy.resize(4 * n + 5, T{});
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

    void build(vector<T> &a) {build(a, 1, 1, n);}

    void apply(int id, int l, int r, T val){
        node[id] += val * (r - l + 1);
        lazy[id] += val;
    }

    void push(int id, int l, int r){
        if (lazy[id] == T{} || (l == r)) return;
        int mid = l + r >> 1;
        apply(id * 2, l, mid, lazy[id]);
        apply(id * 2 + 1, mid + 1, r, lazy[id]);
        lazy[id] = T{};
    }

    void update(int id, int l, int r, int u, int v, T val){
        if (l > v || r < u) return;
        if (u <= l && r <= v){
            apply(id, l, r, val);
            return;
        }
        push(id, l, r);
        int mid = l + r >> 1;
        update(id * 2, l, mid, u, v, val);
        update(id * 2 + 1, mid + 1, r, u, v, val);
        node[id] = merge(node[id * 2], node[id * 2 + 1]);
    }

    void update(int l, int r, T val){update(1, 1, n, l, r, val);}

    T get(int id, int l, int r, int u, int v){
        if (l > v || r < u) return T{};
        if (u <= l && r <= v) return node[id];
        push(id, l, r);
        int mid = l + r >> 1;
        return merge(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
    }

    T get(int l, int r){return get(1, 1, n, l, r);}

    T merge(T a, T b) {return a + b;} // Change if using min/max/etc.
};
int main() {
    faster
    int n, q; cin >> n >> q;
    Seg<ll> tree(n);
    for (int i = 1; i <= q; ++i){
        int type, l, r; cin >> type >> l >> r; l++;
        if (type & 1) {ll val; cin >> val; tree.update(l, r, val);}
        else cout << tree.get(l, r) << '\n';
    }    
}
// input
// 5 6
// 1 0 3 3
// 2 1 2
// 1 1 4 4
// 2 1 3
// 2 1 4
// 2 3 5
// output
// 3
// 14
// 18
// 4

