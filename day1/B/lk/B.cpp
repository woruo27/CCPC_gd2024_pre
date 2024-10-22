/*
Author: QAQAutoMaton
Lang: C++
Code: ac.cpp
Mail: lk@qaq-am.com
Blog: https://www.qaq-am.com/
*/
#include<bits/stdc++.h>
#define debug(qaq...) fprintf(stderr,qaq)
#define DEBUG printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define Debug debug("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define all(x) x.begin(),x.end()
#define x first
#define y second
#define unq(a) sort(all(a)),a.erase(unique(all(a)),a.end())
using namespace std;
typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef complex<double> cp;
typedef pair<int,int> pii;
int inf;
const double eps=1e-8;
const double pi=acos(-1.0);
template<class T,class T2>int chkmin(T &a,T2 b){return a>b?a=b,1:0;}
template<class T,class T2>int chkmax(T &a,T2 b){return a<b?a=b,1:0;}
template<class T>T sqr(T a){return a*a;}
template<class T,class T2>T mmin(T a,T2 b){return a<b?a:b;}
template<class T,class T2>T mmax(T a,T2 b){return a>b?a:b;}
template<class T>T aabs(T a){return a<0?-a:a;}
template<class T>int dcmp(T a,T b){return a>b;}
template<int *a>int cmp_a(int x,int y){return a[x]<a[y];}
template<class T>bool sort2(T &a,T &b){return a>b?swap(a,b),1:0;}
template<class T,class ...T2>T mmin(T a,T2 ...b){return mmin(a,mmin(b...));}
template<class T,class ...T2>T mmax(T a,T2 ...b){return mmax(a,mmax(b...));}
#define min mmin
#define max mmax
#define abs aabs
struct __INIT__{
	__INIT__(){
		fill((unsigned char*)&inf,(unsigned char*)&inf+sizeof(inf),0x3f);
	}
}__INIT___;
namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	// getchar
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	// print the remaining part
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	// putchar
	inline void putc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	template<typename A>
	inline bool read (A &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;else if(c==EOF)return 0;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
		return 1;
	}
	inline bool read (char &x) {
		while((x=gc())==' '||x=='\n' || x=='\r');
		return x!=EOF;
	}
	inline bool read(char *x){
		while((*x=gc())=='\n' || *x==' '||*x=='\r');
		if(*x==EOF)return 0;
		while(!(*x=='\n'||*x==' '||*x=='\r'||*x==EOF))*(++x)=gc();
		*x=0;
		return 1;
	}
	template<typename A,typename ...B>
	inline bool read(A &x,B &...y){
		return read(x)&&read(y...);
	}
	template<typename A>
	inline bool write (A x) {
		if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) putc (qu[qr --]);
		return 0;
	}
	inline bool write (char x) {
		putc(x);
		return 0;
	}
	inline bool write(const char *x){
		while(*x){putc(*x);++x;}
		return 0;
	}
	inline bool write(char *x){
		while(*x){putc(*x);++x;}
		return 0;
	}
	template<typename A,typename ...B>
	inline bool write(A x,B ...y){
		return write(x)||write(y...);
	}
	//no need to call flush at the end manually!
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: read;
using io :: putc;
using io :: write;
const int p[]={956849779,982649851,982649851};
const int q[]={17,31,59};
const int k=2;
int l,c,mo;
array<int,k+2> pre[3000005],suf[3000005]; 
char s[3000005];
int h[k],pw[3000005],hp[k];
int fail[3000005];
signed main(){
#ifdef QAQAutoMaton 
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
#endif
	read(l,c,mo);
	int m=0;
	pw[0]=1;
	for(int i=1;i<=3000000;++i)pw[i]=(ll)pw[i-1]*c%mo;
	int ans=(ll)l*l%mo;
	for(;l;--l){
		read(s+1);
		int n=strlen(s+1);
		for(int i=0;i<k;++i)h[i]=0;
		fail[1]=0;
		for(int i=1;i<=n;++i){
			for(int j=0;j<k;++j)h[j]=((ll)h[j]*q[j]+s[i])%p[j];
			++m;
			pre[m][0]=i;
			for(int j=1;j<=k;++j)pre[m][j]=h[j-1];
			pre[m][k+1]=pw[i]-pw[fail[i]];
			int j=fail[i];
			while(j && s[j+1]!=s[i+1])j=fail[j];
			fail[i+1]=s[j+1]==s[i+1]?j+1:0;
		}
		m-=n;
		reverse(s+1,s+n+1);
		for(int j=0;j<k;++j)h[j]=0,hp[j]=1;
		for(int i=1;i<=n;++i){
			for(int j=0;j<k;++j){
				h[j]=((ll)hp[j]*s[i]+h[j])%p[j];
				hp[j]=(ll)hp[j]*q[j]%p[j];
			}
			++m;
			suf[m][0]=i;
			for(int j=1;j<=k;++j)suf[m][j]=h[j-1];
			suf[m][k+1]=pw[i]-pw[fail[i]];
			int j=fail[i];
			while(j && s[j+1]!=s[i+1])j=fail[j];
			fail[i+1]=s[j+1]==s[i+1]?j+1:0;
		}
	}
	sort(pre+1,pre+m+1);
	sort(suf+1,suf+m+1);
	for(int i=1,j=1;i<=m && j<=m;){
		if(pre[i]!=suf[j]){
			if(pre[i]<suf[j])++i;else ++j;
		}
		else{
			int c1=0,c2=0;
			while(pre[i+c1]==pre[i])++c1;
			while(suf[j+c2]==suf[j])++c2;
			ans=(ans+(ll)c1*c2%mo*(pre[i][k+1]+mo))%mo;
			i+=c1;j+=c2;
		}
	}
	printf("%d\n",ans);
	return 0;
}
