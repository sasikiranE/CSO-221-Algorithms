#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct DisjointSetUnion {
    vector<int> parent, size;

    DisjointSetUnion(int n) {
        parent.resize(n + 1);
        size.resize(n + 1);
    }

    void make_set(int v) {
        size[v] = 1;
        parent[v] = v;
    }

    int find_set(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b]) swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};


struct Edge {
    int u, v, weight;

    bool operator < (Edge const &other) {
        return weight < other.weight;
    }
};

long long minimumCost;

vector<Edge> kruskal(vector<Edge> edges, int n) {
    DisjointSetUnion dsu = DisjointSetUnion(n);
    for (int i = 1; i <= n; i++) {
        dsu.make_set(i);
    }
    sort(edges.begin(), edges.end());
    vector<Edge> minSpanTree;
    minimumCost = 0;
    for (Edge &e : edges) {
        if (dsu.find_set(e.u) == dsu.find_set(e.v)) continue;
        minSpanTree.push_back(e);
        minimumCost += e.weight;
        dsu.union_sets(e.u, e.v);
    }
    return minSpanTree;
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (Edge &e : edges) {
        cin >> e.u >> e.v >> e.weight;
    }
    vector<Edge> minSpanTree = kruskal(edges, n);
    cout << "Minimum Spanning Tree : " << "\n";
    for (auto &e : minSpanTree) {
        cout << e.u << " " << e.v << " " << e.weight << "\n";
    }
    cout << "minimumCost : " << minimumCost << endl;
    return 0;
}