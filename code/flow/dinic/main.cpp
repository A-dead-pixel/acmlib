/*
 * Opis: O(V^2 E) Dinic bez skalowania.
 *   funkcja \texttt{get\_flowing()} zwraca dla każdej oryginalnej krawędzi ile przez nią leci.
 */
struct Dinic {
	using T = int;
	struct Edge {
		int v, u;
		T flow, cap;
	};
	int n;
	V<V<int>> graph;
	V<Edge> edges;
	Dinic(int N) : n(N), graph(n) {}
	void add_edge(int v, int u, T cap) {
		debug(v, u, cap);
		int e = ssize(edges);
		graph[v].eb(e);
		graph[u].eb(e + 1);
		edges.eb(v, u, 0, cap);
		edges.eb(u, v, 0, 0);
	}
	V<int> dist;
	bool bfs(int source, int sink) {
		dist.assign(n, 0);
		dist[source] = 1;
		deque<int> que = {source};
		while(ssize(que) and dist[sink] == 0) {
			int v = que.front();
			que.pop_front();
			for(int e : graph[v])
				if(edges[e].flow != edges[e].cap and dist[edges[e].u] == 0) {
					dist[edges[e].u] = dist[v] + 1;
					que.eb(edges[e].u);
				}
		}
		return dist[sink] != 0;
	}
	V<int> ended_at;
	T dfs(int v, int sink, T flow = numeric_limits<T>::max()) {
		if(flow == 0 or v == sink)
			return flow;
		for(; ended_at[v] != ssize(graph[v]); ++ended_at[v]) {
			Edge &e = edges[graph[v][ended_at[v]]];
			if(dist[v] + 1 == dist[e.u])
				if(T pushed = dfs(e.u, sink, min(flow, e.cap - e.flow))) {
					e.flow += pushed;
					edges[graph[v][ended_at[v]] ^ 1].flow -= pushed;
					return pushed;
				}
		}
		return 0;
	}
	T operator()(int source, int sink) {
		T answer = 0;
		while(bfs(source, sink)) {
			ended_at.assign(n, 0);
			while(T pushed = dfs(source, sink))
				answer += pushed;
		}
		return answer;
	}
	map<pii, T> get_flowing() {
		map<pii, T> ret;
		REP(v, n)
			for(int i : graph[v]) {
				if(i % 2) // considering only original edges
					continue;
				Edge &e = edges[i];
				ret[pair(v, e.u)] += e.flow;
			}
		return ret;
	}
};
