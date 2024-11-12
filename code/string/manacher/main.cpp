/*
 * Opis: O(n), \texttt{radius[p][i]} = $rad$ = największy promień palindromu
 *   parzystości $p$ o środku $i$. $L=i-rad+!p, \; R=i+rad$ to palindrom.
 *   Dla \texttt{[abaababaab]} daje \texttt{[003000020], [0100141000]}.
 */
array<V<int>, 2> manacher(V<int> &in) {
	int n = ssize(in);
	array<V<int>, 2> radius = {{V<int>(n - 1), V<int>(n)}};
	REP(parity, 2) {
		int z = parity ^ 1, L = 0, R = 0;
		REP(i, n - z) {
			int &rad = radius[parity][i];
			if(i <= R - z)
				rad = min(R - i, radius[parity][L + (R - i - z)]);
			int l = i - rad + z, r = i + rad;
			while(0 <= l - 1 && r + 1 < n && in[l - 1] == in[r + 1])
				++rad, ++r, --l;
			if(r > R)
				L = l, R = r;
		}
	}
	return radius;
}
