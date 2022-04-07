#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<char>> grid;
vector<bool> col, diag1, diag2;
int ans = 0;

void solve(int x) {
	if (x == n) {
		ans++;
		return;
	}
	for (int y = 0; y < n; y++) {
		if (col[y] or diag1[x + y] or diag2[y - x + n - 1] or grid[x][y] == '*') continue;
		col[y] = diag1[x + y] = diag2[y - x + n - 1] = true;
		solve(x + 1);
		col[y] = diag1[x + y] = diag2[y - x + n - 1] = false;
	}
}

int main() {
	cin >> n;
	
	grid.resize(n, vector<char>(n));
	col.assign(n, false);
	diag1.assign(n, false);
	diag2.assign(n, false);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	solve(0);

	cout << ans << "\n";
	return 0;
}