#include <iostream>

using namespace std;

void towerOfHanoi(int n, int left, int middle, int right) {
    if (n <= 0) return;
    // move (n - 1) discs from left to middle using right.
    towerOfHanoi(n - 1, left, right, middle);
    // move the last disc remaining from left to right.
    cout << "Move disc form " << left << " to " << right << "\n";
    // move the (n - 1) discs from middle to right using left.
    towerOfHanoi(n - 1, middle, left, right);
}

int main() {
    int n;
    cin >> n;
    towerOfHanoi(n, 1, 2, 3);
    return 0;
}