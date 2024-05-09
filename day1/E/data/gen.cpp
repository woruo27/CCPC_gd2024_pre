#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;
typedef unsigned long long uint64_t;
int main() {
	vector<pair<uint64_t, uint64_t> > query;
	for (uint64_t n = 2; n <= 500; n += 1)
		for (uint64_t m = 2; m <= n; m += 1)
			query.push_back(make_pair(n, m));
	for (uint64_t i = 1e18 - 5e9 - 1e4; i <= 1e18 - 5e9; i++) {
		uint64_t n = i + rand() * (RAND_MAX + 1ll) + rand();
		query.push_back(make_pair(n, 2));
		query.push_back(make_pair(n, 3));
		query.push_back(make_pair(n, n - 1));
		query.push_back(make_pair(n, n - 2));
		query.push_back(make_pair(n, n / 2 + 1));
		query.push_back(make_pair(n, n / 2 + 2));
		query.push_back(make_pair(n, n / 2 + 3));
		query.push_back(make_pair(n, n / 2 + rand()));
		query.push_back(make_pair(n, n / 2 - rand()));
		query.push_back(make_pair(n, n / 2 + 10000 * rand()));
		query.push_back(make_pair(n, n / 2 - 10000 * rand()));
	}
	printf("%u\n", query.size());
	for (auto q : query) printf("%llu %llu\n", q.first, q.second - 1);
	return 0;
}