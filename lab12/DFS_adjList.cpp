#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int n, m;
vector<vector<int>> adjList;
vector<bool> vis;

void DFS(int node) {
    stack<int> st;
    st.push(node);
    vis[node] = true;
    while (!st.empty()) {
        int curr = st.top();
        cout << curr << " ";
        st.pop();
        for (int &nei : adjList[curr]) {
            if (vis[nei]) continue;
            st.push(nei);
            vis[nei] = true;
        }
    }
}

int main() {
    cin >> n >> m;
    adjList.resize(n + 1, vector<int>());
    vis.assign(n + 1, false);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    DFS(1);
    return 0;
}