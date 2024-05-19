#include <cstdio>
#include <vector>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long uint64_t;
int main() {
	srand(time(0));
	mt19937 rnd(time(0));
	int T = 300000;
	vector<pair<uint64_t, uint64_t> > query;
	for (uint64_t n = 2; n <= 500; n += 1)
		for (uint64_t m = 2; m <= n; m += 1)
			query.push_back(make_pair(n, m));
	for (uint64_t i = 1e18l - 5e9l - 1e4l; i <= 1e18l - 5e9l; i++) {
		uint64_t n = i + rand() * (RAND_MAX + 1ll) + rand();
		query.push_back(make_pair(n, 2));
		query.push_back(make_pair(n, 3));
		query.push_back(make_pair(n, 4));
		query.push_back(make_pair(n, n));
		query.push_back(make_pair(n, n - 1));
		query.push_back(make_pair(n, n - 2));
		query.push_back(make_pair(n, n / 2 - 1));
		query.push_back(make_pair(n, n / 2));
		query.push_back(make_pair(n, n / 2 + 1));
		query.push_back(make_pair(n, n / 2 + 2));
		query.push_back(make_pair(n, n / 2 + 3));
		query.push_back(make_pair(n, n / 2 + rnd()));
		query.push_back(make_pair(n, n / 2 - rnd()));
		query.push_back(make_pair(n, n / 2 + 10000ll * rnd()));
		query.push_back(make_pair(n, n / 2 - 10000ll * rnd()));
	}
	cerr<<query.size()<<endl;
	while(query.size() < T){
		uint64_t n = (rnd() * 4294967296ll + rnd()) % ((uint64_t)(1e18l - 1)) + 2;
		uint64_t m = (rnd() * 4294967296ll + rnd()) % (n - 1) + 1;
		query.push_back(make_pair(n, m));
	}
	freopen("1.in","w",stdout);
	printf("%u\n", query.size());
	for (auto q : query) printf("%llu %llu\n", q.first, q.second - 1);
	return 0;
}
