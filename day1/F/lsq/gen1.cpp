#include"testlib.h"
const int maxn=100000,maxm=200000;
int main(int argc,char**argv){
    registerGen(argc,argv,1);
    int nx=opt<int>("n"),mx=opt<int>("m");
    int t=std::min(maxn/nx,maxm/mx);
    printf("%d\n",t);
    while(t--){
        int n=nx,m=mx;
        printf("%d %d\n",n,m);
        for(int i=1;i<=m;++i){
            int u=rnd.next(1,n),v=rnd.next(1,n-1);
            if(v>=u)++v;
            printf("%d %d\n",u,v);
        }
    }
    return 0;
}