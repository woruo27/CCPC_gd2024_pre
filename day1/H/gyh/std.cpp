#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,a[502],b[502],pos[502],ans,T[502];
deque<int>G[502],my[502],Ans,H[502];
char v[502];
inline int dfs(re int x){
	for(auto z:G[x]){
		if(v[z])continue;
		v[z]=1;
		if(my[z].size()<b[z]){my[z].push_back(x);return 1;}
		for(auto &u:my[z])if(dfs(u)){u=x;return 1;}
	}return 0;
}
inline void Del(deque<int>&A,re int x){
	for(re int i=0;i<A.size();++i)if(A[i]==x){swap(A[i],A[0]);A.pop_front();return;}
}
int main(){
	int t=read();
	while(t--){
		n=read(),m=read();
		for(re int i=1;i<=m;++i)b[i]=read();
		for(re int i=1,x;i<=n;++i){
			x=read();
			while(x--)G[i].push_back(read());
		}
		for(re int i=1;i<=n;++i)memset(v,0,sizeof(v)),ans+=dfs(i);
		for(re int i=1;i<=m;++i)for(auto z:my[i])T[z]=i;
		printf("%d\n",ans);
		while(1){
			for(re int i=1;i<=n;++i)
				if(G[i].size()&&T[i]!=G[i][0]&&my[G[i][0]].size()<b[G[i][0]])
					Del(my[T[i]],i),my[G[i][0]].push_back(i);
			re int o=0;
			for(re int i=1;i<=n;++i)
				if(G[i].size()&&T[i]==G[i][0])
					Del(my[T[i]],i),--b[T[i]],Ans.push_back(i),G[i].clear();
			for(re int i=1;i<=n;++i)
				while(G[i].size()){
					if(!b[G[i][0]])G[i].pop_front();
					else break;
				}
			for(re int i=1;i<=n;++i)H[i]=G[i],T[i]=0,random_shuffle(G[i].begin(),G[i].end());
			for(re int i=1;i<=m;++i)my[i].clear();
			re int s=0;
			for(re int i=1;i<=n;++i)memset(v,0,sizeof(v)),s+=dfs(i);
			if(!s)break;
			for(re int i=1;i<=n;++i)G[i]=H[i];for(re int i=1;i<=m;++i)for(auto z:my[i])T[z]=i;
		}
		memset(T,0,sizeof(T));for(auto z:Ans)T[z]=1;for(re int i=1;i<=n;++i)if(!T[i])Ans.push_back(i);
		for(auto z:Ans)printf("%d ",z);puts("");
		for(re int i=1;i<=n;++i)G[i].clear(),T[i]=0;for(re int i=1;i<=m;++i)my[i].clear();ans=0,Ans.clear();
	}
}



