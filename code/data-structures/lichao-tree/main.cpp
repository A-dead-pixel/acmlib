/*
 * Opis: Dla funkcji, których pary przecinają się
 *   co najwyżej raz, oblicza minimum w punkcie $x$.
 *   Podany kod jest dla funkcji liniowych.
 */
struct Function {
	int a;
	ll b;
	ll operator()(int x) {
		return x * ll(a) + b;
	}
	Function(int p = 0, ll q = infll) : a(p), b(q) {}
};
ostream& operator<<(ostream &os, Function f) {
	return os << pair(f.a, f.b);
}
struct LiChaoTree {
	int size = 1;
	V<Function> tree;
	LiChaoTree(int n) {
		while(size < n)
			size *= 2;
		tree.resize(size << 1);
	}
	ll get_min(int x) {
		int v = x + size;
		ll ans = infll;
		while(v) {
			chmin(ans, tree[v](x));
			v >>= 1;
		}
		return ans;
	}
	void add_func(Function new_func, int v, int l, int r) {
		int m = (l + r) / 2;
		bool domin_l = tree[v](l) > new_func(l),
			 domin_m = tree[v](m) > new_func(m);
		if(domin_m)
			swap(tree[v], new_func);
		if(l == r)
			return;
		else if(domin_l == domin_m)
			add_func(new_func, v << 1 | 1, m + 1, r);
		else
			add_func(new_func, v << 1, l, m);
	}
	void add_func(Function new_func) {
		add_func(new_func, 1, 0, size - 1);
	}
};
