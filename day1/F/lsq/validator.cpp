#include"testlib.h"
const int maxT=10'000,
    maxN=100'000,sumN=100'000,
    maxM=200'000,sumM=200'000;
int main(int argc,char**argv){
    registerValidation(argc,argv);
    int T=inf.readInt(1,maxT,"T");
    inf.readEoln();
    int sn=0,sm=0;
    for(int i=1;i<=T;++i){
        setTestCase(i);
        int n=inf.readInt(2,maxN,"n");inf.readSpace();
        int m=inf.readInt(1,maxM,"m");inf.readEoln();
        sn+=n;sm+=m;
        ensuref(sn<=maxN,format("sum of n should not exceed %d",sumN).c_str());
        ensuref(sm<=maxM,format("sum of n should not exceed %d",sumM).c_str());
        for(int j=1;j<=m;++j){
            int u=inf.readInt(1,n,"u");inf.readSpace();
            int v=inf.readInt(1,n,"v");inf.readEoln();
            ensuref(u!=v,"No self-loop.");
        }
    }
    inf.readEof();
    return 0;
}