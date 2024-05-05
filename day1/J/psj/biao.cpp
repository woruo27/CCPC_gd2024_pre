#include<bits/stdc++.h>
using namespace std;

#define int long long
const int BLOCK = 1e8, MAX = 1e11, P = 998244353, _ = 4e5;

int prm[_], cprm; bool noprime[_];
void sieve(){
	for(int i = 2 ; i < _ ; ++i){
		if(!noprime[i]) prm[++cprm] = i;
		for(int j = 1 ; j <= cprm && prm[j] * i < _ ; ++j){
			noprime[i * prm[j]] = 1; if(i % prm[j] == 0) break;
		}
	}
}

vector < int > pw[2];
void solve(int l, int r){
	static bool arr[BLOCK + 5]; memset(arr, 0, sizeof(arr));
	int sum1 = 0, sum2 = 0;
	for(int i = 1; i <= cprm && prm[i] * prm[i] <= r ; ++i)
		for(int j = max(prm[i], (l + prm[i] - 1) / prm[i]) * prm[i] ; j <= r ; j += prm[i]) arr[j - l] = 1;
	for(int i = 0 ; i <= r - l ; ++i)
		if(!arr[i]){int val = (l + i) % P; sum1 += val; sum2 = (sum2 + val * val) % P;}
	pw[0].push_back((pw[0].back() + sum1) % P);
	pw[1].push_back((pw[1].back() + sum2) % P);
	cerr << l << endl;
}

signed main(){
	sieve(); pw[0] = pw[1] = {0};
	for(int i = 1; i <= MAX; i += BLOCK) solve(i, i + BLOCK - 1);
	for(int p = 0 ; p < 2 ; ++p, cout << endl) for(auto t : pw[p]) cout << t << ',';
	return 0;
}