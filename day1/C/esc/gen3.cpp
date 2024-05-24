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
std::random_device device;
std::mt19937_64 gen(device());
long long R(long long l, long long r){
	return std::uniform_int_distribution<long long>(l,r)(gen);
}
int bl[222222],pb;
int main(){
	int n=200000;
    printf("%d\n",n);
    for(int i=1;i<=n;++i){
        printf("%d%c",R(1,100000000)," \n"[i==n]);
    }
	int sum=0;
	while(sum<n-1){
		int x=std::geometric_distribution<int>(1.0/8)(gen)+1;
		bl[++pb]=dmin(x,n-1-sum);
		sum+=x;
	}
	int pv=2;
	for(int i=1;i<=pb;++i){
		printf("1%c"," \n"[i==pb&&bl[i]==1]);
		for(int j=1;j<bl[i];++j){
			printf("%d%c",pv," \n"[i==pb&&j==bl[i]-1]);
		}
		pv+=bl[i];
	}
	return 0;
}