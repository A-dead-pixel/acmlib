/*
 * Opis: Generatorka wielokątów wypukłych.
 * Zwraca wielokąt z co najmniej $n \cdot \texttt{PROC}$ punktami w zakresie $[-\texttt{range}, \texttt{range}]$.
 * Jeśli $n$ $(n > 2)$ jest około $\texttt{range}^{}\frac{2}{3}$, to powinno chodzić O(n \log n).
 * Dla większych $n$ może nie dać rady.
 * Ostatni punkt jest zawsze w $(0, 0)$ - można dodać przesunięcie o wektor dla pełnej losowości.
 */
#include "../point/main.cpp"
#include "../angle-sort/main.cpp"
#include "../../headers/gen.cpp"
V<int> num_split(int value, int n) {
	V<int> v(n, value);
	REP(i, n - 1)
		v[i] = rd(0, value);
	sort(all(v));
	adjacent_difference(all(v), v.begin());
	return v;
}
V<int> capped_zero_split(int cap, int n) {
	int m = rd(1, n - 1);
	auto lf = num_split(cap, m);
	auto rg = num_split(cap, n - m);
	for (int i : rg)
		lf.eb(-i);
	return lf;
}
V<P> gen_convex_polygon(int n, int range, bool strictly_convex = false) {
	assert(n > 2);
	V<P> t;
	C double PROC = 0.9;
	do {
		t.clear();
		auto dx = capped_zero_split(range, n);
		auto dy = capped_zero_split(range, n);
		shuffle(all(dx), rng);
		REP (i, n)
			if (dx[i] || dy[i])
				t.eb(dx[i], dy[i]);
		t = angle_sort(t);
		if (strictly_convex) {
			V<P> nt(1, t[0]);
			FOR (i, 1, ssize(t) - 1) {
				if (!sign(cross(t[i], nt.back())))
					nt.back() += t[i];
				else
					nt.eb(t[i]);
			}
			while (!nt.empty() && !sign(cross(nt.back(), nt[0]))) {
				nt[0] += nt.back();
				nt.pop_back();
			}
			t = nt;
		}
	} while (ssize(t) < n * PROC);
	partial_sum(all(t), t.begin());
	return t;
}
