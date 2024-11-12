/*
 * Opis: O(k^n), ciag/cykl de Brujina słów długości $n$ nad alfabetem $\{0, 1, ..., k - 1\}$.
 * Jeżeli \texttt{is\_path} to zwraca ciąg, wpp. zwraca cykl.
 */
#include "../eulerian-path/main.cpp"
V<int> de_brujin(int k, int n, bool is_path) {
	if (n == 1) {
		V<int> v(k);
		iota(v.begin(), v.end(), 0);
		return v;
	}
	if (k == 1)
		return V (n, 0);
	int N = 1;
	REP(i, n - 1)
		N *= k;
	V<pii> edges;
	REP(i, N)
		REP(j, k)
			edges.eb(i, i * k % N + j);
	V<int> path = get<2>(eulerian_path(N, edges, true));
	path.pop_back();
	for(auto& e : path)
		e = e % k;
	if (is_path)
		REP(i, n - 1)
			path.eb(path[i]);
	return path;
}
