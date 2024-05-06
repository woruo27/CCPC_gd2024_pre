#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxm=200005;
int f[maxm*3],n,st[maxm*3];
int get(int t,int x){
    x=x+t*n;
    int tp=0;
    while(f[x]!=x){
        st[++tp]=x;
        x=f[x];
    }
    while(tp)
        f[st[tp--]]=x;
    return x;
}
struct Edge{
    int v,nt;
    Edge(int v=0,int nt=0):
        v(v),nt(nt){}
}e[maxm*6];
int hd[maxm*3],num;
void qwq(int u,int v){
    e[++num]=Edge(v,hd[u]);
    hd[u]=num;
}
void link(int t,int x,int y){
    f[get(t,x)]=get(t,y);
    x=x+t*n,y=y+t*n;
    qwq(x,y);qwq(y,x);
}
int tp;
int dfs(int u,int p,int tar){
    int re=(u==tar);
    for(int i=hd[u];i;i=e[i].nt){
        int v=e[i].v;
        if(v==p)continue;
        re|=dfs(v,u,tar);
    }
    if(re)st[++tp]=(u-1)%n+1;
    return re;
}
int main(){
    // freopen("test.in","r",stdin);
    // freopen("test.ans","w",stdout);
    int T;scanf("%d",&T);
    while(T--){
        int m;
        scanf("%d%d",&n,&m);
        int k=(m+n-2)/(n-1),nk=n*k;
        for(int i=1;i<=nk;++i)f[i]=i;
        for(int i=1;i<=m;++i){
            int u,v;
            scanf("%d%d",&u,&v);
            if(get(k-1,u)==get(k-1,v))continue;
            int l=0,r=k-1;
            while(l<r){
                int mid=(l+r)/2;
                if(get(mid,u)==get(mid,v))l=mid+1;
                else r=mid;
            }
            link(l,u,v);
        }
        int s=0,t=0;
        for(int i=1;i<=n;++i){
            if(get(k-1,i)!=(k-1)*n+i){
                s=i,t=(get(k-1,i)-1)%n+1;
            }
        }
        if(s==0){
            puts("-1");
        }
        else{
            printf("%d %d\n",s,t);
            for(int i=0;i<k;++i){
                tp=0;
                dfs(i*n+s,0,i*n+t);
                printf("%d ",tp);
                while(tp){
                    printf("%d",st[tp]);
                    printf("%c"," \n"[(--tp)==0]);
                }
            }
        }
        for(int i=1;i<=nk;++i)hd[i]=0;
        num=0;
    }
    return 0;
}