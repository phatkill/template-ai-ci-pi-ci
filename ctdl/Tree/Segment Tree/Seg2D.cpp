/**
problem:
A rebellious thought defies heaven — countless schemes perish
Date: 2025/11/04, Time: 06:06:52
create by: Phat Of Bug
**/

#include <bits/stdc++.h>
using namespace std;
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define ll long long 

template<typename T>
struct SegmentTree2D {
    int h, w; // Height and width of the array
    vector<vector<T>> node; // 2D segment tree: node[id_x][id_y]

    // Initialize with size h x w
    SegmentTree2D(int height, int width) : h(height), w(width) {
        node.resize(4 * h + 5);
        for (int i = 0; i < 4 * h + 5; ++i) {
            node[i].resize(4 * w + 5, T{}); // Default neutral value (e.g. 0 for sum)
        }
    }

    // Merge two values; change for other problems (min, max, ...)
    T merge(T a, T b) {
        return a + b;
    }

    // --- BUILD FUNCTIONS ---

    // Build 1D tree over y-axis for node id_x (manages segment [l_x, r_x])
    void build_y(int id_x, int l_x, int r_x, int id_y, int l_y, int r_y, const vector<vector<T>>& a) {
        if (l_y == r_y) {
            if (l_x == r_x) {
                // Leaf in both axes: take value from base array
                node[id_x][id_y] = a[l_x][l_y];
            } else {
                // Leaf in y but internal in x: merge children in x
                node[id_x][id_y] = merge(node[id_x * 2][id_y], node[id_x * 2 + 1][id_y]);
            }
            return;
        }

        int mid_y = (l_y + r_y) >> 1;
        build_y(id_x, l_x, r_x, id_y * 2, l_y, mid_y, a);
        build_y(id_x, l_x, r_x, id_y * 2 + 1, mid_y + 1, r_y, a);
        // Merge children along y
        node[id_x][id_y] = merge(node[id_x][id_y * 2], node[id_x][id_y * 2 + 1]);
    }

    // Build 2D tree along x-axis (segment [l_x, r_x])
    void build_x(int id_x, int l_x, int r_x, const vector<vector<T>>& a) {
        if (l_x != r_x) {
            int mid_x = (l_x + r_x) >> 1;
            build_x(id_x * 2, l_x, mid_x, a);
            build_x(id_x * 2 + 1, mid_x + 1, r_x, a);
        }
        // After x-children built, build y-tree for current id_x
        build_y(id_x, l_x, r_x, 1, 1, w, a);
    }

    // Public build from 1-based 2D array
    void build(const vector<vector<T>>& a) {
        build_x(1, 1, h, a);
    }

    // --- POINT UPDATE FUNCTIONS ---

    // Update 1D y-tree at node id_x
    void update_y(int id_x, int l_x, int r_x, int id_y, int l_y, int r_y, int x, int y, T val) {
        if (l_y == r_y) {
            if (l_x == r_x) {
                // Leaf in both axes: assign new value
                node[id_x][id_y] = val;
            } else {
                // Update internal node along x
                node[id_x][id_y] = merge(node[id_x * 2][id_y], node[id_x * 2 + 1][id_y]);
            }
            return;
        }

        int mid_y = (l_y + r_y) >> 1;
        if (y <= mid_y) {
            update_y(id_x, l_x, r_x, id_y * 2, l_y, mid_y, x, y, val);
        } else {
            update_y(id_x, l_x, r_x, id_y * 2 + 1, mid_y + 1, r_y, x, y, val);
        }
        // Update parent along y
        node[id_x][id_y] = merge(node[id_x][id_y * 2], node[id_x][id_y * 2 + 1]);
    }

    // Update 2D tree along x-axis
    void update_x(int id_x, int l_x, int r_x, int x, int y, T val) {
        if (l_x != r_x) {
            int mid_x = (l_x + r_x) >> 1;
            if (x <= mid_x) {
                update_x(id_x * 2, l_x, mid_x, x, y, val);
            } else {
                update_x(id_x * 2 + 1, mid_x + 1, r_x, x, y, val);
            }
        }
        // Update y-tree at id_x (and its ancestors implicitly)
        update_y(id_x, l_x, r_x, 1, 1, w, x, y, val);
    }

    // Public point update at (x, y)
    void update(int x, int y, T val) {
        update_x(1, 1, h, x, y, val);
    }

    // --- RANGE QUERY (RECTANGLE SUM) FUNCTIONS ---

    // Query 1D along y-axis at node id_x
    T get_y(int id_x, int id_y, int l_y, int r_y, int y1, int y2) {
        if (r_y < y1 || l_y > y2) {
            return T{}; // Neutral value (0 for sum)
        }
        if (y1 <= l_y && r_y <= y2) {
            return node[id_x][id_y];
        }

        int mid_y = (l_y + r_y) >> 1;
        return merge(get_y(id_x, id_y * 2, l_y, mid_y, y1, y2),
                     get_y(id_x, id_y * 2 + 1, mid_y + 1, r_y, y1, y2));
    }

    // Query 2D along x-axis
    T get_x(int id_x, int l_x, int r_x, int x1, int x2, int y1, int y2) {
        if (r_x < x1 || l_x > x2) {
            return T{}; // Neutral value (0 for sum)
        }
        if (x1 <= l_x && r_x <= x2) {
            // Segment [l_x, r_x] fully inside [x1, x2]
            // Just query y-tree here
            return get_y(id_x, 1, 1, w, y1, y2);
        }

        int mid_x = (l_x + r_x) >> 1;
        return merge(get_x(id_x * 2, l_x, mid_x, x1, x2, y1, y2),
                     get_x(id_x * 2 + 1, mid_x + 1, r_x, x1, x2, y1, y2));
    }

    // Public rectangle sum from (x1, y1) to (x2, y2)
    T get(int x1, int y1, int x2, int y2) {
        return get_x(1, 1, h, x1, x2, y1, y2);
    }
};

int main() {
    faster
    int h, w, q;
    cin >> h >> w >> q;

    vector<vector<ll>> a(h + 1, vector<ll>(w + 1));
    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            cin >> a[i][j];
        }
    }

    SegmentTree2D<ll> tree(h, w);
    tree.build(a);

    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            // Update
            int x, y;
            ll val;
            cin >> x >> y >> val;
            tree.update(x, y, val);
        } else {
            // Query
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << tree.get(x1, y1, x2, y2) << '\n';
        }
    }

    return 0;
}

// Sum queries example
// input
// 3 3 5
// 1 2 3
// 4 5 6
// 7 8 9
// 2 1 1 3 3
// 1 2 2 10
// 2 1 1 3 3
// 2 2 2 3 3
// 2 1 2 2 3
// output
// 45
// 50
// 33
// 21