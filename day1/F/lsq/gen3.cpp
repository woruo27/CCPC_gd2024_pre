#include"testlib.h"
#include<queue>
const int maxn=100000,maxm=200000;
struct EdgeX{
    int u,v;
    EdgeX(int u=0,int v=0){
        if(rnd.next(0,1))
            this->u=u,this->v=v;
        else
            this->v=u,this->u=v;
    }
}e[maxm+5];
int num;
void OpEdge(void){
    shuffle(e+1,e+num+1);
    for(int i=1;i<=num;++i)
        printf("%d %d\n",e[i].u,e[i].v);
    num=0;
}
int d[maxn+5],p[maxn+5];
std::priority_queue<int>q;
void gen_tree(int n){
    for(int i=1;i<=n-2;++i)
        ++d[p[i]=rnd.next(1,n)];
    for(int i=1;i<=n;++i)
        if(d[i]==0)q.push(i);
    for(int i=1;i<=n-2;++i){
        int u=q.top();q.pop();
        e[++num]=EdgeX(u,p[i]);
        if((--d[p[i]])==0)
            q.push(p[i]);
    }
    int u=q.top();q.pop();
    int v=q.top();q.pop();
    e[++num]=EdgeX(u,v);
}
int main(int argc,char**argv){
    registerGen(argc,argv,1);
    int nx=opt<int>("n"),mx=opt<int>("m");
    int t=std::min(maxn/nx,maxm/mx);
    printf("%d\n",t);
    while(t--){
        int n=nx,m=mx;
        printf("%d %d\n",n,m);
        num=0;
        if(m>=n-1){
            int km=m/(n-1)*(n-1);
            gen_tree(n);
            for(int i=n;i<=km;++i){
                int u=e[i-n+1].u,v=e[i-n+1].v;
                e[i]=EdgeX(u,v);
            }
            num=km;
            m-=km;
        }
        for(int i=1;i<=m;++i){
            int u=rnd.next(1,n),v=rnd.next(1,n-1);
            if(v>=u)++v;e[++num]=EdgeX(u,v);
        }
        OpEdge();
    }
    return 0;
}