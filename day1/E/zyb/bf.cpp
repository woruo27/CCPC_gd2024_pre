#include<bits/stdc++.h>
using namespace std;
int ans,a[10],b[10],c[10][10],n,m,d[10];
bool chk1(){
	for(int i = 1;i <= m + 1;++i){
		bool fg = 1;
		for(int j = 1;j <= m + 1;++j){
			if(i != j && c[d[i]][d[j]]){
				fg = 0;
				break;
			}
		}
		if(fg) return 1;
	}
	return 0;
}
bool chk2(){
	for(int i = 1;i <= m + 1;++i){
		bool fg = 1;
		for(int j = 1;j <= m + 1;++j){
			if(i != j && !c[d[i]][d[j]]){
				fg = 0;
				break;
			}
		}
		if(fg) return 1;
	}
	return 0;
}
bool dfs(int x,int y){
	if(x == n){
		if(y != m + 2) return 1;
		return chk1() && chk2();
	}
	d[y] = x;
	if(!dfs(x + 1,y + 1)) return 0;
	return dfs(x + 1,y);
}
void chk(int x){
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	for(int i = 0,l = 0;i < n - 1;++i){
		for(int j = i + 1;j < n;++j){
			int k = x & (1 << l);
			if(k) c[i][j] = 1,++a[i];
			else c[j][i] = 1,++a[j];
			++l;
		}
	}
	int sl = 0;
	for(int i = 0;i < n;++i){
		if(!b[a[i]]) ++sl;
		b[a[i]] = 1;
		if(sl >= ans) return;
	}
	/*
	cerr<<n<<" "<<m<<" "<<x<<": ";
	for(int i = 0;i < n;++i) cerr<<a[i]<<" ";cerr<<endl; 
	for(int i = 0;i < n;++i){
		for(int j = 0;j < n;++j){
			cerr<<c[i][j]<<" ";
		}
		cerr<<endl;
	}
	cerr<<sl<<endl;
	*/
	if(dfs(0,1)) ans = sl;
}
int main(){
	for(int i = 2;i <= 8;++i){
		for(int j = 1;j < i;++j){
			n = i;m = j;
			ans = n;
			for(int l = 1;l < (1 << (n * (n - 1) / 2));l += 2){
				chk(l);
			}
			cerr<<ans<<" ";
		}
		cerr<<endl;
	}
	return 0;
} 
