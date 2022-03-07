#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> PII;

struct Edge {
    int u, v, weight;
};

long long minimumCost;

vector<Edge> prims(vector<vector<PII>> &adj) {
    int n = adj.size() - 1;
    vector<bool> marked(n + 1, false);
    vector<int> parent(n + 1, -1);
    vector<Edge> minSpanTree;
    minimumCost = 0;

    priority_queue<PII, vector<PII>, greater<PII>> Q;
    int src = 1;
    Q.push({0, 1});
    while (!Q.empty()) {
        auto p = Q.top();
        Q.pop();
        int wt = p.first;
        int x = p.second;
        if (marked[x]) continue;
        marked[x] = true;
        if (parent[x] != -1) {
            minSpanTree.push_back({parent[x], x, wt});
            minimumCost += wt;
        }
        for (auto &e : adj[x]) {
            if (marked[e.second]) continue;
            parent[e.second] = x;
            Q.push(e);
        }
    }
    return minSpanTree;
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<PII>> adj(n + 1);
    int u, v, wt;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> wt;
        adj[u].push_back({wt, v});
        adj[v].push_back({wt, u});
    }

    vector<Edge> minSpanTree = prims(adj);
    cout << "Minimum Spanning Tree : " << "\n";
    for (auto &e : minSpanTree) {
        cout << e.u << " " << e.v << " " << e.weight << "\n";
    }
    cout << "minimumCost : " << minimumCost << endl;
    return 0;
}