#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	function<int(V<vi>)> brute = [&](V<vi> a) {
		C int n = ssize(a);
		if (n == 1)
			return a[0][0];
		int ret = 0;
		REP(i, n) {
			V<vi> b;
			REP(j, n)
				if (j != i)
					b.eb(a[j].begin() + 1, a[j].end());
			int val = mul(a[i][0], brute(b));
			if (i % 2 == 0)
				ret = add(ret, val);
			else
				ret = sub(ret, val);
		}
		debug(a, ret);
		return ret;
	};
	C int mn = 8;
	int n = rd(1, mn);
	V a(n, V(n, 0));
	C int limit = rd(0, 1) ? 3 : mod - 1;
	REP(i, n)
		REP(j, n)
			a[i][j] = rd(0, limit);
	auto bout = brute(a);
	auto mout = determinant(a);
	debug(bout, mout);
	assert(bout == mout);
}
