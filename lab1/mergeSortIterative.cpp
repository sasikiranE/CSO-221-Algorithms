#include <bits/stdc++.h>

using namespace std;

void merge(vector<int> &arr, int l, int m, int r) {
    // left[l..m] and right[m + 1..r].
    vector<int> left(m - l + 1);
    vector<int> right(r - m);
    for (int i = 0; i < left.size(); i++) {
        left[i] = arr[l + i];
    }
    for (int i = 0; i < right.size(); i++) {
        right[i] = arr[m + i + 1];
    }
    int i = 0, j = 0, k = l;
    while (i < left.size() and j < right.size()) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

void mergeSort(vector<int> &arr) {
    int n = arr.size();
    for (int curr = 1; curr < n; curr *= 2) {
        for (int l = 0; l < n - 1; l += 2 * curr) {
            int m = min(l + curr - 1, n - 1);
            int r = min(l + 2 * curr - 1, n - 1);
            merge(arr, l, m, r);
        }
    }
}

int main() {
    vector<int> v = {10, 7, 8, 0, 1, 5};
    mergeSort(v);
    for (auto &e : v) {
        cout << e << " ";
    }
    cout << "\n";
    return 0;
}