#include <bits/stdc++.h>

using namespace std;

void merge(vector<int> &arr, vector<int> &left, vector<int> &right) {
    int i = 0, j = 0, k = 0;
    while (i < left.size() and j < right.size()) {
        if (left[i] < right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

void mergeSort(vector<int> &arr) {
    if (arr.size() <= 1) return;
    int mid = arr.size() / 2;
    vector<int> left(mid);
    vector<int> right(arr.size() - mid);
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    for (int i = mid; i < arr.size(); i++) {
        right[i - mid] = arr[i];
    }
    mergeSort(left);
    mergeSort(right);
    merge(arr, left, right);
}

int main() {
    vector<int> v = {10, 7, 8, 9, 1, 5};
    mergeSort(v);
    for (auto &e : v) {
        cout << e << " ";
    }
    cout << "\n";
    return 0;
}