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
struct SegmentTree2D {
    int h, w; // Chiều cao và chiều rộng của mảng
    vector<vector<T>> node; // Cây 2D: node[id_x][id_y]

    // Khởi tạo với kích thước h x w
    SegmentTree2D(int height, int width) : h(height), w(width) {
        node.resize(4 * h + 5);
        for (int i = 0; i < 4 * h + 5; ++i) {
            node[i].resize(4 * w + 5, T{}); // Khởi tạo giá trị mặc định (vd: 0 cho tổng)
        }
    }

    // Hàm gộp hai giá trị, thay đổi hàm này cho các bài toán khác (min, max, ...)
    T merge(T a, T b) {
        return a + b;
    }

    // --- CÁC HÀM BUILD (XÂY DỰNG CÂY) ---

    // Xây dựng cây con 1D theo trục y tại một node id_x (quản lý đoạn [l_x, r_x])
    void build_y(int id_x, int l_x, int r_x, int id_y, int l_y, int r_y, const vector<vector<T>>& a) {
        if (l_y == r_y) {
            if (l_x == r_x) {
                // Node lá ở cả 2 trục: lấy giá trị từ mảng gốc
                node[id_x][id_y] = a[l_x][l_y];
            } else {
                // Node lá ở trục y, nhưng là node tổng hợp ở trục x
                // Gộp giá trị từ 2 node con theo trục x
                node[id_x][id_y] = merge(node[id_x * 2][id_y], node[id_x * 2 + 1][id_y]);
            }
            return;
        }

        int mid_y = (l_y + r_y) >> 1;
        build_y(id_x, l_x, r_x, id_y * 2, l_y, mid_y, a);
        build_y(id_x, l_x, r_x, id_y * 2 + 1, mid_y + 1, r_y, a);
        // Gộp giá trị từ 2 node con theo trục y
        node[id_x][id_y] = merge(node[id_x][id_y * 2], node[id_x][id_y * 2 + 1]);
    }

    // Xây dựng cây 2D theo trục x (quản lý đoạn [l_x, r_x])
    void build_x(int id_x, int l_x, int r_x, const vector<vector<T>>& a) {
        if (l_x != r_x) {
            int mid_x = (l_x + r_x) >> 1;
            build_x(id_x * 2, l_x, mid_x, a);
            build_x(id_x * 2 + 1, mid_x + 1, r_x, a);
        }
        // Sau khi các node con theo trục x đã được xây dựng,
        // xây dựng cây 1D theo trục y cho node id_x hiện tại
        build_y(id_x, l_x, r_x, 1, 1, w, a);
    }

    // Hàm public để xây dựng cây từ mảng 2D (1-based)
    void build(const vector<vector<T>>& a) {
        build_x(1, 1, h, a);
    }

    // --- CÁC HÀM UPDATE (CẬP NHẬT ĐIỂM) ---

    // Cập nhật cây 1D theo trục y tại node id_x
    void update_y(int id_x, int l_x, int r_x, int id_y, int l_y, int r_y, int x, int y, T val) {
        if (l_y == r_y) {
            if (l_x == r_x) {
                // Node lá ở cả 2 trục: gán giá trị mới
                node[id_x][id_y] = val;
            } else {
                // Cập nhật node tổng hợp theo trục x
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
        // Cập nhật lại giá trị node cha theo trục y
        node[id_x][id_y] = merge(node[id_x][id_y * 2], node[id_x][id_y * 2 + 1]);
    }

    // Cập nhật cây 2D theo trục x
    void update_x(int id_x, int l_x, int r_x, int x, int y, T val) {
        if (l_x != r_x) {
            int mid_x = (l_x + r_x) >> 1;
            if (x <= mid_x) {
                update_x(id_x * 2, l_x, mid_x, x, y, val);
            } else {
                update_x(id_x * 2 + 1, mid_x + 1, r_x, x, y, val);
            }
        }
        // Cập nhật cây 1D theo trục y tại node id_x (và các node cha của nó)
        update_y(id_x, l_x, r_x, 1, 1, w, x, y, val);
    }

    // Hàm public để cập nhật giá trị tại (x, y)
    void update(int x, int y, T val) {
        update_x(1, 1, h, x, y, val);
    }

    // --- CÁC HÀM GET (TRUY VẤN TỔNG HÌNH CHỮ NHẬT) ---

    // Truy vấn 1D theo trục y tại node id_x
    T get_y(int id_x, int id_y, int l_y, int r_y, int y1, int y2) {
        if (r_y < y1 || l_y > y2) {
            return T{}; // Trả về giá trị trung lập (0 cho tổng)
        }
        if (y1 <= l_y && r_y <= y2) {
            return node[id_x][id_y];
        }

        int mid_y = (l_y + r_y) >> 1;
        return merge(get_y(id_x, id_y * 2, l_y, mid_y, y1, y2),
                     get_y(id_x, id_y * 2 + 1, mid_y + 1, r_y, y1, y2));
    }

    // Truy vấn 2D theo trục x
    T get_x(int id_x, int l_x, int r_x, int x1, int x2, int y1, int y2) {
        if (r_x < x1 || l_x > x2) {
            return T{}; // Trả về giá trị trung lập (0 cho tổng)
        }
        if (x1 <= l_x && r_x <= x2) {
            // Đoạn [l_x, r_x] nằm hoàn toàn trong [x1, x2]
            // Chỉ cần truy vấn 1D theo trục y trên cây con tương ứng
            return get_y(id_x, 1, 1, w, y1, y2);
        }

        int mid_x = (l_x + r_x) >> 1;
        return merge(get_x(id_x * 2, l_x, mid_x, x1, x2, y1, y2),
                     get_x(id_x * 2 + 1, mid_x + 1, r_x, x1, x2, y1, y2));
    }

    // Hàm public để truy vấn tổng hình chữ nhật từ (x1, y1) đến (x2, y2)
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
            // Get
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << tree.get(x1, y1, x2, y2) << '\n';
        }
    }

    return 0;
}

//tinh tong
//input
// 3 3 5
// 1 2 3
// 4 5 6
// 7 8 9
// 2 1 1 3 3
// 1 2 2 10
// 2 1 1 3 3
// 2 2 2 3 3
// 2 1 2 2 3
//output
// 45
// 50
// 33
// 21