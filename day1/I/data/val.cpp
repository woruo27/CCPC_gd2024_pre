#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define uint unsigned int
#define ull unsigned lint
#define db double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define gc getchar()
#define lb(x) ((x)&-(x))
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
inline int getn(int a,int b) { return (rand()*32767+rand())%(b-a+1)+a; }
int inn() { int x;scanf("%d",&x);return x; }
inline void R(int x,int l,int r) { assert(x>=l&&x<=r); }
int main()
{
	rep(id,1,40)
	{
		debug(id)sp;string ids;for(int x=id;x;x/=10) ids+=char('0'+x%10);
		reverse(ids.begin(),ids.end()),freopen((ids+".in").c_str(),"r",stdin);
		int n=inn(),m=inn();
		R(n,1,200000),R(m,1,200000);
		while(m--) R(inn(),1,n),R(inn(),1,n),R(inn(),1,n);
		fclose(stdin);
		debug(id)ln;
	}
	return 0;
}
