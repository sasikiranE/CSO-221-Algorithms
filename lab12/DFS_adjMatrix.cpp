#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

int n, m;
vector<vector<int>> grid;
vector<vector<bool>> vis;

vector<int> dx = {-1, 1, 0, 0};
vector<int> dy = {0, 0, -1, 1};

bool inside(int x, int y) {
    return x >= 0 and y >= 0 and x < n and y < m;
}

void DFS(int x, int y) {
    stack<pair<int, int>> st;
    st.push(make_pair(x, y));
    vis[x][y] = true;
    while (!st.empty()) {
        auto node = st.top();
        cout << node.first << " " << node.second << "\n";
        st.pop();
        for (int k = 0; k < dx.size(); k++) {
            int i = x + dx[k];
            int j = y + dy[k];
            if (inside(i, j) and !vis[i][j] and grid[i][j] == 1) {
                st.push(make_pair(i, j));
                vis[i][j] = true;
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    grid.resize(n, vector<int>(m));
    vis.assign(n, vector<bool>(m, false));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    DFS(0, 0);
    return 0;
}