#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;
pair<int, int> mid;


class ConvexHull {
public:
	vector<pair<int, int>> getConvexHull(vector<pair<int, int>> points) {
		sort(points.begin(), points.end());
		return divide(points);
	}
private:
	vector<pair<int, int>> divide(vector<pair<int, int>> points) {
		if (points.size() <= 5) {
			return bruteHull(points);
		}
		vector<pair<int, int>> left, right;
		for (int i = 0; i < points.size() / 2; i++) {
			left.push_back(points[i]);
		}
		for (int i = points.size() / 2; i < points.size(); i++) {
			right.push_back(points[i]);
		}
		vector<pair<int, int>> leftHull = divide(left);
		vector<pair<int, int>> rightHull = divide(right);
		return mergeHulls(leftHull, rightHull);
	}

	vector<pair<int, int>> mergeHulls(vector<pair<int, int>> A, vector<pair<int, int>> B) {
		int n1 = A.size(), n2 = B.size();
		int ia = 0, ib = 0;
		for (int i = 1; i < n1; i++) {
			if (A[i].first > A[ia].first)
				ia = i;
		}
		for (int i = 1; i < n2; i++) {
			if (B[i].first < B[ib].first)
				ib = i;
		}
		// find upper tangent.
		int inda = ia, indb = ib;
		bool done = false;
		while (!done) {
			done = 1;
			while (orientation(B[indb], A[inda], A[(inda + 1) % n1]) >= 0)
				inda = (inda + 1) % n1;

			while (orientation(A[inda], B[indb], B[(n2 + indb - 1) % n2]) <= 0) {
				indb = (n2 + indb - 1) % n2;
				done = 0;
			}
		}
		int uppera = inda, upperb = indb;
		inda = ia, indb = ib;
		done = 0;
		int g = 0;
		// find lower tangent.
		while (!done) {
			done = 1;
			while (orientation(A[inda], B[indb], B[(indb + 1) % n2]) >= 0)
				indb = (indb + 1) % n2;

			while (orientation(B[indb], A[inda], A[(n1 + inda - 1) % n1]) <= 0) {
				inda = (n1 + inda - 1) % n1;
				done = 0;
			}
		}
		int lowera = inda, lowerb = indb;
		// return res with point sorted in counter-clockwise dir.
		vector<pair<int, int>> res;
		int ind = uppera;
		res.push_back(A[uppera]);
		while (ind != lowera) {
			ind = (ind + 1) % n1;
			res.push_back(A[ind]);
		}
		ind = lowerb;
		res.push_back(B[lowerb]);
		while (ind != upperb) {
			ind = (ind + 1) % n2;
			res.push_back(B[ind]);
		}
		return res;
	}

	// brute force way of finding convex hull.
	vector<pair<int, int>> bruteHull(vector<pair<int, int>> points) {
		set<pair<int, int>> s;
		for (int i = 0; i < points.size(); i++) {
			for (int j = i + 1; j < points.size(); j++) {
				int x1 = points[i].first, y1 = points[i].second;
				int x2 = points[j].first, y2 = points[j].second;
				int a1 = y1 - y2;
				int b1 = x2 - x1;
				int c1 = x1 * y2 - y1 * x2;
				int pos = 0, neg = 0;
				for (int k = 0; k < points.size(); k++) {
					if (a1 * points[k].first + b1 * points[k].second + c1 <= 0)
						neg++;
					if (a1 * points[k].first + b1 * points[k].second + c1 >= 0)
						pos++;
				}
				if (pos == points.size() or neg == points.size()) {
					s.insert(points[i]);
					s.insert(points[j]);
				}
			}
		}
		// return res with point sorted in counter-clockwise dir.
		vector<pair<int, int>> res;
		for (auto &e : s)
			res.push_back(e);
		mid = {0, 0};
		int n = res.size();
		for (int i = 0; i < n; i++) {
			mid.first += res[i].first;
			mid.second += res[i].second;
			res[i].first *= n;
			res[i].second *= n;
		}
		sort(res.begin(), res.end(), compare);
		for (int i = 0; i < n; i++) {
			res[i] = {res[i].first / n, res[i].second / n};
		}
		return res;
	}

	// get orientation of three points.
	static int orientation(const pair<int, int> &a, const pair<int, int> &b, const pair<int, int> &c) {
		int k = (b.second - a.second) * (c.first - b.first) -
		        (c.second - b.second) * (b.first - a.first);
		if (k == 0) return 0; // collinear
		if (k > 0) return 1; // cw
		return -1; // ccw
	}

	// get the quadrant of the point.
	static int quad(const pair<int, int> &p) {
		if (p.first >= 0 and p.second >= 0) return 1;
		if (p.first <= 0 and p.second >= 0) return 2;
		if (p.first <= 0 and p.second <= 0) return 3;
		return 4;
	}

	// comparator func to sort points in counter clockwise dir.
	static bool compare(const pair<int, int> &p1, const pair<int, int> &q1) {
		pair<int, int> p = {p1.first - mid.first, p1.second - mid.second};
		pair<int, int> q = {q1.first - mid.first, q1.second - mid.second};
		int one = quad(p);
		int two = quad(q);
		if (one != two) return one < two;
		return (p.second * q.first - q.second - p.first);
	}
};


int main() {
	vector<pair<int, int>> points = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};  
    ConvexHull algo = ConvexHull();
    vector<pair<int, int>> ans = algo.getConvexHull(points);
    cout << "Convex Hull : " << "\n";
    for (auto &p : ans) {
    	cout << '(' << p.first << ' ' << p.second <<  ')' << '\n';
    }
	return 0;
}