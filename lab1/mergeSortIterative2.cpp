#include <iostream>
using namespace std;

void merge(int arr[], int l, int m, int r) {
    int leftSize = m - l + 1;
    int rightSize = r - m;
    int left[leftSize], right[rightSize];
    for (int i = 0; i < leftSize; i++) {
        left[i] = arr[l + i];
    }
    for (int i = 0; i < rightSize; i++) {
        right[i] = arr[m + 1 + i];
    }
    int i = 0, j = 0, k = l;
    while (i < leftSize and j < rightSize) {
        if (left[i] <= right[j]) 
            arr[k++] = left[i++];
        else 
            arr[k++] = right[j++];
    }
    while (i < leftSize) 
        arr[k++] = left[i++];
    while (j < rightSize)
        arr[k++] = right[j++];
}

void mergeSort(int arr[], int n) {
    for (int curr = 1; curr < n; curr *= 2) {
        for (int l = 0; l < n - 1; l += 2 * curr) {
            int m = min(l + curr - 1, n - 1);
            int r = min(l + 2 * curr - 1, n - 1);
            // merge arr[l..m] and arr[m + 1, r].
            merge(arr, l, m, r);
        }
    }
}

int main() {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    mergeSort(arr, n);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
    return 0;
}