#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=100005,maxm=200005;
struct Edge{
    int v,w,nt;
    Edge(int v=0,int w=0,int nt=0):
        v(v),w(w),nt(nt){}
}e[maxm*2];
int hd[maxn],num=1;
void qwq(int u,int v,int w){
    e[++num]=Edge(v,w,hd[u]),hd[u]=num;
}
int q[maxn],dis[maxn],n;
int bfs(int s,int t){
    for(int i=1;i<=n;++i)
        dis[i]=0;
    int fro=0,bac=0;
    dis[q[bac++]=s]=1;
    while(fro<bac){
        int u=q[fro++];
        for(int i=hd[u];i;i=e[i].nt){
            int v=e[i].v;
            if(e[i].w&&!dis[v]){
                dis[q[bac++]=v]=dis[u]+1;
            }
        }
    }
    return dis[t];
}
int cur[maxn];
int dfs(int u,int sm,int t){
    if(u==t)return sm;
    int re=0;
    for(int&i=cur[u];i;i=e[i].nt){
        int v=e[i].v,w=e[i].w;
        if(dis[v]==dis[u]+1&&w){
            int fw=dfs(v,min(sm,w),t);
            sm-=fw;e[i].w-=fw;
            re+=fw;e[i^1].w+=fw;
        }
    }
    return re;
}
int dinic(int s,int t){
    int re=0;
    while(bfs(s,t)){
        for(int i=1;i<=n;++i)cur[i]=hd[i];
        re+=dfs(s,0x3f3f3f3f,t);
    }
    return re;
}
int st[maxm],tp;
void sear(int u,int t){
    st[++tp]=u;
    if(u==t)return;
    for(int i=hd[u];i;i=e[i].nt){
        int v=e[i].v,w=e[i].w;
        if(!w){
            ++e[i].w;--e[i^1].w;
            return sear(v,t);
        }
    }
}
int main(){
    // freopen("test.in","r",stdin);
    // freopen("test.out","w",stdout);
    int T;scanf("%d",&T);
    while(T--){
        int m;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;++i){
            int u,v;
            scanf("%d%d",&u,&v);
            qwq(u,v,1);qwq(v,u,1);
        }
        int k=(m+n-2)/(n-1),ok=false;
        for(int s=1;s<=n&&!ok;++s){
            for(int t=s+1;t<=n&&!ok;++t){
                if(dinic(s,t)>=k){
                    printf("%d %d\n",s,t);
                    for(int i=1;i<=k;++i){
                        tp=0;
                        sear(s,t);
                        printf("%d ",tp);
                        for(int i=1;i<=tp;++i)
                            printf("%d%c",st[i]," \n"[i==tp]);
                    }
                    ok=true;
                }
                for(int i=2;i<=num;++i)
                    e[i].w=1;
            }
        }
        if(!ok)puts("-1");
        num=1;
        for(int i=1;i<=n;++i)
            hd[i]=0;
    }
    return 0;
}