#include <cstdio>
using namespace std;
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		long long n, m; scanf("%lld%lld", &n, &m), m += 1;
		if (m == 2ll) printf("%lld\n", 2 - (n & 1));
		else if (m <= n / 2 + 2) printf("%lld\n", n);
		else printf("%lld\n", n - (m - n / 2 - 2) * 2);
	}
	return 0;
}