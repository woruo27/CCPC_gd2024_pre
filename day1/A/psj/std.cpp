#include<bits/stdc++.h>
using namespace std;

#define int long long
const int _ = 3e5 + 7 , __ = _ * 3;

namespace bit{
	#define lowbit(x) ((x) & -(x))
	int arr[__];
	void add(int x , int v){while(x < __){arr[x] += v; x += lowbit(x);}}
	int qry(int x){int sum = 0; while(x){sum += arr[x]; x -= lowbit(x);} return sum;}
}using bit::add, bit::qry;
struct line{
	int x1, y1, x2, y2;
	void input(){cin >> x1 >> y1 >> x2 >> y2;}
	void swapdim(){swap(x1, y1); swap(x2, y2);}
}; vector < line > hor, col; int n;
struct Eve{int tm, pos, type;}; 

map < int , vector < line > > getbatch(vector < line > dat, bool swap){
	if(swap) for(auto &t : dat) t.swapdim();
	vector < Eve > event; 
	for(auto t : dat){event.push_back((Eve){t.y1, t.x1, 0}); event.push_back((Eve){t.y2, t.x1, 1});}
	sort(event.begin(), event.end(), [&](Eve p, Eve q){return p.tm < q.tm || p.tm == q.tm && p.type < q.type;});

	map < int , int > cur;
	map < int , vector < line > > ans;
	set < int > lines {(int)-1e18, (int)-1e16, (int)-1e14, (int)1e14, (int)1e16, (int)1e18};
	for(auto eve: event){
		assert((lines.find(eve.pos) != lines.end()) == eve.type);
		auto adjust = [&](auto pos, bool type, int width){
			while(width--){
				auto pos1 = pos; ++pos1; auto pos2 = pos1; ++pos2;
				if(*pos2 - *pos1 == *pos1 - *pos)
					if(type) cur[*pos] = eve.tm;
					else{
						line res{*pos, cur[*pos], *pos2, eve.tm - (*pos2 - *pos)};
						if(res.y2 >= res.y1){
							if(swap) res.swapdim();
							ans[*pos2 - *pos].push_back(res);
						}
						cur.erase(cur.find(*pos));
					}
				--pos;
			}
		};
		adjust(--lines.upper_bound(eve.pos), 0, 2 + eve.type);
		eve.type ? (void)lines.erase(eve.pos) : (void)lines.insert(eve.pos);
		adjust(--lines.upper_bound(eve.pos), 1, 3 - eve.type);
	}
	return ans;
}

signed main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for(int i = 1 ; i <= n ; ++i){line tmp; tmp.input(); (tmp.x1 == tmp.x2 ? col : hor).push_back(tmp);}
	map < int, vector < line > > batchcol = getbatch(col, 0) , batchhor = getbatch(hor, 1);
	int ans = 0;
	for(auto &p: batchcol)
		if(batchhor.find(p.first) != batchhor.end()){
			vector < line > col = p.second , hor = batchhor[p.first]; vector < Eve > eve;
			for(auto t : col){
				eve.push_back((Eve){t.y1, t.x1, 1});
				eve.push_back((Eve){t.y2 + 1, t.x1, -1});
			}
			for(auto t : hor){
				eve.push_back((Eve){t.y1, t.x2, 2});
				eve.push_back((Eve){t.y1, t.x1 - 1, -2});
			}
			vector < int > lsh; for(auto t : eve) lsh.push_back(t.pos);
			sort(lsh.begin(), lsh.end());
			for(auto &t : eve) t.pos = lower_bound(lsh.begin(), lsh.end(), t.pos) - lsh.begin() + 1;
			sort(eve.begin(), eve.end(), [&](Eve p, Eve q){return p.tm < q.tm || p.tm == q.tm && abs(p.type) < abs(q.type);});
			for(auto t : eve)
				if(abs(t.type) == 1) bit::add(t.pos, t.type);
				else ans += (t.type >> 1) * bit::qry(t.pos);
		}
	cout << ans << '\n'; 
}