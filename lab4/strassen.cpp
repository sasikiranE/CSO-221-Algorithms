#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Strassen {
public:

	void multiply(vector<vector<int>> &A, vector<vector<int>> &B) {
		int p = A.size();
		int q = A[0].size();
		int r = B.size();
		int s = B[0].size();

		int k = max({p, q, r, s});

		int n = next2thPower(k);

		vector<vector<int>> newA(n, vector<int>(n, 0)), newB(n, vector<int>(n, 0)), newC(n, vector<int>(n, 0));

		for (int i = 0; i < p; i++) {
			for (int j = 0; j < q; j++) {
				newA[i][j] = A[i][j];
			}
		}

		for (int i = 0; i < r; i++) {
			for (int j = 0; j < s; j++) {
				newB[i][j] = B[i][j];
			}
		}

		multiply(newA, newB, newC);

		display(newC, p, s);

	}
private:

	void multiply(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C) {
		int n = A.size();
		if (n == 1) {
			C[0][0] = A[0][0] * B[0][0];
			return;
		}
		vector<vector<int>> A11(n / 2, vector<int>(n / 2)), A12(n / 2, vector<int>(n / 2)),
							A21(n / 2, vector<int>(n / 2)), A22(n / 2, vector<int>(n / 2)),
							B11(n / 2, vector<int>(n / 2)), B12(n / 2, vector<int>(n / 2)),
							B21(n / 2, vector<int>(n / 2)), B22(n / 2, vector<int>(n / 2)),
							C11(n / 2, vector<int>(n / 2)), C12(n / 2, vector<int>(n / 2)),
							C21(n / 2, vector<int>(n / 2)), C22(n / 2, vector<int>(n / 2));

		vector<vector<int>>	P1(n / 2, vector<int>(n / 2)) , P2(n / 2, vector<int>(n / 2)),
							P3(n / 2, vector<int>(n / 2)) , P4(n / 2, vector<int>(n / 2)),
							P5(n / 2, vector<int>(n / 2)) , P6(n / 2, vector<int>(n / 2)),
							P7(n / 2, vector<int>(n / 2));

		vector<vector<int>> aux1(n / 2, vector<int>(n / 2)), aux2(n / 2, vector<int>(n / 2));

		split(A, A11, 0, 0);
		split(A, A12, 0, n / 2);
		split(A, A21, n / 2, 0);
		split(A, A22, n / 2, n / 2);

		split(B, B11, 0, 0);
		split(B, B12, 0, n / 2);
		split(B, B21, n / 2, 0);
		split(B, B22, n / 2, n / 2);

		add(A11, A22, aux1);
		add(B11, B22, aux2);
		multiply(aux1, aux2, P1);			// P1 = (A11 + A22) * (B11 + B22)
		add(A21, A22, aux1);
		multiply(aux1, B11, P2);			// P2 = (A21 + A22) * B11
		sub(B12, B22, aux2);
		multiply(A11, aux2, P3);			// P3 = A11 * (B12 - B22)
		sub(B21, B11, aux2);
		multiply(A22, aux2, P4);			// P4 = A22 * (B21 - B11)
		add(A11, A12, aux1);
		multiply(aux1, B22, P5);			// P5 = (A11 + A12) * B22
		sub(A21, A11, aux1);
		add(B11, B12, aux2);
		multiply(aux1, aux2, P6);			// P6 = (A21 - A11) * (B11 + B12)
		sub(A12, A22, aux1);
		add(B21, B22, aux2);				
		multiply(aux1, aux2, P7);			// P7 = (A12 - A22) * (B21 + B22)

		// C11 = P1 + P4 - P5 + P7
		add(P1, P4, aux1);
		add(aux1, P7, aux2);
		sub(aux2, P5, C11);
		// C12 = P3 + P5
		add(P3, P5, C12);
		// C21 = P2 + P4
		add(P2, P4, C21);
		// C22 = P1 + P3 - P2 + P6
		add(P1, P3, aux1);
		add(aux1, P6, aux2);
		sub(aux2, P2, C22);

		// Joining C11, C12, C21, C22 into C.

		join(C, C11, 0, 0);
		join(C, C12, 0, n / 2);
		join(C, C21, n / 2, 0);
		join(C, C22, n / 2, n / 2);
	}

	int next2thPower(int n) {
		int size = 1;
		while (size < n) size *= 2;
		return size;
	}

	void split(vector<vector<int>> &parent, vector<vector<int>> &child, int startRow, int startCol) {
		for (int i1 = 0, i2 = startRow; i1 < child.size(); i1++, i2++) {
			for (int j1 = 0, j2 = startCol; j1 < child.size(); j1++, j2++) {
				child[i1][j1] = parent[i2][j2];
			}
		}
	}

	void join(vector<vector<int>> &parent, vector<vector<int>> &child, int startRow, int startCol) {
		for (int i1 = 0, i2 = startRow; i1 < child.size(); i1++, i2++) {
			for (int j1 = 0, j2 = startCol; j1 < child.size(); j1++, j2++) {
				parent[i2][j2] = child[i1][j1];
			}
		}
	}

	void add(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &R) {
		int n = A.size();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				R[i][j] = A[i][j] + B[i][j];
			}
		}
	}

	void sub(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &R) {
		int n = A.size();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				R[i][j] = A[i][j] - B[i][j];
			}
		}
	}

	void display(vector<vector<int>> &C, int r, int c) {
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				cout << C[i][j] << " ";
			}
			cout << "\n";
		}
	}
};


int main() {
	Strassen st;
	vector<vector<int>> A = {
		{1, 2, 3},
		{4, 5, 6}
	};
	vector<vector<int>> B = {
		{7, 8},
		{9, 10},
		{11, 12}
	};
	st.multiply(A, B);
	return 0;
}