#include <bits/stdc++.h>
using namespace std;

int parent[100005];
map<int, int> m;
int inc = -1;
pair<int, int> p = {0, 0};
vector<int> present;

int edg = 0;

struct edge {
    int src, dest;
    long double weight;
} edges[100005];

bool cmp(edge x, edge y) {
    return x.weight < y.weight;
}

void initialise(int n) {
    for (int i = 1; i <= n; i++)
        parent[i] = i;
}

int find(int x) {
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

long double union1(int i, long double sum) {
    int x, y;
    x = find(edges[i].src);
    y = find(edges[i].dest);
    if (x != y) {
        parent[x] = y;

        present.push_back(i);
        m[i] = 1;

        sum += edges[i].weight;
    }
    return sum;
}

long double union2(int i, long double sum) {
    int x, y;
    x = find(edges[i].src);
    y = find(edges[i].dest);
    if (x != y) {
        parent[x] = y;

        sum += edges[i].weight;
        edg++;
        if (m[i] == 0) inc = i;
    }
    return sum;
}

int main() {
    int v, e; cin >> v >> e;
    initialise(v);

    for (int i = 0; i < e; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    sort(edges, edges + e, cmp);

    long double sum = 0;
    for (int i = 0; i < e; i++) {
        sum = union1(i, sum);
    }

    cout << "MST: " << sum << "\n";

    long double sec_best_mst = INT_MAX;

    sum = 0;
    int j;
    for (j = 0; j < present.size(); j++) {
        initialise(v);
        edg = 0;
        for (int i = 0; i < e; i++) {

            if (i == present[j])
                continue;
            sum = union2(i, sum);
        }
        if (edg != v - 1) {
            sum = 0;
            continue;
        }

        if (sec_best_mst > sum) {
            sec_best_mst = sum;
            p = {j, inc};
        }
        sum = 0;
    }

    cout << "Second Best MST: " << sec_best_mst << "\n";

    for (int i = 0; i < present.size(); i++) {
        if (i != p.first) cout << edges[present[i]].src << " " << edges[present[i]].dest << " ->" << edges[present[i]].weight << "\n";
    }
    int x = p.second;
    cout << edges[x].src << " " << edges[x].dest << " ->" << edges[x].weight << "\n";
    return 0;
}