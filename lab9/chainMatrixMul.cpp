#include <bits/stdc++.h>

using namespace std;

class Solution {
    vector<vector<int>> dp;
public:
    int chainMatrixMul(vector<int> dim) {
        int n = dim.size();
        dp.assign(n, vector<int>(n, -1));
        return chainMatrixMul(dim, 1, n - 1);
    }
private:
    int chainMatrixMul(vector<int> &dim, int i, int j) {
        if (i == j) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        dp[i][j] = INT_MAX;
        for (int k = i; k < j; k++) {
            dp[i][j] = min(dp[i][j], chainMatrixMul(dim, i, k) + chainMatrixMul(dim, k + 1, j) + dim[i - 1] * dim[k] * dim[j]);
        }
        return dp[i][j];
    }   
};


int main() {
    vector<int> dim = {1, 2, 3, 4};
    Solution algo;
    int ans = algo.chainMatrixMul(dim);
    cout << "Minimum no of operations : " << ans << "\n";
    return 0;
}