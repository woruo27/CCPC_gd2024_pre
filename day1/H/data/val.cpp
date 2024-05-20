#include <bits/stdc++.h>
#include "testlib.h"

signed main (int argc, char *argv[])
{
	registerValidation(argc, argv);
	int T = inf.readInt(1, 500, "T"); inf.readEoln();
	for (int id = 1; id <= T; id++)
	{
		int n = inf.readInt(1, 500, "n"); inf.readSpace();
		int m = inf.readInt(1, 500, "m"); inf.readEoln();
		for (int i = 1; i <= m; i++)
		{
			inf.readInt(0, 500, "b_i");
			if (i < m) inf.readSpace(); else inf.readEoln();
		}
		for (int i = 1; i <= n; i++)
		{
			int k = inf.readInt(0, m, "k_i");
			std::vector<int> a(k);
			for (int j = 0; j < k; j++)
			{
				inf.readSpace();
				a[j] = inf.readInt(1, m, "a_{i, j}");
			}
			std::sort(a.begin(), a.end());
			ensuref(std::unique(a.begin(), a.end()) - a.begin() == k, "a_{i, 1}, \\dots, a_{i, k_i} are not pairwise distinct.");
			inf.readEoln();
		}
	}
	inf.readEof();
	return 0;
}