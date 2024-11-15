#include "../point/before_bits.cpp"
#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(2, 10);
	V<P> in(n);
	for(auto &p : in)
		p = P(rd(-10, 10), rd(-10, 10));
	debug(in);

	auto [wzorc0, wzorc1] = closest_pair(in);
	D wzorc = dist(wzorc0, wzorc1);

	D brute = 1e9;
	REP(i, n)
		REP(j, i)
			chmin(brute, dist(in[i], in[j]));
	debug(wzorc, brute);

	assert(abs(wzorc - brute) < eps);
}
