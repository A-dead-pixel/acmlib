#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream& o, __int128_t x) {
	if(x < 0) {
		x = -x;
		o << "-";
	}
	vi v;
	if (x == 0) v.eb(0);
	while (x > 0) {
		v.eb(x % 10);
		x /= 10;
	}
	reverse(all(v));
	for (auto xd : v) {
		o << xd;
	}
	return o;
}

#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

template<typename T1, typename T2>
bool issame(T1 num, T2 x) {
	stringstream snum;
	snum << num;
	stringstream sx;
	sx << x;
	return snum.str() == sx.str();
}

using T = __int128_t;
constexpr T INF = (__int128_t)(1ll << 60) * (1ll << 60);
T gcd(T a, T b) {
	if (b == T(0)) {
		return a;
	}
	return gcd(b, a % b);
}

T abs(T x) { return x < 0 ? -x : x; }

void test() {
	V<Num> vnum{1, 2, 4, 11};
	V<T> vt{1, 2, 4, 11};
	set<T> st{1, 2, 4, 11};
	int opcnt = rd(1, 1000);
	map<int,int> cnt;
	while (opcnt) {
		int x = rd(0, ssize(vnum) - 1);
		int y = rd(0, ssize(vnum) - 1);
		int type = rd(0, 11);
		int sp = ssize(vt);
		debug(vt[x], vt[y], type);
		if (type == 0) {
			if (INF - abs(vt[x]) < abs(vt[y])) continue;
			vt.eb(vt[x] + vt[y]);
			vnum.eb(vnum[x] + vnum[y]);
		}
		else if (type == 1) {
			assert((vt[x] < vt[y]) == (vnum[x] < vnum[y]));
		}
		else if (type == 2) {
			assert((vt[x] == vt[y]) == (vnum[x] == vnum[y]));
		}
		else if (type == 3) {
			assert((vt[x] <= vt[y]) == (vnum[x] <= vnum[y]));
		}
		else if (type == 4) {
			if (vt[x] < vt[y]) continue;
			vt.eb(vt[x] - vt[y]);
			vnum.eb(vnum[x] - vnum[y]);
		}
		else if (type == 5) {
			int val = rd(-1e9, 1e9);
			debug(val);
			if (INF / abs(val) < abs(vt[x])) continue;
			vt.eb(vt[x] * val);
			vnum.eb(vnum[x] * val);
		}
		else if (type == 6) {
			if (vt[x] != 0 and INF / abs(vt[x]) < abs(vt[y])) continue;
			vt.eb(vt[x] * vt[y]);
			vnum.eb(vnum[x] * vnum[y]);
		}
		else if (type == 7) {
			int val = rd(-1e9, 1e9);
			debug(val);
			vt.eb(vt[x] / val);
			vnum.eb(vnum[x] / val);
		}
		else if (type == 8) {
			if (vt[y] == 0) continue;
			vt.eb(vt[x] / vt[y]);
			vnum.eb(vnum[x] / vnum[y]);
		}
		else if (type == 9) {
			if (vt[y] == 0) continue;
			vt.eb(vt[x] % vt[y]);
			vnum.eb(vnum[x] % vnum[y]);
		}
		else if (type == 10) {
			int val = rd(-1e9, 1e9);
			debug(val);
			vt.eb(vt[x] % val);
			vnum.eb(vnum[x] % val);
		}
		else if (type == 11) {
			if (vt[x] == 0 and vt[y] == 0) continue;
			vt.eb(gcd(vt[x], vt[y]));
			vnum.eb(nwd(vnum[x], vnum[y]));
		}
		if (sp != ssize(vt)) {
			if (st.find(vt.back()) == st.end()) {
				st.emplace(vt.back());
			}
			else {
				vt.pop_back();
				vnum.pop_back();
			}
		}
		debug(vt);
		debug(vnum);
		assert(issame(vt.back(), vnum.back()));
		--opcnt;
		++cnt[type];
	}
	debug(cnt);
}
