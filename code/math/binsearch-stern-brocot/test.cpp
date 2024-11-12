#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	ll max_value = rd(0, 1) ? ll(1e1) : rd(0, 1) ? ll(4e2) : ll(1e18);
	long double ld = uniform_real_distribution<long double>(0, max_value + 1)(rng);
	debug(max_value, ld);
	auto is_good = [&](pair<ll, ll> p) {
		assert(p.second > 0);
		assert(p.first >= 0);
		return p.first / (long double)(p.second) <= ld;
	};
	pair<ll, ll> found = binsearch(max_value, is_good);

	if(max_value == ll(1e18))
		return;

	vector<pair<ll, ll>> possible;
	FOR(a, 0, max_value)
		FOR(b, 1, max_value)
			if(is_good(pair(a, b)) and __gcd(a, b) == 1)
				possible.emplace_back(pair(a, b));
	sort(possible.begin(), possible.end(), [&](pair<ll, ll> l, pair<ll, ll> r) {
		return l.first / (long double)(l.second) < r.first / (long double)(r.second);
	});
	pair<ll, ll> best = possible.back();
	debug(best, found);
	assert(best == found);
	assert(__gcd(found.first, found.second) == 1);
	assert(found.first >= 0 and found.second > 0);
}
