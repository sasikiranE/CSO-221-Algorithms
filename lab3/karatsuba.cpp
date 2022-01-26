#include <bits/stdc++.h>
using namespace std;

class Karatsuba {
public:
	long long multiply(string X, string Y) {
		int len = makeEqualLength(X, Y);
		if (len == 0) return 0;
		if (len == 1) return multiplySingleBit(X, Y);

		int f = len / 2;
		int s = len - f;

		string a = X.substr(0, f);
		string b = X.substr(f, s);

		string c = Y.substr(0, f);
		string d = Y.substr(f, s);

		long long p1 = multiply(a, c);
		long long p2 = multiply(b, d);
		long long p3 = multiply(addBitStrings(a, b), addBitStrings(c, d));

		return p1 * (1 << (2 * s)) + (p3 - p1 - p2) * (1 << s) + p2;
	}

private:
	int makeEqualLength(string &X, string &Y) {
		int len1 = X.size();
		int len2 = Y.size();
		if (len1 == len2) return len1;
		else if (len1 < len2) {
			for (int i = 0; i < len2 - len1; i++) {
				X = '0' + X;
			}
			return len2;
		}
		else {
			for (int i = 0; i < len1 - len2; i++) {
				Y = '0' + Y;
			}
			return len1;
		}
	}

	string addBitStrings(string X, string Y) {
		string res;
		int len = makeEqualLength(X, Y);
		int carry = 0;
		for (int i = len - 1; i >= 0; i--) {
			int bit1 = X[i] - '0';
			int bit2 = Y[i] - '0';
			char sum = (bit1 ^ bit2 ^ carry) + '0';
			res = sum + res;
			carry = (bit1 & bit2) | (bit2 & carry) | (carry & bit1);
		}
		if (carry) {
			res = '1' + res;
		}
		return res;
	}

	long long multiplySingleBit(string X, string Y) {
		return (X[0] - '0') * (Y[0] - '0');
	}
};

int main() {
	Karatsuba kb;
	cout << kb.multiply("110", "1010") << "\n";
	return 0;
}