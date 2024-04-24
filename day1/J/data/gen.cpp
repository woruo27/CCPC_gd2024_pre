#include <bits/stdc++.h>
#include "testlib.h"

signed main (int argc, char* argv[])
{
	registerGen(argc, argv, 1);
	std::vector<long long> vec;
	for (int i = 4; i <= 10; i++) vec.emplace_back(i);
	for (int i = 998244350; i <= 998244356; i++) vec.emplace_back(i);
	for (long long i = 99999999995LL; i <= 100000000000LL; i++) vec.emplace_back(i);
	for (int c = 1; c <= 10; c++) vec.emplace_back(rnd.next(4, 1000));
	for (int c = 1; c <= 10; c++) vec.emplace_back(rnd.next(4, 1000000));
	for (int c = 1; c <= 10; c++) vec.emplace_back(rnd.next(4LL, 100000000000LL));
	std::sort(vec.begin(), vec.end());
	vec.resize(std::unique(vec.begin(), vec.end()) - vec.begin());
	assert(system("g++ -o std ../rsy/std.cpp -static -O2 -std=c++17") == 0);
	assert(system("g++ -o brute ../rsy/brute.cpp -static -O2 -std=c++17") == 0);
	for (int i = 1; i <= (int)vec.size(); i++)
	{
		std::ofstream fout((std::to_string(i) + ".in").c_str());
		fout << vec[i - 1] << std::endl; fout.close();
		assert(system(("./std < " + std::to_string(i) + ".in > " + std::to_string(i) + ".ans").c_str()) == 0);
		if (vec[i - 1] <= 1000)
		{
			assert(system(("./brute < " + std::to_string(i) + ".in > " + std::to_string(i) + ".out").c_str()) == 0);
			assert(system(("diff " + std::to_string(i) + ".out " + std::to_string(i) + ".ans").c_str()) == 0);
			assert(system(("rm " + std::to_string(i) + ".out").c_str()) == 0);
		}
	}
	assert(system("rm std") == 0);
	assert(system("rm brute") == 0);
	return 0;
}