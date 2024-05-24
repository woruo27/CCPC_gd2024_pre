#include<bits/stdc++.h>
using namespace std;

const int _ = 2e5 + 7, P[2] = {(int)1e9 + 7, (int)1e9 + 9}, base = 11; int pwp[2][_];

struct Hash{
	int hashval[2], len; Hash(int x = 0){hashval[0] = hashval[1] = x; len = !!x;}
	int& operator [](int x){return hashval[x];}
	friend bool operator <(Hash p, Hash q){
		if(p[0] != q[0]) return p[0] < q[0];
		if(p[1] != q[1]) return p[1] < q[1];
		return p.len < q.len;
	}
	friend bool operator ==(Hash p, Hash q){return !(p < q) && !(q < p);}
	friend void operator ^=(Hash &p, int q){for(int j = 0 ; j < 2 ; ++j) p[j] = 1ll * p[j] * pwp[j][q] % P[j];}
	friend Hash operator +(Hash p, Hash q){
		p ^= q.len; for(int i = 0 ; i < 2 ; ++i) p[i] = (p[i] + q[i]) % P[i];
		p.len += q.len; return p;
	}
	friend Hash operator -(Hash p, Hash q){
		q ^= p.len - q.len; for(int i = 0 ; i < 2 ; ++i) p[i] = (p[i] - q[i] + P[i]) % P[i];
		p.len -= q.len; return p;
	}
};
struct String{
	string str; vector < Hash > prefix;
	String(string _str){
		str = _str; prefix = {Hash()};
		for(int i = 0 ; i < str.size() ; ++i)
			prefix.push_back(prefix.back() + Hash(str[i] - '0' + 1));
	}
	Hash all(){return prefix.back();}
	Hash getsuffix(Hash pref){
		if(pref.len <= str.size() && prefix[pref.len] == pref)
			return prefix.back() - prefix[pref.len];
		return Hash(-1);
	}
}; vector < String > tokens[_]; int n , q , f[_] , s[_]; vector < int > ch[_], nxt[_];
struct Qry{int id; String str; Qry(int _id, string _str): id(_id), str(_str){}}; vector < Qry > qry[_];
int ans_cnt[_], ans_id[_];

bool vis[_]; int totsz, mnsz, mnid;
void getsz(int x){vis[x] = 1; ++totsz; for(auto t : nxt[x]){if(!vis[t]) getsz(t);} vis[x] = 0;}
int getmn(int x){
	int sz = 1, mx = 0; vis[x] = 1;
	for(auto t : nxt[x]) if(!vis[t]){int s = getmn(t); sz += s; mx = max(mx, s);}
	vis[x] = 0; mx = max(mx, totsz - sz); if(!s[x] && mx < mnsz){mnsz = mx; mnid = x;}
	return sz;
}

struct PartialQry{int id; Hash match;};
bool operator <(PartialQry x, PartialQry y){return x.match < y.match;}
struct Data{vector < PartialQry > query, endpoints;};

void getdata(int x, bool dir, Data &data, Hash from = Hash(), Hash to = Hash()){
	vis[x] = 1;
	if(s[x]){
		for(auto t : qry[x]) data.query.push_back((PartialQry){t.id, t.str.getsuffix(from)});
		data.endpoints.push_back((PartialQry){x, to + tokens[x][0].all()});
	}
	for(auto t : nxt[x])
		if(!vis[t]){
			bool newdir = t != f[x];
			getdata(t, newdir, data, 
					tokens[x][(newdir != dir ? 2 : !newdir)].all() + from, 
					to + tokens[x][(newdir != dir ? 2 : newdir)].all());
		}
	vis[x] = 0;
}

Data addup(vector < Data > &dat){
	Data res;
	for(auto t: dat){
		res.query.insert(res.query.end(), t.query.begin(), t.query.end());
		res.endpoints.insert(res.endpoints.end(), t.endpoints.begin(), t.endpoints.end());
	}
	return res;
}

void solvedat(vector < PartialQry > &x, vector < PartialQry > &y, int m){
	sort(x.begin(), x.end()); sort(y.begin(), y.end());
	int cnt = 0 , sumid = 0; auto ly = y.begin() , ry = y.begin();
	for(auto t : x){
		while(ry != y.end() && !(t.match < ry->match)){++cnt; sumid += ry->id; ++ry;}
		while(ly != y.end() && ly->match < t.match){--cnt; sumid -= ly->id; ++ly;}
		ans_cnt[t.id] += cnt * m; ans_id[t.id] += sumid * m;
	}
}

void getval(vector < Data > &dat1, vector < Data > &dat2, int m, bool twoside = 0){
	Data res1 = addup(dat1), res2 = addup(dat2);
	solvedat(res1.query, res2.endpoints, m); if(twoside) solvedat(res2.query, res1.endpoints, m);
}

void dfz(int x){
	totsz = 0; mnsz = 1e9; getsz(x); getmn(x); if(mnsz == 1e9) return;
	vis[x = mnid] = 1; vector < Data > ch_data;
	for(auto t : ch[x]) if(!vis[t]){Data tmp; getdata(t, 1, tmp); ch_data.push_back(tmp);}
	if(f[x] && !vis[f[x]]){
		Data tmp; getdata(f[x], 0, tmp, tokens[x][1].all(), tokens[x][0].all()); vector < Data > fa_data{tmp};
		getval(fa_data, ch_data, 1, 1);
	}
	for(auto &t: ch_data) for(auto &p: t.endpoints) p.match = tokens[x][2].all() + p.match;
	getval(ch_data, ch_data, 1);
	for(auto &t : ch_data){vector < Data > tmp{t}; getval(tmp, tmp, -1);}
	for(auto t : nxt[x]) if(!vis[t]) dfz(t);
}

int main(){
	pwp[0][0] = pwp[1][0] = 1;
	for(int j = 0 ; j < 2 ; ++j) for(int i = 1 ; i < _ ; ++i) pwp[j][i] = 1ll * pwp[j][i - 1] * base % P[j];
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cin >> n >> q;
	for(int i = 1 ; i <= n ; ++i){
		string str, token; cin >> f[i] >> s[i] >> str; ch[f[i]].push_back(i);
		if(f[i]){nxt[i].push_back(f[i]); nxt[f[i]].push_back(i);}
		istringstream ss(str); while(std::getline(ss, token, '/')) tokens[i].emplace_back(token);
		while(!s[i] && tokens[i].size() < 3) tokens[i].emplace_back("");
	}
	for(int i = 1 ; i <= q ; ++i){int x; string str; cin >> x >> str; qry[x].emplace_back(i, str);}
	dfz(1);
	for(int i = 1 ; i <= q ; ++i)
		if(ans_cnt[i] == 1) cout << "1 " << ans_id[i] << '\n';
		else cout << "0 " << ans_cnt[i] << '\n';
	return 0;
}