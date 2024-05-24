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
int main(){
	int n=200000;
    printf("%d\n",n);
    for(int i=1;i<=n;++i){
        printf("%d%c",R(1,1<<R(1,26))," \n"[i==n]);
    }
    for(int i=2;i<=n;++i){
        printf("%d%c",R(1,i-1)," \n"[i==n]);
    }
	return 0;
}