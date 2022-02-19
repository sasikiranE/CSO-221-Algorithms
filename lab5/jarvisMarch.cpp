#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class JarvisMarch {
public:
	vector<pair<int, int>> giftWrapping(vector<pair<int, int>>& points) {
		vector<pair<int, int>> hull;
		pair<int, int> onHull = *min_element(points.begin(), points.end());
		while (true) {
			hull.push_back(onHull);
			pair<int, int> nextPoint = points[0];
			for (auto& point : points) {
				int o = orientation(onHull, nextPoint, point);
				if (nextPoint == onHull or o == 1 or (o == 0 and dis(onHull, nextPoint) < dis(onHull, point))) {
					nextPoint = point;
				}
			}
			onHull = nextPoint;
			if (onHull == hull[0]) break;
		}
		return hull;
	}

private:
	int orientation(pair<int, int>& p1, pair<int, int>& p2, pair<int, int>& p3) {
		int d = (p3.second - p2.second) * (p2.first - p1.first) - (p2.second - p1.second) * (p3.first - p2.first);
		if (d > 0) return 1;
		else if (d < 0) return -1;
		else return 0;
	}

	int dis(pair<int, int>& p1, pair<int, int>& p2) {
		int a = p2.first - p1.first;
		int b = p2.second - p1.second;
		return a * a + b * b;
	}
};


int main() {
	vector<pair<int, int>> points = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
	JarvisMarch jm;
	vector<pair<int, int>> convexHull = jm.giftWrapping(points);
	for (auto& p : convexHull) {
		cout << p.first << " " << p.second << "\n";
	}
	return 0;
}
