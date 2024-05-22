#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define lint long long
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
typedef pair<int,int> pii;
inline int inn() { int x;scanf("%d",&x);return x; }
const int N=200010;
int x[N],y[N],z[N],d[N],val[N],c[N];
vector<pii> g[N];
inline lint solve(int n)
{
	queue<int> q;int cnt=0;
	rep(i,1,n) if(!d[i]) q.push(i),val[i]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop(),cnt++;
		for(pii t:g[u])
		{
			int v=t.fir,id=t.sec;c[id]--;
			if(!c[id]) d[v]--,val[x[id]]=max(val[x[id]],val[y[id]]+val[z[id]]);
			if(!d[v]) q.push(v);
		}
	}
	lint ans=0;rep(i,1,n) ans+=val[i];
	return (cnt==n)?((ans<=1000000000)?ans:-1):-1;
}
int main()
{
	int n=inn(),m=inn();
	rep(i,1,m)
		x[i]=inn(),y[i]=inn(),z[i]=inn(),d[x[i]]++,c[i]=2,
		g[y[i]].pb(mp(x[i],i)),g[z[i]].pb(mp(x[i],i));
	return !printf("%lld\n",solve(n));
}
