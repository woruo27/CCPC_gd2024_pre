#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include "testlib.h"

using std::map;
using std::pair;
using std::make_pair;
using std::swap;
const int maxT=10'000,
    maxN=100'000,sumN=100'000,
    maxM=200'000,sumM=200'000;
map<pair<int,int>,int> mp,vis;
int s[maxM+5];
int chk(int u,int v){
    if(u>v)swap(u,v);
    pair<int,int>tmp=make_pair(u,v);
    return (++vis[tmp])<=mp[tmp];
}

int main(int argc, char **argv){
	// registerTestlibCmd(argc, argv);
    registerLemonChecker(argc, argv);
    int T=inf.readInt(1,maxT,"T");
    int sn=0,sm=0;
    for(int i=1;i<=T;++i){
        int n=inf.readInt(2,maxN,"n"),m=inf.readInt(1,maxM,"m");
        sn+=n;sm+=m;
        ensuref(sn<=maxN,"sum of n should not exceed 100000.");
        ensuref(sm<=maxM,"sum of m should not exceed 200000.");
        for(int i=1;i<=m;++i){
            int u=inf.readInt(1,n,"u"),v=inf.readInt(1,n,"v");
            ensuref(u!=v,"No self-loop.");
            if(u>v)swap(u,v);
            ++mp[make_pair(u,v)];
        }
        int k=(m+n-2)/(n-1);
        int anss=ans.readInt(1,n),anst=ans.readInt(1,n);
        ensuref(anss!=anst,"s should not be equal to t.");
        for(int j=1;j<=k;++j){
            int cn=ans.readInt(1,m+1);
            for(int k=1;k<=cn;++k)
                s[k]=ans.readInt(1,n);
            ensuref(s[1]==anss,"Begin in s.");
            ensuref(s[cn]==anst,"End in t.");
            for(int k=1;k<cn;++k){
                int u=s[k],v=s[k+1];
                ensuref(chk(u,v),"No edge cross.");
            }
        }
        vis.clear();
        int oufs=ouf.readInt(1,n),ouft=ouf.readInt(1,n);
        ensuref(oufs!=ouft,"s should not be equal to t.");
        for(int j=1;j<=k;++j){
            int cn=ouf.readInt(1,m+1);
            for(int k=1;k<=cn;++k)
                s[k]=ouf.readInt(1,n);
            ensuref(s[1]==oufs,"Begin in s.");
            ensuref(s[cn]==ouft,"End in t.");
            for(int k=1;k<cn;++k){
                int u=s[k],v=s[k+1];
                ensuref(chk(u,v),"No edge cross.");
            }
        }
        vis.clear();
        mp.clear();
    }
	quitf(_ok, "AC\n");
	return 0;
}
