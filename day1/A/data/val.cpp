#include <bits/stdc++.h>
#include "testlib.h"
signed main (int argc, char *argv[])
{
	registerValidation(argc, argv);
	int n = inf.readInt(1, 300000); inf.readEoln();
	std::map<int, std::vector<std::pair<int, int>>> E[2];
	for (int i = 1; i <= n; i++)
	{
		int _x1 = inf.readInt(-1000000000, 1000000000); inf.readSpace();
		int _y1 = inf.readInt(-1000000000, 1000000000); inf.readSpace();
		int _x2 = inf.readInt(-1000000000, 1000000000); inf.readSpace();
		int _y2 = inf.readInt(-1000000000, 1000000000); inf.readEoln();
		ensuref((_x1 == _x2) + (_y1 == _y2) == 1, "x1 = x2 and y1 = y2 do not exactly have one true.");
		ensuref((_x1 <= _x2) && (_y1 <= _y2), "Coordinate order invalid.");
		if (_x1 == _x2) E[0][_x1].emplace_back(_y1, _y2);
		if (_y1 == _y2) E[1][_y1].emplace_back(_x1, _x2);
	}
	for (int o = 0; o < 2; o++) for (auto [p, v]: E[o])
	{
		std::sort(v.begin(), v.end());
		for (size_t i = 0; i + 1 < v.size(); i++)
			ensuref(v[i].second < v[i + 1].first,
				"(%d, %d, %d, %d) and (%d, %d, %d, %d) intersect.", p, v[i].first, p, v[i].second, p, v[i + 1].first, p, v[i + 1].second);
	}
	inf.readEof();
}