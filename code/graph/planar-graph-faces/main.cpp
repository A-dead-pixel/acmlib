/*
 * Opis: O(m\log m), zakłada, że każdy punkt ma podane współrzędne,
 * punkty są parami różne oraz krawędzie są nieprzecinającymi się odcinkami.
 * Zwraca wszystkie ściany (wewnętrzne posortowane clockwise, zewnętrzne cc).
 * WAŻNE czasem trzeba złączyć wszystkie ściany zewnętrzne
 * (których może być kilka, gdy jest wiele spójnych) w jedną ścianę.
 * Zewnętrzne ściany mogą wyglądać jak kaktusy, a wewnętrzne zawsze są niezdegenerowanym wielokątem.
 */
struct Edge {
	int e, from, to;
	// face is on the right of "from -> to"
};
ostream& operator<<(ostream &o, Edge e) {
	return o << V{e.e, e.from, e.to};
}
struct Face {
	bool is_outside;
	V<Edge> sorted_edges;
	// edges are sorted clockwise for inside and cc for outside faces
};
ostream& operator<<(ostream &o, Face f) {
	return o << pair(f.is_outside, f.sorted_edges);
}
V<Face> split_planar_to_faces(V<pair<int, int>> coord, V<pair<int, int>> edges) {
	int n = ssize(coord);
	int E = ssize(edges);
	V<V<int>> graph(n);
	REP(e, E) {
		auto [v, u] = edges[e];
		graph[v].emplace_back(e);
		graph[u].emplace_back(e);
	}
	V<int> lead(2 * E);
	iota(lead.begin(), lead.end(), 0);
	function<int (int)> find = [&](int v) {
		return lead[v] == v ? v : lead[v] = find(lead[v]);
	};
	auto side_of_edge = [&](int e, int v, bool outward) {
		return 2 * e + ((v != min(edges[e].first, edges[e].second)) ^ outward);
	};
	REP(v, n) {
		V<pair<pair<int, int>, int>> sorted;
		for(int e : graph[v]) {
			auto p = coord[edges[e].first ^ edges[e].second ^ v];
			auto center = coord[v];
			sorted.emplace_back(pair(p.first - center.first, p.second - center.second), e);
		}
		sort(sorted.begin(), sorted.end(), [&](pair<pair<int, int>, int> l0, pair<pair<int, int>, int> r0) {
			auto l = l0.first;
			auto r = r0.first;
			bool half_l = l > pair(0, 0);
			bool half_r = r > pair(0, 0);
			if(half_l != half_r)
				return half_l;
			return l.first * ll(r.second) - l.second * ll(r.first) > 0;
		});
		REP(i, ssize(sorted)) {
			int e0 = sorted[i].second;
			int e1 = sorted[(i + 1) % ssize(sorted)].second;
			int side_e0 = side_of_edge(e0, v, true);
			int side_e1 = side_of_edge(e1, v, false);
			lead[find(side_e0)] = find(side_e1);
		}
	}
	V<V<int>> comps(2 * E);
	REP(i, 2 * E)
		comps[find(i)].emplace_back(i);
	V<Face> polygons;
	V<V<pair<int, int>>> outgoing_for_face(n);
	REP(leader, 2 * E)
		if(ssize(comps[leader])) {
			for(int id : comps[leader]) {
				int v = edges[id / 2].first;
				int u = edges[id / 2].second;
				if(v > u)
					swap(v, u);
				if(id % 2 == 1)
					swap(v, u);
				outgoing_for_face[v].emplace_back(u, id / 2);
			}
			V<Edge> sorted_edges;
			function<void (int)> dfs = [&](int v) {
				while(ssize(outgoing_for_face[v])) {
					auto [u, e] = outgoing_for_face[v].back();
					outgoing_for_face[v].pop_back();
					dfs(u);
					sorted_edges.emplace_back(e, v, u);
				}
			};
			dfs(edges[comps[leader].front() / 2].first);
			reverse(sorted_edges.begin(), sorted_edges.end());
			ll area = 0;
			for(auto edge : sorted_edges) {
				auto l = coord[edge.from];
				auto r = coord[edge.to];
				area += l.first * ll(r.second) - l.second * ll(r.first);
			}
			polygons.emplace_back(area >= 0, sorted_edges);
		}
	// Remember that there can be multiple outside faces.
	return polygons;
}
