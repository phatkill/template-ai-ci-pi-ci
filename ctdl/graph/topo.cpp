#include <bits/stdc++.h>
using namespace std;
const int maxN = 110;
int n, m;
int visited[maxN], ans[maxN];
vector <int> g[maxN];
stack <int> topo;

// DFS to find topological order
void dfs(int u) {
    visited[u] = 1; // Mark u as being processed (on recursion stack)
    
    // Iterate adjacent vertices of u
    for (auto v : g[u]) {
        // If v is being processed (visited[v] = 1) => cycle detected
        if (visited[v] == 1) {
            cout << "Error: graph contains a cycle";
            exit(0);
        }
        // If v not visited, continue DFS
        if (!visited[v]) dfs(v);
    }
    
    // Push u after exploring all descendants
    // Ensures descendants appear above u in the stack
    topo.push(u);
    visited[u] = 2; // Mark u finished
}

int main() {
    cin >> n >> m;
    
    // Read input and build graph
    while (m--) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v); // Add directed edge u -> v
    }
    
    // Run DFS from all unvisited vertices (handles disconnected graphs)
    for (int i = 1; i <= n; ++i)
        if (!visited[i]) dfs(i);
    
    
    int cnt = 0;
    while (!topo.empty()) {
    ans[topo.top()] = ++cnt; // Assign new order index to vertex
        topo.pop();
    }
    
    // In ra chỉ số mới của các đỉnh theo thứ tự từ 1 đến n
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
}
// Input
// 5 5
// 1 2
// 1 3
// 2 4
// 3 4
// 3 5
// Output
// 1 4 2 5 3