#include <bits/stdc++.h>
using namespace std;
const int maxN = 110;
int n, m;
int visited[maxN], ans[maxN];
vector <int> g[maxN];
stack <int> topo;

// Hàm DFS để tìm thứ tự tô-pô
void dfs(int u) {
    visited[u] = 1; // Đánh dấu đỉnh u đang được xét (đang trong stack của DFS)
    
    // Duyệt qua các đỉnh kề của u
    for (auto v : g[u]) {
        // Nếu v đang được xét (visited[v] = 1) => phát hiện chu trình
        if (visited[v] == 1) {
            cout << "Error: graph contains a cycle";
            exit(0);
        }
        // Nếu v chưa được thăm, tiếp tục DFS
        if (!visited[v]) dfs(v);
    }
    
    // Đẩy đỉnh u vào stack sau khi đã xét hết các đỉnh con của nó
    // Điều này đảm bảo các đỉnh được xét sau (đỉnh con) sẽ nằm trên đỉnh u trong stack
    topo.push(u);
    visited[u] = 2; // Đánh dấu đỉnh u đã xét xong
}

int main() {
    cin >> n >> m;
    
    // Đọc dữ liệu và xây dựng đồ thị
    while (m--) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v); // Thêm cung từ u đến v
    }
    
    // Thực hiện DFS từ tất cả các đỉnh chưa được thăm
    // (xử lý cả trường hợp đồ thị không liên thông)
    for (int i = 1; i <= n; ++i)
        if (!visited[i]) dfs(i);
    
    
    int cnt = 0;
    while (!topo.empty()) {
        ans[topo.top()] = ++cnt; // Gán chỉ số mới cho đỉnh topo.top()
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