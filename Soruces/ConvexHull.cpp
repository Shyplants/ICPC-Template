// [1708] 볼록 껍질
// https://www.acmicpc.net/problem/1708

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Point {
	ll x, y;
	Point(ll _x, ll _y) : x(_x), y(_y) {};
	Point() {};
	bool operator<(const Point& rhs) const { 
		if(x != rhs.x) return x < rhs.x;
		return y < rhs.y;
	}
};
struct Line {Point s, e;};
int ccw(Point &p1, Point &p2, Point &p3) {
  ll tmp = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y;
  tmp -= p1.y * p2.x + p2.y * p3.x + p3.y * p1.x;
  return (0 < tmp) - (tmp < 0);
}
bool intersect(Line &l1, Line &l2) {
  int ccw1 = ccw(l1.s, l1.e, l2.s) * ccw(l1.s, l1.e, l2.e);
  int ccw2 = ccw(l2.s, l2.e, l1.s) * ccw(l2.s, l2.e, l1.e);
  return (ccw1 < 0) && (ccw2 < 0);
}

ll getDist(Point& p1, Point& p2) {
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

const int MAX_N = 1e5 + 5;

int n;
vector<Point> point;
vector<Point> pv;

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> n;
	point.resize(n);
	for(int i=0; i<n; ++i) cin >> point[i].x >> point[i].y;

	swap(point[0], *min_element(point.begin(), point.end()));
	sort(point.begin()+1, point.end(), [](Point& p1, Point& p2){
		int ret = ccw(point[0], p1, p2);
		if(ret != 0) return ret > 0;
		return getDist(point[0], p1) < getDist(point[0], p2);
	});

	for(auto p : point) {
		while(pv.size() >= 2 && ccw(pv[pv.size()-2], pv.back(), p) <= 0) {
			pv.pop_back();
		}

		pv.push_back(p);
	}

	cout << pv.size() << '\n';
	return 0;
}