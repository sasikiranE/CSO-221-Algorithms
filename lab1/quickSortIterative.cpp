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

void quickSort(vector<int> &arr) {
    stack<pair<int, int>> st;
    int n = arr.size();
    st.push(make_pair(0, n - 1));
    while (!st.empty()) {
        int start = st.top().first;
        int end = st.top().second;
        st.pop();
        if (start >= end) continue;
        int boundary = partition(arr, start, end);
        st.push(make_pair(start, boundary - 1));
        st.push(make_pair(boundary + 1, end));
    }
}

int main() {
    vector<int> v = {10, 7, 8, 9, 1, 5};
    quickSort(v);
    for (auto &e : v) {
        cout << e << " ";
    }
    cout << "\n";
    return 0;
}