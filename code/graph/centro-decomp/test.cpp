#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	C int INF = 1e9;
	int n = rd(1, 100);
	V graph(n, vi());
	V per(n, 0);
	iota(all(per), 0);
	REP (i, n) {
		swap(per[i], per[rd(0, i)]);
	}
	FOR (v, 1, n - 1) {
		int u = rd(0, v - 1);
		graph[per[v]].eb(per[u]);
		graph[per[u]].eb(per[v]);
	}
	CentroDecomp CD(n, graph);
	V sons(n, vi());
	int root = -1;
	REP (v, n) {
		if (CD.par[v] == -1) {
			assert(root == -1);
			root = v;
		}
		else
			sons[CD.par[v]].eb(v);
	}
	assert(root != -1);
	vi odw(n), gle(n);
	int licz = 1;

	int zli;
	V akt(n, 0);
	auto dfs = [&](int v) {
		++licz;
		queue<int> q;
		q.emplace(v);
		while (!q.empty()) {
			v = q.front();
			q.pop();
			odw[v] = licz;
			zli += akt[v];
			akt[v] = 0;
			for (int u : graph[v])
				if (odw[u] < licz)
					q.emplace(u);
		}
	};

	queue<int> que;
	que.emplace(root);
	gle[root] = 0;
	while (!que.empty()) {
		int v = que.front();
		que.pop();
		assert(odw[v] != INF);
		odw[v] = INF;
		for (int u : sons[v])
			akt[u] = 1;
		int cur = 0;
		for (int u : graph[v]) {
			if (odw[u] != INF) {
				zli = 0;
				dfs(u);
				assert(zli == 1);
				++cur;
			}
		}
		assert(cur == ssize(sons[v]));
		for (int u : sons[v]) {
			gle[u] = gle[v] + 1;
			que.emplace(u);
		}
	}
	int siz = __lg(n);
	REP (i, n) {
		assert(siz >= gle[i]);
	}
}
