/*
 * Opis: O(n^2 \log k),
 *   \texttt{BerlekampMassey<mod> bm(x)} zgaduje rekurencję ciągu $x$,
 *   \texttt{bm.get(k)} zwraca $k$-ty wyraz ciągu $x$ (index 0)
 */
#include "../simple-modulo/main.cpp"
struct BerlekampMassey {
	int n;
	vi x, c;
	BerlekampMassey(C vi &_x) : x(_x) {
		auto B = c = {1};
		int b = 1, m = 0;
		REP(i, ssize(x)) {
			m++; int d = x[i];
			FOR(j, 1, ssize(c) - 1)
				d = add(d, mul(c[j], x[i - j]));
			if(d == 0) continue;
			auto _B = c;
			c.resize(max(ssize(c), m + ssize(B)));
			int coef = mul(d, inv(b));
			FOR(j, m, m + ssize(B) - 1)
				c[j] = sub(c[j], mul(coef, B[j - m]));
			if(ssize(_B) < m + ssize(B)) { B = _B; b = d; m = 0; }
		}
		c.erase(c.begin());
		for(int &t : c) t = sub(0, t);
		n = ssize(c);
	}
	vi combine(vi a, vi b) {
		vi ret(n * 2 + 1);
		REP(i, n + 1) REP(j, n + 1)
			ret[i + j] = add(ret[i + j], mul(a[i], b[j]));
		for(int i = 2 * n; i > n; i--) REP(j, n)
			ret[i - j - 1] = add(ret[i - j - 1], mul(ret[i], c[j]));
		return ret;
	}
	int get(ll k) {
		if (!n) return 0;
		vi r(n + 1), pw(n + 1);
		r[0] = pw[1] = 1;
		for(k++; k; k /= 2) {
			if(k % 2) r = combine(r, pw);
			pw = combine(pw, pw);
		}
		int ret = 0;
		REP(i, n) ret = add(ret, mul(r[i + 1], x[i]));
		return ret;
	}
};
