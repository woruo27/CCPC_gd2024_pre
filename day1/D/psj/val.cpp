#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5, MAXLEN = 3e6;
int f[MAXN + 3], t[MAXN + 3]; bool havechild[MAXN + 3];

int main(){
	registerValidation();
	int N = inf.readInt(2, MAXN, "N"); inf.readSpace();
	int Q = inf.readInt(1, MAXN, "Q"); inf.readEoln();
	int tot_abcdlen = 0;
	for(int i = 1 ; i <= N ; ++i){
		f[i] = inf.readInt(0, i - 1, "f"); inf.readSpace();
		ensuref(!f[i] ^ (i != 1), "f = 0 can only happen when i = 1");
		havechild[f[i]] = 1; t[i] = inf.readInt(0, 1, "t"); inf.readSpace();
		string s = inf.readToken(); inf.readEoln();
		ensuref(count(s.begin(), s.end(), '/') == (t[i] ? 0 : 2), "s format error");
		for(auto t : s)
			ensuref(isdigit(t) || t == '/', "s contains other characters");
		tot_abcdlen += s.size() - count(s.begin(), s.end(), '/');
	}
	for(int i = 1 ; i <= N ; ++i)
		ensuref(t[i] ^ havechild[i], "t does not exactly match the leaf info.");
	ensuref(tot_abcdlen <= MAXLEN, "tot abcd > 3e6");
	int tot_rlen = 0;
	for(int i = 1 ; i <= Q ; ++i){
		int p = inf.readInt(1, N, "p"); inf.readSpace();
		ensuref(t[p], "p is not a leaf");
		string r = inf.readToken(); inf.readEoln();
		for(auto t : r)
			ensuref(isdigit(t), "r contains other characters");
		tot_rlen += r.size();
	}
	ensuref(tot_rlen <= MAXLEN, "tot r > 3e6");
	inf.readEof();
	return 0;
}