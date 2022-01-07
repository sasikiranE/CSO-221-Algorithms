#include <bits/stdc++.h>

using namespace std;

int partition(vector<int> &arr, int start, int end) {
    int pivot = arr[end];
    int boundary = start - 1;
    for (int i = start; i <= end; i++) {
        if (arr[i] <= pivot) {
            swap(arr[++boundary], arr[i]);
        }
    }
    return boundary;
}

void quickSort(vector<int> &arr, int start, int end) {
    if (start >= end) return;
    int boundary = partition(arr, start, end);
    quickSort(arr, start, boundary - 1);
    quickSort(arr, boundary + 1, end);
}

int main() {
    vector<int> v = {10, 7, 8, 9, 1, 5};
    quickSort(v, 0, v.size() - 1);
    for (auto &e : v) {
        cout << e << " ";
    }
    cout << "\n";
    return 0;
}