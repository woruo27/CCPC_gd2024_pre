#include <bits/stdc++.h>
// #define DEBUG
constexpr int inf = 1 << 30;
int n; long long ans; std::set<int> S;
std::vector<std::tuple<int, int, int>> L[2];
std::map<int, std::vector<std::tuple<int, int, int>>> M[2];
signed main ()
{
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
	std::cin >> n;
	for (int i = 1, _x1, _y1, _x2, _y2; i <= n; i++)
		std::cin >> _x1 >> _y1 >> _x2 >> _y2, _x1 == _x2 ? L[0].emplace_back(_x1, _y1, _y2) : L[1].emplace_back(_y1, _x1, _x2);
	for (int o = 0; o < 2; o++)
	{
#ifdef DEBUG
		std::cerr << "o = " << o << ", L[o].size() = " << L[o].size() << std::endl;
#endif
		std::vector<std::tuple<int, int, int>> E;
		std::map<std::pair<int, int>, std::vector<int>> V;
		for (auto [p, l, r]: L[o]) E.emplace_back(l, 1, p), E.emplace_back(r, -1, p);
		std::sort(E.begin(), E.end());
		std::set<int> s; s.insert(-inf); s.insert(inf);
		for (auto [p, v, d]: E)
		{
			auto ins = [&] (int p1, int p2, int p3) {if (p1 != -inf and p3 != inf and p3 - p2 == p2 - p1) V[std::pair(p2, p2 - p1)].emplace_back(p);};
			if (v == 1)
			{
				auto [it, _] = s.insert(d);
				// del
				if (std::prev(it) != s.begin()) ins(*std::prev(std::prev(it)), *std::prev(it), *std::next(it));
				if (std::next(std::next(it)) != s.end()) ins(*std::prev(it), *std::next(it), *std::next(std::next(it)));
				// add
				if (std::prev(it) != s.begin()) ins(*std::prev(std::prev(it)), *std::prev(it), *it);
				if (true) ins(*std::prev(it), *it, *std::next(it));
				if (std::next(std::next(it)) != s.end()) ins(*it, *std::next(it), *std::next(std::next(it)));
			}
			else
			{
				auto it = s.lower_bound(d);
				// del
				if (std::prev(it) != s.begin()) ins(*std::prev(std::prev(it)), *std::prev(it), *it);
				if (true) ins(*std::prev(it), *it, *std::next(it));
				if (std::next(std::next(it)) != s.end()) ins(*it, *std::next(it), *std::next(std::next(it)));
				// add
				it = s.erase(it);
				if (std::prev(it) != s.begin()) ins(*std::prev(std::prev(it)), *std::prev(it), *it);
				if (std::next(it) != s.end()) ins(*std::prev(it), *it, *std::next(it));
			}
		}
		for (auto [p, vec]: V)
		{
#ifdef DEBUG
			std::cerr << "(" << p.first << ", " << p.second << "): ";
			for (auto p: vec) std::cerr << p << " ";
			std::cerr << std::endl;
#endif
			S.insert(p.second); assert(vec.size() % 2 == 0);
			for (size_t i = 0; i < vec.size(); i += 2) if (vec[i + 1] - vec[i] >= 2 * p.second) M[o][p.second].emplace_back(p.first, vec[i], vec[i + 1]);
		}
	}
	for (int c: S) if (M[0].count(c) and M[1].count(c))
	{
		std::vector<int> w;
		for (auto [x, l, r]: M[0][c]) w.emplace_back(x);
		for (auto [y, d, u]: M[1][c]) w.emplace_back(d + c - 1), w.emplace_back(u - c);
		std::sort(w.begin(), w.end()); w.resize(std::unique(w.begin(), w.end()) - w.begin());
		std::vector<int> t(w.size() + 1);
		std::vector<std::pair<int, int>> Ea, Ed;
		for (auto [x, l, r]: M[0][c]) x = std::lower_bound(w.begin(), w.end(), x) - w.begin() + 1, Ea.emplace_back(l, x), Ed.emplace_back(r, x);
		std::sort(Ea.begin(), Ea.end());
		std::sort(Ed.begin(), Ed.end());
		std::sort(M[1][c].begin(), M[1][c].end());
		size_t pa = 0, pd = 0;
		auto add = [&] (int x, int v) {for (size_t i = x; i < t.size(); i += i & -i) t[i] += v;};
		auto ask = [&] (int x) {long long r = 0; for (size_t i = x; i; i -= i & -i) r += t[i]; return r;};
		for (auto [y, d, u]: M[1][c])
		{
			for (; pa < Ea.size() and Ea[pa].first <= y - c; ) add(Ea[pa++].second, 1);
			for (; pd < Ed.size() and Ed[pd].first < y + c; ) add(Ed[pd++].second, -1);
			ans += ask(std::lower_bound(w.begin(), w.end(), u - c) - w.begin() + 1) - ask(std::lower_bound(w.begin(), w.end(), d + c - 1) - w.begin() + 1);
		}
	}
	std::cout << ans << std::endl;
	return 0;
}
/*
8
0 0 10 0
1 1 3 1
0 2 10 2
0 4 10 4
0 0 0 10
1 1 1 3
2 0 2 10
4 0 4 10
*/