#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define lint long long
using namespace std;
inline int inn() { int x;scanf("%d",&x);return x; }
const int N=200010;vector<int> g[N];long long ans[N],w[N];int sz[N];
inline bool cmp(int x,int y) { return (lint)w[x]*sz[y]<(lint)w[y]*sz[x]; }
void dfs(int x)
{
	for(auto y:g[x]) dfs(y);
	sort(g[x].begin(),g[x].end(),cmp),ans[x]=w[x],sz[x]=1;
	for(auto y:g[x]) ans[x]+=sz[x]*w[y]+ans[y],sz[x]+=sz[y],w[x]+=w[y];
}
int main()
{
	int n=inn();rep(i,1,n) w[i]=inn();
	rep(i,2,n) g[inn()].push_back(i);
	return dfs(1),!printf("%lld\n",ans[1]);
}
