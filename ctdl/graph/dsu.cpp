#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Edge structure
struct Edge {
    int u, v, weight;
    // Overload operator < for easy sorting
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

const int MAXN = 100005;
int parent[MAXN];
int sz[MAXN];

// --- DSU section ---
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
    // Optimize I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; // n vertices, m edges
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    // Step 1: Sort edges by non-decreasing weight
    sort(edges.begin(), edges.end());

    // Step 2: Initialize DSU
    make_set(n);

    long long mst_weight = 0;
    int edges_count = 0;
    vector<Edge> mst_edges; // If you need to store MST edges

    // Step 3: Iterate through sorted edges
    for (const auto& edge : edges) {
        // If u and v are not in the same connected component
        if (unite(edge.u, edge.v)) {
            mst_weight += edge.weight;
            // mst_edges.push_back(edge); // Store the edge if needed
            edges_count++;
            // Optimization: stop early when we have n-1 edges
            if (edges_count == n - 1) break;
        }
    }

    if (edges_count < n - 1) {
        cout << "The graph is disconnected; no MST exists.\n";
    } else {
        cout << mst_weight << "\n";
        // Print edges if needed
        // for (auto& e : mst_edges) cout << e.u << " " << e.v << "\n";
    }

    return 0;
}
