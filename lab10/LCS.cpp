#include <bits/stdc++.h>

using namespace std;

class Solution {
	vector<vector<int>> dp;
public:
	int lcs(string a, string b) {
		int m = a.size();
		int n = b.size();
		dp.assign(m + 1, vector<int>(n + 1, -1));
		return lcs(a, b, m, n);
	}

	string getLCS(string a, string b) {
		string ans;
		int m = a.size();
		int n = b.size();
		int i = m, j = n;
		while (i > 0 and j > 0) {
			if (a[i - 1] == b[j - 1]) {
				ans.push_back(a[i - 1]);
				i--;
				j--;
			}
			else if (dp[i - 1][j] > dp[i][j - 1]) {
				i--;
			}
			else j--;
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}
private:
	int lcs(string &a, string &b, int m, int n) {
		if (m == 0 or n == 0) return dp[m][n] = 0;
		if (dp[m][n] != -1) return dp[m][n];
		if (a[m - 1] == b[n - 1]) return dp[m][n] = 1 + lcs(a, b, m - 1, n - 1);
		else return dp[m][n] = max(lcs(a, b, m - 1, n), lcs(a, b, m, n - 1));
	}
};

int main() {
	string a = "abcde";
	string b = "ace";
	Solution algo;
	cout << algo.lcs(a, b) << endl;
	cout << algo.getLCS(a, b) << endl;
	return 0;
}