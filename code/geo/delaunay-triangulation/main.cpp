/*
 * Opis: O(n \log n), zwraca zbiór trójkątów
 * sumujący się do otoczki wypukłej, gdzie
 * każdy trójkąt nie zawiera żadnego innego punktu wewnątrz
 * okręgu opisanego
 * (czyli maksymalizuje minimalny kąt trójkątów).
 * Zakłada brak identycznych punktów.
 * W przypadku współliniowości wszystkich punktów
 * zwraca pusty V.
 * Zwraca V rozmiaru 3X, gdzie wartości 3i, 3i+1, 3i+2
 * tworzą counter-clockwise trójkąt.
 * Wśród sąsiadów zawsze jest najbliższy wierzchołek.
 * Euclidean min. spanning tree to podzbiór krawędzi.
 */
using PI = pii;
typedef struct Quad* Q;
PI distinct(INT_MAX, INT_MAX);
ll dist2(PI p) {
	return p.fi * ll(p.fi)
		+ p.se * ll(p.se);
}
ll operator*(PI a, PI b) {
	return a.fi * ll(b.se)
		- a.se * ll(b.fi);
}
PI operator-(PI a, PI b) {
	return {a.fi - b.fi,
		a.se - b.se};
}
ll cross(PI a, PI b, PI c) { return (a - b) * (b - c); }
struct Quad {
	Q rot, o = nullptr;
	PI p = distinct;
	bool mark = false;
	Quad(Q _rot) : rot(_rot) {}
	PI& F() { return r()->p; }
	Q& r() { return rot->rot; }
	Q prev() { return rot->o->rot; }
	Q next() { return r()->prev(); }
} *H; // it's safe to use in multitests
V<Q> to_dealloc;
bool is_p_inside_circle(PI p, PI a, PI b, PI c) {
	__int128_t p2 = dist2(p), a2 = dist2(a)-p2,
	    b2 = dist2(b)-p2, c2 = dist2(c)-p2;
	return cross(p,a,b) * c2 + cross(p,b,c) * a2 + cross(p,c,a) * b2 > 0;
}
Q makeEdge(PI orig, PI dest) {
	Q r = H;
	if (!r) {
		r = new Quad(new Quad(new Quad(new Quad(0))));
		Q del = r;
		REP(i, 4) {
			to_dealloc.eb(del);
			del = del->rot;
		}
	}
	H = r->o; r->r()->r() = r;
	REP(i, 4) {
		r = r->rot, r->p = distinct;
		r->o = i & 1 ? r : r->r();
	}
	r->p = orig; r->F() = dest;
	return r;
}
void splice(Q a, Q b) {
	swap(a->o->rot->o, b->o->rot->o);
	swap(a->o, b->o);
}
Q connect(Q a, Q b) {
	Q q = makeEdge(a->F(), b->p);
	splice(q, a->next());
	splice(q->r(), b);
	return q;
}
pair<Q, Q> rec(C V<PI>& s) {
	if (ssize(s) <= 3) {
		Q a = makeEdge(s[0], s[1]);
		Q b = makeEdge(s[1], s.back());
		if (ssize(s) == 2) return {a, a->r()};
		splice(a->r(), b);
		auto side = cross(s[0], s[1], s[2]);
		Q c = side ? connect(b, a) : 0;
		return {side < 0 ? c->r() : a,
			side < 0 ? c : b->r()};
	}
	auto valid = [&](Q e, Q base) {
		return cross(e->F(), base->F(), base->p) > 0;
	};
	int half = ssize(s) / 2;
	auto [ra, A] = rec({s.begin(), s.end() - half});
	auto [B, rb] = rec({ssize(s) - half + s.begin(), s.end()});
	while ((cross(B->p, A->F(), A->p) < 0
				and (A = A->next()))
	       or (cross(A->p, B->F(), B->p) > 0 
			   and (B = B->r()->o))) {}
	Q base = connect(B->r(), A);
	if (A->p == ra->p) ra = base->r();
	if (B->p == rb->p) rb = base;
	auto del = [&](Q init, function<Q (Q)> dir) {
		Q e = dir(init);
		if (valid(e, base))
			while (is_p_inside_circle(dir(e)->F(), base->F(), base->p, e->F())) {
				Q t = dir(e);
				splice(e, e->prev());
				splice(e->r(), e->r()->prev());
				e->o = H; H = e; e = t;
			}
		return e;
	};
	while(true) {
		Q LC = del(base->r(), [&](Q q) { return q->o; });
		Q RC = del(base, [&](Q q) { return q->prev(); });
		if (!valid(LC, base) and !valid(RC, base)) break;
		if (!valid(LC, base) or (valid(RC, base)
					and is_p_inside_circle(RC->F(), RC->p, LC->F(), LC->p)))
			base = connect(RC, base->r());
		else
			base = connect(base->r(), LC->r());
	}
	return {ra, rb};
}
V<PI> triangulate(V<PI> in) {
	sort(all(in)); 
	assert(unique(all(in)) == in.end());
	if (ssize(in) < 2) return {};
	Q e = rec(in).fi;
	V<Q> q = {e};
	int qi = 0;
	while (cross(e->o->F(), e->F(), e->p) < 0)
		e = e->o;
	auto add = [&] {
		Q c = e;
		do {
			c->mark = 1;
			in.eb(c->p);
			q.eb(c->r());
			c = c->next();
		} while (c != e);
	};
	add(); in.clear();
	while (qi < ssize(q))
		if (!(e = q[qi++])->mark) add();
	for (Q x : to_dealloc) delete x;
	to_dealloc.clear();
	return in;
}
