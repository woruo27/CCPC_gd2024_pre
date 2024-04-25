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
	for (int c: S)
	{
		for (auto [x, l, r]: M[0][c])
			for (auto [y, d, u]: M[1][c])
				if (d <= x - c and x + c <= u and l <= y - c and y + c <= r) ans++;
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