#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

V<P> top_hull(V<P> pts) {
	sort(pts.begin(), pts.end());
	pts.erase(unique(pts.begin(), pts.end()), pts.end());
	V<P> top;
	for(auto p : pts) {
		while(ssize(top) > 1 and dir(top.end()[-2], top.back(), p) >= 0)
			top.pop_back();
		top.emplace_back(p);
	}
	return top;
}

void test() {
	int n = rd(1, 10);
	const int mx = V<int>{10, int(1e5), int(1e9)}[rd(0, 2)];
	UpperConvexHull online;
	V<P> curr;
	while(n --> 0) {
		P p = {rd(-mx, mx), rd(-mx, mx)};
		curr.emplace_back(p);
		online.add_point(p);
		auto brute = top_hull(curr);
		auto main = V<P>(online.hull.begin(), online.hull.end());
		debug(curr, brute, main);
		assert(brute == main);
	}
}
