#include"testlib.h"
const int maxn=100000,maxm=200000;
int N[maxm+5],M[maxm+5];
int main(int argc,char**argv){
    registerGen(argc,argv,1);
    int nx=opt<int>("n"),mx=opt<int>("m");
    int t=0,sn=maxn,sm=maxm;
    while(sn>=2&&sm>=1){
        ++t;
        N[t]=rnd.next(2,std::min(nx,sn));
        M[t]=rnd.next(1,std::min(mx,sm));
        sn-=N[t];sm-=M[t];
    }
    printf("%d\n",t);
    for(int i=1;i<=t;++i){
        int n=N[i],m=M[i];
        printf("%d %d\n",n,m);
        for(int i=1;i<=m;++i){
            int u=rnd.next(1,n),v=rnd.next(1,n-1);
            if(v>=u)++v;
            printf("%d %d\n",u,v);
        }
    }
    return 0;
}