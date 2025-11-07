#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Cấu trúc lưu trữ cạnh
struct Edge {
    int u, v, weight;
    // Overload toán tử < để sort dễ dàng
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

const int MAXN = 100005;
int parent[MAXN];
int sz[MAXN];

// --- Phần DSU ---
void make_set(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
}

int find(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find(parent[v]);
}

bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
    return false;
}
// ----------------

int main() {
    // Tối ưu I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; // n đỉnh, m cạnh
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    // B1: Sắp xếp các cạnh theo trọng số tăng dần
    sort(edges.begin(), edges.end());

    // B2: Khởi tạo DSU
    make_set(n);

    long long mst_weight = 0;
    int edges_count = 0;
    vector<Edge> mst_edges; // Nếu cần lưu các cạnh của MST

    // B3: Duyệt các cạnh đã sắp xếp
    for (const auto& edge : edges) {
        // Nếu u và v chưa thuộc cùng một thành phần liên thông
        if (unite(edge.u, edge.v)) {
            mst_weight += edge.weight;
            // mst_edges.push_back(edge); // Lưu cạnh vào kết quả nếu cần
            edges_count++;
            // Tối ưu: Nếu đã đủ n-1 cạnh thì dừng sớm
            if (edges_count == n - 1) break;
        }
    }

    if (edges_count < n - 1) {
        cout << "Do thi khong lien thong, khong co MST.\n";
    } else {
        cout << mst_weight << "\n";
        // In ra các cạnh nếu cần
        // for (auto& e : mst_edges) cout << e.u << " " << e.v << "\n";
    }

    return 0;
}
