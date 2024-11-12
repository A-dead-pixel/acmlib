/*
 * Opis: O(nB+B^2) dla $B=bits$, dla $S$ wyznacza minimalny zbiór $B$ taki, że każdy element $S$ można zapisać jako xor jakiegoś podzbioru $B$.
 */
int highest_bit(int ai) {
	return ai == 0 ? 0 : __lg(ai) + 1;
}
constexpr int bits = 30;
V<int> xor_base(V<int> elems) {
	V<V<int>> at_bit(bits + 1);
	for(int ai : elems)
		at_bit[highest_bit(ai)].eb(ai);
	for(int b = bits; b >= 1; --b)
		while(ssize(at_bit[b]) > 1) {
			int ai = at_bit[b].back();
			at_bit[b].pop_back();
			ai ^= at_bit[b].back();
			at_bit[highest_bit(ai)].eb(ai);
		}
	at_bit.erase(at_bit.begin());
	REP(b0, bits - 1)
		for(int a0 : at_bit[b0])
			FOR(b1, b0 + 1, bits - 1)
				for(int &a1 : at_bit[b1])
					if((a1 >> b0) & 1)
						a1 ^= a0;
	V<int> ret;
	for(auto &v : at_bit) {
		assert(ssize(v) <= 1);
		for(int ai : v)
			ret.eb(ai);
	}
	return ret;
}
