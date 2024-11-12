#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	const int mn = 5e2, ml = 5e5;
	int n = rd(1, mn);
	int l = rd(1, ml);
	debug(n, l);

	auto check = [&](ll x, ll y) {
		assert(x == 0 or x * __int128(x) - n * __int128(y) * y == 1);
	};

	auto [min_x, min_y] = pell(n);
	check(min_x, min_y);

	auto v = all_pell(n, l);
	for (auto [x, y] : v)
		check(x, y);
	sort(v.begin(), v.end());
	FOR(x, 2, l) {
		auto it = lower_bound(v.begin(), v.end(), pair<ll, ll>(x, -1));
		const ll y = ll(sqrtl((x * ll(x) - 1) / n));
		if (x * __int128(x) - n * __int128(y) * y == 1) {
			assert(x >= min_x);
			assert(it != v.end() and *it == pair(ll(x), y));
		}
		else {
			assert(it == v.end() or *it != pair(ll(x), y));
		}
	}
}
