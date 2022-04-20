#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> adjList;
vector<bool> vis;

void BFS(int src) {
    queue<int> q;
    q.push(src);
    vis[src] = true;
    while (!q.empty()) {
        int node = q.front();
        cout << node << " ";
        q.pop();
        for (int nei : adjList[node]) {
            if (vis[nei]) continue;
            q.push(nei);
            vis[nei] = true;
        }
    }
    cout << "\n";
}

int main() {
    int n, m;
    cin >> n >> m;
    adjList.assign(n + 1, vector<int>());
    vis.assign(n + 1, false);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    BFS(1);
    return 0;
}