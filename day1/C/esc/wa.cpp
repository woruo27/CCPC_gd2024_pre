#include<bits/stdc++.h>
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define cmax(a,b) (a<(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io{
	int F(){
		int n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
	long long G(){
		long long n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
}
struct edge{
	int to;
	int next;
}e[444444];
int pe=222222;
void insert(int a,int to){
	e[pe]=(edge){to,e[a].next};
	e[a].next=pe++;
}
int w[222222];
int siz[222222];
long long sum[222222];
long long f[222222];
void dfs(int o){
	siz[o]=1;
	sum[o]=w[o];
	std::vector<int> ch;
	for(int p=e[o].next;p;p=e[p].next){
		dfs(e[p].to);
		siz[o]+=siz[e[p].to];
		sum[o]+=sum[e[p].to];
		ch.push_back(e[p].to);
	}
	std::sort(ch.begin(),ch.end(),[&](int x, int y){
		return sum[y]/siz[y]>sum[x]/siz[x];
	});
	int presum=1;
	f[o]=w[o];
	for(int c:ch){
		f[o]+=presum*sum[c]+f[c];
		presum+=siz[c];
	}
}
int main(){
	int n=io::F();
	for(int i=1;i<=n;++i){
		w[i]=io::F();
	}
	for(int i=2;i<=n;++i){
		int fa=io::F();
		insert(fa,i);
	}
	dfs(1);
	printf("%lld\n",f[1]);
	return 0;
}