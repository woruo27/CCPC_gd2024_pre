#include"testlib.h"
#include <bits/stdc++.h>
#define re register
using namespace std;
int n,m,b[1002],a[1002],num;
vector<int>G[1002]; 
int main(int argc, char* argv[]){
	registerTestlibChecker(argc, argv);
	int t=inf.readInt(1,500);
	while(t--){
		n=inf.readInt(1,500),m=inf.readInt(1,500);
		for(re int i=1;i<=m;++i)b[i]=inf.readInt(0,500);
		for(re int i=1;i<=n;++i){
			G[i].clear();
			re int x=inf.readInt(0,m);
			while(x--)G[i].push_back(inf.readInt(1,m));
		}
		int pans=ouf.readInt(0,n),jans=ans.readInt(0,n);
		if(pans!=jans)quitf(_wa,"wrong answer");
		memset(a,0,sizeof(a));
		int o=0;
		for(re int i=1;i<=n;++i){
			int x=ouf.readInt(1,n);
			if(a[x])quitf(_wa,"not a permutation");a[x]=1;
			for(auto z:G[x])if(b[z]){--b[z];++o;break;}
		}
		if(o!=jans)quitf(_wa,"wrong rearrangement %d %d",o,jans);
	}
	quitf(_ok,"Correct!");
}
