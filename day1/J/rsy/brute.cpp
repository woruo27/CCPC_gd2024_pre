#include <bits/stdc++.h>
constexpr int mod = 998244353;
int n, ans, anc[1 << 20];
int find (int x) {return anc[x] == x ? x : anc[x] = find(anc[x]);}
signed main ()
{
	std::cin >> n;
	for (int i = 2; i <= n; i++) anc[i] = i;
	for (int i = 2; i <= n; i++) for (int j = i; j <= n; j += i) anc[find(j)] = find(i);
	for (int i = 2; i < n; i++) for (int j = i + 1; j <= n; j++) ans = (ans + 1LL * (find(i) == find(j)) * i * j) % mod;
	for (int i = 2; i < n; i++) for (int j = i + 1; j <= n; j++) if (find(i) == find(j)) printf("(%d, %d), ", i, j);
	std::cout << ans << std::endl;
	return 0;
}