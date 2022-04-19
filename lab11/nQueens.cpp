#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<char>> board;
vector<bool> col, diag1, diag2;
int ans = 0;
vector<vector<vector<char>>> solution;

void placeQueen(int x) {
	if (x == n) {
		ans++;
		solution.push_back(board);
		return;
	}
	for (int y = 0; y < n; y++) {
		if (col[y] or diag1[x + y] or diag2[y - x + n - 1] or board[x][y] == '*') continue;
		board[x][y] = '*';
		col[y] = diag1[x + y] = diag2[y - x + n - 1] = true;
		placeQueen(x + 1);
		board[x][y] = '.';
		col[y] = diag1[x + y] = diag2[y - x + n - 1] = false;
	}
}

void printBoard(vector<vector<char>> &board) {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board.size(); j++) {
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
}

int main() {
	cin >> n;
	
	board.assign(n, vector<char>(n, '.'));
	col.assign(n, false);
	diag1.assign(2 * n - 1, false);
	diag2.assign(2 * n - 1, false);

	placeQueen(0);

	cout << "No of solutions : " << ans << "\n";

	for (int k = 0; k < solution.size(); k++) {
		printBoard(solution[k]);
		cout << "\n";
	}

	return 0;
}
