#include <bits/stdc++.h>

using namespace std;

bool isThereSubsetSum(vector<int> &arr, int n, int sum) {
	if (sum == 0) return true;
	if (n == 0) return false;
	if (arr[n - 1] > sum) return isThereSubsetSum(arr, n - 1, sum);
	return isThereSubsetSum(arr, n - 1, sum) or isThereSubsetSum(arr, n - 1, sum - arr[n - 1]);
}

int main() {
	int n, target_sum;
	cin >> n >> target_sum;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << (isThereSubsetSum(arr, n, target_sum) ? "YES" : "NO") << "\n";
	return 0;
}