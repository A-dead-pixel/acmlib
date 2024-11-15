/*
 * Opis: O(\log^2 n), pamięć O(n \log n),
 *   2D offline,
 *   wywołujemy \texttt{preprocess(x, y)} na pozycjach, które chcemy updateować, później \texttt{init()}.
 *   \texttt{update(x, y, val)} dodaje \texttt{val} do $[x, y]$, \texttt{query(x, y)} zwraca sumę na prostokącie $(0, 0) - (x, y)$.
 */
#include "../fenwick-tree/main.cpp"
struct Fenwick2d {
	V<vi> ys;
	V<Fenwick> ft;
	Fenwick2d(int limx) : ys(limx) {}
	void preprocess(int x, int y) {
		for(; x < ssize(ys); x |= x + 1)
			ys[x].pb(y);
	}
	void init() {
		for(auto &v : ys) {
			sort(all(v));
			ft.eb(ssize(v));
		}
	}
	int ind(int x, int y) {
		auto it = lower_bound(all(ys[x]), y);
		return int(distance(ys[x].begin(), it));
	}
	void update(int x, int y, ll val) {
		for(; x < ssize(ys); x |= x + 1)
			ft[x].update(ind(x, y), val);
	}
	ll query(int x, int y) {
		ll sum = 0;
		for(x++; x > 0; x &= x - 1)
			sum += ft[x - 1].query(ind(x - 1, y + 1) - 1);
		return sum;
	}
};
