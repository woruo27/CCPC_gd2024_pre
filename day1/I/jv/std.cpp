#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
const int mod=998244353,N=2e5+5,inf=1e9+1;
typedef long long ll;
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second

void add(int &x,int y){x=(x+y>=mod)?(x+y-mod):x+y;}
int qpow(int x,int y){int ret=1;while(y){if(y&1)ret=1ll*ret*x%mod;x=1ll*x*x%mod;y>>=1;}return ret;}
int n,m,ord[N],ans[N],l=1,r,q[N],deg[N],cnt,tot;

vector<int>f[N];vector<pii>cst[N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1,x,y,z;i<=m;i++){
        cin>>x>>y>>z;f[x].pb(y);f[x].pb(z);++deg[y];++deg[z];cst[x].pb(mp(y,z));
    }
    rep(i,1,n)if(deg[i]==0)q[++r]=i;
    while(l<=r){
        int u=q[l++];ord[++cnt]=u;
        for(auto v:f[u]){
            --deg[v];if(deg[v]==0)q[++r]=v;
        }
    }
    if(cnt<n){
        printf("-1\n");return 0;
    }
    reverse(ord+1,ord+n+1);
    rep(i,1,n)printf("%d ",ord[i]);puts("");
    rep(i,1,n){
        int u=ord[i];
        ans[u]=1;
        for(auto x:cst[u])ans[u]=max(ans[u],ans[x.fi]+ans[x.se]);
        ans[u]=min(ans[u],inf);
        tot+=ans[u];
        if(tot>=inf){
            printf("-1\n");return 0;
        }
    }
    printf("%d\n",tot);
    rep(i,1,n)printf("%d ",ans[i]);
	return 0;
}
