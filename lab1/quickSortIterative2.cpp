#include <iostream>
using namespace std;

int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int boundary = left - 1;
    for (int i = left; i <= right - 1; i++) {
        if (arr[i] <= pivot)
            swap(arr[++boundary], arr[i]);
    }
    swap(arr[right], arr[++boundary]);
    return boundary;
}

void quickSort(int arr[], int n) {
    int stack[n];
    int top = -1;
    stack[++top] = 0;
    stack[++top] = n - 1;
    while (top != -1) {
        int right = stack[top--];
        int left = stack[top--];
        int boundary = partition(arr, left, right);
        // if left segment size > 1.
        if (boundary - left > 1) {
            stack[++top] = left;
            stack[++top] = boundary - 1;
        }
        // if right segment size > 1.
        if (right - boundary > 1) {
            stack[++top] = boundary + 1;
            stack[++top] = right;
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
    quickSort(arr, n);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
    return 0;
}