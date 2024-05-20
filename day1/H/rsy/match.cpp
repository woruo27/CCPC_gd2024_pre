#include <bits/stdc++.h>
constexpr int inf = 1 << 30;
struct Graph {
	int N;
	std::vector<int> h;
	std::vector<std::tuple<int, int, int>> e;
	Graph (int _N): N(_N) {h = std::vector<int>(N + 1, -1);}
	void add (int u, int v, int f) {
		e.emplace_back(v, h[u], f); h[u] = e.size() - 1;
		e.emplace_back(u, h[v], 0); h[v] = e.size() - 1;
	}
	int maxflow (int S, int T) {
		int ans = 0;
		std::vector<int> dep(N + 1);
		while ([&] (void) {
			std::fill(dep.begin(), dep.end(), -1);
			std::queue<int> q; q.push(S); dep[S] = 0;
			while (!q.empty()) {
				int u = q.front(); q.pop();
				for (int i = h[u]; ~i; i = std::get<1>(e[i]))
					if (int v = std::get<0>(e[i]); !~dep[v] and std::get<2>(e[i])) q.push(v), dep[v] = dep[u] + 1;
			}
			return ~dep[T];
		}()) {
			std::vector<int> cur(h);
			std::function<int(int, int)> dfs = [&] (int u, int F) {
				if (u == T or !F) return F;
				int w = 0;
				for (int &i = cur[u]; ~i; i = std::get<1>(e[i]))
					if (int v = std::get<0>(e[i]), &f = std::get<2>(e[i]); dep[v] == dep[u] + 1 and f) {
						int d = dfs(v, std::min(F, f));
						w += d; F -= d; f -= d; std::get<2>(e[i ^ 1]) += d;
						if (!F) break;
					}
				return w;
			};
			ans += dfs(S, inf);
		}
		return ans;
	}
};
void solve (void)
{
	int n, m; std::cin >> n >> m;
	Graph G(n + m + 2);
	for (int i = 1, b; i <= m; i++) std::cin >> b, G.add(n + i, n + m + 2, b);
	for (int i = 1, k; i <= n; i++)
	{
		std::cin >> k; G.add(n + m + 1, i, 1);
		for (int j = 1, a; j <= k; j++) std::cin >> a, G.add(i, n + a, 1);
	}
	std::cout << G.maxflow(n + m + 1, n + m + 2) << '\n';
}
signed main ()
{
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
	int T; for (std::cin >> T; T--; solve()) ;
	return 0;
}