#include <bits/stdc++.h>
constexpr int mod = 998244353;
constexpr int maxn = 1 << 20;
int S1 (long long n) {n %= mod; return n * (n + 1) % mod * (mod + 1) / 2 % mod;}
int S2 (long long n) {n %= mod; return n * (n + 1) % mod * (2 * n + 1) % mod * (mod + 1) / 6 % mod;}
std::pair<int, int> Sp (long long n)
{
	static int f[maxn], p[maxn], id1[maxn], id2[maxn], s1[maxn], s2[maxn], sp1[maxn], sp2[maxn];
	static long long q[maxn];
	int m = sqrt(n), c = 0, t = 0;
	for (int i = 2; i <= m; i++) f[i] = 0;
	for (int i = 2; i <= m; i++)
	{
		if (!f[i]) p[++c] = i, sp1[c] = (sp1[c - 1] + i) % mod, sp2[c] = (sp2[c - 1] + 1LL * i * i) % mod;
		for (int j = 1; j <= c and i * p[j] <= m; j++)
		{
			f[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
	for (long long l = 1, r, k; l <= n; l = r + 1)
		r = n / (q[++t] = k = n / l), k <= m ? id1[k] = t : id2[n / k] = t,
		s1[t] = (S1(k) - 1 + mod) % mod, s2[t] = (S2(k) - 1 + mod) % mod;
	for (int j = 1; j <= c; j++) for (int i = 1; i <= t and 1LL * p[j] * p[j] <= q[i]; i++)
	{
		long long x = q[i] / p[j]; int id = x <= m ? id1[x] : id2[n / x];
		s1[i] = (s1[i] - 1LL * p[j] * (s1[id] - sp1[j - 1] + mod) % mod + mod) % mod;
		s2[i] = (s2[i] - 1LL * p[j] * p[j] % mod * (s2[id] - sp2[j - 1] + mod) % mod + mod) % mod;
	}
	return std::make_pair(s1[id2[1]], s2[id2[1]]);
}
signed main ()
{
	long long n; std::cin >> n;
	auto [s, s2] = Sp(n); auto [_s, _s2] = Sp(n / 2); s = (s - _s + mod) % mod; s2 = (s2 - _s2 + mod) % mod;
	int ans = (1LL * S1(n) * S1(n) - 2 * S1(n) - S2(n) + 2 + mod + mod + mod) % mod * (mod + 1) / 2 % mod;
	ans = (ans - 1LL * s * (S1(n) - s - 1 + mod) % mod - (1LL * s * s - s2 + mod) % mod * (mod + 1) / 2 % mod + mod + mod) % mod;
	std::cout << ans << std::endl;
	return 0;
}